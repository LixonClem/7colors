/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */

#include <stdlib.h>   /* rand */

#include <stdbool.h> /*booleens*/
#include <string.h>

/* We want a 30x30 board game by default */
#define BOARD_SIZE 25

/** Represent the actual current board game
 *
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *     an appropriate data structure would also be preferred), but don't worry.
 *     For this first assignment, no dinosaure will get you if you do that.
 */
char board[BOARD_SIZE * BOARD_SIZE] = {0}; // Filled with zeros

/** Retrieves the color of a given board cell */
char get_cell(int x, int y) {
    return board[y * BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color) {
    board[y * BOARD_SIZE + x] = color;
}

/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
void print_board() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
    }
}

/** Convert a char (like A, B...) in an int (0, 1, ...) **/
int convert_char_int(char let) {
    return (let - 'A');
}

/** Make the contrary of the former function **/
char convert_int_char(int nb) {
    return (char) (nb + 'A');
}

/** return a bool : if the cell is in the grid **/
bool is_in_grid(int i, int j) {
    return ((i < BOARD_SIZE) && (i > 0) && (j < BOARD_SIZE) && (j > 0));
}

/** return true if the cell contains a color **/
bool is_color(int i, int j) {
    return (get_cell(i, j) != 'v' && get_cell(i, j) != '^');
}

/** return true, if there is a player around the letter **/
bool is_close(int i, int j, char player) {
    if ((is_in_grid(i, j + 1)) && (get_cell(i, j + 1) == player) ||
        (is_in_grid(i, j - 1)) && (get_cell(i, j - 1) == player) ||
        (is_in_grid(i + 1, j)) && (get_cell(i + 1, j) == player) ||
        (get_cell(i - 1, j) == player)) {
        return true;
    }
    return false;
}

/** sert pour chercher un élément dans la copie du tableau de l'ia gloutonne **/
bool general_is_close(int i, int j, char *board, char symbol) {
    if ((is_in_grid(i, j + 1)) && (board[(j+1) * BOARD_SIZE + i] == symbol) ||
        (is_in_grid(i, j - 1)) && (board[(j-1) * BOARD_SIZE + i] == symbol) ||
        (is_in_grid(i + 1, j)) && (board[j * BOARD_SIZE + i+1] == symbol) ||
        (board[j * BOARD_SIZE + i-1] == symbol)) {
        return true;
    }
    return false;
}

/** fill the grid with the 7 colors **/
void fill() {
    int i, j;
    char colors[] = "ABCDEFG";
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if ((i == 0) & (j == BOARD_SIZE - 1)) {
                set_cell(i, j, '^');
            } else {
                if ((i == BOARD_SIZE - 1) & (j == 0)) {
                    set_cell(i, j, 'v');
                } else {
                    int alea = rand() % 7;
                    set_cell(i, j, colors[alea]);
                }
            }
        }
    }
}

/** update the grid with the color chosen **/
void update(char player, char color) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((((j < BOARD_SIZE - 1) & (get_cell(i, j + 1) == player))
                 || ((j > 0) & (get_cell(i, j - 1) == player))
                 || ((i > 0) & (get_cell(i - 1, j) == player))
                 || ((i < BOARD_SIZE - 1) & (get_cell(i + 1, j) == player)))
                & (get_cell(i, j) == color)) {
                set_cell(i, j, player);
                i = 0;
                j = 0;
            }
        }
    }
}

/**function which updates the grid if a human is playing **/
void player(char play) {
    char color[2];
    printf("\nChoose a color player %c :\n", play);
    scanf("%s", color);
    update(play, color[0]);
    print_board();
}


/** count the number of cells of the player**/
int nb_of_cases(char player) {
    int cpt = 0;
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (get_cell(i, j) == player) {
                cpt++;
            }
        }
    }
    return cpt;
}

static void avail_colo(char player, int *available) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if ((is_color(i, j)) && (is_close(i, j, player))) {
                printf("%d %d \n", i, j);
                available[convert_char_int(get_cell(i, j))] = 1;
            }
        }
    }
}


int number_of_choice(int *tab) {
    int cpt = 0;
    for (int i = 0; i < 7; i++) {
        if (tab[i] == 1) {
            cpt++;
        }
    }
    return cpt;
}

int max_array(int *tab) {
    int cand = 0;
    for (int i = 0; i < 7; i++) {
        if (tab[i] > tab[cand]) {
            cand = i;
        }
    }
    return cand;
}

char max_letter(char player) {
    char board_copy[BOARD_SIZE * BOARD_SIZE] = {0};
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            board_copy[y * BOARD_SIZE + x] = 'Z';
        }
    }
    int nb_of_colors[7] = {0};
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_color(i, j) &&
                board_copy[j * BOARD_SIZE + i] == 'Z' &&
                (is_close(i, j, player) | general_is_close(i, j, board_copy, get_cell(i, j)))) {
                board_copy[j * BOARD_SIZE + i] = get_cell(i, j);
                nb_of_colors[convert_char_int(get_cell(i, j))]++;
                j = 0;
                i = 0;
            }

        }
    }
    return (convert_int_char(max_array(nb_of_colors)));
}

void artificial1(void) {
    char colors[] = "ABCDEFG";
    char color;
    color = colors[rand() % 7];
    printf("IA chose %c\n", color);
    update('^', color);
    print_board();
}

void artificial2(void) {
    int avail[] = {0, 0, 0, 0, 0, 0, 0};
    int noc, cpt = 0;
    char color;
    char *colors;
    avail_colo('^', avail);
    noc = number_of_choice(avail);
    colors = malloc(noc * sizeof(char));
    for (int i = 0; i < 7; i++) {
        if (avail[i] == 1) {
            colors[cpt] = convert_int_char(i);
            cpt++;
        }
    }
    color = colors[rand() % noc];
    free(colors);
    printf("%c\n", color);
    update('^', color);
    print_board();
}

void artificial3(void) {
    char color;
    color = max_letter('^');
    printf("%c\n", color);
    update('^', color);
    print_board();
}

/** Program entry point */
int main(void) {

    char play[] = "v^";
    int i = 0, choice;
    int possession1 = 0;
    int possession2 = 0;

    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
                   "*****************************************************\n\n"
                   "Please choose a game mode :\n"
                   " 1 : Human\n"
                   " 2 : IA random\n"
                   " 3 : IA random upgraded\n"
                   " 4 : IA gloutonne\n");
    scanf("%d", &choice);

    printf("Current board state:\n");

    fill();
    print_board();

    while ((possession1 <= 50) & (possession2 <= 50)) {
        if (i % 2 == 1 && choice == 4) {
            artificial3();
        }

        if (i % 2 == 1 && choice == 3) {
            artificial2();
        }

        if (i % 2 == 1 && choice == 2) {
            artificial1();
        }

        if (i % 2 == 1 && choice == 1) {
            player(play[i % 2]);
        }

        if (i % 2 == 0) {
            player(play[i % 2]);
        }

        i++;
        possession1 = 100 * nb_of_cases(play[0]) / (BOARD_SIZE * BOARD_SIZE);
        possession2 = 100 * nb_of_cases(play[1]) / (BOARD_SIZE * BOARD_SIZE);
        printf("\nLe joueur v possède %d pourcent des cases\n", possession1);
        printf("Le joueur ^ possède %d pourcent des cases\n", possession2);
        if (possession1 > 50) {
            printf("Le joueur v a gagné");
        }
        if (possession2 > 50) {
            printf("Le joueur ^ a gagné");
        }

    }
    return 0; // Everything went well
}
