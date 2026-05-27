#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "headerfile.h"
void tic_tac_toe();


#define BOARD_SIZE  3

int difficulty;
typedef struct{
    int player;
   int computer;
    int draw;
}Score;
Score scoreT = {.player = 0, .computer = 0, .draw = 0};// we are using scortT not score as it is already used in snake 
void input_difficulty();
void clear_screen();
void print_board_score(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE],char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_gameT();
void player_move(char board[BOARD_SIZE][BOARD_SIZE],char player);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);



// int main(){ 
//     srand(time(NULL));
//     int choice;
//    input_difficulty();
//  do{  play_gameT();
//    printf("\nDo you want to play again? If yes enter 1 otherwise 0: ");
//    scanf("%d",&choice);
// if(choice==1) input_difficulty();
// }while(choice==1);
//    printf("%sBye Bye!!! Thanks for playing!!!%s",Pink,color_end);

//     return 0;
// }

void input_difficulty(){
    while(1){
        printf("\nSelect difficulty level:");
        printf("\n1.Human(Standard)");
        printf("\n2.God(Very hard to win)");
        printf("\nEnter your choice:");
        scanf("%d",&difficulty);
    if(difficulty!=1 && difficulty!=2) {
        printf("\n\nWrong choice !!!\n Select from 1 or 2!!! ");
    }
    else{
        break;
    }
}// ye while loop tab tak run karega jab tak sahi input nhi de dete..
}



void print_board_score(char board[BOARD_SIZE][BOARD_SIZE]){
    clear_screen();
    printf("Score - Player X - %d Computer - %d Draw - %d",scoreT.player,scoreT.computer,scoreT.draw);
    printf("\nTic Tac Toe\n");
    for(int i =0; i<BOARD_SIZE; i++){
        printf("\n");
        for(int j =0; j<BOARD_SIZE; j++){
            if(board[i][j]=='X'){
            printf(" %s%c%s ",Yellow,board[i][j],color_end);
        }
            else{
                printf(" %s%c%s ",Red,board[i][j],color_end);

            }
            if(j<BOARD_SIZE-1){
            printf("|");}
        }
        if(i<BOARD_SIZE-1){
            printf("\n---+---+---");
        }
    }
}


int check_win(char board[BOARD_SIZE][BOARD_SIZE],char player){

    for(int i =0; i<BOARD_SIZE; i++){
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player)
            return 1;

        if(board[0][i]==player && board[1][i]==player && board[2][i]==player)
            return 1;
    }

    if(
        (board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
        (board[0][2]==player && board[1][1]==player && board[2][0]==player)
      )
        return 1;

    return 0;
}


int check_draw(char board[BOARD_SIZE][BOARD_SIZE]){
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
            if(board[i][j]==' ')
                return 0;
        }
    }
    return 1;
}

void play_gameT(){
   
    char board[BOARD_SIZE][BOARD_SIZE] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char current_player;
    if(rand()%2==0) current_player = 'X';
    else current_player = 'O';
    print_board_score(board);

    while(1){
if(current_player=='X'){
    player_move(board,'X');
    print_board_score(board);

    current_player = 'O';
   if( check_win(board,'X')){
    scoreT.player++;
    print_board_score(board);

    printf("\n%sCongratulations!!! You have won the match.%s",Yellow,color_end);
    break;
   }

}

else{
    computer_move(board);
    print_board_score(board);
    current_player = 'X';


    if(check_win(board,'O')){
        scoreT.computer++;
    print_board_score(board);

        printf("\n%sI have won the match. But you played very well...%s",Red,color_end);
        break;
    }
}

if(check_draw(board)){
    scoreT.draw++;
    printf("\n%sIt is a draw!!!%s",LightBlue,color_end);
    break;
}
    }



}
void player_move(char board[BOARD_SIZE][BOARD_SIZE],char player ){
    int count = 0;
    int a = 0;
    int b = 0;
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
            if(board[i][j]==' ') {count++;
            a = i;
        b = j;
    }

        }
    }
    if(count==1){
    board[a][b] = 'X';
return;}
    int row,col;
   do{ printf("\nPlayer %c turn",player);
    printf("\nEnter row and column:");
    scanf("%d %d",&row,&col);
    row--;
    col--;}while(row<0 || col<0 || row>2 || col>2 || board[row][col]!=' ');
    board[row][col] = player;
}
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]){
    //1. Immediate win
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
           if(board[i][j]==' '){
            board[i][j] = 'O';
           
           if(check_win(board,'O')){ 
            return;
           }
            board[i][j] = ' ';}
        }
    }
    // 2. Stop opposite player
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
           if(board[i][j]==' '){
            board[i][j] = 'X';
           
           if(check_win(board,'X')){
            board[i][j] = 'O';
            return;
           }
            board[i][j] = ' ';}
        }
    }
    // God mode
    if(difficulty==2){
        // centre position
        if(board[1][1]==' ') {
            board[2][2] = 'O';
        return;}
        // check corner position
         if(board[0][0]==' ') {board[0][0] = 'O';
        return;}
         if(board[0][2]==' ') {board[0][2] = 'O';
        return;}
         if(board[2][0]==' ') {board[2][0] = 'O';
        return;}
        if(board[2][2]==' ') {board[2][2] = 'O';
        return;}


    }
    // 3. Remaining position par assign 
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
            if(board[i][j]==' '){
            board[i][j] = 'O';
            return;
        }
        }
    }
    
    
}
void tic_tac_toe(){
    srand(time(NULL));
    int choice;
   input_difficulty();
 do{  play_gameT();
   printf("\nDo you want to play again? If yes enter 1 otherwise 0: ");
   scanf("%d",&choice);
if(choice==1) input_difficulty();
}while(choice==1);
   printf("%sBye Bye!!! Thanks for playing!!!%s",Pink,color_end);

    
}
