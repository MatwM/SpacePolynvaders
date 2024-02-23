#include "OVNI.h"    
        
void fusee_suit_souris(float *x_pos, float *y_pos, float *x_vel, float *y_vel,SDL_Rect dest_fus){
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        // Calcul vitesse de la fusée selon souris
        int target_x = mouse_x - dest_fus.w / 2;
        int target_y = mouse_y - dest_fus.h / 2;
        float delta_x = target_x - *x_pos;
        float delta_y = target_y - *y_pos;
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        // Prévenir tremblement
        if (distance < 25)
        {
            *x_vel = *y_vel = 0;
        }
        else
        {
            *x_vel = delta_x * SPEED_FUSEE / distance;
            *y_vel = delta_y * SPEED_FUSEE / distance;
        }
        // Appuie clique gauche = inverser vitesse
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            *x_vel = -*x_vel;
            *y_vel = -*y_vel;
        }
        // Prévenir tremblement
        if (distance < 25)
        {
            *x_vel = *y_vel = 0;
        }
        else
        {
            *x_vel = delta_x * SPEED_FUSEE / distance;
            *y_vel = delta_y * 1.75 * SPEED_FUSEE / distance;
        }
        // Appuie clique gauche = inverser vitesse
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            *x_vel = -*x_vel;
            *y_vel = -*y_vel;
        }
        // Nouvelle position
        *x_pos += *x_vel*3 / 60;
        *y_pos += *y_vel*3 / 60;
        // Collision avec bord de la fenêtre
        if (*x_pos <= 0) *x_pos = 0;
        if (*y_pos <= 0) *y_pos = 0;
        if (*x_pos >= WINDOW_WIDTH - dest_fus.w) *x_pos = WINDOW_WIDTH - dest_fus.w;
        if (*y_pos >= WINDOW_HEIGHT - dest_fus.h) *y_pos = WINDOW_HEIGHT - dest_fus.h;

        // MàJ de la position
        dest_fus.y = (int) *y_pos;
        dest_fus.x = (int) *x_pos;
}

void fusee_suit_clavier(float *x_pos, float *y_pos, float *x_vel, float *y_vel,SDL_Rect dest_fus){
    const Uint8* pression = SDL_GetKeyboardState(NULL);
    if (pression[SDL_SCANCODE_LEFT] && *x_pos > 0) {
        *x_vel = -SPEED_FUSEE/50;
    } else if (pression[SDL_SCANCODE_RIGHT] && dest_fus.x < WINDOW_WIDTH - dest_fus.w) {
        *x_vel = SPEED_FUSEE/50;
    }
    if (pression[SDL_SCANCODE_UP] && *y_pos > WINDOW_HEIGHT/1.5) {
        *y_vel = -SPEED_FUSEE/50;
    } else if (pression[SDL_SCANCODE_DOWN] && dest_fus.y < WINDOW_HEIGHT - dest_fus.h) {
        *y_vel = SPEED_FUSEE/50;
    }
    *x_pos += *x_vel*1.5;
    *y_pos += *y_vel*2.5;
    *y_vel = 0;
    *x_vel = 0;
}

int collision_bombfusee(SDL_Rect dest_fus, float x_mis, float y_mis){
    if ((y_mis<dest_fus.y+dest_fus.h)&&(y_mis > dest_fus.y-200)){
        if ((dest_fus.x< x_mis)&&(dest_fus.x+dest_fus.w > x_mis)){
            return 1;
        }
    }
    return 0;   
}

int collision_misméchant(Sprite sprite,float x_mis,float y_mis, int taille){ //Doit etre patch
    if ((y_mis<sprite.y+sprite.surface->h)&&(y_mis > sprite.y-sprite.surface->h/2)){
        if ((sprite.x< x_mis)&&(sprite.x+sprite.surface->w > x_mis)){
            return 1;
        }
    }
    return 0;
}