#ifndef HEADER_2048_H
#define HEADER_2048_H

#define BORDER_PURCENT 3.5

typedef struct plateau_2048
{
	int x, y, largeur, taille;
	int **tab;
} plateau_2048;

#endif