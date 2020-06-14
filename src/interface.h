#ifndef INTERFACE_H
#define INTERFACE_H

/**
* \file interface.h
* \brief prototype du fichier interface.c
* \author Vincent Mastain
* \author Ahmed Trabelsi
* \version 0.1
* \date 12 juin 2020
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode);
void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode);
void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color, SHP_bool darkmode);
void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode);

void affiche_titre(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode);
void affiche_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void affiche_vs(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void affiche_ia(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void affiche_quitter(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void affiche_continuer(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void arcade(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode);
void mode1(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode);
void mode2(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode);
void mode3(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode);

animation_2048 anim_detruire_element(animation_2048 li);
void anim_detruire_list(animation_2048 *li);
void anim_rajoute_element(animation_2048 *li, animation_value_2048 valeur);

void debug_anim_list(animation_list_2048 *li);
SHP_bool anim_deplacement(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode);
SHP_bool anim_addition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode);
SHP_bool anim_apparition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode);

coord_2048 coordTabAcoordAffichage(plateau_2048 plateau, coord_2048 coordEntieres);

SHP_bool atteindre_2048(plateau_2048 plateau);
SHP_bool continuer_jeu_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode);

position_utilisateur quitter(SDL_Renderer *renderer, SDL_Rect fenetre, plateau_2048 plateau1, plateau_2048 plateau2, position_utilisateur position, partie_2048 partie, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode);
void recommencer(SDL_Renderer *renderer, SDL_Rect fenetre, position_utilisateur position, partie_2048 *partie, plateau_2048 *plateau, plateau_2048 *plateau2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode);
SHP_bool defaite_unJoueur(plateau_2048 plateau);

void afficherTitreJoueur(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2, SHP_bool darkmode);
void afficher_Victoire(SDL_Renderer *renderer, SDL_Rect fenetre, int joueur_gagnant, SHP_bool darkmode);
void afficher_Egalite(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode);

void afficher_bonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur, SHP_bool darkmode);

void afficher_info_text(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], char valeur[100], SHP_bool darkmode);
void afficher_info_int(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], int valeur, SHP_bool darkmode);

void bouton_darkmode(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool *darkmode, coord_2048 coord_clic);

#endif