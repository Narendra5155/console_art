#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define microsecond 1000
#define Row_size 80
#define Column_size 27

void printHelp(){
    printf("The syntax is \n .\\console_art1 \"YOUR TEXT TO ANIMATE\"");
    printf("\nUse the -h or -help flag to print this messeage\n");
}

void printBox(){
    printf("\033[H\033[J");
    printf(" ");
        for(int i=1;i<=Row_size+1;i++)
            printf("_");
    printf(" \n");
        
        for(int i=1;i<=Column_size;i++){
             printf("|");
             for(int j=0;j<=Row_size;j++)
                printf(" ");
             printf("|\n");
        }
    printf("|");
        for(int i=0;i<=Row_size;i++)
            printf("-");
    printf("|\n");
}

int main(int argc, char *argv[]){
    //Check if an argument is passed or not
    if(argv[1]==NULL){
        printf("No argument");
        return 1;
    }
    if(strcmp(argv[1],"-h")==0|| strcmp(argv[1],"--help")==0){
        printHelp();
        return 0;
        }

    //variable decleration
    int size,direction,pivit,a,b;
    a=-2;
    b=2;                                               //downword movement step
    pivit=9;                                           //initial position
    direction=1;                                        //direction of the lateral movement

    char* name;
    name=(char*)calloc(strlen(argv[1])+1,sizeof(char));          //string that stores the passed argument

    //Storing the string and appending the empty spaces around it
    strcpy(name,argv[1]);
    char* mask;
    mask=(char*)calloc(strlen(name)+1,sizeof(char));
    for(int i=0;i<strlen(name);i++)
    mask[i]=' ';
    mask[strlen(name)]='\0';
    size=strlen(name);
    size=Row_size-size;
    
    printBox();

    while(1){
        printf("\033[?25l");                            //hiding the cursor   
        printf("\033[%d;%dH",pivit+1,direction+1);
        printf("%s",mask);                                         
        pivit=pivit+a;                                  //pivit increment or decrement
        if(pivit>=Column_size|| pivit<=1)                        // change the pivit direction once it reaches an extreme
        a*=-1;
        direction=direction+b;
        if(direction>=size || direction<=1)
        b*=-1;
        printf("\033[%d;%dH",pivit+1,direction+1);
        printf("%s",name);
        
        usleep(100*microsecond);                                  //clearing the output buffer 
    }

}