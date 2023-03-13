#include "CLI.hpp"

#include "instances.h"

CLI::CLI() {}

CLI::~CLI() {}

void CLI::init() {
    lwshell_init();
    lwshell_register_cmd("led", &CLI::led, "LED Functions");
    lwshell_register_cmd("speak", &CLI::speak, "Serial Send Help");
}

bool CLI::parse(uint16_t size) {
    if (lwshell_input(serialCOM.m_rx_data, size) == lwshellOK) {
        return true;
    }
    return false;
}

int32_t CLI::led(int32_t argc, char** argv) {
    led_user.on();
    return 0;
}

int32_t CLI::speak(int32_t argc, char** argv) {
    led_user.on();
    return 0;
}
