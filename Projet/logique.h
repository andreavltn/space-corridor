/**
 * \file logique_jeu.h
 * \brief Header de logique_jeu.c
 * \author Valentini Andréa & Viale Romain
 */

#ifndef LOGIQUE_H
#define LOGIQUE_H

#include "sdl2-light.h"
#include "affichage.h"

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
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event, world_t *world);

/**
 * \brief Renvoie l'état de fin du jeu (0 ou 1)
 * \param world les données du monde
 */   
int is_game_over(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t *world);

#endif