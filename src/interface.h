#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre);
void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau);
void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color);
void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau);

animation_2048 anim_detruire_element(animation_2048 li);
void anim_detruire_list(animation_2048 *li);
void anim_rajoute_element(animation_2048 *li, animation_value_2048 valeur);

void debug_anim_list(animation_list_2048 *li);
SHP_bool anim_deplacement(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li);
SHP_bool anim_addition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li);
SHP_bool anim_apparition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li);

coordInt_2048 coordTabAcoordAffichage(plateau_2048 plateau, coordInt_2048 coordEntieres);

void afficher_score(SDL_Renderer *renderer, plateau_2048 plateau, int x, int y);

#endif