#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>

enum Action {
    None,
    Solve,
    AddToSolveBuffer,
    ClearSolveBuffer
}

std::map<std::string, Action> ActionMap{
    { "", Action::None},
    { "Solve", Action::Solve },
    { "BufAdd", Action::AddToSolveBuffer },
    { "ClrBuf", Action::ClearSolveBuffer },
};

class Command {
public:
    Command(std::string command, std::string param);
    ~Command();

    Action getAction();
    std::string getParam();

private:
    Action m_action;
    std::string m_param;
}

#endif // COMMAND_H