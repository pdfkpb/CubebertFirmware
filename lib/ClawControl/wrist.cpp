#include "wrist.h"

#include "pico/stdio.h"
#include "pico/stdlib.h"

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
    Direction tmpDir = m_direction;

    // Begin Homing
    m_speed = HOMING_SPEED;
    m_direction = Direction::CW;

    while (gpio_get(m_homingPin)) {
        // Some PWM thing to rotate
    }

    // Some PWM to back up a few steps

    m_speed /= 2;
    while(gpio_get(m_homingPin)) {
        // Some PWM thing to rotate
    }
    // End Homing

    // Reset
    m_speed = tmpSpeed;
    m_direction = tmpDir;
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
