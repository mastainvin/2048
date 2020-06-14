/**
* \file interface.c
* \brief fonctions d'affichage sur la fenêtre
* \author Vincent Mastain
* \author Ahmed Trabelsi
* \version 0.1
* \date 13 juin 2020
*
*	Fonctions modifiant un Renderer (SDL) pour afficher la fenêtre du 2048.
* Utilisation de la librairie "shape2d" créer par Vincent Mastain afin de 
* faciliter l'affichage. 
*	
* Les fonctions sont peu commentées car reprennent tout le temps la même 
* construction : 
* Création d'un sprite puis affichage de ce sprite avec la lib shape2d
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "interface.h"
#include "jeu.h"
#include "header_2048.h"
#include "sauvegarde.h"

/* Fonction d'affichage du jeu basiques */

/**
* \fn void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief Affichage du fond de la fenêtre
* \author Vincent Mastain
* \version 0.1
* \date 12 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
{
	// Création d'une variable possèdant tout les valeurs afin d'affiche le fond
	SHP_Sprite background;
	background.background.x = 0;
	background.background.y = 0;
	background.background.h = fenetre.h;
	background.background.w = fenetre.w;

	if (darkmode)
	{
		background.background_color.r = 5;
		background.background_color.g = 7;
		background.background_color.b = 26;
	}
	else
	{
		background.background_color.r = 250;
		background.background_color.g = 248;
		background.background_color.b = 239;
	}

	background.withText = false;

	// Affichage du fond
	SHP_PrintSprite(background, renderer);
}

/**
* \fn void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode)
* \brief Affichage du plateau vide
* \author Vincent Mastain
* \version 0.1
* \date 12 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau contenant une taille et un tableau d'entiers
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode)
{
	SHP_Sprite plateau_fond;
	plateau_fond.background.x = plateau.x;
	plateau_fond.background.y = plateau.y;
	plateau_fond.background.w = plateau.largeur;
	plateau_fond.background.h = plateau.largeur;

	if (darkmode)
	{
		plateau_fond.background_color.r = 68;
		plateau_fond.background_color.g = 81;
		plateau_fond.background_color.b = 95;
	}
	else
	{
		plateau_fond.background_color.r = 187;
		plateau_fond.background_color.g = 174;
		plateau_fond.background_color.b = 160;
	}

	plateau_fond.withText = false;

	SHP_PrintSprite(plateau_fond, renderer);

	/* Affichage de toutes les cases vides */
	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			SHP_Sprite case_vide;
			case_vide.background.x = plateau_fond.background.x + j * (largeur_case + largeur_bordure) + largeur_bordure;
			case_vide.background.y = plateau_fond.background.y + i * (largeur_case + largeur_bordure) + largeur_bordure;
			case_vide.background.w = largeur_case;
			case_vide.background.h = largeur_case;

			if (darkmode)
			{
				case_vide.background_color.r = 50;
				case_vide.background_color.g = 63;
				case_vide.background_color.b = 75;
			}
			else
			{
				case_vide.background_color.r = 205;
				case_vide.background_color.g = 193;
				case_vide.background_color.b = 180;
			}

			case_vide.withText = false;

			SHP_PrintSprite(case_vide, renderer);
		}
	}
}

/**
* \fn void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color, SHP_bool darkmode)
* \brief Attribution d'une couleur en fonction d'un entier
* \author Vincent Mastain
* \version 0.1
* \date 12 juin 2020
* \param n entier de la case
* \param color couleur du fond de la case
* \param text_color couleur du texte de la case
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
* Attribution d'une couleur correspondant à un entier sur une case du tableau d'un joueur
*/
void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color, SHP_bool darkmode)
{

	if (darkmode)
	{
		text_color->r = 0;
		text_color->g = 0;
		text_color->b = 0;

		switch (n)
		{
		case 2:
			color->r = 17;
			color->g = 27;
			color->b = 37;

			text_color->r = 136;
			text_color->g = 145;
			text_color->b = 154;
			break;
		case 4:
			color->r = 18;
			color->g = 31;
			color->b = 55;

			text_color->r = 136;
			text_color->g = 145;
			text_color->b = 154;
			break;
		case 8:
			color->r = 13;
			color->g = 78;
			color->b = 134;

			break;
		case 16:
			color->r = 10;
			color->g = 106;
			color->b = 155;

			break;
		case 32:
			color->r = 9;
			color->g = 131;
			color->b = 160;

			break;
		case 64:
			color->r = 24;
			color->g = 132;
			color->b = 170;
			break;
		case 128:
			color->r = 18;
			color->g = 41;
			color->b = 113;
			break;
		case 256:
			color->r = 13;
			color->g = 48;
			color->b = 174;
			break;
		case 512:
			color->r = 18;
			color->g = 55;
			color->b = 175;
			break;
		case 1024:
			color->r = 18;
			color->g = 158;
			color->b = 193;
			break;
		case 2048:
			color->r = 18;
			color->g = 161;
			color->b = 209;
			break;
		case 4096:
			color->r = 195;
			color->g = 197;
			color->b = 205;
			break;
		case 8192:
			color->r = 179;
			color->g = 181;
			color->b = 189;
			break;
		default:
			color->r = 180;
			color->g = 184;
			color->b = 200;
			break;
		}
	}
	else
	{
		text_color->r = 255;
		text_color->g = 255;
		text_color->b = 255;

		switch (n)
		{
		case 2:
			color->r = 238;
			color->g = 228;
			color->b = 218;

			text_color->r = 119;
			text_color->g = 110;
			text_color->b = 101;
			break;
		case 4:
			color->r = 237;
			color->g = 224;
			color->b = 200;

			text_color->r = 119;
			text_color->g = 110;
			text_color->b = 101;
			break;
		case 8:
			color->r = 242;
			color->g = 177;
			color->b = 121;

			break;
		case 16:
			color->r = 245;
			color->g = 149;
			color->b = 100;

			break;
		case 32:
			color->r = 246;
			color->g = 124;
			color->b = 95;

			break;
		case 64:
			color->r = 231;
			color->g = 123;
			color->b = 85;
			break;
		case 128:
			color->r = 237;
			color->g = 214;
			color->b = 142;
			break;
		case 256:
			color->r = 242;
			color->g = 207;
			color->b = 81;
			break;
		case 512:
			color->r = 237;
			color->g = 200;
			color->b = 80;
			break;
		case 1024:
			color->r = 237;
			color->g = 97;
			color->b = 62;
			break;
		case 2048:
			color->r = 237;
			color->g = 94;
			color->b = 46;
			break;
		case 4096:
			color->r = 60;
			color->g = 58;
			color->b = 50;
			break;
		case 8192:
			color->r = 76;
			color->g = 74;
			color->b = 66;
			break;
		default:
			color->r = 75;
			color->g = 71;
			color->b = 55;
			break;
		}
	}
}

/**
* \fn void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode)
* \brief Affichage d'une plateau avec toutes les cases d'un tableau
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau d'un joueur de 2048
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau, SHP_bool darkmode)
{
	/* Affichage de toutes les cases */
	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			if (plateau.tab[i][j] != 0)
			{

				SHP_Sprite case_pleine;
				case_pleine.background.x = plateau.x + j * (largeur_case + largeur_bordure) + largeur_bordure;
				case_pleine.background.y = plateau.y + i * (largeur_case + largeur_bordure) + largeur_bordure;
				case_pleine.background.w = largeur_case;
				case_pleine.background.h = largeur_case;

				attributionCouleur(plateau.tab[i][j], &case_pleine.background_color, &case_pleine.text_color, darkmode);

				case_pleine.withText = true;

				sprintf(case_pleine.text, "%d", plateau.tab[i][j]);

				if ((largeur_case / strlen(case_pleine.text)) < largeur_case / 3)
					case_pleine.text_size = largeur_case / (strlen(case_pleine.text));
				else
					case_pleine.text_size = largeur_case / 3;

				SHP_PrintSprite(case_pleine, renderer);
			}
		}
	}
}

/* -------- Fonctions d'animation -------- */

// Fonctions de l'animation de déplacement

// Fonctions de la liste de l'animation de déplacements

/**
* \fn animation_2048 anim_detruire_element(animation_2048 li)
* \brief Destruction du premier élément d'une liste d'animation
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param li liste d'animation
* \return NULL dans tous les cas
*/
animation_2048 anim_detruire_element(animation_2048 li)
{
	// Si la liste est déjà vide ont retourne une liste vide
	if (li == NULL)
	{
		return NULL;
	}
	/* Si cela correpond au dernier */
	if (li->next == NULL)
	{
		free(li);
		li = NULL;
		return NULL;
	}
	/* On récupère l'élément suivant pour le définir comme la liste et on libère le premier*/
	animation_list_2048 *element;
	element = malloc(sizeof(*element));
	element = li->next;
	free(li);
	return element;
}

/**
* \fn void anim_detruire_list(animation_2048 *li)
* \brief Destruction de toute une liste d'animation
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param li liste d'animation
* \return rien dans tous les cas
*/
void anim_detruire_list(animation_2048 *li)
{
	while (*li != NULL)
	{
		*li = anim_detruire_element(*li);
	}
}

/**
* \fn void anim_rajoute_element(animation_2048 *li, animation_value_2048 valeur)
* \brief Rajout d'un élément dans une liste d'animation
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param li liste d'animation
* \param valeur nouvelle valeur à insérer dans la liste d'animation
* \return rien dans tous les cas
*/
void anim_rajoute_element(animation_2048 *li, animation_value_2048 valeur)
{
	animation_list_2048 *newElement;
	newElement = malloc(sizeof(*newElement));

	if (newElement == NULL)
	{
		printf("Erreur d'allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	newElement->next = *li;
	newElement->value = valeur;

	*li = newElement;
}

/**
* \fn SHP_bool anim_deplacement(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
* \brief affichage d'une animation de déplacement
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau d'un joueur de 2048
* \param li liste d'animation
* \param darkmode couleur d'affichage
* \return false si la liste est vide, vraie sinon
*/
SHP_bool anim_deplacement(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
{
	// Si la fonction n'a pas d'animation a faire elle retourne false sinon elle retourn true
	if (*li == NULL)
	{
		return false;
	}

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	animation_list_2048 *temp = *li;

	while (temp != NULL)
	{
		// On parcours toute la liste et on vérifie que la case doit se déplacer si c'est le case on déplace la case
		SHP_bool egalite_abs = (temp->value.affichage.x >= temp->value.arrive.x - ANIMATION_SPEED) && (temp->value.affichage.x <= temp->value.arrive.x + ANIMATION_SPEED);
		SHP_bool egalite_ord = (temp->value.affichage.y >= temp->value.arrive.y - ANIMATION_SPEED) && (temp->value.affichage.y <= temp->value.arrive.y + ANIMATION_SPEED);

		SHP_bool pas_mouvement = (temp->value.depart.x == temp->value.arrive.x || temp->value.depart.y == temp->value.arrive.y) && (temp->value.depart.x != temp->value.arrive.x || temp->value.depart.y != temp->value.arrive.y);
		if (egalite_abs && egalite_ord && pas_mouvement)
		{
			anim_detruire_list(li);
			return false;
		}
		else
		{
			temp->value.affichage.x += (temp->value.arrive.x - temp->value.depart.x) / ANIMATION_SPEED;
			temp->value.affichage.y += (temp->value.arrive.y - temp->value.depart.y) / ANIMATION_SPEED;

			SHP_Sprite case_pleine;
			case_pleine.background.x = temp->value.affichage.x;
			case_pleine.background.y = temp->value.affichage.y;
			case_pleine.background.w = largeur_case;
			case_pleine.background.h = largeur_case;

			attributionCouleur(temp->value.valeur_case, &case_pleine.background_color, &case_pleine.text_color, darkmode);

			case_pleine.withText = true;

			sprintf(case_pleine.text, "%d", temp->value.valeur_case);

			if ((largeur_case / strlen(case_pleine.text)) < largeur_case / 3)
				case_pleine.text_size = largeur_case / (strlen(case_pleine.text));
			else
				case_pleine.text_size = largeur_case / 3;

			SHP_PrintSprite(case_pleine, renderer);

			temp = temp->next;
		}
	}

	return true;
}

/**
* \fn SHP_bool anim_addition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
* \brief affichage d'une animation d'addition
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau d'un joueur de 2048
* \param li liste d'animation
* \param darkmode couleur d'affichage
* \return false si la liste est vide, vraie sinon
*/
SHP_bool anim_addition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
{
	// Si la fonction n'a pas d'animation a faire elle retourne false sinon elle retourn true
	if (*li == NULL)
	{
		return false;
	}

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case_max = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille * 1.25;
	unsigned int largeur_case_init = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	animation_list_2048 *temp = *li;
	SHP_bool addition = false;
	while (temp != NULL)
	{
		SHP_bool egalite = temp->value.affichage.x >= largeur_case_max;

		if (egalite && temp->value.affichage.x > 0)
		{
			anim_detruire_list(li);
			return false;
		}
		else
		{
			unsigned int largeur_case = largeur_case_init;

			if (temp->value.affichage.x > 0)
			{
				addition = true;
				temp->value.affichage.x += ANIMATION_POP_SPEED;
				largeur_case = temp->value.affichage.x;
			}

			SHP_Sprite case_pleine;
			case_pleine.background.x = temp->value.depart.x - (largeur_case - largeur_case_init) / 2;
			case_pleine.background.y = temp->value.depart.y - (largeur_case - largeur_case_init) / 2;
			case_pleine.background.w = largeur_case;
			case_pleine.background.h = largeur_case;

			attributionCouleur(temp->value.valeur_case, &case_pleine.background_color, &case_pleine.text_color, darkmode);

			case_pleine.withText = true;

			sprintf(case_pleine.text, "%d", temp->value.valeur_case);

			if ((largeur_case / strlen(case_pleine.text)) < largeur_case / 3)
				case_pleine.text_size = largeur_case / (strlen(case_pleine.text));
			else
				case_pleine.text_size = largeur_case / 3;

			SHP_PrintSprite(case_pleine, renderer);

			temp = temp->next;
		}
	}
	if (!addition)
	{
		anim_detruire_list(li);
		return false;
	}
	return true;
}

/**
* \fn SHP_bool anim_apparition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
* \brief affichage d'une animation d'apparition
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau d'un joueur de 2048
* \param li liste d'animation
* \param darkmode couleur d'affichage
* \return false si la liste est vide, vraie sinon
*/
SHP_bool anim_apparition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li, SHP_bool darkmode)
{
	// Si la fonction n'a pas d'animation a faire elle retourne false sinon elle retourn true
	if (*li == NULL)
	{
		return false;
	}

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case_max = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	animation_list_2048 *temp = *li;

	while (temp != NULL)
	{
		SHP_bool egalite = temp->value.affichage.x >= largeur_case_max;
		if (egalite && temp->value.affichage.x >= 0)
		{
			anim_detruire_list(li);
			return false;
		}
		else
		{
			unsigned int largeur_case = largeur_case_max;
			if (temp->value.affichage.x >= 0)
			{
				temp->value.affichage.x += ANIMATION_APP_SPEED;
				largeur_case = temp->value.affichage.x;
			}

			SHP_Sprite case_pleine;
			case_pleine.background.x = temp->value.depart.x + (largeur_case_max - largeur_case) / 2;
			case_pleine.background.y = temp->value.depart.y + (largeur_case_max - largeur_case) / 2;
			case_pleine.background.w = largeur_case;
			case_pleine.background.h = largeur_case;

			attributionCouleur(temp->value.valeur_case, &case_pleine.background_color, &case_pleine.text_color, darkmode);

			case_pleine.withText = true;

			sprintf(case_pleine.text, "%d", temp->value.valeur_case);

			if ((largeur_case / strlen(case_pleine.text)) < largeur_case / 3)
				case_pleine.text_size = largeur_case / (strlen(case_pleine.text));
			else
				case_pleine.text_size = largeur_case / 3;

			SHP_PrintSprite(case_pleine, renderer);

			temp = temp->next;
		}
	}

	return true;
}

/**
* \fn void debug_anim_list(animation_list_2048 *li)
* \brief debugage d'une liste d'animation
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param li liste d'animation
* \return rien dans tous les cas
*/
void debug_anim_list(animation_list_2048 *li)
{
	while (li != NULL)
	{
		printf("tab : %d/%d, affichage : %d/%d, depart : %d/%d, arrivee : %d/%d \n", li->value.depart_int.x, li->value.depart_int.y, li->value.affichage.x, li->value.affichage.y, li->value.depart.x, li->value.depart.y, li->value.arrive.x, li->value.arrive.y);
		li = li->next;
	}
}

/**
* \fn coord_2048 coordTabAcoordAffichage(plateau_2048 plateau, coord_2048 coordEntieres)
* \brief passage de coordonnées d'un tableau au coordonnées d'une fenêtre
* \author Vincent Mastain
* \version 0.1
* \date 1 juin 2020
* \param plateau plateau d'un joueur de 2048
* \param coordEntières coordonnées d'une case d'un tableau
* \return coordonnées x, y dans tous les cas
*/
coord_2048 coordTabAcoordAffichage(plateau_2048 plateau, coord_2048 coordEntieres)
{
	coord_2048 coordAffichage;

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	coordAffichage.x = plateau.x + coordEntieres.y * (largeur_case + largeur_bordure) + largeur_bordure;
	coordAffichage.y = plateau.y + coordEntieres.x * (largeur_case + largeur_bordure) + largeur_bordure;

	return coordAffichage;
}

/**
* \fn void affiche_titre(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du titre dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_titre(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
{

	SHP_Sprite titre;

	titre.withText = true;

	titre.text_size = 60;

	titre.background.x = (fenetre.w - 170) / 2;
	titre.background.y = 10;

	titre.background.w = 170;
	titre.background.h = 70;

	if (darkmode)
	{
		titre.text_color.r = 158;
		titre.text_color.g = 180;
		titre.text_color.b = 187;

		titre.background_color.r = 5;
		titre.background_color.g = 7;
		titre.background_color.b = 26;
	}
	else
	{
		titre.text_color.r = 97;
		titre.text_color.g = 75;
		titre.text_color.b = 68;

		titre.background_color.r = 250;
		titre.background_color.g = 248;
		titre.background_color.b = 239;
	}

	strcpy(titre.text, "2048");
	SHP_PrintSprite(titre, renderer);

	return;
}

/**
* \fn void affiche_solo(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton solo dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{
	SHP_Sprite solo;

	solo.withText = true;

	solo.text_size = 20;

	solo.background.x = (fenetre.w - 140) / 2;
	solo.background.y = 160;

	solo.background.w = 140;
	solo.background.h = 50;

	if (darkmode)
	{
		solo.text_color.r = 17;
		solo.text_color.g = 27;
		solo.text_color.b = 37;

		if (coord_curseur.x >= solo.background.x && coord_curseur.x <= solo.background.x + solo.background.w && coord_curseur.y >= solo.background.y && coord_curseur.y <= solo.background.y + solo.background.h)
		{
			solo.background_color.r = 48;
			solo.background_color.g = 61;
			solo.background_color.b = 75;
		}

		else
		{

			solo.background_color.r = 68;
			solo.background_color.g = 81;
			solo.background_color.b = 95;
		}
	}
	else
	{
		solo.text_color.r = 238;
		solo.text_color.g = 228;
		solo.text_color.b = 218;

		if (coord_curseur.x >= solo.background.x && coord_curseur.x <= solo.background.x + solo.background.w && coord_curseur.y >= solo.background.y && coord_curseur.y <= solo.background.y + solo.background.h)
		{
			solo.background_color.r = 207;
			solo.background_color.g = 194;
			solo.background_color.b = 180;
		}

		else
		{

			solo.background_color.r = 187;
			solo.background_color.g = 174;
			solo.background_color.b = 160;
		}
	}

	strcpy(solo.text, "SOLO");

	SHP_PrintSprite(solo, renderer);

	return;
}

/**
* \fn void affiche_vs(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton vs dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_curseur coordonnées de la souris sans clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_vs(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{
	SHP_Sprite vs;

	vs.withText = true;

	vs.text_size = 20;

	vs.background.x = (fenetre.w - 140) / 2;
	vs.background.y = 230;

	vs.background.w = 140;
	vs.background.h = 50;

	if (darkmode)
	{
		vs.text_color.r = 17;
		vs.text_color.g = 27;
		vs.text_color.b = 37;

		if (coord_curseur.x >= vs.background.x && coord_curseur.x <= vs.background.x + vs.background.w && coord_curseur.y >= vs.background.y && coord_curseur.y <= vs.background.y + vs.background.h)
		{
			vs.background_color.r = 48;
			vs.background_color.g = 61;
			vs.background_color.b = 75;
		}

		else
		{

			vs.background_color.r = 68;
			vs.background_color.g = 81;
			vs.background_color.b = 95;
		}
	}
	else
	{
		vs.text_color.r = 238;
		vs.text_color.g = 228;
		vs.text_color.b = 218;

		if (coord_curseur.x >= vs.background.x && coord_curseur.x <= vs.background.x + vs.background.w && coord_curseur.y >= vs.background.y && coord_curseur.y <= vs.background.y + vs.background.h)
		{
			vs.background_color.r = 207;
			vs.background_color.g = 194;
			vs.background_color.b = 180;
		}

		else
		{

			vs.background_color.r = 187;
			vs.background_color.g = 174;
			vs.background_color.b = 160;
		}
	}

	strcpy(vs.text, "1 VS 1");

	SHP_PrintSprite(vs, renderer);

	return;
}

/**
* \fn void affiche_ia(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton ia dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_curseur coordonnées de la souris sans clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_ia(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{

	SHP_Sprite ia;

	ia.withText = true;

	ia.text_size = 20;

	ia.background.x = (fenetre.w - 140) / 2;
	ia.background.y = 300;

	ia.background.w = 140;
	ia.background.h = 50;

	if (darkmode)
	{
		ia.text_color.r = 17;
		ia.text_color.g = 27;
		ia.text_color.b = 37;

		if (coord_curseur.x >= ia.background.x && coord_curseur.x <= ia.background.x + ia.background.w && coord_curseur.y >= ia.background.y && coord_curseur.y <= ia.background.y + ia.background.h)
		{
			ia.background_color.r = 48;
			ia.background_color.g = 61;
			ia.background_color.b = 75;
		}

		else
		{

			ia.background_color.r = 68;
			ia.background_color.g = 81;
			ia.background_color.b = 95;
		}
	}
	else
	{
		ia.text_color.r = 238;
		ia.text_color.g = 228;
		ia.text_color.b = 218;

		if (coord_curseur.x >= ia.background.x && coord_curseur.x <= ia.background.x + ia.background.w && coord_curseur.y >= ia.background.y && coord_curseur.y <= ia.background.y + ia.background.h)
		{
			ia.background_color.r = 207;
			ia.background_color.g = 194;
			ia.background_color.b = 180;
		}

		else
		{

			ia.background_color.r = 187;
			ia.background_color.g = 174;
			ia.background_color.b = 160;
		}
	}

	strcpy(ia.text, "IA");

	SHP_PrintSprite(ia, renderer);

	return;
}

/**
* \fn void affiche_continuer(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton continuer dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_curseur coordonnées de la souris sans clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_continuer(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{

	SHP_Sprite continuer;

	continuer.withText = true;

	continuer.text_size = 20;

	continuer.background.x = (fenetre.w - 140) / 2;
	continuer.background.y = 90;

	continuer.background.w = 140;
	continuer.background.h = 50;

	if (darkmode)
	{
		continuer.text_color.r = 17;
		continuer.text_color.g = 27;
		continuer.text_color.b = 37;

		if (coord_curseur.x >= continuer.background.x && coord_curseur.x <= continuer.background.x + continuer.background.w && coord_curseur.y >= continuer.background.y && coord_curseur.y <= continuer.background.y + continuer.background.h)
		{
			continuer.background_color.r = 48;
			continuer.background_color.g = 61;
			continuer.background_color.b = 75;
		}

		else
		{

			continuer.background_color.r = 68;
			continuer.background_color.g = 81;
			continuer.background_color.b = 95;
		}
	}
	else
	{
		continuer.text_color.r = 238;
		continuer.text_color.g = 228;
		continuer.text_color.b = 218;

		if (coord_curseur.x >= continuer.background.x && coord_curseur.x <= continuer.background.x + continuer.background.w && coord_curseur.y >= continuer.background.y && coord_curseur.y <= continuer.background.y + continuer.background.h)
		{
			continuer.background_color.r = 207;
			continuer.background_color.g = 194;
			continuer.background_color.b = 180;
		}

		else
		{

			continuer.background_color.r = 187;
			continuer.background_color.g = 174;
			continuer.background_color.b = 160;
		}
	}

	strcpy(continuer.text, "CONTINUER");

	SHP_PrintSprite(continuer, renderer);

	return;
}

/**
* \fn void affiche_quitter(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton quitter dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_curseur coordonnées de la souris sans clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void affiche_quitter(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{

	SHP_Sprite quitter;

	quitter.withText = true;

	quitter.text_size = 20;

	quitter.background.x = (fenetre.w - 140) / 2;
	quitter.background.y = 440;

	quitter.background.w = 140;
	quitter.background.h = 50;

	if (darkmode)
	{
		quitter.text_color.r = 17;
		quitter.text_color.g = 27;
		quitter.text_color.b = 37;

		if (coord_curseur.x >= quitter.background.x && coord_curseur.x <= quitter.background.x + quitter.background.w && coord_curseur.y >= quitter.background.y && coord_curseur.y <= quitter.background.y + quitter.background.h)
		{
			quitter.background_color.r = 48;
			quitter.background_color.g = 61;
			quitter.background_color.b = 75;
		}

		else
		{

			quitter.background_color.r = 68;
			quitter.background_color.g = 81;
			quitter.background_color.b = 95;
		}
	}
	else
	{
		quitter.text_color.r = 238;
		quitter.text_color.g = 228;
		quitter.text_color.b = 218;

		if (coord_curseur.x >= quitter.background.x && coord_curseur.x <= quitter.background.x + quitter.background.w && coord_curseur.y >= quitter.background.y && coord_curseur.y <= quitter.background.y + quitter.background.h)
		{
			quitter.background_color.r = 207;
			quitter.background_color.g = 194;
			quitter.background_color.b = 180;
		}

		else
		{

			quitter.background_color.r = 187;
			quitter.background_color.g = 174;
			quitter.background_color.b = 160;
		}
	}

	strcpy(quitter.text, "QUITTER");

	SHP_PrintSprite(quitter, renderer);

	return;
}

/**
* \fn void arcade(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief affichage du bouton arcade dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_curseur coordonnées de la souris sans clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void arcade(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, SHP_bool darkmode)
{

	SHP_Sprite arcade;

	arcade.withText = true;

	arcade.text_size = 20;

	arcade.background.x = (fenetre.w - 140) / 2;
	arcade.background.y = 370;

	arcade.background.w = 140;
	arcade.background.h = 50;

	if (darkmode)
	{
		arcade.text_color.r = 17;
		arcade.text_color.g = 27;
		arcade.text_color.b = 37;

		if (coord_curseur.x >= arcade.background.x && coord_curseur.x <= arcade.background.x + arcade.background.w && coord_curseur.y >= arcade.background.y && coord_curseur.y <= arcade.background.y + arcade.background.h)
		{
			arcade.background_color.r = 48;
			arcade.background_color.g = 61;
			arcade.background_color.b = 75;
		}

		else
		{

			arcade.background_color.r = 68;
			arcade.background_color.g = 81;
			arcade.background_color.b = 95;
		}
	}
	else
	{
		arcade.text_color.r = 238;
		arcade.text_color.g = 228;
		arcade.text_color.b = 218;

		if (coord_curseur.x >= arcade.background.x && coord_curseur.x <= arcade.background.x + arcade.background.w && coord_curseur.y >= arcade.background.y && coord_curseur.y <= arcade.background.y + arcade.background.h)
		{
			arcade.background_color.r = 207;
			arcade.background_color.g = 194;
			arcade.background_color.b = 180;
		}

		else
		{

			arcade.background_color.r = 187;
			arcade.background_color.g = 174;
			arcade.background_color.b = 160;
		}
	}

	strcpy(arcade.text, "ARCADE");

	SHP_PrintSprite(arcade, renderer);

	return;
}

/**
* \fn void mode1(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du selecteur 4X4 dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param f taille déjà sélectionnée
* \param coord_clic coordonnées du clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void mode1(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
{

	SHP_Sprite mode1;

	mode1.withText = true;

	mode1.text_size = 20;

	mode1.background.x = (fenetre.w - 60) / 4;
	mode1.background.y = 520;

	mode1.background.w = 60;
	mode1.background.h = 60;

	if (darkmode)
	{
		mode1.text_color.r = 17;
		mode1.text_color.g = 27;
		mode1.text_color.b = 37;

		mode1.background_color.r = 68;
		mode1.background_color.g = 81;
		mode1.background_color.b = 95;
	}
	else
	{
		mode1.text_color.r = 238;
		mode1.text_color.g = 228;
		mode1.text_color.b = 218;

		mode1.background_color.r = 187;
		mode1.background_color.g = 174;
		mode1.background_color.b = 160;
	}

	if (coord_clic.x >= (fenetre.w - 60) / 4 && coord_clic.x <= (fenetre.w - 60) / 4 + 60 && coord_clic.y >= 520 && coord_clic.y <= 520 + 60)
	{
		*f = 4;
	}

	if (*f == 4)
	{
		if (darkmode)
		{
			mode1.background_color.r = 108;
			mode1.background_color.g = 121;
			mode1.background_color.b = 135;
		}
		else
		{
			mode1.background_color.r = 147;
			mode1.background_color.g = 134;
			mode1.background_color.b = 120;
		}
	}

	strcpy(mode1.text, "4X4");

	SHP_PrintSprite(mode1, renderer);
}

/**
* \fn void mode2(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du selecteur 8X8 dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param f taille déjà sélectionnée
* \param coord_clic coordonnées du clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void mode2(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
{
	SHP_Sprite mode2;

	mode2.withText = true;

	mode2.text_size = 20;

	mode2.background.x = (fenetre.w - 60) / 2;
	mode2.background.y = 520;

	mode2.background.w = 60;
	mode2.background.h = 60;

	if (darkmode)
	{
		mode2.text_color.r = 17;
		mode2.text_color.g = 27;
		mode2.text_color.b = 37;

		mode2.background_color.r = 68;
		mode2.background_color.g = 81;
		mode2.background_color.b = 95;
	}
	else
	{
		mode2.text_color.r = 238;
		mode2.text_color.g = 228;
		mode2.text_color.b = 218;

		mode2.background_color.r = 187;
		mode2.background_color.g = 174;
		mode2.background_color.b = 160;
	}

	if (coord_clic.x >= (fenetre.w - 60) / 2 && coord_clic.x <= (fenetre.w - 60) / 2 + 50 && coord_clic.y >= 520 && coord_clic.y <= 520 + 60)
	{
		*f = 8;
	}

	if (*f == 8)
	{
		if (darkmode)
		{
			mode2.background_color.r = 108;
			mode2.background_color.g = 121;
			mode2.background_color.b = 135;
		}
		else
		{
			mode2.background_color.r = 147;
			mode2.background_color.g = 134;
			mode2.background_color.b = 120;
		}
	}

	strcpy(mode2.text, "8X8");

	SHP_PrintSprite(mode2, renderer);
}

/**
* \fn void mode3(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du selecteur 15X15 dans le menu
* \author Ahmed Trabelsi
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param f taille déjà sélectionnée
* \param coord_clic coordonnées du clique
* \param darkmode couleur d'affichage 
* \return rien dans tous les cas
*/
void mode3(SDL_Renderer *renderer, SDL_Rect fenetre, int *f, coord_2048 coord_clic, SHP_bool darkmode)
{

	SHP_Sprite mode3;

	mode3.withText = true;

	mode3.text_size = 20;

	mode3.background.x = (3 * (fenetre.w - 60) / 4);
	mode3.background.y = 520;

	mode3.background.w = 60;
	mode3.background.h = 60;

	if (darkmode)
	{
		mode3.text_color.r = 17;
		mode3.text_color.g = 27;
		mode3.text_color.b = 37;

		mode3.background_color.r = 68;
		mode3.background_color.g = 81;
		mode3.background_color.b = 95;
	}
	else
	{
		mode3.text_color.r = 238;
		mode3.text_color.g = 228;
		mode3.text_color.b = 218;

		mode3.background_color.r = 187;
		mode3.background_color.g = 174;
		mode3.background_color.b = 160;
	}

	if (coord_clic.x >= ((3 * (fenetre.w - 60)) / 4) && coord_clic.x <= ((3 * (fenetre.w - 60) / 4)) + 60 && coord_clic.y >= 520 && coord_clic.y <= 520 + 60)
	{
		*f = 15;
	}

	if (*f == 15)
	{
		if (darkmode)
		{
			mode3.background_color.r = 108;
			mode3.background_color.g = 121;
			mode3.background_color.b = 135;
		}
		else
		{
			mode3.background_color.r = 147;
			mode3.background_color.g = 134;
			mode3.background_color.b = 120;
		}
	}

	strcpy(mode3.text, "15X15");

	SHP_PrintSprite(mode3, renderer);
}

/**
* \fn position_utilisateur quitter(SDL_Renderer *renderer, SDL_Rect fenetre, plateau_2048 plateau1, plateau_2048 plateau2, position_utilisateur position, partie_2048 partie, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du bouton quitter en jeu
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param plateau1 plateau du joueur 1
* \param plateau2 plateau du joueur 2
* \param position mode que l'utilisateur a décidé de quitter
* \param partie variable de gestion d'une partie
* \param joueur1 variable du joueur 1 en mode arcade (bonus)
* \param joueur2 variable du joueur 2 en mode arcade (bonus)
* \param coord_clic coordonnées du clique
* \param coord_curseur coordonnées du curseur
* \param darkmode couleur d'affichage
* \return menu_principal dans tous les cas
* Affichage + gestion du clique sur le bouton quitter
* Le clique entraine une libération de tous les tableaux et un retour au menu principal
*/
position_utilisateur quitter(SDL_Renderer *renderer, SDL_Rect fenetre, plateau_2048 plateau1, plateau_2048 plateau2, position_utilisateur position, partie_2048 partie, joueur_arcade_2048 joueur1, joueur_arcade_2048 joueur2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
{
	SHP_Sprite bouton_quitter;
	bouton_quitter.background.x = (fenetre.w - 170) / 2;
	bouton_quitter.background.y = fenetre.h - 55;
	bouton_quitter.background.w = 170;
	bouton_quitter.background.h = 50;

	bouton_quitter.withText = true;

	if (darkmode)
	{
		if (coord_curseur.x >= bouton_quitter.background.x && coord_curseur.x <= bouton_quitter.background.x + bouton_quitter.background.w && coord_curseur.y >= bouton_quitter.background.y && coord_curseur.y <= bouton_quitter.background.y + bouton_quitter.background.h)
		{
			bouton_quitter.background_color.r = 48;
			bouton_quitter.background_color.g = 61;
			bouton_quitter.background_color.b = 75;
		}
		else
		{
			bouton_quitter.background_color.r = 68;
			bouton_quitter.background_color.g = 81;
			bouton_quitter.background_color.b = 95;
		}

		bouton_quitter.text_color.r = 17;
		bouton_quitter.text_color.g = 27;
		bouton_quitter.text_color.b = 37;
	}
	else
	{
		if (coord_curseur.x >= bouton_quitter.background.x && coord_curseur.x <= bouton_quitter.background.x + bouton_quitter.background.w && coord_curseur.y >= bouton_quitter.background.y && coord_curseur.y <= bouton_quitter.background.y + bouton_quitter.background.h)
		{
			bouton_quitter.background_color.r = 207;
			bouton_quitter.background_color.g = 194;
			bouton_quitter.background_color.b = 180;
		}
		else
		{
			bouton_quitter.background_color.r = 187;
			bouton_quitter.background_color.g = 174;
			bouton_quitter.background_color.b = 160;
		}

		bouton_quitter.text_color.r = 238;
		bouton_quitter.text_color.g = 228;
		bouton_quitter.text_color.b = 218;
	}

	bouton_quitter.text_size = 20;
	strcpy(bouton_quitter.text, "QUITTER");

	SHP_PrintSprite(bouton_quitter, renderer);

	if (coord_clic.x >= bouton_quitter.background.x && coord_clic.x <= bouton_quitter.background.x + bouton_quitter.background.w && coord_clic.y >= bouton_quitter.background.y && coord_clic.y <= bouton_quitter.background.y + bouton_quitter.background.h)
	{
		sauvegarde(plateau1, plateau2, partie, position, joueur1, joueur2);
		libererTab(plateau1.tab, plateau1.taille);
		if (position == deuxJoueur || position == IA || position == deuxJoueurArcadeMode)
			libererTab(plateau2.tab, plateau2.taille);
		position = menu_principal;
	}

	return position;
}

/**
* \fn SHP_bool continuer_jeu_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du bouton continuer lorsque le joueur atteind 2048 en solo
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param coord_clic coordonnées du clique
* \param coord_curseur coordonnées du curseur
* \param darkmode couleur d'affichage
* \return true si l'utilisateur veut continuer, false sinon
*/
SHP_bool continuer_jeu_solo(SDL_Renderer *renderer, SDL_Rect fenetre, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
{
	SHP_Sprite fin_2048;
	fin_2048.background.x = (fenetre.w - 300) / 2;
	fin_2048.background.y = (fenetre.h - 75) / 2;
	fin_2048.background.w = 300;
	fin_2048.background.h = 75;

	fin_2048.withText = true;

	if (darkmode)
	{
		fin_2048.background_color.r = 68;
		fin_2048.background_color.g = 81;
		fin_2048.background_color.b = 95;

		fin_2048.text_color.r = 17;
		fin_2048.text_color.g = 27;
		fin_2048.text_color.b = 37;
	}
	else
	{
		fin_2048.background_color.r = 187;
		fin_2048.background_color.g = 174;
		fin_2048.background_color.b = 160;

		fin_2048.text_color.r = 238;
		fin_2048.text_color.g = 228;
		fin_2048.text_color.b = 218;
	}

	fin_2048.text_size = 70;
	strcpy(fin_2048.text, "  2048 !");

	SHP_PrintSprite(fin_2048, renderer);

	SHP_Sprite bouton_continuer;
	bouton_continuer.background.x = (fenetre.w - 170) / 2;
	bouton_continuer.background.y = fenetre.h - 170;
	bouton_continuer.background.w = 170;
	bouton_continuer.background.h = 50;

	bouton_continuer.withText = true;

	if (darkmode)
	{
		if (coord_curseur.x >= bouton_continuer.background.x && coord_curseur.x <= bouton_continuer.background.x + bouton_continuer.background.w && coord_curseur.y >= bouton_continuer.background.y && coord_curseur.y <= bouton_continuer.background.y + bouton_continuer.background.h)
		{
			bouton_continuer.background_color.r = 48;
			bouton_continuer.background_color.g = 61;
			bouton_continuer.background_color.b = 75;
		}
		else
		{
			bouton_continuer.background_color.r = 68;
			bouton_continuer.background_color.g = 81;
			bouton_continuer.background_color.b = 95;
		}

		bouton_continuer.text_color.r = 17;
		bouton_continuer.text_color.g = 27;
		bouton_continuer.text_color.b = 37;
	}
	else
	{
		if (coord_curseur.x >= bouton_continuer.background.x && coord_curseur.x <= bouton_continuer.background.x + bouton_continuer.background.w && coord_curseur.y >= bouton_continuer.background.y && coord_curseur.y <= bouton_continuer.background.y + bouton_continuer.background.h)
		{
			bouton_continuer.background_color.r = 207;
			bouton_continuer.background_color.g = 194;
			bouton_continuer.background_color.b = 180;
		}
		else
		{
			bouton_continuer.background_color.r = 187;
			bouton_continuer.background_color.g = 174;
			bouton_continuer.background_color.b = 160;
		}

		bouton_continuer.text_color.r = 238;
		bouton_continuer.text_color.g = 228;
		bouton_continuer.text_color.b = 218;
	}

	bouton_continuer.text_size = 20;
	strcpy(bouton_continuer.text, "CONTINUER");

	SHP_PrintSprite(bouton_continuer, renderer);

	if (coord_clic.x >= bouton_continuer.background.x && coord_clic.x <= bouton_continuer.background.x + bouton_continuer.background.w && coord_clic.y >= bouton_continuer.background.y && coord_clic.y <= bouton_continuer.background.y + bouton_continuer.background.h)
	{
		return true;
	}

	return false;
}

/**
* \fn SHP_bool atteindre_2048(plateau_2048 plateau)
* \brief test de l'arrivée à 2048 d'un joueur
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param plateau plateau du joueur
* \return true si l'utilisateur a atteind 2048, false sinon
*/
SHP_bool atteindre_2048(plateau_2048 plateau)
{
	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			if (plateau.tab[i][j] == 2048)
				return true;
		}
	}
	return false;
}

/**
* \fn void recommencer(SDL_Renderer *renderer, SDL_Rect fenetre, position_utilisateur position, partie_2048 *partie, plateau_2048 *plateau, plateau_2048 *plateau2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode) void recommencer(SDL_Renderer *renderer, SDL_Rect fenetre, position_utilisateur position, partie_2048 *partie, plateau_2048 *plateau, plateau_2048 *plateau2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
* \brief affichage du bouton recommencer en jeu
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer d'une fenêtre SDL
* \param fenetre taille de la fenêtre SDL
* \param plateau1 plateau du joueur 1
* \param plateau2 plateau du joueur 2
* \param position mode que l'utilisateur a décidé de quitter
* \param partie variable de gestion d'une partie
* \param coord_clic coordonnées du clique
* \param coord_curseur coordonnées du curseur
* \param darkmode couleur d'affichage
* \return menu_principal dans tous les cas
* Affichage + gestion du clique sur le bouton recommencer
* Le clique réinitialise toutes variables et tableaux
*/
void recommencer(SDL_Renderer *renderer, SDL_Rect fenetre, position_utilisateur position, partie_2048 *partie, plateau_2048 *plateau, plateau_2048 *plateau2, coord_2048 coord_curseur, coord_2048 coord_clic, SHP_bool darkmode)
{
	SHP_Sprite bouton_recommencer;
	bouton_recommencer.background.x = (fenetre.w - 170) / 2;
	bouton_recommencer.background.y = fenetre.h - 110;
	bouton_recommencer.background.w = 170;
	bouton_recommencer.background.h = 50;

	bouton_recommencer.withText = true;

	if (darkmode)
	{
		if (coord_curseur.x >= bouton_recommencer.background.x && coord_curseur.x <= bouton_recommencer.background.x + bouton_recommencer.background.w && coord_curseur.y >= bouton_recommencer.background.y && coord_curseur.y <= bouton_recommencer.background.y + bouton_recommencer.background.h)
		{
			bouton_recommencer.background_color.r = 48;
			bouton_recommencer.background_color.g = 61;
			bouton_recommencer.background_color.b = 75;
		}
		else
		{
			bouton_recommencer.background_color.r = 68;
			bouton_recommencer.background_color.g = 81;
			bouton_recommencer.background_color.b = 95;
		}

		bouton_recommencer.text_color.r = 17;
		bouton_recommencer.text_color.g = 27;
		bouton_recommencer.text_color.b = 37;
	}
	else
	{
		if (coord_curseur.x >= bouton_recommencer.background.x && coord_curseur.x <= bouton_recommencer.background.x + bouton_recommencer.background.w && coord_curseur.y >= bouton_recommencer.background.y && coord_curseur.y <= bouton_recommencer.background.y + bouton_recommencer.background.h)
		{
			bouton_recommencer.background_color.r = 207;
			bouton_recommencer.background_color.g = 194;
			bouton_recommencer.background_color.b = 180;
		}
		else
		{
			bouton_recommencer.background_color.r = 187;
			bouton_recommencer.background_color.g = 174;
			bouton_recommencer.background_color.b = 160;
		}

		bouton_recommencer.text_color.r = 238;
		bouton_recommencer.text_color.g = 228;
		bouton_recommencer.text_color.b = 218;
	}

	bouton_recommencer.text_size = 20;
	strcpy(bouton_recommencer.text, "RECOMMENCER");

	SHP_PrintSprite(bouton_recommencer, renderer);

	if (coord_clic.x >= bouton_recommencer.background.x && coord_clic.x <= bouton_recommencer.background.x + bouton_recommencer.background.w && coord_clic.y >= bouton_recommencer.background.y && coord_clic.y <= bouton_recommencer.background.y + bouton_recommencer.background.h)
	{
		plateau->score = 0;
		initialisation(*plateau);
		depart(*plateau);

		if (position == deuxJoueur || position == IA || position == deuxJoueurArcadeMode)
		{
			plateau2->score = 0;
			initialisation(*plateau2);
			depart(*plateau2);
		}

		if (position == deuxJoueurArcadeMode)
		{
			partie->chrono = 60;
			partie->palier_max = 2048;
		}

		partie->numero_tour = 1;
		partie->tour = 1;
		partie->continuer_apres_2048 = false;
	}
}

/**
* \fn SHP_bool defaite_unJoueur(plateau_2048 plateau)
* \brief test de la défaite au 2048 d'un joueur
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param plateau plateau du joueur
* \return true si l'utilisateur peut jouer, false sinon
*/
SHP_bool defaite_unJoueur(plateau_2048 plateau)
{
	SHP_bool peut_jouer = false;

	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			if (j + 1 < plateau.taille)
			{
				if (plateau.tab[i][j] == plateau.tab[i][j + 1])
					peut_jouer = true;
			}

			if (i + 1 < plateau.taille)
			{
				if (plateau.tab[i][j] == plateau.tab[i + 1][j])
					peut_jouer = true;
			}

			if (plateau.tab[i][j] == 0)
				peut_jouer = true;
		}
	}

	return peut_jouer;
}

/* ------- Fonctions affichage mode 2 joueurs --------- */
/**
* \fn void afficherTitreJoueur(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2, SHP_bool darkmode)
* \brief Affiche joueur 1 et joueur 2 en partie deux joueurs
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau du joueur 1
* \param plateau2 plateau du joueur 2
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
*/
void afficherTitreJoueur(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2, SHP_bool darkmode)
{
	SHP_Sprite tour_joueur1;

	tour_joueur1.background.x = plateau.x + (plateau.largeur - 170) / 2;
	tour_joueur1.background.y = plateau.y + plateau.largeur + 25;
	tour_joueur1.background.w = 170;
	tour_joueur1.background.h = 50;

	tour_joueur1.withText = true;

	if (darkmode)
	{
		tour_joueur1.background_color.r = 68;
		tour_joueur1.background_color.g = 81;
		tour_joueur1.background_color.b = 95;

		tour_joueur1.text_color.r = 0;
		tour_joueur1.text_color.g = 0;
		tour_joueur1.text_color.b = 0;
	}
	else
	{
		tour_joueur1.background_color.r = 187;
		tour_joueur1.background_color.g = 174;
		tour_joueur1.background_color.b = 160;

		tour_joueur1.text_color.r = 255;
		tour_joueur1.text_color.g = 255;
		tour_joueur1.text_color.b = 255;
	}

	tour_joueur1.text_size = 20;

	strcpy(tour_joueur1.text, "JOUEUR 1");

	SHP_PrintSprite(tour_joueur1, renderer);

	SHP_Sprite tour_joueur2;

	tour_joueur2.background.x = plateau2.x + (plateau2.largeur - 170) / 2;
	tour_joueur2.background.y = plateau2.y + plateau2.largeur + 25;
	tour_joueur2.background.w = 170;
	tour_joueur2.background.h = 50;

	tour_joueur2.withText = true;

	if (darkmode)
	{
		tour_joueur2.background_color.r = 68;
		tour_joueur2.background_color.g = 81;
		tour_joueur2.background_color.b = 95;

		tour_joueur2.text_color.r = 0;
		tour_joueur2.text_color.g = 0;
		tour_joueur2.text_color.b = 0;
	}
	else
	{
		tour_joueur2.background_color.r = 187;
		tour_joueur2.background_color.g = 174;
		tour_joueur2.background_color.b = 160;

		tour_joueur2.text_color.r = 255;
		tour_joueur2.text_color.g = 255;
		tour_joueur2.text_color.b = 255;
	}

	tour_joueur2.text_size = 20;

	strcpy(tour_joueur2.text, "JOUEUR 2");

	SHP_PrintSprite(tour_joueur2, renderer);
}

/**
* \fn void afficher_Victoire(SDL_Renderer *renderer, SDL_Rect fenetre, int joueur_gagnant, SHP_bool darkmode)
* \brief Affiche victoire lorsqu'elle a lieu
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre fenêtre de la SDL
* \param joueur_gagnant joueurs qui a gagné
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
*/
void afficher_Victoire(SDL_Renderer *renderer, SDL_Rect fenetre, int joueur_gagnant, SHP_bool darkmode)
{
	SHP_Sprite victoire;
	victoire.background.x = (fenetre.w - 310) / 2;
	victoire.background.y = (fenetre.h - 60) / 2;
	victoire.background.w = 310;
	victoire.background.h = 60;

	victoire.withText = true;

	if (darkmode)
	{
		victoire.background_color.r = 68;
		victoire.background_color.g = 81;
		victoire.background_color.b = 95;

		victoire.text_color.r = 17;
		victoire.text_color.g = 27;
		victoire.text_color.b = 37;
	}
	else
	{
		victoire.background_color.r = 187;
		victoire.background_color.g = 174;
		victoire.background_color.b = 160;

		victoire.text_color.r = 238;
		victoire.text_color.g = 228;
		victoire.text_color.b = 218;
	}

	victoire.text_size = 30;
	sprintf(victoire.text, "VICTOIRE JOUEUR %d", joueur_gagnant);

	SHP_PrintSprite(victoire, renderer);
}

/**
* \fn void afficher_Egalite(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
* \brief Affiche égalité lorsqu'elle a lieu
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre fenêtre de la SDL
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
*/
void afficher_Egalite(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool darkmode)
{
	SHP_Sprite egalite;
	egalite.background.x = (fenetre.w - 200) / 2;
	egalite.background.y = (fenetre.h - 60) / 2;
	egalite.background.w = 200;
	egalite.background.h = 60;

	egalite.withText = true;

	if (darkmode)
	{

		egalite.background_color.r = 68;
		egalite.background_color.g = 81;
		egalite.background_color.b = 95;

		egalite.text_color.r = 17;
		egalite.text_color.g = 27;
		egalite.text_color.b = 37;
	}
	else
	{

		egalite.background_color.r = 187;
		egalite.background_color.g = 174;
		egalite.background_color.b = 160;

		egalite.text_color.r = 238;
		egalite.text_color.g = 228;
		egalite.text_color.b = 218;
	}

	egalite.text_size = 30;
	strcpy(egalite.text, "EGALITE");

	SHP_PrintSprite(egalite, renderer);
}

/**
* \fn void afficher_bonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur, SHP_bool darkmode)
* \brief Affiche des bonus que possède un joueur
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param plateau plateau du joueur
* \param joueur bonus que possède le joueur
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
*/
void afficher_bonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur, SHP_bool darkmode)
{
	switch (joueur.bonus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "2 -> 8", darkmode);

		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rangement", darkmode);

		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rapidité", darkmode);

		break;

	default:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rien", darkmode);

		break;
	}

	switch (joueur.malus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Détruire", darkmode);
		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Mélanger", darkmode);
		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Inverser", darkmode);
		break;
	default:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Rien", darkmode);
		break;
	}
}

/**
* \fn void afficher_info_text(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], char valeur[100], SHP_bool darkmode)
* \brief Affiche d'une information sous forme de texte
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre fenêtre de la SDL
* \param x position en abscisse
* \param y position en ordonnée
* \param titre titre de l'information
* \param valeur valeur de l'information
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
* Affichage un encadrée avec un titre plus une information dessous
*/
void afficher_info_text(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], char valeur[100], SHP_bool darkmode)
{
	SHP_Sprite info_titre;
	info_titre.background.x = x;
	info_titre.background.y = y;
	info_titre.background.w = 100;
	info_titre.background.h = 30;

	info_titre.withText = true;

	if (darkmode)
	{

		info_titre.background_color.r = 68;
		info_titre.background_color.g = 81;
		info_titre.background_color.b = 95;

		info_titre.text_color.r = 17;
		info_titre.text_color.g = 27;
		info_titre.text_color.b = 37;
	}
	else
	{

		info_titre.background_color.r = 187;
		info_titre.background_color.g = 174;
		info_titre.background_color.b = 160;

		info_titre.text_color.r = 238;
		info_titre.text_color.g = 228;
		info_titre.text_color.b = 218;
	}

	info_titre.text_size = 14;

	strcpy(info_titre.text, titre);

	SHP_Sprite info_valeur;

	info_valeur.background.x = info_titre.background.x;
	info_valeur.background.y = info_titre.background.y + 30;
	info_valeur.background.w = 100;
	info_valeur.background.h = 40;

	if (x == CENTER)
		info_titre.background.x = (fenetre->w - info_titre.background.w) / 2;

	if (y == CENTER)
		info_titre.background.y = (fenetre->h - info_titre.background.h) / 2;

	info_valeur.withText = true;

	if (darkmode)
	{

		info_valeur.background_color.r = 68;
		info_valeur.background_color.g = 81;
		info_valeur.background_color.b = 95;

		info_valeur.text_color.r = 0;
		info_valeur.text_color.g = 0;
		info_valeur.text_color.b = 0;
	}
	else
	{

		info_valeur.background_color.r = 187;
		info_valeur.background_color.g = 174;
		info_valeur.background_color.b = 160;

		info_valeur.text_color.r = 255;
		info_valeur.text_color.g = 255;
		info_valeur.text_color.b = 255;
	}

	info_valeur.text_size = 14;

	strcpy(info_valeur.text, valeur);

	SHP_PrintSprite(info_titre, renderer);
	SHP_PrintSprite(info_valeur, renderer);
}

/**
* \fn void afficher_info_int(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], int valeur, SHP_bool darkmode)
* \brief Affiche d'une information sous forme d'entier
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre fenêtre de la SDL
* \param x position en abscisse
* \param y position en ordonnée
* \param titre titre de l'information
* \param valeur valeur de l'information
* \param darkmode couleur d'affichage
* \return rien dans tous les cas
* Affichage un encadrée avec un titre plus une information dessous
*/
void afficher_info_int(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], int valeur, SHP_bool darkmode)
{
	SHP_Sprite info_titre;
	info_titre.background.x = x;
	info_titre.background.y = y;
	info_titre.background.w = 100;
	info_titre.background.h = 30;

	if (x == CENTER)
		info_titre.background.x = (fenetre->w - info_titre.background.w) / 2;

	if (y == CENTER)
		info_titre.background.y = (fenetre->h - info_titre.background.h) / 2;

	info_titre.withText = true;

	if (darkmode)
	{
		info_titre.background_color.r = 68;
		info_titre.background_color.g = 81;
		info_titre.background_color.b = 95;

		info_titre.text_color.r = 17;
		info_titre.text_color.g = 27;
		info_titre.text_color.b = 37;
	}
	else
	{
		info_titre.background_color.r = 187;
		info_titre.background_color.g = 174;
		info_titre.background_color.b = 160;

		info_titre.text_color.r = 238;
		info_titre.text_color.g = 228;
		info_titre.text_color.b = 218;
	}

	info_titre.text_size = 14;

	strcpy(info_titre.text, titre);

	SHP_Sprite info_valeur;

	info_valeur.background.x = info_titre.background.x;
	info_valeur.background.y = info_titre.background.y + 30;
	info_valeur.background.w = 100;
	info_valeur.background.h = 40;

	info_valeur.withText = true;

	if (darkmode)
	{

		info_valeur.background_color.r = 68;
		info_valeur.background_color.g = 81;
		info_valeur.background_color.b = 95;

		info_valeur.text_color.r = 0;
		info_valeur.text_color.g = 0;
		info_valeur.text_color.b = 0;
	}
	else
	{

		info_valeur.background_color.r = 187;
		info_valeur.background_color.g = 174;
		info_valeur.background_color.b = 160;

		info_valeur.text_color.r = 255;
		info_valeur.text_color.g = 255;
		info_valeur.text_color.b = 255;
	}

	info_valeur.text_size = 30;

	sprintf(info_valeur.text, "%d", valeur);
	SHP_PrintSprite(info_titre, renderer);
	SHP_PrintSprite(info_valeur, renderer);
}

/**
* \fn void bouton_darkmode(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool *darkmode, coord_2048 coord_clic)
* \brief Affiche le bouton darkmode dans le menu principale
* \author Vincent Mastain
* \version 0.1
* \date 9 juin 2020
* \param renderer renderer de la fenêtre SDL
* \param fenetre fenêtre de la SDL
* \param darkmode couleur d'affichage
* \param coord_clic coordonnées du clic
* \return rien dans tous les cas
* Affichage et gestion du darkmode
* modifie la valeur de darkmode pour contrôler la couleur des boutons/informations dans le autres fonctions
*/
void bouton_darkmode(SDL_Renderer *renderer, SDL_Rect fenetre, SHP_bool *darkmode, coord_2048 coord_clic)
{
	SHP_Sprite darkmode_bouton;

	darkmode_bouton.background.x = fenetre.w - 110;
	darkmode_bouton.background.y = 20;
	darkmode_bouton.background.w = 100;
	darkmode_bouton.background.h = 40;

	if (*darkmode)
	{
		strcpy(darkmode_bouton.text, "LIGHTMODE");
		darkmode_bouton.background_color.r = 255;
		darkmode_bouton.background_color.g = 255;
		darkmode_bouton.background_color.b = 255;

		darkmode_bouton.text_color.r = 40;
		darkmode_bouton.text_color.g = 40;
		darkmode_bouton.text_color.b = 40;
	}
	else
	{
		strcpy(darkmode_bouton.text, "DARKMODE");

		darkmode_bouton.background_color.r = 40;
		darkmode_bouton.background_color.g = 40;
		darkmode_bouton.background_color.b = 40;

		darkmode_bouton.text_color.r = 255;
		darkmode_bouton.text_color.g = 255;
		darkmode_bouton.text_color.b = 255;
	}

	if (coord_clic.x >= darkmode_bouton.background.x && coord_clic.x <= darkmode_bouton.background.x + darkmode_bouton.background.w && coord_clic.y >= darkmode_bouton.background.y && coord_clic.y <= darkmode_bouton.background.y + darkmode_bouton.background.h)
	{
		*darkmode = !*darkmode;
	}

	darkmode_bouton.withText = true;
	darkmode_bouton.text_size = 15;

	SHP_PrintSprite(darkmode_bouton, renderer);
}