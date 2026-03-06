#include "command.hpp"
#include "engine.hpp"

class CmdColor : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.size() >= 2) {
            eng->characterColors[args[0]] = "\033[1;" + args[1] + "m";
        }
    }
};
REGISTER_COMMAND(CmdColor, "color")