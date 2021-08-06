
// This file contains definitions to
// r2-exported-util.h

#include "r2-exported-util.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// A slightly modified version of r_cons_printf,
// used for printing variadic string arguments.
int r_cons_printf(const char* format, ...) {
  va_list ap;
  if (!format || !*format) {
    return -1;
  }
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);

  return 0;
}

// Get the current time, format it for radare.
unsigned long long r_time_now(void) {
  unsigned long long ret;
  struct timeval now;
  gettimeofday(&now, NULL);
  ret = now.tv_sec * R_USEC_PER_SEC;
  ret += now.tv_usec;
  return ret;
}

// Pad a string.
const char* r_str_pad(const char ch, int sz) {
  static char pad[1024];
  if (sz < 0) {
    sz = 0;
  }
  int pad_sz = (int)sizeof(pad);
  memset(pad, ch, R_MIN(sz, pad_sz));
  if (sz < pad_sz) {
    pad[sz] = 0;
  }
  pad[pad_sz - 1] = 0;
  return pad;
}

// Radare2 handles initialization for srand.
// This program should only be run once anyways,
// so it does not concern with checking if
// srand had previously been initialized.
void r_num_irand(void) {
  srand(r_time_now());
}

// Get a random number.
int r_num_rand(int max) {
  r_num_irand();
  if (!max) {
    max = 1;
  }
  return rand() % max;
}
