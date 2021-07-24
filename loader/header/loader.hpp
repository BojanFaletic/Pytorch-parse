#pragma once

#include <errno.h>
#include <iostream>
#include <string>
#include <vector>
#include <zip.h>

// for parsing .pkl file
struct nn_layer {
  std::string name;
  std::string weight, bias;
};

// layer weights or biases
struct nn_parameters {
  std::string name;
  float *weight_param;
  float *bias_param;
  uint32_t weight_size;
  uint32_t bias_size;
};

int read_content(zip *z, const char *f_name, char *content, uint32_t &size);
int check_version(zip *z);

std::vector<std::string> data_names(zip *z);
std::vector<nn_layer> file_content(zip *z);
std::vector<nn_parameters> data_content(zip *z, std::string const &name);
std::vector<nn_parameters> read_zip_file(char const *name);
