#include "../lib/caesar.h"
#include <iostream>
#include <string>

int main(){
    std::string plain = "meet at the midnight";
    std::string cipher;
    Caesar caesar;
    caesar.encrypt(plain, cipher);
    std::cout << cipher ;
}