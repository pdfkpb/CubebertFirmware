#include "fipc.h"

#include <stdio.h>

FIPC::FIPC() {
    m_commandBuffer = new CommandBuffer();
}

FIPC::~FIPC() {
    delete m_commandBuffer;
}

Command* FIPC::next() {
    processQueue();
    return m_commandBuffer->pop();
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

        Command* cmd(action, param);
        m_commandBuffer->push(cmd);
    }
}