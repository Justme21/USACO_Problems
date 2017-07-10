/*
ID: buzzgea1
PROG: wormhole
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

/**THIS CODE MAY BE THE DEVIL. ABANDON ALL HOPE, YE WHO ENTER HERE
   
   Problem: Portals are in a space. Portals are pairwise connected (N portals result in N/2 distinct pairs)
            Cow on the space moves in +x direction. Identify all pairs in which the cow could get caught in an infinite loop
            (Count the number of maps which have at least one loop) **/

class Wormhole{
    /**Wormhole objects for this problem. Use this to store the location of holes
       and defining relative values (such as < and ==)**/
    private:
        int x,y; //the x and y coordinates of the Wormhole

    public:
        Wormhole(){} //the default required to declare and uninitialised Wormhole

        Wormhole(const int in_x, const int in_y){
           /**Initialising a Wormhole**/
            x = in_x;
            y = in_y;
        }

        const int getX() const {
            /**Return the x coordinate of the portal (private otherwise). Is const so can
               be used as in "<" and "==" operations**/
            return x;
        }

        const int getY() const{
            /**Return the y coordinate of the portal (private otherwise). Is const so can
               be used as map key and in "<" and "=="**/
            return y;
        }

        bool operator < (const Wormhole& hole) const{
            /**Define '<' operation between two wormholes (called by w1 when checking w1<w2, where w2 passed as argument
               Required for sorting arrays**/
            return (y==hole.getY()&&x<hole.getX())||(y<hole.getY());
        }

        bool operator == (const Wormhole& hole) const{
            /**Define '==' operation (called by w1 when checking w1==w2). Required at vairious points in the problem including find in a map**/
            return (x==hole.getX()&&y==hole.getY());
        }

};

bool hasLoop(map <Wormhole,Wormhole> path_map, map <int, vector <Wormhole> > grid_map){
    /**Check if the links as defined in path_map defines at least one path which has a loop in it.
       grid_map contains the relative positions of the portals and path_map identifies which portals are linked together**/
    map <Wormhole,Wormhole>::iterator path_it; //iterator for path_map
    vector <Wormhole> row; //for reading a single row from grid_map
    vector <Wormhole>::iterator row_it; //for iterating through a row
    Wormhole cur_hole; // used to trace a path through hte portals
    
    for(path_it = path_map.begin(); path_it!= path_map.end(); path_it++){
        /*Try every possible start point to identify any which might have loops*/
        cur_hole = path_it->second; //start assuming you walked into path_it->first and came out in cur_hole path_it->second
        while(true){
            row = grid_map[cur_hole.getY()]; //the row the current portal is on
            row_it = find(row.begin(),row.end(),cur_hole); //the location of the current portal in the row
            if(!((*row_it)==(*(row.end()-1)))){ //this makes sure *row_it isn't the last in the row (otherwise won't have a neighbour) => path ends
                cur_hole = *(row_it+1); //if has neighbour then move to the neighbour
                if(cur_hole == path_it->first){return true;} //if back at the start then are in a loop
                else{cur_hole = path_map[cur_hole];} //move through the portal to come out the linked portal
            }
            else{break;} //came to the end of the path => no loop
        }
    }
    return false; //if gets this far then no loop was found
}

int iterThroughPaths(map <Wormhole,Wormhole> path_map, map<int, vector <Wormhole> > grid_map, vector <Wormhole> source_holes, vector <Wormhole> to_holes){
    /**Recursive program that gets the number of loops possible by creating every possible path and checking how many of those paths
       result in loops
       This is essentially a Depth First British Museum algorithm
       path_map identifies which portals are linked together (A linked to be => if you enter A you come out B)
       grid_map stores the relative location of portals used to identify neighbours
       source_holes is a list of portals still available to be sources for portals
       to_holes is a list of portals that can be used as destinations
       IT MIGHT NOT BE NECESSARY TO HAVE BOTH source_holes AND to_holes **/

    int num_paths = 0; //the number of paths found on this branch
    if(source_holes.size()==0){ //termination condition. Source having no elements meaning every portal is linked to another
        if(hasLoop(path_map,grid_map)){num_paths++;} //if a loop is found then increment the number of paths with loops
    }
    else{ //if source is not empty then there are at least 2 portals that can be linked together
        bool el_rmvd; // records whether or not an element was removed (prevents Seg fault, I think)
        vector <Wormhole> to_copy(to_holes); makes a copy of the list of destination portals so that one can be removed while iterating through the list
        vector <Wormhole>::iterator to_it, temp_it; //used to iterate through destination portals and to record if a portal is already paired
        Wormhole start; //identify the branching point at this level
        start = source_holes.back(); //the current branching point is taken as the last element in the list of possible sources (easier to replace later)
        source_holes.pop_back(); //remove the source so that it isn't reused later on
        to_holes.erase(find(to_holes.begin(),to_holes.end(),start)); //remove start from the desintations since the links are paired

        for(to_it = to_holes.begin(); to_it!=to_holes.end();to_it++){ //iterate through remaining possible destination portals
            if(!(start==*to_it)&&path_map.count(*to_it)==0){ //ensure start isn't accidentally chosen destination and the destination chosen not previously used
                el_rmvd = false; //initially assume an element will not have to be removed
                path_map[start] = *to_it; //link start with chosen destination
                path_map[*to_it] = start; // symmetrically link destination with start
                to_copy.erase(find(to_copy.begin(),to_copy.end(),*to_it)); //remove the chosen destination from the pool of possible destinations
                temp_it = find(source_holes.begin(),source_holes.end(),*to_it); //if the destination is a possible destination remove it //PROBABLY UNNECESSARY
                if(temp_it!= source_holes.end()){ //if the destination is found in the list of sources
                    el_rmvd = true; //an element is being removed
                    source_holes.erase(temp_it); //remove the destination from possible sources
                }
                num_paths += iterThroughPaths(path_map,grid_map,source_holes,to_copy); //RECURSION HERE
                to_copy.push_back(*to_it); //restore the destination that was removed
                path_map.erase(path_map.find(start)); //erase the link created for start
                path_map.erase(path_map.find(*to_it)); // erase the link created for the destination
                if(el_rmvd){source_holes.push_back(*to_it);} //if the destination was removed from source_list then return it
            }
        }
    }
    return num_paths; // return the number of paths that contain loops
}

int main(){
    /**Read in the number of portals there are, followed by their coordinates.
       These are inserted into a map using the y_coordinate as the key (so "neighbouring" portals can
       be iterated through
       Each row in the map is sorted so that the portal with the smallest x_coordinate is first
       (This allows for "neighbours" in the positive x direction to be identified)
       Finally iterThroughPaths iterates through all possible paths counting those with loops
    **/
    ifstream fin("wormhole.in"); //input stream
    ofstream fout("wormhole.out"); //output stream
    int num_wormholes,x_posit,y_posit, num_paths; // #wormholes, portal x/y coords, # paths that have loops
    map <int, vector <Wormhole> > disorder_grid, portal_grid; //creating a dynamic grid of portals grouped by y-coord, identical map with ordered vectors
    map <int,vector <Wormhole> >::iterator map_it; // iterator for the map
    map <Wormhole, Wormhole> path_map; //map identifying linked portals
    vector <Wormhole> row_vec, hole_list; //vector to hold each row in map, single list with all holes
    vector <Wormhole>::iterator row_it; //iterate through rows
    Wormhole cur_hole; // used to insert Wormholes into map
    fin>>num_wormholes; //read in the number of Wormholes

    //Read in all the points and store in disordered map
    for(int i=0;i<num_wormholes;i++){
        fin>>x_posit>>y_posit;
        cur_hole = Wormhole(x_posit,y_posit);
        disorder_grid[y_posit].push_back(cur_hole); //putting the wormhole into the map
    }
    
    //Creating the complete list of portals and creating the map of ordered vectors
    //(Creating ordered map might be unnecessary but was inserted as a fix and have not checked the ultimate result)
    for(map_it = disorder_grid.begin();map_it!=disorder_grid.end();map_it++){
        row_vec = map_it->second;
        portal_grid[map_it->first].insert(portal_grid[map_it->first].end(),row_vec.begin(),row_vec.end());
        sort(row_vec.begin(),row_vec.end());
        hole_list.insert(hole_list.end(),row_vec.begin(),row_vec.end());
    }
    num_paths = iterThroughPaths(path_map,portal_grid,hole_list,hole_list);
    fout<<num_paths<<endl;
    return 0;
}
