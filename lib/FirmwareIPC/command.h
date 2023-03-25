#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>

enum Action {
    None,
    Solve,
    AddToSolveBuffer,
    ClearSolveBuffer
};

class Command {
public:
    Command(std::string command, std::string param);
    ~Command();

    Action action();
    std::string param();

private:
    std::map<std::string, Action> ActionMap{
        { "",       Action::None},
        { "Solve",  Action::Solve },
        { "BufAdd", Action::AddToSolveBuffer },
        { "ClrBuf", Action::ClearSolveBuffer },
    };

    Action m_action;
    std::string m_param;
};

#endif // COMMAND_H