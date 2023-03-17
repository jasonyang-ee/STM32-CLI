#ifndef CORE_INC_CLI
#define CORE_INC_CLI

#include "lwshell.h"
#include "string.h"

class CLI {
   public:
    CLI();
    virtual ~CLI();
    void init();
    bool parse();
    static void output(const char*, lwshell*);

	// Recelived Command Size
	uint16_t cmd_size;

    // User Commands
    static int32_t led(int32_t, char**);
    static int32_t help(int32_t, char**);
};

#endif /* CORE_INC_CLI */
