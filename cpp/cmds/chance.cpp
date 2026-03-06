#include "command.hpp"
#include "engine.hpp"
#include <filesystem>
#include "logger.hpp"
#include <ctime>

namespace fs = std::filesystem;

class CmdChance : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.size() < 3) return;
        int prob = 0;
        try { prob = std::stoi(args[0]); } catch (...) { prob = 0; }

        eng->chapterFinished = true;
        bool win = (std::rand() % 100 < prob);
        std::string nextFile = win ? args[1] : args[2];
        eng->nextChapterFile = (fs::path(DIR_RES) / DIR_SCENARIO / nextFile).string();
        
        Logger::getInstance().info("Command: chance (" + std::to_string(prob) + "%) | Win: " + (win?"Yes":"No") + " | Next: " + nextFile);
    }
};
REGISTER_COMMAND(CmdChance, "chance")