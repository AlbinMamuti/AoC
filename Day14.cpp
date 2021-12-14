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
using namespace std;
void tokenize2(string &str, char delim, vector<char> &in)
{
    stringstream ss(str);
    std::string s;
    std::getline(ss,s,delim);
    int n = s.length();
    char arr[n+1];
    strcpy(arr, s.c_str());
    for(int i = 0; i < n; i++)
        in.push_back(arr[i]);
}
void tokenize(string &str, char delim, map<string,char> &rules)
{
    stringstream ss(str);
    std::string s;
    std::getline(ss,s,delim);

    string from = s;
    std::getline(ss,s,delim);
    std::getline(ss,s,delim);
    std::getline(ss,s,delim);
    char to = s.front();
    rules[from] = to;

}

int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<char> in;
    map<string,char> rules; 
    map<char,long long> score;
    map<string,long long> numOcc;
    string line;
    getline(input_file,line);
    tokenize2(line, ' ', in);
    getline(input_file,line);
    for(string line; getline(input_file,line);){
       tokenize(line, ' ', rules);
    }
    vector<pair<char,char>> list;
    for(int i = 0; i < in.size()-1; i++){
        string from = std::string() + in[i] + in[i+1];
        numOcc[from]++;
    }
    int n = in.size();
    string temp = std::string() + in[n-1] + ' ';
    numOcc[temp]++;
    temp = std::string() + ' ' + in[0];
    numOcc[temp]++;  
    for(int i = 0; i < 40; i++){
        map<string,long long> tempMap;
        for (auto const& x : numOcc)
        {
            string fromS = x.first;
            long long mul = x.second;
            if(fromS.front() == ' ' || fromS.back() == ' '){
                tempMap[fromS] = 1;
                continue;
            }
            char Middle = rules[fromS];
            string lefti = std::string() + fromS.front() + Middle;
            string righti = std::string() + Middle + fromS.back();
            tempMap[lefti] += mul;
            tempMap[righti] += mul; 
        }
        numOcc = tempMap;
    }
    for(auto const& x : numOcc){
        string from = x.first;
        if(from.back() == ' ')
            continue;
        if(from.front() == ' '){
            score[from.back()]++;
            continue;
        }
        char to = from.back();
        long long mul = x.second;
        score[to] += mul;

    }
    long long max = LONG_LONG_MIN;
    long long  min = LONG_LONG_MAX;
    for (auto const& x : score)
    {
        if(x.second > max)
            max = x.second;
        else if(x.second <= min)
            min = x.second;
    }
    cout << (max - min) << endl;
}
