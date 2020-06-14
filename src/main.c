/**
* \file main.c
* \brief fichier principale 2048
* \author Vincent Mastain
* \version 0.1
* \date 10 juin 2020
*
*	Programme principale pour le jeu 2048
* Utilise une boucle infinie qui affiche à l'écran les données en fonction de l'emplacement
* de l'utilisateur dans le programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "jeu.h"
#include "interface.h"
#include "sauvegarde.h"
#include "IA.h"
#include "header_2048.h"

/**
* \fn int main(int argc, char** argv)
* \brief Fonction principale du 2048
* \author Vincent Mastain
* \author Ahmed Trabelsi
* \version 0.1
* \date 14 juin 2020
* \param argc Nombre d'argument de la ligne de commande
* \param argv Paramètres de la ligne de commande
* \return 0 dans tous les cas
*
* Cette fonction affiche gère le 2048 
* Affichage d'un menu, de plateaux dans une boucle infinie
* Quitte le programme lorsque l'utilisateur le demande
*
*/
int main(int argc, char **argv)
{
	// Initialisation de la SDL
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	// Création du rectangle représentant la fenêtre et création de la fenêre SDL
	SDL_Rect fenetre;
	fenetre.w = 400;
	fenetre.h = 600;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_CreateWindowAndRenderer(fenetre.w, fenetre.h, 0, &window, &renderer);

	// Création des differents états du curseurs
	coord_2048 coord_curseur;
	coord_curseur.x = 0;
	coord_curseur.y = 0;

	coord_2048 coord_clic;
	coord_clic.x = 0;
	coord_clic.y = 0;

	// Variable correspondant à la taille sélectionnée du tableau
	int mode_de_jeu = 4;

	// Utilisée dans la boucle infinie du jeu
	SHP_bool play = true;

	// Variable permettant la gestion des fps
	int frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;

	// Création du plateau pour le joueur 1
	plateau_2048 plateau;
	plateau.largeur = min(fenetre.h, fenetre.w) / 1.2;
	plateau.x = (fenetre.w - plateau.largeur) / 2;
	plateau.y = 150;
	plateau.taille = 4;
	plateau.score = 0;
	plateau.bestscore = 0;

	// Création du plateau pour le joueur 2
	plateau_2048 plateau2;
	plateau2.largeur = plateau.largeur;
	plateau2.x = 900 - plateau2.largeur - plateau.x;
	plateau2.y = 150;
	plateau2.taille = 4;
	plateau2.score = 0;
	plateau2.bestscore = 0;

	// Création des variables correspondant a la gestion des animations
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

	position_utilisateur position = menu_principal;

	partie_2048 partie;

	joueur_arcade_2048 joueur1_arcade;
	joueur_arcade_2048 joueur2_arcade;

	int time_after = SDL_GetTicks();
	int time_before = SDL_GetTicks();
	int time_before2 = SDL_GetTicks();
	int time_before_jeu = SDL_GetTicks();

	// Récupération des valeurs principales de la sauvegarde
	position_utilisateur position_sauvegarde;
	int meilleur_score_sauvegarde;
	lecture_position(&position_sauvegarde, &meilleur_score_sauvegarde);

	SHP_bool darkmode = false;

	while (play)
	{

		// Déclaration de la variable événement
		SDL_Event event;

		// On reinitialise les variables pour empêches les conflits
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

		// On efface ce qu'il y a sur l'écran  +  on affiche le fond
		SDL_RenderClear(renderer);
		afficherFond(renderer, fenetre, darkmode);

		switch (position)
		{
			/* Selon la position de l'utilisateur on affiche different boutons/informations*/
		case menu_principal:
		{
			/* Cas du menu_principal 
				On affiche donc tout les boutons correspondants à chaque modes + les boutons de gestion de la taille des plateaus
				On gère aussi le clic de la souris sur ces boutons, à partir du clic on initialise des variables puis on change la
				position de l'utilisateur*/

			if (fenetre.w == 900)
			{
				fenetre.w = 400;
				SDL_SetWindowSize(window, fenetre.w, fenetre.h);
			}
			affiche_solo(renderer, fenetre, coord_curseur, darkmode);
			affiche_vs(renderer, fenetre, coord_curseur, darkmode);
			affiche_ia(renderer, fenetre, coord_curseur, darkmode);
			affiche_quitter(renderer, fenetre, coord_curseur, darkmode);
			bouton_darkmode(renderer, fenetre, &darkmode, coord_clic);

			if (position_sauvegarde != menu_principal)
				affiche_continuer(renderer, fenetre, coord_curseur, darkmode);
			arcade(renderer, fenetre, coord_curseur, darkmode);
			affiche_titre(renderer, fenetre, darkmode);
			mode1(renderer, fenetre, &mode_de_jeu, coord_clic, darkmode);
			mode3(renderer, fenetre, &mode_de_jeu, coord_clic, darkmode);
			mode2(renderer, fenetre, &mode_de_jeu, coord_clic, darkmode);

			if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 90 && coord_clic.y <= 90 + 50)
			{
				if (position_sauvegarde != menu_principal)
				{
					lecture(&plateau, &plateau2, &partie, &position, &joueur1_arcade, &joueur2_arcade);

					if (position == deuxJoueur || position == IA || position == deuxJoueurArcadeMode)
					{
						fenetre.w = 900;
						SDL_SetWindowSize(window, fenetre.w, fenetre.h);
					}
				}
			}
			else if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 160 && coord_clic.y <= 160 + 50)
			{
				plateau.taille = mode_de_jeu;
				plateau.tab = creerTab(plateau.taille);
				plateau.score = 0;
				plateau.bestscore = meilleur_score_sauvegarde;
				initialisation(plateau);
				depart(plateau);

				partie.continuer_apres_2048 = false;

				position = unJoueur;
				position_sauvegarde = unJoueur;
			}

			else if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 230 && coord_clic.y <= 230 + 50)
			{
				plateau.taille = mode_de_jeu;
				plateau.tab = creerTab(plateau.taille);
				plateau.score = 0;
				plateau.bestscore = meilleur_score_sauvegarde;
				initialisation(plateau);
				depart(plateau);

				plateau2.taille = mode_de_jeu;
				plateau2.tab = creerTab(plateau2.taille);
				plateau2.score = 0;
				initialisation(plateau2);
				depart(plateau2);

				partie.tour = 1;
				partie.numero_tour = 1;

				fenetre.w = 900;
				SDL_SetWindowSize(window, fenetre.w, fenetre.h);
				position = deuxJoueur;
				position_sauvegarde = deuxJoueur;
			}

			else if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 300 && coord_clic.y <= 300 + 50)
			{
				plateau.taille = mode_de_jeu;
				plateau.tab = creerTab(plateau.taille);
				plateau.score = 0;
				plateau.bestscore = meilleur_score_sauvegarde;
				initialisation(plateau);
				depart(plateau);

				plateau2.taille = mode_de_jeu;
				plateau2.tab = creerTab(plateau2.taille);
				plateau2.score = 0;
				initialisation(plateau2);
				depart(plateau2);

				partie.tour = 1;
				partie.numero_tour = 1;

				fenetre.w = 900;
				SDL_SetWindowSize(window, fenetre.w, fenetre.h);
				position = IA;
				position_sauvegarde = IA;
			}

			else if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 370 && coord_clic.y <= 370 + 50)

			{
				plateau.taille = mode_de_jeu;
				plateau.tab = creerTab(plateau.taille);
				plateau.score = 0;
				plateau.bestscore = meilleur_score_sauvegarde;
				initialisation(plateau);
				depart(plateau);

				plateau2.taille = mode_de_jeu;
				plateau2.tab = creerTab(plateau2.taille);
				plateau2.score = 0;
				initialisation(plateau2);
				depart(plateau2);

				joueur1_arcade.bonus = 0;
				joueur1_arcade.malus = 0;
				generer_bonus(&joueur1_arcade);

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

				partie.chrono = 60;
				partie.palier_max = 2048;
				fenetre.w = 900;
				SDL_SetWindowSize(window, fenetre.w, fenetre.h);
				position = deuxJoueurArcadeMode;
				position_sauvegarde = deuxJoueurArcadeMode;
			}

			else if (coord_clic.x >= (fenetre.w - 120) / 2 && coord_clic.x <= (fenetre.w - 120) / 2 + 120 && coord_clic.y >= 440 && coord_clic.y <= 440 + 50)
			{
				play = false;
			}
		}
		break;
		case unJoueur:
		{
			/* Cas du jeu seul 
				On vérifie que l'utilisateur ait appuyé sur une des flèches
				On vérifie qu'il n'est pas perdu puis on réalise le déplacement correspondant
				Les listes d'animations sont remplis lors du mouvement puis affichées à la fin*/
			meilleur_score_sauvegarde = plateau.bestscore;
			SHP_bool peut_jouer = defaite_unJoueur(plateau);
			if (fleche != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer && (!atteindre_2048(plateau) || partie.continuer_apres_2048))
			{
				plateau.score += mouvement(plateau, fleche, &liste_animation, &liste_animation_dep, &liste_animation_app);
				plateau.bestscore = max(plateau.score, plateau.bestscore);
			}

			// On affiche le plateau vide et les cases en déplacements indépendemment
			afficherPlateauVide(renderer, plateau, darkmode);

			// On anime la liste de déplacement
			enMouvement = anim_deplacement(renderer, plateau, &liste_animation, darkmode);

			if (!enMouvement)
			{
				// On anime en même temps la liste d'addition et la liste d'apparition
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep, darkmode);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app, darkmode);
			}

			// Lorsque toutes les animations sont terminées on affiche le tableau plein

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau, darkmode);

			// Affichage du score
			afficher_info_int(renderer, NULL, plateau.largeur + (fenetre.w - plateau.largeur) / 2 - 100, 50, "SCORE", plateau.score, darkmode);
			afficher_info_int(renderer, NULL, plateau.x, 50, "MEILLEUR", plateau.bestscore, darkmode);

			// Si la partie est finie on obliger l'utilisateur à appuyer sur recommencer ou quitter
			if ((!peut_jouer || (atteindre_2048(plateau) && !partie.continuer_apres_2048)) && !enMouvement && !enAddition && !enApparation)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
			}
			if (atteindre_2048(plateau) && partie.continuer_apres_2048 == false)
			{
				partie.continuer_apres_2048 = continuer_jeu_solo(renderer, fenetre, coord_curseur, coord_clic, darkmode);
			}
		}
		break;
		case deuxJoueur:
		{
			/* Cas du jeu à deux normal tour par tour
				Le fonctionnement est similaire à celui du mode un joueur
				Le seul changement est qu'on réalise les déplacements chacun après l'autre
				La fin de partie est géré par un nombre de tour max = 30 après cela on compare
				les scores */
			afficherPlateauVide(renderer, plateau, darkmode);
			afficherPlateauVide(renderer, plateau2, darkmode);

			SHP_bool fin_partie = partie.numero_tour == TOUR_MAX || !defaite_unJoueur(plateau) || !defaite_unJoueur(plateau2);

			SHP_bool peut_jouer = defaite_unJoueur(plateau);
			if (fleche2 != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer && partie.tour == 1 && !fin_partie)
			{
				int **tab_temp = creerTab(plateau.taille);
				copierPlateauVersTab(plateau, tab_temp);
				plateau.score += mouvement(plateau, fleche2, &liste_animation, &liste_animation_dep, &liste_animation_app);

				if (!estEgale(plateau.tab, tab_temp, plateau.taille))
				{
					partie.tour = 2;
					partie.numero_tour++;
				}
				libererTab(tab_temp, plateau.taille);
			}

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation, darkmode);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep, darkmode);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app, darkmode);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau, darkmode);

			SHP_bool peut_jouer2 = defaite_unJoueur(plateau2);
			if (fleche != 0 && !enMouvement2 && !enAddition2 && !enApparation2 && peut_jouer2 && partie.tour == 2 && !fin_partie)
			{
				int **tab_temp = creerTab(plateau2.taille);
				copierPlateauVersTab(plateau2, tab_temp);
				plateau2.score += mouvement(plateau2, fleche, &liste_animation2, &liste_animation_dep2, &liste_animation_app2);

				if (!estEgale(plateau2.tab, tab_temp, plateau2.taille))
				{
					partie.tour = 1;
				}
				libererTab(tab_temp, plateau2.taille);
			}

			enMouvement2 = anim_deplacement(renderer, plateau2, &liste_animation2, darkmode);

			if (!enMouvement2)
			{
				enAddition2 = anim_addition(renderer, plateau2, &liste_animation_dep2, darkmode);
				enApparation2 = anim_apparition(renderer, plateau2, &liste_animation_app2, darkmode);
			}

			if (!enMouvement2 && !enAddition2 && !enApparation2)
				afficherPlateauPlein(renderer, plateau2, darkmode);

			afficher_info_int(renderer, &fenetre, CENTER, 100, "JOUEUR", partie.tour, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2, 50, "SCORE", plateau.score, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2 + fenetre.w / 2 + 50, 50, "SCORE", plateau2.score, darkmode);
			afficherTitreJoueur(renderer, plateau, plateau2, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, (fenetre.h - 30) / 2 - 30, "TOUR", partie.numero_tour, darkmode);

			if (fin_partie)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

				if (plateau.score > plateau2.score)
				{
					afficher_Victoire(renderer, fenetre, 1, darkmode);
				}
				else if (plateau2.score > plateau.score)
				{
					afficher_Victoire(renderer, fenetre, 2, darkmode);
				}
				else if (plateau2.score == plateau.score)
				{
					afficher_Egalite(renderer, fenetre, darkmode);
				}
			}
		}
		break;
		case IA:
		{
			/* Cas de l'IA
				Le fonctionnement est égale à celui du deux joueurs l'exception est lors du jeu du joueur 2
				Aucun choix n'est fait par clavier mais simplement la fonction choisissant le meilleur coup */

			afficherPlateauVide(renderer, plateau, darkmode);
			afficherPlateauVide(renderer, plateau2, darkmode);
			SHP_bool fin_de_partie = partie.numero_tour == TOUR_MAX || !defaite_unJoueur(plateau) || !defaite_unJoueur(plateau2);
			SHP_bool peut_jouer = defaite_unJoueur(plateau);
			if (fleche2 != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer && partie.tour == 1 && !fin_de_partie)
			{
				int **tab_temp = creerTab(plateau.taille);
				copierPlateauVersTab(plateau, tab_temp);
				plateau.score += mouvement(plateau, fleche2, &liste_animation, &liste_animation_dep, &liste_animation_app);

				if (!estEgale(plateau.tab, tab_temp, plateau.taille))
				{
					partie.tour = 2;
					partie.numero_tour++;
				}
				libererTab(tab_temp, plateau.taille);
			}

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation, darkmode);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep, darkmode);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app, darkmode);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau, darkmode);

			SHP_bool peut_jouer2 = defaite_unJoueur(plateau2);
			if (!enMouvement2 && !enAddition2 && !enApparation2 && peut_jouer2 && partie.tour == 2)
			{
				// Coup de l'IA avec création dynamique des tableaux permettant une gestion de la mémoire
				coup_IA position_temp;
				position_temp.position_coup.tab = creerTab(plateau2.taille);
				copier_plateau(plateau2, &position_temp.position_coup);
				libererTab(plateau2.tab, plateau2.taille);
				// Fonction choisissant le meilleur coup pour l'IA
				plateau2 = IA_max(position_temp, DEPTH_IA, &liste_animation2, &liste_animation_dep2, &liste_animation_app2).position_coup;
				partie.tour = 1;
				libererTab(position_temp.position_coup.tab, plateau2.taille);
			}

			enMouvement2 = anim_deplacement(renderer, plateau2, &liste_animation2, darkmode);

			if (!enMouvement2)
			{
				enAddition2 = anim_addition(renderer, plateau2, &liste_animation_dep2, darkmode);
				enApparation2 = anim_apparition(renderer, plateau2, &liste_animation_app2, darkmode);
			}

			if (!enMouvement2 && !enAddition2 && !enApparation2)
				afficherPlateauPlein(renderer, plateau2, darkmode);

			afficher_info_int(renderer, &fenetre, CENTER, 100, "JOUEUR", partie.tour, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2, 50, "SCORE", plateau.score, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2 + fenetre.w / 2 + 50, 50, "SCORE", plateau2.score, darkmode);
			afficherTitreJoueur(renderer, plateau, plateau2, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, (fenetre.h - 30) / 2 - 30, "TOUR", partie.numero_tour, darkmode);

			if (fin_de_partie)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

				if (plateau.score > plateau2.score)
				{
					afficher_Victoire(renderer, fenetre, 1, darkmode);
				}
				else if (plateau2.score > plateau.score)
				{
					afficher_Victoire(renderer, fenetre, 2, darkmode);
				}
				else if (plateau2.score == plateau.score)
				{
					afficher_Egalite(renderer, fenetre, darkmode);
				}
			}
		}
		break;
		case deuxJoueurArcadeMode:
		{
			/* Cas du mode arcade 
				Le mode de jeu ce comporte globalement comme le mode un Joueur
				Cependant, des atouts sont distribué au fur et à mesure dans la 
				partie faisant modifié le tableau adverse ou le sien*/

			// Vérification de la victoire si l'un des deux joueurs à atteint le palier ou a remplis son tableau
			SHP_bool victoire = 0;
			if (max_tab(plateau) == partie.palier_max || !defaite_unJoueur(plateau2))
			{
				victoire = 1;
			}
			else if (max_tab(plateau2) == partie.palier_max || !defaite_unJoueur(plateau))
			{
				victoire = 2;
			}
			SHP_bool fin_de_partie = (victoire != 0);

			// Gestion du bonus rapidité et du malus inverser
			if ((joueur1_arcade.inverse || joueur1_arcade.rapide) && joueur1_arcade.chrono == 0)
				joueur1_arcade.chrono = 10;

			if ((joueur1_arcade.inverse || joueur1_arcade.rapide) && temps_passe >= 1000 && !fin_de_partie)
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

			if ((joueur2_arcade.inverse || joueur2_arcade.rapide) && temps_passe2 >= 1000 && !fin_de_partie)
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

			afficherPlateauVide(renderer, plateau, darkmode);
			afficherPlateauVide(renderer, plateau2, darkmode);

			SHP_bool peut_jouer = defaite_unJoueur(plateau);

			if (fleche2 != 0 && !enMouvement && !enAddition && !enApparation && peut_jouer && !fin_de_partie)
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

			// Gestion des bonus et malus en fonction de la touche appuyée
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

			enMouvement = anim_deplacement(renderer, plateau, &liste_animation, darkmode);

			if (!enMouvement)
			{
				enAddition = anim_addition(renderer, plateau, &liste_animation_dep, darkmode);
				enApparation = anim_apparition(renderer, plateau, &liste_animation_app, darkmode);
			}

			if (!enMouvement && !enAddition && !enApparation)
				afficherPlateauPlein(renderer, plateau, darkmode);

			SHP_bool peut_jouer2 = defaite_unJoueur(plateau2);
			if (fleche != 0 && !enMouvement2 && !enAddition2 && !enApparation2 && peut_jouer2 && !fin_de_partie)
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

			enMouvement2 = anim_deplacement(renderer, plateau2, &liste_animation2, darkmode);

			if (!enMouvement2)
			{
				enAddition2 = anim_addition(renderer, plateau2, &liste_animation_dep2, darkmode);
				enApparation2 = anim_apparition(renderer, plateau2, &liste_animation_app2, darkmode);
			}

			if (!enMouvement2 && !enAddition2 && !enApparation2)
				afficherPlateauPlein(renderer, plateau2, darkmode);

			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2, 10, "PALIER", joueur1_arcade.palier, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w / 2 - 150) / 2 + fenetre.w / 2 + 50, 10, "PALIER", joueur2_arcade.palier, darkmode);

			afficher_bonus(renderer, plateau, joueur1_arcade, darkmode);
			afficher_bonus(renderer, plateau2, joueur2_arcade, darkmode);

			afficher_info_int(renderer, NULL, plateau.x + (plateau.largeur - 100) / 2, plateau.y + plateau.largeur + 10, "CHRONO J1", joueur1_arcade.chrono, darkmode);
			afficher_info_int(renderer, NULL, plateau2.x + (plateau2.largeur - 100) / 2, plateau2.y + plateau2.largeur + 10, "CHRONO J2", joueur2_arcade.chrono, darkmode);

			// Gestion du chrono de la partie
			if (temps_passe_jeu >= 1000 && !fin_de_partie)
			{
				time_before_jeu = SDL_GetTicks();
				partie.chrono--;
			}

			// Si ce chrono atteint 0 il est remit à 60 est le palier maximum diminue
			if (partie.chrono <= 0)
			{
				partie.chrono = 60;
				partie.palier_max = partie.palier_max / 2;
			}

			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, 100, "PALIER MAX", partie.palier_max, darkmode);
			afficher_info_int(renderer, NULL, (fenetre.w - 100) / 2, 200, "CHRONO JEU", partie.chrono, darkmode);

			if (fin_de_partie)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(renderer, NULL);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
				afficher_Victoire(renderer, fenetre, victoire, darkmode);
			}
		}
		break;
		default:
			break;
		}
		// En jeu, les boutons recommencer et quitter sont toujours présents
		if (position != menu_principal)
		{
			recommencer(renderer, fenetre, position, &partie, &plateau, &plateau2, coord_curseur, coord_clic, darkmode);
			position_sauvegarde = position;
			position = quitter(renderer, fenetre, plateau, plateau2, position, partie, joueur1_arcade, joueur2_arcade, coord_curseur, coord_clic, darkmode);
		}

		SDL_RenderPresent(renderer);

		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;
		SHP_Limit_FPS(frame_limit);
		frame_limit = SDL_GetTicks() + SHP_FRAME_PER_SECOND;

		time_after = SDL_GetTicks();
	}

	// On libère toutes les listes restantes
	anim_detruire_list(&liste_animation);
	anim_detruire_list(&liste_animation_dep);
	anim_detruire_list(&liste_animation_app);

	anim_detruire_list(&liste_animation2);
	anim_detruire_list(&liste_animation_dep2);
	anim_detruire_list(&liste_animation_app2);

	// On libére les tableaux si besoin
	if (position != menu_principal)
	{
		libererTab(plateau.tab, plateau.taille);
		libererTab(plateau2.tab, plateau2.taille);
	}

	// Enfin, la fenêtre est détruite et on quitte la SDL
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	return 0;
}