#ifndef CORE_INC_THREAD
#define CORE_INC_THREAD

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

class Thread {
   public:
    Thread();
    virtual ~Thread();

    TaskHandle_t app_1_Handle;
    TaskHandle_t schedule_Handle;

    static void app_1(void const*);
    static void schedule(void const*);


};

#endif /* CORE_INC_THREAD */
