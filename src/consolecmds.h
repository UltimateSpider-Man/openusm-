#pragma once

#include <list>
#include <vector>

struct mString;

struct ConsoleCommand {
    char field_4[32];

    ConsoleCommand();

    virtual ~ConsoleCommand() = default;

    virtual bool process_cmd(const std::vector<mString> &);

    virtual const char *helpText();

    mString getName();

    void setName(const mString &pName);

    bool match(const mString &a2);
};

extern std::list<ConsoleCommand *> *g_console_cmds;

struct ExecCommand : ConsoleCommand {
    virtual bool process_cmd(const std::vector<mString> &a1) override;

    virtual const char *helpText() override {
        return "exec [file] -> Executes a console script file";
    }
};

struct HelpCommand : ConsoleCommand {
    HelpCommand();

    virtual bool process_cmd(const std::vector<mString> &a1) override;

    virtual const char *helpText() override {
        return "Retrieves help for console / command";
    }
};

struct ListEntsCommand : ConsoleCommand {
    ListEntsCommand();

    bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override {
        return "List visible entities";
    }
};

struct LoadLevelCommand : ConsoleCommand {
    LoadLevelCommand();

    virtual bool process_cmd(const std::vector<mString> &a1) override;

    virtual const char *helpText() override {
        return "Loads a new level (nuking the current one)";
    }
};

struct VariableList : ConsoleCommand {
    VariableList();

    bool process_cmd(const std::vector<mString> &) override;

    const char *helpText() override {
        return "Lists all available variables";
    }
};

struct SetCommand : ConsoleCommand {
    SetCommand();

    bool process_cmd(const std::vector<mString> &a2) override;

    const char *helpText() override {
        return "set [name] [val] -> Sets the value of a variable";
    }
};

struct GetCommand : ConsoleCommand {
    GetCommand();

    bool process_cmd(const std::vector<mString> &a2) override;

    const char *helpText() override {
        return "get [name] -> Gets the value of a variable";
    }
};

struct GameStateCommand : ConsoleCommand {
    GameStateCommand();

    bool process_cmd(const std::vector<mString> &cmds) override;

    const char *helpText() override {
        return "get / set game_state variables";
    }
};

struct QuitCommand : ConsoleCommand {
    QuitCommand();

    bool process_cmd(const std::vector<mString> &) override;

    const char *helpText() override {
        return "quit -> exit program.  good for test scripts.";
    }
};

struct CommandList : ConsoleCommand {
    CommandList();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override;
};

struct ForceMissionCommand : ConsoleCommand {
    ForceMissionCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override
    {
        return "force_mission of given district, name, and instance";
    }
};

struct ListDebugVariablesCommand : ConsoleCommand
{
    ListDebugVariablesCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override
    {
        return "Lists all available debug variables";
    } 
};

struct ListMissionsCommand : ConsoleCommand
{
    ListMissionsCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override
    {
        return "list_missions currently available";
    }
        
};

struct DebugRenderCommand : ConsoleCommand
{
    DebugRenderCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override;
};

struct PlayAnimCommand : ConsoleCommand
{
    PlayAnimCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override;
};

struct ListNearbyEntsCommand : ConsoleCommand
{
    ListNearbyEntsCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override;
};

struct DumpThreadsCommand : ConsoleCommand {
    DumpThreadsCommand();

    virtual bool process_cmd(const std::vector<mString> &) override;

    virtual const char *helpText() override;
};
