/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "logique.h"
#include "affichage.h"

/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
  clean_data(world);
  clean_textures(textures);
  clean_sdl(renderer,window);
}

/**
 * \brief Fonction de test des coordonnées du sprite
 */
void print_sprite(sprite_t *sprite){
  printf("x : %d\n",sprite->x); // Affichage de la position x du sprite
  printf("y : %d\n",sprite->y); // Affichage de la position y du sprite 
  printf("w : %d\n",sprite->w); // Affichage de la largeur du sprite
  printf("h : %d\n",sprite->h); // Affichage de la hauteur du sprite
}
 
/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[] ){
  SDL_Event event;
  world_t world;
  textures_t textures;
  SDL_Renderer *renderer;
  SDL_Window *window;

  //initialisation du jeu
  init(&window,&renderer,&textures,&world);
  while(!is_game_over(&world)){ // tant que le jeu n'est pas fini
         
    //gestion des évènements
    handle_events(&event,&world);
         
    //mise à jour des données liée à la physique du monde
    update_data(&world,&textures);
         
    //rafraichissement de l'écran
    refresh_graphics(renderer,&world,&textures);
         
    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(10);
  }
     
  //nettoyage final
  clean(window,renderer,&textures,&world);
    
  return 0;
}
 