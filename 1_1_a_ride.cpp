/*
ID: buzzgea1
LANG: C++
PROG: ride
*/
#include <fstream>
#include <string>
using namespace std;

/*Reads in 2 strings and compute their numerical product mod47.
  If the numbers are equal print "GO", or else print "STAY"*/

/*Returns the product of the numerical values of the letters in the string
  s1, mod47*/
int parseString(string s1){
    int init = 1;
    for(int i=0;i<s1.length();i++){
        init*=(s1[i]-'A'+1);
    }
    return init%47;
}

int main(){
    int v1,v2;
    string s1,s2;
    ifstream fin("ride.in"); //define the file to read input from
    ofstream fout("ride.out"); //defines the file that output will be written to
    fin>>s1>>s2;
    v1 = parseString(s1);
    v2 = parseString(s2);
    if(v1==v2){fout<<"GO"<<endl;}
    else{fout<<"STAY"<<endl;}
    return 0;
}
