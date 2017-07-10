/*
ID: buzzgea1
LANG: C++
PROG: barn1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
    int maxBoards,numStalls,numCows,numGroups=0,cow,i,tempVal=-1,minGap,dist;
    vector<int>::iterator it, it2;
    fin>>maxBoards>>numStalls>>numCows;
    int *stalls= (int*)calloc(numStalls,sizeof(int));
    vector <int> sortedGaps, unsortedGaps, gapPositions;
    for(int i=0;i<numCows;i++){
        fin>>cow;
        stalls[cow-1]=1;
    }
    i=0;
    while(i<numStalls){
        if(i<numStalls-1&&stalls[i]==1&&stalls[i+1]==0){
            if(tempVal==-1){numGroups++;} //the first gap makes 2 groups
            tempVal = i;
            while(i+1<numStalls&&stalls[i+1]==0){i++;}
            if(i<numStalls-1){
                gapPositions.push_back(tempVal+1);
                tempVal = i-tempVal;
                sortedGaps.push_back(tempVal);
                unsortedGaps.push_back(tempVal);
                numGroups++;
            }
        }
        i++;
    }
    sort(sortedGaps.begin(),sortedGaps.end());
    for(it=sortedGaps.begin(); it!=sortedGaps.end()&&numGroups>maxBoards;it++){
        minGap = *it;
        it2 = find(unsortedGaps.begin(),unsortedGaps.end(),minGap);
        dist = distance(unsortedGaps.begin(),it2);
        tempVal = *(gapPositions.begin()+dist);
        while(stalls[tempVal]!=1){
            stalls[tempVal]=1;
            tempVal++;
        }
        unsortedGaps.erase(unsortedGaps.begin()+dist);
        gapPositions.erase(gapPositions.begin()+dist);
        numGroups--;
    }
    numCows = 0; //reused to count the number of stalls blocked
    for(int i=0;i<numStalls;i++){
        if(stalls[i]==1){numCows++;}
    }
    fout<<numCows<<endl;
    return 0;
}
