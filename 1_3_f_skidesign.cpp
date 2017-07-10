/*
ID: buzzgea1
PROG: skidesign
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int MAX_DIFF = 17;

int main(){
    
    //Initialisation
    ifstream fin("skidesign.in");
    ofstream fout("skidesign.out");
    int min,max,N,hill,score,minScore=-1,interLo,interHi;
    vector <int> hills;
    vector <int>::iterator hill_it;
    fin>>N;
    for(int i=0;i<N;i++){
        fin>>hill;
        hills.push_back(hill);
    }
    sort(hills.begin(),hills.end());
    min = hills.front();
    max = hills.back();
    interLo=min;
    do{
        score = 0;
        interHi = interLo+MAX_DIFF;
        for(hill_it = hills.begin();hill_it!=hills.end();hill_it++){
            hill = *hill_it;
            if(hill<interLo){score+=(interLo-hill)*(interLo-hill);}
            else if(hill>interHi){score+=(hill-interHi)*(hill-interHi);}
        }
        if(minScore<0||score<minScore){minScore=score;}
        interLo++;
    }while(interLo<max);
    fout<<minScore<<endl;
    return 0;
}
