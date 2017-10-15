#include "board.h"
#include <stdbool.h>
#include <stdio.h> /* printf */
#include <stdlib.h>

#define RANDOM_COLOR 1 + (int)(rand() % 7)
// caution next 2 define need a tmp value
#define COMP_CJ(c, j) ((tmp = c).type == 1 && tmp.value.id == j)
#define CELL_TO_CHAR(c)                                \
    (((tmp = c).type == 0) ? 'A' + tmp.value.color - 1 \
                           : PLAYER_SYMBOLS[tmp.value.id - 1])

unsigned players_area[PLAYER_NUMBER] = {1, 1};

void add_points(Player_id player, int n)
{
    if (player == J1)
        players_area[0] += n;
    else if (player == J2)
        players_area[1] += n;
}

/** Board representation in memory
 * There is many diferents ways to represent the board in memory
 * mainly because of the fixed 'word' size taken by the processor
 * so for readability we will choose
 *  -zero mean uninitialized, blank
 *  -negative int for players starting at minus one like Player_id starting at one
 *
 *  -positive int for colors it's start at 1 to
 **/
int board[BOARD_SIZE * BOARD_SIZE] = {0}; // Filled with zeros TODO set to static

Cell get_cell(int x, int y)
{
    Cell c;
    int tmp = board[y * BOARD_SIZE + x];
    if (tmp > 0)
    {
        c.type = tcolor;
        c.value.color = (CellColor)abs(tmp);
    }
    else
    {
        c.type = tplayer;
        c.value.id = (Player_id)abs(tmp);
    }
    return c;
}

static void set_cell(int x, int y, int v) { board[y * BOARD_SIZE + x] = v; }

bool is_adjacent(int x, int y, Player_id player)
{
    Cell tmp;
    bool r = (x > 0 && COMP_CJ(get_cell(x - 1, y), player)) ||
             (x < BOARD_SIZE - 1 && COMP_CJ(get_cell(x + 1, y), player)) ||
             (y > 0 && COMP_CJ(get_cell(x, y - 1), player)) ||
             (y < BOARD_SIZE - 1 && COMP_CJ(get_cell(x, y + 1), player));
    return r;
}

void print_board(void)
{
    Cell tmp;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c", CELL_TO_CHAR(get_cell(j, i)));
        }
        printf("\n");
    }
}

void fill_board(void)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            set_cell(j, i, RANDOM_COLOR);
        }
    }
    set_cell(BOARD_SIZE - 1, 0, -J1);
    set_cell(0, BOARD_SIZE - 1, -J2);
}

void modify(Player_id player, CellColor color)
{
    bool changed;
    int how_many = 0;
    do
    {
        changed = false;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                // better to save get_cell? if yes, in or out forloop?
                // clang-format off
                Cell zazaz = get_cell(i, j);
                if (get_cell(i, j).type == 0 
                && get_cell(i, j).value.color == color 
                && is_adjacent(i, j, player))
                // clang-format on
                {
                    set_cell(i, j, -player);
                    how_many = how_many + 1;
                    changed = true;
                }
            }
        }
    } while (changed);
    add_points(player, how_many);
}

bool there_is_a_winner(void)
{
    unsigned last = 0;
    for (int i = 0; i < PLAYER_NUMBER; i++)
    {
        if (last < players_area[i])
            last = players_area[i];
    }
    return (double)last >= (double)(BOARD_SIZE * BOARD_SIZE) / PLAYER_NUMBER;
}

unsigned numberOfCells(Player_id player) { return players_area[player - 1]; }