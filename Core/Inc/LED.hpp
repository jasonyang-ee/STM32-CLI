#ifndef CORE_INC_LED
#define CORE_INC_LED

#include "main.h"

class LED {
   public:
    LED(uint16_t, uint16_t, uint16_t);
    virtual ~LED();

    void setCCR(__IO uint32_t *);
    void setScale(uint16_t);
    void setLevel(uint16_t);

    void on();
    void off();
    void half();
    void toggle();
    void set(bool);

    void scheduler();

    void breath();
    void blink();
    void rapid();

   private:
    // Setting
    __IO uint32_t *m_CCR;          // Ex: htim3.Instance->CCR2 for Timer3 Channel2
    uint16_t m_level{100};         // light level
    uint16_t m_scale{1};           // light scale
    uint16_t m_ext_frequency{20};  // external interrupt frequency
    uint16_t m_schedule{0};        // schedule timer

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

#endif /* CORE_INC_LED */
