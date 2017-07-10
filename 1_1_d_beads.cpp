/*
ID: buzzgea1
LANG: C++
PROG: beads
*/
#include <iostream>
#include <fstream>

using namespace std;

/*Given a string of beads of either blue,red or white, find a place to split the string to maximise the number of beads that can be taken where you can only
 take adjacent beads of the same colour from either end (except for white which
 is interpreted as either colour*/

/*Singly Linked List used to represent the string*/
typedef struct SLL_NODE{
    char col;
    int count;
    struct SLL_NODE * next;
}SLL_NODE;

/*Replaces the string AwA with AAA with a longer count,where w represents a white
  bead, and A is any other bead type */
SLL_NODE* fix_chain(SLL_NODE* first){
    SLL_NODE* cur = first;
    do{
        //the condition for AwA
        if(cur->col!='w'&&cur->col==cur->next->next->col&&cur->next->col=='w'){
            SLL_NODE* temp = (SLL_NODE*)calloc(1,sizeof(SLL_NODE));
            cur->count += cur->next->count+cur->next->next->count;
            temp = cur->next->next->next; //skip to the next unmerged link
            // move the position of first if it is about to be overwritten
            if(cur->next->next==first||cur->next==first){first = cur;} 
            free(cur->next);
            free(cur->next->next);
            cur->next = temp;
        }
        else{cur = cur->next;}
    }while(cur!=first);
    return first;
}

/*Get the length of the string of beads*/
int length(SLL_NODE* first){
    int length = 0;
    SLL_NODE* cur = first;
    do{
        length++;
        cur = cur->next;
    }while(cur!=first);
    return length;
}

/*Get the maximum number of beads that can be taken starting from start and
  checking up to limit.*/
int get_limit(SLL_NODE* start,SLL_NODE* limit, int maxSum){
    static char col = ' ';
    static int white = 0,red = 0,blue = 0,curSum = 0;
    static int* incr;
    do{
        col = start->col; //get the colour of the current section of beads
        if(col=='w'){ //white is treated differently to other bead types
            white = start->count; // the number of beads in the current section
            curSum+=white; //add this on to the current Sum
        }
        else{
            if(col=='r'){incr =&red;} //referring to the red variable
            else{incr =&blue;} //referring to the blue variable
            curSum -= *incr; // remove the previously added number of beads
            //include the most recent number of white beads to the next 
            // occurring set of blue/red beads
            *incr = white+start->count; 
            curSum += *incr-white; //deduct the previously added white beads
            white = 0;
        }
        start = start->next; // progress to the next section
        if(curSum>maxSum){maxSum = curSum;} //keep the max
    }while(start!=limit);
    return maxSum;
}

int main(){
    ifstream fin("beads.in");
    ofstream fout("beads.out");
    char col=' ';
    int i = 0,N,maxSum = 0,count,len;
    int* incr;
    SLL_NODE  *prev = NULL, *cur,*first = NULL;
    fin>>N; //the total number of beads
    //Store each set of consecutive beads as a singly entry in linked list
    while(i<N){
        cur = (SLL_NODE*) calloc(1,sizeof(SLL_NODE));
        count = 0;
        if(col==' '){fin>>col;} // the first iteration
        cur->col = col; //store the colour as the colour of the current section
        while(i<N&&col==cur->col){ //all adjacent beads of the same colour
            count++;
            i++;
            if(i<N){fin>>col;}
        }
        cur->count = count; \\store the number of beads in the list entry
        if(first==NULL){first = cur;} \\defining the first entry
        if(prev!=NULL){prev->next = cur;}
        prev = cur;
    }
    prev->next=first;//close the loop of the string
    //if the last entry and the first entry have the same colour merge them
    if(prev->col==first->col&&prev!=first){
        prev->count += first->count;
        first = first->next;
        free(prev->next);
        prev->next = first;
    }
    first = fix_chain(first); //remove the AxA patterns in the string
    len = length(first); \\get the length of the string, n
    maxSum = get_limit(first,first,maxSum); //get the max over the string 0->n-2
    // always adding in 3's, if more than 3 entries then consider the 
    // sums arising from the overlap at the end of the string
    if(len>=5){maxSum = get_limit(first,first->next->next,maxSum);}
    else if(len==4){maxSum = get_limit(first, first->next,maxSum);}
    fout<<maxSum<<endl; //print out the max
    return 0; 
}
