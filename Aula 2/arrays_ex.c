#include <stdio.h>
#include <stdlib.h>

void PrintArray(char s[], int a[], size_t n){
    int i=0;
    printf("%s : %d",s,a[i]);
    for(size_t i = 1;i < n;i++){
        printf(", %d",a[i]);
    }
    printf("\n");
}

void CumulativeSum(int a[], int b[], size_t n){
    b[0] = a[0];
    for(size_t i = 1;i < n;i++){
        b[i] = b[i-1] + a[i];
    }
}

int main(){
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int b[10];
    PrintArray("Primeiro Array",a,10);
    CumulativeSum(a,b,10);
    PrintArray("Somas",b,10);
    return 0;
}