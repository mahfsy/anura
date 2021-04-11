#ifndef COMMAND_H
#define COMMAND_H

enum {
    MOVE_PLAYER,
}

typedef struct {
    int type;
    //time?
    union {
        struct {
            player_idx;
            Vec2 start;
            Vec2 end;
        } move_player_command;
    }
} Command;

#endif
