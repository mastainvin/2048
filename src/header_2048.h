#ifndef HEADER_2048_H
#define HEADER_2048_H

/**
* \file header_2048.h
* \brief en-tête principale du programme
* \author Vincent Mastain
* \version 0.1
* \date 13 juin 2020
*	Gestion de toutes les constantes prototypes et enumération du programme
*/

#define BORDER_PURCENT 10
#define ANIMATION_SPEED 4
#define ANIMATION_POP_SPEED 5
#define ANIMATION_APP_SPEED 12
#define CENTER 99999
#define TOUR_MAX 30
#define DEPTH_IA 5

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

/**
 * \enum position_utilisateur 
 * \brief enumération des positions possibles de l'utilisateur
 *
 * Permet la gestion du menu et de la boucle principale
 */
typedef enum position_utilisateur
{
	continuer,					 /* ! < continuer la partie*/
	menu_principal,			 /* ! < dans le menu principale du jeu*/
	unJoueur,						 /* ! < joue seul*/
	deuxJoueur,					 /* ! < joue à deux*/
	IA,									 /* ! < joue contre une IA*/
	deuxJoueurArcadeMode /* ! < joue à deux dans le mode arcade*/
} position_utilisateur;

/**
 * \struct plateau_2048 
 * \brief plateau de jeu d'un joueur
 *
 * Objet gérant l'ensemble des données d'un plateau de 2048
 */
typedef struct plateau_2048
{
	int x;				 /* ! < position x du plateau */
	int y;				 /* ! < position y du plateau */
	int largeur;	 /* ! < taille en px */
	int taille;		 /* ! < taille du tableau */
	int score;		 /* ! < score actuel du joueur*/
	int bestscore; /* ! <  meilleur score */
	int **tab;		 /* ! < tableau du joueur*/
} plateau_2048;

/**
 * \struct partie_2048 
 * \brief gérer une partie de 2048
 *
 * Objet gérant l'ensemble des données d'une partie de 2048
 */
typedef struct partie_2048
{
	int tour;											 /* ! < Joueur a qui c'est le tour*/
	int numero_tour;							 /* ! < Nomnbre de tour joués*/
	SHP_bool continuer_apres_2048; /* ! < choix un seul joueur pour jouer après 2048*/
	int palier_max;								 /* ! < palier max en mode arcade*/
	int chrono;										 /* ! < chrono d'une partie en mode arcade*/
} partie_2048;

/**
 * \struct joueur_arcade_2048 
 * \brief données d'un joueur en mode arcade
 *
 */
typedef struct joueur_arcade_2048
{
	int bonus, malus;										/* ! < bonus et malus actuels*/
	int prochain_bonus, prochain_malus; /* ! < bonus et malus suivants*/
	int palier;													/* ! < palier pour avoir ses bonus*/
	int chrono;													/* ! < chrono du bonus ou malus d'un joueur*/
	SHP_bool rapide;										/* ! < bonus rapide*/
	SHP_bool inverse;										/* ! < malus touches inversés*/
} joueur_arcade_2048;

/**
 * \struct coord_2048 
 * \brief regroupe x et y 
 *
 */
typedef struct coord_2048
{
	int x, y;
} coord_2048;

/**
 * \struct animation_value_2048 
 * \brief valeur d'une animation
 *
 * Objet permettant d'afficher une animation sur la fenêtre
 */
typedef struct animation_value_2048
{
	coord_2048 depart;		 /* ! < coordonnées de départ*/
	coord_2048 arrive;		 /* ! < coordonnées d'arrivée*/
	coord_2048 affichage;	 /* ! < coordonnées d'affichage*/
	coord_2048 depart_int; /* ! < coordonnées de départ dans le tableau*/
	int valeur_case;			 /* ! < valeur de la case à animer*/
} animation_value_2048;

/**
 * \struct animation_list_2048 
 * \brief liste d'animation
 *
 * Liste constituée d'animation à afficher en même temps
 */
typedef struct animation_list_2048
{
	animation_value_2048 value;				/* ! < valeur de l'animation*/
	struct animation_list_2048 *next; /* ! < animation suivantes*/
} animation_list_2048, *animation_2048;

/**
 * \struct coup_IA 
 * \brief coup que peut faire l'IA
 *
 */
typedef struct coup_IA
{
	int valeur_coup;						/* ! < valeur du coup */
	plateau_2048 position_coup; /* ! < le coup en lui même */
} coup_IA;

#endif