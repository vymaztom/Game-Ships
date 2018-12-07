#ifndef _GAME
#define _GAME

#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "player.h"


/*******************************************************************************

                            MAIN GAME FUNCTION

*******************************************************************************/

// start one game
void game(player_t* one, player_t* two);


/*******************************************************************************

                        PLAYER SUPPORT FUNCTIONS

*******************************************************************************/

// generate valide move for player one
int player_generateAttack(player_t* one, player_t* two);

// generate matrix of ships
void player_generate_matrix(player_t* one);

// switch for AI and Person
int player_move(player_t* one, player_t* two);

// test if attack is valide
int player_test_valide_attack(player_t* one, int pos_x, int pos_y);

/*******************************************************************************

                        SHIPS SUPPORT FUNCTIONS

*******************************************************************************/

// test if ships could be place into map
int can_place(player_t* one, int pos_x, int pos_y, int ship, int rot);

// place ship into map
void place(player_t* one, int pos_x, int pos_y, int ship, int rot, char s_id);

/*******************************************************************************

                        SAVE STATISTC OF GAME

*******************************************************************************/

// calcule statistis and save it into file
void save_statistic(player_t* one, player_t* two);

#endif
