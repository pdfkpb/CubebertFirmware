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
    Palm::Palm* m_palm;
    Wrist::Wrist* m_wrist;
};

#endif // CLAW_H
