#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_LEN   20
#define LEFT        0
#define RIGHT       1
#define UP          2
#define DOWN        3

struct Point {
    int r;
    int c;
};

struct Pivot {
    struct Point *coordinates;
    int direction;    
};

struct Snake_Body {
    struct Point *piece;
    int direction; 
};

struct Snake {
    int size;
    int apples_eaten;
    struct Snake_Body *body[BOARD_LEN*BOARD_LEN];
};

int init_snake(struct Snake *);
int place_snake(char board[][BOARD_LEN], struct Snake *);
int setup_board(char board[][BOARD_LEN]);
int print_board(char board[][BOARD_LEN]); 
int process_input();
int move_snake(struct Snake *);
int eat_apple();
int place_snake(char board[][BOARD_LEN], struct Snake *);

int main() {
    char board[BOARD_LEN][BOARD_LEN];
    struct Snake my_snake= {};
    init_snake(&my_snake);
    setup_board(board);
    place_snake(board, &my_snake);
    print_board(board); 
    int success = 1;
    while (success) {
        system("clear");
        setup_board(board);
        move_snake(&my_snake);
        success = place_snake(board, &my_snake);
        if (!success)
            break;
        print_board(board); 
        usleep(100000);
    } 
    printf("Game Over\n");
}

int init_snake(struct Snake *my_snake) {
    my_snake->size = 0;
    my_snake->apples_eaten = 0;
    int mid_idx = BOARD_LEN / 2;

    struct Snake_Body *back = (struct Snake_Body *)malloc(sizeof(struct Snake_Body));
    struct Point *back_p = (struct Point *) malloc(sizeof(struct Point));
    back->piece = back_p;
    back->direction = RIGHT;
    back_p->r = mid_idx;  
    back_p->c = mid_idx - 1;

    struct Snake_Body *mid = (struct Snake_Body *)malloc(sizeof(struct Snake_Body));
    struct Point *mid_p = (struct Point *) malloc(sizeof(struct Point));
    mid->piece = mid_p;
    mid->direction = RIGHT;
    mid_p->r = mid_idx;
    mid_p->c = mid_idx;

    struct Snake_Body *front = (struct Snake_Body *)malloc(sizeof(struct Snake_Body));
    struct Point *front_p = (struct Point *) malloc(sizeof(struct Point));
    front->piece = front_p;
    front->direction = RIGHT;
    front_p->r = mid_idx;
    front_p->c = mid_idx + 1;

    my_snake->body[0] = back;
    my_snake->body[1] = mid;
    my_snake->body[2] = front;
    my_snake->body[3] = '\0';
}

int place_snake(char board[][BOARD_LEN], struct Snake *my_snake) {
    // Look through all the points, and place them 
    struct Snake_Body **pp = my_snake->body;
    for (int i = 0; *(pp + i) != NULL; i++) {
        int r = (*(pp + i))->piece->r;
        int c = (*(pp + i))->piece->c;
        if (r <= 0 || r >= BOARD_LEN-1 || c <= 0 || c >= BOARD_LEN-1) {
            return 0;
        } 
        board[r][c] = '.';
    } 
    return 1;
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

int move_snake(struct Snake *my_snake) {
    struct Snake_Body **body = my_snake->body;
    
    for (int i = 0; *(body + i) != NULL; i++) { 
        struct Snake_Body *curr_body = *(body + i); 
        switch (curr_body->direction) {
            case RIGHT:
                curr_body->piece->c++;
                break;
            case LEFT:
                curr_body->piece->c--;
                break;
            case UP:
                curr_body->piece->r++;
                break;
            case DOWN:  
                curr_body->piece->r--;
                break;
        }
    } 
}

int eat_apple() {

}
