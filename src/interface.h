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

SHP_bool atteindre_2048(plateau_2048 plateau);
SHP_bool continuer_jeu_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, coord_2048 coord_clic);

position_utilisateur quitter(SDL_Renderer *renderer, SDL_Rect fenetre, plateau_2048 plateau1, plateau_2048 plateau2, position_utilisateur position, coord_2048 coord_curseur, coord_2048 coord_clic);
void recommencer(SDL_Renderer *renderer, SDL_Rect fenetre, partie_2048 *partie, plateau_2048 *plateau, plateau_2048 *plateau2, coord_2048 coord_curseur, coord_2048 coord_clic);
SHP_bool defaite_unJoueur(plateau_2048 plateau);

void afficherTitreJoueur(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2);
void recommencer_deuxJoueurs(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2, int *score, int *score2, coord_2048 coord_curseur, coord_2048 coord_clic, SDL_Rect fenetre, partie_2048 *partie);
void afficher_Victoire(SDL_Renderer *renderer, SDL_Rect fenetre, int joueur_gagnant);
void afficher_Egalite(SDL_Renderer *renderer, SDL_Rect fenetre);

void afficher_prochainBonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur);
void afficher_bonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur);

void afficher_info_text(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], char valeur[100]);
void afficher_info_int(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], int valeur);

#endif