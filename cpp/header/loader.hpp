#pragma once

#include <errno.h>
#include <iostream>
#include <zip.h>

int read_zip_file(char const *name);
int check_version(zip *z);