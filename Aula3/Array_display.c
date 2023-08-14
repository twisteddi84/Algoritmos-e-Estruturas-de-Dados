#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void Display(int *a,size_t size){
    assert(a!=NULL && size>0);
    printf("Array = [");

    for(size_t i =0; i<size-1 ; ++i ){
        printf("%d, ",a[i]);

    }
    printf("%d] \n",a[size-1]);
}

int* Read(size_t *size){

    size_t n;
    printf("Array size:");
    scanf("%lu", &n);

    int* array = malloc(n*sizeof(int));
    if(array == NULL){
        *size = 0;
        return NULL;
    }

    for(size_t i = 0; i<n;i++){
        printf("A[%2lu] =", i);
        scanf ("%d",&array[i]);
    }

    *size = n;
    return array;
}

int* Append(int* array1,size_t size1,int* array2, size_t size2){
    size_t novo_size = size1 + size2;
    int *novo_array = malloc(novo_size * sizeof(int));

    for (size_t i = 0; i<size1;i++){
        novo_array[i] = array1[i];        
    }

    for(size_t i=0; i<size2; i++){
        novo_array[size1+i] = array2[i];
    }

    return novo_array;

}

int main(void){

    int* array1;
    size_t size1;
    array1 = Read(&size1);
    int* array2;
    size_t size2;
    array2 = Read(&size2);
    int*array3 = Append(array1,size1,array2,size2);
    Display(array3,6);
    

    return 0;

}