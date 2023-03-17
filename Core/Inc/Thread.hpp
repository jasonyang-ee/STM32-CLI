#ifndef CORE_INC_THREAD
#define CORE_INC_THREAD

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

class Thread {
   public:
    Thread();
    virtual ~Thread();

    TaskHandle_t parse_Handle;
    void parse();

    TaskHandle_t app_1_Handle;
    void app_1();

    TaskHandle_t app_2_Handle;
    void app_2();

    TaskHandle_t schedule_20Hz_Handle;
    void schedule_20Hz();

    TaskHandle_t serial_send_Handle;
    void serial_send();

	SemaphoreHandle_t serialCOM_sem;
};

#endif    /* CORE_INC_THREAD */
