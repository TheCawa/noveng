#include "command.hpp"
#include "engine.hpp"

class CmdSfx : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (!args.empty()) eng->playSFX(args[0]);
    }
};
REGISTER_COMMAND(CmdSfx, "sfx")