#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;
class Beacon;
class Beacon{
    public:
    int x,y,z;
    Beacon(){};
    Beacon(int _x, int _y, int _z) {x = _x; y = _y; z = _z;}
    string offsetHash(Beacon b) { stringstream s; s << "[" << b.x-x << "," << b.y-y << "," << b.z-z << "]"; return s.str(); }
    int offset(Beacon b) { return abs(b.x - x) + abs(b.y -y ) + abs(b.z -z);}
    bool operator==(const Beacon & b) { return (x == b.x ) && (y == b.y) && (z == b.z);}
    bool operator< (const Beacon & b) { return (x < b.x); }
};
#define IT(i, x, y, z) case i: for (auto b: ref) s.push_back(Beacon(x, y, z)); break;
vector<Beacon> getIteration(vector<Beacon> ref, int iteration) {
    vector<Beacon> s;
    switch (iteration) {
        IT( 0, b.x, b.y, b.z) IT( 1, b.x,-b.z, b.y) IT( 2, b.x,-b.y,-b.z) IT( 3, b.x, b.z,-b.y)
        IT( 4, b.y, b.z, b.x) IT( 5, b.y,-b.x, b.z) IT( 6, b.y,-b.z,-b.x) IT( 7, b.y, b.x,-b.z)
        IT( 8, b.z, b.x, b.y) IT( 9, b.z,-b.y, b.x) IT(10, b.z,-b.x,-b.y) IT(11, b.z, b.y,-b.x)
        IT(12,-b.z,-b.y,-b.x) IT(13,-b.z, b.x,-b.y) IT(14,-b.z, b.y, b.x) IT(15,-b.z,-b.x, b.y)
        IT(16,-b.y,-b.x,-b.z) IT(17,-b.y, b.z,-b.x) IT(18,-b.y, b.x, b.z) IT(19,-b.y,-b.z, b.x)
        IT(20,-b.x,-b.z,-b.y) IT(21,-b.x, b.y,-b.z) IT(22,-b.x, b.z, b.y) IT(23,-b.x,-b.y, b.z)
    }
    return s;
};

Beacon findTrans(vector<Beacon> a, vector <Beacon> b, string offset){
    for(auto i: a){
        for( auto j : b){
            if(i.offsetHash(j) == offset)
                return Beacon( i.x-j.x, i.y-j.y, i.z-j.z );
        }
    }
    return Beacon();
}

int main(int argc, char * argv[]){

    ifstream input; string line;
    if (argc < 2) { 
        input.open("inputPartOne.txt");
    }else
        input.open(argv[1]);
    
    queue<vector<Beacon>> scanners;
    vector<Beacon> scanner, grid;
    while (!input.eof()) {
        std::getline(input, line);
        if (line.find("scanner") != string::npos) {
            if (scanner.size() > 0) scanners.push(scanner);
            scanner = vector<Beacon>();
        } else if (line == "") {
            continue;
        } else {
            vector<int> vals;
            int c1 = line.find(",");
            int c2 = line.find(",", c1+1);
            int x = stoi(line.substr(0,c1));
            int y = stoi(line.substr(c1+1, c2-c1));
            int z = stoi(line.substr(c2+1));
            scanner.push_back(Beacon(x, y, z));
        }
    }
    if (scanner.size() > 0) scanners.push(scanner);
    grid = scanners.front();
    std::sort(grid.begin(), grid.end());
    scanners.pop(); // initialize scanner 0 as root for finding all others position

    vector<Beacon> scannerPos;
    scannerPos.push_back(Beacon(0,0,0)); // first scanner is at pos 0,0,0

    while(!scanners.empty()){
        vector<Beacon> current = scanners.front();
        scanners.pop();

        pair<int, int> maxPair = {-1,0};
        string maxOff = "";

        for(int i = 0; i < 24; i++) // 24 Perm
        {
            map<string, int> offSet;
            map<int,int> count;
            vector<Beacon> iteration = getIteration(current,i);
            for(auto ref : grid){
                for(auto b : iteration){
                    offSet[ref.offsetHash(b)]++;
                }
            }
            for(auto dist : offSet){
                count[dist.second]++;
            }
            for(auto c : count){
                if(c.first >= 12 && c.first > maxPair.second)//Probably the second part is not tested
                {
                    maxPair = {i,c.first};
                    for(auto n : offSet)
                        if(n.second == c.first)
                            maxOff = n.first;
                }
            }
        }
        if(maxPair.first == -1){
            scanners.push(current); // nothing found in this round
            continue;
        }

        vector<Beacon> matching = getIteration(current,maxPair.first);
        Beacon t = findTrans(grid,matching,maxOff); 
        int dupecount = 0;
        vector<Beacon> candidates;
        // we want to find the transformation so that it matches other points in grid
        for(auto m : matching){
            Beacon candidate = Beacon(m.x+t.x,m.y+t.y,m.z+t.z);
            bool dupe = false;
            for(auto g : grid){
                if(candidate == g){
                    dupe = true;
                    dupecount++;
                    break;
                }
            }
            if(!dupe) candidates.push_back(candidate); //these are beacons not already in grid
        }
        if(dupecount < maxPair.second){
            scanners.push(current);
            continue;
        }
        vector<Beacon> newGrid;
        merge(grid.begin(), grid.end(), candidates.begin(), candidates.end(), back_inserter(newGrid));
        newGrid.erase(unique(newGrid.begin(), newGrid.end()), newGrid.end());
        grid = newGrid;
        scannerPos.push_back(t);
    }
    cout << grid.size() << endl;
    int maxDist = -1;
    for(auto l: scannerPos)
    for(auto r: scannerPos)
        if(l.offset(r) > maxDist)
            maxDist = l.offset(r);
    cout << maxDist << endl;
}