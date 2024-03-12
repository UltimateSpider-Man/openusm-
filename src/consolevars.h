#pragma once

#include <list>
#include <string>

struct ConsoleVariable {
    char field_4[32];

    ConsoleVariable();

    virtual ~ConsoleVariable() = default;

    virtual void setValue(const std::string &, const std::string &);

    virtual void setValue(const std::string &);

    virtual std::string getValue();

    virtual const char *helpText() {
        return "No help available.";
    }

    void setName(const std::string &pName);

    bool match(std::string a2);

    std::string getName();
};

extern std::list<ConsoleVariable *> *g_console_vars;

struct ConsoleHeightVariable : ConsoleVariable {
    ConsoleHeightVariable();

    virtual void setValue(const std::string &a2) override;

    virtual std::string getValue() override;

    virtual const char *helpText() override {
        return "Height of the console in pixels";
    }
};

struct HealthVariable : ConsoleVariable {
    HealthVariable();

    void setValue(const std::string &arg0, const std::string &a1) override;

    void setValue(const std::string &arg0) override;

    virtual ~HealthVariable() = default;
};

struct RenderFramerateVariable : ConsoleVariable {
    RenderFramerateVariable();

    void setValue(const std::string &a1) override;

    std::string getValue() override;

    const char *helpText() override {
        return "Render frames per second";
    }
};

struct ProjZoomVariable : ConsoleVariable {
    ProjZoomVariable();

    void setValue(const std::string &a2) override;

    std::string getValue() override;

    const char *helpText() override {
        return "FOV factor";
    }
};

struct DifficultyVariable : ConsoleVariable {
    DifficultyVariable();

    void setValue(const std::string &a2) override;

    std::string getValue() override;

    const char *helpText() override {
        return "Difficulty level (0=bleep, 1=ez, 2=norm, 3=hero, 4=super hero)";
    }
};
