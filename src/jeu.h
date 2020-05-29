#ifndef JEU_H
#define JEU_H

#include "header_2048.h"

void copierPlateauVersTab(plateau_2048 plateau, int **tab);
void copierTabVersPlateau(plateau_2048 plateau, int **tab);
int **creerTab(int taille);
void libererTab(int **tab, int taille);

int mouvement(plateau_2048 plateau, int n, animation_2048 *li, animation_2048 *anim_dep, animation_2048 *anim_app);

void depart(plateau_2048 plateau);
void affichage(int **tab);
void initialisation(plateau_2048 plateau);
#endif