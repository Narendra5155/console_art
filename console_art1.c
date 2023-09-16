#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define microsecond 1000
int Row_size=39;
int Column_size=21;
//time delay between frames
int time =100;

void printHelp(){
    printf("The syntax is \n .\\console_art1 -t \"YOUR TEXT TO ANIMATE\"");
    printf("\nUse the \n-h --help\t to print this messeage\n");
    printf("-r --rows\t to change to size of rows DEFAULT=%d [1-80]\n",Row_size);
    printf("-c --column\t to change the size of column DEFAULT=%d [0-29]\n",Column_size);
    printf("-t --text \t to use custom text\n");
    printf("-q --time \t to set the time delay between frames DEFAULT=%dms\n",time);
    exit(1);
}

void printBox(){
    printf("\033[H\033[J");
    printf(" ");
        for(int i=1;i<=Row_size+1;i++)
            printf("_");
    printf(" \n");
        
        for(int i=1;i<=Column_size;i++){
             printf("|\033[%d;%dH",i+1,Row_size+3);
             printf("|\n");
        }
    printf("|");
        for(int i=0;i<=Row_size;i++)
            printf("-");
    printf("|\n");
}

int main(int argc, char *argv[]){
    //setting a default text
    char* name;
    name=(char*)calloc(4,sizeof(char));
    strcpy(name,"DVD");

    for(int iarg=1;iarg<argc;iarg++){
    if(strcmp(argv[iarg],"-h")==0|| strcmp(argv[iarg],"--help")==0)
        printHelp();
    else if(strcmp(argv[iarg],"-t")==0 || strcmp(argv[iarg],"--text")==0){
        if(iarg+1==argc)
            {
                fprintf(stderr,"Error: missing the text input");
            }
            iarg++;
        name=(char*)calloc(strlen(argv[iarg]),sizeof(char));
        if(name==NULL){
            fprintf(stderr,"Error: invalid string");
            printHelp();
        }
        strcpy(name,argv[iarg]);
    }
    else if(strcmp(argv[iarg],"-r")==0 || strcmp(argv[iarg],"--row")==0){
        if(iarg+1==argc)
            {
                fprintf(stderr,"Error: missing the Size of rows\n");
            }
            iarg++;
        
        if(sscanf(argv[iarg],"%d",&Row_size)!=1 || Row_size>80 || Row_size<0){
        fprintf(stderr,"Error: Invalid size of rows = %s\n",argv[iarg]);
        printHelp();
        }
    }
    else if(strcmp(argv[iarg],"-c")==0 || strcmp(argv[iarg],"--column")==0){
    if(iarg+1==argc)
        {
            fprintf(stderr,"Error: missing the Size of column\n");
        }
        iarg++;
    
    if(sscanf(argv[iarg],"%d",&Column_size)!=1 || Column_size>30 || Column_size<0){
    fprintf(stderr,"Error: Invalid size of column = %s\n",argv[iarg]);
    printHelp();
    }
    
    }
    else if(strcmp(argv[iarg],"-q")==0 || strcmp(argv[iarg],"--time")==0){
    if(iarg+1==argc)
        {
            fprintf(stderr,"Error: missing the time delay\n");
        }
        iarg++;
    
    if(sscanf(argv[iarg],"%d",&time)!=1 || time<0){
    fprintf(stderr,"Error: Invalid amount of time = %s\n",argv[iarg]);
    printHelp();
    }
    }
    else{
        fprintf(stderr,"Error : Invalid flag\n");
        printHelp();
    }
    }

    //velocity
    int vertical_velocity=1;
    int horizontal_velocity=1;                    
    
    //initial position
    int y=(int)Column_size/2;                                           
    int x =1;
    if(y%2!=Column_size%2)
    y--;                       
    
    //setting the width that it remain constant regarless of what string is input
    int width=strlen(name);
        width=Row_size-width; 

    //Creating a mask
    char* mask;
    mask=(char*)calloc(strlen(name)+1,sizeof(char));
    for(int i=0;i<strlen(name);i++)
    mask[i]=' ';
    mask[strlen(name)]='\0';
    
    printf("\033[?25l");                            //hiding the cursor 
    
    printBox();

    while(1){
        //erasing the text from previous loop  
        printf("\033[%d;%dH",y+1,x+1);                  //moving the cursor the coordinate
        printf("%s",mask);                              //printing the mask           
        
        //new coordinates
        y=y+vertical_velocity;                           
        if(y>=Column_size|| y<=1)                        // change the pivit direction once it reaches an extreme
        vertical_velocity=-vertical_velocity;
        x=x+horizontal_velocity;
        if(x>width+1 || x<=1)
        horizontal_velocity=-horizontal_velocity;
        
        //printing the text 
        printf("\033[%d;%dH",y+1,x+1);
        printf("%s",name);
        
        //halting the loop for some time
        usleep(time*microsecond);                                  
    }

}