

#include "Thread.hpp"

#include "instances.h"

Thread::Thread() {
	xTaskCreate((TaskFunction_t) &Thread::thread1, "thread2", 128, this, osPriorityAboveNormal, &thread1Handle);
}

Thread::~Thread() {

}

void Thread::thread1(void const *argument) {
	while(1) {
		serialCOM.sendString("test\n");
		vTaskDelay(250);
	}
}