#include "loader.hpp"
#include <string.h>
#include "string_util.hpp"

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

std::vector<nn_layer> file_content(zip *z) {
  const char *f_name = "archive/data.pkl";

  char *content = nullptr;
  uint32_t size = 0;
  read_content(z, f_name, &content, size);

  std::vector<nn_layer> layers;

  std::vector<std::string> params = data_names(z);

  // parse input
  for (std::string const &n : params) {
    struct nn_layer single_layer;

    int found = find_first_of(content, size, n.c_str());

    if (found != -1){
      std::cout << "found at idx: " << found << " " << n << '\n';

      if (strcmp(n.c_str(), "94779429638048") == 0){
        std::cout << "here\n";
      }
      // look back to find name
      int bias_idx = find_reverse_first_of(content, found, "bias");
      int weight_idx = find_reverse_first_of(content, found, "weight");


      if (bias_idx == -1 && weight_idx == -1){
        std::cerr << "No valid weight or bias file found\n";
        exit(1);
      }
      bool valid_bias = false;
      bool valid_weight = false;
      std::string name = n;
      if (bias_idx > weight_idx){
        valid_bias = true;
      }
      else{
        valid_weight = true;
      }
      int valid_idx = std::max(bias_idx, weight_idx);

      // search back to find name
      const uint32_t max_layer_name = 16;
      uint32_t it = 0;
      for (int i=0; i<max_layer_name; i++){
        char letter = *(content + valid_idx - i);
        if (letter == 'X'){
          it = i-1;
          break;
        }
      }
      uint32_t str_start = valid_idx - it;
      // increment start pointer to remove non ASCII characters
      uint32_t offset = 0;
      while (!std::isalpha(content[str_start + offset])){
        offset++;
      }
      str_start = str_start+offset;

      // decrete end ptr to remove dot
      for (uint32_t i=0; i<it; i++){
        if (content[str_start+i] == '.'){
          it = i;
          break;
        }
      }

      std::string layer_name(content+str_start, it);

      std::cout << layer_name << "\n";

      // assign name
      single_layer.name = layer_name;


      // check if name is unique, else add it to layers
      bool layer_exists = false;
      for (nn_layer &nn : layers){
        if (nn.name == single_layer.name){
          // found existing name
          if (valid_weight){
            nn.weight = name;
          }
          if (valid_bias){
            nn.bias = name;
         }
         layer_exists = true;
         break;
        }
      }
      if (!layer_exists){
        struct nn_layer l;
        l.name = layer_name;
        if (valid_weight){
          l.weight = name;
        }
        if (valid_bias){
          l.bias = name;
        }

        // append to layer list
        layers.push_back(l);
      }

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

int read_zip_file(char const *name) {
  int err;
  zip *z = zip_open(name, 0, &err);

  if (err == 9) {
    std::cerr << "zip not found: err " << err << "\n";
    exit(1);
  }

  int status = check_version(z);
  std::cout << status << "\n";

  auto aa = file_content(z);

  zip_close(z);

  return 0;
}
