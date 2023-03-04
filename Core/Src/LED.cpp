#include "LED.h"

/**
 * @brief Construct a new LED::LED object
 *
 * Light max brightness level set at 100, scale set at. Scale is used to divide
 * brightness.
 *
 * @warning Initialize LED::LED object before main(). Then port must be set
 * after HAL_TIM_PWM_Start() using setPort().
 * @see setPort() for setting HAL PWM register
 * @see setScale() to set scale/divider of brightness
 * @see setLevel() to set brightness base value
 */
LED::LED() {
    m_level /= m_scale;  // Initialize LED on level with scale
    m_breath_itr = 0;    // Breathing light level table iterator
}

/**
 * @brief Destroy the LED::LED object
 *
 */
LED::~LED() { *m_port = 0; }

/**
 * @brief Initialize with passing Timer PWM CCR register reference.
 *
 * Must use after HAL_TIM_PWM_Start().
 * Example: Timer_1 Channel_3 will be &htim1.Instance->CCR3.
 * @param port Timer PWM CCR register.
 */
void LED::setPort(__IO uint32_t *port) {
    m_port = port;
    *m_port = 0;  // Turn LED off when start
}

/**
 * @brief Turn on LED using stored brightness and scale.
 *
 */
void LED::on() {
    *m_port = m_level / m_scale;
    m_breath_toggle = false;
    m_blink_toggle = false;
    m_rapid_toggle = false;
}

/**
 * @brief Turn off LED.
 *
 */
void LED::off() {
    *m_port = 0;
    m_breath_toggle = false;
    m_blink_toggle = false;
    m_rapid_toggle = false;
}

/**
 * @brief Set LED max brightness to half.
 *
 */
void LED::half() { m_level = 50 / m_scale; }

/**
 * @brief Toggle LED on/off state.
 *
 */
void LED::toggle() {
    if (*m_port > 0) {
        *m_port = 0;
    } else {
        *m_port = m_level / m_scale;
    }
}

void LED::set(bool state) {
    if (state)
        on();
    else
        off();
}

/**
 * @brief Set brightness scale.
 *
 * @param value
 */
void LED::setScale(uint16_t value) { m_scale = value; }

/**
 * @brief Set brightness max level.
 *
 * @param value
 */
void LED::setLevel(uint16_t value) {
    m_level = 64000 * value / 100;
    *m_port = m_level / m_scale;
}

/**
 * @brief Use in 20Hz timer interrupt to periodically update LED brightness to
 * emulate breathing and blinking.
 *
 * Run this in HAL_TIM_PeriodElapsedCallback() for the 20Hz timer.
 */
void LED::scheduler() {
    // Breathing LED Logic
    if (m_breath_toggle) {
        if (++m_breath_itr < 25)
            m_level = 64000 * m_breath[m_breath_itr] / 100;
        else
            m_breath_itr = 0;

        *m_port = m_level / m_scale;
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

/**
 * @brief Start breathing effect.
 *
 * LED breathing turn on. The brightness will change based on scheduler().
 */
void LED::breath() {
    m_breath_toggle = !m_breath_toggle;
    m_blink_toggle = false;
    m_rapid_toggle = false;
    *m_port = 0;
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
    *m_port = 0;
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
    *m_port = 0;
}
