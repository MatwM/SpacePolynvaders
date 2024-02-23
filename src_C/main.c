#include "main.h"
#include "sprite.h"

#define taille_petit 1
#define taille_gros 4

// Var globale SDL
SDL_Window* win = NULL;
SDL_Renderer* rend = NULL;
SDL_Event event;

// Pour le fond
SDL_Surface *surface_fond;
SDL_Texture *tex_fond;
SDL_Rect dest_fond;
// Pour EON
SDL_Surface *surface_eon;
SDL_Texture *tex_eon;
SDL_Rect dest_eon;
// Pour le texte
SDL_Surface *surface_txt;
SDL_Texture *tex_txt;
SDL_Rect dest_txt;
// Pour la fusée
SDL_Surface* surface_fus;
SDL_Texture* tex_fus;
SDL_Rect dest_fus;
// Pour les missiles
SDL_Surface* surface_mis;
SDL_Texture* tex_mis;
SDL_Rect dest_mis;
// Pour les missiles (bombe) du boss
SDL_Surface* surface_bomb;
SDL_Texture* tex_bomb;
SDL_Rect dest_bomb;
// Pour les vague de méchants
Sprite sprites_lvl1[NOMBRE_MECHANT]; // /!\ Tableau de structure et non de pointeurs
// Pour les bosses
Sprite *Boss1;
// Pour l'explosion
SDL_Surface* surface_exp;
SDL_Texture* tex_exp;
SDL_Rect dest_exp;
// Pour l'image de victoire
SDL_Surface* surface_win;
SDL_Texture* tex_win;
SDL_Rect dest_win;
// Pour l'image de victoire
SDL_Surface* surface_def;
SDL_Texture* tex_def;
SDL_Rect dest_def;
// Pour le son
Mix_Chunk* music;
Mix_Chunk* explo;

/* --------------------------- Procédures SDL -------------------------------*/

int SDLInit(char *nom){ // Initialisation de SDL et des composants du jeu
        // Init de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }
        // Création de la fenêtre
    win = SDL_CreateWindow(nom,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("Erreur de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }
        // Création du renderer
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("Erreur création du renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }
        // Chargement du fond
    surface_fond = IMG_Load("resources/fond_ecran/fond19.png"); // Chgt de l'image dans une surface
    if (!surface_fond)
    {
        printf("Erreur création surface fond\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_fond = SDL_CreateTextureFromSurface(rend, surface_fond); // Creation texture
    SDL_FreeSurface(surface_fond); // Libérer la surface
    if (!tex_fond)
    {
        printf("Erreur création texture fond: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_fond, NULL, NULL, &dest_fond.w, &dest_fond.h); // Dimensionnement
    dest_fond.w = WINDOW_WIDTH; // Ajustement dimensions...
    dest_fond.h = WINDOW_HEIGHT;
    dest_fond.x = 0; // Position...
    dest_fond.y = 0;
        // Chargement d'EON
    surface_eon = IMG_Load("resources/mobs/EON.png");
    if (!surface_eon)
    {
        printf("Erreur création surface eon\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_eon = SDL_CreateTextureFromSurface(rend, surface_eon); // Creation texture
    SDL_FreeSurface(surface_eon); // Libérer la surface
    if (!tex_eon)
    {
        printf("Erreur création texture eon: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_eon, NULL, NULL, &dest_eon.w, &dest_eon.h); // Dimensionnement
    dest_eon.w *= 2*WINDOW_HEIGHT/1240;
    dest_eon.h *= 2*WINDOW_WIDTH/1980;
    dest_eon.x = 0;
    dest_eon.y = WINDOW_HEIGHT - dest_eon.h;
        // Chargement de la fusée
    surface_fus = IMG_Load("resources/joueur/fusée2.png");
    if (!surface_fus)
    {
        printf("Erreur création surface fusée\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_fus = SDL_CreateTextureFromSurface(rend, surface_fus);
    SDL_FreeSurface(surface_fus);
    if (!tex_fus)
    {
        printf("Erreur création texture fusée: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_fus, NULL, NULL, &dest_fus.w, &dest_fus.h);
    dest_fus.w *= 2*WINDOW_WIDTH/1980;
    dest_fus.h *= 2*WINDOW_HEIGHT/1240;
        // Chargement du missile
    surface_mis = IMG_Load("resources/projectile/missile1.png");
    if (!surface_mis)
    {
        printf("Erreur de création surface missile\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_mis = SDL_CreateTextureFromSurface(rend, surface_mis);
    SDL_FreeSurface(surface_mis);
    if (!tex_mis)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_mis, NULL, NULL, &dest_mis.w, &dest_mis.h);
    dest_mis.w *= 2*WINDOW_WIDTH/1980;
    dest_mis.h *= 5*WINDOW_HEIGHT/1240;
      // Chargement du missile (bombe) du boss
    surface_bomb = IMG_Load("resources/projectile/méchant3.png");
    if (!surface_mis)
    {
        printf("Erreur de création surface missile boss\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_bomb = SDL_CreateTextureFromSurface(rend, surface_bomb);
    SDL_FreeSurface(surface_bomb);
    if (!tex_bomb)
    {
        printf("Erreur création texture missile boss: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_bomb, NULL, NULL, &dest_bomb.w, &dest_bomb.h);
    dest_bomb.w *= 2*WINDOW_WIDTH/1980;
    dest_bomb.h *= 2*WINDOW_HEIGHT/1240;
        // Chargement de l'explosion
    surface_exp = IMG_Load("resources/explosion/explo2.png");
    if (!surface_exp)
    {
        printf("Erreur création surface explosion\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_exp = SDL_CreateTextureFromSurface(rend, surface_exp);
    SDL_FreeSurface(surface_exp);
    if (!tex_exp)
    {
        printf("Erreur création texture explosion: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_mis, NULL, NULL, &dest_exp.w, &dest_exp.h);
    dest_exp.w *= 8*WINDOW_WIDTH/1980;
    dest_exp.h *= 6*WINDOW_HEIGHT/1240;
        // Chargement de le l'image de victoire
    surface_win = IMG_Load("resources/interface/youwin.png");
    if (!surface_win)
    {
        printf("Erreur création surface image victoire\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_win = SDL_CreateTextureFromSurface(rend, surface_win);
    SDL_FreeSurface(surface_win);
    if (!tex_win)
    {
        printf("Erreur création texture image de victoire: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_win, NULL, NULL, &dest_win.w, &dest_win.h);
    dest_win.w *= 6*WINDOW_WIDTH/1980;
    dest_win.h *= 6*WINDOW_HEIGHT/1240;
    dest_win.y = (WINDOW_HEIGHT-dest_win.h)/2;
    dest_win.x = (WINDOW_WIDTH-dest_win.w)/2;
        // Chargement de le l'image de defaite
    surface_def = IMG_Load("resources/interface/gameover.png");
    if (!surface_def)
    {
        printf("Erreur création surface image défaite\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    tex_def = SDL_CreateTextureFromSurface(rend, surface_def);
    SDL_FreeSurface(surface_def);
    if (!tex_win)
    {
        printf("Erreur création texture image de défaite: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex_def, NULL, NULL, &dest_def.w, &dest_def.h);
    dest_def.w *= 6*WINDOW_WIDTH/1980;
    dest_def.h *= 6*WINDOW_HEIGHT/1240;
    dest_def.y = (WINDOW_HEIGHT-dest_def.h)/2;
    dest_def.x = (WINDOW_WIDTH-dest_def.w)/2;
        // Chargement des mobs
    Boss1 = SpriteInit("resources/mobs/boss1.png",0,0,15);
    SpritesInit(sprites_lvl1,1);
        // Son
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        printf("Erreur lors de l'initialisation de SDL Mixer : %s\n", Mix_GetError());
        return 1;
    }
    Mix_AllocateChannels(2); // Allouer 2 cannaux
    Mix_Volume(0, MIX_MAX_VOLUME/3); // Mets le son a 100% en volume pour le premier cannaux
    Mix_Volume(1, MIX_MAX_VOLUME/2); // Mets le son a 50% en volume pour le deuxièmme cannaux
    music = Mix_LoadWAV("resources/son/Euro-Mir-Theme-Song.wav");
    explo = Mix_LoadWAV("resources/son/explo2.wav");
    return 0;
}

int SurfaceApply( int x, int y, SDL_Surface* source,int taille) //Affiche un méchant
{
    SDL_Rect rect; // Pour contenir la texture
    rect.x = x;
    rect.y = y;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, source); // Création de la texture
    if (!tex){
        printf("Erreur création texture dans _apply_surface_: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h); // Dimensionnement
    rect.h *= taille*WINDOW_HEIGHT/1240; // Zoom...
    rect.w *= taille*WINDOW_WIDTH/1980;
    SDL_RenderCopy(rend, tex, NULL, &rect); // Afficher

    return 0;
}

/* ------------------------------- main ------------------------------------ */


int main(int argc, char **argv){
    int i,j,sens_mov_old = 1, flag_nouv_missile = 0, flag_exp = 0, flag_controle = 0;
    int killed[NOMBRE_MECHANT], nb_killed = 0, flag_controle_souris = 0, duree_exp = 0;
    int level = 1, flag_chgt_sens = 0, flag_nouv_bomb = 0, sens_tremblement = 1, count_tremblement,
    pause_tremblement = 0, axe_tremblement = 1, chgt_controle = 0, flag_bord = 0;
    bool quit = false;
    const Uint8* pression = SDL_GetKeyboardState(NULL); // Passe à un si touche pressée

    // Inititalisations du jeu
    if (SDLInit("Space Polynvaders")== 1){
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);        
        return -1;
    }

    // Initialisation des ariables des OVNI
    float x_pos = (WINDOW_WIDTH - dest_fus.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest_fus.h);
    float x_vel = 0;
    float y_vel = 0;
    float x_mis;
    float y_mis;
    float x_bomb;
    float y_bomb;

    // Cinématique
    Boss1->x = WINDOW_WIDTH-Boss1->surface->w;
    Mix_PlayChannel(0, music,0);
    while (flag_bord == 0){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) // Appuie croix pour fermer fenêtre
                quit = true;
        }
        SDL_RenderCopy(rend,tex_fond,NULL, &dest_fond);
        Boss1->x -= 7*WINDOW_WIDTH/1980;

        if (Boss1->x+Boss1->surface->w*4 < 0){
            flag_bord = 1;
        }
        SurfaceApply(Boss1->x,Boss1->y,Boss1->surface,taille_gros);
        SDL_RenderPresent(rend);
        SDL_Delay(10);
        SDL_RenderClear(rend);  
        if (quit == true){
                SpriteDelete(Boss1);
            SpriteDelete(sprites_lvl1);
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_DestroyTexture(tex_exp);
            SDL_DestroyTexture(tex_fond);
            SDL_DestroyTexture(tex_fus);
            SDL_DestroyTexture(tex_mis);
            return 0;
        }
    }
    Boss1->x = 0;
    for (i = 0; i < 9; i++){ //Scénario
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) // Appuie croix pour fermer fenêtre
                quit = true;
        }
        if (pression[SDL_SCANCODE_S]){
            goto jeu;
        }
        SDL_RenderCopy(rend,tex_fond,NULL, &dest_fond);
        if (i < 5){
            SDL_RenderCopy(rend,tex_eon,NULL,&dest_eon);
            if (i == 0){
                surface_txt = IMG_Load("resources/mobs/Texte1.png");
                if (!surface_txt)
            {
                printf("Erreur création surface texte 1 \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 1){
                surface_txt = IMG_Load("resources/mobs/Texte1bis.png");
                if (!surface_txt)
            {
                printf("Erreur création surface texte 1bis \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 2){
                surface_txt = IMG_Load("resources/mobs/Texte2.png");
                if (!surface_txt)
            {
                printf("Erreur création surface texte 2 \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 3){
                surface_txt = IMG_Load("resources/mobs/Texte3.png");
                if (!surface_txt)
                {
                    printf("Erreur création surface texte 3 \n");
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    return 1;
                }
            }
            if (i == 4){
                surface_txt = IMG_Load("resources/mobs/Texte4.png");
                if (!surface_txt)
                {
                    printf("Erreur création surface texte 4 \n");
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    return 1;
                }
            }
            SurfaceApply(dest_eon.x+dest_eon.w,dest_eon.y-WINDOW_HEIGHT/4,surface_txt,1);
        }
        else {
            if (i == 5){
                surface_txt = IMG_Load("resources/mobs/3.png");
                if (!surface_txt)
            {
                printf("Erreur création surface  3 \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 6){
                surface_txt = IMG_Load("resources/mobs/2.png");
                if (!surface_txt)
            {
                printf("Erreur création surface 2 \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 7){
                surface_txt = IMG_Load("resources/mobs/1.png");
                if (!surface_txt)
            {
                printf("Erreur création surface texte 1 \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
            }
            if (i == 8){
                surface_txt = IMG_Load("resources/mobs/12.png");
                if (!surface_txt)
                {
                    printf("Erreur création surface 12 \n");
                    SDL_DestroyRenderer(rend);
                    SDL_DestroyWindow(win);
                    SDL_Quit();
                    return 1;
                }
            }
            
            SurfaceApply(WINDOW_WIDTH/2-WINDOW_WIDTH*200/1240,0,surface_txt,2);
        }
        SDL_RenderCopy(rend,tex_txt,NULL,&dest_txt);
        SDL_RenderPresent(rend);
        if (i < 5) SDL_Delay(3700);
        else SDL_Delay(1000);
        SDL_RenderClear(rend);
        if (quit == true){
            SpriteDelete(Boss1);
            SpriteDelete(sprites_lvl1);
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_DestroyTexture(tex_exp);
            SDL_DestroyTexture(tex_fond);
            SDL_DestroyTexture(tex_fus);
            SDL_DestroyTexture(tex_mis);
        return 0;
        }
    }
    SDL_FreeSurface(surface_txt);
    jeu: 
    while (!quit){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) // Appuie croix pour fermer fenêtre
                quit = true;
        }

    // Calcul des déplacements de la fusée et du missile selon mode de contrôle
        if (flag_controle_souris){ // Controle de la fusée avec la souris
            fusee_suit_souris(&x_pos,&y_pos,&x_vel,&y_vel,dest_fus);
            if (chgt_controle){ // Idem avec le clavier
                x_pos = (WINDOW_WIDTH - dest_fus.w) / 2;
                y_pos = (WINDOW_HEIGHT - dest_fus.h);
                chgt_controle = 0;
            }
        }
        else{ // Controle avec le clavier
            fusee_suit_clavier(&x_pos, &y_pos, &x_vel, &y_vel,dest_fus);
            if (chgt_controle){ // Eviter de perdre la fusée hors de l'écran
                x_pos = (WINDOW_WIDTH - dest_fus.w) / 2;
                y_pos = (WINDOW_HEIGHT - dest_fus.h);
                chgt_controle = 0;
            }
        }
        if (pression[SDL_SCANCODE_C]) // Chgt du mode de controle de la fusée
        {
            if (flag_controle == 0){
                flag_controle_souris = 1 - flag_controle_souris;
                chgt_controle = 1;
            }
            flag_controle ++;
            if (flag_controle > 4){ // Pour éviter les rebonds
                flag_controle = 0;
            }
        }
        /*if (pression[SDL_SCANCODE_P]){
            pause = 1;
        }
        printf("%d", pause);
        while (pause){
            if (pression[SDL_SCANCODE_P]){
                pause = 0;
            }
            printf("%d", pause);
        }*/
        if (y_mis < 0){
            flag_nouv_missile = 1;
        }
        if (flag_nouv_missile){ // Création d'un nouveau missile
            x_mis = dest_fus.x+dest_fus.w/2-3;
            y_mis = dest_fus.y-dest_mis.h+10;
            flag_nouv_missile = 0;
        }
        else if (GameOver == false) { // Avancement du missile
            y_mis -= (float) 2*SPEED_MISSILE/60*WINDOW_HEIGHT/1980;
        }
        if (y_bomb > WINDOW_HEIGHT && level == 2){
            flag_nouv_bomb = 1;
        }
        if (flag_nouv_bomb){// Création d'une nouvelle bombe
            x_bomb = (Boss1->x+Boss1->surface->w/2);
            y_bomb = Boss1->y;
            flag_nouv_bomb = 0;
            count_tremblement = 4;
        }
        else if (GameOver == false) { // Chute de la bombe
            y_bomb += (float) 1.1*SPEED_MISSILE/60*(1 - Boss1->y/WINDOW_HEIGHT);
        }

    // MàJ les positions de la fusée, du missile et de la bombe pour lvl 2
        dest_fus.y = (int) y_pos;
        dest_fus.x = (int) x_pos;
        dest_mis.x = (int) x_mis;
        dest_mis.y = (int) y_mis;
        if (level == 2){ // Pour la bombe
            dest_bomb.x = (int) x_bomb-dest_bomb.w/2;
            if (dest_bomb.x < 0){
                dest_bomb.x = -dest_bomb.x;
            }
            dest_bomb.y = (int) y_bomb+(Boss1->surface->h)-80; // Adapatation au dessin
        }

    // Deplacement des monstres !   
        if (level == 1 && GameOver == false){
            for (i = 0; i < NOMBRE_MECHANT; i++){
                if (ListPresent(i,killed,nb_killed) == 0){
                    flag_chgt_sens = SpriteMove(sprites_lvl1+i,sens_mov_old*SPEED_MOVE,0,taille_petit);
                    if (flag_chgt_sens == 1){ // Correction décalage ligne
                        if (sens_mov_old == 1){
                            for (j = i; j> i-NOMBRE_COLONE; j--){
                                SpriteMove(sprites_lvl1+j,-sens_mov_old*SPEED_MOVE*WINDOW_WIDTH/1980,0,taille_petit);
                            }
                        }
                        for (i = 0; i < NOMBRE_MECHANT; i++){
                            SpriteMove(sprites_lvl1+i,0,ESPACE_LIGNE/2*WINDOW_HEIGHT/1240,taille_petit);
                        }
                            if (sens_mov_old == 1) sens_mov_old = -1;
                            else sens_mov_old = 1;                           
                    }
                }
            }
        }
        if (level == 2 && GameOver == false){
            if (count_tremblement > 0){ // Tremblement quand il tire
                if (pause_tremblement == 1){
                    if (axe_tremblement == 1){
                    Boss1->x += (1-sens_tremblement*2)*16*WINDOW_WIDTH/1980;
                    axe_tremblement = 0;
                    }
                    else {
                    Boss1->y += (1-sens_tremblement*2)*16*WINDOW_HEIGHT/1240;
                    axe_tremblement = 1;
                    sens_tremblement = 1 -sens_tremblement;
                    count_tremblement --;
                    if (count_tremblement == 0){
                        pause_tremblement = 0;
                    }
                    }
                }
                else pause_tremblement = 1;
            }
            if (collision_bombfusee(dest_fus,x_bomb,y_bomb)){
                dest_exp.x = dest_fus.x;
                dest_exp.y = dest_fus.y;
                dest_exp.w = dest_fus.w;
                dest_exp.h = dest_fus.h;
                GameOver = true;
            }
            if ((Boss1->PV > 0)&&(count_tremblement == 0)){ //A l'arret quand il tremble
                flag_chgt_sens = SpriteMove(Boss1,sens_mov_old*SPEED_MOVE*1.8*WINDOW_WIDTH/1980,0,taille_petit);
                if (flag_chgt_sens == 1){ // Correction décalage ligne
                    SpriteMove(Boss1,0,1.5*ESPACE_LIGNE*WINDOW_HEIGHT/1240,taille_gros);
                    if (sens_mov_old == 1) sens_mov_old = -1;
                    else sens_mov_old = 1;                           
                }
            }
        }
    
    //MàJ affichage
            // Ajout du fond
        SDL_RenderCopy(rend,tex_fond,NULL, &dest_fond);
            // Ajout des méchants si tjr en vie
        if (level == 1){ // Affichage du level 1 à modifier test
            for (i=0; i < NOMBRE_MECHANT; i++){
                if (ListPresent(i,killed,nb_killed) == 0){
                    if ((sprites_lvl1+i)->surface != NULL){
                        SurfaceApply( sprites_lvl1[i].x, sprites_lvl1[i].y, (sprites_lvl1+i)->surface,taille_petit);
                    }
                    if (sprites_lvl1[i].surface!=NULL){
                        if (collision_misméchant(sprites_lvl1[i],x_mis,y_mis,taille_petit) == 1){
                            killed[nb_killed] = i;
                            nb_killed ++;
                            flag_nouv_missile = 1;
                            dest_exp.h = sprites_lvl1[i].surface->h;
                            dest_exp.w = sprites_lvl1[i].surface->w;
                            dest_exp.x = sprites_lvl1[i].x;
                            dest_exp.y = sprites_lvl1[i].y-10;
                            flag_exp= 1;
                            Mix_PlayChannel(1, explo,0);
                        }
                    }
                }
            }
        }
        if (level == 2){ // Affichage du level 2
            if (Boss1->PV == 0) GameOver = true;
            else {
                    if (collision_misméchant(*Boss1,x_mis,y_mis,taille_gros) == 1){
                        Boss1->PV --;
                        flag_nouv_missile = 1;
                        if (Boss1->PV == 0){
                            dest_exp.x = Boss1->x;
                            dest_exp.y = Boss1->y;
                            dest_exp.h = Boss1->surface->h;
                            dest_exp.w = Boss1->surface->w;
                        }
                        else {
                            dest_exp.x = x_mis-dest_exp.w/2;
                            dest_exp.y = y_mis-100-dest_exp.h/2;
                            dest_exp.w = Boss1->surface->w*0.5;
                            dest_exp.h = Boss1->surface->w*0.5;
                        }
                        flag_exp= 1;
                        Mix_PlayChannel(1, explo,0);
                    }
                    SurfaceApply(Boss1->x,Boss1->y,Boss1->surface,taille_petit);
            }
        }
        if (GameOver == false){ // Le jeu continue
            SDL_RenderCopy(rend, tex_fus, NULL, &dest_fus);//Ajout de la fusée
            SDL_RenderCopy(rend,tex_mis,NULL,&dest_mis);//Ajout du missile
            if (level == 2){
                SDL_RenderCopy(rend,tex_bomb,NULL,&dest_bomb);//Ajout du missile du boss  
            }
            //SDL_RenderCopy(rend, tex_txt,NULL, &dest_tex);//Ajout du texte
                    // Ajout de l'explosion si besoin
                if (flag_exp == 1){
                    SDL_RenderCopy(rend, tex_exp, NULL, &dest_exp);
                    duree_exp ++;
                    if (duree_exp > 5){
                        flag_exp = 0;
                        duree_exp = 0;
                    }
                }
            SDL_RenderPresent(rend);
        }
        if (nb_killed == NOMBRE_MECHANT){ //Changement de niveau
            level = 2;
        }
        if (GameOver == true){ // Fin de jeu
            SDL_Delay(3000/60);
            SDL_RenderCopy(rend,tex_fond,NULL, &dest_fond);
            SDL_RenderCopy(rend, tex_exp, NULL, &dest_exp);
            if ((Boss1->PV == 0) /*&& (nb_killed == NOMBRE_MECHANT)*/){
                surface_txt = IMG_Load("resources/mobs/bravo.png");
                if (!surface_txt)
            {
                printf("Erreur création surface bravo \n");
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 1;
            }
                SurfaceApply(dest_eon.w,dest_eon.y,surface_txt,1);
                SDL_RenderCopy(rend,tex_txt,NULL,&dest_txt);
                SDL_RenderCopy(rend,tex_eon,NULL,&dest_eon);
                dest_win.y = -200;
                SDL_RenderCopy(rend,tex_win,NULL,&dest_win);
            }
            else{
                SDL_RenderCopy(rend,tex_def,NULL,&dest_def);
            }
            SDL_RenderPresent(rend);
            if (pression[SDL_SCANCODE_R]){
                nb_killed = 0;
                for (i = 0; i < NOMBRE_MECHANT; i++){
                    killed[i] = -1;
                }
                x_pos = (WINDOW_WIDTH - dest_fus.w) / 2;
                y_pos = (WINDOW_HEIGHT - dest_fus.h);
                x_mis = x_pos + dest_fus.w/2;
                y_mis = y_pos;
                x_vel = 0;
                y_vel = 0;
                Boss1 = SpriteInit("resources/mobs/boss1.png",0,0,20);
                SpritesInit(sprites_lvl1,1);
                GameOver = false;
                level = 1;
            }
        }
        SDL_RenderClear(rend);
        SDL_Delay(1500/60); // *Vérif ->Repos: très important ! Sinon erreur de seg et de texturisation
    }
    
    printf("check 1 \n");
    SpriteDelete(Boss1);
    SpriteDelete(sprites_lvl1);
    printf("check 2 \n");
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    //SDL_FreeSurface(surface_txt); segmentation fault...
    SDL_DestroyTexture(tex_txt);
    printf("check 3 \n"); // Segmentation fault entre check 2 et 3
    SDL_DestroyTexture(tex_exp);
    SDL_DestroyTexture(tex_fond);
    SDL_DestroyTexture(tex_fus);
    SDL_DestroyTexture(tex_mis);
    printf("check 4 \n");
    SDL_DestroyTexture(tex_bomb);
    SDL_DestroyTexture(tex_win);
    SDL_DestroyTexture(tex_def);   
    SDL_DestroyTexture(tex_eon);
    Mix_FreeChunk(music);
    Mix_FreeChunk(explo);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}