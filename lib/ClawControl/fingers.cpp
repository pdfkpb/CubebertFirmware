#include "fingers.h"

Fingers::Fingers(int vertPin, int horPin) {
    m_set1Pin = nsPin;
    m_set2Pin = ewPin;

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
    case
    }
}