#include "command.hpp"
#include "engine.hpp"

class CmdSet : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.size() < 2) return;
        eng->variables[args[0]] = std::stoi(args[1]);
    }
};
REGISTER_COMMAND(CmdSet, "set")