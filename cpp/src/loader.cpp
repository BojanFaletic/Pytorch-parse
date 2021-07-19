#include "loader.hpp"

int check_version(zip *z) {
  const char *f_name = "archive/version";

  struct zip_stat st;
  zip_stat_init(&st);
  zip_stat(z, f_name, 0, &st);

  if (st.valid == 0) {
    std::cout << "File not found\n";
    return EXIT_FAILURE;
  }

  char *content = new char[st.size];

  zip_file *f = zip_fopen(z, f_name, 0);
  zip_fread(f, content, st.size);
  zip_fclose(f);

  uint32_t version_num;
  sscanf(content, "%u", &version_num);
  delete[] content;

  constexpr uint32_t min_version = 3;
  if (version_num >= min_version) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int read_zip_file(char const *name) {
  int err;
  zip *z = zip_open(name, 0, &err);

  if (err == 9) {
    std::cout << "zip not found: err " << err << "\n";
    return 1;
  }

  int status = check_version(z);
  std::cout << status << "\n";

  zip_close(z);

  return 0;
}
