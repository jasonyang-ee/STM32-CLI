#include "LED.hpp"

/**
 * @brief Construct a new LED::LED object
 * @param level britness % relative to PWM period value. Period of 100 works best.
 * @param scale global dimmer for level
 * @param freq PWM Update Event interrupt frequency (1KHz works good)
 * @warning setCCR(&htimX->CCRX) is required to run.
 *
 */
LED::LED(uint16_t level, uint16_t scale, uint16_t freq) {
    m_level = level;
    m_scale = scale;
    m_ext_frequency = freq;
    m_breath_itr = 0;
}

/**
 * @brief Destroy the LED::LED object
 *
 */
LED::~LED() { *m_CCR = 0; }

/**
 * @brief Initialize with passing Timer PWM CCR register reference.
 *
 * Must use after HAL_TIM_PWM_Start().
 * Example: Timer_1 Channel_3 will be &htim1.Instance->CCR3.
 * @param port Timer PWM CCR register.
 */
void LED::setCCR(__IO uint32_t *CCR) { m_CCR = CCR; }

/**
 * @brief Turn on LED using stored brightness and scale.
 *
 */
void LED::on() {
    *m_CCR = m_level / m_scale;
    m_breath_toggle = false;
    m_blink_toggle = false;
    m_rapid_toggle = false;
}

/**
 * @brief Turn off LED.
 *
 */
void LED::off() {
    *m_CCR = 0;
    m_breath_toggle = false;
    m_blink_toggle = false;
    m_rapid_toggle = false;
}

/**
 * @brief Toggle LED on/off state.
 *
 */
void LED::toggle() {
    if (*m_CCR > 0) {
        *m_CCR = 0;
    } else {
        *m_CCR = m_level / m_scale;
    }
}

/**
 * @brief Programmable On/Off setter.
 * @param state on=true, off=false
 */
void LED::set(bool state) {
    if (state)
        on();
    else
        off();
}

/**
 * @brief Set brightness scale.
 * @param value
 */
void LED::setScale(uint16_t value) { m_scale = value; }

/**
 * @brief Set brightness max level.
 *
 * @param value
 */
void LED::setLevel(uint16_t value) { m_level = value; }

/**
 * @brief Set LED max brightness to half.
 *
 */
void LED::half() { *m_CCR = m_level / m_scale / 2; }

/**
 * @brief Use in 20Hz timer interrupt to periodically update LED brightness to
 * emulate breathing and blinking.
 *
 * Run this in HAL_TIM_PeriodElapsedCallback() for the 20Hz timer.
 */
void LED::scheduler() {
    if (m_schedule == 0) {
        // Breathing LED Logic
        if (m_breath_toggle) {
            if (++m_breath_itr < 25)
                m_level = m_breath[m_breath_itr];
            else
                m_breath_itr = 0;

            *m_CCR = m_level / m_scale;
        }

        // Slow Blinking LED Logic
        if (m_blink_toggle) {
            if (m_blink_timer > 5) {
                toggle();
                m_blink_timer = 0;
            } else
                m_blink_timer++;
        }

        // Fast Blinking LED Logic
        if (m_rapid_toggle) {
            if (m_rapid_timer > 1) {
                toggle();
                m_rapid_timer = 0;
            } else
                m_rapid_timer++;
        }
    }
    if (m_schedule++ > (m_ext_frequency / 20)) m_schedule = 0;  // making 20Hz schedule
}

/**
 * @brief Start breathing effect.
 *
 * LED breathing turn on. The brightness will change based on scheduler().
 */
void LED::breath() {
    m_breath_toggle = !m_breath_toggle;
    m_blink_toggle = false;
    m_rapid_toggle = false;
    *m_CCR = 0;
}

/**
 * @brief Start slow blinking.
 *
 * LED blinking turn on. The on/off will change based on scheduler().
 */
void LED::blink() {
    m_blink_toggle = !m_blink_toggle;
    m_breath_toggle = false;
    m_rapid_toggle = false;
    *m_CCR = 0;
}

/**
 * @brief Start fast blinking.
 *
 * Led blinking turn on. The on/off will change based on scheduler().
 */
void LED::rapid() {
    m_rapid_toggle = !m_rapid_toggle;
    m_breath_toggle = false;
    m_blink_toggle = false;
    *m_CCR = 0;
}
