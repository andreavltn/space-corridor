/**
 * \file structures.h
 * \brief Contient l'ensemble des structures du jeu
 * \author Valentini Andréa & Viale Romain
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * \brief Type qui correspond au sprite
 */
 typedef struct sprite_s{
    int x; /*!< Champ indiquant la position x du sprite */
    int y; /*!< Champ indiquant la position y du sprite */
    int w; /*!< Champ indiquant la largeur w du sprite */
    int h; /*!< Champ indiquant la hauteur h du sprite */
} sprite_t;
  
/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
typedef struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* ligne_arrivee; /*!< Texture liée à l'image de la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< Texture liée à l'image d'une météorite */
} textures_t;
   
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

#endif