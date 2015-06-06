#ifdef __linux
#include <wiringpi>
#else
#define wiringPiSetup() 1
#define pinMode(a,b) 1
#define digitalWrite(a,b) 1
#define delay(a)

#define LOW 0
#define HIGH 1
#define OUTPUT 1
#endif