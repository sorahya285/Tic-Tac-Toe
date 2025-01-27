#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
    char board[3][3];
    char current_player;
} TicTacToeBoard;

// Function Prototype to display the Tic Tac Toe board
void display_board(TicTacToeBoard* board);


// Function Prototype to initialize the Tic Tac Toe board with empty cells
void initialize_board(TicTacToeBoard* board);

// Function Prototype to make a move on the Tic Tac Toe board
int make_move(TicTacToeBoard* board, int row, int col);


// Function Prototype to check if a player has won
int check_win(TicTacToeBoard* board, char player);

// Function Prototype to check if the game is a draw
int check_draw(TicTacToeBoard* board);

// Function Prototype to save the game state to a file
void save_board_to_file(TicTacToeBoard* board, char* file_path);

// Function Prototype to load the game state from a file
void load_board_from_file(TicTacToeBoard* board, char* file_path);


int main() {
    char* file_path = "tic_tac_toe_board.txt";
    TicTacToeBoard board;
    initialize_board(&board);

    char player1[50], player2[50];
    printf("Enter Player 1 name: ");
    scanf("%s", player1);
    printf("Enter Player 2 name: ");
    scanf("%s", player2);

    char choice;
    printf("Do you want to continue the previous game? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        load_board_from_file(&board, file_path);
        printf("Loaded the previous game board:\n");
        display_board(&board);
    }

    display_board(&board);

    int row, col;
    while (1) {
       
        printf("\nPlease enter the row and column for your move, leave space in between the numbers: ");
        scanf("%d%d", &row, &col);

        int move_result = make_move(&board, row, col);
        if (move_result == 0) {
            printf("Cell is already occupied or invalid input. Try again.\n");
            continue;
        }

        display_board(&board);
        
        int player_won = check_win(&board, 'X');
        int opponent_won = check_win(&board, 'O');
        int is_draw = check_draw(&board);

        if (player_won) {
            printf("\n\nCongratulations %s you win!\n", player1);
            break;
        } else if (opponent_won) {
            printf("\n\nCongratulations %s you win!\n", player2);
            break;
        } else if (is_draw) {
            printf("\n\nIt's a draw!\n");
            break;
        }
    }

    save_board_to_file(&board, file_path);
    return 0;
}

// Function to display the Tic Tac Toe board
void display_board(TicTacToeBoard * board) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf(" %c ", board->board[row][col]);
            if (col < 2) {
                printf("|");
            }
        }
        if (row < 2) {
            printf("\n---+---+---\n");
        }
    }
    // Your code here
}

// Function to initialize the Tic Tac Toe board with empty cells
void initialize_board(TicTacToeBoard* board) {
    //setting every spot in the board to a empty space
    for (int row =0; row <3; row++) { 
        for (int col = 0; col < 3; col++) {
            board->board[row][col] =' ';
        }
    }
    board->current_player = 'X'; //setting the first player to be X
}

// Function to make a move on the Tic Tac Toe board
int make_move(TicTacToeBoard * board, int row, int col) {
    //decreasing values by 1 so they can be input properly into the array
    row = row - 1; 
    col = col - 1;

    //checking if the position entered is valid and if the space is empty
    if (row < 0 || row > 2 || col < 0 || col > 2 || board->board[row][col] != ' ') { 
        return 0;
    }

    board->board[row][col] = board->current_player; //entering the current players letter into the board
    board->current_player = (board->current_player == 'X') ? 'O' : 'X'; //switching current player
   
    return 1;

    // Your code here
}

// Function to check if a player has won
int check_win(TicTacToeBoard* board, char player) {
    //this loop checks if game is one by either a full row or full col
    for (int i = 0; i < 3; i++) {
        if (board->board[i][0] == player && board->board[i][1] == player && board->board[i][2] == player) {
            return 1;
        }
        else if (board->board[0][i] == player && board->board[1][i] == player && board->board[2][i] == player) {
            return 1;
        }
    }
    //this loop checks if game is one by checking the two diagonal options
    if (board->board[0][0] == player && board->board[1][1] == player && board->board[2][2] == player) {
        return 1;
    }
    else if (board->board[2][0] == player && board->board[1][1] == player && board->board[0][2] == player) {
        return 1;
    }
    else {
        return 0;
    }
}

// Function to check if the game is a draw
int check_draw(TicTacToeBoard* board) {
    //loops check if there is any empty spaces in the file and game will continue if there are
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board->board[row][col] == ' ')
                return 0;
        }
    }
    return 1;
}

// Function to save the game state to a file
void save_board_to_file(TicTacToeBoard* board, char* file_path) {
    FILE* inPtr;
    inPtr = fopen(file_path, "w"); //creating file to write the board game into
    
    //printing the rows and columns using the same for loop as display 
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            fprintf(inPtr," %c ", board->board[row][col]);
            if (col < 2) {
                fprintf(inPtr, "|");
            }
        }
        if (row < 2) {
            fprintf(inPtr, "\n---+---+---\n");
        }
    }
}

// Function to load the game state from a file
void load_board_from_file(TicTacToeBoard* board, char* file_path) {
  
}