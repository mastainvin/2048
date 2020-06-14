#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

/**
* \file sauvegarde.h
* \brief prototypes du fichier sauvegarde.h
* \author Vincent Mastain
* \version 0.1
* \date 12 juin 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void sauvegarde(plateau_2048 plateau, plateau_2048 plateau2, partie_2048 partie, position_utilisateur position, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2);
void lecture(plateau_2048 *plateau, plateau_2048 *plateau2, partie_2048 *partie, position_utilisateur *position, joueur_arcade_2048 *joueur1, joueur_arcade_2048 *joueur2);
void lecture_position(position_utilisateur *position, int *best_score);

#endif