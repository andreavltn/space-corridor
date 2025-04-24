/**
 * \file affichage_jeu.h
 * \brief Header de affichage_jeu.c
 * \author Valentini Andréa & Viale Romain
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "sdl2-light.h"

/**
 * \brief Type qui correspond au sprite
 */
typedef struct sprite_s{
    float x; /*!< Champ indiquant la position x du sprite */
    float y; /*!< Champ indiquant la position y du sprite */
    float w; /*!< Champ indiquant la largeur w du sprite */
    float h; /*!< Champ indiquant la hauteur h du sprite */
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
    sprite_t wall[6]; /*!< Champ représentant le tableau du sprite des murs de météorites */
    float vy; /*!< Champ représentant la vitesse de déplacement de la ligne d'arrivée */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
} world_t;

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
 */
void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);

/**
 * \brief fonction qui applique la texture des murs de météorites
 * \param textures les textures du jeu
 * \param renderer le renderer
 * \param world le monde
 */
void apply_walls(textures_t* textures, SDL_Renderer* renderer, world_t* world);

/**
 * \brief La fonction applique la texture du sprite sur le renderer lié à l'écran de jeus
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param world le monde du jeu
 */
void apply_sprite(SDL_Renderer *renderer , textures_t *textures , world_t * world);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 */
void apply_background(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param textures les textures du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
 */
void clean_textures(textures_t *textures);

#endif