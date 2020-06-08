#include "interface.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

/* Fonction d'affichage du jeu basiques */

// Fonction qui permet d'afficher le fond de la fénêtrd
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
// Fonction qui permet d'afficher un plateau vide
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

			case_vide.background_color.r = 205;
			case_vide.background_color.g = 193;
			case_vide.background_color.b = 180;

			case_vide.withText = false;

			SHP_PrintSprite(case_vide, renderer);
		}
	}
}
// Fonction qui permet d'attribuer des couleurs en fonction d'un nombre
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
// Fonction qui affiche un plateau avec les cases le composants
void afficherPlateauPlein(SDL_Renderer *renderer, plateau_2048 plateau)
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

// Fonction detruit un seul élément de la liste d'animations
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
// Fonction qui détruit toute une liste d'animations
void anim_detruire_list(animation_2048 *li)
{
	while (*li != NULL)
	{
		*li = anim_detruire_element(*li);
	}
}
// Fonction permettant de rajouter un élément à la liste des animations de déplacements
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

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
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
// Fonction permettant d'animer l'addition après déplacement
SHP_bool anim_addition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li)
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
	if (!addition)
	{
		anim_detruire_list(li);
		return false;
	}
	return true;
}
// Fonction qui anime l'apparation de nouvelles cases
SHP_bool anim_apparition(SDL_Renderer *renderer, plateau_2048 plateau, animation_2048 *li)
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
		printf("tab : %d/%d, affichage : %d/%d, depart : %d/%d, arrivee : %d/%d \n", li->value.depart_int.x, li->value.depart_int.y, li->value.affichage.x, li->value.affichage.y, li->value.depart.x, li->value.depart.y, li->value.arrive.x, li->value.arrive.y);
		li = li->next;
	}
}

// Fonction traduit coord entière de tableau en coordonnées d'affichage
coordInt_2048 coordTabAcoordAffichage(plateau_2048 plateau, coordInt_2048 coordEntieres)
{
	coordInt_2048 coordAffichage;

	unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
	unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

	coordAffichage.x = plateau.x + coordEntieres.y * (largeur_case + largeur_bordure) + largeur_bordure;
	coordAffichage.y = plateau.y + coordEntieres.x * (largeur_case + largeur_bordure) + largeur_bordure;

	return coordAffichage;
}

/* ------- Affichage score --------- */
// Toutes les fonctions concernant le score par en fonction d'un plateau à un état donné



// Fonction permettant de recommencer
int recommencer(SDL_Renderer *renderer, plateau_2048 plateau, coord_2048 coord_curseur, coord_2048 coord_clic, int x, int y)
{
	int score = plateau.score;
	SHP_Sprite bouton_recommencer;
	bouton_recommencer.background.x = x;
	bouton_recommencer.background.y = y;
	bouton_recommencer.background.w = 170;
	bouton_recommencer.background.h = 50;

	if (x == CENTER)
		bouton_recommencer.background.x = plateau.x + (plateau.largeur - bouton_recommencer.background.w) / 2;

	if (y == CENTER)
		bouton_recommencer.background.y = plateau.y + (plateau.largeur - bouton_recommencer.background.h) / 2;

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

	bouton_recommencer.withText = true;

	bouton_recommencer.text_color.r = 238;
	bouton_recommencer.text_color.g = 228;
	bouton_recommencer.text_color.b = 218;

	bouton_recommencer.text_size = 20;
	strcpy(bouton_recommencer.text, "RECOMMENCER");

	SHP_PrintSprite(bouton_recommencer, renderer);

	if (coord_clic.x >= bouton_recommencer.background.x && coord_clic.x <= bouton_recommencer.background.x + bouton_recommencer.background.w && coord_clic.y >= bouton_recommencer.background.y && coord_clic.y <= bouton_recommencer.background.y + bouton_recommencer.background.h)
	{
		score = 0;
		initialisation(plateau);
		depart(plateau);
	}

	return score;
}

// Fonction permettant de detecter une défaite
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

void afficherTitreJoueur(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2)
{
	SHP_Sprite tour_joueur1;

	tour_joueur1.background.x = plateau.x + (plateau.largeur - 170) / 2;
	tour_joueur1.background.y = plateau.y + plateau.largeur + 25;
	tour_joueur1.background.w = 170;
	tour_joueur1.background.h = 50;

	tour_joueur1.background_color.r = 187;
	tour_joueur1.background_color.g = 174;
	tour_joueur1.background_color.b = 160;

	tour_joueur1.withText = true;

	tour_joueur1.text_color.r = 255;
	tour_joueur1.text_color.g = 255;
	tour_joueur1.text_color.b = 255;

	tour_joueur1.text_size = 20;

	strcpy(tour_joueur1.text, "JOUEUR 1");

	SHP_PrintSprite(tour_joueur1, renderer);

	SHP_Sprite tour_joueur2;

	tour_joueur2.background.x = plateau2.x + (plateau2.largeur - 170) / 2;
	tour_joueur2.background.y = plateau2.y + plateau2.largeur + 25;
	tour_joueur2.background.w = 170;
	tour_joueur2.background.h = 50;

	tour_joueur2.background_color.r = 187;
	tour_joueur2.background_color.g = 174;
	tour_joueur2.background_color.b = 160;

	tour_joueur2.withText = true;

	tour_joueur2.text_color.r = 255;
	tour_joueur2.text_color.g = 255;
	tour_joueur2.text_color.b = 255;

	tour_joueur2.text_size = 20;

	strcpy(tour_joueur2.text, "JOUEUR 2");

	SHP_PrintSprite(tour_joueur2, renderer);
}

// Fonction permettant de faire recommencer une partie en mode 2 joueurs
void recommencer_deuxJoueurs(SDL_Renderer *renderer, plateau_2048 plateau, plateau_2048 plateau2, int *score, int *score2, coord_2048 coord_curseur, coord_2048 coord_clic, SDL_Rect fenetre, partie_2048 *partie)
{
	SHP_Sprite bouton_recommencer;
	bouton_recommencer.background.x = (fenetre.w - 170) / 2;
	bouton_recommencer.background.y = plateau.y + plateau.largeur + 25;
	bouton_recommencer.background.w = 170;
	bouton_recommencer.background.h = 50;

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

	bouton_recommencer.withText = true;

	bouton_recommencer.text_color.r = 238;
	bouton_recommencer.text_color.g = 228;
	bouton_recommencer.text_color.b = 218;

	bouton_recommencer.text_size = 20;
	strcpy(bouton_recommencer.text, "RECOMMENCER");

	SHP_PrintSprite(bouton_recommencer, renderer);

	if (coord_clic.x >= bouton_recommencer.background.x && coord_clic.x <= bouton_recommencer.background.x + bouton_recommencer.background.w && coord_clic.y >= bouton_recommencer.background.y && coord_clic.y <= bouton_recommencer.background.y + bouton_recommencer.background.h)
	{
		initialisation(plateau);
		depart(plateau);
		initialisation(plateau2);
		depart(plateau2);
		*score = 0;
		*score2 = 0;
		partie->numero_tour = 1;
		partie->tour = 1;
	}
}

void afficher_Victoire(SDL_Renderer *renderer, SDL_Rect fenetre, int joueur_gagnant)
{
	SHP_Sprite victoire;
	victoire.background.x = (fenetre.w - 310) / 2;
	victoire.background.y = (fenetre.h - 60) / 2;
	victoire.background.w = 310;
	victoire.background.h = 60;

	victoire.background_color.r = 187;
	victoire.background_color.g = 174;
	victoire.background_color.b = 160;

	victoire.withText = true;

	victoire.text_color.r = 238;
	victoire.text_color.g = 228;
	victoire.text_color.b = 218;

	victoire.text_size = 30;
	sprintf(victoire.text, "VICTOIRE JOUEUR %d", joueur_gagnant);

	SHP_PrintSprite(victoire, renderer);
}
void afficher_Egalite(SDL_Renderer *renderer, SDL_Rect fenetre)
{
	SHP_Sprite egalite;
	egalite.background.x = (fenetre.w - 200) / 2;
	egalite.background.y = (fenetre.h - 60) / 2;
	egalite.background.w = 200;
	egalite.background.h = 60;

	egalite.background_color.r = 187;
	egalite.background_color.g = 174;
	egalite.background_color.b = 160;

	egalite.withText = true;

	egalite.text_color.r = 238;
	egalite.text_color.g = 228;
	egalite.text_color.b = 218;

	egalite.text_size = 30;
	strcpy(egalite.text, "EGALITE");

	SHP_PrintSprite(egalite, renderer);
}

void afficher_prochainBonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur)
{
	switch (joueur.prochain_bonus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y - 75, "BONUS suiv.", "2 -> 8");
		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y - 75, "BONUS suiv.", "Rangement");
		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y - 75, "BONUS suiv.", "Rapidité");
		break;
	default:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y - 75, "BONUS suiv.", "Rien");
		break;
	}

	switch (joueur.prochain_malus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y - 75, "MALUS suiv.", "Détruire");
		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y - 75, "MALUS suiv.", "Mélanger");
		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y - 75, "MALUS suiv.", "Inverser");
		break;
	default:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y - 75, "MALUS suiv.", "Rien");
		break;
	}
}

void afficher_bonus(SDL_Renderer *renderer, plateau_2048 plateau, joueur_arcade_2048 joueur)
{
	switch (joueur.bonus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "2 -> 8");

		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rangement");

		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rapidité");

		break;

	default:
		afficher_info_text(renderer, NULL, plateau.x, plateau.y + plateau.largeur + 10, "BONUS", "Rien");

		break;
	}

	switch (joueur.malus)
	{
	case 1:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Détruire");
		break;
	case 2:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Mélanger");
		break;
	case 3:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Inverser");
		break;
	default:
		afficher_info_text(renderer, NULL, plateau.x + plateau.largeur - 100, plateau.y + plateau.largeur + 10, "MALUS", "Rien");
		break;
	}
}
void afficher_info_text(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], char valeur[100])
{
	SHP_Sprite info_titre;
	info_titre.background.x = x;
	info_titre.background.y = y;
	info_titre.background.w = 100;
	info_titre.background.h = 30;

	info_titre.background_color.r = 187;
	info_titre.background_color.g = 174;
	info_titre.background_color.b = 160;

	info_titre.withText = true;

	info_titre.text_color.r = 238;
	info_titre.text_color.g = 228;
	info_titre.text_color.b = 218;

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

	info_valeur.background_color.r = 187;
	info_valeur.background_color.g = 174;
	info_valeur.background_color.b = 160;

	info_valeur.withText = true;

	info_valeur.text_color.r = 255;
	info_valeur.text_color.g = 255;
	info_valeur.text_color.b = 255;

	info_valeur.text_size = 14;

	strcpy(info_valeur.text, valeur);

	SHP_PrintSprite(info_titre, renderer);
	SHP_PrintSprite(info_valeur, renderer);
}

void afficher_info_int(SDL_Renderer *renderer, SDL_Rect *fenetre, int x, int y, char titre[100], int valeur)
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

	info_titre.background_color.r = 187;
	info_titre.background_color.g = 174;
	info_titre.background_color.b = 160;

	info_titre.withText = true;

	info_titre.text_color.r = 238;
	info_titre.text_color.g = 228;
	info_titre.text_color.b = 218;

	info_titre.text_size = 14;

	strcpy(info_titre.text, titre);

	SHP_Sprite info_valeur;

	info_valeur.background.x = info_titre.background.x;
	info_valeur.background.y = info_titre.background.y + 30;
	info_valeur.background.w = 100;
	info_valeur.background.h = 40;

	info_valeur.background_color.r = 187;
	info_valeur.background_color.g = 174;
	info_valeur.background_color.b = 160;

	info_valeur.withText = true;

	info_valeur.text_color.r = 255;
	info_valeur.text_color.g = 255;
	info_valeur.text_color.b = 255;

	info_valeur.text_size = 30;

	sprintf(info_valeur.text, "%d", valeur);
	SHP_PrintSprite(info_titre, renderer);
	SHP_PrintSprite(info_valeur, renderer);
}
