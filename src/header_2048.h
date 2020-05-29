#ifndef HEADER_2048_H
#define HEADER_2048_H

#define BORDER_PURCENT 10
#define ANIMATION_SPEED 6
#define ANIMATION_POP_SPEED 3
#define ANIMATION_APP_SPEED 9

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

typedef enum position_utilisateur
{
	menu_principal,
	unJoueur,
	deuxJoueur,
	IA,
	deuxJoueurArcadeMode
}position_utilisateur;

typedef struct plateau_2048
{
	int x, y, largeur, taille, score;
	int **tab;
} plateau_2048;

typedef struct coord_2048
{
	double x,y;
}coord_2048;

typedef struct coordInt_2048
{
	int x,y;
}coordInt_2048;

typedef struct animation_value_2048
{
	coordInt_2048 depart, arrive, affichage;
	coordInt_2048 depart_int;
	int valeur_case;
}animation_value_2048;

typedef struct animation_list_2048
{
	animation_value_2048 value;
	struct animation_list_2048 *next;
}animation_list_2048, *animation_2048;


#endif