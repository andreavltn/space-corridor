/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Valentini Andréa & Viale Romain
 */

#include "logique.h"
#include "affichage.h"
#include "constantes.h"

/**
 * \brief Fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des ressources, initialisation des données
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
 * \brief Fonction qui gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event, world_t* world){
  Uint8 *keystates;

  while(SDL_PollEvent(event)){

    // si l'utilisateur a cliqué sur le X de la fenêtre
    if(event->type == SDL_QUIT) {
      // fin du jeu
      world->gameover = 1;
    }

    // si une touche est appuyée
    if(event->type == SDL_KEYDOWN){

      // touche echap
      if(event->key.keysym.sym == SDLK_ESCAPE){
        world->gameover = 1;
      }

      // si le jeu n'a pas encore commencé, espace pour lancer le jeu
      if (!world->game_started) {
          if(event->key.keysym.sym == SDLK_SPACE){
              world->game_started = 1; 
          }

      // sinon, contrôle normal des touches
      } else {

          // touche droite/d
          if(event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d){
            if(world->spacecraft.x + world->spacecraft.w + MOVING_STEP < SCREEN_WIDTH) {
              world->spacecraft.x+=MOVING_STEP;
            }
          }

          // touche gauche/q
          if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q){
            if(world->spacecraft.x - MOVING_STEP > 0){
              world->spacecraft.x-=MOVING_STEP;
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
            // si il n'y a pas de cooldown au tir de missile
            if(world->missileCooldown == 0){
              shoot_missile(world); // tirer un missile
              world->missileCooldown = MISSILE_COOLDOWN; // maj du cooldown
            }
          }
      }
    }
  }
}

/**
 * \brief Fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
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
 *  \brief Le programme principal qui lance et gère le déroulement du jeu
 */
int main(int argc, char* args[]){
  SDL_Event event;
  world_t world;
  ressources_t ressources;
  SDL_Renderer *renderer;
  SDL_Window *window;

  unsigned int gameStartTick = 0; // tick auquel le jeu a commencé
  unsigned int lastTimeCheck = 0; // dernier check du temps pour le timer
  unsigned int lastMissileCooldownCheck = 0; // dernier check du temps pour le cooldown du missile
  unsigned int timeSinceLaunch; // temps actuel (ms passées depuis le lancement du jeu)
  unsigned int actualTime; // temps réel

  // initialisation du jeu
  init(&window,&renderer,&ressources,&world);

  while(!is_finished(&world)){ // tant que le jeu n'est pas fini
    timeSinceLaunch = SDL_GetTicks();

    // gestion des évènements
    handle_events(&event,&world);

    // si le jeu n'a pas commencé
    if(!world.game_started) {

      // fait clignoter le texte "PRESS SPACE TO START!"
      blink_splash_text(&world,timeSinceLaunch);

    } else { // sinon le jeu a commencé

      // stocke le tick auquel le jeu a commencé (pour démarrer le timer à 0s une fois qu'on a appuyé sur start)
      if(gameStartTick==0){ // condition pour ne le faire qu'une seule fois
        gameStartTick = SDL_GetTicks();
      }

      // calcul du temps réel
      actualTime = timeSinceLaunch - gameStartTick;

      // mise à jour des données liées à la physique du monde
      update_data(&world,&ressources);

      // mise à jour du temps écoulé
      update_time(&world, actualTime, &lastTimeCheck);

      // mise à jour du cooldown restant du tir de missile
      update_missileCooldown(&world, actualTime, &lastMissileCooldownCheck);
    }

    // rafraichissement de l'écran 
    refresh_graphics(renderer,&world,&ressources);

    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(10);
  }

  // pause de 3s a la fin du jeu (si le jeu a été lancé)
  if(world.game_started){
    pause(3000);
  }

  // nettoyage final
  clean(window,renderer,&ressources,&world);

  return 0;
}