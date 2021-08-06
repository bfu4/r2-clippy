
// This file contains definitions to
// r2-exported-util.h

#include "r2-exported-util.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

unsigned long long r_time_now(void) {
  unsigned long long ret;
  struct timeval now;
  gettimeofday(&now, NULL);
  ret = now.tv_sec * R_USEC_PER_SEC;
  ret += now.tv_usec;
  return ret;
}

const char* r_str_pad(const char ch, int sz) {
  static char pad[1024];
  if (sz < 0) {
    sz = 0;
  }
  memset(pad, ch, R_MIN(sz, sizeof(pad)));
  if (sz < sizeof(pad)) {
    pad[sz] = 0;
  }
  pad[sizeof(pad) - 1] = 0;
  return pad;
}

size_t r_str_utf8_codepoint(const char* s, size_t left) {
  if ((*s & 0x80) != 0x80) {
    return 0;
  } else if ((*s & 0xe0) == 0xc0 && left >= 1) {
    return ((*s & 0x1f) << 6) + (*(s + 1) & 0x3f);
  } else if ((*s & 0xf0) == 0xe0 && left >= 2) {
    return ((*s & 0xf) << 12) + ((*(s + 1) & 0x3f) << 6) + (*(s + 2) & 0x3f);
  } else if ((*s & 0xf8) == 0xf0 && left >= 3) {
    return ((*s & 0x7) << 18) + ((*(s + 1) & 0x3f) << 12) +
           ((*(s + 2) & 0x3f) << 6) + (*(s + 3) & 0x3f);
  }
  return 0;
}

bool r_str_char_fullwidth(const char* s, size_t left) {
  size_t codepoint = r_str_utf8_codepoint(s, left);
  return (codepoint >= 0x1100 &&
          (codepoint <= 0x115f || /* Hangul Jamo init. consonants */
           codepoint == 0x2329 || codepoint == 0x232a ||
           (R_BETWEEN(0x2e80, codepoint, 0xa4cf) &&
            codepoint != 0x303f) ||                /* CJK ... Yi */
           R_BETWEEN(0xac00, codepoint, 0xd7a3) || /* Hangul Syllables */
           R_BETWEEN(0xf900, codepoint,
                     0xfaff) || /* CJK Compatibility Ideographs */
           R_BETWEEN(0xfe10, codepoint, 0xfe19) || /* Vertical forms */
           R_BETWEEN(0xfe30, codepoint, 0xfe6f) || /* CJK Compatibility Forms */
           R_BETWEEN(0xff00, codepoint, 0xff60) || /* Fullwidth Forms */
           R_BETWEEN(0xffe0, codepoint, 0xffe6) ||
           R_BETWEEN(0x20000, codepoint, 0x2fffd) ||
           R_BETWEEN(0x30000, codepoint, 0x3fffd)));
}

size_t r_str_len_utf8(const char* s) {
  size_t i = 0, j = 0, fullwidths = 0;
  while (s[i]) {
    if ((s[i] & 0xc0) != 0x80) {
      j++;
      if (r_str_char_fullwidth(s + i, 4)) {
        fullwidths++;
      }
    }
    i++;
  }
  return j + fullwidths;
}

void r_num_srand(int seed) {
  srand(seed);
}

void r_num_irand(void) {
  r_num_srand(r_time_now());
}

int r_rand(int mod) {
  return rand() % mod;
}

int r_num_rand(int max) {
  static bool rand_initialized = false;
  if (!rand_initialized) {
    r_num_irand();
    rand_initialized = true;
  }
  if (!max) {
    max = 1;
  }
  return r_rand(max);
}
