#include "hill.h"

Hill::Hill(){}
Hill::Hill(int nn, int *k[]){ //传进来
    n = nn;
    key = new int*[n];
    for (int i=0;i<n;i++){ //创建空间
        key[i] = new int[n];
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            key[i][j] = k[i][j];
        }
    }
}
Hill::~Hill(){
    for (int i=0;i<n;i++){ //回收
        delete[] key[i];
    }
    delete key;
    if (hasDkey){
        for (int i=0;i<n;i++){ //回收
            delete[] Dkey[i];
        }
        delete Dkey;
        hasDkey=0;
    }
    
}
//  P(1*n) * key(n*n) = C(1*n)
string Hill::encrypt(string plain){ //加密
    string text = prepareInput(plain);
    string result;
    int len = text.length();
    int p[n], c[n];
    for (int i=0;i<len;i+=n){
        for (int j=0;j<n;j++){
            p[j] = text[i+j] - 'A';
        }
        calc(p, key, c);// p*key = c
        for (int j=0;j<n;j++){
            result += (char)(c[j]+'A');
        }
    }
    return result;
}

string Hill::decrypt(string cipher){ //解密
    makeDecryptKey();
    //假定cipher已经是N的倍数了，而且全部是大写字母
    string result;
    int len = cipher.length();
    int p[n], c[n];
    for (int i=0;i<len;i+=n){
        for (int j=0;j<n;j++){
            c[j] = cipher[i+j] - 'A';
        }
        calc(c, Dkey, p);// c * Dkey = p
        for (int j=0;j<n;j++){
            result += (char)(p[j]+'A');
        }
        
    }
    return result;
} 
// 只保留字母，并将所有字母转成大写
// 并做填充
string Hill::prepareInput(string plain){ 
    string text;
    int len = plain.length();
    int lenText = 0; // for text
    for (int i=0;i<len;i++){
        if (isalpha(plain[i])){
            text += toupper(plain[i]);
            lenText++;
        }
    }
    while (lenText%n!=0){ //填充
        text += text[lenText-1];
        lenText++;
    }
    //cout << text << endl;
    return text;
}

void Hill::makeDecryptKey(){ // not completed
    Dkey = new int*[n]; //allocate
    for (int i=0;i<n;i++){ //allocate
        Dkey[i] = new int[n];
    }
    hasDkey=1;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            Dkey[i][j] = key[i][j];
        }
    }
    if (n==2){
        swap(Dkey[0][0], Dkey[1][1]);
        Dkey[0][1] = -Dkey[0][1];
        Dkey[1][0] = -Dkey[1][0];

        int val = 23;
        for (int i=0;i<2;i++){
            for (int j=0;j<2;j++){
                Dkey[i][j] = (Dkey[i][j] * val % 26 + 26) % 26;
            }
        }
    }
}
// p(1*n) * key(n*n) = c(1*n)
void Hill::calc(int *p, int **key, int *c){
    for (int i=0;i<n;i++){
        c[i] = 0; // initial
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            //cout <<"***"<< c[i]<<' '<<key[i][j] << ' '<<p[j]<<endl;
            c[i] += p[j] * key[j][i];
        }
        c[i] %= 26;
    }
}

/* test */
int main(){
    int n = 2;
    int *k[2];
    for (int i=0;i<2;i++) k[i] = new int[2];
    k[0][0]=9;k[0][1]=4;
    k[1][0]=5;k[1][1]=7;//{{9,4}, {5,7}};
    Hill hill(2, k);
    string cipher = hill.encrypt("meet me at the usual place at ten rather than eight oclock");
    cout << cipher << endl;
    string plain = hill.decrypt(cipher);
    cout << plain << endl;
    /*int n = 3;
    int *k[3];
    for (int i=0;i<3;i++) k[i] = new int[3];
    k[0][0]=17;k[0][1]=17;k[0][2]=5;
    k[1][0]=21;k[1][1]=18;k[1][2]=21;
    k[2][0]=2; k[2][1]=2; k[2][2]=19;
    Hill hill(3, k);
    string cipher = hill.encrypt("Pay more money");
    cout << cipher << endl;*/
    return 0;
}