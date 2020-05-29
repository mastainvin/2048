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

int **creerTab(int taille)
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

void depart(plateau_2048 plateau)
{

  int a;
  int b;
  int c;
  int d;

  srand(time(NULL));

  a = rand() % plateau.taille;
  b = rand() % plateau.taille;
  do
  {
    c = rand() % plateau.taille;
    d = rand() % plateau.taille;
  } while (a == c && b == d);

  plateau.tab[a][b] = 2 * (rand() % 2 + 1);

  plateau.tab[c][d] = 2 * (rand() % 2 + 1);
}

/*-------------------------------*/

int mouvement(plateau_2048 plateau, int n,animation_2048 *li, animation_2048 *anim_dep, animation_2048 *anim_app)
{
  unsigned int largeur_bordure = BORDER_PURCENT * plateau.largeur / (100 * (plateau.taille + 1));
  unsigned int largeur_case = (plateau.largeur - largeur_bordure * (plateau.taille + 1)) / plateau.taille;

  int score = 0;
  int i;
  int j;
  int k;
  SHP_bool mouvement = false;
  int a = 0;
  int b;

  if (n == 1) // Pour aller à droite //
  {
    SHP_bool addition = false;

    for (i = 0; i < plateau.taille; i++)
    {
      for (j = plateau.taille - 1; j >= 0; j--)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;
          element.valeur_case = plateau.tab[i][j];
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          animation_value_2048 element_dep;
          element_dep.valeur_case = plateau.tab[i][j];
          element_dep.affichage.x = -1;
          element_dep.affichage.y = -1;

          k = j;

          if (j != plateau.taille - 1)
          {
            do
            {
              k++;
            } while (k != plateau.taille - 1 && plateau.tab[i][k] == 0);
          }

          if (plateau.tab[i][k] == 0 || k == j)
          {
            coordArrive.x = i;
            coordArrive.y = k;
            addition = false;
            if (k != j)
            {
              mouvement = true;
              plateau.tab[i][k] = plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          else
          {
            if (plateau.tab[i][k] == plateau.tab[i][j] && !addition)
            {
              mouvement = true;
              addition = true;
              coordArrive.x = i;
              coordArrive.y = k;
              plateau.tab[i][k] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;

              element_dep.affichage.x = largeur_case;
              element_dep.valeur_case = plateau.tab[i][k];

              score += plateau.tab[i][k];
            }
            else
            {
              coordArrive.x = i;
              coordArrive.y = k - 1;
              addition = false;
              if (k - 1 != j)
              {
                mouvement = true;
                plateau.tab[i][k - 1] = plateau.tab[i][j];
                plateau.tab[i][j] = 0;
              }
            }
          }

          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          element_dep.depart = element.arrive;
          anim_rajoute_element(li, element);
          anim_rajoute_element(anim_dep, element_dep);
        }
      }
    }
  }
  else if (n == 2) // Pour aller à gauche //
  {
    SHP_bool addition = false;

    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;
          element.valeur_case = plateau.tab[i][j];
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          animation_value_2048 element_dep;
          element_dep.valeur_case = plateau.tab[i][j];
          element_dep.affichage.x = -1;

          k = j;
          if (j != 0)
          {
            do
            {
              k--;
            } while (k != 0 && plateau.tab[i][k] == 0);
          }

          if (plateau.tab[i][k] == 0 || k == j)
          {
            coordArrive.x = i;
            coordArrive.y = k;
            addition = false;
            if (k != j)
            {
              mouvement = true;

              plateau.tab[i][k] = plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          else
          {
            if (plateau.tab[i][k] == plateau.tab[i][j] && !addition)
            {
              mouvement = true;

              addition = true;
              coordArrive.x = i;
              coordArrive.y = k;
              plateau.tab[i][k] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;

              element_dep.affichage.x = largeur_case;
              element_dep.valeur_case = plateau.tab[i][k];

              score += plateau.tab[i][k];
            }
            else
            {
              addition = false;
              coordArrive.x = i;
              coordArrive.y = k + 1;

              if (k + 1 != j)
              {
                mouvement = true;
                plateau.tab[i][k + 1] = plateau.tab[i][j];
                plateau.tab[i][j] = 0;
              }
            }
          }

          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          element_dep.depart = element.arrive;
          anim_rajoute_element(li, element);
          anim_rajoute_element(anim_dep, element_dep);
        }
      }
    }
  }
  else if (n == 3) // Pour aller en haut //
  {
    SHP_bool addition = false;

    for (j = 0; j < plateau.taille; j++)
    {
      for (i = 0; i < plateau.taille; i++)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;
          element.valeur_case = plateau.tab[i][j];
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          animation_value_2048 element_dep;
          element_dep.valeur_case = plateau.tab[i][j];
          element_dep.affichage.x = -1;

          k = i;
          if (i != 0)
          {
            do
            {
              k--;
            } while (k != 0 && plateau.tab[k][j] == 0);
          }

          if (plateau.tab[k][j] == 0 || k == i)
          {
            addition = false;
            coordArrive.x = k;
            coordArrive.y = j;

            if (k != i)
            {
              mouvement = true;
              plateau.tab[k][j] = plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          else
          {
            if (plateau.tab[k][j] == plateau.tab[i][j] && !addition)
            {
              mouvement = true;
              addition = true;
              coordArrive.x = k;
              coordArrive.y = j;
              plateau.tab[k][j] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;

              element_dep.affichage.x = largeur_case;
              element_dep.valeur_case = plateau.tab[k][j];

              score += plateau.tab[k][j];
            }
            else
            {
              addition = false;
              coordArrive.x = k + 1;
              coordArrive.y = j;

              if (k + 1 != i)
              {
                mouvement = true;
                plateau.tab[k + 1][j] = plateau.tab[i][j];
                plateau.tab[i][j] = 0;
              }
            }
          }

          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          element_dep.depart = element.arrive;
          anim_rajoute_element(li, element);
          anim_rajoute_element(anim_dep, element_dep);
        }
      }
    }
  }
  else if (n == 4) // Pour aller en bas //
  {
    SHP_bool addition = false;

    for (j = 0; j < plateau.taille; j++)
    {
      for (i = plateau.taille - 1; i >= 0; i--)
      {
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element;

          element.valeur_case = plateau.tab[i][j];
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coordInt_2048 coordArrive;
          coordArrive = element.depart_int;

          animation_value_2048 element_dep;
          element_dep.valeur_case = plateau.tab[i][j];
          element_dep.affichage.x = -1;

          k = i;

          if (i != plateau.taille - 1)
          {
            do
            {
              k++;
            } while (k != plateau.taille - 1 && plateau.tab[k][j] == 0);
          }

          if (plateau.tab[k][j] == 0 || k == i)
          {
            addition = false;
            coordArrive.x = k;
            coordArrive.y = j;

            if (k != i)
            {
              mouvement = true;
              plateau.tab[k][j] = plateau.tab[i][j];
              plateau.tab[i][j] = 0;
            }
          }
          else
          {
            if (plateau.tab[k][j] == plateau.tab[i][j] && !addition)
            {
              mouvement = true;
              addition = true;
              coordArrive.x = k;
              coordArrive.y = j;
              plateau.tab[k][j] = 2 * plateau.tab[i][j];
              plateau.tab[i][j] = 0;

              element_dep.affichage.x = largeur_case;
              element_dep.valeur_case = plateau.tab[k][j];

              score += plateau.tab[k][j];
            }
            else
            {
              addition = false;
              coordArrive.x = k - 1;
              coordArrive.y = j;

              if (k - 1 != i)
              {
                mouvement = true;
                plateau.tab[k - 1][j] = plateau.tab[i][j];
                plateau.tab[i][j] = 0;
              }
            }
          }
          element.arrive = coordTabAcoordAffichage(plateau, coordArrive);
          element_dep.depart = element.arrive;
          anim_rajoute_element(li, element);
          anim_rajoute_element(anim_dep, element_dep);
        }
      }
    }
  }

  if (mouvement == false)
  {
    anim_detruire_list(li);
  }
  else
  {
    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if(plateau.tab[i][j] != 0)
        {
          animation_value_2048 element_app;
          element_app.depart_int.x = i;
          element_app.depart_int.y = j;

          element_app.depart = coordTabAcoordAffichage(plateau,element_app.depart_int);

          element_app.affichage.x = -1;
          element_app.valeur_case = plateau.tab[i][j];

          anim_rajoute_element(anim_app,element_app);
        }
      }
      
    }
    
    int taille_max_possibilitees = plateau.taille * plateau.taille - 1;
    coordInt_2048 possibilitees[taille_max_possibilitees];

    for (i = 0; i < taille_max_possibilitees; i++)
    {
      possibilitees[i].x = -1;
      possibilitees[i].y = -1;
    }

    for (i = 0; i < plateau.taille; i++)
    {
      for (j = 0; j < plateau.taille; j++)
      {
        if (plateau.tab[i][j] == 0)
        {
          k = 0;
          while (possibilitees[k].x != -1)
          {
            k++;
          }
          possibilitees[k].x = i;
          possibilitees[k].y = j;
        }
      }
    }
    int taille_possibilitees = 0;

    while (possibilitees[taille_possibilitees].x != -1 && taille_possibilitees < taille_max_possibilitees)
    {
      taille_possibilitees++;
    }

    coordInt_2048 nouvelle_case = possibilitees[rand() % taille_possibilitees];
    a = nouvelle_case.x;
    b = nouvelle_case.y;

    plateau.tab[a][b] = 2 * (rand() % 2 + 1);

    animation_value_2048 element_app;
    element_app.depart_int.x = a;
    element_app.depart_int.y = b;

    element_app.depart = coordTabAcoordAffichage(plateau, element_app.depart_int);

    element_app.affichage.x = 0;
    element_app.valeur_case = plateau.tab[a][b];

    anim_rajoute_element(anim_app, element_app);
  }

  return score;
}



