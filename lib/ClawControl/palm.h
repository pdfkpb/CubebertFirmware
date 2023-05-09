#ifndef PALM_H
#define PALM_H

#include "fingers.h"

class Palm {
public:
    Palm();
    ~Palm();

    void home();

private:
    int m_state;

    Fingers::Fingers* m_setOne;
    Fingers::Fingers* m_setTwo;
};

#endif // PALM_H
