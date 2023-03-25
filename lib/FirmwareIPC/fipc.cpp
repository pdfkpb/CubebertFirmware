#include "fipc.h"

#include "pico/stdio.h"

FIPC::FIPC() {
    m_commandBuffer = new CommandBuffer();
}

FIPC::~FIPC() {
    delete m_commandBuffer;
}

Command* FIPC::next() {
    processQueue();

    Command* cmd = m_commandBuffer->front();
    m_commandBuffer->pop();
    
    return cmd;
}

//*******************//
// PRIVATE FUNCTIONS //
//*******************//

void FIPC::processQueue() {
    std::string action;
    std::string param;

    while(scanf("[^]%s$%s&", &action, &param) != EOF) {
        if(ferror(stdin)) {
            printf("Invalid Command");
            continue;
        }

        Command* cmd = new Command(action, param);
        m_commandBuffer->push(cmd);
    }
}