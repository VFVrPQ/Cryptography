#include "playfair.h"

Playfair::Playfair(){
}

Playfair::Playfair(string k){
    memset(vis, 0, sizeof vis); //所有字母都没有使用
    vis['J'-'A'] = 1;//I,J共用一个地方，假设都用I
    int len = k.length();
    int pos = 0;// 现在key里面填到哪个位置了
    for (int i=0;i<len;i++){
        char c = k[i];
        if (isalpha(c)){
            c = toupper(c);
            if (c=='J') c--; //如果是J，变成I（因为两个位置相同）
            if (!vis[c-'A']){
                key[pos/5][pos%5] = c; pos++;
                vis[c-'A']=1;
            }
        }
    }
    for (int i=0;i<26;i++) if (!vis[i]){
        key[pos/5][pos%5] = (char)(i+'A');
        pos++;
        vis[i]=1;
    }
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            pos_x[ key[i][j]-'A' ] = i;
            pos_y[ key[i][j]-'A' ] = j;
        }
    }
    pos_x['J'-'A'] = pos_x['I'-'A'];//add
    pos_y['J'-'A'] = pos_y['I'-'A'];//add
    debug();
}

string Playfair::encrypt(string plain, char x){ // x='X'
    string dirty = prepare_input(plain, x);
    string result ; 
    int len = dirty.length();
    for (int i=0;i<len;i+=2){
        int u1 = pos_x[ dirty[i]-'A' ], v1 = pos_y[ dirty[i]-'A' ];
        int u2 = pos_x[ dirty[i+1]-'A'], v2 = pos_y[ dirty[i+1]-'A' ];
        if (u1==u2){
            //v1!=v2
            result += key[u1][(v1+1)%5];
            result += key[u2][(v2+1)%5];
        }else
        if (v1==v2){
            //u1!=u2
            result += key[(u1+1)%5][v1];
            result += key[(u2+1)%5][v2];
        }else{
            //v1!=v2 && u1!=u2, 如果最后一个字符是X的话并不能保证的
            result += key[u1][v2];
            result += key[u2][v1];
        }
    }
    return result;
}

//默认为输入的都是大写字母，无其他字符；且长度是2的倍数
string Playfair::decrypt(string cipher){
    string result;
    int len = cipher.length();
    cout<< len << endl;
    for (int i=0;i<len;i+=2){
        int u1 = pos_x[ cipher[i]-'A' ], v1 = pos_y[ cipher[i]-'A' ];
        int u2 = pos_x[ cipher[i+1]-'A'], v2 = pos_y[ cipher[i+1]-'A' ];
        if (u1==u2){
            //v1!=v2
            result += key[u1][(v1-1+5)%5];
            result += key[u2][(v2-1+5)%5];
        }else
        if (v1==v2){
            //u1!=u2
            result += key[(u1-1+5)%5][v1];
            result += key[(u2-1+5)%5][v2];
        }else{
            //v1!=v2 && u1!=u2, 如果最后一个字符是X的话并不能保证的
            result += key[u1][v2];
            result += key[u2][v1];
        }
    }
    return result;
}

string Playfair::prepare_input(string plain, char x){
    string mid;
    int len = plain.length();
    for (int i=0;i<len;i++){
        if (isalpha(plain[i])){//过滤其他字符
            char c = toupper(plain[i]);//转换成大写
            if (c=='J') c--;//变成I
            mid += c;
        }
    }
    string dirty;
    len = mid.length();
    int n = 0;//for dirty
    for (int i=0;i<len;i++){
        if (n%2==1 && dirty[n-1]==mid[i]){
            dirty += x; 
            dirty += mid[i];
            n+=2;
        }else{
            dirty += mid[i];
            n++;
        }
    }
    if (n%2==1) dirty += x;
    return dirty;
}

int main(){
    //Playfair playfair("boys and girls are students");
    //string cipher = playfair.encrypt("It is not a problem. It is a challenge. Enjoy facing it.");
    //cout << cipher << endl;
    //Playfair playfair("boys and girls are students");
    //string plain = playfair.decrypt("GUUIDBCYZCYOETXUUGABEPBCETDILVLDDSBKRPRDIRLW");
    //cout << plain << endl;
    //Playfair playfair("royal new zealand navy");
    //string plain = playfair.decrypt("KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBWTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ");
    //cout<< plain << endl;
    Playfair playfair("largest");
    string cipher = playfair.encrypt("Must see you over cadogan west. coming at once.");
    cout<< cipher << endl;
    return 0;
}