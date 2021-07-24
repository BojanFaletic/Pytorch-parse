#pragma once
#include <stdint.h>
// find idx of first occurrence of key in string of length c_size

// search from beggining of string to end
int find_first_of(char const *ch, uint32_t c_size, char const *key);

// search from end of string to beginning
int find_reverse_first_of(char const *ch, uint32_t c_size, char const *key);