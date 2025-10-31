#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_LEN   20

struct Point {
    int r;
    int c;
};

struct Snake {
    int size;
    int apples_eaten;
    struct Point *body[BOARD_LEN*BOARD_LEN];
};

int init_snake(struct Snake*);
int place_snake(char board[][BOARD_LEN], struct Snake*);
int setup_board(char board[][BOARD_LEN]);
int print_board(char board[][BOARD_LEN]); 
int process_input();
int move_snake();
int eat_apple();
int place_snake(char board[][BOARD_LEN], struct Snake *);

int main() {
    char board[BOARD_LEN][BOARD_LEN];
    struct Snake my_snake= {};
    setup_board(board);
    init_snake(&my_snake);
    place_snake(board, &my_snake);
    print_board(board); 
}

int init_snake(struct Snake *my_snake) {
    my_snake->size = 0;
    my_snake->apples_eaten = 0;

    // Place a length of 3 in the middle of the board
    int mid_idx = BOARD_LEN / 2;
    struct Point *back = (struct Point *)malloc(sizeof(struct Point));
    back->r = mid_idx;  
    back->c = mid_idx - 1;
    struct Point *mid = (struct Point *)malloc(sizeof(struct Point));
    mid->r = mid_idx;
    mid->c = mid_idx;
    struct Point *front = (struct Point *)malloc(sizeof(struct Point));
    front->r = mid_idx;
    front->c = mid_idx + 1;
    my_snake->body[0] = back;
    my_snake->body[1] = mid;
    my_snake->body[2] = front;
    my_snake->body[3] = '\0';
}

int place_snake(char board[][BOARD_LEN], struct Snake *my_snake) {
    // Look through all the points, and place them 
    struct Point **pp = my_snake->body;
    
    for (int i = 0; *(pp + i) != NULL; i++) {
        int r = (*(pp + i))->r;
        int c = (*(pp + i))->c;
        board[r][c] = '-';
    } 
}

int setup_board(char board[][BOARD_LEN]) {
    for (int i = 0; i < BOARD_LEN; i++) {
        for (int j = 0; j < BOARD_LEN; j++) {
            board[i][j] = ' ';
        }
    }

    // Place border
    for (int i = 0; i < BOARD_LEN; i++) {
        board[0][i] = '\\';
    }
    for (int i = 0; i < BOARD_LEN; i++) {
        board[BOARD_LEN-1][i] = '\\';    
    }
    for (int i = 0; i < BOARD_LEN; i++) {
        board[i][0] = '\\';    
    }
    for (int i = 0; i < BOARD_LEN; i++) {   
        board[i][BOARD_LEN-1] = '\\';    
    }

    return 1;
}

int print_board(char board[][BOARD_LEN]) {
    for (int i = 0; i < BOARD_LEN; i++) {
        for (int j = 0; j < BOARD_LEN; j++) {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

int process_input() {
    
}

int move_snake() {

}

int eat_apple() {

}
