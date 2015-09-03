#ifndef _COMMON_DEFINES_H
#define _COMMON_DEFINES_H

#include "mongoose.h"

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace rapidjson;
using namespace std;

// #ifdef __arm__
//   #define GAMESHOW_BUILD_RASPI
// #endif

#define SIZEOF(n) ((int)(sizeof(n) / sizeof(n[0])))
// #define NULL (0)
#define FALSE (0)
#define TRUE  (1)

#define COIL_COUNT (14)
#define FLASHER_COUNT (8)

#define COIL_OFF 0
#define COIL_ON  1
#define COIL_ON_TIME 20 //the amount of time a coil is allowed to be continuously on for
#define COIL_COOLDOWN_TIME 20 //the amount of time a coil must be off before firing again

enum LampState{LAMP_OFF, LAMP_ON, LAMP_FLASH_SLOW, LAMP_FLASH_FAST};

#endif