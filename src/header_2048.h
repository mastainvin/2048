#ifndef HEADER_2048_H
#define HEADER_2048_H

#define BORDER_PURCENT 3.5
#define ANIMATION_SPEED 50
#define ANIMATION_MAX 5

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

typedef struct plateau_2048
{
	int x, y, largeur, taille;
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
}animation_value_2048;

typedef struct animation_list_2048
{
	animation_value_2048 value;
	struct animation_list_2048 *next;
}animation_list_2048, *animation_2048;


#endif