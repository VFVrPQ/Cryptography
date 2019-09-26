#ifndef HILL_H
#define HILL_H

#include <iostream>
#include <string>

using namespace std;
class Hill{
    public:
        Hill(int nn, int *k[]);
        ~Hill();
        string encrypt(string plain); //加密
        string decrypt(string cipher); //解密
    private:
        int n;
        int **key;
        int **Dkey;
        int hasDkey=0;
        //int key[N][N]; // matrix ?*?
        Hill();
        string prepareInput(string plain);
        void makeDecryptKey();
        void calc(int *p, int **key, int *c);
        void debug(){
            for (int i=0;i<5;i++){
                for (int j=0;j<5;j++){
                    printf("%c",key[i][j]);
                }
                printf("\n");
            }
        }
};
#endif // HILL_H