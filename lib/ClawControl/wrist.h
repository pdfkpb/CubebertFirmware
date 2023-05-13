#ifndef WRIST_H
#define WRIST_H

#include "hardware/pio.h"

#define HOMING_SPEED   0.2f
#define HOMING_POLL_MS 100u

#define HALF_STEP            0.5f
#define QUARTER_STEP         0.25f
#define EIGTH_STEP           0.125f
#define THIRTY_SECONDTH_STEP 0.03125f

#define DEG_PER_STEP         1.8f
#define STEP_RESOLUTION      QUARTER_STEP
#define STEPS_PER_REVOLUTION (360 / (DEG_PER_STEP * STEP_RESOLUTION))

class Wrist {
public:
    Wrist(
        uint32_t stepPin,
        uint32_t directionPin,
        uint32_t sleepPin,
        uint32_t homingPin);
    ~Wrist();

    void home();

    void turn(int32_t deg);
    void setSpeed(float speed); // (0.0, 1.0]

    bool isReady();

private:
    static uint32_t pioBlockCounter;

    uint32_t m_stepPin;
    uint32_t m_directionPin;
    uint32_t m_sleepPin;
    uint32_t m_homingPin;

    void enable();
    void disable();
    uint32_t angle2Steps(uint32_t angle);

    struct StepperController {
        PIO pio;
        uint32_t stateMachine;
        uint32_t programOffset;
    } m_stepperConfig;

    enum Direction {
        CW,
        CCW
    };
};

#endif // WRIST_H
