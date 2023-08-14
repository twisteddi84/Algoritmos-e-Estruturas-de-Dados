#include <stdio.h>

int array_to_num(int *arr, int n){
    int i=0, size;
    int b=0;
    int mult = 1;
    size = sizeof(arr)/sizeof(arr[0]);
    for(i=0;i<n;i++)
    {
        if((arr[i] < 0) ||(arr[i]>9)) return -1;
        if(i==0)
        {
            b += arr[i];
        }
        else
        {
            b *= 10;
            b += arr[i];
        }
    }
    return b;   
}

//function to print the array
void printarray(int arr[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}

//function to swap the variables
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permutation(int *arr, int start, int end)
{
    if(start==end)
    {
        //printarray(arr, end+1);
        int numero = 0;
        numero = array_to_num(arr,10);
        if(numero%10 == 0){
            int novo_numero = numero/10;
            if(novo_numero%9==0){
                novo_numero = numero/10;
                if(novo_numero%8 ==0){
                    novo_numero = numero/10;
                    if(novo_numero%7==0){
                        novo_numero = numero/10;
                        if(novo_numero%6 ==0){
                            novo_numero = numero/10;
                            if(novo_numero%5==0){
                                novo_numero = numero/10;
                                if(novo_numero%4 ==0){
                                    novo_numero = numero/10;
                                    if(novo_numero%3==0){
                                        novo_numero = numero/10;
                                        if(novo_numero%2 ==0){
                                            printf("%d",numero);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}

int main()
{
    //taking input to the array
    int size = 10;
    int arr[10] = {1,2,3,4,5,6,7,9,0};
    //calling permutation function
    permutation(arr, 0, size-1);
    return 0;
}