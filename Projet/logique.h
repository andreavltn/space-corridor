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
    sprite_t spacecraft; /*!< Champ représentant le sprite du vaisseau */
    sprite_t ligne_arrivee; /*!< Champ représentant le sprite de la ligne d'arrivée */
    sprite_t walls_level_1[6]; /*!< Champ représentant le tableau du sprite des murs de météorites du niveau 1 */
    sprite_t walls_level_2[50]; /*!< Champ représentant le tableau du sprite des murs de météorites du niveau 2 */
    sprite_t ovnis_level_1[3]; /*!< Champ représentant le tableau du sprite des ovnis du niveau 1 */
    sprite_t ovnis_level_2[30]; /*!< Champ représentant le tableau du sprite des ovnis du niveau 2 */
    sprite_t missiles[10]; /*!< Champ représentant le tableau des sprites des missiles tirés par le vaisseau */
    sprite_t invisible_limit; /*!< Champ représentant le sprite de la limite invisible (pour stopper les missiles) */
    int game_status; /*!< Champ indiquant si le statut actuel du jeu */
    float vy; /*!< Champ représentant la vitesse de déplacement de la ligne d'arrivée */
    int gameover; /*!< Champ indiquant si on a perdu */
    int win; /*!< Champ indiquant si on a gagné */
    float time; /*!< Champ représentant le temps écoulé depuis le début du jeu */
    unsigned int missileCooldown; /*!< Champ représentant le cooldown restant du tir de missile (en ms) */
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
 * \brief La fonction initialise la position des murs du niveau 1
 * \param world les données du monde
 */
void init_walls_level_1(world_t* world);

/**
 * \brief La fonction initialise la position des murs du niveau 2
 * \param world les données du monde
 */
void init_walls_level_2(world_t* world);

/**
 * \brief La fonction initialise la position des ovnis du niveau 1
 * \param world les données du monde
 */
void init_ovnis_level_1(world_t* world);

/**
 * \brief La fonction initialise la position des ovnis du niveau 2
 * \param world les données du monde
 */
void init_ovnis_level_2(world_t* world);

/**
 * \brief La fonction initialise les données du monde du niveau 1
 * \param world les données du monde
 */
void init_data_level_1(world_t * world);

/**
 * \brief La fonction initialise les données du monde du niveau 2
 * \param world les données du monde
 */
void init_data_level_2(world_t * world);

/**
 * \brief Fait clignoter le texte "PRESS SPACE TO START!" en fonction de la constante SPLASH_TEXT_TIME
 * \param world les données du monde
 * \param timeSinceLaunch la durée depuis laquelle le jeu est lancé (en ms)
 */
void blink_splash_text(world_t* world, unsigned int timeSinceLaunch);

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
 * \param make_disappear 1 si sp1 doit disparaître en cas de collision, 2 si sp1 et sp2 doivent disparaitre, 0 sinon
 * \param make_win 1 si la collision déclenche la victoire, 0 si défaite, autre valeur entière si ça ne doit rien faire 
 * \param ressources les ressources du jeu
 */
void handle_sprites_collision(world_t* world, sprite_t* sp1, sprite_t* sp2, int make_disappear, int make_win);

/**
 * \brief Renvoie l'état du niveau (jeu gagné/jeu perdu)
 * \param world les données du monde
 */   
int is_finished_level(world_t *world);

/**
 * \brief Met à jour le temps écoulé
 * \param world les données du monde
 * \param actualTime le temps écoulé depuis le lancement du jeu (en ms)
 * \param lastTimeCheck le temps écoulé au dernier check (en ms)
 */   
void update_time(world_t* world, unsigned int actualTime, unsigned int* lastTimeCheck);

/**
 * \brief Met à jour la position de la ligne d'arrivée + gère les collisions
 * \param world les données du monde
 */   
void update_finishline(world_t* world);

/**
 * \brief Met à jour la position des murs de météorites + gère les collisions (niveau 1)
 * \param world les données du monde
 */
void update_walls_level_1(world_t* world);

/**
 * \brief Met à jour la position des murs de météorites + gère les collisions (niveau 2)
 * \param world les données du monde
 */
void update_walls_level_2(world_t* world);


/**
 * \brief Met à jour la position des ovnis + gère les collisions (niveau 1)
 * \param world les données du monde
 */
void update_ovnis_level_1(world_t* world);

/**
 * \brief Met à jour la position des ovnis + gère les collisions (niveau 2)
 * \param world les données du monde
 */
void update_ovnis_level_2(world_t* world);

/**
 * \brief Tire un missile à partir du vaisseau
 * \param world les données du monde
 */   
void shoot_missile(world_t* world);

/**
 * \brief Met à jour la position du missile + gère les collisions (niveau 1)
 * \param world les données du monde
 */   
void update_missiles(world_t* world);

/**
 * \brief Met à jour la position du missile + gère les collisions (niveau 2)
 * \param world les données du monde
 */   
void update_missiles_level_2(world_t* world);

/**
 * \brief Met à jour le temps restant au cooldown du tir de missile du vaisseau
 * \param world les données du monde
 * \param actualTime le temps écoulé depuis le lancement du jeu (en ms)
 * \param lastMissileCooldownCheck le temps écoulé au dernier check (en ms)
 */   
void update_missileCooldown(world_t* world, unsigned int actualTime, unsigned int* lastMissileCooldownCheck);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde (niveau 1)
 * \param world les données du monde
 * \param ressources les ressources du jeu
 */
void update_data_level_1(world_t *world, ressources_t* ressources);


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde (niveau 2)
 * \param world les données du monde
 * \param ressources les ressources du jeu
 */
void update_data_level_2(world_t* world, ressources_t* ressources);

#endif