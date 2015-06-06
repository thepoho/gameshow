#include <iostream>

#ifdef _WIN32
#include "wiringpi.h"
#elif __linux
#include <wiringpi>
#endif

#define SIZEOF(n) (sizeof(n) / sizeof(n[0]))
