#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "header_2048.h"
void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre);
void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau);
void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color);
void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau);
#endif