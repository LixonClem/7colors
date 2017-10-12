#include <stdio.h> /* printf */
#include <stdlib.h>
#include "board.h"

#define random0_7 (int)(rand() % 7)

int players_area[PLAYER_NUMBER] = {0, 0};

void add_points(Player_id player, int n)
{
    if (player == J1)
        players_area[0] += n;
    else if (player == J2)
        players_area[1] += n;
}

char board[BOARD_SIZE * BOARD_SIZE] = {0}; // Filled with zeros

char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

bool is_adjacent(int x, int y, Player_id player)
{
    return (x > 0 && get_cell(x - 1, y) == (char)player) ||
           (x < BOARD_SIZE - 1 && get_cell(x + 1, y) == (char)player) ||
           (y > 0 && get_cell(x, y - 1) == (char)player) ||
           (y < BOARD_SIZE - 1 && get_cell(x, y + 1) == (char)player);
}

void print_board(void)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
    }
}

char get_random_char(int qtt, int first)
{
    return 'A' + random0_7;
}

void fill_board(void)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            set_cell(i, j, get_random_char(7, 'A'));
        }
    }
    set_cell(0, BOARD_SIZE - 1, J1);
    set_cell(BOARD_SIZE - 1, 0, J2);
}

void modify(Player_id player, char color)
{
    bool changed;
    int how_many = 0;
    do
    {
        changed = FALSE;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (color == get_cell(i, j) && is_adjacent(i, j, player))
                {
                    set_cell(i, j, player);
                    how_many = how_many + 1;
                    changed = TRUE;
                }
            }
        }
    } while (changed);
    add_points(player, how_many);
}

bool there_is_a_winner(void)
{
    int last = 0;
    for (int i = 0; i < PLAYER_NUMBER; i++)
    {
        if (last < players_area[i])
            last = players_area[i];
    }
    printf("j1 %lf\n", (double)players_area[0] / (BOARD_SIZE * BOARD_SIZE));
    printf("j2 %lf\n", (double)players_area[1] / (BOARD_SIZE * BOARD_SIZE));
    printf("** %d\n", (double)last > (double)(BOARD_SIZE * BOARD_SIZE) / PLAYER_NUMBER);
    return (double)last > (double)(BOARD_SIZE * BOARD_SIZE) / PLAYER_NUMBER;
}

double area(Player_id player)
{
    int r = 0;
    if (player == J1)
        r = players_area[0];
    else if (player == J1)
        r = players_area[1];
    return (double)r / (BOARD_SIZE * BOARD_SIZE);
}