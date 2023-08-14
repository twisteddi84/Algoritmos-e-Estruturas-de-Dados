#include <stdio.h>

int main(void){
    int a = 0;
    int b = 1;

    f1(a,b);
    printf("%d , %d \n",a,b);

    f2(&a,&b);
    printf("%d , %d \n",a,b);

    swap1(&a,&b);
    printf("%d , %d \n",a,b);

    return 0;
}


void f1(int a, int b){
    a = 10;
    b = 20;
}

void f2(int *a, int *b){
    *a = 100;
    *b = 200;
}

void swap1(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}