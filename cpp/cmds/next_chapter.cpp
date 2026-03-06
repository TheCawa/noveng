#include "command.hpp"
#include "engine.hpp"
#include <filesystem>
#include "logger.hpp"

namespace fs = std::filesystem;

class CmdNextChapter : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.empty()) return;
        eng->chapterFinished = true;
        eng->nextChapterFile = (fs::path(DIR_RES) / DIR_SCENARIO / args[0]).string();
        Logger::getInstance().info("Command: next_chapter -> " + eng->nextChapterFile);
    }
};
REGISTER_COMMAND(CmdNextChapter, "next_chapter")