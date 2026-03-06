#include "command.hpp"
#include "engine.hpp"
#include "logger.hpp"
#include <filesystem>

class CmdPlay : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.empty()) return;
        if (eng->currentMusicFile == args[0] && !eng->activeSounds.empty()) return;
        
        eng->stopAudio();
        eng->currentMusicFile = args[0];
        std::filesystem::path path = std::filesystem::path(DIR_RES) / DIR_MUSIC / args[0];
        
        auto pSound = std::make_unique<ma_sound>();
        if (ma_sound_init_from_file(&eng->audio, path.string().c_str(), 0, NULL, NULL, pSound.get()) == MA_SUCCESS) {
            bool looping = false;
            for (const auto& arg : args) if (arg == "loop") looping = true;
            ma_sound_set_looping(pSound.get(), looping ? MA_TRUE : MA_FALSE);
            ma_sound_start(pSound.get());
            eng->activeSounds.push_back(std::move(pSound));
            Logger::getInstance().debug("BGM Started: " + args[0]);
        }
    }
};
REGISTER_COMMAND(CmdPlay, "play")