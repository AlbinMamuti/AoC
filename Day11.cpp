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

using namespace std;

void tokenize(string &str, char delim, vector<vector<int>> &out)
{
    stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim))
    {
        long long x = stoll(s);
        vector<int> temp;
        while(x){
            temp.push_back(x%10);
            x /= 10;
        }
        reverse(temp.begin(),temp.end());
        out.push_back(temp);
    }
}

int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<vector<int>> input;
    vector<pair<int,int>> dir = {{0,-1},{0,1},{1,0},{1,1}, {1,-1},{-1,0},{-1,-1},{-1,1}};
    for(string line; getline(input_file,line);){
        tokenize(line, ' ', input);
    }
    int size = 10;
    auto inb = [size](int i, int j) {return 0 <= i && i < size && 0 <= j && j < size;};
    int ans = 0;
    for(int Time = 0; Time < 1000; Time++){
        vector<vector<bool>> expl(size, vector<bool>(size));
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                input[i][j]++;
            }
        }
        
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(input[i][j] > 9){
                    queue<pair<int,int>> q;
                    q.push({i,j});
                    while(!q.empty() ){
                        pair<int,int> curr = q.front();
                        q.pop();
                        if(expl[curr.first][curr.second])
                            continue;
                        expl[curr.first][curr.second] = true;
                        input[curr.first][curr.second] = 0;
                        ans++;
                        for(pair<int,int> p : dir){
                            int row = curr.first + p.first;
                            int col = curr.second + p.second;
                            if(!inb(row, col) || expl[row][col])
                                continue;
                            if(!expl[row][col])    
                                input[row][col]++;
                            if(input[row][col] > 9){
                                q.push({row,col});
                            }    
                        }
                    } 
                }
            }
        }
        bool flag = true;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(input[i][j] != 0){
                    flag = false;
                    break;
                }
            }
        }
        if(flag){
            cout << Time+1 << endl;
            break;
        }
            
        
    }
}