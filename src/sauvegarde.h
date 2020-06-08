#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void sauvegarde(plateau_2048 plateau);
void lecture(plateau_2048 *plateau);

#endif