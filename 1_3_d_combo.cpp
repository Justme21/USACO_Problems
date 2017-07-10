/*
ID: buzzgea1
LANG: C++
PROG: combo
*/
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int TOLERANCE = 2;

vector<int> getComboVector(int value,int min,int max){
    int i_dup;
    vector <int> value_vector;
    for(int i=value-TOLERANCE;i<=value+TOLERANCE;i++){
        i_dup=i;
        if(i_dup>max){do{i_dup-=max;}while(i_dup>max);}
        else if(i_dup<min){do{i_dup+=max;}while(i_dup<min);}
        if(find(value_vector.begin(),value_vector.end(),i_dup%(max+1))==value_vector.end()){
            value_vector.push_back(i_dup%(max+1));
        }
        else{ break;} //if a digit is found that was already inserted are in loop so end
    }
    return value_vector;
}

vector < vector<int> > getCombos(int values[], int length, int min, int max){
    vector< vector<int> > combo_vec;
    for(int i=0;i<length;i++){
        combo_vec.push_back(getComboVector(values[i],min,max));
    }
    return combo_vec;
}

int getNumCombos(vector < vector<int> > combo_list){
    int num_poss = 1;
    vector < vector<int> >::iterator it;
    for(it = combo_list.begin();it!=combo_list.end();it++){
        num_poss *= (*it).size();
    }
    return num_poss;
}

vector< vector<int> > getOverlap(vector< vector<int> > v1, vector< vector<int> > v2){
    vector< vector<int> >::iterator it1,it2;
    vector<int>::iterator vec_it;
    vector <int> vec1_sub, vec1_dup, vec2_sub;
    it1 = v1.begin();
    it2 = v2.begin();
    while(it1!=v1.end()){
        vec1_sub = *it1;
        vec1_dup = *it1;
        vec2_sub = *it2;
        for(vec_it = vec1_sub.begin(); vec_it!=vec1_sub.end();vec_it++){
            if(find(vec2_sub.begin(),vec2_sub.end(),*vec_it)==vec2_sub.end()){
                vec1_dup.erase(find(vec1_dup.begin(),vec1_dup.end(),*vec_it));
            }
        }
        (*it1).swap(vec1_dup);
        it1++;
        it2++;
    }
    return v1;
}

int main(){
    ifstream fin("combo.in");
    ofstream fout("combo.out");
    int N,d1,d2,d3,tot_num_combos=0;
    int dials[3];
    vector < vector<int> > john_combo_list, master_combo_list;
    vector < vector<int> >::iterator it;
    vector <int>::iterator it2;
    fin>>N;
    for(int i=0;i<3;i++){fin>>dials[i];}
    john_combo_list = getCombos(dials,3,1,N);
    for(int i=0;i<3;i++){fin>>dials[i];}
    master_combo_list = getCombos(dials,3,1,N);
    tot_num_combos += getNumCombos(john_combo_list);
    tot_num_combos += getNumCombos(master_combo_list);
    tot_num_combos -= getNumCombos(getOverlap(john_combo_list,master_combo_list));
    fout<<tot_num_combos<<endl;
    return 0;
}
