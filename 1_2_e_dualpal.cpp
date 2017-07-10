/*
ID: buzzgea1
LANG: C++
PROG: dualpal
*/
#include <fstream>
#include <string.h>

using namespace std;

int MAX_SIZE = 40;

class baseNum{
    private:
        int base,size;
    public:
        char* number;

        char changeToBase(int number){
            if(number<=9){return '0' + number;}
            else{return 'A' + number - 10;}
        }
        
        baseNum(int b, int num){
            int lenFinder = 1, len=0;
            base = b;
            number = (char*) calloc(MAX_SIZE,sizeof(char));
            do{
                len++;
                lenFinder*=b;
            }while(lenFinder<=num);
            size = len;
            for(int i=len-1;i>=0;i--){
                number[i] = changeToBase(num%base);
                num/=base;
            }
        }

        void incrSize(){
            char lead_char = '1';
            if(size+1>MAX_SIZE){exit(-1);}
            for(int i=0;i<size;i++){
                number[i+1] = number[i];
                number[i] = lead_char;
                lead_char = number[i+1];
            }
            size++;
        }

        char incrDigit(char digit){
            if(digit=='9'){return 'A';}
            else{return digit+1;}
        }
        
        void increment(){ //this assumes number is correct when read in
            int remainder = 1;
            for(int i=size-1;i>=0&&remainder>0;i--){
                if(remainder>0){number[i]=incrDigit(number[i]);}
                if(number[i]==changeToBase(base)){number[i] = '0';}
                else{remainder = 0;}
            }
            if(remainder!=0){incrSize();}
        }
};

bool isPalindrome(char*number){
    int size = strlen(number);
    for(int i=0;i<size/2;i++){
        if(number[i]!=number[size-1-i]){return false;}
    }
    return true;
}

int main(){
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");
    int N,S,count = 0;
    bool prevPalin,cont;
    baseNum* numList = (baseNum*) calloc(9,sizeof(baseNum));
    fin>>N>>S;
    for(int i=2;i<=10;i++){
        numList[i-2] = baseNum(i,S+1);
    }
    while(count<N){
        prevPalin = false;
        cont = true;
        for(int i=0;i<9&&cont;i++){
            if(isPalindrome(numList[i].number)){
                if(prevPalin){
                    fout<<numList[8].number<<endl;
                    count++;
                    cont = false;
                }
                else{prevPalin = true;}
            }
        }
        for(int i=0;i<9;i++){numList[i].increment();}
    }
    return 0;
}
