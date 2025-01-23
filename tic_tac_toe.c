#include <stdio.h>
#include <stdlib.h>

char **create_board(int size)
{
    char **board = (char **)malloc(size * sizeof(char)); // Dynamically allocating the rows of the board
    for (int i = 0; i < size; i++)
    {
        board[i] = (char *)malloc(size * sizeof(char)); // Dynamically allocating the column of the board

        for (int j = 0; j < size; j++)
        {
            board[i][j] = ' '; // initializing every position with a space.
        }
    }
    // returning the 2D array of board
    return board;
}

void print_board(char **board, int size)
{
    printf("-------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("|");
        for (int j = 0; j < size; j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

int check_winner(char **board, int size)
{
    // checking for 3 same signs in the rows
    for (int i = 0; i < size; i++)
    {
        if (board[i][0] != ' ')
        {
            int j;
            for (j = 1; j < size; j++)
            {
                if (board[i][j] != board[i][0])
                {
                    break;
                }
            }
            if (j == size)
            {
                if (board[i][0] == 'X')
                    return 1;
                else
                    return 2;
            }
        }
    }
    // checking for 3 same signs in the coloumns
    for (int i = 0; i < size; i++)
    {
        if (board[0][i] != ' ')
        {
            int j;
            for (j = 1; j < size; j++)
            {
                if (board[j][i] != board[0][i])
                {
                    break;
                }
            }
            if (j == size)
            {
                if (board[0][i] == 'X')
                    return 1;
                else
                    return 2;
            }
        }
    }

    // checking for 3 same signs in the diagonals
    if (board[0][0] != ' ')
    {
        int i;
        for (i = 1; i < size; i++)
        {
            if (board[i][i] != board[0][0])
            {
                break;
            }
        }
        if (i == size)
        {
            if (board[0][0] == 'X')
                return 1;
            else
                return 2;
        }
    }

    // now checking the other diagonal present
    if (board[0][size - 1] != ' ')
    {
        int i;
        for (i = 1; i < size; i++)
        {
            if (board[i][size - 1 - i] != board[0][size - 1])
            {
                break;
            }
        }
        if (i == size)
        {
            if (board[0][size - 1] == 'X')
                return 1;
            else
                return 2;
        }
    }

    return 0;
}

int make_move(char **board, int size, int player)
{
    int row, col;
    int ctr;
    printf("Player %d's turn\n", player);
    while (1)
    {
        printf("Enter row (1-%d): ", size);
        scanf("%d", &row);
        row = row - 1;
        printf("Enter column (1-%d): ", size);
        scanf("%d", &col);
        col = col - 1;

        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            printf("Invalid move. Please try again.\n");
            continue;
        }

        if (board[row][col] != ' ')
        {
            printf("Cell already occupied.\n Please try again.\n");
            continue;
        }
        break;
    }

    if (player == 1)
    {
        board[row][col] = 'X';
    }
    else
    {
        board[row][col] = 'O';
    }

    return 1;
}

void free_board(char **board, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(board[i]);
    }
    free(board);
}

int main()
{
    int size = 3;
    int player = 2; // Start with player 2's turn
    int moves = 0;
    int winner = 0;

    printf("\tWELCOME TO TIC TAC TOE\n");
    printf("Player 1 = X\nPlayer 2 = O\n");

    // creating a 2D array for board using pointer to pointer.
    char **board = create_board(size);

    do
    {
        print_board(board, size);

        if (player == 1)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }

        if (!make_move(board, size, player))
        {
            continue;
        }

        moves++;
        winner = check_winner(board, size);
    } while (winner == 0 && moves < size * size);

    print_board(board, size);

    if (winner == 1)
    {
        printf("WINNER = Player 1 using 'X' !!\n");
    }
    else if (winner == 2)
    {
        printf("WINNER = Player 2 using 'O' !!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }

    free_board(board, size);
    return 0;
}
