#include "wrist.h"

Wrist::Wrist(int stepPin, int directionPin, int sleepPin, int homingPin) {
    m_stepPin = stepPin;
    m_directionPin = directionPin;
    m_sleepPin = sleepPin;
    m_homingPin = homingPin;

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

    // Homing Fun!
    m_speed = HOMING_SPEED;
    m_direction = Direction::CW;

    // Fill in with homing details

    // Reset
    m_speed = tmpSpeed;
    m_direction = tmpDir;
}
