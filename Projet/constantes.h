/**
 * \file constantes.h
 * \brief Contient l'ensemble des constantes du jeu
 * \author Valentini Andréa & Viale Romain
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

/**
 * \brief Représentation du monde du jeu
 */
typedef struct world_s{
    sprite_t vaisseau; /*!< Champ représentant le sprite du vaisseau */
    sprite_t ligne_arrivee; /*!< Champ représentant le sprite de la ligne d'arrivée */
    sprite_t mur_meteorite; /*!< Champ représentant le sprite du mur de météorites */
    float vy; /*!< Champ représentant la vitesse de déplacement de la ligne d'arrivée */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
} world_t;

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300
 
/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480
 
/**
 * \brief Taille d'un vaisseau
 */
#define SHIP_SIZE 32
 
/**
 * \brief Taille d'un météorite
 */
#define METEORITE_SIZE 32
 
/**
 * \brief Nombre de météorites en largeur
 */
#define NBR_METEORITE_WIDTH 3
 
/**
 * \brief Nombre de météorites en hauteur
 */
#define NBR_METEORITE_HEIGHT 7
 
/**
 * \brief Hauteur de la ligne d'arrivée
 */
#define FINISH_LINE_HEIGHT 10
 
/**
* \brief Pas de déplacement horizontal du vaisseau
*/
#define MOVING_STEP 10
 
/**
 * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
 */
#define INITIAL_SPEED 2

#endif