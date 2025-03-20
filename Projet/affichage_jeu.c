/**
 * \file affichage_jeu.c
 * \brief Contient l'ensemble des fonctions relatives à l'affichage des éléments du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "constantes.h"
#include "affichage_jeu.h"

void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}

void init_data(world_t * world){
    // initialisation du vaisseau (milieu de l'écran, à 32 pixels du bas, en 32x32)
    init_sprite(&(world->vaisseau), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
  
    // initialisation de la ligne d'arrivée (milieu de l'écran, à 10 pixels du haut, LARGEUR_ECRANx100)
    init_sprite(&(world->ligne_arrivee), 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 100);
  
    // initialisation du mur de météorites -> position de la météorite en haut à droite
    // (pour que le mur soit centré verticalement et horizontalement, avec le nombre de météorites choisi)
    init_sprite(&(world->mur_meteorite), 
    SCREEN_WIDTH/2-(METEORITE_SIZE*NBR_METEORITE_WIDTH)/2, SCREEN_HEIGHT/2-(METEORITE_SIZE*NBR_METEORITE_HEIGHT)/2, 
    METEORITE_SIZE, METEORITE_SIZE);
  
    // vitesse de la ligne d'arrivée
    world->vy = INITIAL_SPEED;
  
    // gameover
    world->gameover = 0; 
}

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau=load_image("ressources/spaceship.bmp",renderer);
    textures->ligne_arrivee=load_image("ressources/finish_line.bmp",renderer);
    textures->meteorite=load_image("ressources/meteorite.bmp",renderer);     
}

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}

void apply_sprite(SDL_Renderer *renderer , textures_t *textures , world_t * world ){
  
    // texture du vaisseau
    apply_texture(textures->vaisseau, renderer, world->vaisseau.x, world->vaisseau.y);
    
    // texture de la ligne d'arrivée
    apply_texture(textures->ligne_arrivee, renderer, world->ligne_arrivee.x, world->ligne_arrivee.y);
  
    // texture du mur de météorites (quadrillage de météorites)
    for(int i=0; i<NBR_METEORITE_HEIGHT; i++){ 
        for(int j=0; j<NBR_METEORITE_WIDTH; j++){
            apply_texture(textures->meteorite, renderer, world->mur_meteorite.x + (32*j), world->mur_meteorite.y + (32*i));
        }
    }
}
  
void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
        apply_texture(textures->background, renderer, 0, 0);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures){
    // on vide le renderer
    clear_renderer(renderer);
       
    // application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures, world);
  
    // on met à jour l'écran
    update_screen(renderer);
}

void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}
    
void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);  
}

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}