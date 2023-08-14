#include <iostream>

int main(){
    int y;
    std::cout << "Contagem ate que numero:";
    std::cin >> y;

    for(int i = 0; i<=y ; i++){
        std::cout << "(" << i << ")" << std::endl;
    }
    return 0;
}