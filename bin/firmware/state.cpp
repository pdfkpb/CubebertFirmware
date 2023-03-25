#include "state.h"

#include "fipc.h"

StateMachine::StateMachine(State initialState) {
    m_state = initialState;
    m_fipc = new FIPC();
}

StateMachine::~StateMachine() {
    delete m_fipc;
}

void StateMachine::Ready() {
    m_fipc->readr
}