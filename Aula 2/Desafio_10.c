#include <stdio.h>
#include <stdlib.h>


int main(void){
    int n = 1234567899;
    int array[10];
    char *numero_char[10];

    if(n>999999999 && n<10000000000){

        for (size_t i = 10; i>0 ;i--){
            array[i-1] = n%10;
            n = n/10;
        }   

        for (size_t i = 0; i<10;i++){

            char c = array[i] + '0';
            numero_char[i]=c;
            printf("%c\n",numero_char[i]);

        }

    }


    return 0;
}