#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

class NovelEngine;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(NovelEngine* eng, const std::vector<std::string>& args) = 0;
};

class CommandFactory {
public:
    using Creator = std::function<std::unique_ptr<ICommand>()>;
    static CommandFactory& getInstance() {
        static CommandFactory instance;
        return instance;
    }
    void registerCommand(const std::string& name, Creator creator) {
        creators[name] = creator;
    }
    std::map<std::string, Creator>& getCreators() { return creators; }
private:
    std::map<std::string, Creator> creators;
};

#define REGISTER_COMMAND(className, cmdName) \
    static bool className##_registered = []() { \
        CommandFactory::getInstance().registerCommand(cmdName, []() { return std::make_unique<className>(); }); \
        return true; \
    }();
