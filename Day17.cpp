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
#include "Graph.h"
using namespace std;
#define INF 0x3f3f3f3f
typedef tuple<int,int,int> triplet;


bool read_input(vector<int> &input){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    for(string line;getline(input_file, line);){
        stringstream ss(line);
        std::string s;
        for(int i = 0; i<  4; i++){
            std::getline(ss,s,' ');
            int t = stoi (s);
            input.push_back(t);
        }
    }
    return true;
}

bool inbound(int x, int y, vector<int> input){
    return input[0] <= x && x <= input[1] && input[2] <= y && y <= input[3];
}

vector<pair<int,int>> bf2(vector<int> input){
    vector<pair<int,int>> ans;
    for(int i = 1; i < 1000; i++){
        for(int j = -200; j < 1000; j++){
            int x = 0;
            int y = 0;
            int velX = i;
            int velY = j;
            for(int time = 0; time < 1000000; time++){
                x += velX;
                y += velY;
                if(x > input[1])
                    break;
                if(y < input[2])
                    break;
                if(inbound(x,y,input)){
                    ans.push_back(make_pair(i,j));
                    break;
                }
                if(velX == 0){
                    velY--;
                }else if(velX > 0){
                    velX--;
                    velY--;
                }else{
                    velX++;
                    velY--;
                }
            }
        }
    }
    return ans;
}

pair<int,int> bf(vector<int> input){
    pair<int,int> ans;
    int highestYValue = -1000000;
    for(int i = 0; i < 1000; i++){
        for(int j = -86; j < 1000; j++){
            int x = 0;
            int y = 0;
            int velX = i;
            int velY = j;
            int highesYintern = -10000;
            for(int time = 0; time < 1000000; time++){
                x += velX;
                y += velY;
                if(x > input[1])
                    break;
                if(y < input[2])
                    break;
                if(velY > 0)
                    highesYintern = y;
                if(inbound(x,y,input)){
                    if(highestYValue < highesYintern){
                        highestYValue = highesYintern;
                        ans = {i,j};
                    }
                }
                if(velX == 0){
                    velY--;
                }else if(velX > 0){
                    velX--;
                    velY--;
                }else{
                    velX++;
                    velY--;
                }
            }
        }
    }
    cout << highestYValue << endl;
    return ans;
}

int main(){
    
    vector<int> input;

    read_input(input);

    //pair<int,int> ans = bf(input);
    //cout << ans.first << " " << ans.second << endl;
    vector<pair<int,int>> ans = bf2(input);
    cout << ans.size() << endl;

}
