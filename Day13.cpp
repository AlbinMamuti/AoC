#include <fstream>
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
using namespace std;
void tokenize2(string &str, char delim, vector<pair<int,int>> &coord)
{
    stringstream ss(str);
    std::string s;
    std::getline(ss,s,delim);
    std::getline(ss,s,delim);
    std::getline(ss,s,delim);
    bool flagy = false;
    if(s == "y")
        flagy = true;
    std::getline(ss,s,delim);
    std::getline(ss,s,delim);
    int temp = stoi(s);
    if(flagy){
        coord.push_back({0,temp});
    }
    else{
        coord.push_back({temp,0});
    }
}
bool tokenize(string &str, char delim, vector<pair<int,int>> &coord)
{
    stringstream ss(str);
    std::string s;
    std::getline(ss,s,delim);
    if(s == ""){
        return false;
    }
    int t = stoi(s);
    std::getline(ss,s,delim);
    int b = stoi(s);
    pair<int,int> p = {t,b};
    coord.push_back(p); 
    return true;
}
void draw(vector<pair<int,int>> coord){
    int xmax = 0;
    int ymax = 0;
    for(pair<int,int> p : coord){
        xmax = p.first > xmax ? p.first : xmax;
        ymax = p.second > ymax ? p.second : ymax;
    }
    ymax++;
    xmax++;
    char drw[ymax][xmax];
    for(int i = 0; i < ymax; i++){
        for(int j = 0; j < xmax; j++){
            drw[i][j] = '.';
        }
    }
    for(pair <int,int> p : coord){
        drw[p.second][p.first] = '#';
    }
    for(int i = 0; i < ymax; i++){
        for(int j = 0; j < xmax; j++){
            cout << drw[i][j];
        }
        cout << endl;
    }
}
void eraseD(vector<pair<int,int>> &coord){
    vector<pair<int,int>> ret;
    for(int i = 0; i < coord.size(); i++){
        bool flag = false;
        for(int j = i+1; j < coord.size(); j++){
            pair<int,int> p1 = coord[i];
            pair<int,int> p2 = coord[j];
            if(p1.first == p2.first && p1.second == p2.second){
                flag = true;
            }
        }
        if(flag)
            continue;
        ret.push_back(coord[i]);
    }
    coord = ret;
}
int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<pair<int,int>> coord;
    vector<pair<int,int>> folds;

//    vector<pair<int,int>> dir = {{0,-1},{0,1},{1,0},{1,1}, {1,-1},{-1,0},{-1,-1},{-1,1}};
    for(string line; getline(input_file,line);){
        if(!tokenize(line, ',', coord)) break;
    }
    //read folds
    for(string line; getline(input_file,line);){
        tokenize2(line, ' ', folds);
    }
    //draw(coord);
    cout << endl;
    for(pair<int,int> f : folds){
        if(f.first == 0){//y fold
            for(pair<int,int> &c : coord){
                int diff = std::abs(c.second - f.second);
                c.second = f.second - diff;
            }
        }
        else{//x fold
            for(pair<int,int> &c: coord){
                int diff = std::abs(c.first - f.first);
                c.first = f.first - diff;
            }
        }
        eraseD(coord);
        //
        //cout << coord.size() << endl;
    }
    draw(coord);
    return 0;
}
