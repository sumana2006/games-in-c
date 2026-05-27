#include<stdio.h>
#include "B24CH1028_B24CS1076_B24CH1049_B24CS1049_B24CM1062_headerfile.h"

int main(){
    int n;
    printf("\t\t\t %s....WELCOME TO C GAME TRIO....%s",Yellow,color_end       );
    printf("\n%sBelow are three game choices:%s",Yellow,color_end);
    printf("\n%s1. Tic Tac Toe",Green);
    printf("\n2. Snake Game");
    printf("\n3.KBCC%s",color_end);
   printf("\n%sWhich game do you want to play?",Yellow);
   printf("\nEnter option number:%s",color_end);
   scanf("%d",&n);
   switch(n){
   case 1:
   tic_tac_toe();
   break;
   case 2:
   snake();
   break;
   case 3:
   kbcc();
   break;

   }

    return 0;
}