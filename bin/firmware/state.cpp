#include "state.h"

#include "command.h"
#include "pico/stdio.h"

StateMachine::StateMachine(State initialState) {
    m_state = initialState;
    m_fipc = new FIPC();
}

StateMachine::~StateMachine() {
    delete m_fipc;
}

void StateMachine::setState(State state) {
    m_state = state;
}

State StateMachine::state() {
    return m_state;
}

void StateMachine::Ready() {
    Command* cmd = m_fipc->next();

    switch(cmd->action()) {
    case Action::Solve:
        break;
    case Action::None:
    default:
        printf("No Command On Deck\n");
        break;
    }

    delete cmd;
}