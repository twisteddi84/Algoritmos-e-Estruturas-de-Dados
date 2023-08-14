#include <iostream>

int main(){
    int x;
    std::cout << "Escreve a tua idade:";
    std::cin >> x;
    int y = 2022 - x;
    std::cout << "Nasceste em: " << y << std::endl;
    return 0;
    
}