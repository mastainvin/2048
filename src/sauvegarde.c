#include "sauvegarde.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void sauvegarde(plateau_2048 plateau)
{
	FILE *fichier = NULL;
	int i;
	int j;

	fichier = fopen("sauvegarde.txt", "w");

	if (fichier != NULL)
	{
		fprintf(fichier,"%d %d %d\n", plateau.score, plateau.bestscore, plateau.taille);
		for (i = 0; i < plateau.taille; i++)
		{
			for (j = 0; j < plateau.taille; j++)
			{
				fprintf(fichier, "%d ", plateau.tab[i][j]);
			}
			fprintf(fichier,"\n");
		}
	}

	fclose(fichier);
}
void lecture(plateau_2048 *plateau)
{
	int i;
	int j;

	FILE *fichier = NULL;

	fichier = fopen("sauvegarde.txt", "r");

	

	if (fichier != NULL)
	{
		if (feof(fichier))
			return;
			
		fscanf(fichier, "%d %d %d\n", &plateau->score, &plateau->bestscore, &plateau->taille);
		for (i = 0; i < plateau->taille; i++)
		{
			for (j = 0; j < plateau->taille; j++)
			{
			fscanf(fichier, "%d ", &plateau->tab[i][j]);
			}
			fscanf(fichier, "\n");
		}

		fclose(fichier);
	}
}
