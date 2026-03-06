#include "command.hpp"
#include "engine.hpp"
#include "localisation.hpp"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <filesystem>
#include "logger.hpp"

namespace fs = std::filesystem;

class CmdChoice : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        Logger::getInstance().info("Command: choice started.");
        std::cout << "\n" << CLR_NAME << LocalizationManager::getInstance().get("choice_header") << CLR_RESET << std::endl;
        
        int numOptions = (int)(args.size() / 2);
        for (int i = 0; i < numOptions; ++i) {
            std::cout << "  " << (i + 1) << ". " << args[i * 2] << std::endl;
        }

        int selected = 0;
        while (selected < 1 || selected > numOptions) {
            if (_kbhit()) {
                int ch = _getch();
                if (ch >= '1' && ch <= ('0' + numOptions)) selected = ch - '0';
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        eng->chapterFinished = true;
        std::string nextFile = args[(selected - 1) * 2 + 1];
        eng->nextChapterFile = (fs::path(DIR_RES) / DIR_SCENARIO / nextFile).string();
        Logger::getInstance().info("User made choice: " + std::to_string(selected));
    }
};
REGISTER_COMMAND(CmdChoice, "choice")