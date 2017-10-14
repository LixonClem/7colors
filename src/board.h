#pragma once
#include <stdbool.h>
#include "parameters.h"
#include "player.h"

// definitions of types related to the board

typedef enum CellColor CellColor;
enum CellColor
{
    c1=1,
    c2,
    c3,
    c4,
    c5,
    c6,
    c7
};
enum CellType
{
    tcolor,tplayer
};

union CellValues {
    CellColor color; Player_id id;
};

typedef struct Cell Cell;
struct Cell
{
    enum CellType type;
    union CellValues value;
};

//------------------------- Functions

/** Retrieves the color of a given board cell */
Cell get_cell(int x, int y);

/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 **/
void print_board(void);

/**  Fill board with random colors out of 7 
 **/
void fill_board(void);

/** modify: Player_id x {'A', ..., 'G'} -> void
 *           player   ,   color        |-> give to player (set to player color) 
 *                                         the blocks corresponding with color
 *                                         and adjacents to player blocks 
 **/
void modify(Player_id player, CellColor color);

bool there_is_a_winner(void);

unsigned numberOfCells(Player_id player);