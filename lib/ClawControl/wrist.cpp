#include "wrist.h"

#include "stepper.pio.h"

#include <stdio.h>
#include "pico/time.h"
#include "pico/stdlib.h"

Wrist::Wrist(
    uint32_t stepPin,
    uint32_t directionPin,
    uint32_t sleepPin,
    uint32_t homingPin) {
    // Save Pin Info
    m_stepPin = stepPin;
    m_directionPin = directionPin;
    m_sleepPin = sleepPin;
    m_homingPin = homingPin;

    // Initialize Pins
    m_stepperConfig.pio = (pioBlockCounter++ % 2) ? pio0 : pio1;
    m_stepperConfig.stateMachine = pio_claim_unused_sm(m_stepperConfig.pio, true);
    m_stepperConfig.programOffset = pio_add_program(m_stepperConfig.pio, &stepper_program);
    stepper_program_init(m_stepperConfig.pio, m_stepperConfig.stateMachine, m_stepperConfig.programOffset, m_stepPin);

    gpio_init(m_directionPin);
    gpio_set_dir(m_directionPin, GPIO_OUT);

    gpio_init(m_sleepPin);
    gpio_set_dir(m_sleepPin, GPIO_OUT);
    gpio_put(m_sleepPin, 1); // Start with the motor asleep

    gpio_init(m_homingPin);
    gpio_set_dir(m_homingPin, GPIO_IN);
    gpio_pull_up(m_homingPin);
}

Wrist::~Wrist() {
    
}

void Wrist::home() {
    // Begin Homing
    setSpeed(HOMING_SPEED);
    gpio_put(m_directionPin, Direction::CW);

    
    while (gpio_get(m_homingPin)) {
        sleep_ms(HOMING_POLL_MS);
    }
    disable();

    // Some PWM to back up a few steps
    gpio_put(m_directionPin, Direction::CCW);
    enable();
    sleep_ms(HOMING_POLL_MS);
    disable();

    setSpeed(HOMING_SPEED / 2);
    gpio_put(m_directionPin, Direction::CW);

    while(gpio_get(m_homingPin)) {
        sleep_ms(HOMING_POLL_MS);
    }
    disable();
    // End Homing
}

/**
 * @brief Sets the Angle and 
 * 
 * @param angle - in degrees
 */
void Wrist::turn(int32_t angle) {
    gpio_put(m_directionPin, (angle > 0 ? Direction::CW : Direction::CCW));

    enable();

    uint32_t steps = angle2Steps(angle);
    pio_sm_put_blocking(m_stepperConfig.pio, m_stepperConfig.stateMachine, (FUNC_STEPPER_TURN & steps));
}


void Wrist::setSpeed(float speed) {
    if (speed = 0 && speed <= 1) {
        // Come back to this function
        // pio_sm_put_blocking(pio, sm, (FUNC_STEPPER_TURN & ));
    }
}

/**
 * @brief Checks the Wrist is ready to perform another action
 * 
 * @return true - We all good
 * @return false - If there is no response from the SM or there is an error response
 */
bool Wrist::isReady() {
    return !pio_sm_is_rx_fifo_empty(m_stepperConfig.pio, m_stepperConfig.stateMachine) && !pio_sm_get(m_stepperConfig.pio, m_stepperConfig.stateMachine);
}

// ------ Private ------ //

uint32_t Wrist::pioBlockCounter = 0;

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

/**
 * @brief Converts the given angle in Degrees to Steps based on Resolution
 * 
 * @param angle - angle in degrees
 * @return uint32_t - the number of steps that correlates to
 */
uint32_t Wrist::angle2Steps(uint32_t angle) {
    return static_cast<uint32_t>(angle / (DEG_PER_STEP * STEP_RESOLUTION));
}