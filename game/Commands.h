#ifndef COMMAND_H
#define COMMAND_H

#include <math/Vec2.h>
#include "commands/AutoPatherMoveCommand.h"

typedef struct {
    int (*new_func)();
    void* (*get_func)(int);
    void (*issue_func)(int);
} CommandType;

enum DefaultCommands {
    AUTO_PATHER_MOVE_COMMAND,
    ABILITYUSER_USE_ABILITY,
};

void Command_init_defaults();
int Command_create(CommandType c); //create a new command that can be issued, get a handle to it

int Command_new(int command_handle); //first create a new command
void* Command_get(int command_handle, int index); //compose it
void Command_issue(int command_handle, int index); //then issue it

#endif
