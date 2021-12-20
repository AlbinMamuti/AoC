#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#include <Eigen/Dense>
using namespace std;
#define INF 0x3f3f3f3f
typedef Eigen::Vector3i beacon;
typedef Eigen::Matrix3i Perm;
typedef tuple<int,int,int> triplet;

vector<beacon> generatePerm(beacon input){

    auto roll = [](beacon in){
        beacon res = {in(0),in(2),-in(3)};
        return res;
    };
    auto turn = [](beacon in){
        beacon res = {-in(1),in(0),in(2)};
        return res;
    };
    vector<beacon> res;
    for(int c = 0; c < 2; c++){
        for(int s = 0; s < 3; s++){
            input = roll(input);
            res.push_back(input);
            for(int i = 0; i < 3; i++){
                input = turn(input);
                res.push_back(input);
            }
        }
        input = roll(turn(roll(input)));
    }
    return res;
}

bool read_input(vector<vector<beacon>> &input){
    string filename = "inputPartOne.txt";   
    ifstream input_file(filename);
    int i = 0;
    string temp1;
    getline(input_file,temp1);
    vector<beacon> row;
    for(string line;getline(input_file, line);){
        int n = line.size();
        char arr[n+1];
        strcpy(arr,line.c_str());
        if(arr[0] == '-' && arr[1] == '-' && arr[2] == '-'){
            i++;
            continue;
        }
        if(n == 0){
            input.push_back(row);
            row.clear();
            continue;
        }
        stringstream ss(line);
        std::string s;
        
        getline(ss,s,',');
        int x = stoi(s); 
        getline(ss,s,',');
        int y = stoi(s);
        getline(ss,s,',');
        int z = stoi(s);
        beacon t = {x,y,z};
        row.push_back(t);
    }
    return false;
}

triplet convBeacon(beacon in){
    return make_tuple(in(0),in(1),in(2));
}
beacon convTriplet(triplet in){
    int x,y,z;
    std::tie(x,y,z) = in;
    beacon res;
    res << x,y,z;
    return res;
}
beacon calc(beacon a, beacon b){
    beacon res;
    res = a + b ;

    return res;
}
void solve(vector<vector<beacon>> input){
    vector<Perm> rot;
    beacon p;
    vector<beacon> flips;
    Perm one, two, three, four, five , six;
    beacon a,b,c,d,e,f,g,h;
    a << 1,1,1; 
    b << 1,1,-1; c << 1,-1,1; d << -1,1,1; e << 1,-1,-1; f << -1,-1,1;
    g << -1,1,-1; h << -1,-1,-1;
    flips.push_back(a);flips.push_back(b);flips.push_back(c);flips.push_back(d);
    flips.push_back(e);flips.push_back(f);flips.push_back(g);flips.push_back(h);
    one << 1, 0, 0 , 0 , 1 , 0, 0 , 0 , 1;
    two << 1,0,0,0,0,1,0,1,0;
    three << 0,1,0,1,0,0,0,0,1;
    four << 0,1,0,0,0,1,1,0,0;
    five << 0,0,1,0,1,0,1,0,0;
    six << 0,0,1,1,0,0,0,1,0;
    //cout << one << endl << two << endl << three << endl << four << endl << five << endl << six << endl;
    rot.push_back(one);rot.push_back(two);rot.push_back(three);rot.push_back(four);
    rot.push_back(five);rot.push_back(six);
    vector<Perm> perms;
    for(Perm A: rot){
        for(beacon B: flips){
            
            Perm res = B.asDiagonal() * A;
            perms.push_back(res);
        }
    }
    int n = input.size();
    vector<beacon> pos(n);
    vector<int> rotation(n, -1);
    vector<bool> vis(n, false);
    pos[0] = {0,0,0};
    rotation[0] = 0;
    vis[0] = true;
    for(int scanner1 = 0; scanner1 < n; scanner1++){
        if(!vis[scanner1])
            continue;
        for(int scanner2 = scanner1+1; scanner2 < n; scanner2++){
            bool foundWinnter = false;
                for(int rot2 = 0; rot2 < 48; rot2++){
                    map<triplet, int> diffCounter;
                    for(int beacon1 = 0; beacon1 < input[scanner1].size(); beacon1++){
                        for(int beacon2 = 0; beacon2 < input[scanner2].size(); beacon2++){
                            beacon b1 = input[scanner1][beacon1];
                            beacon b2 = perms[rot2] * input[scanner2][beacon2]; 
                            beacon diff = (b1 - b2);
                            triplet diffForMap = convBeacon(diff);
                            diffCounter[diffForMap]++;
                            if(diffCounter[diffForMap] >= 12){
                                foundWinnter = true;
                                beacon relDist = pos[scanner1] - diff;
                                beacon relDist2 = pos[scanner1] + diff;
                                beacon relDist3 = diff - pos[scanner1] ;
                                cout << " found match: " << scanner1 << " " << scanner2 << endl;
                                cout << pos[scanner1].transpose() << " pos Scanner 1 "<< endl;
                                cout << diff.transpose() << " diff" << endl;
                                cout << (relDist).transpose() << " relDist"  << endl;
                                cout << (relDist2).transpose() << " relDist2"  << endl;
                                cout << (relDist3).transpose() << " relDist3"  << endl;
                                cout << endl;
                                //cout << perms[rot2]<< endl;
                                rotation[scanner2] = rot2;
                                pos[scanner2] = diff;

                            }
                        }
                        if(foundWinnter)
                            break;
                    }
                    if(foundWinnter)
                    break;                    
                }
            if(!foundWinnter)
                continue;
            vector<beacon> curr = input[scanner2];
            int rot = rotation[scanner2];
            beacon posMe = pos[scanner2];
            for(int i = 0; i < curr.size(); i++){          
                curr[i] = perms[rot] * curr[i];
                curr[i] += posMe;
                cout << " " << curr[i].transpose() << endl;
            }
            vis[scanner2] = true;
        }
    }

}

int main(){
    vector<vector<beacon>> input;
    read_input(input);
    solve(input);


}
