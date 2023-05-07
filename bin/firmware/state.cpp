#include "state.h"

#include "command.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"

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

void led() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

void StateMachine::Ready() {
    Command* cmd = m_fipc->next();

    switch(cmd->action()) {
    case Action::Solve:
        printf(cmd->param().c_str());
        led();
        break;
    case Action::None:
    default:
        printf("No Command On Deck\n");
        break;
    }

    delete cmd;
}