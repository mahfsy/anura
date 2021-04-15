#include "Commands.h"
#include <stdbool.h>
#include <stddef.h>

#include <game/commands/AutoPatherMoveCommand.h>
#include <game/commands/ChampionUseAbilityCommand.h>
#include <utils/Vector.h>

static Vector commands;
static bool commands_initialized = false;

void Command_init_defaults() {
    if (!commands_initialized) {
        Vector_init(&commands, sizeof(CommandType));
        commands_initialized = true;
    }
    CommandType auto_pather_move_command = {
        AutoPatherMoveCommand_new,
        AutoPatherMoveCommand_get,
        AutoPatherMoveCommand_issue,
    };

    Vector_set(&commands, AUTO_PATHER_MOVE_COMMAND, &auto_pather_move_command);
}
int Command_create(CommandType c); //create a new command type that can be issued, get a handle to it

int Command_new(int command_handle) {
    CommandType* ct = Vector_get(&commands, command_handle);
    if (!ct) return -1;

    return ct->new_func();
}

void* Command_get(int command_handle, int index) {
    CommandType* ct = Vector_get(&commands, command_handle);
    if (!ct) return NULL;

    return ct->get_func(index);
}

void Command_issue(int command_handle, int index) {
    CommandType* ct = Vector_get(&commands, command_handle);
    if (!ct) return;   

    ct->issue_func(index);
}
