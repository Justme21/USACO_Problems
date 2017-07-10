/*
ID: buzzgea1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>

/*Given the beginning and end times for N farmers milking cows, prints
  the longest interval during which at least one cow was milked
  and prints the longest time interval after milking starts during which
  no cow was being milked*/

//Given upper limit for the time
const int maxNum = 1000000;

using namespace std;

int main(){
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");
    int N,a,b,longIdle=0,longMilk=0,posit,cur,maxB=0,minA=-1,temp;
    //Array with an entry of every possible second of time, all initialised to
    //zero
    int milkingTimes[maxNum]={0};
    int * curMax;
    fin>>N; //input the number of farmers (instances to be read in)
    for(int i=0;i<N;i++){
        fin>>a>>b; //beginning and end time
        if(minA<0){minA=a;} //conditions to handle first iteration
        for(int j=a;j<b;j++){
            milkingTimes[j] = 1; // set milking to "true" in the given period
        }
        if(b>maxB){maxB = b;} //finding when milking stoppped
        if(a<minA){minA = a;} //finding when milking started
    }
    //iterating through entire period from when milking began to when it ended
    posit = minA;
    while(posit<maxB){
        temp = posit;
        if(milkingTimes[posit]== 1){
            cur = 1; //specifying we are currently looking at times of milking
            curMax = &longMilk; //max period for milking occurring
        }
        else{
            cur = 0; //specifying times of no milking
            curMax = &longIdle; //max period with no milking
        }
        //find end of period of time during which nothing changes
        while(posit<maxB&&milkingTimes[posit]==cur){posit++;}
        temp = posit-temp;//length of period measured
        //if the current period is longer than the previously found max, replace
        if(temp>*curMax){*curMax = temp;}
    }
    fout<<longMilk<<" "<<longIdle<<endl; //print out maxes found
    return 0;
}
