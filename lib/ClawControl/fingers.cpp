#include "fingers.h"

Fingers::Fingers() {
    m_state = State::Initialize;
}

Fingers::~Fingers() {
}

void Fingers::next() {
    switch(m_state) {
    case Initialize:
        break;
    case Set1Vertical:
        break;
    case Set2Vertical:
        break;
    default:
        
    }
}