#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <client/graphics/Window.h>

void RenderSystem_init(Window* the_window);

void RenderSystem_start();
void RenderSystem_update(float delta);

#endif
