/**
 * @Author: Tomas Vymazal <vymaztom>
 * @Date:   2018-10-25T19:03:38+02:00
 * @Email:  xvymaz11@vutbr.cz
 * @Filename: main.c
 * @Last modified by:   vymaztom
 * @Last modified time: 2018-10-29T22:13:00+01:00
 * @License: MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "player.h"
#include "game.h"


int main(int argc, char const *argv[]) {

    player_t* p1 = (player_t*)malloc(sizeof(player_t));
    player_t* p2 = (player_t*)malloc(sizeof(player_t));;

    load_player(p1);
    load_player(p2);

    game_menu(p1,p2);
    game(p1,p2);

    kill_player(p1);
    kill_player(p2);

    return 0;
}
