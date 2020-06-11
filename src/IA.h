#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

#define DEPTH_IA 5
int evaluation(plateau_2048 plateau);
coup_IA IA_max(coup_IA position, int depth, animation_2048 *dep_IA, animation_2048 *add_IA, animation_2048 *app_IA);

#endif