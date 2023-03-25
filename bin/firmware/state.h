#ifndef STATE_H
#define STATE_H

#include "fipc.h"

enum State {
    Shutdown,
    Ready
};

class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void setState();

    void Ready();
private:
    State m_state;
    FIPC* m_fipc;
};