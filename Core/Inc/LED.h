#ifndef SRC_LED_H_
#define SRC_LED_H_

#include "main.h"

class LED {
   public:
    LED();
    virtual ~LED();

    // Setting
    void setPort(__IO uint32_t *);
    void setScale(uint16_t);
    void setLevel(uint16_t);

    // Basic
    void on();
    void off();
    void half();
    void toggle();
	void set(bool);

    // Time Based for 20Hz Scheduling
    void scheduler();

    // Toggle for Time Based Schedules
    void breath();
    void blink();
    void rapid();

   private:
    // Setting
    __IO uint32_t *m_port;  // Ex: htim15.Instance->CCR2
    uint16_t m_level{100};  // light level
    uint16_t m_scale{1};    // light scale

    // Time Based for 20Hz Scheduling
    bool m_breath_toggle{};
    bool m_blink_toggle{};
    bool m_rapid_toggle{};

    uint16_t m_blink_timer{};
    uint16_t m_rapid_timer{};

    uint8_t m_breath_itr{};
    uint16_t m_breath[25] = {0,  5,  10, 17, 29, 43, 60, 69, 77, 83, 91, 97, 99,
                             99, 84, 70, 55, 45, 37, 29, 23, 19, 16, 10, 6};
};

#endif /* SRC_LED_H_ */
