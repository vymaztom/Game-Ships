/**
 * @Author: Tomas Vymazal <vymaztom>
 * @Date:   2018-12-02T14:29:48+01:00
 * @Email:  xvymaz11@vutbr.cz
 * @Project: SHIPS_GAME_VUT_SEMESTRAL
 * @Last modified by:   vymaztom
 * @Last modified time: 2018-12-02T15:39:03+01:00
 * @License: MIT
 */


#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "player.h"
#include "gui.h"
#include "game.h"

/*******************************************************************************

                                MAIN MENU

********************************************************************************/

// main menu to set kind of game
void game_menu(player_t* pl1, player_t* pl2){
    int p1 = 0, p2 = 0;
    while(1){
        start:
        fflush(stdin);
        system("cls");
        print_name_of_game();
        printf("\n");
        printf("               1) Single-player\n");
        printf("               2) Multi-player\n");
        printf("               3) Konec\n");
        char c = getch();
        if(c == '1'){
            p1 = submenu("Person");
            pl1->name = "Person";
            pl2->name = "PC";
            pl1->isPC = 0;
            pl2->isPC = 1;
            if(p1 == 3){
                goto start;
            }
            break;
        }
        if(c == '2'){
            p1 = submenu("player1");
            p2 = submenu("player2");
            pl1->name = "Player_1";
            pl2->name = "Player_2";
            pl1->isPC = 0;
            pl2->isPC = 0;
            if(p1 == 3){
                goto start;
            }
            break;
        }
        if(c == '3'){
            exit(0);
        }
    }

    if(p1 == 1){
        place_ships(pl1);
    }else{
        player_generate_matrix(pl1);
    }

    if(pl2->isPC == 1){
        player_generate_matrix(pl2);
    }else{
        if(p2 == 1){
            place_ships(pl2);
        }else{
            player_generate_matrix(pl2);
        }
    }

}

// print headline of game
void print_name_of_game(){
    for(int i =  0; i < 60 ; i++){
        printf("*");
    }
    printf("\n");
    printf("*");
    for(int i =  0; i < 25 ; i++){
        printf(" ");
    }
    printf("HRA LODE");
    for(int i =  0; i < 25 ; i++){
        printf(" ");
    }
    printf("*");
    printf("\n");
    for(int i =  0; i < 60 ; i++){
        printf("*");
    }
    printf("\n");
}

// menu for config player
int submenu(char* name_of_player){
    while(1){
        fflush(stdin);
        system("cls");
        print_name_of_game();
        printf("\n");
        printf("Rozvrzeni lodi pro %s:\n", name_of_player);
        printf("               1) Vytvorit\n");
        printf("               2) Vygenerovat\n");
        printf("               3) Zpet\n");
        char c = getch();
        if(c == '1'){
            return(1);
        }
        if(c == '2'){
            return(2);
        }
        if(c == '3'){
            return(3);
        }
    }
    return 0;
}

/*******************************************************************************

                                PLAYER SET SHIPS

********************************************************************************/

// function for grapic set one ship
void place_print_matrix(player_t* one, int offset, int pos_x, int pos_y, int ship, int rot, int* ships){
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    for(int j = 0 ; j < one->size_x+2 ; j++){
        printf("0");
    }
    printf("\n");

    for(int i = 0 ; i < one->size_x ; i++){
        for(int j = 0 ; j < offset-1 ; j++){
            printf(" ");
        }
        printf("0");

        for(int j = 0 ; j < one->size_y ; j++){
            if((rot == 0) && (pos_x == i) && (j >= pos_y) && (j <= pos_y+ship)){
                printf("*");
            }else if((rot == 1) && (pos_y == j) && (i >= pos_x) && (i <= pos_x+ship)){
                printf("*");
            }else{
                if(one->mineMatrix[i][j] != ' '){
                    printf("*");
                }else{
                    printf(" ");
                }
            }
        }

        printf("0\n");
    }

    // print end
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    for(int j = 0 ; j < one->size_x+2 ; j++){
        printf("0");
    }
    printf("\n\n");
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    printf("R) Otocit    U)  Umistit\n");
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    printf("1) * x%i    2) ** x%i    3) *** x%i    4) **** x%i\n",ships[0],ships[1],ships[2],ships[3]);
};

// function for set all ships by player
void place_ships(player_t *one){
    int ships[4] = {4,2,2,1};
    int selected = 0;
    int rot = 0;
    int pos_x = 0;
    int pos_y = 0;
    char s_id = 0;
    while((ships[0] != 0) || (ships[1] != 0) || (ships[2] != 0) || (ships[3] != 0)){
        fflush(stdin);
        system("cls");
        printf("Umistovani lodi : %s\n", one->name);
        place_print_matrix(one, 10, pos_x, pos_y, selected, rot, ships);
        char c = getch();
        if((c == 'R') || (c == 'r')){
            rot = (rot+1)%2;
        }else if((c == 'U') || (c == 'u')){

            if(can_place(one, pos_x, pos_y, selected, rot) != 0){
                printf("tesrt\n");
                if(ships[selected] > 0){
                    ships[selected]--;
                    place(one, pos_x, pos_y, selected, rot, s_id);
                    s_id++;
                    printf("plaxe\n");
                }else{
                    printf("Tento typ lodi byl vycerpan\n");
                }
            }else{
                printf("Zde nemuzete umistit lod\n");
            }
        }else if(c == '1'){
            selected = 0;
        }else if(c == '2'){
            selected = 1;
        }else if(c == '3'){
            selected = 2;
        }else if(c == '4'){
            selected = 3;
        }else if(c == LEFT){
            pos_y = (pos_y+9)%10;
        }else if(c == RIGHT){
            pos_y = (pos_y+11)%10;
        }else if(c == UP){
            pos_x = (pos_x+9)%10;
        }else if(c == DOWN){
            pos_x = (pos_x+11)%10;
        }

    }
}


/*******************************************************************************

                                    ATTACK

********************************************************************************/

// function for grphic attack
void print_matrix_attack(player_t* one, int offset, int pos_x, int pos_y){
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    for(int j = 0 ; j < one->size_x*2+4 ; j++){
        printf("0");
    }
    printf("\n");

    for(int i = 0 ; i < one->size_x ; i++){
        for(int j = 0 ; j < offset-1 ; j++){
            printf(" ");
        }
        printf("0");

        for(int j = 0 ; j < one->size_y ; j++){
            if((one->mineMatrix[i][j] != ' ') && (one->mineMatrix[i][j] != '+') && (one->mineMatrix[i][j] != 'x')){
                printf("*");
            }else{
                printf("%c",one->mineMatrix[i][j]);
            }
        }

        printf("00");

        for(int j = 0 ; j < one->size_y ; j++){
            if((i == pos_x) && (j == pos_y)){
                printf("+");
            }else{
                printf("%c",one->oposMatrix[i][j]);
            }
        }
        printf("0\n");
    }


    // print end
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    for(int j = 0 ; j < one->size_x*2+4 ; j++){
        printf("0");
    }
    printf("\n\n");
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
    printf("U)  Umistit\n");
    for(int j = 0 ; j < offset-1 ; j++){
        printf(" ");
    }
};

// function for graphic attack
int attak(player_t* one, player_t* other){
    int pos_x = 0;
    int pos_y = 0;
    while(1){
        fflush(stdin);
        system("cls");
        printf("Na tahu : %s\n\n\n", one->name);
        print_matrix_attack(one, 10, pos_x, pos_y);
        char c = getch();
        if(((c == 'U') || (c == 'u')) && player_test_valide_attack(one, pos_x, pos_y)){
            int value = player_getAttack(other, pos_x, pos_y);
            if(value == 0){
                one->oposMatrix[pos_x][pos_y] = '+';
                other->mineMatrix[pos_x][pos_y] = '+';
            }else{
                one->oposMatrix[pos_x][pos_y] = 'x';
                other->mineMatrix[pos_x][pos_y] = 'x';
            }
            return value;
        }else if(c == LEFT){
            pos_y = (pos_y+9)%10;
        }else if(c == RIGHT){
            pos_y = (pos_y+11)%10;
        }else if(c == UP){
            pos_x = (pos_x+9)%10;
        }else if(c == DOWN){
            pos_x = (pos_x+11)%10;
        }
    }
}

// print state atfter move
void print_situation(int state,player_t* active, player_t* next){
    int StatIsSave = 0;
    while(1){
        fflush(stdin);
        system("cls");
        printf("\n\n\n\n");
        int value = 1;
        for(int i  = 0 ; i < 10000; i++){
            value = value*3;
        }
        if(state == 1){
            printf("      %s zasahl lod\n\n\n", active->name);
        }
        if(state == 0){
            printf("      %s Zasahl vodu\n\n\n", active->name);
        }
        printf("\n\n\n      %s je na tahu\n\n", next->name);
        if(StatIsSave == 1){
            printf("Statistika byla ulozena do souboru\n");
        }
        printf("P) Pokracovat   K) Konec   S) Ulozit statistiku do souboru\n\n\n");
        char c = getch();
        if((c == 'P') || (c == 'p')){
            break;
        }else if((c == 'K') || (c == 'k')){
            exit(0);
        }else if((c == 'S') || (c == 's')){
            StatIsSave = 1;
            save_statistic(active, next);
        }
    }
}

// print who win the game
void print_end(player_t* win, player_t* looser){
    int StatIsSave = 0;
    while(1){
        fflush(stdin);
        system("cls");
        printf("\n\n\n\n");
        printf("       %s Vyhral\n\n\n", win->name);
        if(StatIsSave == 1){
            printf("Statistika byla ulozena do souboru\n");
        }
        printf("K) Konec S) Ulozit statistiku do souboru\n\n\n");

        char c = getch();
        if((c == 'K') || (c == 'k')){
            break;
        }else if((c == 'S') || (c == 's')){
            StatIsSave = 1;
            save_statistic(win, looser);
        }
    }
}
