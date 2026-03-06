#include "command.hpp"
#include "engine.hpp"
#include "logger.hpp"

class CmdStopMusic : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        Logger::getInstance().debug("Stopping music via command.");
        eng->stopAudio();
        eng->currentMusicFile = "";
    }
};
REGISTER_COMMAND(CmdStopMusic, "stop_music")