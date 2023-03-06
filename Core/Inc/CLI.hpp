#ifndef CORE_INC_CLI
#define CORE_INC_CLI

#include "lwshell.h"

class CLI {
   public:
    CLI();
	virtual ~CLI();
	void init();
	bool parse(uint16_t);

	// User Commands

	static int32_t led(int32_t, char**);


};

#endif /* CORE_INC_CLI */
