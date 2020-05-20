#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "header_2048.h"

void creerTab(int **tab, int taille)
{
  tab = (int **) malloc(taille * sizeof(int*));

  for (int i = 0; i < taille; i++)
  {
    tab[i] = (int *) malloc(taille * sizeof(int));  
  }
}

void libererTab(int **tab, int taille)
{
  for (int i = 0; i < taille; i++)
  {
    free(tab[i]);
  }
  free(tab);
}

void affichage(int **tab) // Procédure qui permet d'afficher le tableau sur le terminal//
{
  int i;
  int j;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      if (tab[i][j] == 0)
      {
        printf("|  |");
      }

      else
        printf("| %d|", tab[i][j]);
    }

    printf("\n");
  }
}

/*-------------------------------*/

void initialisation(plateau_2048 plateau)
{
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      plateau.tab[i][j] = 0;
    }
  }
}

/*-------------------------------*/

void depart(int **tab)
{

  int a;
  int b;
  int c;
  int d;

  srand(time(NULL));

  a = rand() % 4;
  b = rand() % 4;
  c = rand() % 4;
  d = rand() % 4;

  tab[a][b] = 2;

  tab[c][d] = 2;
}

/*-------------------------------*/

void mouvement(int **tab, int n)
{
  int i;
  int j;
  int temp = 0;
  int k;

  int a = 0;
  int b;
  
  if (n == 1) // Pour aller à droite //
  {
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
      {       
        for (k = j + 1; k < 4; k++)
        {
          if (tab[i][j] != 0 && tab[i][k] == 0)
          {
            temp = tab[i][j];
            tab[i][j] = tab[i][k];
            tab[i][k] = temp;
          }
          else if (tab[i][j] != 0 && tab[i][k] == tab[i][j])
          {
            tab[i][k] = 2 * tab[i][j];
            tab[i][j] = 0;
          }
        }
      }
    }
  }

  else if (n == 2) // Pour aller à gauche //
  {

    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
      {
        for (k = j + 1; k < 4; k++)
        {
          if (tab[i][3-j] != 0 && tab[i][3-k] == 0)
          {
            temp = tab[i][3-j];
            tab[i][3-j] = tab[i][3-k];
            tab[i][3-k] = temp;
          }

          else if (tab[i][3-j] != 0 && tab[i][3-k] == tab[i][3-j])
          {
            tab[i][3-k] = 2 * tab[i][3-j];
            tab[i][3-j] = 0;
          }
        }
      }
    }
  }

  else if (n == 3) // Pour aller en haut //
  {

    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
      {

        for (k = i + 1; k < 4; k++)
        {
          if (tab[3-i][j] != 0 && tab[3-k][j] == 0)
          {
            temp = tab[3-i][j];
            tab[3-i][j] = tab[3-k][j];
            tab[3-k][j] = temp;
          }

          else if (tab[3-i][j] != 0 && tab[3-k][j] == tab[3-i][j])
          {
            tab[3-k][j] = 2 * tab[3-i][j];
            tab[3-i][j] = 0;
          }
        }
      }
    }
  }

  else if (n == 4) // Pour aller en bas //
  {
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
      {
        for (k = i; k < 4; k++)
        {
          if (tab[i][j] != 0 && tab[k][j] == 0)
          {
            temp = tab[i][j];
            tab[i][j] = tab[k][j];
            tab[k][j] = temp;
          }

          else if (tab[i][j] != 0 && tab[k][j] == tab[i][j])
          {
            tab[k][j] = 2 * tab[i][j];
            tab[i][j] = 0;
          }
        }
      }
    }
  }

  a = rand() % 4;
  b = rand() % 4;

  while (tab[a][b] != 0)
  {

    srand(time(NULL));

    a = rand() % 4;
    b = rand() % 4;
  }

  tab[a][b] = 2;
}

