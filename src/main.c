#include <stdbool.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand, srand */
#include <time.h>   /* time */

#include "parameters.h"
#include "ia.h"
#include "board.h"
#include "player.h"

Player_type Players_type[PLAYER_NUMBER] = {0};

Player get_player(Player_id i)
{
    Player j;
    j.id = i;
    j.type = Players_type[i - 1];
    return j;
}

bool play(Player_id player) //false if wrong input
{
    bool valid_input = true;
    if (Players_type[player - 1] != HUMAN)
    {
        CellColor ia_play = iaPlay(player);
        printf("the ia J%i played %c\n", player, 'A'+ia_play-1);
        modify(player, ia_play);
        print_board();
    }
    else
    {
        char *buffer;
        size_t bufsize = 32;
        size_t characters;

        buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }
        print_board();
        printf("%s insert your chosen color:", (player == J1) ? "J1" : "J2");

        if ((characters = getline(&buffer, &bufsize, stdin)) > 2 || characters < 1)
        {
            valid_input = false;
            printf("%zu characters were read.\n"
                   "but 1 were expected.\n",
                   characters - 1);
        }
        else if ((buffer[0] >= 'A' && buffer[0] <= 'G') || (buffer[0] >= 'a' && buffer[0] <= 'g'))
        {
            printf("You have chose: '%c'\n", buffer[0]);
            modify(player, ('a' <= buffer[0] && buffer[0] <= 'g') ? buffer[0] - 'a' + c1 : buffer[0] - 'A' + c1);
        }
        else
        {
            valid_input = false;
            printf("A caractere between A and G or between a and g were expected.\n"
                   "But you gave %c.\n",
                   buffer[0]);
        }
        free(buffer);
    }
    return valid_input;
}

/** Program entry point */
int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc == PLAYER_NUMBER + 1)
    {
        for (int i = 0; i < PLAYER_NUMBER; i++)
        {
            Players_type[i] = (int)(*argv[i + 1] - '0');
        }
    }
    else
    {
        Players_type[J1 - 1] = RANDOM2;
        Players_type[J2 - 1] = GLOUTON;
    }

    printf("J1 set to %i\n"
           "J2 set to %i\n",
           Players_type[J1 - 1],
           Players_type[J2 - 1]);

    fill_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");

    print_board();

    bool j1Turn = true;
    bool game_is_running = true;
    int turns = 0;
    while (game_is_running)
    {
        turns++;
        if (play(j1Turn ? J1 : J2))
        {
            if (there_is_a_winner())
            {
                //print_board();
                game_is_running = false;
                printf("you have took %i turns to find who's the best.\n"
                    "%s win with %lf pourcent\n"
                       "%s only have %lf pourcent\n",
                       turns,
                       j1Turn ? "J1" : "J2",
                       (double)numberOfCells(j1Turn ? J1 : J2) / (BOARD_SIZE * BOARD_SIZE) * 100,
                       !j1Turn ? "J1" : "J2",
                       (double)numberOfCells(j1Turn ? J2 : J1) / (BOARD_SIZE * BOARD_SIZE) * 100);
            }
            else
            {
                j1Turn = !j1Turn;
            }
        }
        else
        {
            if (true)
                game_is_running = false;
        }
    }

    return 0; // Everything went well
}