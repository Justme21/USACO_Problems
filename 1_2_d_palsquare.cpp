/*
ID: buzzgea1
LANG: C++
PROG: palsquare
*/
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;

const int N_LIM = 300;

bool isPalindrome(char* number){
    int size = strlen(number);
    for(int i=0;i<size/2;i++){
        if(number[i]!=number[size-1-i]){return false;}
    }
    return true;
}

char changeToBase(int number){
    if(number<=9){return '0'+number;}
    else{return 'A'+number-10;}
}

char* base10toBase(int base, int number){
    int len = 0,lenFinder = 1;
    do{
        len++;
        lenFinder*=base;
    }while(lenFinder<=number);
    char* newNum = new char(len);
    for(int i=len-1;i>=0;i--){
        newNum[i] = changeToBase(number%base);
        number/=base;
    }
    return newNum;
}

int main(){
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    int base;
    char* sqr;
    fin>>base;
    for(int N=1;N<=N_LIM;N++){
        sqr = base10toBase(base,N*N);
        if(isPalindrome(sqr)){fout<<base10toBase(base,N)<<" "<<sqr<<endl;}
    }
    return 0;
}
