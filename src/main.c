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

	plateau.tab = creerTab(plateau.taille);

	animation_list_2048 *liste_animation = NULL;

	/*plateau.tab[0][0] = 2;
	animation_value_2048 element_test;
	element_test.depart_int.x = 0;
	element_test.depart_int.y = 0;

	coordInt_2048 arrive_test;
	arrive_test.x = 0;
	arrive_test.y = 3;

	element_test.depart = coordTabAcoordAffichage(plateau, element_test.depart_int);
	element_test.affichage = element_test.depart;
	element_test.arrive = coordTabAcoordAffichage(plateau, arrive_test);

	anim_rajoute_element(&liste_animation, element_test);*/
	initialisation(plateau);
	depart(plateau.tab);
	SHP_bool enAnimation = true;

	int **tab_temp = creerTab(plateau.taille);
	int **tab_temp2 = creerTab(plateau.taille);
	copierPlateauVersTab(plateau, tab_temp2);

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

		if (fleche != 0 && !enAnimation)
		{
			copierPlateauVersTab(plateau, tab_temp);
			mouvement(plateau, fleche, &liste_animation);
			copierPlateauVersTab(plateau, tab_temp2);
			copierTabVersPlateau(plateau, tab_temp);
			debug_anim_list(liste_animation);
		}


		SDL_RenderClear(renderer);
		afficherFond(renderer, fenetre);
		afficherPlateauVide(renderer, plateau);

		enAnimation = anim_deplacement(renderer, plateau, &liste_animation);

		if (!enAnimation)
		{
			copierTabVersPlateau(plateau, tab_temp2);
			afficherPlateauPlein(renderer, plateau);
		}
		
		SDL_RenderPresent(renderer);

		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
		SHP_Limit_FPS(frame_limit);
		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
	}

	anim_detruire_list(&liste_animation);
	libererTab(plateau.tab, plateau.taille);
	libererTab(tab_temp, plateau.taille);
	libererTab(tab_temp2, plateau.taille);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	return 0;
}