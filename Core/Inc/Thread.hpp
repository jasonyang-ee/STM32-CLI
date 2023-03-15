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
    TaskHandle_t app_1_Handle;
    TaskHandle_t app_2_Handle;
    TaskHandle_t schedule_20Hz_Handle;
    TaskHandle_t schedule_10Hz_Handle;

    void parse();
    void app_1();
    void app_2();
    void schedule_20Hz();
    void schedule_10Hz();
};

#endif /* CORE_INC_THREAD */
