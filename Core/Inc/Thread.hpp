#ifndef CORE_INC_THREAD
#define CORE_INC_THREAD

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"



class Thread {
   public:
    Thread();
    virtual ~Thread();

    TaskHandle_t thread1Handle;
	static void thread1(void const*);

   
};

#endif    /* CORE_INC_THREAD */
