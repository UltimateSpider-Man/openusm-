#pragma once

#include <list>

struct mString;

struct ConsoleVariable {
    char field_4[32];

    ConsoleVariable();

    virtual ~ConsoleVariable() = default;

    virtual void setValue(const mString &, const mString &);

    virtual void setValue(const mString &);

    virtual mString getValue();

    virtual const char *helpText() {
        return "No help available.";
    }

    void setName(const mString &pName);

    bool match(mString a2);

    mString getName();
};

extern std::list<ConsoleVariable *> *g_console_vars;

struct ConsoleHeightVariable : ConsoleVariable {
    ConsoleHeightVariable();

    virtual void setValue(const mString &a2) override;

    virtual mString getValue() override;

    virtual const char *helpText() override {
        return "Height of the console in pixels";
    }
};

struct HealthVariable : ConsoleVariable {
    HealthVariable();

    void setValue(const mString &arg0, const mString &a1) override;

    void setValue(const mString &arg0) override;

    virtual ~HealthVariable() = default;
};

struct RenderFramerateVariable : ConsoleVariable {
    RenderFramerateVariable();

    void setValue(const mString &a1) override;

    mString getValue() override;

    const char *helpText() override {
        return "Render frames per second";
    }
};

struct ProjZoomVariable : ConsoleVariable {
    ProjZoomVariable();

    void setValue(const mString &a2) override;

    mString getValue() override;

    const char *helpText() override {
        return "FOV factor";
    }
};

struct DifficultyVariable : ConsoleVariable {
    DifficultyVariable();

    void setValue(const mString &a2) override;

    mString getValue() override;

    const char *helpText() override {
        return "Difficulty level (0=bleep, 1=ez, 2=norm, 3=hero, 4=super hero)";
    }
};
