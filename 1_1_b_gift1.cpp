/*
ID: buzzgea1
LANG: C++
PROG: gift1
*/
#include <fstream>
#include <map>
#include <string>

using namespace std;

/*Given a list of people who intend on giving equal monetary gifts to each other
  friend. 
  First each person is mapped to the amount of money they have, then the amount
  in the map is edited as people give and take gifts.*/

int main(){
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");
    int numPeople,amountMoney,numGifts;
    string name;
    string* nameList;
    map<string,int> nameMap; // mapping string keys to integers
    fin>>numPeople; // read in the number of people in the group
    nameList = new string[numPeople]; //this will record all the people
    //Initialise all the people who will be included in the program
    for(int i=0;i<numPeople;i++){
        fin>>name;
        nameList[i] = name;
        nameMap[name] = 0;
    }
    //Record how much each person is giving to everyone else
    for(int i=0;i<numPeople;i++){
        fin>>name>>amountMoney>>numGifts;//gift giver,amount giving, #recipients
        if(numGifts!=0&&amountMoney!=0){
            //how much money the gift giver will have left over after giving
            nameMap[name] += (amountMoney%numGifts)-amountMoney;
            //giving remaining people their gifts
            for(int j=0;j<numGifts;j++){
                fin>>name;
                nameMap[name] += (amountMoney/numGifts);
            }
        }
    }
    //print out results
    for(int i=0;i<numPeople;i++){
        fout<<nameList[i]<<" "<<nameMap[nameList[i]]<<endl;
    }
    return 0;
}
