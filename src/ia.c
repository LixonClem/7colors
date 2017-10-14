#include <stdbool.h>
#include <stdlib.h> /* rand, srand */
#include <stdio.h>  /* printf */
#include "ia.h"
#include "parameters.h"

// struct Node
// {
//     void * data;
//     struct Node * next;
// };
// typedef struct Node LList;
extern Player_type Players_type[PLAYER_NUMBER];//TODO extern and []

static CellColor randomPlay(Player_id player)
{
    return 1 + (int)(rand() % 7);
}

static CellColor random2Play(Player_id player)
{
    return 1;
}

static CellColor gloutonPlay(Player_id player)
{
    return 1;
}
typedef CellColor (*f_ptr)(Player_id);

static f_ptr IaFunct[]={&randomPlay,&random2Play,&gloutonPlay};

CellColor iaPlay(Player_id id)
{
    //shorter than switch !!!!!
    printf("--%u--\n",id-1);
    Player_type t = (Players_type)[id-1];
    return (*(IaFunct[t-1]))(id);
    // IaFunct:              randomPlay, random2Play, gloutonPlay
    // Player_type:   HUMAN, RANDOM,     RANDOM2,     GLOUTON
}