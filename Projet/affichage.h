/**
 * \file affichage.h
 * \brief Header de affichage.c
 * \author Valentini Andréa & Viale Romain
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
 */
typedef struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* ligne_arrivee; /*!< Texture liée à l'image de la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< Texture liée à l'image d'une météorite */
    TTF_Font* font; /*!< Texture liée à la police du texte */
} ressources_t;

#include "logique.h" // plus bas pour éviter les dépendances circulaires

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
 */
void init_textures(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * \brief fonction qui applique la texture des murs de météorites
 * \param ressources les ressources du jeu
 * \param renderer le renderer
 * \param world le monde du jeu
 */
void apply_walls(ressources_t* ressources, SDL_Renderer* renderer, world_t* world);

/**
 * \brief La fonction applique la texture du sprite sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param ressources les ressources du jeu
 * \param world le monde du jeu
 */
void apply_sprite(SDL_Renderer *renderer , ressources_t *ressources , world_t * world);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param ressources les ressources du jeu
 */
void apply_background(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * \brief La fonction affiche le timer et les messages de fin sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param world le monde du jeu
 * \param ressources les ressources du jeu
 */
void apply_texts(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world le monde du jeu
 * \param ressources les ressources du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * \brief La fonction nettoie les ressources
 * \param ressources les ressources
 */
void clean_ressources(ressources_t *ressources);

#endif