#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <iostream>
#include <string>

using namespace std;
class Playfair{
    public:
        Playfair(string k);
        string encrypt(string plain, char x='X'); //加密
        string decrypt(string cipher); //解密
    private:
        char key[5][5]; // matrix 5*5
        bool vis[26]; // 标记是否使用过了，即在key里面了
        int pos_x[26], pos_y[26]; // 字母的key小标
        Playfair();
        string prepare_input(string plain, char x);
        void debug(){
            for (int i=0;i<5;i++){
                for (int j=0;j<5;j++){
                    printf("%c",key[i][j]);
                }
                printf("\n");
            }
        }
};
#endif // PLAYFAIR_H