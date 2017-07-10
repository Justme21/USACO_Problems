/*
ID: buzzgea1
LANG: C++
PROG: friday
*/
#include <iostream>
#include <fstream>

using namespace std;

/*Calculate how often the 13th falls on different days from 1900 to a given
  date*/

/*return the adjustment required to calculate the day from dates from 
  various centuries*/
int yearTrans(int year){
    if(year<2000){return 1;}
    else if(year<2100){return 0;}
    else if(year<2200){return -2;}
    else if(year<2300){return -4;}
    return 0;
}

int main(){
    ifstream fin("friday.in");
    ofstream fout("friday.out");
    //the standard month codes for the calculation and a bucket to store
    // the number of occurrences for each day
    int month[12] = {6,2,2,5,0,3,5,1,4,6,2,4}, dayBucket[7]={0,0,0,0,0,0,0};
    int year=1900, N,val,yearTemp;
    fin>>N;// how many years to consider for
    //Iterate through every month of every year in the interval
    for(int i=0;i<N;i++){
        for(int j=0;j<12;j++){
            val=13+month[j]+year%100+(year%100)/4;
            if((year%400==0||(year%100!=0&&year%4==0))&&(j==0||j==1)){val-=1;}
            val+=yearTrans(year);
            dayBucket[val%7]++;
        }
        year++;
    }
    fout<<dayBucket[6];//output starts with Saturday
    for(int i=0;i<6;i++){fout<<" "<<dayBucket[i];}
    fout<<endl;
    return 0;
}
