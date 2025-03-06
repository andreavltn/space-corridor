/**
 * \file main.c
 * \brief Programme principal initial du niveau 0
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran
*/


#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran
*/

#define SCREEN_HEIGHT 480

/**
 * \brief Taille d'un vaisseau
 */

 #define SHIP_SIZE 32


/**
 * \brief Taille d'un météorite
*/

 #define METEORITE_SIZE 32


 /**
  * \brief Hauteur de la ligne d'arrivée
  */
 
 
 #define FINISH_LINE_HEIGHT 10
 
 
 /**
  * \brief Pas de déplacement horizontal du vaisseau
 */
 
 #define MOVING_STEP 10
 
 
 /**
   * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
 */
 
 #define INITIAL_SPEED 2
 
/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
  SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
  SDL_Texture* sprite;
};
Projet

/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
  
  sprite_t sprite; /*!< Champ représentant le sprite*/
  int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

struct sprite_s{
  int x; /*!< Champ indiquant la position x du sprite */
  int y; /*!< Champ indiquant la position y du sprite */
  int w; /*!< Champ indiquant la largeur w du sprite */
  int h; /*!< Champ indiquant la hauteur h du sprite */
} 

typedef struct sprite_s sprite_t;


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
  world->sprite->x=SCREEN_WIDTH/2; /*!< Initialisation de la position x du sprite dans le monde */
  world->sprite->y=SHIP_SIZE; /*!< Initialisation de la position y du sprite dans le monde */
  world->gameover = 0; /*!< Initialisation de l'état de gameover (fin du jeu) à 0 */
    
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    /* A COMPLETER */
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
          // touche echap
	        if (event->key.keysym.sym == SDLK_ESCAPE){
	          world->gameover = 1;
	        }
          // touche droite/d
	        if(event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d){
	          world->sprite_x+=MOVING_STEP;
	        }
          // touche gauche/q
	        if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q){
	          world->sprite_x-=MOVING_STEP;
          }
          // haut/z
	        if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z){
	          world->sprite_y-=MOVING_STEP;
	        }
          // bas/s
	        if(event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
	          world->sprite_y+=MOVING_STEP;
	        }     
        }
    }
}


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->sprite);
   
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->sprite=load_image("ressources/sprite.bmp",renderer);   
}


void init_sprite( sprite_t *sprite, int x, int y, int w, int h){
  sprite->x=x;
  sprite->y=y;
  sprite->w=w;
  sprite->h=h;

}


/**
 * \brief La fonction applique la texture du sprite sur le renderer lié à l'écran de jeus
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param world le monde du jeu
*/
void apply_sprite(SDL_Renderer *renderer , textures_t *textures , world_t * world ){
  if(textures ->sprite != NULL){
    apply_texture(textures->sprite, renderer, world->sprite_x-SPRITE_SIZE /2, world->sprite_y-SPRITE_SIZE /2);
  }
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param textures les textures du jeu
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer, textures, world);
    // on met à jour l'écran
    update_screen(renderer);
}



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
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
