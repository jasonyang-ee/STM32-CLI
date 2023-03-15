

#include "Thread.hpp"

#include "instances.h"

Thread::Thread() {
    // Template for creating task
    // auto _task = [](void *arg) { static_cast<Thread *>(arg)->(); };
    // xTaskCreate(_task, "", 512, this, 2, &_Handle);

    auto parse_task = [](void *arg) { static_cast<Thread *>(arg)->parse(); };
    xTaskCreate(parse_task, "cli parsing", 256, this, 0, &parse_Handle);

    auto app_1_task = [](void *arg) { static_cast<Thread *>(arg)->app_1(); };
    xTaskCreate(app_1_task, "app 1", 128, this, 0, &app_1_Handle);

    auto app_2_task = [](void *arg) { static_cast<Thread *>(arg)->app_2(); };
    xTaskCreate(app_2_task, "app 2", 128, this, 0, &app_2_Handle);

    auto schedule_20Hz_task = [](void *arg) {
        static_cast<Thread *>(arg)->schedule_20Hz();
    };
    xTaskCreate(schedule_20Hz_task, "schedule 20Hz", 128, this, 0, &schedule_20Hz_Handle);

    auto schedule_10Hz_task = [](void *arg) {
        static_cast<Thread *>(arg)->schedule_10Hz();
    };
    xTaskCreate(schedule_10Hz_task, "schedule 10Hz", 128, this, 1, &schedule_10Hz_Handle);
}

Thread::~Thread() {}

void Thread::parse() {
    while (1) {
        // cli.parse();
        vTaskDelay(1000);
    }
}

void Thread::app_1() {
    while (1) {
        serialCOM.sendString("Tick: ");
        serialCOM.sendNumber(HAL_GetTick());
        serialCOM.sendLn();
        vTaskDelay(5000);
    }
}

void Thread::app_2() { serialCOM.sendString("Here: "); }

void Thread::schedule_20Hz() {
    while (1) {
        led_user.scheduler();
        vTaskDelay(50);
    }
}
void Thread::schedule_10Hz() {
    while (1) {
        serialCOM.scheduler();
        vTaskDelay(100);
    }
}