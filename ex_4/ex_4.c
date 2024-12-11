/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_4
*System username: feldmaaf
******************************************/

#include <stdio.h>

#define SIZE 4
// Game states:
#define INVALID 0
#define ONGOING 1
#define WINNER 2
#define TIE 3

/*************************************************************************
* function name: mark *
* The Input: x, y, z - the mark's position. turn (X/O), the boards. *
* The output: Returns 0 if the input is incorrect and 1 otherwise. *
* The Function Operation: checks for incorrect inputs and
 * places the player's mark on the board. *
*************************************************************************/

int mark(int x, int y, int z, int player, int boards[SIZE][SIZE][SIZE]) {
    // Checks if the input is out of range:
    if (!(0 <= x && x <= SIZE - 1) ||
        !(0 <= y && y <= SIZE - 1) ||
        !(0 <= z && z <= SIZE - 1))
        return 0;
    // Checks if the cell isn't empty:
    if (boards[x][y][z] != 0)
        return 0;
    boards[x][y][z] = player;
    return 1;
}

/*************************************************************************
* function name: winCheck *
* The Input: The boards. *
* The output: Returns 2 if someone won, 3 if it's a tie,
 * and 1 otherwise (game continues) *
* The Function operation: Checks if either someone won,
 * there's a tie, or the game didn't end. *
* How the function works: The function goes through all the boards and checks
 * for win patterns. Each variable counts how many of the same X/O there are
 * in the win line, for example: rows: it goes through each row and counts
 * how many signs are equal to the first one in the row, and also makes sure
 * it's not empty. So if rows == SIZE someone won. flatDiag1 and 2 check the
 * same thing but for the 2D diagonals (flatDiag1 is for the diagonal in one
 * direction and flatDiag2 is for the other direction).
 * cubeDiag1-4 check the 3D diagonals. *
*************************************************************************/

int winCheck(int boards[SIZE][SIZE][SIZE]) {
    int isBoardFull = 1;
    int cubeDiag1 = 0, cubeDiag2 = 0, cubeDiag3 = 0, cubeDiag4 = 0;
    for (int i = 0; i < SIZE; i++) {
        int flatDiag1 = 0, flatDiag2 = 0;
        for (int j = 0; j < SIZE; j++) {
            int rows = 0, cols = 0, poles = 0;
            for (int k = 0; k < SIZE; k++) {
                // 2D rows check:
                if (boards[i][j][0] == boards[i][j][k])
                    rows++;
                // This checks if the cell is empty:
                if (boards[i][j][k] == 0) {
                    isBoardFull = 0;
                    // Reset rows because there's an empty cell in the row:
                    rows = 0;
                }

                // Everything else is the same as for rows. 2D columns check:
                if (boards[i][0][j] == boards[i][k][j])
                    cols++;
                if (boards[i][k][j] == 0)
                    cols = 0;

                // 3D columns check ("poles"):
                if (boards[0][i][j] == boards[k][i][j])
                    poles++;
                if (boards[k][i][j] == 0)
                    poles = 0;
            }
            // End of for loop

            // Verify if someone won:
            if (rows == SIZE || cols == SIZE || poles == SIZE)
                return WINNER;

            // 2D diagonal check (this only needs 2 indexes):
            if (boards[i][0][0] == boards[i][j][j])
                flatDiag1++;
            if (boards[i][j][j] == 0)
                flatDiag1 = 0;

            if (boards[i][0][SIZE - 1] == boards[i][j][SIZE - j - 1])
                flatDiag2++;
            if (boards[i][j][SIZE - j - 1] == 0)
                flatDiag2 = 0;
        }
        // End of for loop

        // Verify if someone won:
        if (flatDiag1 == SIZE || flatDiag2 == SIZE)
            return WINNER;

        // 3D diagonal check (this only needs one index):
        if (boards[0][0][0] == boards[i][i][i])
            cubeDiag1++;
        if (boards[i][i][i] == 0)
            cubeDiag1 = 0;

        if (boards[SIZE - 1][0][0] == boards[SIZE - i - 1][i][i])
            cubeDiag2++;
        if (boards[SIZE - i - 1][i][i] == 0)
            cubeDiag2 = 0;

        if (boards[0][SIZE - 1][0] == boards[i][SIZE - i - 1][i])
            cubeDiag3++;
        if (boards[i][SIZE - i - 1][i] == 0)
            cubeDiag3 = 0;

        if (boards[0][0][SIZE - 1] == boards[i][i][SIZE - i - 1])
            cubeDiag4++;
        if (boards[i][i][SIZE - i - 1] == 0)
            cubeDiag4 = 0;
    }
    // End of for loop

    // Verify if someone won:
    if (cubeDiag1 == SIZE || cubeDiag2 == SIZE ||
        cubeDiag3 == SIZE || cubeDiag4 == SIZE)
        return WINNER;
    // If the board is full and there's no winner, it must be a tie:
    if (isBoardFull)
        return TIE;
    // If no one won and there's no tie, then the game isn't over:
    return ONGOING;
}
// End of function

/*************************************************************************
* function name: printBoards *
* The Input: The boards. *
* The output: Prints the boards. *
* The Function operation: Goes through all the boards and prints them. *
*************************************************************************/

void printBoards(int boards[SIZE][SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
                printf("(%d %d %d) ", i, j, k);
            for (int k = 0; k < SIZE; k++)
                // The empty cells are 0 in the array, so it swaps with '*':
                printf("%c ", boards[i][j][k] == 0 ? '*' : boards[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    printf("Would you like to start? (y/n)\n");
    char wantStart = ' ';
    scanf(" %c", &wantStart);
    while (1) {
        if (wantStart == 'n') {
            printf("YEET");
            break;
        } else {
            printf("Please enter your game sequence.\n");

            /*
             * Variables:
             * - boards is the 4 boards in a 3D array, each "layer" is a board
             * - turn is who's turn it is.
             * - x, y, and z are the inputs.
             * - state is the game's state: invalid input/game ongoing/win/tie
             */

            int boards[SIZE][SIZE][SIZE] = {}, turn = 'O',
                x, y, z, state = ONGOING;
            while (state == ONGOING) {
                // Makes "turn" the next player:
                turn = (turn == 'O') ? 'X' : 'O';
                scanf(" %d %d %d", &x, &y, &z);
                // If the input is invalid this will be 0, else 2 or 3:
                state = mark(x, y, z, turn, boards) * winCheck(boards);
            }
            while (getchar() != '\n') {}

            if (state == INVALID)
                printf("Input incorrect.\n");
            else if (state == WINNER)
                // If someone won, it must be the last player that played:
                printf("%c is the winner.\n", turn);
            else
                printf("Tie.\n");
            if (state != INVALID)
                printBoards(boards);
        }
        // End of if-else
        printf("Would you like to continue? (y/n)\n");
        scanf(" %c", &wantStart);
    }
    // End of while
    return 0;
}
