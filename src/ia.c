#include <stdbool.h>
#include <stdlib.h> /* rand, srand */
#include <stdio.h>  /* printf */
#include "ia.h"
#include "parameters.h"
#include "board.h"
#define IA_GET_CELL(X, Y, B, SIZE) B[Y * SIZE + X]
#define F(X, Y, B, SIZE, COLOR, PLAYER) \
    (IA_GET_CELL(X, Y, B, SIZE) && \
        ((get_cell(X, Y).type == tcolor && get_cell(X, Y).value.color == COLOR) \
        || (get_cell(X, Y).type == tplayer && get_cell(X, Y).value.id == PLAYER)))
// struct Node
// {
//     void * data;
//     struct Node * next;
// };
// typedef struct Node LList;
extern Player_type Players_type[PLAYER_NUMBER]; //TODO extern and []
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
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell c = get_cell(i, j);
            if (c.type == tcolor && is_adjacent(i, j, player))
            {
                return c.value.color;
            }
        }
    }
    return c1;
}

static CellColor gloutonPlay(Player_id player)
{
    unsigned colors[COLORS_NUMBER + 1] = {0};
    bool adj[BOARD_SIZE * BOARD_SIZE] = {false};
    bool changed;
    //set each cell of player to true in adj
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("a");
            Cell c = get_cell(i, j);
            if (c.type == tplayer && c.value.id == player)
            {
                adj[j * BOARD_SIZE + i] = true;
            }
        }
    }
    do
    {
        changed = false;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                printf("%i %i %i\n", i, j, IA_GET_CELL(i + 1, j, adj, BOARD_SIZE));
                Cell c = get_cell(i, j);
                // clang-format off
                if (c.type == tcolor && !adj[j * BOARD_SIZE + i]
                    &&(   (i > 0              && F(i - 1, j, adj, BOARD_SIZE,c.value.color,player)) 
                       || (i < BOARD_SIZE - 1 && F(i + 1, j, adj, BOARD_SIZE,c.value.color,player)) 
                       || (j > 0              && F(i, j - 1, adj, BOARD_SIZE,c.value.color,player)) 
                       || (j < BOARD_SIZE - 1 && F(i, j + 1, adj, BOARD_SIZE,c.value.color,player))))
                // clang-format off
                {
                    colors[c.value.color] += 1;
                    adj[j * BOARD_SIZE + i] = true;
                    changed = true;
                }
            }
        }
    } while (changed);
    CellColor res = 0;

    for (int i = 1; i < COLORS_NUMBER; i++)
    {
        printf("colors[%i]:%i\n", i, colors[i]);
        if (colors[i] > colors[res])
            res = i;
    }
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