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


int max_4(int a, int b, int c, int d)
{
  int maximum = a;
  if(b > maximum)
    maximum = b;

  if (c > maximum)
    maximum = c;

  if (d > maximum)
    maximum = d;

  return maximum;
}
SHP_bool estEgale(int **tab, int **tab2, int taille)
{
  int egale = true;
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      if(tab[i][j] != tab2[i][j])
        egale = false;
    }
    
  }
  return egale;
  
}
// Fonction permettant de trier un tableau d'entiers
void trier_tab(int *tab, int taille)
{
  for (int i = 0; i < taille; i++)
  {
    int temp = tab[i];

    int j = i;
    while (j > 0 && tab[j - 1] > temp)
    {
      tab[j] = tab[j - 1];
      j = j - 1;
    }
    tab[j] = temp;
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
  printf("\n");
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

void copier_plateau(plateau_2048 plateau, plateau_2048 *nouveau)
{
  nouveau->taille = plateau.taille;
  nouveau->bestscore = plateau.bestscore;
  nouveau->score = plateau.score;
  nouveau->largeur = plateau.largeur;
  initialisation(*nouveau);
  copierPlateauVersTab(plateau, nouveau->tab);

  nouveau->taille = plateau.taille;
  nouveau->x = plateau.x;
  nouveau->y = plateau.y;
}

/*-------------------------------*/

int mouvement(plateau_2048 plateau, int n, animation_2048 *li, animation_2048 *anim_dep, animation_2048 *anim_app)
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
        if (plateau.tab[i][j] != 0)
        {
          animation_value_2048 element_app;
          element_app.depart_int.x = i;
          element_app.depart_int.y = j;

          element_app.depart = coordTabAcoordAffichage(plateau, element_app.depart_int);

          element_app.affichage.x = -1;
          element_app.valeur_case = plateau.tab[i][j];

          anim_rajoute_element(anim_app, element_app);
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

/*------- Fonctions concernant le mode arcade 1vs1 --------*/

// Fonctions des bonus

// Bonus 2 deviennent 8
void bonus_2to8(plateau_2048 plateau)
{
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      if (plateau.tab[i][j] == 2)
      {
        plateau.tab[i][j] = 8;
      }
    }
  }
}

// Bonus rangement
void bonus_rangement(plateau_2048 plateau)
{
  int taille_tab_temp = plateau.taille * plateau.taille;
  int tab[taille_tab_temp];

  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      tab[plateau.taille * i + j] = plateau.tab[i][j];
    }
  }

  trier_tab(tab, taille_tab_temp);
  
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      plateau.tab[i][j] = tab[i * plateau.taille + j];
    }
  }
}


// Bonus détruire
void bonus_detuire(plateau_2048 plateau)
{
  int maximum = -1;
  int i_temp = -1;
  int j_temp = -1;
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      if (plateau.tab[i][j] >= maximum)
      {
        maximum = plateau.tab[i][j];
        i_temp = i;
        j_temp = j;
      }
    }
  }
  plateau.tab[i_temp][j_temp] = 0;
}

// Bonus inverser les touches

void bonus_inverserTouches(int *fleche)
{
  switch (*fleche)
  {
  case 1:
    *fleche = 2;
    break;
  case 2:
    *fleche = 1;
    break;
  case 3:
    *fleche = 4;
    break;
  case 4:
    *fleche = 3;
    break;
  default:
    break;
  }
}

// Bonus mélanger

void bonus_melange(plateau_2048 plateau)
{
  int taille_case_tab = plateau.taille * plateau.taille;
  int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
  int temp;

  for (int i = 0; i < taille_case_tab; i++)
  {
    i_temp_1 = rand() % 4;
    j_temp_1 = rand() % 4;

    i_temp_2 = rand() % 4;
    j_temp_2 = rand() % 4;

    temp = plateau.tab[i_temp_1][j_temp_1];
    plateau.tab[i_temp_1][j_temp_1] = plateau.tab[i_temp_2][j_temp_2];
    plateau.tab[i_temp_2][j_temp_2] = temp;
  }
}
// Fonction calculant la valeur de la case maximum d'un tableau
int max_tab(plateau_2048 plateau)
{
  int maximum;
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      maximum = max(maximum, plateau.tab[i][j]);
    }
  }

  return maximum;
}
// Fonction calculant la valeur du prochain palier
int palier(plateau_2048 plateau)
{
 
  return max_tab(plateau) * 4;
}

void  generer_bonus(joueur_arcade_2048 *joueur)
{
  joueur->prochain_bonus = rand() % 3 + 1;
  joueur->prochain_malus = rand() % 3 + 1;
}