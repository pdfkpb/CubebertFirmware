#include "commmand.h"

Command::Command(std::string command, std::string param) {
    m_action = ActionMap[command];
    m_param = param;
}

Command::~Command() {

}

Action Command::getAction() {
    return m_action;
}

std::string Command::getParam() {
    return m_param;
}