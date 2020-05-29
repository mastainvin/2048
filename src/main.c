#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "jeu.h"
#include "interface.h"

#include "header_2048.h"

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
	plateau.score = 0;
	plateau.tab = creerTab(plateau.taille);

	animation_list_2048 *liste_animation = NULL;
	animation_list_2048 *liste_animation_dep = NULL;
	animation_list_2048 *liste_animation_app = NULL;

	SHP_bool enMouvement = false;
	SHP_bool enAddition = false;
	SHP_bool enApparation = false;

	initialisation(plateau);
	depart(plateau);

	position_utilisateur position = unJoueur;

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
		SDL_RenderClear(renderer);
		afficherFond(renderer, fenetre);

		switch(position)
		{
			case menu_principal:
			break;
			case unJoueur:
			{
				if (fleche != 0 && !enMouvement && !enAddition && !enApparation)
					plateau.score += mouvement(plateau, fleche, &liste_animation, &liste_animation_dep, &liste_animation_app);

				afficherPlateauVide(renderer, plateau);

				enMouvement = anim_deplacement(renderer, plateau, &liste_animation);

				if (!enMouvement)
				{
					enAddition = anim_addition(renderer, plateau, &liste_animation_dep);
					enApparation = anim_apparition(renderer, plateau, &liste_animation_app);
				}

				if (!enMouvement && !enAddition && !enApparation)
					afficherPlateauPlein(renderer, plateau);

				afficher_score(renderer, plateau, plateau.largeur + (fenetre.w - plateau.largeur) / 2 - 100, 50);
			}		
			break;
			case deuxJoueur:
			break;
			case IA:
			break;
			case deuxJoueurArcadeMode:
			break;
			default:
			break;
		}

	
		SDL_RenderPresent(renderer);

		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
		SHP_Limit_FPS(frame_limit);
		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
	}

	anim_detruire_list(&liste_animation);
	anim_detruire_list(&liste_animation_dep);
	anim_detruire_list(&liste_animation_app);

	libererTab(plateau.tab, plateau.taille);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	return 0;
}