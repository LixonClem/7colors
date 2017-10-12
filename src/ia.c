#include <stdlib.h> /* rand, srand */
#include "ia.h"

struct Node
{
    void * data;
    Node * next;
};
Node * iaList= NULL;


void createIA(Player_id player){
    
}


char randomPlay(Player_id player){
    return 'A'+(int)(rand() % 7);
}

char random2Play(Player_id player){
    return 'A';
}

char gloutonPlay(Player_id player){
    return 'A';
}