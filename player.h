/**
 * @Author: Tomas Vymazal <vymaztom>
 * @Date:   2018-10-27T23:01:51+02:00
 * @Email:  xvymaz11@vutbr.cz
 * @Project: SHIPS_GAME_VUT_SEMESTRAL
 * @Last modified by:   vymaztom
 * @Last modified time: 2018-10-29T10:01:12+01:00
 * @License: MIT
 */



#ifndef _PLAYER
#define _PLAYER



#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*******************************************************************************

                        DEFINE STRUCTURES OF PLAYER

*******************************************************************************/


// structure of one player
typedef struct player{
    char* name;
    uint8_t size_x;
    uint8_t size_y;
    char** mineMatrix;
    char** oposMatrix;
    uint8_t isPC;
    uint8_t ships[9];
}player_t;

/*******************************************************************************

                        DEFINE FUNCTIONS FOR PLAYER

*******************************************************************************/

// return 1 if game is ower, return 0 otherwise
uint8_t player_isEnd(player_t* one);

// fill structure player_t and load data from gui
void load_player(player_t* one);

// free data saved into structure player_t
void kill_player(player_t* one);

uint8_t player_getAttack(player_t* one, int pos_x, int pos_y);





#endif
