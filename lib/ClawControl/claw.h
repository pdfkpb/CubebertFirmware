#ifndef CLAW_H
#define CLAW_H

#include "fingers.h"
#include "wrist.h"

class Claw {
public:
    Claw();
    ~Claw();

private:



    Wrist::Wrist* wrist;
};

#endif // CLAW_H
