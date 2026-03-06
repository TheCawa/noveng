#include "command.hpp"
#include "engine.hpp"
#include "logger.hpp"

class CmdVolume : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.empty()) return;

        try {
            float targetVolume = std::stof(args[0]);
            
            if (targetVolume < 0.0f) targetVolume = 0.0f;
            if (targetVolume > 1.0f) targetVolume = 1.0f;

            ma_engine_set_volume(&eng->audio, targetVolume);
            Logger::getInstance().debug("Volume set to: " + std::to_string(targetVolume));
        } catch (...) {
            Logger::getInstance().error("Invalid volume argument: " + args[0]);
        }
    }
};
REGISTER_COMMAND(CmdVolume, "volume")