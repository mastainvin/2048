#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "interface.h"
#include "header_2048.h"

void copierPlateauVersTab(plateau_2048 plateau, int **tab)
{
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      tab[i][j] = plateau.tab[i][j];
    }
  }
}

void copierTabVersPlateau(plateau_2048 plateau, int **tab)
{
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      plateau.tab[i][j] = tab[i][j];
    }
  }
}

int  **creerTab(int taille)
{
  int **tab;
  tab = (int **)malloc(taille * sizeof(int *));

  for (int i = 0; i < taille; i++)
  {
    tab[i] = (int *)malloc(taille * sizeof(int));
  }
  return tab;
}

void libererTab(int **tab, int taille)
{
  for (int i = 0; i < taille; i++)
  {
    free(tab[i]);
  }
  free(tab);
}

void affichage(int **tab) // Procédure qui permet d'afficher le tableau sur le terminal
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

void mouvement(plateau_2048 plateau, int n, animation_2048 *li)
{
  int i;
  int j;
  int temp = 0;
  int k;

  int a = 0;
  int b;

  if (n == 1) // Pour aller à droite //
  {
    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          for (k = j + 1; k < plateau.taille; k++)
          {
            if (plateau.tab[i][k] == 0)
            {
              coordArrive.x = i;
              coordArrive.y = k;
              temp = plateau.tab[i][j];
              plateau.tab[i][j] = plateau.tab[i][k];
              plateau.tab[i][k] = temp;
            }
            else if (plateau.tab[i][k] == plateau.tab[i][j])
            {
              coordArrive.x = i;
              coordArrive.y = k;
              plateau.tab[i][k] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          anim_rajoute_element(li, element);
        }
      }
    }
  }

  else if (n == 2) // Pour aller à gauche //
  {

    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[i][3 - j] != 0)
        {
          animation_value_2048 element;
          element.depart_int.x = i;
          element.depart_int.y = 3 - j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;
          for (k = j + 1; k < plateau.taille; k++)
          {
        

            if (plateau.tab[i][3 - k] == 0)
            {
              coordArrive.x = i;
              coordArrive.y = 3 - k;
              temp = plateau.tab[i][3 - j];
              plateau.tab[i][3 - j] = plateau.tab[i][3 - k];
              plateau.tab[i][3 - k] = temp;
            }

            else if (plateau.tab[i][3 - k] == plateau.tab[i][3 - j])
            {
              coordArrive.x = i;
              coordArrive.y = 3 - k;
              plateau.tab[i][3 - k] = 2 * plateau.tab[i][3 - j];
              plateau.tab[i][3 - j] = 0;
            }
          }
          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          anim_rajoute_element(li, element);
        }
      }
    }
  }
  else if (n == 3) // Pour aller en haut //
  {
    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[3 - i][j] != 0)
        {
          animation_value_2048 element;
          element.depart_int.x = 3 - i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          for (k = i + 1; k < plateau.taille; k++)
          {
           
            

            if (plateau.tab[3 - k][j] == 0)
            {
              coordArrive.x = 3 - k;
              coordArrive.y = j;
              temp = plateau.tab[3 - i][j];
              plateau.tab[3 - i][j] = plateau.tab[3 - k][j];
              plateau.tab[3 - k][j] = temp;
            }
            else if (plateau.tab[3 - k][j] == plateau.tab[3 - i][j])
            {
              coordArrive.x = 3 - k;
              coordArrive.y = j;
              plateau.tab[3 - k][j] = 2 * plateau.tab[3 - i][j];
              plateau.tab[3 - i][j] = 0;
            }
          }
          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          anim_rajoute_element(li, element);
        }
      }
    }
  }
  else if (n == 4) // Pour aller en bas //
  {
    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          for (k = i + 1; k < plateau.taille; k++)
          {
            if (plateau.tab[k][j] == 0)
            {
              coordArrive.x = k;
              coordArrive.y = j;
              temp = plateau.tab[i][j];
              plateau.tab[i][j] = plateau.tab[k][j];
              plateau.tab[k][j] = temp;
            }
            else if (plateau.tab[k][j] == plateau.tab[i][j])
            {
              coordArrive.x = k;
              coordArrive.y = j;
              plateau.tab[k][j] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          anim_rajoute_element(li, element);
        }
      }
    }
  }

  a = rand() % plateau.taille;
  b = rand() % plateau.taille;

  while (plateau.tab[a][b] != 0)
  {

    srand(time(NULL));

    a = rand() % plateau.taille;
    b = rand() % plateau.taille;
  }

  plateau.tab[a][b] = 2;
}
