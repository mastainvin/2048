#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "jeu.h"
#include "interface.h"

#include "header_2048.h"

#define min(a, b) a < b ? a : b

int main(int argc, char **argv)
{
	// SDL and TTF init + renderer and window creation
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Rect fenetre;
	fenetre.w = 400;
	fenetre.h = 600;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_CreateWindowAndRenderer(fenetre.w, fenetre.h, 0, &window, &renderer);

	SHP_bool play = true;
	int frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;

	plateau_2048 plateau;
	plateau.largeur = min(fenetre.h, fenetre.w) / 1.2;
	plateau.x = (fenetre.w - plateau.largeur) / 2;
	plateau.y = 150;
	plateau.taille = 4;

	plateau.tab = (int **)malloc(plateau.taille * sizeof(int *));

	for (int i = 0; i < plateau.taille; i++)
	{
		plateau.tab[i] = (int *)malloc(plateau.taille * sizeof(int));
	}

	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			plateau.tab[i][j] = 0;
		}
	}
	initialisation(plateau);
	depart(plateau.tab);
	while (play)
	{
		// Déclaration de la variable événement
		SDL_Event event;

		int fleche = 0;
		// Récupération des événement avec la SDL
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				play = false;
			}
			break;
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						fleche = 3;
					break;
					case SDLK_DOWN:
						fleche = 4;
					break;
					case SDLK_LEFT:
						fleche = 2;
					break;
					case SDLK_RIGHT:
						fleche = 1;
					break;
				}
			}
			default:
				break;
			}
		}

		if(fleche != 0)
			mouvement(plateau.tab, fleche);
		SDL_RenderClear(renderer);
		afficherFond(renderer, fenetre);
		afficherPlateauVide(renderer, plateau);
		afficherPlateauPlein(renderer, plateau);
		SDL_RenderPresent(renderer);

		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
		SHP_Limit_FPS(frame_limit);
		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
	}

	libererTab(plateau.tab, plateau.taille);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	return 0;
}