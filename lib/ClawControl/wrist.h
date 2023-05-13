#ifndef WRIST_H
#define WRIST_H

#include "hardware/irq.h"

#define HOMING_SPEED 0.2
#define HOMING_POLL_MS 100

enum Direction {
    CW,
    CCW
};

class Wrist {
public:
    Wrist(int stepPin, int directionPin, int sleepPin, int homingPin);
    ~Wrist();

    void home();

    void turn(float deg);
    bool setSpeed(float speed); // [0.0, 1.0)
    void setDirection(Direction direction);

    bool pollState();

private:
    int m_stepPin;
    int m_directionPin;
    int m_sleepPin;
    int m_homingPin;

    int m_currentAngle;
    float m_angle;
    float m_speed;
    Direction m_direction;

    void enable();
    void disable();

    void pio_pwm_set_period(PIO pio, uint sm, uint32_t period);
    void pio_pwm_set_level(PIO pio, uint sm, uint32_t level);
};

#endif // WRIST_H
