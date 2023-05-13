#include "wrist.h"

#include "stepper.pio.h"

#include <stdio.h>
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"

Wrist::Wrist(int stepPin, int directionPin, int sleepPin, int homingPin) {
    // Save Pin Info
    m_stepPin = stepPin;
    m_directionPin = directionPin;
    m_sleepPin = sleepPin;
    m_homingPin = homingPin;

    // Initialize Pins
    // This one is probably wrong, it needs to be a PWM pin
    gpio_init(m_stepPin);
    gpio_set_dir(m_stepPin, GPIO_OUT);

    gpio_init(m_directionPin);
    gpio_set_dir(m_directionPin, GPIO_OUT);

    gpio_init(m_sleepPin);
    gpio_set_dir(m_sleepPin, GPIO_OUT);
    gpio_put(m_sleepPin, 1); // Start with the motor asleep

    gpio_init(m_homingPin);
    gpio_set_dir(m_homingPin, GPIO_IN);
    gpio_pull_up(m_homingPin);

    // Set Some Defaults
    m_angle = 0;
    m_speed = 0.0;
    m_direction = Direction::CW;
}

Wrist::~Wrist() {
    
}

void Wrist::home() {
    // Hold for reseting at the end
    float tmpSpeed = m_speed;

    // Begin Homing
    m_speed = HOMING_SPEED;
    gpio_put(m_directionPin, Direction::CW);

    enable();
    while (gpio_get(m_homingPin)) {
        sleep_ms(HOMING_POLL_MS);
    }
    disable();

    // Some PWM to back up a few steps
    gpio_put(m_directionPin, Direction::CCW);
    enable();
    sleep_ms(HOMING_POLL_MS);
    disable();

    m_speed /= 2;
    gpio_put(m_directionPin, Direction::CW);

    while(gpio_get(m_homingPin)) {
        sleep_ms(HOMING_POLL_MS);
    }
    disable();
    // End Homing

    // Reset
    m_speed = tmpSpeed;
}

/**
 * @brief Sets the Angle and 
 * 
 * @param deg 
 */
void Wrist::turn(float deg) {
    m_angle += deg;
    
    enable();

    uint32_t steps = angle2Steps(m_angle);
    pio_sm_put_blocking(pio, sm, steps);
}


bool Wrist::setSpeed(float speed) {
    if (speed >= 0 && speed < 1) {
        m_speed = speed;

        pio_sm_set_enabled(m_pio, m_sm, false);
        pio_sm_put_blocking(m_pio, m_sm, period);
        pio_sm_exec(m_pio, m_sm, pio_encode_pull(false, false));
        pio_sm_exec(m_pio, m_sm, pio_encode_out(pio_isr, 32));

        return true;
    }
    return false;
}

void Wrist::setDirection(Direction direction) {
    m_direction = direction;
}

/**
 * @brief Checks the Wrist is ready to perform another action
 * 
 * @return true - We all good
 * @return false - If there is no response from the SM or there is an error response
 */
bool Writst::isReady() {
    return !pio_sm_is_rx_fifo_empty(m_pio, m_sm) && !(m_err = pio_sm_get(m_pio, m_sm));
}

// Private Functions

/**
 * @brief brings the sleep pin high, costing some power, but at least we can turn
 * 
 */
void Wrist::enable() {
    gpio_put(m_sleepPin, 1);
}

/**
 * @brief brings the sleep pin low, saving some power at the cost of torque
 * 
 */
void Wrist::disable() {
    gpio_put(m_sleepPin, 0);
}

// Write `period` to the input shift register
void Wrist:(PIO pio, uint sm, uint32_t period) {
    
}

// Write `level` to TX FIFO. State machine will copy this into X.
void Wrist::pio_pwm_set_level(PIO pio, uint sm, uint32_t level) {
    pio_sm_put_blocking(pio, sm, level);
}
