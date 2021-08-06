#include "r2-clippy.h"
#include "r2-exported-util.h"

#include <stdio.h>
#include <string.h>

// Radare2's print-clippy function
void r2_clippy(const char* msg) {
  const char* f;
  int msglen = r_str_len_utf8(msg);
  char* s = strdup(r_str_pad(' ', msglen));
  char* l = strdup(r_str_pad('-', msglen));
  f = avatar_clippy_utf8[r_num_rand(R_ARRAY_SIZE(avatar_clippy_utf8))];

  r_cons_printf(f, l, s, msg, s, l);
  free(l);
  free(s);
}

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 1;
  }
  r2_clippy(argv[1]);
  return 0;
}
