/*
ID: buzzgea1
PROG: transform
LANG: C++
*/
#include <fstream>

/*Given two square patterns find the shortest combination of transformations
  required to transform one into the other (legal transformations 
  pre-programmed*/

using namespace std;

/*Fill the 2-D square array of given size from the input file*/
char **fill_array(ifstream& fin,int N){
    char **array = new char*[N];
    for(int i=0;i<N;i++){array[i] = new char[N];}
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fin>>array[i][j];
        }
    }
    return array;
}

/*Compare two 2-D square arrays of equal size to see if they are equal*/
bool is_equal(char **orig, char **trans, int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(orig[i][j]!=trans[i][j]){return false;}
        }
    }
    return true;
}

/*Reads in the original array and the target array (both 2-D square).
  N is size of arrays
  Cases defines the permissable different transformations to consider
  (mainly relevant for combination transformations)
  This basically brute forces every possible combination of transformations
  until it finds one that works.*/
char test(char **orig, char **trans, int N, string cases){
    char ** alt = new char*[N]; //alt will be transformed orig
    for(int i=0;i<N;i++){alt[i]=new char[N];}
    for(int i=0;i<cases.size();i++){
        switch(cases[i]){
            case '1': //90 degree rotation
                for(int i=0;i<N;i++){
                    for(int j=0;j<N;j++){alt[i][j] = orig[N-1-j][i];}
                }
                break;
            case '2': //180 degree rotation
                for(int i=0;i<N;i++){
                    for(int j=0;j<N;j++){alt[i][j] = orig[N-1-i][N-1-j];}
                }
                break;
            case '3': //270 degree rotation
                for(int i=0;i<N;i++){
                    for(int j=0;j<N;j++){alt[i][j] = orig[j][N-1-i];}
                }
                break;
            case '4': //reflection
                for(int i=0;i<N;i++){
                    for(int j=0;j<N;j++){alt[i][j] = orig[i][N-1-j];}
                }
                //Combination: reflection followed by rotation
                if(!is_equal(alt,trans,N)){
                    cases = "123";
                    //7 indicates orig cannot be transformed to trans
                    if(test(alt,trans,N,"123")=='7'){return '7';}
                    else{return '5';}
                }
                else{return '4';}
                break;
            case '6':
                alt = orig;
        }
        if(is_equal(alt,trans,N)){return cases[i];}
    }
    return '7';
}

int main(){
    ifstream fin("transform.in");
    ofstream fout("transform.out");
    int N;
    char sol;
    fin>>N;
    char **orig = fill_array(fin,N), **trans = fill_array(fin,N);
    string cases = "12346";
    sol = test(orig,trans,N,cases);
    fout<<sol<<endl;
    return 0;
}
