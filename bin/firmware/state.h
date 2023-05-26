#ifndef STATE_H
#define STATE_H

#include "fipc.h"

enum State {
    Shutdown,
    Ready
};

class StateMachine {
public:
    StateMachine(State initialState);
    ~StateMachine();

    void setState(State state);
    State state();

    void Ready();
private:
    struct Robot {
        Claw *north;
        Claw *south;
        Claw *east;
        Claw *west;
    };
    
    Robot m_robot;

    State m_state;
    FIPC* m_fipc;
};

#endif // STATE_H
