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

void init_walls_level_1(world_t* world){
    init_sprite(&(world->walls_level_1[0]),0,0,96,192);
    init_sprite(&(world->walls_level_1[1]),204,0,96,192);
    init_sprite(&(world->walls_level_1[2]),0,-352,32,160);
    init_sprite(&(world->walls_level_1[3]),74,-352,224,160);
    init_sprite(&(world->walls_level_1[4]),0,-704,96,192);
    init_sprite(&(world->walls_level_1[5]),204,-704,96,192);
}

void init_walls_level_2(world_t* world){
    // PLACEHOLDER
}

void init_ovnis_level_1(world_t* world){
    init_sprite(&(world->ovnis_level_1[0]),110,-810,OVNI_WIDTH,OVNI_HEIGHT);
    init_sprite(&(world->ovnis_level_1[1]),137,-810,OVNI_WIDTH,OVNI_HEIGHT);
    init_sprite(&(world->ovnis_level_1[2]),164,-810,OVNI_WIDTH,OVNI_HEIGHT);
}

void init_ovnis_level_2(world_t* world){
    // PLACEHOLDER
}

void init_data_level_1(world_t* world){
    
    // initialisation du vaisseau
    init_sprite(&(world->spacecraft), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);

    // initialisation de la ligne d'arrivée du niveau 1
    init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT_1, SCREEN_WIDTH, 20);

    // initialisation des murs de météorites du niveau 1
    init_walls_level_1(world);

    // initialisation des ovnis du niveau 1
    init_ovnis_level_1(world);

    // initialisation de la limite invisible
    init_sprite(&(world->invisible_limit), 0, INVISIBLE_LIMIT_HEIGHT, SCREEN_WIDTH, 20);

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

void init_data_level_2(world_t* world){

    // initialisation du vaisseau
    init_sprite(&(world->spacecraft), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);

    // initialisation de la ligne d'arrivée du niveau 2
    init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT_2, SCREEN_WIDTH, 20);

    // initialisation des murs de météorites du niveau 2
    init_walls_level_2(world);

    // initialisation des ovnis du niveau 2
    init_ovnis_level_2(world);

    // initialisation de la limite invisible
    init_sprite(&(world->invisible_limit), 0, INVISIBLE_LIMIT_HEIGHT, SCREEN_WIDTH, 20);

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

void blink_splash_text(world_t* world, unsigned int timeSinceLaunch){

    // en utilisant le modulo, le temps écoulé peut faire partie de deux intervalles, ce qui permet d'alterner visible/caché
    if(timeSinceLaunch%(2*SPLASH_TEXT_TIME) <= SPLASH_TEXT_TIME){ 
        init_sprite(&(world->splash_text), 0, SCREEN_HEIGHT/2 + 50, 100, SCREEN_WIDTH); // -> texte affiché
    } else { // sinon le temps écoulé est compris dans (TIME/2,TIME)
        init_sprite(&(world->splash_text), -10000, SCREEN_HEIGHT/2 + 50, 100, SCREEN_WIDTH); // -> texte caché
    }
}

int sprites_collide(sprite_t* sp1, sprite_t* sp2){

    // déplacement au centre des coordonnées (qui étaient initialement dans le coin en haut à gauche)
    int x1 = sp1->x + sp1->w/2;
    int x2 = sp2->x + sp2->w/2;
    int y1 = sp1->y + sp1->h/2;
    int y2 = sp2->y + sp2->h/2;

    // si les deux sprites sont en collision
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

int is_finished_level(world_t* world){
    return world->gameover || world->win;
}

void update_time(world_t* world, unsigned int actualTime, unsigned int* lastTimeCheck){
    // si on a passé 0.1s depuis le dernier check
    if(actualTime > *lastTimeCheck + 100) {
      world->time = (float)actualTime / 1000;  // met à jour le temps (conversion ms en s), cast en float
      *lastTimeCheck = actualTime; // met à jour le "dernier check" par pointeur
    }
}

void update_finishline(world_t* world){
    // la ligne d'arrivée descend de vy
    world->ligne_arrivee.y += world->vy;
    // gestion de la collision avec le vaisseau (victoire)
    handle_sprites_collision(world,&(world->spacecraft),&(world->ligne_arrivee),0,1);
}

void update_walls_level_1(world_t* world){
    // pour chaque indice du tableau de murs
    for(int indice=0; indice<6; indice++){
        // le mur de météorites descend de vy
        world->walls_level_1[indice].y += world->vy;
        // gestion des collisions entre le vaisseau et le mur (disparition + défaite)
        handle_sprites_collision(world,&(world->spacecraft),&(world->walls_level_1[indice]),1,0);
    }
}

void update_walls_level_2(world_t* world){
    // PLACEHOLDER
}

void update_ovnis_level_1(world_t* world){
    // pour chaque indice du tableau d'ovnis
    for(int indice=0; indice<3; indice++){
        // l'ovni descend de vy
        world->ovnis_level_1[indice].y += world->vy;
        // gestion des collisions entre le vaisseau et l'ovni (disparition + défaite)
        handle_sprites_collision(world,&(world->spacecraft),&(world->ovnis_level_1[indice]),1,0);
    }
}

void update_ovnis_level_2(world_t* world){
    // PLACEHOLDER
}

void shoot_missile(world_t* world){

    // pour chaque indice de missile possible dans le tableau
    for(int i=0; i<10; i++){
        // si le spot est disponible
        if(world->missiles[i].x == -10000){
            // apparition du missile juste au dessus du vaisseau
            init_sprite(&(world->missiles[i]), world->spacecraft.x+(SHIP_SIZE/2 - MISSILE_WIDTH/2), world->spacecraft.y-MISSILE_HEIGHT, MISSILE_WIDTH, MISSILE_HEIGHT);
            world->missileCooldown = MISSILE_COOLDOWN;
            break;
        }
    }
}

void update_missiles_level_1(world_t* world){

    // pour chaque missile du tableau
    for(int i=0; i<10; i++){

        // le missile monte de la vitesse associée
        world->missiles[i].y -= MISSILE_SPEED;

        // pour chaque mur du niveau 1
        for(int j=0; j<6; j++){
            // gestion de la collision entre le missile et le mur (disparition)
            handle_sprites_collision(world,&(world->missiles[i]),&(world->walls_level_1[j]),1,-1);
        }

        // pour chaque ovni du niveau 1
        for(int k=0; k<3; k++){
            // gestion de la collision entre l'ovni et le missile (disparition)
            handle_sprites_collision(world,&(world->ovnis_level_1[k]),&(world->missiles[i]),1,-1);
        }

        // gestion de la collision entre le missile et la limite invisible (disparition)
        handle_sprites_collision(world,&(world->missiles[i]),&(world->invisible_limit),1,-1);

        // gestion de la collision entre le missile et la ligne d'arrivée (disparition)
        handle_sprites_collision(world,&(world->missiles[i]),&(world->ligne_arrivee),1,-1);
    }
}

void update_missiles_level_2(world_t* world){

    // pour chaque missile du tableau
    for(int i=0; i<10; i++){

        // le missile monte de la vitesse associée
        world->missiles[i].y -= MISSILE_SPEED;

        // pour chaque mur du niveau 1
        for(int j=0; j<50; j++){
            // gestion de la collision entre le missile et le mur (disparition)
            handle_sprites_collision(world,&(world->missiles[i]),&(world->walls_level_2[j]),1,-1);
        }

        // pour chaque ovni du niveau 2
        for(int k=0; k<30; k++){
            // gestion de la collision entre l'ovni et le missile (disparition)
            handle_sprites_collision(world,&(world->ovnis_level_2[k]),&(world->missiles[i]),1,-1);
        }

        // gestion de la collision entre le missile et la limite invisible (disparition)
        handle_sprites_collision(world,&(world->missiles[i]),&(world->invisible_limit),1,-1);

        // gestion de la collision entre le missile et la ligne d'arrivée (disparition)
        handle_sprites_collision(world,&(world->missiles[i]),&(world->ligne_arrivee),1,-1);
    }
}

void update_missileCooldown(world_t* world, unsigned int actualTime, unsigned int* lastMissileCooldownCheck) {
    unsigned int elapsed = actualTime - *lastMissileCooldownCheck; // temps écoulé depuis le dernier check
    if (elapsed > 0) { // si du temmps s'est passé
        if (world->missileCooldown > 0) { // si le cooldown n'est tjrs pas égal à 0
            if (elapsed < world->missileCooldown) { // si le temps écoulé est inférieur au cooldown restant (donc la soustraction >0)
                world->missileCooldown -= elapsed; // maj du temps
            } else {
                world->missileCooldown = 0; // sinon on met à 0 (plafond inférieur)
            }
        }
        *lastMissileCooldownCheck = actualTime; // maj du dernier check
    }
}

void update_data_level_1(world_t* world, ressources_t* ressources){

    // mise à jour de la position de la ligne d'arrivée + gestion des collisions
    update_finishline(world);

    // mise à jour de la position des murs + gestion des collisions
    update_walls_level_1(world);

    // mise à jour de la position des ovnis + gestion des collisions
    update_ovnis_level_1(world);

    // mise à jour de la position du missile + gestion des collisions
    update_missiles_level_1(world);
}

void update_data_level_2(world_t* world, ressources_t* ressources){

    // mise à jour de la position de la ligne d'arrivée + gestion de la collision entre le vaisseau et celle-ci
    update_finishline(world);

    // mise à jour de la position des murs + gestion des collisions entre le vaisseau et les murs
    update_walls_level_2(world);

    // mise à jour de la position des ovnis + gestion des collisions
    update_ovnis_level_2(world);

    // mise à jour de la position du missile + gestion des collisions avec les murs
    update_missiles_level_2(world);
}