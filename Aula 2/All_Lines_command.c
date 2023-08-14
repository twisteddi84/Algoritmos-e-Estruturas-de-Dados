#include <stdio.h>
#include <stdlib.h>

int IsInteger(char *string){
    int i = 0;
    if(string[0] == '+' || string[0] == '-'){
        if(string[1] == '\0'){
            return 0;
        }
        i = 1;
    }

    while(string[i] != '\0'){
        if(string[i] < '0' || string[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc,char *argv[argc])
{
    for(size_t i = 0;i < argc;i++){
        char *token = argv[i];
        if(IsInteger(token)){
            printf("argv[%2lu] = \"%s\" integer value:%ld\n",i,token,atol(token));
        }else{
            printf("argv[%2lu] = \"%s\"\n",i,token);
        }


    }       
    return 0;
}
