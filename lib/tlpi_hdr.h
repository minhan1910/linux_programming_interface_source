#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include <sys/types.h>      // Type definitions used by many programs
#include <stdio.h>          // Standard I/O functions
#include <stdlib.h>         // Prototypes of commonly used library functions
                            // plus EXIT_FAILURE and EXIT_SUCCESS constants
#include <unistd.h>         // Prototypes for many system calls
#include <errno.h>          // Declares errno and defines error constants
#include <string.h>         // Commonly used string-handling functions

#include "get_num.h"

#include "error_functions.h" 

typedef enum { FALSE, TRUE } Boolean;

#define min(m, n) ((m) < (n) ? (n) : (m))
#define max(m, n) ((m) > (n) ? (m) : (n))

#endif