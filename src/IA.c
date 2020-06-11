#include "IA.h"
#include "interface.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"
#include "header_2048.h"

int evaluation(plateau_2048 plateau)
{
	int acc = 0;

	for (int i = 0; i < plateau.taille; i++)
	{
		for (int j = 0; j < plateau.taille; j++)
		{
			acc += plateau.tab[i][j] * plateau.tab[i][j];

			/*if (i + 1 < plateau.taille)
			{
				if (plateau.tab[i + 1][j] == plateau.tab[i][j])
					acc += plateau.tab[i][j] / 2;
			}
			if (j + 1 < plateau.taille)
			{
				if (plateau.tab[i][j + 1] == plateau.tab[i][j])
					acc += plateau.tab[i][j] / 2;
			}*/
		}
	}

	return acc;
}

coup_IA IA_max(coup_IA position, int depth, animation_2048 *dep_IA, animation_2048 *add_IA, animation_2048 *app_IA)
{
	coup_IA coup;
	if (depth <= 0 || !defaite_unJoueur(position.position_coup))
	{
		//coup.valeur_coup = evaluation(position.position_coup);
		coup.valeur_coup = position.position_coup.score;
	}
	else
	{
		coup.position_coup.tab = creerTab(position.position_coup.taille);

		animation_list_2048 *dep_temp_1 = NULL;
		animation_list_2048 *add_temp_1 = NULL;
		animation_list_2048 *app_temp_1 = NULL;

		animation_list_2048 *dep_temp_2 = NULL;
		animation_list_2048 *add_temp_2 = NULL;
		animation_list_2048 *app_temp_2 = NULL;

		animation_list_2048 *dep_temp_3 = NULL;
		animation_list_2048 *add_temp_3 = NULL;
		animation_list_2048 *app_temp_3 = NULL;

		animation_list_2048 *dep_temp_4 = NULL;
		animation_list_2048 *add_temp_4 = NULL;
		animation_list_2048 *app_temp_4 = NULL;

		coup_IA position_temp_1;
		coup_IA position_temp_2;
		coup_IA position_temp_3;
		coup_IA position_temp_4;

		position_temp_1.position_coup.tab = creerTab(position.position_coup.taille);
		position_temp_2.position_coup.tab = creerTab(position.position_coup.taille);
		position_temp_3.position_coup.tab = creerTab(position.position_coup.taille);
		position_temp_4.position_coup.tab = creerTab(position.position_coup.taille);

		copier_plateau(position.position_coup, &position_temp_1.position_coup);
		copier_plateau(position.position_coup, &position_temp_2.position_coup);
		copier_plateau(position.position_coup, &position_temp_3.position_coup);
		copier_plateau(position.position_coup, &position_temp_4.position_coup);

		position_temp_1.position_coup.score += mouvement(position_temp_1.position_coup, 1, &dep_temp_1, &add_temp_1, &app_temp_1);
		position_temp_2.position_coup.score += mouvement(position_temp_2.position_coup, 2, &dep_temp_2, &add_temp_2, &app_temp_2);
		position_temp_3.position_coup.score += mouvement(position_temp_3.position_coup, 3, &dep_temp_3, &add_temp_3, &app_temp_3);
		position_temp_4.position_coup.score += mouvement(position_temp_4.position_coup, 4, &dep_temp_4, &add_temp_4, &app_temp_4);

		int **tab_comparaison;
		tab_comparaison = creerTab(position.position_coup.taille);
		copierPlateauVersTab(position.position_coup, tab_comparaison);
		position_temp_1.valeur_coup = -1;
		position_temp_2.valeur_coup = -1;
		position_temp_3.valeur_coup = -1;
		position_temp_4.valeur_coup = -1;

		if (!estEgale(tab_comparaison, position_temp_1.position_coup.tab, position_temp_1.position_coup.taille))
		{
			position_temp_1.valeur_coup = IA_max(position_temp_1, depth - 1, &dep_temp_1, &add_temp_1, &app_temp_1).valeur_coup;
		}
		

		if (!estEgale(tab_comparaison, position_temp_2.position_coup.tab, position_temp_2.position_coup.taille))
		{
			position_temp_2.valeur_coup = IA_max(position_temp_2, depth - 1, &dep_temp_2, &add_temp_2, &app_temp_2).valeur_coup;
		}
			
		if (!estEgale(tab_comparaison, position_temp_3.position_coup.tab, position_temp_3.position_coup.taille))
		{
			position_temp_3.valeur_coup = IA_max(position_temp_3, depth - 1, &dep_temp_3, &add_temp_3, &app_temp_3).valeur_coup;
		}

		if (!estEgale(tab_comparaison, position_temp_4.position_coup.tab, position_temp_4.position_coup.taille))
		{
			position_temp_4.valeur_coup = IA_max(position_temp_4, depth - 1, &dep_temp_4, &add_temp_4, &app_temp_4).valeur_coup;
		}

		int maximum = max_4(position_temp_1.valeur_coup, position_temp_2.valeur_coup, position_temp_3.valeur_coup, position_temp_4.valeur_coup);
		
		if (maximum == position_temp_1.valeur_coup)
		{
			copier_plateau(position_temp_1.position_coup, &coup.position_coup);
			coup.valeur_coup = position_temp_1.valeur_coup;

			if (depth == DEPTH_IA)
			{
				*dep_IA = dep_temp_1;
				*app_IA = app_temp_1;
				*add_IA = add_temp_1;
			}
			else
			{
				anim_detruire_list(&dep_temp_1);
				anim_detruire_list(&add_temp_1);
				anim_detruire_list(&app_temp_1);
			}
			if (!estEgale(tab_comparaison, position_temp_2.position_coup.tab, position_temp_2.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_2);
				anim_detruire_list(&add_temp_2);
				anim_detruire_list(&app_temp_2);
			}

			if (!estEgale(tab_comparaison, position_temp_3.position_coup.tab, position_temp_3.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_3);
				anim_detruire_list(&add_temp_3);
				anim_detruire_list(&app_temp_3);
			}

			if (!estEgale(tab_comparaison, position_temp_4.position_coup.tab, position_temp_4.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_4);
				anim_detruire_list(&add_temp_4);
				anim_detruire_list(&app_temp_4);
			}
		}
		else if (maximum == position_temp_2.valeur_coup)
		{
			copier_plateau(position_temp_2.position_coup, &coup.position_coup);
			coup.valeur_coup = position_temp_2.valeur_coup;
			if (depth == DEPTH_IA)
			{
				*dep_IA = dep_temp_2;
				*app_IA = app_temp_2;
				*add_IA = add_temp_2;
			}
			else
			{
				anim_detruire_list(&dep_temp_2);
				anim_detruire_list(&add_temp_2);
				anim_detruire_list(&app_temp_2);
			}
			if (!estEgale(tab_comparaison, position_temp_1.position_coup.tab, position_temp_1.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_1);
				anim_detruire_list(&add_temp_1);
				anim_detruire_list(&app_temp_1);
			}

			if (!estEgale(tab_comparaison, position_temp_3.position_coup.tab, position_temp_3.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_3);
				anim_detruire_list(&add_temp_3);
				anim_detruire_list(&app_temp_3);
			}

			if (!estEgale(tab_comparaison, position_temp_4.position_coup.tab, position_temp_4.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_4);
				anim_detruire_list(&add_temp_4);
				anim_detruire_list(&app_temp_4);
			}
		}
		else if (maximum == position_temp_3.valeur_coup)
		{
			copier_plateau(position_temp_3.position_coup, &coup.position_coup);
			coup.valeur_coup = position_temp_3.valeur_coup;

			if (depth == DEPTH_IA)
			{
				*dep_IA = dep_temp_3;
				*app_IA = app_temp_3;
				*add_IA = add_temp_3;
			}
			else
			{
				anim_detruire_list(&dep_temp_3);
				anim_detruire_list(&add_temp_3);
				anim_detruire_list(&app_temp_3);
			}

			if (!estEgale(tab_comparaison, position_temp_1.position_coup.tab, position_temp_1.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_1);
				anim_detruire_list(&add_temp_1);
				anim_detruire_list(&app_temp_1);
			}
			if (!estEgale(tab_comparaison, position_temp_2.position_coup.tab, position_temp_2.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_2);
				anim_detruire_list(&add_temp_2);
				anim_detruire_list(&app_temp_2);
			}
			if (!estEgale(tab_comparaison, position_temp_4.position_coup.tab, position_temp_4.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_4);
				anim_detruire_list(&add_temp_4);
				anim_detruire_list(&app_temp_4);
			}
		}
		else
		{
			copier_plateau(position_temp_4.position_coup, &coup.position_coup);
			coup.valeur_coup = position_temp_4.valeur_coup;

			if (depth == DEPTH_IA)
			{
				*dep_IA = dep_temp_4;
				*app_IA = app_temp_4;
				*add_IA = add_temp_4;
			}
			else
			{
				anim_detruire_list(&dep_temp_4);
				anim_detruire_list(&add_temp_4);
				anim_detruire_list(&app_temp_4);
			}
			if (!estEgale(tab_comparaison, position_temp_1.position_coup.tab, position_temp_1.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_1);
				anim_detruire_list(&add_temp_1);
				anim_detruire_list(&app_temp_1);
			}
			if (!estEgale(tab_comparaison, position_temp_2.position_coup.tab, position_temp_2.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_2);
				anim_detruire_list(&add_temp_2);
				anim_detruire_list(&app_temp_2);
			}
			if (!estEgale(tab_comparaison, position_temp_3.position_coup.tab, position_temp_3.position_coup.taille))
			{
				anim_detruire_list(&dep_temp_3);
				anim_detruire_list(&add_temp_3);
				anim_detruire_list(&app_temp_3);
			}
		}

		libererTab(tab_comparaison, position.position_coup.taille);
		libererTab(position_temp_1.position_coup.tab, position_temp_1.position_coup.taille);
		libererTab(position_temp_2.position_coup.tab, position_temp_2.position_coup.taille);
		libererTab(position_temp_3.position_coup.tab, position_temp_3.position_coup.taille);
		libererTab(position_temp_4.position_coup.tab, position_temp_4.position_coup.taille);

		if(depth != DEPTH_IA)
		{
			libererTab(coup.position_coup.tab, coup.position_coup.taille);
		}
	}
	return coup;
}
