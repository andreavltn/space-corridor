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
    switch(world->game_status){
        case 0: // au debut du jeu -> initialisation des murs du niveau 1

            // ligne 1
            init_sprite(&(world->walls_level_1[0]),0,0,3*METEORITE_SIZE,6*METEORITE_SIZE);
            init_sprite(&(world->walls_level_1[1]),204,0,3*METEORITE_SIZE,6*METEORITE_SIZE);
            // ligne 2
            init_sprite(&(world->walls_level_1[2]),0,-352,1*METEORITE_SIZE,5*METEORITE_SIZE);
            init_sprite(&(world->walls_level_1[3]),74,-352,7*METEORITE_SIZE,5*METEORITE_SIZE);
            // ligne 3
            init_sprite(&(world->walls_level_1[4]),0,-704,3*METEORITE_SIZE,6*METEORITE_SIZE);
            init_sprite(&(world->walls_level_1[5]),204,-704,3*METEORITE_SIZE,6*METEORITE_SIZE);
            break;

        case 3: // ecran titre du niveau 2 -> initialisation des murs du niveau 2

            // ligne 1
            init_sprite(&(world->walls_level_2[0]), 0, 64, 6*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 6x2
            // ligne 2
            init_sprite(&(world->walls_level_2[1]), 0, -200, 3*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 3x2
            init_sprite(&(world->walls_level_2[2]), 236, -168, 2*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 2x3
            // ligne 3
            init_sprite(&(world->walls_level_2[3]), 76, -432, 7*METEORITE_SIZE, 4*METEORITE_SIZE); // mur droite 7x4
            // ligne 4
            init_sprite(&(world->walls_level_2[4]), 0, -632, 2*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 2x3
            init_sprite(&(world->walls_level_2[5]), 172, -600, 4*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 4x2
            // ligne 5 
            init_sprite(&(world->walls_level_2[6]), 76, -800, 7*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 7x2
            // ligne 6 
            init_sprite(&(world->walls_level_2[7]), 0, -1000, 5*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 5x3 
            // ligne 7 
            init_sprite(&(world->walls_level_2[8]), 0, -1200, 3*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 3x3
            init_sprite(&(world->walls_level_2[9]), 236, -1200, 2*METEORITE_SIZE, 3*METEORITE_SIZE); // mur droite 2x3
            // ligne 8
            init_sprite(&(world->walls_level_2[10]), 108, -1400, 6*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 6x2
            // ligne 9 
            init_sprite(&(world->walls_level_2[11]), 0, -1600, 7*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 7x2
            // ligne 10 
            init_sprite(&(world->walls_level_2[12]), 0, -1800, 2*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 2x3
            init_sprite(&(world->walls_level_2[13]), 172, -1800, 4*METEORITE_SIZE, 3*METEORITE_SIZE); // mur droite 4x3
            // ligne 11 
            init_sprite(&(world->walls_level_2[14]), 0, -2000, 5*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 5x3
            // ligne 12 
            init_sprite(&(world->walls_level_2[15]), 0, -2200, 4*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 4x2
            init_sprite(&(world->walls_level_2[16]), 236, -2150, 2*METEORITE_SIZE, 3*METEORITE_SIZE); // mur droite 2x3
            // ligne 13
            init_sprite(&(world->walls_level_2[17]), 0, -2450, 2*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 2x2
            init_sprite(&(world->walls_level_2[18]), 128, -2500, 1*METEORITE_SIZE, 3*METEORITE_SIZE); // mur centre 1x3
            init_sprite(&(world->walls_level_2[19]), 236, -2450, 2*METEORITE_SIZE, 4*METEORITE_SIZE); // mur droite 2x4
            // ligne 14
            init_sprite(&(world->walls_level_2[20]), 0, -2700, 7*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 7x3
            // ligne 15
            init_sprite(&(world->walls_level_2[21]), 0, -2900, 3*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 3x3
            init_sprite(&(world->walls_level_2[22]), 140, -2900, 5*METEORITE_SIZE, 3*METEORITE_SIZE); // mur droite 5x3
            // ligne 16
            init_sprite(&(world->walls_level_2[23]), 55, -3100, 6*METEORITE_SIZE, 3*METEORITE_SIZE); // mur centre 6x3
            // lignes 17 - 18
            init_sprite(&(world->walls_level_2[24]), 0, -3250, 3*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 3x2
            init_sprite(&(world->walls_level_2[25]), 188, -3300, 2* METEORITE_SIZE, 1*METEORITE_SIZE); // mur centre-droite 2x3
            init_sprite(&(world->walls_level_2[26]), 268, -3420, 1*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 1x2
            init_sprite(&(world->walls_level_2[27]), 64, -3500, 4*METEORITE_SIZE, 4*METEORITE_SIZE); // mur centre-gauche 4x4
            // ligne 19
            init_sprite(&(world->walls_level_2[28]), 0, -3700, 8*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 8x2
            // ligne 20 
            init_sprite(&(world->walls_level_2[29]), 0, -3900, 2*METEORITE_SIZE, 3*METEORITE_SIZE); // mur gauche 2x2
            init_sprite(&(world->walls_level_2[30]), 108, -3900, 6*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 6x2
            // ligne 21 
            init_sprite(&(world->walls_level_2[31]), 54, -4100, 6*METEORITE_SIZE, 1*METEORITE_SIZE); // mur centre 6x1
            // ligne 22
            init_sprite(&(world->walls_level_2[32]), 0, -4300, 7*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 7x2
            // ligne 23
            init_sprite(&(world->walls_level_2[33]), 0, -4600, 3*METEORITE_SIZE, 4*METEORITE_SIZE); // mur gauche 3x4
            init_sprite(&(world->walls_level_2[34]), 204, -4486, 3*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 3x2
            // ligne 24
            init_sprite(&(world->walls_level_2[35]), 44, -4750, 8*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 8x2
            // ligne 25
            init_sprite(&(world->walls_level_2[36]), 0, -5150, 3*METEORITE_SIZE, 6*METEORITE_SIZE); // mur gauche 3x6
            init_sprite(&(world->walls_level_2[37]), 236, -5150, 2*METEORITE_SIZE, 6*METEORITE_SIZE); // mur droite 2x6
            // ligne 26
            init_sprite(&(world->walls_level_2[38]), 0, -5350, 6*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 6x2
            // ligne 27
            init_sprite(&(world->walls_level_2[39]), 0, -5750, 2*METEORITE_SIZE, 5*METEORITE_SIZE); // mur gauche 2x5
            init_sprite(&(world->walls_level_2[40]), 140, -5750, 5*METEORITE_SIZE, 5*METEORITE_SIZE); // mur droite 5x5
            // lignes 28-29-30
            init_sprite(&(world->walls_level_2[41]), 130, -5900, 2*METEORITE_SIZE, 2*METEORITE_SIZE); // mur centre 2x2
            init_sprite(&(world->walls_level_2[42]), 204, -6000, 3*METEORITE_SIZE, 2*METEORITE_SIZE); // mur droite 3x2
            init_sprite(&(world->walls_level_2[43]), 0, -6100, 1*METEORITE_SIZE, 5*METEORITE_SIZE); // mur gauche 1x5
            init_sprite(&(world->walls_level_2[44]), 150, -6150, 4*METEORITE_SIZE, 4*METEORITE_SIZE); // mur centre-droite 4x4
            init_sprite(&(world->walls_level_2[45]), 50, -6300, 2*METEORITE_SIZE, 2*METEORITE_SIZE); // mur gauche 2x2
            init_sprite(&(world->walls_level_2[46]), 200, -6300, 1*METEORITE_SIZE, 1*METEORITE_SIZE); // mur droite 1x1
            // ligne 31
            init_sprite(&(world->walls_level_2[47]), 38, -6450, 7*METEORITE_SIZE, 2*METEORITE_SIZE); // mur centre 7x2
            // ligne 32
            init_sprite(&(world->walls_level_2[48]), 0, -6900, 3*METEORITE_SIZE, 8*METEORITE_SIZE); // mur gauche 3x8
            init_sprite(&(world->walls_level_2[49]), 204, -6900, 3*METEORITE_SIZE, 8*METEORITE_SIZE); // mur droite 3x8
            break;
    }
}

void init_ovnis(world_t* world){

    switch(world->game_status){
        case 0: // au debut du jeu -> initialisation des ovnis du niveau 1

            // ligne de 3 ovnis avant la ligne d'arrivée
            init_sprite(&(world->ovnis_level_1[0]),110,-810,OVNI_WIDTH,OVNI_HEIGHT);
            init_sprite(&(world->ovnis_level_1[1]),137,-810,OVNI_WIDTH,OVNI_HEIGHT);
            init_sprite(&(world->ovnis_level_1[2]),164,-810,OVNI_WIDTH,OVNI_HEIGHT);
            break;

        case 3: // à l'écran titre du niveau 2 -> initialisation des ovnis du niveau 2

            // ligne 1
            init_sprite(&(world->ovnis_level_2[0]), 219, 80, OVNI_WIDTH, OVNI_HEIGHT); // a droite
            init_sprite(&(world->ovnis_level_2[1]), 246, 80, OVNI_WIDTH, OVNI_HEIGHT); // pareil
            // ligne 3
            init_sprite(&(world->ovnis_level_2[2]), 24, -360, OVNI_WIDTH, OVNI_HEIGHT); // a gauche
            // ligne 5
            init_sprite(&(world->ovnis_level_2[3]), 24, -790, OVNI_WIDTH, OVNI_HEIGHT); // a gauche
            // ligne 6
            init_sprite(&(world->ovnis_level_2[4]), 193, -960, OVNI_WIDTH, OVNI_HEIGHT); // a droite
            init_sprite(&(world->ovnis_level_2[5]), 220, -960, OVNI_WIDTH, OVNI_HEIGHT); // pareil a coté
            // ligne 8
            init_sprite(&(world->ovnis_level_2[6]), 40, -1360, OVNI_WIDTH, OVNI_HEIGHT); // a gauche
            // ligne 10
            init_sprite(&(world->ovnis_level_2[7]), 91, -1750, OVNI_WIDTH, OVNI_HEIGHT); // au centre
            init_sprite(&(world->ovnis_level_2[8]), 118, -1750, OVNI_WIDTH, OVNI_HEIGHT); // pareil a coté
            // ligne 11
            init_sprite(&(world->ovnis_level_2[9]), 203, -1960, OVNI_WIDTH, OVNI_HEIGHT); // a droite
            init_sprite(&(world->ovnis_level_2[10]), 230, -1960, OVNI_WIDTH, OVNI_HEIGHT); // pareil
            // ligne 13
            init_sprite(&(world->ovnis_level_2[11]), 184, -2455, OVNI_WIDTH, OVNI_HEIGHT); // centre droite
            // ligne 16
            init_sprite(&(world->ovnis_level_2[12]), 14, -3060, OVNI_WIDTH, OVNI_HEIGHT); // gauche
            init_sprite(&(world->ovnis_level_2[13]), 261, -3060, OVNI_WIDTH, OVNI_HEIGHT); // droite
            // ligne 17-18
            init_sprite(&(world->ovnis_level_2[14]), 18, -3450, OVNI_WIDTH, OVNI_HEIGHT); // gauche  
            // ligne 20
            init_sprite(&(world->ovnis_level_2[15]), 72, -3865, OVNI_WIDTH, OVNI_HEIGHT); // centre
            // ligne 21
            init_sprite(&(world->ovnis_level_2[16]), 13, -4095, OVNI_WIDTH, OVNI_HEIGHT); // gauche
            init_sprite(&(world->ovnis_level_2[17]), 260, -4095, OVNI_WIDTH, OVNI_HEIGHT); // droite
            // ligne 23
            init_sprite(&(world->ovnis_level_2[18]), 136, -4530, OVNI_WIDTH, OVNI_HEIGHT); // centre
            init_sprite(&(world->ovnis_level_2[19]), 136, -4570, OVNI_WIDTH, OVNI_HEIGHT); // pareil au dessus
            // ligne 25
            init_sprite(&(world->ovnis_level_2[20]), 152, -5000, OVNI_WIDTH, OVNI_HEIGHT); // centre
            init_sprite(&(world->ovnis_level_2[21]), 152, -5063, OVNI_WIDTH, OVNI_HEIGHT); // pareil au dessus
            init_sprite(&(world->ovnis_level_2[22]), 152, -5126, OVNI_WIDTH, OVNI_HEIGHT); // pareil au dessus
            // ligne 27
            init_sprite(&(world->ovnis_level_2[23]), 88, -5680, OVNI_WIDTH, OVNI_HEIGHT); // centre
            // ligne 28-29-30
            init_sprite(&(world->ovnis_level_2[24]), 49, -5985, OVNI_WIDTH, OVNI_HEIGHT); // gauche
            init_sprite(&(world->ovnis_level_2[25]), 108, -6030, OVNI_WIDTH, OVNI_HEIGHT); // pareil en zigzag
            init_sprite(&(world->ovnis_level_2[26]), 76, -6075, OVNI_WIDTH, OVNI_HEIGHT); // pareil en zigzag
            // ligne 31
            init_sprite(&(world->ovnis_level_2[27]), 5, -6425, OVNI_WIDTH, OVNI_HEIGHT); // gauche
            init_sprite(&(world->ovnis_level_2[28]), 267, -6425, OVNI_WIDTH, OVNI_HEIGHT); // droite
            // ligne 32 (fin)
            init_sprite(&(world->ovnis_level_2[29]), 136, -6875, OVNI_WIDTH, OVNI_HEIGHT); // centre
            break;
    }
}

void init_data(world_t* world){
    
    // initialisation du vaisseau
    init_sprite(&(world->spacecraft), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);

    switch(world->game_status){

        case 0: // niveau 1
            init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT_1, SCREEN_WIDTH, 20); // FINISH_LINE_HEIGHT_1
            break;

        case 3: // niveau 2
            init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT_2, SCREEN_WIDTH, 20); // FINISH_LINE_HEIGHT_2
            break;
    }

    // initialisation des murs de météorites
    init_walls(world);

    // initialisation des ovnis
    init_ovnis(world);

    // initialisation de la limite invisible
    init_sprite(&(world->invisible_limit), 0, INVISIBLE_LIMIT_HEIGHT, SCREEN_WIDTH, 20);

    // initialisation des missiles en dehors de l'écran (inactifs)
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
        if(make_disappear==1){
            sp1->x = -10000; // déplace le sprite en dehors de l'écran
        } else if(make_disappear==2){ // si il est a 2
            sp1->x = -10000; // déplace les deux sprites
            sp2->x = -10000;
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

int is_finished_game(world_t* world){
    return world->game_status==-1;
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

void update_walls(world_t* world){
    switch(world->game_status){

        case 2: // gameplay du niveau 1

            // pour chaque indice du tableau de murs
            for(int indice=0; indice<6; indice++){
                // le mur de météorites descend de vy
                world->walls_level_1[indice].y += world->vy;
                // gestion des collisions entre le vaisseau et le mur (disparition + défaite)
                handle_sprites_collision(world,&(world->spacecraft),&(world->walls_level_1[indice]),1,0);
            }
            break;

        case 4: // gameplay du niveau 2

            // pour chaque indice du tableau de murs
            for(int indice=0; indice<50; indice++){
                // le mur de météorites descend de vy
                world->walls_level_2[indice].y += world->vy;
                // gestion des collisions entre le vaisseau et le mur (disparition + défaite)
                handle_sprites_collision(world,&(world->spacecraft),&(world->walls_level_2[indice]),1,0);
            }
            break;
    }
}


void update_ovnis(world_t* world){
    switch(world->game_status){

        case 2: // gameplay du niveau 1

            // pour chaque indice du tableau d'ovnis
            for(int indice=0; indice<3; indice++){
                // l'ovni descend de vy
                world->ovnis_level_1[indice].y += world->vy;
                // gestion des collisions entre le vaisseau et l'ovni (disparition + défaite)
                handle_sprites_collision(world,&(world->spacecraft),&(world->ovnis_level_1[indice]),1,0);
            }
            break;

        case 4: // gameplay du niveau 2

            // pour chaque indice du tableau d'ovnis
            for(int indice=0; indice<30; indice++){
                // l'ovni descend de vy
                world->ovnis_level_2[indice].y += world->vy;
                // gestion des collisions entre le vaisseau et l'ovni (disparition + défaite)
                handle_sprites_collision(world,&(world->spacecraft),&(world->ovnis_level_2[indice]),1,0);
            }
            break;
    }
}

void shoot_missile(world_t* world){

    // pour chaque indice de missile possible dans le tableau
    for(int i=0; i<10; i++){
        // si le spot est disponible
        if(world->missiles[i].x == -10000){
            // tir du missile
            init_sprite(&(world->missiles[i]), world->spacecraft.x+(SHIP_SIZE/2 - MISSILE_WIDTH/2), world->spacecraft.y-MISSILE_HEIGHT, MISSILE_WIDTH, MISSILE_HEIGHT);
            // réinitialisation du cooldown
            world->missileCooldown = MISSILE_COOLDOWN; 
            break; // le missile est tiré
        }
    }
}

void update_missiles(world_t* world){

    // pour chaque missile
    for(int i=0; i<10; i++){
        world->missiles[i].y -= MISSILE_SPEED; // le missile monte de sa vitesse

        switch(world->game_status){

            case 2: // gameplay du niveau 1

                // pour chaque mur du niveau 1
                for(int j=0; j<6; j++){
                    // gestion de la collision entre le missile et le mur (disparition)
                    handle_sprites_collision(world,&(world->missiles[i]),&(world->walls_level_1[j]),1,-1);
                }

                // pour chaque ovni du niveau 1
                for(int k=0; k<3; k++){
                    // gestion de la collision entre l'ovni et le missile (disparition des deux)
                    handle_sprites_collision(world,&(world->ovnis_level_1[k]),&(world->missiles[i]),2,-1);
                }
                break;

            case 4: // gameplay du niveau 2

                // pour chaque mur du niveau 2
                for(int j=0; j<50; j++){
                    // gestion de la collision entre le missile et le mur (disparition)
                    handle_sprites_collision(world,&(world->missiles[i]),&(world->walls_level_2[j]),1,-1);
                }

                // pour chaque ovni du niveau 2
                for(int k=0; k<30; k++){
                    // gestion de la collision entre l'ovni et le missile (disparition des deux)
                    handle_sprites_collision(world,&(world->ovnis_level_2[k]),&(world->missiles[i]),2,-1);
                }
                
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

void update_data(world_t* world, ressources_t* ressources){

    // mise à jour de la position de la ligne d'arrivée + gestion des collisions
    update_finishline(world);

    // mise à jour de la position des murs + gestion des collisions
    update_walls(world);

    // mise à jour de la position des ovnis + gestion des collisions
    update_ovnis(world);

    // mise à jour de la position du missile + gestion des collisions
    update_missiles(world);
}