/**
 * \file logique.h
 * \brief Header de logique.c
 * \author Valentini Andréa & Viale Romain
 */

#ifndef LOGIQUE_H
#define LOGIQUE_H

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
 * \brief Représentation du monde du jeu
 */
 typedef struct world_s{
    sprite_t splash_text; /*!< Champ représentant le sprite du texte PRESS SPACE TO START */
    sprite_t vaisseau; /*!< Champ représentant le sprite du vaisseau */
    sprite_t ligne_arrivee; /*!< Champ représentant le sprite de la ligne d'arrivée */
    sprite_t walls[6]; /*!< Champ représentant le tableau du sprite des murs de météorites */
    sprite_t missiles[10]; /*!< Champ représentant le tableau des sprites des missiles tirés par le vaisseau */
    sprite_t limite_invisible; /*!< Champ représentant le sprite de la limite invisible (pour stopper les missiles) */
    int game_started; /*!< Champ représentant si oui ou non, le jeu a commencé */
    float vy; /*!< Champ représentant la vitesse de déplacement de la ligne d'arrivée */
    int gameover; /*!< Champ indiquant si on a perdu */
    int win; /*!< Champ indiquant si on a gagné */
    float time; /*!< Champ représentant le temps écoulé depuis le début du jeu */
    unsigned int missileCooldown; /*!< Champ représentant le cooldown restant du tir de missile */ 
} world_t;

#include "affichage.h" // plus bas pour éviter les dépendances circulaires

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
 * \brief La fonction initialise la position des murs de météorites
 *  \param world les données du monde
 */
void init_walls(world_t* world);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);

/**
 * \brief La fonction renvoie l'état de collision de 2 sprites (0 ou 1)
 * \param sp1 le premier sprite
 * \param sp2 le deuxième sprite
 */
int sprites_collide(sprite_t* sp1, sprite_t* sp2);

/**
 * \brief La fonction gère les collisions entre deux sprites
 * \param world les données du monde
 * \param sp1 le premier sprite
 * \param sp2 le deuxième sprite
 * \param make_disappear 1 si sp1 doit disparaître en cas de collision, 0 sinon
 * \param make_win 1 si la collision déclenche la victoire, 0 si défaite, autre valeur entière si ça ne doit rien faire 
 * \param ressources les ressources du jeu
 */
void handle_sprites_collision(world_t* world, sprite_t* sp1, sprite_t* sp2, int make_disappear, int make_win);

/**
 * \brief Renvoie l'état de fin du jeu (jeu gagné/jeu perdu)
 * \param world les données du monde
 */   
int is_finished(world_t *world);

/**
 * \brief Met à jour le temps écoulé
 * \param world les données du monde
 * \param currentTime le temps écoulé actuel
 * \param lastTimeCheck le temps écoulé au dernier check
 */   
void update_time(world_t* world, unsigned int currentTime, unsigned int* lastTimeCheck);

/**
 * \brief Met à jour la position de la ligne d'arrivée + gère les collisions
 * \param world les données du monde
 * \param currentTime le temps écoulé actuel
 * \param lastTimeCheck le temps écoulé au dernier check
 */   
void update_finishline(world_t* world);

/**
 * \brief Met à jour la position des murs de météorites + gère les collisions
 * \param world les données du monde
 * \param ressources les ressources du jeu
 */
void update_walls(world_t* world);

/**
 * \brief Tire un missile à partir du vaisseau
 * \param world les données du monde
 */   
void shoot_missile(world_t* world);

/**
 * \brief Met à jour la position du missile + gère les collisions
 * \param world les données du monde
 */   
void update_missiles(world_t* world);

void update_missileCooldown(world_t* world, unsigned int currentTime, unsigned int* lastMissileCooldownCheck);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 * \param ressources les ressources du jeu
 */
void update_data(world_t *world, ressources_t* ressources);

#endif