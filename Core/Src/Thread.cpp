

#include "Thread.hpp"

#include "instances.h"

Thread::Thread() {
    xTaskCreate((TaskFunction_t)&Thread::app_1, "Application 1", 128, this,
                osPriorityAboveNormal, &app_1_Handle);
    xTaskCreate((TaskFunction_t)&Thread::schedule, "Instance Schedule", 128, this,
                osPriorityAboveNormal, &schedule_Handle);
}

Thread::~Thread() {}

void Thread::app_1(void const *arg) {
    while (1) {
		serialCOM.sendString("Tick: ");
        serialCOM.sendNumber(HAL_GetTick());
		serialCOM.sendLn();
        vTaskDelay(100);
    }
}

void Thread::schedule(void const *arg) {
	while (1) {
		led_user.scheduler();
		serialCOM.scheduler();
		vTaskDelay(10);
	}
}