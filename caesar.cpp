#include "caesar.h"

bool Caesar::encrypt(std::string plain, std::string &cipher){
    if (plain.empty()){ // 空的失败了
        return false;
    }
    int len = plain.size();
    cipher = "";
    //是字母则按偏移量偏移，不是则直接添加
    for (int i=0;i<len;i++){
        if (isalpha(plain[i])){
            int num = std::toupper(plain[i])-'A';
            int nxt = (num+offset+26) % 26;
            cipher.append(alphabet[nxt]);
        }else{
            std::string temp;
            temp = plain[i];
            cipher.append(temp);
        }
    }
    return true;
}

bool Caesar::decrypt(std::string cipher, std::string& plain){
    if( cipher.empty() ){
        return false;
    }
    int len = cipher.size();
    // 是字母则按偏移量偏移，不是则直接添加
    for(int i = 0;i<len;i++){
        if(isalpha(cipher[i])){
            int num = toupper(cipher[i]) - 'A';
            int nxt = (num-offset+26) % 26;
            plain.append(alphabet[nxt]);
        }
        else{
            std::string temp;
            temp = cipher[i];
            plain.append(temp);
        }
    }
    return true;
}