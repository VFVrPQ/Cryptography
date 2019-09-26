#include <string>
#include <iostream>
using namespace std;

class AES{
    public:

    private:
        void substitutionBytes(char bef[4][4], char aft[4][4]);//字节代换
        void shiftRows(char bef[4][4], char aft[4][4]);//行置换
        void mixColumns(char bef[4][4], char aft[4][4]);//列混淆
        void AddRoundKey(char bef[4][4], char aft[4][4], int round);//密钥的异或运算
        //void expandKey();
};