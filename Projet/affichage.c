/**
 * \file affichage_jeu.c
 * \brief Contient l'ensemble des fonctions relatives à l'affichage des éléments du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "affichage.h"
#include "logique.h"
#include "constantes.h"

void init_textures(SDL_Renderer* renderer, ressources_t* textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau=load_image("ressources/spaceship.bmp",renderer);
    textures->ligne_arrivee=load_image("ressources/finish_line.bmp",renderer);
    textures->meteorite=load_image("ressources/meteorite.bmp",renderer);
    textures->font = load_font("ressources/arial.ttf",14); 
}

void init(SDL_Window** window, SDL_Renderer** renderer, ressources_t* textures, world_t* world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_textures(*renderer,textures);
}

void apply_walls(ressources_t* textures, SDL_Renderer* renderer, world_t* world){
    // pour chaque mur
    for (int h=0; h<6;h++){
        // pour chaque spot horizontal de météorite
        for(int i=0; i<world->wall[h].w; i+=32){
            // pour chaque spot vertical de météorite 
            for(int j=0; j<world->wall[h].h; j+=32){
                apply_texture(textures->meteorite, renderer, world->wall[h].x + i, world->wall[h].y + j);
            }
        }   
    } 
}

void apply_sprite(SDL_Renderer* renderer, ressources_t* textures, world_t* world){
  
    // texture du vaisseau
    apply_texture(textures->vaisseau, renderer, world->vaisseau.x, world->vaisseau.y);
    
    // texture de la ligne d'arrivée
    apply_texture(textures->ligne_arrivee, renderer, world->ligne_arrivee.x, world->ligne_arrivee.y);
    
    // texture du mur de météorites (quadrillage de météorites)
    apply_walls(textures, renderer, world);
  
} 

void apply_background(SDL_Renderer* renderer, ressources_t* textures){
    if(textures->background != NULL){
        apply_texture(textures->background, renderer, 0, 0);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t* world, ressources_t* textures){
    // on vide le renderer
    clear_renderer(renderer);
       
    // application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures, world);

    // application du temps en haut à gauche
    char texte[10];
    sprintf(texte, "Time: %.1f", world->time); 
    apply_text(renderer,10,10,90,50,texte,textures->font);

    if(is_finished(world)){
        if(world->gameover){
            apply_text(renderer,SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-25,100,50,"You lost !",textures->font);
        } else if(world->win){
            char texte_win[50];
            sprintf(texte_win, "You finished in %.1fs !", world->time); 
            apply_text(renderer,SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-25,200,50,texte_win,textures->font);
        }
    }
  
    // on met à jour l'écran
    update_screen(renderer);
}

void clean_data(world_t* world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}
    
void clean_textures(ressources_t* textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);
    clean_font(textures->font);    
}