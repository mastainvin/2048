/**
* \file jeu.c
* \brief fonctions de gestions d'actions du 2048
* \author Vincent Mastain
* \author Ahmed Trabelsi
* \version 0.1
* \date 10 juin 2020
*	Fonctions modifiant et testant les tableaux. 
* Remplissage des listes permattant l'affichage d'animations
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "interface.h"
#include "header_2048.h"

/**
* \fn void copierPlateauVersTab(plateau_2048 plateau, int **tab)
* \brief copie un plateau dans un tableau
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param plateau plateau du joueur
* \param tab tableau de taille dynamique
* \return rien dans tous les cas
*/
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

/**
* \fn void copierTabVersPlateau(plateau_2048 plateau, int **tab)
* \brief copie un tableau dans un plateau
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param plateau plateau du joueur
* \param tab tableau de taille dynamique
* \return rien dans tous les cas
*/
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

/**
* \fn int max_4(int a, int b, int c, int d)
* \brief détermine la max de 4 entier
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param a entier 1
* \param b entier 2
* \param c entier 3
* \param d entier 4
* \return l'entier le plus grand
*/
int max_4(int a, int b, int c, int d)
{
  int maximum = a;
  if (b > maximum)
    maximum = b;

  if (c > maximum)
    maximum = c;

  if (d > maximum)
    maximum = d;

  return maximum;
}

/**
* \fn SHP_bool estEgale(int **tab, int **tab2, int taille)
* \brief vérifie l'égalite entre 2 tableaux
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param tab premier tableau
* \param tab2 deuxième tableau
* \param taille taille des deux tableau
* \return true s'il sont égaux false sinon
*/
SHP_bool estEgale(int **tab, int **tab2, int taille)
{
  int egale = true;
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      if (tab[i][j] != tab2[i][j])
        egale = false;
    }
  }
  return egale;
}

/**
* \fn void trier_tab(int *tab, int taille)
* \brief trie par insertion d'un trableaux dynamique
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param tab tableau
* \param taille taille du tableau
* \return rien dans tous les cas
*/
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

/**
* \fn int **creerTab(int taille)
* \brief création d'un tableau dynamique
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param taille taille du tableau
* \return un tableau de taille taille * taille
*/
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

/**
* \fn void libererTab(int **tab, int taille)
* \brief libération d'un tableau dynamique
* \author Vincent Mastain
* \version 0.1
* \date 2 juin 2020
* \param tab tableau à libérer
* \param taille taille du tableau
* \return rien dans tous les cas
*/
void libererTab(int **tab, int taille)
{
  for (int i = 0; i < taille; i++)
  {
    free(tab[i]);
  }
  free(tab);
}

/**
* \fn void affichage(int **tab)
* \brief debugage d'un tableau dynamiqeu
* \author Ahmed Trabelsi
* \version 0.1
* \date 2 juin 2020
* \param tab tableau à vérier
* \return rien dans tous les cas
*/
void affichage(int **tab)
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

/**
* \fn void initialisation(plateau_2048 plateau)
* \brief initialisation d'un plateau à 0
* \author Ahmed Trabelsi
* \version 0.1
* \date 1 juin 2020
* \param plateau plateau du joueur de 2048
* \return rien dans tous les cas
*/
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

/**
* \fn void depart(plateau_2048 plateau)
* \brief départ d'un plateau 
* \author Ahmed Trabelsi
* \version 0.1
* \date 1 juin 2020
* \param plateau plateau du joueur de 2048
* \return rien dans tous les cas
* Mise en place des 2 première case
*/
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

/**
* \fn void copier_plateau(plateau_2048 plateau, plateau_2048 *nouveau)
* \brief copie d'un plateau vers un autre plateau 
* \author Mastain Vincent
* \version 0.1
* \date 1 juin 2020
* \param plateau plateau à copier
* \param nouveau nouveau plateau
* \return rien dans tous les cas
*/
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

/**
* \fn int mouvement(plateau_2048 plateau, int n, animation_2048 *li, animation_2048 *anim_dep, animation_2048 *anim_app)
* \brief mouvement d'un joueur 
* \author Mastain Vincent
* \author Ahmed Trabelsi
* \version 0.1
* \date 1 juin 2020
* \param plateau plateau du joueur
* \param n direction du déplacement
* \param li liste d'animation du déplacement
* \param anim_dep liste d'animation de l'addition
* \param anim_app liste d'animation de l'apparation
* \return le score du coup
*/
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

  // Suivant la direction qu'a choisis l'utilisateur on déplacem toute les cases au maximum vers la direction
  if (n == 1) // Pour aller à droite //
  {
    SHP_bool addition = false;

    for (i = 0; i < plateau.taille; i++)
    {
      for (j = plateau.taille - 1; j >= 0; j--)
      {
        // Si la case n'est pas vide
        if (plateau.tab[i][j] != 0)
        {

          // On crée les futures éléments d'animations
          animation_value_2048 element;
          element.valeur_case = plateau.tab[i][j];
          element.depart_int.x = i;
          element.depart_int.y = j;

          element.depart = coordTabAcoordAffichage(plateau, element.depart_int);
          element.affichage = element.depart;
          coord_2048 coordArrive;
          coordArrive = element.depart_int;

          animation_value_2048 element_dep;
          element_dep.valeur_case = plateau.tab[i][j];
          element_dep.affichage.x = -1;
          element_dep.affichage.y = -1;

          k = j;

          // On déplace un curseur vers le prochaine case non vide
          if (j != plateau.taille - 1)
          {
            do
            {
              k++;
            } while (k != plateau.taille - 1 && plateau.tab[i][k] == 0);
          }

          // Tous les cas de figures que peut avoir addition / bord / collision avec case de diff. valeur
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

          // On rajoute à la fin c'est déplacements et additions dans les listes d'animations
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
          coord_2048 coordArrive;
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
          coord_2048 coordArrive;
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
          coord_2048 coordArrive;
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
    coord_2048 possibilitees[taille_max_possibilitees];

    for (i = 0; i < taille_max_possibilitees; i++)
    {
      possibilitees[i].x = -1;
      possibilitees[i].y = -1;
    }

    // On récupère toutes les cases disponibles
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

    // On détermine l'emplacement de la nouvelle case
    coord_2048 nouvelle_case = possibilitees[rand() % taille_possibilitees];
    a = nouvelle_case.x;
    b = nouvelle_case.y;

    // On modifie le tableau
    plateau.tab[a][b] = 2 * (rand() % 2 + 1);

    animation_value_2048 element_app;
    element_app.depart_int.x = a;
    element_app.depart_int.y = b;

    element_app.depart = coordTabAcoordAffichage(plateau, element_app.depart_int);

    element_app.affichage.x = 0;
    element_app.valeur_case = plateau.tab[a][b];

    // On rajoute cette case dans la liste d'apparitions
    anim_rajoute_element(anim_app, element_app);
  }

  return score;
}

/*------- Fonctions concernant le mode arcade 1vs1 --------*/

// Fonctions des bonus

/**
* \fn void bonus_2to8(plateau_2048 plateau)
* \brief bonus les 2 deviennent des 8 
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueur
* \return rien dans tous les cas
*/
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

/**
* \fn void bonus_rangement(plateau_2048 plateau)
* \brief bonus rangement des cases
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueur
* \return rien dans tous les cas
*/
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

/**
* \fn void bonus_detuire(plateau_2048 plateau)
* \brief bonus destruction de la case la plus haute du joueurs adverse
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueur
* \return rien dans tous les cas
*/
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

/**
* \fn void bonus_inverserTouches(int *fleche)
* \brief bonus inversion des touches du joueurs adverse
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param fleche direction désirée
* \return rien dans tous les cas
*/
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

/**
* \fn void bonus_melange(plateau_2048 plateau)
* \brief bonus mélange des cases du joueurs adverse
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueurs adverse
* \return rien dans tous les cas
*/
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

/**
* \fn int max_tab(plateau_2048 plateau)
* \brief détermine la case la plus grande d'un plateau
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueurs adverse
* \return la valeur la plus grande
*/
int max_tab(plateau_2048 plateau)
{
  int maximum = 0;
  for (int i = 0; i < plateau.taille; i++)
  {
    for (int j = 0; j < plateau.taille; j++)
    {
      maximum = max(maximum, plateau.tab[i][j]);
    }
  }

  return maximum;
}

/**
* \fn int palier(plateau_2048 plateau)
* \brief calcule le palier correspondant à un plateau
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param plateau plateau du joueurs adverse
* \return le palier
*/
int palier(plateau_2048 plateau)
{

  return max_tab(plateau) * 4;
}

/**
* \fn void  generer_bonus(joueur_arcade_2048 *joueur)
* \brief génère les bonus d'un joueurs
* \author Mastain Vincent
* \version 0.1
* \date 4 juin 2020
* \param joueurs regroupe les bonus et malus d'un joueur
* \return rien dans tous les cas
*/
void generer_bonus(joueur_arcade_2048 *joueur)
{
  joueur->prochain_bonus = rand() % 3 + 1;
  joueur->prochain_malus = rand() % 3 + 1;
}