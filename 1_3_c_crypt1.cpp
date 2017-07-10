/*
LANG: C++
ID: buzzgea1
PROG: crypt1
*/

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

/*Given a number, and that many digits, need to determine how many different
  products can be constructed (by partial product method - 
  multiplying number by each digit of coefficient and adding together the 
  result (scaled appropriately)) such that only the digits in the list arise
  in the calculation */

/*Checks if every digit in num is in the list of permissable digits.
  Returns true if this is the case*/
bool isGood(int num, vector <int> digits){
    while(num>0){
        if(find(digits.begin(),digits.end(),num%10)==digits.end()){return false;}
        num/=10;
    }
    return true;
}

/*Takes in a list of numbers
  Performs the second step of partial multiplication (summing the numbers,
  multiplying one of the numbers by 10).
  This is performed for every pair of numbers in the list, counting the number
  satisfying the criteria from the problem
*/
int getSum(vector <int> products, vector <int> digits){
    int numGood = 0,sum;
    vector <int>::iterator it1, it2;
    for(it1 = products.begin();it1!=products.end();it1++){
        for(it2 = products.begin();it2!=products.end();it2++){
            //it1 is the tens value from the product, so is scaled by a factor
            // of ten. it2 is the ones value
            sum = (*it1)*10+(*it2);
            if(isGood(sum,digits)){numGood++;}
        }
    }
    return numGood;
}

/*Generates every number that can be made from the list of usable digits
  Each number is multiplied by each digit from the list of numbers.
  This returns the list of partial products for the given number. 
  getSum then performs the rest of the partial product*/
int getProducts(vector <int> digits){
    int number = 0,count = 0, coef,product;
    vector <int> product_vec; //vector storing all the attainable products
    vector <int>::iterator it1, it2, it3, it; //to access digits from the list
    for(it1=digits.begin();it1!=digits.end();it1++){
        number += 100*(*it1); //first digit of the number
        for(it2=digits.begin();it2!=digits.end();it2++){
            number += 10*(*it2); //second digit of the number
            for(it3=digits.begin();it3!=digits.end();it3++){
                number += *it3; //third digit of the number
                for(it=digits.begin();it!=digits.end();it++){
                    coef = *it; //coefficient for the number
                    product = number*coef;
                    //products have 3 digits (given in problem)
                    // if this product is too long so is every after => end loop
                    if(product/1000>0){break;}
                    //if product satisfies problem add to vector
                    if(isGood(product,digits)){product_vec.push_back(product);}
                }
                count+=getSum(product_vec,digits);
                //vector is cleared after trying every possible coefficient
                product_vec.clear(); 
                number -= *it3;//remove third digit
            }
            number -= 10*(*it2);//remove second digit
        }
        number -= 100*(*it1);//remove first digit
    }
    return count;
}

int main(){
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");
    int num_digits, case_digit, count = 0;
    fin>>num_digits;
    vector <int> digits;
    for(int i=0;i<num_digits;i++){
        fin>>case_digit;
        //make sure no repeat digits appear in the vector
        if(find(digits.begin(),digits.end(),case_digit)==digits.end()){
            digits.push_back(case_digit);
        }
    }
    sort(digits.begin(),digits.end());//necessary to have digits in order later
    count = getProducts(digits);
    fout<<count<<endl;
}
