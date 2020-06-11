#ifndef JEU_H
#define JEU_H

#include "header_2048.h"

int max_4(int a, int b, int c, int d);
SHP_bool estEgale(int **tab, int **tab2, int taille);
void copier_plateau(plateau_2048 plateau, plateau_2048 *nouveau);
void copierPlateauVersTab(plateau_2048 plateau, int **tab);
void copierTabVersPlateau(plateau_2048 plateau, int **tab);
int **creerTab(int taille);
void libererTab(int **tab, int taille);

int mouvement(plateau_2048 plateau, int n, animation_2048 *li, animation_2048 *anim_dep, animation_2048 *anim_app);

void depart(plateau_2048 plateau);
void affichage(int **tab);
void initialisation(plateau_2048 plateau);

void bonus_2to8(plateau_2048 plateau);
void bonus_rangement(plateau_2048 plateau);

void bonus_detuire(plateau_2048 plateau);
void bonus_inverserTouches(int *fleche);
void bonus_melange(plateau_2048 plateau);

void trier_tab(int *tab, int taille);

int max_tab(plateau_2048 plateau);
int palier(plateau_2048 plateau);

void generer_bonus(joueur_arcade_2048 *joueur);

#endif