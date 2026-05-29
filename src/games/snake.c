#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "games/snake.h"




// int main()
// {
//     // hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // hideCursor();
    
    // printf("Controls: W = up, S = down, A = left, D = right\n");
    // printf("Press any key to start...");
    // getch();
    
    // system("cls"); // Clear initial screen
    // setup();
    
    // while (gameend != 1)
    // {
    //     input();
    //     makelogic();
    //     drawboard();
    //     Sleep(200);
    // }
    
    // // Show cursor again after game ends
    // CONSOLE_CURSOR_INFO cursorInfo;
    // GetConsoleCursorInfo(hConsole, &cursorInfo);
    // cursorInfo.bVisible = TRUE;
    // SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    // system("cls");
    // printf("Your score is: %d\n", score);
    // return 0;
//}

void snake_startup()
{
    clear_screen();
    hide_cursor();

    printf("Controls: W = up, S = down, A = left, D = right\n");
    printf("Press any key to start...");
    get_key();

    clear_screen();
}

void snake_update(SnakeState *s)
{
    // ----------------------------
    // Tail movement logic
    // ----------------------------
    int prevx = s->tailx[0];
    int prevy = s->taily[0];

    s->tailx[0] = s->x;
    s->taily[0] = s->y;

    for (int i = 1; i < s->pieces; i++) {
        int tempX = s->tailx[i];
        int tempY = s->taily[i];

        s->tailx[i] = prevx;
        s->taily[i] = prevy;

        prevx = tempX;
        prevy = tempY;
    }

    // ----------------------------
    // Movement direction
    // ----------------------------
    switch (s->direction) {

    case DIR_UP:
        s->x--;
        break;

    case DIR_DOWN:
        s->x++;
        break;

    case DIR_LEFT:
        s->y--;
        break;

    case DIR_RIGHT:
        s->y++;
        break;

    default:
        break;
}

    // ----------------------------
    // Wall collision
    // ----------------------------
    if (s->x <= 0 || s->x >= s->height - 1 || s->y <= 0 || s->y >= s->width - 1) {
        s->game_over = 1;
        return;
    }

    // ----------------------------
    // Fruit collision
    // ----------------------------
    if (s->x == s->fruit_x && s->y == s->fruit_y) {
        s->score += 10;
        s->pieces++;

        do {
            s->fruit_x = rand() % (s->height - 2) + 1;
            s->fruit_y = rand() % (s->width - 2) + 1;
        } while (s->fruit_x == s->x && s->fruit_y == s->y);
    }

   
    // Tail collision
    
    for (int i = 0; i < s->pieces; i++) {
        if (s->tailx[i] == s->x && s->taily[i] == s->y) {
            s->game_over = 1;
            return;
        }
    }
}


void snake_input(SnakeState *s)
{
    if (kbhit()) {

        switch (get_key()) {

            case 'w':
            case 'W':
                if (s->direction != DIR_DOWN)
                    s->direction = DIR_UP;
                break;

            case 's':
            case 'S':
                if (s->direction != DIR_UP)
                    s->direction = DIR_DOWN;
                break;

            case 'a':
            case 'A':
                if (s->direction != DIR_RIGHT)
                    s->direction = DIR_LEFT;
                break;

            case 'd':
            case 'D':
                if (s->direction != DIR_LEFT)
                    s->direction = DIR_RIGHT;
                break;
        }
    }
}


void snake_init(SnakeState *s)
{
     s->height = SNAKE_DEFAULT_HEIGHT;
     s->width = SNAKE_DEFAULT_WIDTH;
     s->tick_delay = 300;

    // Initial position
    s->x = s->height / 2;
    s->y = s->width / 2;

    // Initialize tail
    for (int i = 0; i < SNAKE_MAX_TAIL; i++) {
        s->tailx[i] = s->x;
        s->taily[i] = s->y;
    }

    // Fruit position
    s->fruit_x = rand() % (s->height - 2) + 1;
    s->fruit_y = rand() % (s->width - 2) + 1;

    // Reset game state
    s->score = 0;
    s->pieces = 0;
    s->game_over = 0;
    s->direction = DIR_NONE;
}

void snake_render(SnakeState *s)
{
    // Set cursor to top-left instead of clearing screen
    move_cursor(0, 0);
    
    int ch;
    for (int i = 0; i <= s->height; i++)
    {
        for (int j = 0; j <= s->width; j++)
        {
            if (i == 0 || i == s->height || j == 0 || j == s->width)
            {
                printf("%c", SNAKE_BORDER);
            }
            else
            {
                if (i == s->x && j == s->y)
                {
                    printf("%c", SNAKE_HEAD);  // Snake head
                }
                else if (i == s->fruit_x && j == s->fruit_y)
                {
                    printf("%c", SNAKE_FRUIT);  // Fruit
                }
                else
                {
                    ch = 0;
                    for (int k = 0; k < s->pieces; k++)
                    {
                        if (i == s->tailx[k] && j == s->taily[k])
                        {
                            printf("%c", SNAKE_BODY);  // Snake body
                            ch = 1;
                        }
                    }
                    if (ch == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", s->score);  // Score display
}


void snake_cleanup()
{
    show_cursor();
}

int snake_is_over(SnakeState *s)
{
    return s->game_over;
}




