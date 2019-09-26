#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <string>
#include <vector>

class Caesar{
    public:
        Caesar(){}
        bool encrypt(std::string plain, std::string &cipher); //加密
        bool decrypt(std::string cipher, std::string &plain); //解密
    private:
        const int offset = 3; // 偏移量
        const std::string alphabet[26] = {
            "A","B","C","D","E","F","G","H","I","J",
            "K","L","M","N","O","P","Q","R","S","T",
            "U","V","W","X","Y","Z"
        };
};

#endif // CAESARCIPHER_H