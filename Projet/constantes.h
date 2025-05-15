/**
 * \file constantes.h
 * \brief Contient l'ensemble des constantes du jeu
 * \author Valentini Andréa & Viale Romain
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

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
 * \brief Taille d'une météorite
 */
#define METEORITE_SIZE 32

/**
 * \brief Largeur d'un missile
 */
#define MISSILE_WIDTH 9

/**
 * \brief Hauteur d'un missile
 */
#define MISSILE_HEIGHT 17
 
/**
 * \brief Hauteur de la ligne d'arrivée
 */
#define FINISH_LINE_HEIGHT -960

/**
 * \brief Hauteur de la limite verticale invisible du jeu
 */
#define INVISIBLE_LIMIT_HEIGHT -20
 
/**
 * \brief Pas de déplacement horizontal du vaisseau
 */
#define MOVING_STEP 10

/**
 * \brief Vitesse d'un missile 
 */
#define MISSILE_SPEED 2

/**
 * \brief Cooldown d'un missile (en ms)
 */
#define MISSILE_COOLDOWN 1000
 
/**
 * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
 */
#define INITIAL_SPEED 1

#endif