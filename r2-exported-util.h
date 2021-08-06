// The r2-exported-util header file contains
// required radare-2 utilities to be able to print
// accordingly.
#ifndef R2_EXPORTED_UTIL_H
#define R2_EXPORTED_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

// Macro to determine if the number `y` is between the given numbers.
#define R_BETWEEN(x, y, z) (((y) >= (x)) && ((y) <= (z)))

// Usec per sec, used in random functions.
#define R_USEC_PER_SEC 1000000ULL

// Macro to determine the smaller number.
#define R_MIN(x, y) (((x) > (y)) ? (y) : (x))

// Size of an array.
#define R_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// Check for printf, accordingly.
#define R_PRINTF_CHECK(fmt, dots) __attribute__((format(printf, fmt, dots)))

// printf function.
int r_cons_printf(const char* format, ...) R_PRINTF_CHECK(1, 2);

// string padding function.
const char* r_str_pad(const char, int);

// current time.
unsigned long long r_time_now();

// The four functions are helpers to
// the random capability,
// used in https://github.com/radareorg/radare2/blob/master/libr/util/unum.c.

void r_num_irand(void);

int r_num_rand(int);

#ifdef __cplusplus
}
#endif

#endif  // R2_EXPORTED_UTIL_H
