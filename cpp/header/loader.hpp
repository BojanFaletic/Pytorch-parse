#pragma once

#include <errno.h>
#include <iostream>
#include <zip.h>
#include <vector>
#include <string>

struct nn_layer{
    std::string name;
    std::string weight, bias;
};


int read_content(zip *z, const char *f_name, char *content, uint32_t &size);
int read_zip_file(char const *name);
int check_version(zip *z);

std::vector<std::string> data_names(zip *z);
std::vector<nn_layer> file_content(zip *z);