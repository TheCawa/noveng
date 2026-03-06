#include "command.hpp"
#include "engine.hpp"
#include "logger.hpp"

class CmdType : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.size() < 2) return;
        try {
            eng->characterPitches[args[0]] = std::stof(args[1]);
            Logger::getInstance().debug("Set pitch for " + args[0] + " to " + args[1]);
        } catch (...) {
            eng->characterPitches[args[0]] = 1.0f;
        }
    }
};
REGISTER_COMMAND(CmdType, "type")