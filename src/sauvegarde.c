/**
* \file sauvegarde.c
* \brief fonctions gestions de la sauvegarde du 2048
* \author Vincent Mastain
* \author Ahmed Trabelsi
* \version 0.1
* \date 12 juin 2020
*	
*Fonctions lisant et écrivant dans le fichier sauvegarde.txt
* Avec gestion de la taille du tableau et du nombre de joueurs
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "sauvegarde.h"
#include "header_2048.h"
#include "jeu.h"

/**
* \fn void sauvegarde(plateau_2048 plateau, plateau_2048 plateau2, partie_2048 partie, position_utilisateur position, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2)
* \brief sauvegarde une partie 
* \author Ahmed Trabelsi
* \author Vincent Mastain
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueur 1
* \param plateau2 plateau du joueur 2
* \param partie paramètre de la partie jouée
* \param position mode de jeu joué
* \param joueur1 bonus et malus du joueur 1
* \param joueur2 bonus et malus du joueur 2
* \return rien dans tous les cas
* Sauvegarde la partie dans le fichier "sauvegarde.txt"
*/
void sauvegarde(plateau_2048 plateau, plateau_2048 plateau2, partie_2048 partie, position_utilisateur position, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2)
{
	FILE *fichier = NULL;
	int i;
	int j;

	fichier = fopen("sauvegarde.txt", "w");

	if (fichier != NULL)
	{
		fprintf(fichier, "%d %d\n", position, plateau.bestscore);
		if (position == unJoueur)
		{
			fprintf(fichier, "%d\n", partie.continuer_apres_2048);

			fprintf(fichier, "%d %d\n", plateau.score, plateau.taille);
		}
		else if (position == deuxJoueur || position == IA)
		{
			fprintf(fichier, "%d %d\n", partie.tour, partie.numero_tour);
			fprintf(fichier, "%d %d %d %d\n", plateau.score, plateau.taille, plateau2.score, plateau2.taille);
		}
		else if (position == deuxJoueurArcadeMode)
		{
			fprintf(fichier, "%d %d\n", partie.chrono, partie.palier_max);
			fprintf(fichier, "%d %d %d %d\n", plateau.score, plateau.taille, plateau2.score, plateau2.taille);
			fprintf(fichier, "%d %d %d %d %d %d %d %d\n", joueur1.bonus, joueur1.malus, joueur1.prochain_bonus, joueur1.prochain_malus, joueur1.chrono, joueur1.inverse, joueur1.rapide, joueur1.palier);
			fprintf(fichier, "%d %d %d %d %d %d %d %d\n", joueur2.bonus, joueur2.malus, joueur2.prochain_bonus, joueur2.prochain_malus, joueur2.chrono, joueur2.inverse, joueur2.rapide, joueur2.palier);
		}

		for (i = 0; i < plateau.taille; i++)
		{
			for (j = 0; j < plateau.taille; j++)
			{
				fprintf(fichier, "%d ", plateau.tab[i][j]);
			}
			fprintf(fichier, "\n");
		}
		if (position == deuxJoueur || position == IA || position == deuxJoueurArcadeMode)
		{
			for (i = 0; i < plateau2.taille; i++)
			{
				for (j = 0; j < plateau.taille; j++)
				{
					fprintf(fichier, "%d ", plateau2.tab[i][j]);
				}
				fprintf(fichier, "\n");
			}
		}
	}

	fclose(fichier);
}

/**
* \fn void lecture(plateau_2048 *plateau, plateau_2048 *plateau2, partie_2048 *partie, position_utilisateur *position, joueur_arcade_2048 *joueur1, joueur_arcade_2048 *joueur2)
* \brief lecture d'une sauvegarde d'une partie
* \author Ahmed Trabelsi
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueur 1
* \param plateau2 plateau du joueur 2
* \param partie paramètre de la partie jouée
* \param position mode de jeu joué
* \param joueur1 bonus et malus du joueur 1
* \param joueur2 bonus et malus du joueur 2
* \return rien dans tous les cas
* lecture du fichier "sauvegarde.txt"
*/
void lecture(plateau_2048 *plateau, plateau_2048 *plateau2, partie_2048 *partie, position_utilisateur *position, joueur_arcade_2048 *joueur1, joueur_arcade_2048 *joueur2)
{
	int i;
	int j;

	FILE *fichier = NULL;

	fichier = fopen("sauvegarde.txt", "r");

	if (fichier != NULL)
	{
		fscanf(fichier, "%d %d\n", position, &plateau->bestscore);
		//printf("%d\n", *position);
		if (*position == unJoueur)
		{
			fscanf(fichier, "%d\n", &partie->continuer_apres_2048);
			fscanf(fichier, "%d %d\n", &plateau->score, &plateau->taille);
		}
		else if (*position == deuxJoueur || *position == IA)
		{
			fscanf(fichier, "%d %d\n", &partie->tour, &partie->numero_tour);
			fscanf(fichier, "%d %d %d %d\n", &plateau->score, &plateau->taille, &plateau2->score, &plateau2->taille);
		}
		else if (*position == deuxJoueurArcadeMode)
		{
			fscanf(fichier, "%d %d\n", &partie->chrono, &partie->palier_max);
			fscanf(fichier, "%d %d %d %d\n", &plateau->score, &plateau->taille, &plateau2->score, &plateau2->taille);
			fscanf(fichier, "%d %d %d %d %d %d %d %d\n", &joueur1->bonus, &joueur1->malus, &joueur1->prochain_bonus, &joueur1->prochain_malus, &joueur1->chrono, &joueur1->inverse, &joueur1->rapide, &joueur1->palier);
			fscanf(fichier, "%d %d %d %d %d %d %d %d\n", &joueur2->bonus, &joueur2->malus, &joueur2->prochain_bonus, &joueur2->prochain_malus, &joueur2->chrono, &joueur2->inverse, &joueur2->rapide, &joueur2->palier);
		}
		plateau->tab = creerTab(plateau->taille);
		for (i = 0; i < plateau->taille; i++)
		{
			for (j = 0; j < plateau->taille; j++)
			{
				fscanf(fichier, "%d ", &plateau->tab[i][j]);
			}
			fscanf(fichier, "\n");
		}
		if (*position == deuxJoueur || *position == IA || *position == deuxJoueurArcadeMode)
		{
			plateau2->tab = creerTab(plateau2->taille);
			for (i = 0; i < plateau2->taille; i++)
			{
				for (j = 0; j < plateau->taille; j++)
				{
					fscanf(fichier, "%d ", &plateau2->tab[i][j]);
				}
				fscanf(fichier, "\n");
			}
		}
	}
	fclose(fichier);
}

/**
* \fn void lecture_position(position_utilisateur *position, int *best_score)
* \brief lecture d'une sauvegarde d'une partie
* \author Ahmed Trabelsi
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param position mode de jeu joué
* \param best_score
* \return rien dans tous les cas
* lecture des paramtrès globaux du jeu du fichier "sauvegarde.txt"
*/
void lecture_position(position_utilisateur *position, int *best_score)
{
	FILE *fichier = NULL;

	fichier = fopen("sauvegarde.txt", "r");

	*position = menu_principal;
	*best_score = 0;

	if (fichier != NULL)
		fscanf(fichier, "%d %d", position, best_score);
}