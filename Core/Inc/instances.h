#ifndef CORE_INC_INSTANCES
#define CORE_INC_INSTANCES

#include "LED.hpp"
#include "SerialCOM.hpp"

extern LED led_user;
extern SerialCOM serialCOM;

extern EmbeddedCliConfig *config;
extern EmbeddedCli *cli;

#endif    /* CORE_INC_INSTANCES */
