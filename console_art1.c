#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<unistd.h>
#include<conio.h>
#define microsecond 1000
#define Max_size 39
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
    if(argv[argc]==NULL){
        printf("Please Enter the word to animate\n");
        return 1;
    }

    int size,direction,pivit,a;
    a=-2;
    pivit=10;
    direction=1;
    char* name;
    name=(char*)calloc(Max_size,sizeof(char));
    strcpy(name,argv[1]);
    size=strlen(name);
    int empty_space=Max_size-size;
    char space[empty_space+1];
    for(int i=0;i<empty_space;i++)
    space[i]=' ';
    space[empty_space]='\0';
   // name=realloc(name,30*sizeof(char));
    strcat(name,space);
    while(1){
        pivit=pivit+a;
        if(pivit>=20|| pivit<=1)
        a*=-1;
        system("cls");
            printf(" _______________________________________ \n");
        for(int i=1;i<pivit;i++)
            printf("|                                       |\n");
        printf("|%s|\n",name);
        for(int i=pivit+1;i<=20;i++){
            if(i==1)
                continue;
            printf("|                                       |\n");
        }
            printf("|---------------------------------------|\n");
        animate(name,direction);
        if(name[0]!=' ')
        direction=1;
        if(name[Max_size-2]!=' ')
        direction=-1;
        usleep(100*microsecond);
    }

}