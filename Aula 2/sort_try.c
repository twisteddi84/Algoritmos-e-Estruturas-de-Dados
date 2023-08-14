#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int array1[10] = {3,2,6,2,4,5,7,2,1,9};
int array2[10];

int main(){
    int valor_min = array1[0];    int min = array1[0];
    int index_temp;
    int valor_max = array1[0];
    for(int i = 0;i<10;i++){
        if(valor_max<array1[i]){
            valor_max = array1[i];
        }
    }
    for(int i = 0; i<10;i++){
        for(int j = 0; j<10;j++){
            if(valor_min>array1[j] && array1[j] != 0){
                valor_min = array1[j];
                index_temp = j;
            }
        }
        array2[i] = valor_min;
        array1[index_temp] = 0;
        valor_min = valor_max;
    
    }

    for(int x = 0;x<10;x++){
        printf("%d ",array2[x]);
    }

}
