/*
ID: buzzgea1
LANG: C++
PROG: milk
*/

#include <fstream>
#include <map>

using namespace std;

int main(){
    ifstream fin("milk.in");
    ofstream fout("milk.out");
    int N,M,nextPrice, nextVol, cost = 0; //# demand,supply,price,volume,cost
    map <int,long long int> price_vol_map;
    map<int,long long int>::iterator it;
    fin>>N>>M;
    for(int i=0;i<M;i++){
        fin>>nextPrice>>nextVol;
        if(price_vol_map.find(nextPrice) == price_vol_map.end()){
            price_vol_map[nextPrice] = nextVol;
        }
        else{price_vol_map[nextPrice] += nextVol;}
    }
    for(it = price_vol_map.begin();it!=price_vol_map.end()&&N!=0;it++){
        if(it->second<=N){
            N-=it->second;
            cost += it->first*it->second;
        }
        else{
            cost+= it->first*N;
            N=0;
        }
    }
    fout<<cost<<endl;
    return 0;
}
