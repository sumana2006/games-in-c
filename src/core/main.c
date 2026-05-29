#include<stdio.h>
#include "games/snake.h"
#include "platform.h"
#include "common.h"

int main(){
    int n;
    printf("\t\t\t %s....WELCOME TO C GAME TRIO....%s",Yellow,color_end       );
    printf("\n%sBelow are three game choices:%s",Yellow,color_end);
    printf("\n%s1. Tic Tac Toe",Green);
    printf("\n2. Snake Game");
    printf("\n3. KBCC%s",color_end);
   printf("\n%sWhich game do you want to play?",Yellow);
   printf("\nEnter option number:%s",color_end);
   scanf("%d",&n);
   switch(n){
   case 1:
   tic_tac_toe();
   break;
   case 2:
{
    SnakeState s;

    snake_startup();

    snake_init(&s);

    while (!snake_is_over(&s))
    {
        snake_input(&s);
        snake_update(&s);
        snake_render(&s);

        sleep_ms(s.tick_delay);
    }

    snake_cleanup();

    printf("Game Over!\n");
    printf("Your score is: %d\n", s.score);

    break;
}
   case 3:
   kbcc();
   break;

   }

    return 0;
}
