#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdbool.h>

#define WINDOW_WIDTH 1980 //Division jusqu'à 2 sinon erreur d'arrondi: taille 0 --> Pas d'affichage
#define WINDOW_HEIGHT 1240
#define ESPACE_LIGNE 64
#define ESPACE_COLONE 53
#define NOMBRE_MECHANT 90
#define SPEED_MOVE 22 
#define SPEED_FUSEE 750 
#define SPEED_MISSILE 2500
#define NOMBRE_COLONE 15

extern bool GameOver;




#endif