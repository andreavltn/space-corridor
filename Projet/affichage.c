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
    ressources->vaisseau = load_image("ressources/spaceship.bmp",renderer);
    ressources->ligne_arrivee = load_image("ressources/finish_line.bmp",renderer);
    ressources->meteorite = load_image("ressources/meteorite.bmp",renderer);
    ressources->missile = load_image("ressources/missile.bmp",renderer);
    ressources->ovni = load_image("ressources/ovni.bmp",renderer);
    ressources->font = load_font("ressources/arial.ttf",14); 
}

void apply_walls(ressources_t* ressources, SDL_Renderer* renderer, world_t* world){
    // pour chaque mur
    for(int h=0; h<6;h++){
        // pour chaque spot horizontal de météorite
        for(int i=0; i<world->walls[h].w; i+=32){
            // pour chaque spot vertical de météorite 
            for(int j=0; j<world->walls[h].h; j+=32){
                apply_texture(ressources->meteorite, renderer, world->walls[h].x + i, world->walls[h].y + j);
            }
        }   
    } 
}

void apply_sprite(SDL_Renderer* renderer, ressources_t* ressources, world_t* world){
  
    // texture du vaisseau
    apply_texture(ressources->vaisseau, renderer, world->vaisseau.x, world->vaisseau.y);
    
    // texture de la ligne d'arrivée
    apply_texture(ressources->ligne_arrivee, renderer, world->ligne_arrivee.x, world->ligne_arrivee.y);
    
    // texture du mur de météorites (quadrillage de météorites)
    apply_walls(ressources, renderer, world);

    // texture des missiles
    for(int i=0; i<10; i++){
        apply_texture(ressources->missile, renderer, world->missiles[i].x, world->missiles[i].y);
    }
  
} 

void apply_background(SDL_Renderer* renderer, ressources_t* ressources){
    if(ressources->background != NULL){
        apply_texture(ressources->background, renderer, 0, 0);
    }
}

void apply_texts(SDL_Renderer* renderer, world_t* world, ressources_t* ressources){
    char texte[15];
    sprintf(texte, "Time: %.1f", world->time); 
    apply_text(renderer,10,10,90,50,texte,ressources->font);

    if(is_finished(world)){
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
       
    // application des ressources dans le renderer
    apply_background(renderer, ressources);
    apply_sprite(renderer, ressources, world);

    // affichage du timer en haut à gauche, et du message de fin en cas de win/lose
    apply_texts(renderer,world,ressources);
  
    // on met à jour l'écran
    update_screen(renderer);
}
 
void clean_ressources(ressources_t* ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->vaisseau);
    clean_texture(ressources->ligne_arrivee);
    clean_texture(ressources->meteorite);
    clean_texture(ressources->missile);
    clean_font(ressources->font);    
}