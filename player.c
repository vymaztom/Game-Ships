/**
 * @Author: Tomas Vymazal <vymaztom>
 * @Date:   2018-10-29T09:36:54+01:00
 * @Email:  xvymaz11@vutbr.cz
 * @Project: SHIPS_GAME_VUT_SEMESTRAL
 * @Last modified by:   vymaztom
 * @Last modified time: 2018-11-01T18:13:25+01:00
 * @License: MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "player.h"

/*******************************************************************************

                    FUNCTIONS FOR MENAGE STRUCTURE PLAYER

*******************************************************************************/


// fill structure player_t and load data from gui
void load_player(player_t* one){

    // alloc data into player structure
    one->mineMatrix = (char**)malloc(sizeof(uint8_t*)*10);
    one->oposMatrix = (char**)malloc(sizeof(uint8_t*)*10);
    for(uint8_t i = 0 ; i < 10 ; i++){
        one->mineMatrix[i] = (char*)malloc(sizeof(uint8_t)*10);
        one->oposMatrix[i] = (char*)malloc(sizeof(uint8_t)*10);
    }

    // fill data into structure
    one->size_x = 10;
    one->size_y = 10;
    for(uint8_t i = 0 ; i < 10 ; i++){
        for(uint8_t j = 0 ; j < 10 ; j++){
            one->mineMatrix[i][j] = ' ';
            one->oposMatrix[i][j] = ' ';
        }
    }

    // call gui and ask for isPC and name

}

// free data saved into structure player_t
void kill_player(player_t* one){
    for(uint8_t i = 0 ; i < one->size_x ; i++){
        free(one->mineMatrix[i]);
        free(one->oposMatrix[i]);
    }
    free(one->mineMatrix);
    free(one->oposMatrix);
    free(one);
}

/*******************************************************************************

                        PLAYER GAME FUNCTIONS

*******************************************************************************/

// return 1 if game is ower, return 0 otherwise
uint8_t player_isEnd(player_t* one){
    for(int i = 0 ; i < 9 ; i++){
        if(one->ships[i] > 0){
            return 0;
        }
    }
    return 1;
}

uint8_t player_getAttack(player_t* one, int pos_x, int pos_y){
    int sus = 0;
    if(one->mineMatrix[pos_x][pos_y] != ' '){
        sus = 1;
        one->ships[(int)one->mineMatrix[pos_x][pos_y]]--;
    }
    return sus;
}
