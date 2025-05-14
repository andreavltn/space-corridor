/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "logique.h"
#include "affichage.h"
#include "constantes.h"

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des ressources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources du jeu
 * \param world le monde du jeu 
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world){
  init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
  init_ttf();
  init_data(world);
  init_textures(*renderer,ressources);
}

/**
 * \brief fonction qui gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event, world_t* world){
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
              if(world->vaisseau.x + world->vaisseau.w + MOVING_STEP < SCREEN_WIDTH) {
                  world->vaisseau.x+=MOVING_STEP;
              }
          }

          // touche gauche/q
          if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q){
              if(world->vaisseau.x - MOVING_STEP > 0){
                  world->vaisseau.x-=MOVING_STEP;
              }
          }

          // haut/z
          if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z){
              // si la vitesse est inférieure à 2 (1.9 pour la précision des flottants)
              if(world->vy < 1.9){
                  // augmentation de la vitesse du jeu
                  world->vy+=0.1;
              }
          }

          // bas/s
          if(event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
              // si la vitesse est supérieure à 0.5
              if(world->vy > 0.5){
                  // réduction de la vitesse du jeu
                  world->vy-=0.1;
              }
          }
          
          // barre espace
          if(event->key.keysym.sym == SDLK_SPACE){
            shoot_missile(world);
          }    
      }        
  }
}

/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources
 * \param world le monde
 */
void clean(SDL_Window* window, SDL_Renderer* renderer, ressources_t* ressources, world_t* world){
  clean_ressources(ressources);
  clean_sdl(renderer,window);
}

/**
 * \brief Fonction de test des coordonnées du sprite
 */
void print_sprite(sprite_t* sprite){
  printf("x : %f\n",sprite->x); // Affichage de la position x du sprite
  printf("y : %f\n",sprite->y); // Affichage de la position y du sprite 
  printf("w : %f\n",sprite->w); // Affichage de la largeur du sprite
  printf("h : %f\n",sprite->h); // Affichage de la hauteur du sprite
}
 
/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[] ){
  SDL_Event event;
  world_t world;
  ressources_t ressources;
  SDL_Renderer *renderer;
  SDL_Window *window;

  unsigned int lastTimeCheck = 0;
  unsigned int lastMissileCheck = 0;
  unsigned int currentTime;

  // initialisation du jeu
  init(&window,&renderer,&ressources,&world);
  while(!is_finished(&world)){ // tant que le jeu n'est pas fini
    currentTime = SDL_GetTicks();
         
    // gestion des évènements
    handle_events(&event,&world);
         
    // mise à jour des données liée à la physique du monde
    update_data(&world,&ressources);
    
    // mise à jour du temps écoulé
    update_time(&world, currentTime, &lastTimeCheck);

    // mise à jour du cooldown du tir de missile
    update_missileCooldown(&world,currentTime, &lastMissileCheck);

    // rafraichissement de l'écran
    refresh_graphics(renderer,&world,&ressources);
    
    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(10);
  }

  // pause de 3s a la fin du jeu
  pause(3000);
     
  // nettoyage final
  clean(window,renderer,&ressources,&world);
  
  return 0;
}
 