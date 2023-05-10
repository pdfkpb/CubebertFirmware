#include "wrist.h"

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/pwm.h"

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
    turn(10);
    gpio_put(m_directionPin, Direction::CW);

    m_speed /= 2;
    while(gpio_get(m_homingPin)) {
        sleep_ms(HOMING_POLL_MS);
    }
    disable();
    // End Homing

    // Reset
    m_speed = tmpSpeed;
}

void Wrist::enable() {
    gpio_put(m_sleepPin, 0);
}

void Wrist::disable() {
    gpio_put(m_sleepPin, 1);
}

void Wrist::turn(int deg) {
    m_angle = deg;
}

bool Wrist::setSpeed(float speed) {
    if (speed >= 0 && speed < 1) {
        m_speed = speed;
        return true;
    }
    return false;
}

void Wrist::setDirection(Direction direction) {
    m_direction = direction;
}

// Private Functions

void Wrist::set_pwm_pin(int pin, irq_handler_t callback) {
    // Tell the LED pin that the PWM is in charge of its value.
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Mask our slice's IRQ output into the PWM block's single interrupt line,
    // and register our interrupt handler
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, callback);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 5.0);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);
}
