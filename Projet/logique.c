/**
 * \file logique.c
 * \brief Contient l'ensemble des fonctions relatives à la logique du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "logique.h"
#include "constantes.h"
#include <stdlib.h>

void init_sprite(sprite_t* sprite, int x, int y, int w, int h){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}

void init_walls(world_t* world){
    init_sprite(&(world->wall[0]),0,0,96,192);
    init_sprite(&(world->wall[1]),204,0,96,192);
    init_sprite(&(world->wall[2]),0,-352,32,160);
    init_sprite(&(world->wall[3]),74,-352,224,160);
    init_sprite(&(world->wall[4]),0,-672,96,192);
    init_sprite(&(world->wall[5]),204,-672,96,192);
}

void init_data(world_t* world){
    // initialisation du vaisseau (milieu de l'écran, à 32 pixels du bas, en 32x32)
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
  
    // initialisation de la ligne d'arrivée (milieu de l'écran, à 10 pixels du haut, LARGEUR_ECRANx8).
    init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 8);
  
    // initialisation du mur de météorites
    init_walls(world);
  
    // vitesse de la ligne d'arrivée
    world->vy = INITIAL_SPEED;
  
    // gameover et win
    world->gameover = 0;
    world->win = 0;  

    // temps écoulé
    world->time = 0; 
}


int sprites_collide(sprite_t* sp1, sprite_t* sp2){
    // déplacement au centre des coordonnées (qui étaient initialement dans le coin en haut à gauche)
    int x1 = sp1->x + sp1->w/2;
    int x2 = sp2->x + sp2->w/2;
    int y1 = sp1->y + sp1->h/2;
    int y2 = sp2->y + sp2->h/2;

    // si les deux sprites sont en collisions
    if ((abs(x1 - x2) <= (sp1->w + sp2->w)/2) && (abs(y1 - y2) <= (sp1->h + sp2->h)/2)){
        return 1;
    }
    return 0;
}

void handle_sprites_collision(world_t* world, sprite_t* sp1, sprite_t* sp2, int make_disappear, int make_win, ressources_t* ressources){
    // si les deux sprites sont en collision
    if (sprites_collide(sp1,sp2)){
        world->vy = 0; // arret du jeu

        // si le parametre make_disappear est à 1
        if (make_disappear==1){
            clean_texture(ressources->vaisseau); // rend invisible le vaisseau
        }

        // si le parametre make_win est à 1
        if(make_win){
            world->win = 1; // gagné
        } else {
            world->gameover = 1; // perdu
        }
    } 

}

int is_finished(world_t* world){
    return world->gameover || world->win;
}

void update_time(world_t* world, unsigned int currentTime, unsigned int* lastTime){
    // si on a passé 0.1s depuis le dernier check
    if (currentTime > *lastTime + 100) {
      world->time = (float)currentTime / 1000;  // met à jour le temps (conversion ms en s), cast en float
      *lastTime = currentTime; // met à jour le "dernier check" par pointeur
    }
}

void update_walls(world_t* world, ressources_t* ressources){
    // pour chaque mur
    for (int i=0;i<6;i++){
        // le mur de météorites descend de vy
        world->wall[i].y += world->vy;
        // gestion des collisions entre le vaisseau et le mur (disparition + pas de victoire)
        handle_sprites_collision(world,&(world->vaisseau),&(world->wall[i]),1,0,ressources);
    }
}

void update_data(world_t* world, ressources_t* ressources){
    // la ligne d'arrivée descend de vy
    world->ligne_arrivee.y += world->vy;

    // gestion des collisions entre le vaisseau et la ligne d'arrivée
    handle_sprites_collision(world,&(world->vaisseau),&(world->ligne_arrivee),0,1,ressources);

    // mise à jour de la position des murs + gestion des collisions entre le vaisseau et les murs
    update_walls(world, ressources);
}