#include <stdio.h>
#include <math/AnuraMath.h>
#include <lib/Entity.h>
#include <lib/Player.h>

#include <time.h>

int main() {
    Map m;
    Map_load(&m, "navmesh.obj");
    Map_print(&m);

    Player p;
    Player_init(&p);

    AutoPather_gen_path(&p.auto_pather, &m, (Vec2) {0.0f, 0.0f}, (Vec2){4.0f, 3.0f});

    while (1) {
        Player_update(&p, 1.0f);
        Mat3_print(p.entity.transform);
        break;
        sleep(1);
    }
    Map_delete(&m);
}
