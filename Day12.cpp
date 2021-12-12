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

int paths = 0;
vector<vector<string>> pathAll;
void tokenize(string &str, char delim, map<string,vector<string>> &m,map<string,bool> &visited)
{
    stringstream ss(str);
    std::string s;
    
    std::getline(ss,s,delim);
    string t = s;
    std::getline(ss,s,delim);
    string b = s;
    m[t].push_back(b);
    m[b].push_back(t);
    visited[t] = false;
}
bool isUpper(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isupper(c); });
}
int dfs(map<string,vector<string>> &m, string me, map<string,bool> visited, bool doub,vector<string> path){
    path.push_back(me);
    if(!isUpper(me))
        visited[me] = true;
    if(me == "end"){
        pathAll.push_back(path);
        return 1;
    } 
    int ret = 0;   
    vector<string> temp = m[me];
    for(string s : temp){
        bool iU = isUpper(s);
        if(!visited[s])
            ret += dfs(m,s,visited,doub,path);
        else if(visited[s] && !doub && s != "start"){
            ret += dfs(m,s,visited,true,path);
        }

    }
    return ret;
}
int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    map<string,vector<string>> input;
    map<string,bool> vis;
//    vector<pair<int,int>> dir = {{0,-1},{0,1},{1,0},{1,1}, {1,-1},{-1,0},{-1,-1},{-1,1}};
    for(string line; getline(input_file,line);){
        tokenize(line, '-', input,vis);
    }
    string begin = "start";
    string end = "end";
    vector<string> test;
    test.push_back(" ");

    dfs(input, begin, vis, false,test);
    sort(pathAll.begin(),pathAll.end());
    cout << pathAll.size() << endl; 
}
