#ifndef STATE_H
#define STATE_H

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
};