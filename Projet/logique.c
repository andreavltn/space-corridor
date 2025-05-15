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
    init_sprite(&(world->walls[0]),0,0,96,192);
    init_sprite(&(world->walls[1]),204,0,96,192);
    init_sprite(&(world->walls[2]),0,-352,32,160);
    init_sprite(&(world->walls[3]),74,-352,224,160);
    init_sprite(&(world->walls[4]),0,-672,96,192);
    init_sprite(&(world->walls[5]),204,-672,96,192);
}

void init_data(world_t* world){
    // initialisation du vaisseau (milieu de l'écran, à 32 pixels du bas, en 32px*32px)
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
  
    // initialisation de la ligne d'arrivée (milieu de l'écran, à la hauteur définie, LARGEUR_ECRAN*20px).
    init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 20);
  
    // initialisation du mur de météorites
    init_walls(world);

    // initialisation des missiles en dehors de l'écran (pas encore actifs)
    for(int i=0; i<10; i++){
        init_sprite(&(world->missiles[i]), -10000, 0, MISSILE_WIDTH, MISSILE_HEIGHT);
    }

    // vitesse de la ligne d'arrivée
    world->vy = INITIAL_SPEED;
  
    // gameover et win
    world->gameover = 0;
    world->win = 0;  

    // temps écoulé
    world->time = 0;

    // cooldown du tir de missile
    world->missileCooldown = 0;
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

void handle_sprites_collision(world_t* world, sprite_t* sp1, sprite_t* sp2, int make_disappear, int make_win){
    // si les deux sprites sont en collision
    if (sprites_collide(sp1,sp2)){
        // si le parametre make_disappear est à 1
        if (make_disappear==1){
            sp1->x = -10000; // déplace le sprite en dehors de l'écran
        }

        // si victoire ou défaite
        if(make_win==1 || make_win==0){
            world->vy = 0; // arrêt du jeu
           if(make_win==1){
            world->win = 1;
           } else {
            world->gameover = 1; // perdu
           }
        }
        // sinon rien ne se passe pour toute autre valeur 
    }
}

int is_finished(world_t* world){
    return world->gameover || world->win;
}

void update_time(world_t* world, unsigned int currentTime, unsigned int* lastTimeCheck){
    // si on a passé 0.1s depuis le dernier check
    if(currentTime > *lastTimeCheck + 100) {
      world->time = (float)currentTime / 1000;  // met à jour le temps (conversion ms en s), cast en float
      *lastTimeCheck = currentTime; // met à jour le "dernier check" par pointeur
    }
}

void update_finishline(world_t* world){
    // la ligne d'arrivée descend de vy
    world->ligne_arrivee.y += world->vy;
    // gestion de la collision avec le vaisseau (victoire)
    handle_sprites_collision(world,&(world->vaisseau),&(world->ligne_arrivee),0,1);
}

void update_walls(world_t* world){
    // pour chaque mur
    for(int i=0;i<6;i++){
        // le mur de météorites descend de vy
        world->walls[i].y += world->vy;
        // gestion des collisions entre le vaisseau et le mur (disparition + défaite)
        handle_sprites_collision(world,&(world->vaisseau),&(world->walls[i]),1,0);
    }
}

void shoot_missile(world_t* world){
    // pour chaque indice de missile possible dans le tableau
    for(int i=0; i<10; i++){
        // si le spot est disponible
        if(world->missiles[i].x == -10000){
            // apparition du missile juste au dessus du vaisseau
            init_sprite(&(world->missiles[i]), world->vaisseau.x+(SHIP_SIZE/2 - MISSILE_WIDTH/2), world->vaisseau.y-MISSILE_HEIGHT, MISSILE_WIDTH, MISSILE_HEIGHT);
            world->missileCooldown = MISSILE_COOLDOWN;
            break;
        }
    }
}

void update_missiles(world_t* world){
    // pour chaque missile du tableau
    for(int i=0; i<10; i++){
        // le missile monte de la vitesse associée
        world->missiles[i].y -= MISSILE_SPEED;

        // pour chaque mur
        for(int j=0; j<6; j++){
            // gestion de la collision entre le missile et le mur (disparition)
            handle_sprites_collision(world,&(world->missiles[i]),&(world->walls[j]),1,-1);
        }
    }
}

void update_missileCooldown(world_t* world, unsigned int currentTime, unsigned int* lastMissileCooldownCheck) {
    unsigned int elapsed = currentTime - *lastMissileCooldownCheck; // temps écoulé depuis le dernier check
    if (elapsed > 0) { // si du temmps s'est passé
        if (world->missileCooldown > 0) { // si le cooldown n'est tjrs pas égal à 0
            if (elapsed < world->missileCooldown) { // si le temps écoulé est inférieur au cooldown restant (donc la soustraction >0)
                world->missileCooldown -= elapsed; // maj du temps
            } else {
                world->missileCooldown = 0; // sinon on met à 0 (plafond inférieur)
            }
        }
        *lastMissileCooldownCheck = currentTime; // maj du dernier check
    }
}


void update_data(world_t* world, ressources_t* ressources){
    // mise à jour de la position de la ligne d'arrivée + gestion de la collision entre le vaisseau et celle-ci
    update_finishline(world);

    // mise à jour de la position des murs + gestion des collisions entre le vaisseau et les murs
    update_walls(world);

    // mise à jour de la position du missile + gestion des collisions avec les murs
    update_missiles(world);
}