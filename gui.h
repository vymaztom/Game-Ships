#ifndef _GUI
#define _GUI

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "game.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77



/*******************************************************************************

                                MAIN MENU

********************************************************************************/

// main menu to set kind of game
void game_menu(player_t* pl1, player_t* pl2);

// print headline of game
void print_name_of_game();

// menu for config player
int submenu(char* name_of_player);

/*******************************************************************************

                                PLAYER SET SHIPS

********************************************************************************/

// function for grapic set one ship
void place_print_matrix(player_t* one, int offset, int pos_x, int pos_y, int ship, int rot, int* ships);

// function for set all ships by player
void place_ships(player_t *one);


/*******************************************************************************

                                    ATTACK

********************************************************************************/

// function for grphic attack
void print_matrix_attack(player_t* one, int offset, int pos_x, int pos_y);

// function for graphic attack
int attak(player_t* one, player_t* other);

// print state atfter move
void print_situation(int state,player_t* active, player_t* next);

// print who win the game
void print_end(player_t* win, player_t* looser);


#endif
