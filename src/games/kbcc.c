#include "platform.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "common.h"
void kbcc();
// colors ke liye colors.c file banayi hai , colors ko headerfile me define kiye and colors.c me intialise
typedef struct que_bank{
    char que_text[400];
    char options[4][200];
    char corr_ans;
    int time_out;
    int prize_money;
}que_bank;

void play_game(que_bank question){
    
    int time_left = question.time_out;
    char ans;
   

    while(time_left>0){
        if(kbhit()){// iske liye coni.h file include ki hai , ye check karega keyboard hit hua ya nhi..
            ans = get_key(); // ye bina enter press kiye hi input le leta hai
            ans =  toupper(ans);
            printf("%c\n",ans);
            if(ans==question.corr_ans){
                printf("%sCongrats!! You have entered the correct answer.\n%s",Green,color_end);
                printf("%sYou are awarded with %d points.%s\n",Pink,question.prize_money,color_end);

            }
            if(ans != 'A' &&ans != 'B' &&ans != 'C' && ans != 'D' ){
                printf("%sOption is not available!!!%s",Red,color_end);
                printf("\n%sYour winings are 0.%s",Red,color_end);
            }
            else if(ans!=question.corr_ans && (ans=='A' ||ans=='B' ||ans=='C' ||ans=='D' )){
        
                printf("%sWrong!! correct answer is %c%s",Red,question.corr_ans,color_end);
                printf("\n%sYour winings are 0.%s",Red,color_end);
                exit(0);
        // wrong answer par pura code hi terminate kar jayega..
            }
           
          return;
        }
        sleep_ms(1000);
        time_left--;
    }
    
        printf("%sYour time is out!!!%s",Red,color_end);
        printf("\n%sYou did not answer the question.\nYour winnings are 0.%s",Red,color_end);
    
}
void print_que(que_bank question){
    printf("\n");
    printf("%s%s%s",Yellow,question.que_text,color_end);
    printf("%sA.%s%s",Blue,question.options[0],color_end);
    printf("%sB.%s%s",Blue,question.options[1],color_end);
    printf("%sC.%s%s",Blue,question.options[2],color_end);
    printf("%sD.%s%s",Blue,question.options[3],color_end);
    printf("%sHurry!! You have only %d seconds to answer..%s\n",Yellow,question.time_out,color_end);
    printf("%sEnter your answer (A, B, C or D):%s\n",Green,color_end);
    play_game(question);
    


}
int read_que(char* file_name , que_bank** question){
    FILE* file = fopen(file_name,"r");
    if(file==NULL){
        printf("Unable to access..");
        exit(0);
    }
    char str[400];
    int no_lines = 0;
    while(fgets(str,400,file)!=0){
        no_lines++;
    }
    rewind(file);
    int no_que = no_lines/8;
    *question = (que_bank*)malloc(no_que*sizeof(que_bank));
   
    for(int i =0; i<no_que; i++){
        fgets((*question)[i].que_text , 400,file);
        for(int j =0; j<4; j++){
            fgets((*question)[i].options[j] , 200,file);
        }

        char ans[10];
        fgets(ans,10,file);
        (*question)[i].corr_ans = ans[0];

        char time[10];
        fgets(time,10,file);
        (*question)[i].time_out = atoi(time);

        char reward[10];
        fgets(reward,10,file);
        (*question)[i].prize_money = atoi(reward);
        
    }
    // printf("%sCongrats!!! You have won the game!!!\nThank you for playing%s",Pink,color_end);
    return no_que;
}
// int main(){
//     que_bank* question;
//     int no_que = read_que("KBCquebank.txt",&question);
//     printf("\t\t\t\t%sChalo khelte hai KON BANEGA CRORPATI IN C urf KBCC!!!\n%s",Pink,color_end);
//     for(int i =0; i<no_que; i++){
//         print_que((*question)[i]);
//     }
//     printf("%sCongrats!!! You have won the game!!!\nThank you for playing%s",Pink,color_end);

//     return 0;
// }
void kbcc(){
    que_bank* question;
    int no_que = read_que("data/KBCCquebank.txt",&question);
    printf("\t\t\t\t%sChalo khelte hai KON BANEGA CRORPATI IN C urf KBCC!!!\n%s",Pink,color_end);
    for(int i =0; i<no_que; i++){
        print_que((question)[i]);
    }
    printf("%sCongrats!!! You have won the game!!!\nThank you for playing%s",Pink,color_end);

}




















































