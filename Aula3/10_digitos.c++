#include <bits/stdc++.h>

using namespace std;

int VectorToInt(vector<int> v)
{
    reverse(v.begin(), v.end());
    int decimal = 1;
    int total = 0;
    for (auto& it : v)
    {
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}

int main()
{
    //Obtaining length of array
    int n = 10;

    //Declaring a vector of integers
    vector<int> a(n);
    
    //Taking input of array of integers
    for(int i=0; i<n; i++){
        a[i] = i;
    }

    do{
        //Display the current permutation
        int result = 0;
        for (auto d : a)  
        {
            result = result * 10 + d;
        }
        cout << result;
    }while(next_permutation(a.begin(), a.end())); //Generate next permutation till it is not lexicographically largest

    return 0;
}

