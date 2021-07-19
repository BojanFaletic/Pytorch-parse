#include "loader.hpp"
#include "string_util.hpp"
#include <string.h>

int read_content(zip *z, const char *f_name, char **content, uint32_t &size) {
  struct zip_stat st;
  zip_stat_init(&st);
  zip_stat(z, f_name, 0, &st);

  if (st.valid == 0) {
    std::cerr << "File not found\n";
    return EXIT_FAILURE;
  }

  *content = new char[st.size];
  size = st.size;

  zip_file *f = zip_fopen(z, f_name, 0);
  zip_fread(f, *content, st.size);
  zip_fclose(f);
  return EXIT_SUCCESS;
}

int check_version(zip *z) {
  const char *f_name = "archive/version";
  char *content = nullptr;
  uint32_t size;

  read_content(z, f_name, &content, size);

  uint32_t version_num;
  sscanf(content, "%u", &version_num);
  delete[] content;

  constexpr uint32_t min_version = 3;
  if (version_num < min_version) {
    std::cerr << "Found version is to old\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static std::string find_layer_name(const char *content, int start_idx) {
  const uint32_t max_layer_name = 32;
  uint32_t it = 0;
  for (uint32_t i = 0; i < max_layer_name; i++) {
    if (content[start_idx - i] == 'X') {
      it = i - 1;
      break;
    }
  }
  start_idx -= it;

  // remove zeros before layer name
  while (!std::isalpha(content[start_idx++])) {
  }

  // remove tail
  for (uint32_t i = 0; i < it; i++) {
    if (content[start_idx + i] == '.') {
      it = i;
      break;
    }
  }
  return std::string(content + start_idx - 1, it + 1);
}

static void add_layer_to_stack(std::vector<nn_layer> &layers, bool is_b_or_w,
                               std::string const &layer_name,
                               std::string const &param) {
  // check if name is unique, else add it to layers
  bool layer_exists = false;
  for (nn_layer &nn : layers) {
    if (nn.name == layer_name) {
      if (is_b_or_w) {
        nn.bias = param;
      } else {
        nn.weight = param;
      }
      layer_exists = true;
      break;
    }
  }
  if (!layer_exists) {
    struct nn_layer l;
    l.name = layer_name;
    if (is_b_or_w) {
      l.bias = param;
    } else {
      l.weight = param;
    }
    layers.push_back(l);
  }
}

std::vector<nn_layer> file_content(zip *z) {
  const char *f_name = "archive/data.pkl";
  std::vector<nn_layer> layers;

  char *content = nullptr;
  uint32_t size = 0;
  read_content(z, f_name, &content, size);

  std::vector<std::string> const param_names = data_names(z);
  for (std::string const &name : param_names) {
    int data_name = find_first_of(content, size, name.c_str());
    if (data_name != -1) {
      // look back to find name
      int bias_idx = find_reverse_first_of(content, data_name, "bias");
      int weight_idx = find_reverse_first_of(content, data_name, "weight");

      if (bias_idx == -1 && weight_idx == -1) {
        std::cerr << "No valid weight or bias file found\n";
        exit(1);
      }

      bool is_bias_or_weight = (bias_idx > weight_idx);
      int param_idx = (is_bias_or_weight) ? bias_idx : weight_idx;

      std::string const layer_name = find_layer_name(content, param_idx);
      add_layer_to_stack(layers, is_bias_or_weight, layer_name, name);
    }
  }
  delete[] content;
  return layers;
}

std::vector<std::string> data_names(zip *z) {
  std::vector<std::string> files;

  zip_int64_t num_entries = zip_get_num_entries(z, 0);
  for (int i = 0; i < num_entries; i++) {
    const char *name = zip_get_name(z, i, 0);

    constexpr char prefix[] = "archive/data/";
    if (memcmp(name, prefix, sizeof(prefix) - 1) != 0) {
      continue;
    }

    uint32_t length = strlen(name);
    uint32_t start_ptr = 0;
    for (int i = length - 1; i > 0; i--) {
      if (std::isdigit(name[i])) {
        start_ptr = i;
      }
    }
    files.push_back(&name[start_ptr]);
  }
  return files;
}

std::vector<nn_parameters> data_content(zip *z,
                                        std::vector<nn_layer> const &names) {
  std::vector<nn_parameters> out;

  for (nn_layer const &l : names) {
    std::string const w_name = "archive/data/" + l.weight;
    std::string const b_name = "archive/data/" + l.bias;

    char *w_content = nullptr;
    char *b_content = nullptr;
    uint32_t w_size = 0;
    uint32_t b_size = 0;
    read_content(z, w_name.c_str(), &w_content, w_size);
    read_content(z, b_name.c_str(), &w_content, w_size);

    // init struct for single layer
    struct nn_parameters p;
    p.name = l.name;
    p.weight_param = (float *)w_content;
    p.weight_size = w_size;
    p.bias_param = (float *)b_content;
    p.bias_size = b_size;
    out.push_back(p);
  }
  return out;
}

std::vector<nn_parameters> read_zip_file(char const *name) {
  int err;
  zip *z = zip_open(name, 0, &err);
  if (err == 9) {
    std::cerr << "zip not found: err " << err << "\n";
    exit(1);
  }
  check_version(z);
  std::vector<nn_layer> const layers = file_content(z);
  std::vector<nn_parameters> res = data_content(z, layers);
  zip_close(z);
  return res;
}
