#include "error.h"
#include <cstdio>
#include <cstdlib>

void error_if(bool condition, const char *errmsg)
{
    if(condition) {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}