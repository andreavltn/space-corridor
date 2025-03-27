/**
 * \file affichage_jeu.h
 * \brief Header de affichage_jeu.c
 * \author Valentini Andréa & Viale Romain
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "sdl2-light.h"
#include "constantes.h"

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
 * \brief La fonction initialise la position du sprite
 * \param sprite le sprite du jeu
 * \param x la position x du sprite
 * \param y la position y du sprite
 * \param w la largeur du sprite
 * \param h la hauteur du sprite
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);

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
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);

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

/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

#endif