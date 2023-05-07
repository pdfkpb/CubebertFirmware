#ifndef PALM_H
#define PALM_H

#include "fingers.h"

class Palm {
public:
    Palm();
    ~Palm();

private:
    int m_state;

    Fingers::Fingers* setOne;
    Fingers::Fingers* setTwo;
};

#endif // PALM_H
