#pragma once
typedef enum Player_type Player_type;
enum Player_type
{
    HUMAN,
    RANDOM,
    RANDOM2,
    GLOUTON
};

typedef enum Player_id Player_id;
enum Player_id
{
    J1 = 1,//Do not TOUCH or ajust all the fuction using it
    J2
};

typedef struct Player Player;
struct Player
{
    Player_type type;
    Player_id id;
};