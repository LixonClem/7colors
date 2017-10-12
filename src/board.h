#include "parameters.h"
#include "player.h"

/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

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
void modify(Player_id player, char color);


bool there_is_a_winner(void);

double area(Player_id player);