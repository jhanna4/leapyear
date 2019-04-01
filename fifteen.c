// Implements Game of Fifteen (generalized to d x d)

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9
#define COLOR "\033[32m"

// Board
int board[DIM_MAX][DIM_MAX];

// Dimensions
int d;

// Saved locations of the blank tile
int blank_row;
int blank_col;

// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int *a, int *b);
void print_grid_row(int d);
void print_tile(int tile);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // Ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // Open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (true)
    {
        // Clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // Check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // Prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // Quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // Log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // Sleep thread for animation's sake
        usleep(50000);
    }

    // Close log
    fclose(file);

    // Success
    return 0;
}

// Clears screen using ANSI escape sequences
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

// Initializes the game's board with tiles numbered 1 through d*d - 1
// (i.e., fills 2D array with values but does not actually print them)
void init(void)
{
    // TODO
     // top left corner starts one less than dimension of the board squared
    int k = (d*d) - 1;

    // iterate over entire board
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // insert into board value of counter (being 'k'), then decrement counter
            board[i][j] = k--;
        }
    }
    // '_' or ASCII 95 will represent blank tile
    board[d-1][d-1] = '_';

    // if even dimensions, create a solveable board by switching positions of a and 2
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

// Prints the board in its current state
void draw(void)
{
    // TODO
     // iterate over board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // if current position is blank,  print out "_"
            if (board[i][j] == 95)
            {
                printf(" _ ");
            }
            // else print out value in board
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
    // move to next row
    printf("\n");
    }
}

// If tile borders empty space, moves tile and returns true, else returns false
bool move(int tile)
{
    // TODO
     for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            if (board[row][column] == tile)
            {   // top of blank
                // if current tile is blank
                if (board[row-1][column] == 95)
                {
                    // switch blank and tile
                    board[row-1][column] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // left of blank
                // if current tile is blank
                else if (board[row][column-1] == 95)
                {
                    // switch blank and tile
                    board[row][column-1] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // right of blank
                // if current tile is blank
                else if (board[row][column+1] == 95)
                {
                    // switch blank and tile
                    board[row][column+1] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // below blank
                // if current tile is blank
                else if (board[row+1][column] == 95)
                {
                    // switch blank and tile
                    board[row+1][column] = tile;
                    board[row][column] = 95;
                    return true;
                }
                return false;
             }
          }
       }
       return 0;
}

// Returns true if game is won (i.e., board is in winning configuration), else false
bool won(void)
{
    // TODO
     // top left of board is 1
    int count = 1;
    // iterate over board to make sure current tile is equal to current count value
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            // do not check last tile in board b/c it should be blank
            if (row == d-1 && column == d-1)
            {
                continue;
            }
            // check to see that current board position has value stored in counter
            if (board[row][column] != count++)
            {
                return false;
            }
        }
    }
    return true;
}
