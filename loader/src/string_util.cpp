#include "string_util.hpp"
#include <string.h>

int find_first_of(char const *ch, uint32_t c_size, char const *key) {
  uint32_t max_search_len = c_size - strlen(key);
  for (uint32_t it = 0; it <= max_search_len; it++) {
    if (memcmp(ch + it, key, strlen(key)) == 0) {
      return it;
    }
  }
  return -1;
}

int find_reverse_first_of(char const *ch, uint32_t c_size, char const *key){
  uint32_t max_search_len = c_size - strlen(key);
  for (uint32_t it = max_search_len; it > 0; it--) {
    if (memcmp(ch + it, key, strlen(key)) == 0) {
      return it;
    }
  }
  return -1;
}