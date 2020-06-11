#ifndef HEADER_2048_H
#define HEADER_2048_H

#define BORDER_PURCENT 10
#define ANIMATION_SPEED 4
#define ANIMATION_POP_SPEED 5
#define ANIMATION_APP_SPEED 12
#define CENTER 99999
#define TOUR_MAX 30

#define min(a, b) a<b?a:b
#define max(a, b) a>b?a:b

typedef enum position_utilisateur
{
	continuer,
	menu_principal,
	unJoueur,
	deuxJoueur,
	IA,
	deuxJoueurArcadeMode
}position_utilisateur;

typedef struct plateau_2048
{
	int x, y, largeur, taille, score, bestscore;
	int **tab;
} plateau_2048;

typedef struct partie_2048
{
	int tour;
	int numero_tour;
	SHP_bool continuer_apres_2048;
}partie_2048;

typedef struct joueur_arcade_2048
{
	int bonus, malus;
	int prochain_bonus, prochain_malus;
	int palier;
	int chrono;
	SHP_bool rapide;
	SHP_bool inverse;
}joueur_arcade_2048;

typedef struct coord_2048
{
	int x,y;
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

typedef struct coup_IA
{
	int valeur_coup;
	plateau_2048 position_coup;
}coup_IA;

#endif