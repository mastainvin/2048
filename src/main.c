#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "jeu.h"
#include "interface.h"
#include "sauvegarde.h"

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

	coord_2048 coord_curseur;
	coord_curseur.x = 0;
	coord_curseur.y = 0;

	coord_2048 coord_clic;
	coord_clic.x = 0;
	coord_clic.y = 0;

	SHP_bool play = true;
	int frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;

	plateau_2048 plateau;
	plateau.largeur = min(fenetre.h, fenetre.w) / 1.2;
	plateau.x = (fenetre.w - plateau.largeur) / 2;
	plateau.y = 150;
	plateau.taille = 4;
	plateau.score = 0;
	plateau.bestscore = 0;
	plateau.tab = creerTab(plateau.taille);

	initialisation(plateau);
	depart(plateau);

	//A place dans la condition appuis sur bouton 2 joueurs
	fenetre.w = 900;

	plateau_2048 plateau2;
	plateau2.largeur = plateau.largeur;
	plateau2.x = fenetre.w - plateau2.largeur - plateau.x;
	plateau2.y = 150;
	plateau2.taille = 4;
	plateau2.score = 0;
	plateau2.bestscore = 0;
	plateau2.tab = creerTab(plateau2.taille);

	initialisation(plateau2);
	depart(plateau2);

	animation_list_2048 *liste_animation = NULL;
	animation_list_2048 *liste_animation_dep = NULL;
	animation_list_2048 *liste_animation_app = NULL;

	SHP_bool enMouvement = false;
	SHP_bool enAddition = false;
	SHP_bool enApparation = false;

	animation_list_2048 *liste_animation2 = NULL;
	animation_list_2048 *liste_animation_dep2 = NULL;
	animation_list_2048 *liste_animation_app2 = NULL;

	SHP_bool enMouvement2 = false;
	SHP_bool enAddition2 = false;
	SHP_bool enApparation2 = false;

	// A placer dans la condition appuis sur bouton continuer
	//lecture(&plateau);

	position_utilisateur position = deuxJoueurArcadeMode;
	partie_2048 partie;
	partie.tour = 1;
	partie.numero_tour = 1;

	joueur_arcade_2048 joueur1_arcade;
	joueur1_arcade.bonus = 0;
	joueur1_arcade.malus = 0;
	generer_bonus(&joueur1_arcade);

	joueur_arcade_2048 joueur2_arcade;
	joueur2_arcade.bonus = 0;
	joueur2_arcade.malus = 0;
	generer_bonus(&joueur2_arcade);

	joueur1_arcade.palier = palier(plateau);
	joueur2_arcade.palier = palier(plateau2);

	joueur1_arcade.chrono = 0;
	joueur2_arcade.chrono = 0;

	joueur1_arcade.rapide = false;
	joueur1_arcade.inverse = false;

	joueur2_arcade.rapide = false;
	joueur2_arcade.inverse = false;
	SDL_SetWindowSize(window, fenetre.w, fenetre.h);

	int time_after = SDL_GetTicks();
	int time_before = SDL_GetTicks();
	int time_before2 = SDL_GetTicks();
	int time_before_jeu = SDL_GetTicks();

	int chrono_jeu = 60;
	int palier_max = 2048;

	while (play)
	{

		// Déclaration de la variable événement
		SDL_Event event;

		int fleche = 0;
		int fleche2 = 0;

		int touche_bonus1 = 0;
		int touche_bonus2 = 0;

		coord_clic.x = 0;
		coord_clic.y = 0;

		int temps_passe = time_after - time_before;
		int temps_passe2 = time_after - time_before2;

		int temps_passe_jeu = time_after - time_before_jeu;

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
				case SDLK_z:
					fleche2 = 3;
					break;
				case SDLK_s:
					fleche2 = 4;
					break;
				case SDLK_q:
					fleche2 = 2;
					break;
				case SDLK_d:
					fleche2 = 1;
					break;
				case SDLK_x:
					touche_bonus2 = 1;
					break;
				case SDLK_c:
					touche_bonus2 = 2;
					break;
				case SDLK_l:
					touche_bonus1 = 1;
					break;
				case SDLK_m:
					touche_bonus1 = 2;
					break;
				}
			}
			break;

			case SDL_MOUSEMOTION:
			{
				coord_curseur.x = event.motion.x;
				coord_curseur.y = event.motion.y;
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				coord_clic.x = event.button.x;
				coord_clic.y = event.button.y;
			}
			break;

			default:
				break;
			}
		}
		SDL_RenderClear(renderer);
		afficherFond(renderer, fenetre);

		switch (position)
		{
		case menu_principal:

			break;
		case unJoueur:
		{
			SHP_bool peut_jouer = defaite_unJoueur(plateau);
			if (fleche != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer)
			{
				plateau.score += mouvement(plateau, fleche, &liste_animation, &liste_animation_dep, &liste_animation_app);
				plateau.bestscore = max(plateau.score, plateau.bestscore);
			}

			afficherPlateauVide(renderer, plateau);

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau);

			afficher_info_int(renderer, NULL, plateau.largeur + (fenetre.w - plateau.largeur) / 2 - 100, 50, "SCORE", plateau.score);
			afficher_info_int(renderer, NULL, plateau.x, 50, "MEILLEUR", plateau.bestscore);

			if (!peut_jouer && !enMouvement && !enAddition && !enApparation)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

				plateau.score = recommencer(renderer, plateau, coord_curseur, coord_clic, CENTER, CENTER);
			}
			else
			{
				plateau.score = recommencer(renderer, plateau, coord_curseur, coord_clic, CENTER, plateau.largeur + plateau.y + 25);
			}
		}
		break;
		case deuxJoueur:
		{
			afficherFond(renderer, fenetre);
			afficherPlateauVide(renderer, plateau);
			afficherPlateauVide(renderer, plateau2);

			SHP_bool peut_jouer = defaite_unJoueur(plateau);
			if (fleche2 != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer && partie.tour == 1)
			{
				plateau.score += mouvement(plateau, fleche2, &liste_animation, &liste_animation_dep, &liste_animation_app);
				partie.tour = 2;
				partie.numero_tour++;
			}

			afficherPlateauVide(renderer, plateau);

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau);

			SHP_bool peut_jouer2 = defaite_unJoueur(plateau2);
			if (fleche != 0 && !enMouvement2 && !enAddition2 && !enApparation2 && peut_jouer2 && partie.tour == 2)
			{
				plateau2.score += mouvement(plateau2, fleche, &liste_animation2, &liste_animation_dep2, &liste_animation_app2);
				partie.tour = 1;
			}

			afficherPlateauVide(renderer, plateau2);

			enMouvement2 = anim_deplacement(renderer, plateau2, &liste_animation2);

			if (!enMouvement2)
			{
				enAddition2 = anim_addition(renderer, plateau2, &liste_animation_dep2);
				enApparation2 = anim_apparition(renderer, plateau2, &liste_animation_app2);
			}

			if (!enMouvement2 && !enAddition2 && !enApparation2)
				afficherPlateauPlein(renderer, plateau2);

			afficher_info_int(renderer, &fenetre, CENTER, 100, "JOUEUR", partie.tour);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2, 50, "SCORE", plateau.score);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2 + fenetre.w / 2 + 50, 50, "SCORE", plateau2.score);
			afficherTitreJoueur(renderer, plateau, plateau2);
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, (fenetre.h - 30) / 2 - 30, "TOUR", partie.numero_tour);

			if (partie.numero_tour == TOUR_MAX || !defaite_unJoueur(plateau) || !defaite_unJoueur(plateau2))
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

				if (plateau.score > plateau2.score)
				{
					afficher_Victoire(renderer, fenetre, 1);
				}
				else if (plateau2.score > plateau.score)
				{
					afficher_Victoire(renderer, fenetre, 2);
				}
				else if (plateau2.score == plateau.score)
				{
					afficher_Egalite(renderer, fenetre);
				}

				recommencer_deuxJoueurs(renderer, plateau, plateau2, &plateau.score, &plateau2.score, coord_curseur, coord_clic, fenetre, &partie);
			}
			else
			{
				recommencer_deuxJoueurs(renderer, plateau, plateau2, &plateau.score, &plateau2.score, coord_curseur, coord_clic, fenetre, &partie);
			}
		}
		break;
		case IA:
			break;
		case deuxJoueurArcadeMode:
		{
			if ((joueur1_arcade.inverse || joueur1_arcade.rapide) && joueur1_arcade.chrono == 0)
				joueur1_arcade.chrono = 10;

			if ((joueur1_arcade.inverse || joueur1_arcade.rapide) && temps_passe >= 1000)
			{
				time_before = SDL_GetTicks();
				joueur1_arcade.chrono--;
			}

			if (joueur1_arcade.chrono <= 0)
			{
				joueur1_arcade.chrono = 0;
				joueur1_arcade.inverse = false;
				joueur1_arcade.rapide = false;
			}

			if ((joueur2_arcade.inverse || joueur2_arcade.rapide) && joueur2_arcade.chrono == 0)
				joueur2_arcade.chrono = 10;

			if ((joueur2_arcade.inverse || joueur2_arcade.rapide) && temps_passe2 >= 1000)
			{
				time_before2 = SDL_GetTicks();
				joueur2_arcade.chrono--;
			}

			if (joueur2_arcade.chrono <= 0)
			{
				joueur2_arcade.chrono = 0;
				joueur2_arcade.inverse = false;
				joueur2_arcade.rapide = false;
			}

			if (joueur1_arcade.inverse)
				bonus_inverserTouches(&fleche2);

			if (joueur1_arcade.rapide)
			{
				anim_detruire_list(&liste_animation);
				anim_detruire_list(&liste_animation_dep);
				anim_detruire_list(&liste_animation_app);
			}

			if (joueur2_arcade.inverse)
				bonus_inverserTouches(&fleche);

			if (joueur2_arcade.rapide)
			{
				anim_detruire_list(&liste_animation2);
				anim_detruire_list(&liste_animation_dep2);
				anim_detruire_list(&liste_animation_app2);
			}

			afficherFond(renderer, fenetre);
			afficherPlateauVide(renderer, plateau);
			afficherPlateauVide(renderer, plateau2);

			SHP_bool peut_jouer = defaite_unJoueur(plateau);

			if (fleche2 != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer)
			{
				plateau.score += mouvement(plateau, fleche2, &liste_animation, &liste_animation_dep, &liste_animation_app);
			}

			if (max_tab(plateau) == joueur1_arcade.palier)
			{
				joueur1_arcade.palier = 4 * joueur1_arcade.palier;
				joueur1_arcade.bonus = joueur1_arcade.prochain_bonus;
				joueur1_arcade.malus = joueur1_arcade.prochain_malus;
				generer_bonus(&joueur1_arcade);
			}

			if (touche_bonus2 != 0)
			{
				if (touche_bonus2 == 1)
				{
					switch (joueur1_arcade.bonus)
					{
					case 1:
						bonus_2to8(plateau);
						break;
					case 2:
						bonus_rangement(plateau);
						break;
					case 3:
						joueur1_arcade.rapide = true;
						break;
					}

					joueur1_arcade.bonus = 0;
					joueur1_arcade.malus = 0;
				}
				else
				{
					switch (joueur1_arcade.malus)
					{
					case 1:
						bonus_detuire(plateau2);
						break;

					case 2:
						bonus_melange(plateau2);
						break;
					case 3:
						joueur2_arcade.inverse = true;
						break;
					}
					joueur1_arcade.bonus = 0;
					joueur1_arcade.malus = 0;
				}
			}

			afficherPlateauVide(renderer, plateau);

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau);

			SHP_bool peut_jouer2 = defaite_unJoueur(plateau2);
			if (fleche != 0 && !enMouvement2 && !enAddition2 && !enApparation2 && peut_jouer2)
			{
				plateau2.score += mouvement(plateau2, fleche, &liste_animation2, &liste_animation_dep2, &liste_animation_app2);
			}

			if (max_tab(plateau2) == joueur2_arcade.palier)
			{
				joueur2_arcade.palier = 4 * joueur2_arcade.palier;
				joueur2_arcade.bonus = joueur2_arcade.prochain_bonus;
				joueur2_arcade.malus = joueur2_arcade.prochain_malus;
				generer_bonus(&joueur2_arcade);
			}

			if (touche_bonus1 != 0)
			{
				if (touche_bonus1 == 1)
				{
					switch (joueur2_arcade.bonus)
					{
					case 1:
						bonus_2to8(plateau2);
						break;

					case 2:
						bonus_rangement(plateau2);
						break;
					case 3:
						joueur2_arcade.rapide = true;
						break;
					}

					joueur2_arcade.bonus = 0;
					joueur2_arcade.malus = 0;
				}
				else
				{
					switch (joueur2_arcade.malus)
					{
					case 1:
						bonus_detuire(plateau);
						break;

					case 2:
						bonus_melange(plateau);
						break;
					case 3:
						joueur1_arcade.inverse = true;
						break;
					}
					joueur2_arcade.bonus = 0;
					joueur2_arcade.malus = 0;
				}
			}

			afficherPlateauVide(renderer, plateau2);

			enMouvement2 = anim_deplacement(renderer, plateau2, &liste_animation2);

			if (!enMouvement2)
			{
				enAddition2 = anim_addition(renderer, plateau2, &liste_animation_dep2);
				enApparation2 = anim_apparition(renderer, plateau2, &liste_animation_app2);
			}

			if (!enMouvement2 && !enAddition2 && !enApparation2)
				afficherPlateauPlein(renderer, plateau2);

			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2, 10, "PALIER", joueur1_arcade.palier);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2 + fenetre.w / 2 + 50, 10, "PALIER", joueur2_arcade.palier);
			/*
			afficher_prochainBonus(renderer, plateau, joueur1_arcade);
			afficher_prochainBonus(renderer, plateau2, joueur2_arcade);
			*/
			afficher_bonus(renderer, plateau, joueur1_arcade);
			afficher_bonus(renderer, plateau2, joueur2_arcade);
			
			afficher_info_int(renderer, NULL, plateau.x + (plateau.largeur - 100) / 2, plateau.y + plateau.largeur + 10, "CHRONO J1", joueur1_arcade.chrono);
			afficher_info_int(renderer, NULL, plateau2.x + (plateau2.largeur - 100) / 2, plateau2.y + plateau2.largeur + 10, "CHRONO J2", joueur2_arcade.chrono);
			
			if (temps_passe_jeu >= 1000)
			{
				time_before_jeu = SDL_GetTicks();
				chrono_jeu--;
			}

			if (chrono_jeu <= 0)
			{
				chrono_jeu = 60;
				palier_max = palier_max / 2;
			}

			if (max_tab(plateau) == palier_max || !defaite_unJoueur(plateau2))
			{
				afficher_Victoire(renderer, fenetre, 1);
			}
			else if (max_tab(plateau2) == palier_max || !defaite_unJoueur(plateau))
			{
				afficher_Victoire(renderer, fenetre, 2);
			}
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, 100, "PALIER MAX", palier_max);
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, 200, "CHRONO JEU", chrono_jeu);
		}
		break;
		default:
			break;
		}

		SDL_RenderPresent(renderer);

		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
		SHP_Limit_FPS(frame_limit);
		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;

		time_after = SDL_GetTicks();

	}

	anim_detruire_list(&liste_animation);
	anim_detruire_list(&liste_animation_dep);
	anim_detruire_list(&liste_animation_app);

	anim_detruire_list(&liste_animation2);
	anim_detruire_list(&liste_animation_dep2);
	anim_detruire_list(&liste_animation_app2);

	sauvegarde(plateau);
	libererTab(plateau.tab, plateau.taille);
	libererTab(plateau2.tab, plateau2.taille);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	return 0;
}