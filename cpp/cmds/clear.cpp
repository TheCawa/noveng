#include "command.hpp"
#include "engine.hpp"
#include <iostream>

class CmdClear : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        eng->history.clear(); 
        eng->lastFullText = "";
        eng->lastSpeaker = "";
        #ifdef _WIN32
            system("cls");
        #else
            std::cout << "\033[2J\033[H" << std::flush;
        #endif
    }
};

REGISTER_COMMAND(CmdClear, "clear")