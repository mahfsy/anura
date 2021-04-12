#ifndef COMMAND_H
#define COMMAND_H

#include <math/Vec2.h>

enum {
    SET_PATH,
};

typedef struct {
    int type;
    //time?
    union {
        struct {
            unsigned int pather_idx;
            Vec2 start;
            Vec2 end;
        } set_path_command;
    };
} Command;

#endif
