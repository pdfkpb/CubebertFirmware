#ifndef CLAW_H
#define CLAW_H

#include "palm.h"
#include "wrist.h"

class Claw {
public:
    Claw();
    ~Claw();

    void initialize();

private:
    Palm* m_palm;
    Wrist* m_wrist;
};

#endif // CLAW_H
