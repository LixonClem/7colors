#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand, srand */
#include <time.h>   /* time */

#include "parameters.h"
#include "ia.h"
#include "board.h"
#include "player.h"

bool play(Player player) //false if wrong input
{
    bool valid_input = TRUE;
    if (player.type != HUMAN)
    {
        modify(player.id,iaPlay(player.id));
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
        printf("%s insert your chosen color:", (player.id == (char)J1) ? "J1" : "J2");

        buffer[0] = 'A' + (int)(rand() % 7);
        if ((characters = getline(&buffer, &bufsize, stdin)) > 2 || characters < 1)
        {
            valid_input = FALSE;
            printf("%zu characters were read.\n"
                   "but 1 were expected.\n",
                   characters - 1);
        }
        else if ((buffer[0] >= 'A' && buffer[0] <= 'G') || (buffer[0] >= 'a' && buffer[0] <= 'g'))
        {
            printf("You have chose: '%c'\n", buffer[0]);
            modify(player.id, ('a' <= buffer[0] && buffer[0] <= 'g') ? buffer[0] - 'a' + 'A' : buffer[0]);
        }
        else
        {
            valid_input = FALSE;
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

    Player j1, j2;
    j1.id = J1;
    j2.id = J2;

    if (argc == 2)
    {
        switch ((int)*argv[1])
        {

        case 0:
            j1.type = HUMAN;
            j2.type = HUMAN;
            break;
        case 1:
            j1.type = HUMAN;
            j2.type = RANDOM;
            break;
        case 2:
            j1.type = HUMAN;
            j2.type = RANDOM2;
            break;
        case 3:
            j1.type = RANDOM;
            j2.type = RANDOM2;
            break;
        case 4:
            j1.type = RANDOM;
            j2.type = GLOUTON;
            break;
        case 5:
            j1.type = RANDOM2;
            j2.type = GLOUTON;
            break;
        case 6:
            j1.type = HUMAN;
            j2.type = GLOUTON;
            break;
        default: //TODO handle more choices
            j1.type = HUMAN;
            j2.type = RANDOM;
            break;
        }
    }
    else if (argc > 2)
    {
        j1.type = HUMAN;
        j2.type = RANDOM;
    }
    else
    {
        j1.type = HUMAN;
        j2.type = RANDOM;
    }

    fill_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");

    print_board();

    bool j1Turn = TRUE;
    bool game_is_running = TRUE;
    int turns_left = 1000;
    while (game_is_running && 0 < turns_left--)
    {

        if (play(j1Turn ? j1 : j2))
        {
            if (there_is_a_winner())
            {
                game_is_running = FALSE;
                printf("%s win with %f.\n"
                       "%s only have %f.\n",
                       j1Turn ? "J1" : "J2",
                       area(j1Turn ? j1.id : j2.id),
                       !j1Turn ? "J1" : "J2",
                       area((!j1Turn)? j1.id : j2.id));
            }
            else
            {
                j1Turn = !j1Turn;
            }
        }
        else
        {
            if (TRUE)
                game_is_running = FALSE;
        }
    }

    /*print_board();
    printf("\n");
    for(int i=0; i<70; i++){
        modify('^', 'A'+(int)(rand() % 7));
    }
    print_board();*/

    return 0; // Everything went well
}