#include "claw.h"

Claw::Claw() {
}

Claw::~Claw() {
    delete m_palm;
    delete m_wrist;
}

void Claw::initialize() {
    m_palm->home();
    m_wrist->home();
}
