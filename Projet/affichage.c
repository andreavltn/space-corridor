/**
 * \file affichage.c
 * \brief Contient l'ensemble des fonctions relatives à l'affichage des éléments du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "affichage.h"
#include "logique.h"
#include "constantes.h"

void init_textures(SDL_Renderer* renderer, ressources_t* ressources){
    ressources->start_screen = load_image("ressources/start_screen.bmp",renderer);
    ressources->splash_text = load_image("ressources/splash_text.bmp",renderer);
    ressources->background = load_image("ressources/space-background.bmp",renderer);
    ressources->background2 = load_image("ressources/space-background_2.bmp",renderer);
    ressources->level_1_screen = load_image("ressources/level_1_screen.bmp",renderer);
    ressources->level_2_screen = load_image("ressources/level_2_screen.bmp",renderer);
    ressources->spacecraft = load_image("ressources/spaceship.bmp",renderer);
    ressources->ligne_arrivee = load_image("ressources/finish_line.bmp",renderer);
    ressources->meteorite = load_image("ressources/meteorite.bmp",renderer);
    ressources->missile = load_image("ressources/missile.bmp",renderer);
    ressources->ovni = load_image("ressources/ovni.bmp",renderer);
    ressources->font = load_font("ressources/arial.ttf",14); 
}

void apply_walls_level_1(ressources_t* ressources, SDL_Renderer* renderer, world_t* world){

    // pour les 6 murs du niveau 1
    for(int indice=0; indice<6; indice++){
        // pour chaque spot horizontal de météorite
        for(int i=0; i<world->walls_level_1[indice].w; i+=32){
            // pour chaque spot vertical de météorite 
            for(int j=0; j<world->walls_level_1[indice].h; j+=32){
                apply_texture(ressources->meteorite, renderer, world->walls_level_1[indice].x + i, world->walls_level_1[indice].y + j);
            }
        }   
    }
}

void apply_walls_level_2(ressources_t* ressources, SDL_Renderer* renderer, world_t* world){
    // PLACEHOLDER
}

void apply_ovnis_level_1(ressources_t* ressources, SDL_Renderer* renderer, world_t* world){
    // pour les 3 ovnis du niveau 1
    for(int indice=0; indice<3; indice++){
        apply_texture(ressources->ovni, renderer, world->ovnis_level_1[indice].x, world->ovnis_level_1[indice].y);
    }
}

void apply_ovnis_level_2(ressources_t* ressources, SDL_Renderer* renderer, world_t* world){
    // pour les 30 ovnis du niveau 2
    for(int indice=0; indice<30; indice++){
        apply_texture(ressources->ovni, renderer, world->ovnis_level_2[indice].x, world->ovnis_level_2[indice].y);
    }
}

void apply_sprites_level_1(SDL_Renderer* renderer, ressources_t* ressources, world_t* world){
    
    // texture du vaisseau
    apply_texture(ressources->spacecraft, renderer, world->spacecraft.x, world->spacecraft.y);
    
    // texture de la ligne d'arrivée
    apply_texture(ressources->ligne_arrivee, renderer, world->ligne_arrivee.x, world->ligne_arrivee.y);
    
    // texture des murs de météorites (quadrillage de météorites)
    apply_walls_level_1(ressources, renderer, world);

    // texture des ovnis
    apply_ovnis_level_1(ressources, renderer, world);

    // texture des missiles
    for(int i=0; i<10; i++){
        apply_texture(ressources->missile, renderer, world->missiles[i].x, world->missiles[i].y);
    }
  
}

void apply_sprites_level_2(SDL_Renderer* renderer, ressources_t* ressources, world_t* world){
    // PLACEHOLDER
}

void apply_startscreen(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->start_screen != NULL){
        apply_texture(ressources->start_screen, renderer, 0, 0);
    }
}

void apply_background_level_1(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->background != NULL){
        apply_texture(ressources->background, renderer, 0, 0);
    }
}

void apply_background_level_2(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->background2 != NULL){
        apply_texture(ressources->background2, renderer, 0, 0);
    }
}

void apply_level_1_screen(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->level_1_screen != NULL){
        apply_texture(ressources->level_1_screen, renderer, 0, 0);
    }
}

void apply_level_2_screen(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->level_2_screen != NULL){
        apply_texture(ressources->level_2_screen, renderer, 0, 0);
    }
}

void apply_texts(SDL_Renderer* renderer, world_t* world, ressources_t* ressources){
    char texte[15];
    sprintf(texte, "Time: %.1f", world->time); 
    apply_text(renderer,10,10,90,50,texte,ressources->font);

    if(is_finished_level(world)){
        if(world->gameover){// si on perd -> message de lose
            // le texte "You lost !" fait 100x50, placé au milieu de l'écran 
            apply_text(renderer,SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-25,100,50,"You lost !",ressources->font);
        } else if(world->win){// si on gagne -> message de win 
            char texte_win[50];
            sprintf(texte_win, "You finished in %.1fs !", world->time);
            // le texte "You finished in Xs !" fait 200x50, placé au milieu de l'écran  
            apply_text(renderer,SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-25,200,50,texte_win,ressources->font);
        }
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t* world, ressources_t* ressources){
    // on vide le renderer
    clear_renderer(renderer);

    // en fonction du stage du jeu
    switch(world->game_status){ 
        case 0: // ECRAN TITRE
            
            apply_startscreen(renderer, ressources); // le background avec le titre
            apply_texture(ressources->splash_text, renderer, world->splash_text.x, world->splash_text.y); // le splash_text
            break;

        case 1: // ECRAN NIVEAU 1

            apply_level_1_screen(renderer,ressources); // ecran titre niveau 1
            break;

        case 2: // GAMEPLAY NIVEAU 1

            apply_background_level_1(renderer, ressources); // background bleu
            apply_sprites_level_1(renderer, ressources, world); // les sprites du niveau 1
            apply_texts(renderer,world,ressources); // timer + msg win/gameover
            break;

        case 3: // ECRAN NIVEAU 2

            apply_level_2_screen(renderer,ressources); // ecran titre du niveau 2
            break;

        case 4: // GAMEPLAY NIVEAU 2

            apply_background_level_2(renderer, ressources); // background rouge
            apply_sprites_level_2(renderer, ressources, world); // les sprites du niveau 2
            apply_texts(renderer,world,ressources); // timer + msg win/gameover
            break;
    }


  
    // on met à jour l'écran
    update_screen(renderer);
}
 
void clean_ressources(ressources_t* ressources){
    clean_texture(ressources->start_screen);
    clean_texture(ressources->splash_text);
    clean_texture(ressources->background);
    clean_texture(ressources->background2);
    clean_texture(ressources->level_1_screen);
    clean_texture(ressources->level_2_screen);
    clean_texture(ressources->spacecraft);
    clean_texture(ressources->ligne_arrivee);
    clean_texture(ressources->meteorite);
    clean_texture(ressources->missile);
    clean_texture(ressources->ovni);
    clean_font(ressources->font);    
}