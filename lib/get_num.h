#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG   01      // Value must be >= 0
#define GN_GT_0     02      // value must be > 0

                            // By default, intergers are decimal
#define GN_ANY_BASE 0100    // Can use any base - like strtol(3)
#define GN_BASE_8   0200    // Value is expressed by octal
#define GN_BASE_16   0300    // Value is expressed by hexadecimal

long getLong(const char *arg, int flas, const char *name);
int getInt(const char *arg, int flas, const char *name);

#endif