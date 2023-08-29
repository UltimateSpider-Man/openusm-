#include "consolecmds.h"

#include "actor.h"
#include "console.h"
#include "consolevars.h"
#include "debug_render.h"
#include "filespec.h"
#include "game.h"
#include "mstring.h"
#include "nal_system.h"
#include "script_library_class.h"
#include "script_manager.h"
#include "mission_table_container.h"
#include "region.h"
#include "resource_directory.h"
#include "resource_manager.h"
#include "variables.h"
#include "wds.h"

std::list<ConsoleCommand *> *g_console_cmds{nullptr};

ConsoleCommand::ConsoleCommand() {
    this->setName({});

    if (g_console_cmds == nullptr) {
        g_console_cmds = new std::list<ConsoleCommand *>{};
    }

    g_console_cmds->push_back(this);
}

static constexpr auto MAX_COMMAND_NAME_LEN = 32;

mString ConsoleCommand::getName() {
    mString out{this->field_4};
    return out;
}

void ConsoleCommand::setName(const mString &pName) {
    assert(pName.size() < MAX_COMMAND_NAME_LEN);

    auto *v2 = pName.c_str();
    strcpy(this->field_4, v2);
    strlwr(this->field_4);
}

bool ConsoleCommand::process_cmd(const std::vector<mString> &) {
    return false;
}

const char *ConsoleCommand::helpText() {
    return "No help available.";
}

bool ConsoleCommand::match(const mString &a2) {
    mString v4{this->field_4};

    return (v4 == a2);
}

bool ExecCommand::process_cmd(const std::vector<mString> &a1) {
    if (a1.size()) {
        auto &v1 = a1.front();
        g_console->exec(v1);
    }

    return true;
}

static HelpCommand g_HelpCommand{};

HelpCommand::HelpCommand() {
    setName(mString{"help"});
}

bool HelpCommand::process_cmd(const std::vector<mString> &a2) {
    if (!a2.empty()) {
        g_console->addToLog("");
        auto &v2 = a2[0];

        mString v9{v2};
        v9.to_lower();

        auto *v8 = g_console->getCommand(v9);
        if (v8 != nullptr) {
            auto *v3 = v8->helpText();
            g_console->addToLog(v3);
        } else {
            auto *v7 = g_console->getVariable(v9);
            if (v7 != nullptr) {
                auto *v4 = v7->helpText();
                g_console->addToLog(v4);
            } else {
                auto *v5 = v9.c_str();
                g_console->addToLog("Command '%s' not found!", v5);
            }
        }

    } else {
        g_console->addToLog("");
        g_console->addToLog("<-- Keys -->");
        g_console->addToLog("Up Arrow    Scroll command buffer up");
        g_console->addToLog("Down Arrow  Scroll command buffer down");
        g_console->addToLog("Tab         Complete current command");
        g_console->addToLog("Page Up     Scroll log buffer up");
        g_console->addToLog("Page Down   Scroll log buffer down");
        g_console->addToLog("Home        Scroll log buffer top");
        g_console->addToLog("End         Scroll log buffer bottom");
        g_console->addToLog("ESC         Show / hide console");
        g_console->addToLog("");
        g_console->addToLog("<-- Commands -->");
        g_console->addToLog("cmdlist     List all commands");
        g_console->addToLog("varlist     List all variables");
        g_console->addToLog("help <?>    Get help for a command");
    }

    return true;
}

static ListEntsCommand g_ListEntsCommand{};

ListEntsCommand::ListEntsCommand() {
    setName(mString{"list_ents"});
}

bool ListEntsCommand::process_cmd(const std::vector<mString> &) {
    g_console->addToLog("visible entities:");
    auto *v10 = g_world_ptr()->ent_mgr.get_entities();
    auto it = v10->begin();
    while (1) {
        auto end = v10->end();
        if (it == end) {
            break;
        }

        auto &v8 = (*it.field_8);

        if (v8 != nullptr && !v8->sub_48AE20()) {
            if (v8->is_still_visible()) {
                auto v4 = v8->get_id();
                auto *v5 = v4.to_string();
                g_console->addToLog("  %s", v5);
            }
        }

        ++it;
    }

    return true;
}

static LoadLevelCommand g_LoadLevelCommand{};

LoadLevelCommand::LoadLevelCommand() {
    setName("load_level");
}

bool LoadLevelCommand::process_cmd(const std::vector<mString> &a1) {
    if (a1.size() != 1) {
        return false;
    }

    auto &v2 = a1[0];
    auto *v3 = v2.c_str();
    g_console->addToLog("Now loading level %s", v3);
    auto &v4 = a1[0];
    g_game_ptr()->load_new_level(v4, -1);
    return true;
}

static VariableList g_VariableList{};

VariableList::VariableList() {
    setName("varlist");
}

bool VariableList::process_cmd(const std::vector<mString> &) {
    g_console->addToLog("");
    g_console->addToLog("<-- Console Variables -->");

    if (g_console_vars != nullptr && g_console_vars->size()) {
        auto it = g_console_vars->begin();
        while (1) {
            auto end = g_console_vars->end();
            if (it == end) {
                break;
            }

            if ((*it) != nullptr) {
                auto &v3 = (*it);
                auto v9 = v3->getValue();

                auto v8 = v3->getName();

                auto *v7 = v9.c_str();
                auto *v5 = v8.c_str();
                g_console->addToLog("%s %s", v5, v7);
            }

            ++it;
        }
    }

    return 1;
}

static SetCommand g_SetCommand{};

SetCommand::SetCommand() {
    setName("set");
}

bool SetCommand::process_cmd(const std::vector<mString> &a2) {
    if (a2.size() > 1) {
        auto &v2 = a2[0];
        auto *v12 = g_console->getVariable(v2);
        if (v12 != nullptr) {
            auto v9 = v12->match(mString{"health"});
            if (v9 && a2.size() == 3) {
                v12->setValue(a2[1], a2[2]);
            } else {
                v12->setValue(a2[1]);
            }

        } else {
            auto &v5 = a2[0];
            auto *v6 = v5.c_str();
            g_console->addToLog("??? %s", v6);
        }
    }

    return true;
}

static GetCommand g_GetCommand{};

GetCommand::GetCommand() {
    setName("get");
}

bool GetCommand::process_cmd(const std::vector<mString> &a2) {
    if (a2.size()) {
        auto &v2 = a2[0];
        auto *v11 = g_console->getVariable(v2);
        if (v11 != nullptr) {
            auto v10 = v11->getValue();

            auto v8 = v11->getName();

            auto *v7 = v10.c_str();
            auto *v3 = v8.c_str();
            g_console->addToLog("%s is %s", v3, v7);

        } else {
            auto &v4 = a2[0];
            auto *v5 = v4.c_str();
            g_console->addToLog("??? %s", v5);
        }
    }

    return true;
}

static GameStateCommand g_GameStateCommand{};

GameStateCommand::GameStateCommand() {
    setName("game_state");
}

bool GameStateCommand::process_cmd(const std::vector<mString> &cmds) {
    if (cmds.size() && cmds.size() <= 2) {
        auto &v3 = cmds[0];
        mString a1 = v3;

        bool a2 = false;
        script_library_class *var_type = nullptr;
        auto *v18 = static_cast<float *>(script_manager::get_game_var_address(a1, &a2, &var_type));
        if (v18 != nullptr) {
            if (var_type != nullptr) {
                assert(strcmp(var_type->get_name(), "num") == 0);
            }

            if (cmds.size() <= 1) {
                auto *v15 = (a2 ? "GameVar" : "SharedVar");

                auto v13 = *v18;
                auto *v10 = a1.c_str();
                g_console->addToLog("(%s) %s %s = %4.2f", v15, "num", v10, v13);
            } else {
                auto &v6 = cmds[1];
                auto v17 = v6;
                auto v16 = *v18;

                auto *v7 = v17.c_str();
                auto v8 = atof(v7);
                *v18 = v8;

                auto *v14 = (a2 ? "GameVar" : "SharedVar");

                auto v12 = *v18;
                auto *v9 = a1.c_str();
                g_console->addToLog("(%s) %s %s = %4.2f (was %4.2f)", v14, "num", v9, v12, v16);
            }
        } else {
            auto *v4 = a1.c_str();
            g_console->addToLog("Game state variable %s not found.", v4);
        }

    } else {
        auto *v2 = this->helpText();
        g_console->addToLog(v2);
    }

    return true;
}

static QuitCommand g_QuitCommand{};

QuitCommand::QuitCommand() {
    setName("quit");
}

bool QuitCommand::process_cmd(const std::vector<mString> &) {
    g_game_ptr()->field_164 = true;
    return true;
}

static CommandList g_CommandList{};

CommandList::CommandList() {
    this->setName(mString{"cmdlist"});
}

bool CommandList::process_cmd(const std::vector<mString> &) {
    g_console->addToLog("");
    g_console->addToLog("<-- Console Commands -->");
    if (g_console_cmds != nullptr && g_console_cmds->size()) {
        auto a1 = g_console_cmds->begin();
        while (1) {
            auto v2 = g_console_cmds->end();
            if (a1 == v2) {
                break;
            }

            auto &cmd = (*a1);
            if (cmd != nullptr) {
                auto v6 = cmd->getName();

                auto *v4 = v6.c_str();
                g_console->addToLog("%s", v4);
            }

            ++a1;
        }
    }

    return true;
}

const char *CommandList::helpText() {
    return "Lists all available commands";
}

bool is_int_format(const mString &a1)
{
    if ( a1.size() == 0 )
    {
        return false;
    }

    for ( auto i = 0; i < a1.size(); ++i )
    {
        auto v2 = a1.at(i);
        if ( isdigit(v2) == 0 && (i || a1.at(0) != '-') && (i || a1.at(0) != '+') )
        {
            return false;
        }
    }

    return true;
}

static ForceMissionCommand g_ForceMissionCommand{};

ForceMissionCommand::ForceMissionCommand()
{
    setName(mString{"force_mission"});
}

bool ForceMissionCommand::process_cmd(const std::vector<mString> &a1)
{
    if ( a1.size() == 3 )
    {
        auto &v2 = a1.at(2);
        if ( is_int_format(v2) )
        {
            auto &v3 = a1.at(2);
            auto v19 = v3.to_int();
            auto &v4 = a1.at(1);
            auto *v16 = v4.c_str();
            auto &v5 = a1.at(0);
            auto v14 = v5.to_int();
            auto *v6 = mission_manager::s_inst();
            v6->force_mission(v14, v16, v19, nullptr);
        }
        else
        {
            auto &v7 = a1.at(2);
            auto *v20 = v7.c_str();
            auto &v8 = a1.at(1);
            auto *v17 = v8.c_str();
            auto &v9 = a1.at(0);
            auto v15 = v9.to_int();
            auto *v10 = mission_manager::s_inst();
            v10->force_mission(v15, v17, 0, v20);
        }
    }
    else
    {
        if ( a1.size() != 1 )
        {
            g_console->addToLog("force_mission <district name or global> <mission> <instance>");
            g_console->addToLog("force_mission <mission>");
            return false;
        }

        auto &v11 = a1.at(0);
        auto *v18 = v11.c_str();
        auto *v12 = mission_manager::s_inst();
        v12->force_mission(0, v18, 0, nullptr);
    }

    return true;
}

static ListDebugVariablesCommand g_ListDebugVariablesCommand{};

ListDebugVariablesCommand::ListDebugVariablesCommand()
{
    setName(mString{"dvarlist"});
}

bool ListDebugVariablesCommand::process_cmd(const std::vector<mString> &)
{
    return false;
}

static ListMissionsCommand g_ListMissionsCommand{};

ListMissionsCommand::ListMissionsCommand()
{
    setName(mString{"list_missions"});
}

bool ListMissionsCommand::process_cmd(const std::vector<mString> &)
{
    auto *v2 = mission_manager::s_inst();
    auto v25 = v2->get_district_table_count();
    for ( auto i = -1; i < v25; ++i )
    {
        auto [v20, v21, v19] = [&v2](int i)
            -> std::tuple<fixedstring<8>, mission_table_container *, int>
        {
            if ( i != -1 )
            {
                auto *v21 = v2->get_district_table(i);
                auto *reg = v21->get_region();
                auto &v6 = reg->get_name();
                auto v19 = reg->get_district_id();

                return std::make_tuple(v6, v21, v19);
            }

            auto *v21 = v2->get_global_table();
            return std::make_tuple(fixedstring<8>{"GLOBAL"}, v21, 0);
        }(i);

        _std::vector<mission_table_container::script_info> v23;
        v21->append_script_info(&v23);
        for ( auto &info : v23 )
        {
            auto v14 = info.field_8;
            auto v12 = v19;
            auto *v11 = v20.to_string();
            g_console->addToLog("Name: '%s' District: '%s'(%d) Instance: %d",
                    info.field_0,
                    v11,
                    v12,
                    v14);
        }
    }

    return true;
}

static DebugRenderCommand g_DebugRenderCommand{};

DebugRenderCommand::DebugRenderCommand()
{
    this->setName(mString {"render"});
}

bool DebugRenderCommand::process_cmd(const std::vector<mString> &a2)
{
    int result;
    auto v17 = a2.size();
    if ( v17 != 0 )
    {
        auto &v4 = a2.at(0);
        mString v15 = v4;
        v15.to_upper();
        int v14 = -1;
        for ( auto i = 0; i < 51; ++i )
        {
            if ( v15 == debug_render_items_names()[i] )
            {
                v14 = i;
            }
        }

        if ( v14 == -1 )
        {
            goto LABEL_20;
        }

        if ( v17 == 1 )
        {
            auto &v9 = debug_render_items()[v14];
            auto *v5 = debug_render_items_names()[v14].c_str();
            g_console->addToLog("%s %d", v5, v9);
            return true;
        }

        if ( v17 != 2 )
        {
            LABEL_20:
            g_console->addToLog("Bad syntax or unknown render flag!");
            result = true;
        }
        else
        {
            auto &v6 = a2.at(1);
            auto *v7 = v6.c_str();
            auto v12 = std::atoi(v7);
            auto v11 = debug_render_get_min((debug_render_items_e) v14);
            auto v10 = debug_render_get_max((debug_render_items_e) v14);
            if ( v12 >= v11 && v12 <= v10 )
                debug_render_items()[v14] = v12;
            else
                g_console->addToLog("Value out of range. Should be in [%d, %d]", v11, v10);

            result = true;
        }
    }
    else
    {
        for ( auto j = 0; j < 51; ++j )
        {
            auto &v8 = debug_render_items()[j];
            auto *v2 = debug_render_items_names()[j].c_str();
            g_console->addToLog("%s %d", v2, v8);
        }

        result = true;
    }

    return result;
}

const char *DebugRenderCommand::helpText()
{
    return "render <flag> <value>";
}


static PlayAnimCommand g_PlayAnimCommand{};

PlayAnimCommand::PlayAnimCommand()
{
    this->setName(mString {"play_anim"});
}

bool PlayAnimCommand::process_cmd(const std::vector<mString> &a2)
{
    if (a2.size() == 1 || a2.size() == 2 )
    {
        auto &v3 = a2.at(0);
        filespec v35 {v3};
        mString a1 {v3};
        v35.m_ext = resource_key_type_ext()[g_platform()][RESOURCE_KEY_TYPE_ANIMATION];
        actor *v33 = nullptr;
        if ( a2.size() == 2 )
        {
            auto &v5 = a2.at(1);
            mString v32 {v5};
            v32.to_upper();
            auto *v6 = v32.c_str();
            string_hash v31 {v6};
            auto *ent = entity_handle_manager::find_entity(v31, IGNORE_FLAVOR, true);
            v33 = (actor *) ent;
            if ( v33 == nullptr )
            {
                g_console->addToLog("Entity not found");
                return 1;
            }
        }
        else
        {
#if 0
            j_selection_manager::get(g_selection_mgr, (int)&v30, 0);
            if ( sub_6784B6(&v30) != 5 )
            {
                g_console->addToLog("No entity selected");
                return 1;
            }

            v33 = (actor *)sub_676BA2(&v30);
#else
            assert(0);
#endif
        }

        auto *v29 = v33;
        if ( v33 != nullptr && !v33->is_an_actor() )
        {
            g_console->addToLog("The selected entity is not an actor.");
            return 1;
        }

#if 0
        bool v28 = false;
        auto v15 = v35.m_name + v35.m_ext;
        auto *v9 = v15.c_str();
        auto v27 = create_resource_key_from_path(v9, RESOURCE_KEY_TYPE_NONE);
        auto *resource = resource_manager::get_resource(v27, nullptr, nullptr);
        v28 = resource != nullptr;
        if ( resource == nullptr )
        {
            filespec v26 {a1};
            auto *v11 = v26.m_name.c_str();
            auto v25 = create_resource_key_from_path(v11, RESOURCE_KEY_TYPE_ANIMATION);
            auto *v12 = v29->field_BC;
            resource_manager::push_resource_context(v12);
            v28 = resource_manager::get_resource(v25, nullptr, nullptr) != nullptr;
            resource_manager::pop_resource_context();
            if ( !v28 )
            {
                g_console->addToLog("Entity animation not in packfile.");
                return 1;
            }
        }

        if ( !v33->is_an_actor() )
        {
            g_console->addToLog("Invalid entity (must be an actor).");
            return 1;
        }
#else
        {
            auto *pack_slot = v33->field_BC;
            if (pack_slot != nullptr) {
                auto &res_dir = pack_slot->get_resource_directory();
                auto tlresource_count = res_dir.get_tlresource_count(TLRESOURCE_TYPE_ANIM_FILE);
                assert(tlresource_count == 1);

                const auto idx = 0;
                auto *tlres_loc = res_dir.get_tlresource_location(idx, TLRESOURCE_TYPE_ANIM_FILE);
                nalAnimFile *anim_file = CAST(anim_file, tlres_loc->field_8);
                assert(anim_file->field_0 == 0x10101);

                nalAnimClass<nalAnyPose> *found_anim = nullptr;
                for (auto *anim = bit_cast<nalAnimClass<nalAnyPose> *>(anim_file->field_34);
                        anim != nullptr;
                        anim = anim->field_4) {

                    if (a1 == mString {anim->field_8.to_string()}) {
                        found_anim = anim;
                    }

                    sp_log("%s", anim->field_8.to_string());
                }

                if (found_anim == nullptr)
                {
                    g_console->addToLog("Entity animation not in packfile.");
                    return 1;
                }

                a1 = mString {found_anim->field_8.to_string()};
            }
        }

#endif

        auto *v13 = v29->field_BC;
        resource_manager::push_resource_context(v13);
        string_hash v16 {a1.c_str()};

        auto v24 = v29->play_anim(v16);
        resource_manager::pop_resource_context();

        v24.set_anim_speed(1.0);
    }
    else
    {
        auto *v2 = this->helpText();
        g_console->addToLog(v2);
    }

    return 1;
}

const char *PlayAnimCommand::helpText()
{
  return "play_anim <anim_name> [<entity_id>]";
}
