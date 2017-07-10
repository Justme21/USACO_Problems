/*
ID: buzzgea1
LANG: C++
PROG: namenum
*/
#include <fstream>
#include <string>

const int MAX_SIZE = 5000;

using namespace std;

string translate(char num){
    switch(num){
        case '2': return "ABC";
        case '3': return "DEF";
        case '4': return "GHI";
        case '5': return "JKL";
        case '6': return "MNO";
        case '7': return "PRS";
        case '8': return "TUV";
        case '9': return "WXY";
    }
    return "";
}

int dict_find(string* dict, int dictSize, string word){
    int i=0;
    do{i+=MAX_SIZE/100;}while(i<dictSize&&dict[i][0]<word[0]);
    i-=MAX_SIZE/100;
    for(i=i;i<dictSize&&dict[i][0]<=word[0];i++){
        if(word==dict[i]){return i;}
    }
    return dictSize;
}

bool name_generator(string word,string pName,string* d,int dSize,ofstream &fout){
    bool exist = false, exist_test;
    char num = word[0];
    string possLetter = translate(num), temp = word.substr(1,word.length());
    for(int i=0;i<possLetter.size();i++){
        if(temp.size()>0){
            exist_test = nameGenerator(temp,pName+possLetter[i],d,dSize,fout);
            exist = exist||exist_test;
        }
        else{
            if(dict_find(d,dSize,pName+possLetter[i])!= dSize){
                fout<<pName+possLetter[i]<<endl;
                exist = true;
            }
        }
    }
    return exist;
}

int main(){
    bool exists;
    int dictSize = 0;
    string word;
    string *dict = new string[MAX_SIZE];
    ifstream dictStream("dict.txt");
    while(dictSize<MAX_SIZE&&dictStream>>word){
        dict[dictSize] = word;
        dictSize++;
    }
    ifstream fin("namenum.in");
    ofstream fout("namenum.out");
    fin>>word;
    exists = name_generator(word,"",dict,dictSize,fout);
    if(!exists){fout<<"NONE"<<endl;}
    return 0;
}
