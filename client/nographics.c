#include <stdio.h>
#include <game/World.h>
#include <game/Entity.h>
#include <game/Components.h>
#include <game/components/Transform.h>
#include <game/components/Velocity.h>
#include <game/components/AutoPather.h>
#include <game/Commands.h>
#include <game/commands/AutoPatherMoveCommand.h>

int main() {
    EntityHandle handle = Entity_new();
    Entity_add_component(handle, TRANSFORM);
    Entity_add_component(handle, VELOCITY);
    Entity_add_component(handle, AUTO_PATHER);

    Transform* t = Entity_get_component(handle, TRANSFORM);
    Mat3_print(t->transform);

    Velocity* v = Entity_get_component(handle, VELOCITY);
    v->speed = 1.0;
    //v->velocity = Vec2_normalized((Vec2) {1.0f, 1.0f} );
    Command_init_defaults();
    {
        int cmd_index = Command_new(AUTO_PATHER_MOVE_COMMAND);
        AutoPatherMoveCommand* c = Command_get(AUTO_PATHER_MOVE_COMMAND, cmd_index);
        c->auto_pather_index = Entity_get_component_index(handle, AUTO_PATHER);
        c->start = (Vec2) { 0.0f, 0.0f };
        c->end = (Vec2) { 20.0f, 5.0f };
        Command_issue(AUTO_PATHER_MOVE_COMMAND, cmd_index);
    }

    World_init_systems();
    World_start();
    while (1) {
        World_update(0.00001f);
        printf("=====\n");
        Mat3_print(t->transform);
        Vec2_print(v->velocity);
    }
}
