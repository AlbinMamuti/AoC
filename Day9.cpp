#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <queue>

using namespace std;

void tokenize(string &str, char delim, vector<vector<int>> &out)
{
    stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim))
    {
        int n = s.length();
        char c_a[n+1];
        strcpy(c_a,s.c_str());
        vector<int> temp;
        for(int i = 0; i < n; i++){
            int x = c_a[i] - '0';
            temp.push_back(x);
        }
        out.push_back(temp);
    }
}

void dfs(vector<vector<int>> &input, vector<vector<bool>> &visited, int row, int col){

}
bool bound(int row, int col, int H, int L){
    return (0 <= row && row < H && 0 <= col && col < L);
}
void part2(vector<vector<int>> &input){
    int H = input.size();
    int W = input[0].size();
    vector<vector<bool>> vis(H,vector<bool>(W));
    vector<int> ans;
    for(int row = 0; row < H; row++){
        for(int col = 0; col < W; col++){
            if(!vis[row][col] && input[row][col] != 9){
                int size = 0;
                queue<pair<int,int>> q;
                q.push({row,col});
                vis[row][col] = true;
                while(!q.empty()){
                    pair<int,int> t = q.front();
                    q.pop();
                    if(bound(t.first+1, t.second, H,W) && !vis[t.first+1][t.second] && input[t.first+1][t.second] != 9){
                        q.push({t.first+1,t.second});
                        vis[t.first+1][t.second] = true;
                    }
                     if(bound(t.first, t.second+1, H,W) && !vis[t.first][t.second+1] && input[t.first][t.second+1] != 9){
                        q.push({t.first,t.second+1});
                        vis[t.first][t.second+1] = true;
                    }
                     if(bound(t.first-1, t.second, H,W) && !vis[t.first-1][t.second] && input[t.first-1][t.second] != 9){
                        q.push({t.first-1,t.second});
                        vis[t.first-1][t.second] = true;
                    }
                     if(bound(t.first, t.second-1, H,W) && !vis[t.first][t.second-1] && input[t.first][t.second-1] != 9){
                        q.push({t.first,t.second-1});
                        vis[t.first][t.second-1] = true;
                    }
                    size++;
                }
                ans.push_back(size);
            }
        }
    }
    sort(ans.begin(),ans.end(),greater<int>());
    cout << ans[0] * ans[1] * ans[2] << endl;
    
}

int main(){

    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<vector<int>> input;
    int k = 0;
    int total = 0;
    for(string line; getline(input_file,line);){
        tokenize(line, ' ', input);
    }
    int H = input.size();
    int L = input[0].size();
    vector<int> lowPoints;
    part2(input);
    for(int i = 0; i < H; i++){
        for(int j = 0; j < L; j++){
            if((i == 0 && j == 0)){
                if(input[i][j] < input[i][j+1] && input[i][j] < input[i+1][j])
                    lowPoints.push_back(input[i][j]+1); 
            }
            else if((i == H-1 && j == L-1)){
                if(input[i][j] < input[i][j-1] && input[i][j] < input[i-1][j])
                    lowPoints.push_back(input[i][j]+1); 
            }
            else if((i == 0 && j == L-1)){
                if(input[i][j] < input[i][j-1] && input[i][j] < input[i+1][j])
                    lowPoints.push_back(input[i][j]+1); 
            }
            else if((i == H-1 && j == 0)){
                if(input[i][j] < input[i][j+1] && input[i][j] < input[i-1][j])
                    lowPoints.push_back(input[i][j]+1); 
            }
            else if(i == 0){
                int temp = input[i][j];
                if(temp < input[i+1][j] && temp < input[i][j+1] && temp < input[i][j-1])
                    lowPoints.push_back(temp+1);
            }
            else if(i == H-1){
                int temp = input[i][j];
                if(temp < input[i-1][j] && temp < input[i][j+1] && temp < input[i][j-1])
                    lowPoints.push_back(temp+1);
            }
            else if(j == 0){
                int temp = input[i][j];
                if(temp < input[i+1][j] && temp < input[i-1][j] && temp < input[i][j+1])
                    lowPoints.push_back(temp+1);
            }
            else if(j == L-1){
                int temp = input[i][j];
                if(temp < input[i+1][j] && temp < input[i][j-1] && temp < input[i-1][j])
                    lowPoints.push_back(temp+1);
            }
            else{
                int temp = input[i][j];
                if(temp < input[i+1][j] && temp < input[i][j+1] && temp < input[i-1][j] && temp < input[i][j-1])
                    lowPoints.push_back(temp+1);
            }

        }
    }
    int ans = 0;
    for(int i : lowPoints){
        ans+= i;
    }

}