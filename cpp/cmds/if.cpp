#include "command.hpp"
#include "engine.hpp"

class CmdIf : public ICommand {
public:
    void execute(NovelEngine* eng, const std::vector<std::string>& args) override {
        if (args.size() < 4) return;
        eng->chapterFinished = true;
        bool cond = (eng->variables[args[0]] >= std::stoi(args[1]));
        std::string nextFile = cond ? args[2] : args[3];
        eng->nextChapterFile = (std::filesystem::path(DIR_RES) / DIR_SCENARIO / nextFile).string();
    }
};
REGISTER_COMMAND(CmdIf, "if")