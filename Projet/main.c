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
  world->game_status = 0; // le jeu démarre au stage "0" (écran titre)
  init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT); // initialisation du SDL
  init_ttf(); // initialisation de la police TTF
  init_data(world); // initialisation des données (du niveau 1 ici)
  init_textures(*renderer,ressources); // initialisation des textures
}

/**
 * \brief Fait passer le jeu au niveau suivant
 * \param world les données du monde
 */   
void skip_to_next_stage(world_t* world){
  world->game_status++; // passage au stage suivant
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
      world->game_status = -1;
    }

    // si une touche est appuyée
    if(event->type == SDL_KEYDOWN){

      // ECHAP
      if(event->key.keysym.sym == SDLK_ESCAPE){
        world->game_status = -1; // on sort de la boucle de jeu
      }

      switch(world->game_status){

        case 0: // écran titre

          if(event->key.keysym.sym == SDLK_SPACE){ // si on appuie sur espace à l'écran titre
            skip_to_next_stage(world); // passe au stage suivant (titre du niveau 1)
            break;
          }

        case 2: // GAMEPLAY NIVEAU 1 et
        case 4: // GAMEPLAY NIVEAU 2

          // DROITE/D
          if(event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d){
            if(world->spacecraft.x + world->spacecraft.w + MOVING_STEP < SCREEN_WIDTH) {
              world->spacecraft.x+=MOVING_STEP;
            }
          }

          // GAUCHE/Q
          if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q){
            if(world->spacecraft.x - MOVING_STEP > 0){
              world->spacecraft.x-=MOVING_STEP;
            }
          }

          // HAUT/Z
          if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z){
            // si la vitesse est inférieure à 2 (borne supérieur, 1.9 pour la précision des flottants)
            if(world->vy < 1.9){
              // augmentation de la vitesse du jeu
              world->vy+=0.1;
            }
          }

          // BAS/Q
          if(event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
            // si la vitesse est supérieure à 0.5 (borne inférieur)
            if(world->vy > 0.5){
              // réduction de la vitesse du jeu
              world->vy-=0.1;
            }
          }

          // ESPACE
          if(event->key.keysym.sym == SDLK_SPACE){
            // si il n'y a pas de cooldown au tir de missile
            if(world->missileCooldown == 0){
              shoot_missile(world); // tirer un missile
              world->missileCooldown = MISSILE_COOLDOWN; // maj du cooldown
            }
          }
          break;
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
  clean_ressources(ressources); // nettoyage des ressources
  clean_sdl(renderer,window); // nettoyage de SDL
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
  
  unsigned int timeSinceLaunch; // temps actuel (ms passées depuis le lancement du jeu)
  unsigned int levelSwapTick = 0; // dernier check du temps pour le changement de stage
  unsigned int level_1_startTick = 0; // tick auquel le niveau 1 a commencé
  unsigned int level_2_startTick = 0; // tick auquel le niveau 2 a commencé
  unsigned int lastTimeCheck = 0; // dernier check du temps pour le timer en haut à gauche
  unsigned int lastMissileCooldownCheck = 0; // dernier check du temps pour le cooldown du missile
  unsigned int actualTime; // temps réel du niveau en cours

  // initialisation du jeu (et des données du niveau 1 en avance)
  init(&window,&renderer,&ressources,&world);

  // tant que le jeu n'est pas fini
  while(!is_finished_game(&(world))){ 

    // initialisation du compteur de ticks depuis le lancement du jeu
    timeSinceLaunch = SDL_GetTicks(); 

    // gestion des évènements
    handle_events(&event,&world);

    // en fonction du stage du jeu
    switch(world.game_status){

        case 0: // ECRAN TITRE -> clignottement du sprite "PRESS SPACE TO START"
        
          // fait clignoter le texte "PRESS SPACE TO START!"
          blink_splash_text(&world,timeSinceLaunch);
          break; 

        case 1: // ECRAN NIVEAU 1 -> affichage pendant TRANSITION_TIME, puis on passe au gameplay du niveau 1

          if(levelSwapTick == 0){ // conditionnelle pour ne le faire qu'une seule fois
            levelSwapTick = timeSinceLaunch; // stockage du tick auquel on arrive ici (pour compter le temps écoulé)
          }
   
          if(timeSinceLaunch - levelSwapTick > TRANSITION_TIME){ // si le TRANSITION_TIME s'est écoulé depuis le tick sauvegardé
            levelSwapTick = 0; // reset du tick pour le prochain écran titre
            skip_to_next_stage(&(world)); // passe au gameplay du niveau 1
          }
          break;

        case 2: // GAMEPLAY NIVEAU 1 -> mise à jour de tous les éléments et gestion de la logique du jeu

          if(level_1_startTick==0){ // conditionnelle pour ne le faire qu'une seule fois
            level_1_startTick = timeSinceLaunch; // stocke le tick auquel le niveau a commencé (pour que le timer démarre à 0s)
          }

          // calcul du temps réel (ticks totaux - ticks écoulés entre le lancement du jeu et début du niveau 1)
          actualTime = timeSinceLaunch - level_1_startTick;

          // tant que le niveau n'est pas terminé
          if(!is_finished_level(&(world))){

            // mise à jour des données liées à la physique du monde
            update_data(&world,&ressources);

            // mise à jour du temps écoulé
            update_time(&world, actualTime, &lastTimeCheck);

            // mise à jour du cooldown restant du tir de missile
            update_missileCooldown(&world, actualTime, &lastMissileCooldownCheck);

          } else { // sinon le niveau est terminé

            pause(3000); // pause de 3s avec le message de win/gameover affiché
            skip_to_next_stage(&(world)); // passe à l'écran du niveau 2 
          }
          break;

        case 3: // ECRAN NIVEAU 2 affichage pendant TRANSITION_TIME, puis on passe au gameplay du niveau 2

          if(levelSwapTick == 0){ // conditionnelle pour ne le faire qu'une seule fois
            levelSwapTick = timeSinceLaunch; // stockage du tick auquel on arrive ici (pour compter le temps écoulé)
          }
          

          if(timeSinceLaunch - levelSwapTick > TRANSITION_TIME){ // si le TRANSITION_TIME s'est écoulé depuis le tick sauvegardé
            init_data(&(world)); // initialisation des données pour le niveau 2
            lastTimeCheck = 0; // réinitialisation du checker de temps (pour le timer)
            skip_to_next_stage(&(world)); // passe au gameplay du niveau 2
          }
          break;

        case 4: // GAMEPLAY NIVEAU 2 -> mise à jour de tous les éléments et gestion de la logique du jeu

          // stocke le tick auquel le niveau 2 a commencé (pour démarrer le timer à 0s)
          if(level_2_startTick==0){ // conditionnelle pour ne le faire qu'une seule fois
            level_2_startTick = timeSinceLaunch; // stocke le tick auquel le niveau a commencé (pour que le timer démarre à 0s)
          }

          // calcul du temps réel (ticks totaux - ticks écoulés entre le lancement du jeu et début du niveau 2)
          actualTime = timeSinceLaunch - level_2_startTick;

          // tant que le niveau n'est pas terminé
          if(!is_finished_level(&(world))){
              
            // mise à jour des données liées à la physique du monde
            update_data(&world, &ressources);

            // mise à jour du temps écoulé
            update_time(&world, actualTime, &lastTimeCheck);

            // mise à jour du cooldown restant du tir de missile
            update_missileCooldown(&world, actualTime, &lastMissileCooldownCheck);

          } else{ // sinon le niveau est terminé

            pause(3000); // pause de 3s avec le message de win/gameover affiché
            world.game_status = -1; // sortie de la boucle de jeu (FIN)
          }
          break;
    }

    // rafraichissement de l'écran 
    refresh_graphics(renderer,&world,&ressources);

    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(10);
  }

  // nettoyage final
  clean(window,renderer,&ressources,&world);

  return 0;
}