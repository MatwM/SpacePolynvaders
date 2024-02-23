
#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include "sprite.h"

void fusee_suit_souris(float *x_pos, float *y_pos, float *x_vel, float *y_vel,SDL_Rect dest_fus);
void fusee_suit_clavier(float *x_pos, float *y_pos, float *x_vel, float *y_vel,SDL_Rect dest_fus);
int collision_misméchant(Sprite sprite,float x_mis,float y_mis, int taille);
int collision_bombfusee(SDL_Rect dest_fus, float x_mis, float y_mis);