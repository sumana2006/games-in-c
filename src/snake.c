#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "headerfile.h"

void snake();
// Game variables
int height = 20, width = 20;
int x, y, fruit_x, fruit_y, flag;
int gameend, score = 0;
int pieces = 0;
int tailx[50], taily[50];


// Function prototypes
void drawboard();
void setup();
void input();
void makelogic();



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

void makelogic()
{
    // Tail movement logic
    int prevx = tailx[0];
    int prevy = taily[0];
    tailx[0] = x;
    taily[0] = y;
    
    for (int i = 1; i < pieces; i++) {
        int tempX = tailx[i];
        int tempY = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = tempX;
        prevy = tempY;
    }

    // Movement direction
    switch (flag) {
        case 1: x--; break; // Up
        case 2: x++; break; // Down
        case 3: y--; break; // Left
        case 4: y++; break; // Right
    }

    // Wall collision
    if (x <= 0 || x >= height-1 || y <= 0 || y >= width-1) {
        gameend = 1;
    }

    // Fruit collection
    if (x == fruit_x && y == fruit_y) {
        score += 10;
        pieces++;
        
        // Generate new fruit position
        do {
            fruit_x = rand() % (height-2) + 1;
            fruit_y = rand() % (width-2) + 1;
        } while (fruit_x == x && fruit_y == y);
    }

    // Tail collision
    for (int i = 0; i < pieces; i++) {
        if (tailx[i] == x && taily[i] == y) {
            gameend = 1;
            break;
        }
    }
}

void input()
{
    if (kbhit()) {
            switch (get_key()) {
                case 'w': if (flag != 2) flag = 1; break;
                case 's': if (flag != 1) flag = 2; break;
                case 'a': if (flag != 4) flag = 3; break;
                case 'd': if (flag != 3) flag = 4; break;
            }
      }
    }


void setup()
{
    // Initial positions
    x = height / 2;
    y = width / 2;
    for(int i=0;i<50;i++){
        tailx[i] = x;
        taily[i] = y;
    }
    
    // Initial fruit position
    fruit_x = rand() % (height-2) + 1;
    fruit_y = rand() % (width-2) + 1;
    
    // Reset game state
    gameend = 0;
    score = 0;
    pieces = 0;
}

void drawboard()
{
    // Set cursor to top-left instead of clearing screen
    move_cursor(0, 0);
    
    int k, ch;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || i == height || j == 0 || j == width)
            {
                printf("*");
            }
            else
            {
                if (i == x && j == y)
                {
                    printf("O");  // Snake head
                }
                else if (i == fruit_x && j == fruit_y)
                {
                    printf("@");  // Fruit
                }
                else
                {
                    ch = 0;
                    for (k = 0; k < pieces; k++)
                    {
                        if (i == tailx[k] && j == taily[k])
                        {
                            printf("o");  // Snake tail
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
    printf("Score: %d\n", score);  // Score display
}
void snake(){

    clear_screen();
    hide_cursor();

    printf("Controls: W = up, S = down, A = left, D = right\n");
    printf("Press any key to start...");
    get_key();

    clear_screen();

    setup();

    while (gameend != 1)
    {
        input();
        makelogic();
        drawboard();
        sleep_ms(200);
    }

    show_cursor();

    printf("Game Over!\n");
    printf("Your score is: %d\n", score);
}


