#include "consolecmds.h"

#include "actor.h"
#include "base_ai_core.h"
#include "console.h"
#include "consolevars.h"
#include "debug_render.h"
#include "entity_handle_manager.h"
#include "filespec.h"
#include "game.h"
#include "mstring.h"
#include "nal_anim.h"
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

std::string ConsoleCommand::getName() {
    std::string out{this->field_4};
    return out;
}

void ConsoleCommand::setName(const std::string &pName) {
    assert(pName.size() < MAX_COMMAND_NAME_LEN);

    auto *v2 = pName.c_str();
    strcpy(this->field_4, v2);
    strlwr(this->field_4);
}

bool ConsoleCommand::process_cmd(const std::vector<std::string> &) {
    return false;
}

bool ConsoleCommand::match(const std::string &a2) {
    std::string v4{this->field_4};

    return (v4 == a2);
}

bool ExecCommand::process_cmd(const std::vector<std::string> &a1) {
    if (a1.size()) {
        auto &v1 = a1.front();
        g_console->exec(v1.c_str());
    }

    return true;
}

static HelpCommand g_HelpCommand{};

HelpCommand::HelpCommand() {
    setName(std::string{"help"});
}

bool HelpCommand::process_cmd(const std::vector<std::string> &a2) {
    if (!a2.empty()) {
        g_console->addToLog("");
        auto &v2 = a2[0];

        mString v9{v2.c_str()};
        v9.to_lower();

        auto *v8 = g_console->getCommand(v9.c_str());
        if (v8 != nullptr) {
            auto *v3 = v8->helpText();
            g_console->addToLog(v3);
        } else {
            auto *v7 = g_console->getVariable(v9.c_str());
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
    setName(std::string{"list_ents"});
}

bool ListEntsCommand::process_cmd(const std::vector<std::string> &) {
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

bool LoadLevelCommand::process_cmd(const std::vector<std::string> &a1) {
    if (a1.size() != 1) {
        return false;
    }

    auto &v2 = a1[0];
    auto *v3 = v2.c_str();
    g_console->addToLog("Now loading level %s", v3);
    auto &v4 = a1[0];
    g_game_ptr()->load_new_level(v4.c_str(), -1);
    return true;
}

static VariableList g_VariableList{};

VariableList::VariableList() {
    setName("varlist");
}

bool VariableList::process_cmd(const std::vector<std::string> &) {
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

bool SetCommand::process_cmd(const std::vector<std::string> &a2) {
    if (a2.size() > 1) {
        auto &v2 = a2[0];
        auto *v12 = g_console->getVariable(v2);
        if (v12 != nullptr) {
            auto v9 = v12->match(std::string{"health"});
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

bool GetCommand::process_cmd(const std::vector<std::string> &a2) {
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

bool GameStateCommand::process_cmd(const std::vector<std::string> &cmds) {
    if (cmds.size() && cmds.size() <= 2) {
        auto &v3 = cmds[0];
        mString a1 {v3.c_str()};

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

bool QuitCommand::process_cmd(const std::vector<std::string> &) {
    g_game_ptr()->field_164 = true;
    return true;
}

static CommandList g_CommandList{};

CommandList::CommandList() {
    this->setName("cmdlist");
}

bool CommandList::process_cmd(const std::vector<std::string> &) {
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
    setName("force_mission");
}

bool ForceMissionCommand::process_cmd(const std::vector<std::string> &a1)
{
    if ( a1.size() == 3 )
    {
        auto &v2 = a1.at(2);
        if ( is_int_format(v2.c_str()) )
        {
            mString v3 {a1.at(2).c_str()};
            auto v19 = v3.to_int();
            mString v4 {a1.at(1).c_str()};
            auto *v16 = v4.c_str();
            mString v5 {a1.at(0).c_str()};
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
            mString v9 {a1.at(0).c_str()};
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
    setName("dvarlist");
}

bool ListDebugVariablesCommand::process_cmd(const std::vector<std::string> &)
{
    return false;
}

static ListMissionsCommand g_ListMissionsCommand{};

ListMissionsCommand::ListMissionsCommand()
{
    setName("list_missions");
}

bool ListMissionsCommand::process_cmd(const std::vector<std::string> &)
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
    this->setName("render");
}

bool DebugRenderCommand::process_cmd(const std::vector<std::string> &a2)
{
    int result;
    auto v17 = a2.size();
    if ( v17 != 0 )
    {
        auto &v4 = a2.at(0);
        mString v15 {v4.c_str()};
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

static PlayAnimCommand g_PlayAnimCommand{};

PlayAnimCommand::PlayAnimCommand()
{
    this->setName("play_anim");
}

bool PlayAnimCommand::process_cmd(const std::vector<std::string> &a2)
{
    if (a2.size() == 1 || a2.size() == 2 )
    {
        auto &v3 = a2.at(0);
        mString a1 {v3.c_str()};
        filespec v35 {a1};
        v35.m_ext = resource_key_type_ext()[g_platform()][RESOURCE_KEY_TYPE_ANIMATION];
        actor *v33 = nullptr;
        if ( a2.size() == 2 )
        {
            auto &v5 = a2.at(1);
            mString v32 {v5.c_str()};
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

static ListNearbyEntsCommand g_ListNearbyEntsCommand{};

ListNearbyEntsCommand::ListNearbyEntsCommand() {
    this->setName("list_nearby_ents");
}

bool ListNearbyEntsCommand::process_cmd(const std::vector<std::string> &a2)
{
    auto *v3 = g_world_ptr()->get_hero_ptr(0);
    auto &abs_position = v3->get_abs_position();
    auto a3 = abs_position;
    float v25 = 10.0;
    if ( a2.size() == 1 )
    {
        mString v5 {a2.at(0).c_str()};
        v25 = v5.to_float();
    }


    using map = std::decay_t<decltype(entity_handle_manager::the_map())>;
    auto &the_map = entity_handle_manager::the_map();
    using iterator = map::iterator;

    iterator v24 = the_map.begin();
    iterator end = the_map.end();
    for ( ; v24 != end; ++v24 )
    {
        auto &v7 = (*v24);
        auto *v23 = v7.second;
        auto &v8 = v23->get_abs_position();
        auto a2a = v8;
        auto v9 = a2a - a3;
        auto v21 = v9.length();
        if ( v25 >= v21 )
        {
            auto v16 = a2a.z;
            auto v15 = a2a.y;
            auto v14 = a2a.x;
            auto v13 = v21;
            auto id = v23->get_id();
            auto *v11 = id.to_string();
            g_console->addToLog("%s at %.2f meters (%.1f, %.1f, %.1f)", v11, v13, v14, v15, v16);
        }
    }

    //g_console->addToLog("ENTRY BLOCKS = %d, HASH BLOCKS = %d", dword_1585078, stru_158AC0C.field_8);
    return true;
}

static DumpThreadsCommand g_DumpThreadsCommand{};

DumpThreadsCommand::DumpThreadsCommand() {
    this->setName("dump_threads");
}

bool DumpThreadsCommand::process_cmd(const std::vector<std::string> &a2) {
    if ( a2.size() != 0 ) {
        auto &v2 = a2.at(0);
        if ( v2 != "1" ) {
            return false;
        }

        g_console->addToLog("Threads dumped to file.");
        script_manager::dump_threads_to_file();
    }
    else
    {
        g_console->addToLog(mString::null());
        script_manager::dump_threads_to_console();
    }
    
    return true; 
}

static SetPBFloatCommand g_SetPBFloatCommand {};

SetPBFloatCommand::SetPBFloatCommand() {
    this->setName("set_ai");
}

bool SetPBFloatCommand::process_cmd(const std::vector<std::string> &a2)
{
    auto v46 = a2.size();
    if ( v46 == 2 || v46 == 3 )
    {
        auto &v2 = a2.at(0);
        auto *v3 = v2.c_str();
        string_hash a2a {v3};
        auto *ent = entity_handle_manager::find_entity(a2a, IGNORE_FLAVOR, true);
        if ( ent != nullptr )
        {
            if ( ent->is_an_actor() )
            {
                auto *the_actor = bit_cast<actor *>(ent);
                auto *v42 = the_actor->get_ai_core();
                if ( v42 != nullptr )
                {
                    auto &v8 = a2.at(1);
                    auto *v9 = v8.c_str();
                    string_hash v39 {v9};

                    auto *the_pblock = v42->get_param_block();
                    if ( the_pblock->does_parameter_exist(v39) )
                    {
                        auto pb_float = the_pblock->get_pb_float(v39);
                        if ( v46 == 2 )
                        {
                            auto &v14 = a2.at(1);
                            auto *v15 = v14.c_str();
                            g_console->addToLog("%s = %.2f", v15, pb_float);
                            return true;
                        }
                        else
                        {
                            auto &v16 = a2.at(2);
                            auto *v17 = v16.c_str();
                            auto v38 = atof(v17);
                            the_pblock->set_pb_float(v39, v38, false);

                            auto &v19 = a2.at(1);
                            auto *v20 = v19.c_str();
                            g_console->addToLog("%s was %.2f, now set to %.2f", v20, pb_float);
                            return true;
                        }
                    }
                    else
                    {
                        auto &v12 = a2.at(1);
                        auto *v13 = v12.c_str();
                        g_console->addToLog("Parameter %s does not exist in the param block", v13);
                        return true;
                    }
                }
                else
                {
                    g_console->addToLog("This actor doesn't have an AI core!");
                    return true;
                }
            }
            else
            {
                g_console->addToLog("This entity is not an actor!");
                return true;
            }
        }
        else
        {
            auto &v5 = a2.at(0);
            auto *v6 = v5.c_str();
            g_console->addToLog("Entity %s not found!", v6);
            return true;
        }
    }
    else
    {
        auto *v21 = this->helpText();
        g_console->addToLog(v21);
        return true;
    }
}

