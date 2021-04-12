#ifndef AUTOPATHERMOVECOMMAND_H
#define AUTOPATHERMOVECOMMAND_H

#include <math/Vec2.h>
#include <game/components/AutoPather.h>

typedef struct {
    int auto_pather_index;
    Vec2 start;
    Vec2 end;
} AutoPatherMoveCommand;

void AutoPatherMoveCommand_issue(int index);
void* AutoPatherMoveCommand_get(int index);
int AutoPatherMoveCommand_new();

#endif
