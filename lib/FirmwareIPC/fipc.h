#ifndef FIPC_H
#define FIPC_H

#include <queue>
#include "command.h"

typedef CommandBuffer std::queue<Command*>

class FIPC {
public:
    FIPC();
    ~FIPC();

    Command* next();

private:
    CommandBuffer* m_commandBuffer;

    void processQueue();
}

#endif // FIPC_H