#include "interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

void afficherFond(SDL_Renderer *renderer, SDL_Rect fenetre)
{
	SHP_Sprite background;
	background.background.x = 0;
	background.background.y = 0;
	background.background.h = fenetre.h;
	background.background.w = fenetre.w;

	background.background_color.r = 250;
	background.background_color.g = 248;
	background.background_color.b = 239;

	background.withText = false;

	SHP_PrintSprite(background, renderer);
}

void afficherPlateauVide(SDL_Renderer *renderer, plateau_2048 plateau)
{
	SHP_Sprite plateau_fond;
	plateau_fond.background.x = plateau.x;
	plateau_fond.background.y = plateau.y;
	plateau_fond.background.w = plateau.largeur;
	plateau_fond.background.h = plateau.largeur;

	plateau_fond.background_color.r = 187;
	plateau_fond.background_color.g = 174;
	plateau_fond.background_color.b = 160;

	plateau_fond.withText = false;

	SHP_PrintSprite(plateau_fond, renderer);

	/* Affichage de toutes les cases vides */
	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / 100;
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

			case_vide.background_color.r = 205;
			case_vide.background_color.g = 193;
			case_vide.background_color.b = 180;

			case_vide.withText = false;

			SHP_PrintSprite(case_vide, renderer);
		}
	}
}

void attributionCouleur(int n, SDL_Color *color, SDL_Color *text_color)
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

void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau)
{
	/* Affichage de toutes les cases */
	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / 100;
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

				attributionCouleur(plateau.tab[i][j], &case_pleine.background_color, &case_pleine.text_color);

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

void anim_detruire_list(animation_2048 *li)
{
	while (*li != NULL)
	{
		*li = anim_detruire_element(*li);
	}
}

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

// Fonction permettant d'animer les déplacements avec une liste d'animation
SHP_bool anim_deplacement(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li)
{
	// Si la fonction n'a pas d'animation a faire elle retourne false sinon elle retourn true
	if (*li == NULL)
	{
		return false;
	}

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / 100;
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	animation_list_2048 *temp = *li;
	
	while (temp != NULL)
	{
		SHP_bool egalite_abs = (temp->value.affichage.x >= temp->value.arrive.x - ANIMATION_SPEED) && (temp->value.affichage.x <= temp->value.arrive.x + ANIMATION_SPEED);
		SHP_bool egalite_ord = (temp->value.affichage.y >= temp->value.arrive.y - ANIMATION_SPEED) && (temp->value.affichage.y <= temp->value.arrive.y + ANIMATION_SPEED);

		SHP_bool pas_mouvement = (temp->value.depart.x == temp->value.arrive.x || temp->value.depart.y == temp->value.arrive.y) && (temp->value.depart.x != temp->value.arrive.x || temp->value.depart.y != temp->value.arrive.y);
		if (egalite_abs && egalite_ord && pas_mouvement)
		{
			anim_detruire_list(li);
			break;
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

			attributionCouleur(temp->value.valeur_case, &case_pleine.background_color, &case_pleine.text_color);

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
// Fonction qui permet de debugger la liste d'animation
void debug_anim_list(animation_list_2048 *li)
{
	while (li != NULL)
	{
		printf("tab : %d/%d, affichage : %d/%d, depart : %d/%d, arrivee : %d/%d \n", li->value.depart_int.x, li->value.depart_int.y,li->value.affichage.x, li->value.affichage.y, li->value.depart.x, li->value.depart.y, li->value.arrive.x, li->value.arrive.y);
		li = li->next;
	}
}
// Fonction traduit coord entière de tableau en coordonnées d'affichage
coordInt_2048 coordTabAcoordAffichage(plateau_2048 plateau, coordInt_2048 coordEntieres)
{
	coordInt_2048 coordAffichage;

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / 100;
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	coordAffichage.x = plateau.x + coordEntieres.y * (largeur_case + largeur_bordure) + largeur_bordure;
	coordAffichage.y = plateau.y + coordEntieres.x * (largeur_case + largeur_bordure) + largeur_bordure;

	return coordAffichage;
}