#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "player.h"
#include "game.h"

/*******************************************************************************

                            MAIN GAME FUNCTION

*******************************************************************************/

// start one game
void game(player_t* one, player_t* two){
    uint8_t isEnd =  0;
    uint8_t onMove = 0;
    while(isEnd == 0){
        if(onMove == 0){
            isEnd = player_move(one, two);
        }else{
            isEnd = player_move(two, one);
        }
        onMove++;
        onMove = onMove%2;
    }
    if(onMove == 0){
        print_end(two, one);
    }else{
        print_end(one, two);
    }

}

/*******************************************************************************

                        PLAYER SUPPORT FUNCTIONS

*******************************************************************************/

// generate valide move for player one
int player_generateAttack(player_t* one, player_t* two){
    int pos_x = 0;
    int pos_y = 0;
    int isSet = 0;

    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 10 ; j++){
            if(one->oposMatrix[i][j] == 'x'){
                if(i-1 > 0){
                    if(one->oposMatrix[i-1][j] == ' '){
                        pos_x = i-1;
                        pos_y = j;
                        isSet = 1;
                        break;
                    }
                }
                if(i+1 < 10){
                    if(one->oposMatrix[i+1][j] == ' '){
                        pos_x = i+1;
                        pos_y = j;
                        isSet = 1;
                        break;
                    }
                }
                if(j-1 > 0){
                    if(one->oposMatrix[i][j-1] == ' '){
                        pos_x = i;
                        pos_y = j-1;
                        isSet = 1;
                        break;
                    }
                }
                if(j+1 < 10){
                    if(one->oposMatrix[i][j+1] == ' '){
                        pos_x = i;
                        pos_y = j+1;
                        isSet = 1;
                        break;
                    }
                }
            }
        }
    }

    if(isSet == 0){
        do{
            pos_x = rand()%10;
            pos_y = rand()%10;
        }while(one->oposMatrix[pos_x][pos_y] != ' ');
    }

    uint8_t ret = player_getAttack(two, pos_x, pos_y);
    if(ret == 0){
        one->oposMatrix[pos_x][pos_y] = '+';
        two->mineMatrix[pos_x][pos_y] = '+';
    }else{
        one->oposMatrix[pos_x][pos_y] = 'x';
        two->mineMatrix[pos_x][pos_y] = 'x';
    }
    return((int)ret);
}

// generate matrix of ships
void player_generate_matrix(player_t* one){
    char s_id = 0;
    int pos_x;
    int pos_y;
    int rot;
    for(int i = 0 ; i < 4 ; i++){
        do{
            pos_x = rand()%10;
            pos_y = rand()%10;
            rot = rand()%2;
        }while(can_place(one, pos_x, pos_y, 0, rot) != 1);
        place(one, pos_x,pos_y,0,rot,s_id);
        s_id++;
    }
    for(int i = 0 ; i < 2 ; i++){
        do{
            pos_x = rand()%10;
            pos_y = rand()%10;
            rot = rand()%2;
        }while(can_place(one, pos_x, pos_y, 1, rot) != 1);
        place(one, pos_x,pos_y,1,rot,s_id);
        s_id++;
    }
    for(int i = 0 ; i < 2 ; i++){
        do{
            pos_x = rand()%10;
            pos_y = rand()%10;
            rot = rand()%2;
        }while(can_place(one, pos_x, pos_y, 2, rot) != 1);
        place(one, pos_x,pos_y,2,rot,s_id);
        s_id++;
    }
    for(int i = 0 ; i < 1 ; i++){
        do{
            pos_x = rand()%10;
            pos_y = rand()%10;
            rot = rand()%2;
        }while(can_place(one, pos_x, pos_y, 2, rot) != 1);
        place(one, pos_x,pos_y,3,rot,s_id);
        s_id++;
    }
}

// switch for AI and Person
int player_move(player_t* one, player_t* two){
    int value;
    if(one->isPC == 0){
        value = attak(one, two);
    }else{
        value = player_generateAttack(one, two);
    }
    if(value == 1){
        if(player_isEnd(two) == 1){
            return 1;
        }else{
            print_situation(1, one, two);
            return 0;
        }
    }
    print_situation(0, one, two);
    return 0;
}

// test if attack is valide
int player_test_valide_attack(player_t* one, int pos_x, int pos_y){
    int ret = 0;
    if((one->oposMatrix[pos_x][pos_y] != 'x') && (one->oposMatrix[pos_x][pos_y] != '+')){
        ret = 1;
    }
    return ret;
}
/*******************************************************************************

                        SHIPS SUPPORT FUNCTIONS

*******************************************************************************/

// test if ships could be place into map
int can_place(player_t* one, int pos_x, int pos_y, int ship, int rot){
    int ok = 1;
    if((rot == 1)){
        if(pos_x+ship >= 10){
            return 0;
        }
        for(int i = pos_x ; i <= pos_x+ship ; i++){
            for(int j = pos_y ; j <= pos_y ; j++){
                if(one->mineMatrix[i][j] != ' '){
                    ok = 0;
                }
            }
        }
    }else{
        if(pos_y+ship >= 10){
            return 0;
        }
        for(int i = pos_x ; i <= pos_x ; i++){
            for(int j = pos_y ; j <= pos_y+ship ; j++){
                if(one->mineMatrix[i][j] != ' '){
                    ok = 0;
                }
            }
        }
    }
    return ok;
}

// place ship into map
void place(player_t* one, int pos_x, int pos_y, int ship, int rot, char s_id){
        if(rot == 1){
        for(int i = pos_x ; i <= pos_x+ship ; i++){
            for(int j = pos_y ; j <= pos_y ; j++){
                one->mineMatrix[i][j] = s_id;
            }
        }
    }else{
        for(int i = pos_x ; i <= pos_x ; i++){
            for(int j = pos_y ; j <= pos_y+ship ; j++){
                one->mineMatrix[i][j] = s_id;
            }
        }
    }
    one->ships[(uint8_t)(s_id)] = ship+1;
}

/*******************************************************************************

                        SAVE STATISTC OF GAME

*******************************************************************************/

// calcule statistis and save it into file
void save_statistic(player_t* one, player_t* two){

    int one_ships = 0;
    int two_ships = 0;

    int one_value = 0;
    int two_value = 0;

    int one_good_attack_sum = 0;
    int two_good_attack_sum = 0;

    int one_attack_sum = 0;
    int two_attack_sum = 0;

    float one_percetil_of_good_attacks = 0.0;
    float two_percetil_of_good_attacks = 0.0;

    // calcule active ships
    for(int i = 0 ; i < 9 ; i++){
        if(one->ships[i] > 0){
            one_value += one->ships[i];
            one_ships++;
        }
        if(two->ships[i] > 0){
            two_value += two->ships[i];
            two_ships++;
        }
    }

    // calcule data for percenil of good attacks
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 10 ; j++){
            if(one->oposMatrix[i][j] == '+'){
                one_attack_sum++;
            }else if(one->oposMatrix[i][j] == 'x'){
                one_good_attack_sum++;
                one_attack_sum++;
            }
            if(two->oposMatrix[i][j] == '+'){
                two_attack_sum++;
            }else if(two->oposMatrix[i][j] == 'x'){
                two_good_attack_sum++;
                two_attack_sum++;
            }
        }
    }

    if((one_attack_sum != 0) && (two_attack_sum != 0)){
        one_percetil_of_good_attacks = ((float)one_good_attack_sum/(float)one_attack_sum)*100.0;
        two_percetil_of_good_attacks = ((float)two_good_attack_sum/(float)two_attack_sum)*100.0;
    }


    FILE* file = fopen("statistic.txt", "w");

    fprintf(file, "%s\n",one->name);
    fprintf(file, "Zbylych lodi:       %i/9\n", one_ships);
    fprintf(file, "Zbylych bloku lodi: %i/18\n", one_value);
    fprintf(file, "Uzpesnost zasahu:   %.2f%%\n", one_percetil_of_good_attacks);

    fprintf(file, "\n\n");

    fprintf(file, "%s\n",two->name);
    fprintf(file, "Zbylych lodi:       %i/9\n", two_ships);
    fprintf(file, "Zbylych bloku lodi: %i/18\n", two_value);
    fprintf(file, "Uzpesnost zasahu:   %.2f%%\n", two_percetil_of_good_attacks);

    fclose(file);
}
