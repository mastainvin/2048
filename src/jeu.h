#ifndef JEU_H
#define JEU_H

#include "header_2048.h"

void creerTab(int **tab, int taille);
void libererTab(int **tab, int taille);

void mouvement(int **tab, int n);
void depart(int **tab);
void affichage(int **tab);
void initialisation(plateau_2048 plateau);
#endif