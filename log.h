#ifndef __CLW_LOG_H__
#define __CLW_LOG_H__

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define Log(...) printf(__VA_ARGS__); printf("\n");
#else
#define Log(...) ;
#endif

#endif
