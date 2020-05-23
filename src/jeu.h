#ifndef JEU_H
#define JEU_H

#include "header_2048.h"

void copierPlateauVersTab(plateau_2048 plateau, int **tab);
void copierTabVersPlateau(plateau_2048 plateau, int **tab);
int **creerTab(int taille);
void libererTab(int **tab, int taille);

void mouvement(plateau_2048 plateau, int n, animation_2048 *li);
void depart(int **tab);
void affichage(int **tab);
void initialisation(plateau_2048 plateau);
#endif