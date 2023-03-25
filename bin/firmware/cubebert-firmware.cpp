#include "state.h"

#include "pico/stdio.h"
#include "pico/time.h"

bool init() {
    return true;
}

int main() {
    stdio_init_all();

    StateMachine theMachine(init() ? State::Ready : State::Shutdown);

    while(theMachine.state() != State::Shutdown) {
        switch(theMachine.state()){
        case State::Ready:
            theMachine.Ready();
            break;
        default:
            state = State::Shutdown;
        }
        sleep_ms(1);
    }
}