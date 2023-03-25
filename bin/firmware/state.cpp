#include "state.h"

#include "command.h"

StateMachine::StateMachine(State initialState) {
    m_state = initialState;
    m_fipc = new FIPC();
}

StateMachine::~StateMachine() {
    delete m_fipc;
}

void StateMachine::Ready() {
    Command* cmd = m_fipc->next();

    switch(cmd->action) {
    case Action::Solve:
        break;
    default:
        break;
    }

    delete cmd;
}