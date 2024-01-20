#ifndef CLAW_H
#define CLAW_H

#include "palm.h"
#include "wrist.h"

struct WristConfig {
    uint stepPin;
    uint directionPin;
    uint sleepPin;
    uint homingPin;
};

class Claw {
public:
    Claw(
        uint fingerPin1,
        uint fingerPin2,
        uint stepPin,
        uint directionPin,
        uint sleepPin,
        uint homingPin
    );
    ~Claw();

    void initialize();

private:
    Palm* m_palm;
    Wrist* m_wrist;
};

#endif // CLAW_H
