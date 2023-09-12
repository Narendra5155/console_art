#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define microsecond 1000
#define Max_size 39


/* Funtion to animate the string laterally */ 
void animate(char* text,int direction){
    int length=strlen(text);
    char temp[length+1];
    strcpy(temp,text);
    for(int i=0;i<length;i++){
        if(direction>0)
        text[(i+2)%length]=temp[i];
        else if(direction<0)
        text[i]=temp[(i+1)%length];
    }
}
int main(int argc, char *argv[]){
    //Check if an argument is passed or not
    if(argv[1]==NULL){
        printf("Please Enter the word to animate\n");
        return 1;
    }
    //variable decleration
    int size,direction,pivit,a;
    a=-2;                                               //downword movement step
    pivit=10;                                           //initial position
    direction=1;                                        //direction of the lateral movement

    char* name;
    name=(char*)calloc(Max_size,sizeof(char));          //string that stores the passed argument
    char* output;
    output=(char*)calloc(200,sizeof(char));             //frame string 

    //Storing the string and appending the empty spaces around it
    strcpy(name,argv[1]);
    size=strlen(name);
    int empty_space=Max_size-size;
    char space[empty_space+1];
    for(int i=0;i<empty_space;i++)
    space[i]=' ';
    space[empty_space]='\0';
    strcat(name,space);


    while(1){
        printf("\033[?25l");                            //hiding the cursor
        printf("\033[H\033[J");                         //clearing the console
        pivit=pivit+a;                                  //pivit increment or decrement
        if(pivit>=20|| pivit<=1)                        // change the pivit direction once it reaches an extreme
        a*=-1;

        // Storing the output data in a single frame to reduce flicker
        strcat(output," _______________________________________ \n");
        
        for(int i=1;i<pivit;i++)
             strcat(output,"|                                       |\n");
        
        strcat(output,"|");
        strcat(output,name);
        strcat(output,"|\n");
        
        for(int i=pivit+1;i<=20;i++){
            if(i==1)
                continue;
            strcat(output,"|                                       |\n");
        }
        
        strcat(output,"|---------------------------------------|\n");
        printf("%s",output);
        printf("\033[?25h");
        //animate the next frame
        animate(name,direction);
        if(name[0]!=' ')
            direction=1;
        if(name[Max_size-2]!=' ')
            direction=-1;
        usleep(100*microsecond);
        output[0]='\0';                                  //clearing the output buffer 
    }

}