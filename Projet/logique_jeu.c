/**
 * \file logique_jeu.c
 * \brief Contient l'ensemble des fonctions relatives à la logique du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "constantes.h"
#include "logique_jeu.h"

void handle_events(SDL_Event *event, world_t *world){
    Uint8 *keystates;
    while(SDL_PollEvent(event)){
        // si l'utilisateur a cliqué sur le X de la fenêtre
        if(event->type == SDL_QUIT ) {
            // On indique la fin du jeu
            world->gameover = 1;
        }
  
        // si une touche est appuyée
        if(event->type == SDL_KEYDOWN){

            // touche echap
            if (event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }

            // touche droite/d
            if(event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d){
                world->vaisseau.x+=MOVING_STEP;
            }

            // touche gauche/q
            if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q){
                world->vaisseau.x-=MOVING_STEP;
            }

            // haut/z
            if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z){
                // si la vitesse est inférieure à 4 (3.9 pour la précision des flottants)
                if(world->vy < 3.9){
                    // augmentation de la vitesse du jeu
                    world->vy+=0.1;
                }
            }

            // bas/s
            if(event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
                // si la vitesse est supérieure à 2
                if(world->vy > 2){
                    // réduction de la vitesse du jeu
                    world->vy-=0.1;
                }
            }     
        }        
    }
}



int is_game_over(world_t *world){
    return world->gameover;
}



void update_data(world_t *world){
    // la ligne d'arrivée descend de vy
    world->ligne_arrivee.y += world->vy;
  
    // le mur de météorites descend de vy
    world->mur_meteorite.y += world->vy;
}