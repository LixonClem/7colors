#include <stdbool.h>
#include <stdlib.h> /* rand, srand */
#include <stdio.h>  /* printf */
#include "ia.h"
#include "parameters.h"
#include "board.h"
#define IA_GET_CELL(X, Y, B, SIZE) B[(Y) * (SIZE) + (X)]
#define F(X, Y, B, SIZE, COLOR, PLAYER) \
    (IA_GET_CELL(X, Y, B, SIZE) == COLOR \
    || IA_GET_CELL(X, Y, B, SIZE) == -PLAYER)
// struct Node
// {
//     void * data;
//     struct Node * next;
// };
// typedef struct Node LList;
extern Player_type Players_type[PLAYER_NUMBER]; //TODO extern and []
extern int board[BOARD_SIZE * BOARD_SIZE];
/**IA 1
 * 
 **/
static CellColor randomPlay(Player_id player)
{
    return 1 + (int)(rand() % 7);
}

/**IA 2
 * 
 **/
static CellColor random2Play(Player_id player)
{
    bool colors[COLORS_NUMBER + 1] = {0};
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell c = get_cell(i, j);
            if (c.type == tcolor && is_adjacent(i, j, player))
            {
                colors[c.value.color] == true;
            }
        }
    }
    CellColor res = 1;

    for (int i = 1; i < COLORS_NUMBER + 1; i++)
    {
        printf("%c:%i\n", 'A' + i - 1, colors[i]);
        if (colors[i] > colors[res])
            res = i;
    }
    printf(">from random2: I want %c\n", 'A' + res - 1);
    return res;
}

/**
 * 
 **/
void general_table_print(int *t, size_t size) // TODO remove
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%i ", (int)t[j * size + i]);
        }
        printf("\n");
    }
}

/**IA 2
 * 
 **/
static CellColor gloutonPlay(Player_id player) //TODO bug j1 gauche
{
    static int gg = 0;                  //TODO rm
    printf("id:%u %i\n", player, gg++); //TODO rm
    int adj[BOARD_SIZE * BOARD_SIZE];

    //set each cell of player to true in adj
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell c = get_cell(i, j);
            if (c.type == tplayer && c.value.id == player)
            {
                adj[j * BOARD_SIZE + i] = -player;
            }
            else
            {
                adj[j * BOARD_SIZE + i] = 0;
            }
        }
    } //OK

    unsigned colors[COLORS_NUMBER + 1] = {0};
    bool changed;

    do
    {
        changed = false;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                /*  #i,j
                    #  a
                    #a a a
                    #  a
                */
                /*
                printf("-----i:%i | j:%i\n", i, j);
                printf("  %i\n", j > 0?IA_GET_CELL(i, j - 1, board, BOARD_SIZE):0);
                printf("%i %i %i\n", i > 0?IA_GET_CELL(i - 1, j, board, BOARD_SIZE):0, IA_GET_CELL(i, j, board, BOARD_SIZE), i < BOARD_SIZE - 1?IA_GET_CELL(i + 1, j, board, BOARD_SIZE):0);
                printf("  %i\n", j < BOARD_SIZE - 1?IA_GET_CELL(i, j + 1, board, BOARD_SIZE):0);
                */
                Cell c = get_cell(i,j);
                // clang-format off
                if (IA_GET_CELL(i, j, adj, BOARD_SIZE) == 0 && c.type==tcolor
                && ((i > 0 &&              F(i - 1, j, adj, BOARD_SIZE, c.value.color, player)) 
                 || (i < BOARD_SIZE - 1 && F(i + 1, j, adj, BOARD_SIZE, c.value.color, player)) 
                 || (j > 0 &&              F(i, j - 1, adj, BOARD_SIZE, c.value.color, player)) 
                 || (j < BOARD_SIZE - 1 && F(i, j + 1, adj, BOARD_SIZE, c.value.color, player))))
                // clang-format on
                {
                    //printf("ggggggggggggggg");
                    colors[c.value.color]++;
                    adj[j * BOARD_SIZE + i] = c.value.color;
                    changed = true;
                }
            }
        }
    } while (changed);

    CellColor res = 1;

    for (int i = 1; i < COLORS_NUMBER + 1; i++) //TODO set i to 2
    {
        printf("%c:%i\n", 'A' + i - 1, colors[i]);
        if (colors[i] > colors[res])
            res = i;
    }
    printf(">from glouton: I want %c\n", 'A' + res - 1);
    return res;
}
typedef CellColor (*f_ptr)(Player_id);

static f_ptr IaFunct[] = {&randomPlay, &random2Play, &gloutonPlay};

CellColor iaPlay(Player_id id)
{
    //shorter than switch !!!!!
    printf("--%u--\n", id - 1);
    Player_type t = (Players_type)[id - 1];
    return (*(IaFunct[t - 1]))(id);
    // IaFunct:              randomPlay, random2Play, gloutonPlay
    // Player_type:   HUMAN, RANDOM,     RANDOM2,     GLOUTON
}