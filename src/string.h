#ifndef STRING_H
#define STRING_H

#include "stddef.h"

extern "C" {

void * memcpy(void * dst, const void * src, size_t n);
void * memset(void * b, int c, size_t len);

}

#endif
