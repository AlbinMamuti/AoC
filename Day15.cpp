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
#define INF 0x3f3f3f3f
typedef tuple<int,int,int> triplet;

class Graph
{
    int H;
    int W;
  
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    vector<vector<int>> grid;
  
public:
    Graph(int H, int W,vector<vector<int>> grid);  // Constructor
  
    // function to add an edge to graph
    int number(triplet t);
    // prints shortest path from s
    void shortestPath(int s);
};
  
// Allocates memory for adjacency list
Graph::Graph(int H, int W,vector<vector<int>> grid)
{
    this->H = H;
    this->W = W;
    this->grid = grid;
}
  
int Graph::number(triplet t){
    int w;
    int i;
    int j;
    std::tie(w,i,j) = t;
    return ( H * i + j);
}  
// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{   
    int srcI = 0;
    int srcJ = 0;
    priority_queue< triplet, vector<triplet>, greater<triplet> > pq; 
    vector<int> dist(H*W,INF);
    vector<bool> closed(H*W,false);
    vector<int> pred(H*W,-1);
    pq.push(make_tuple(0,srcI,srcJ));
    dist[src] = 0;
    

    vector<pair<int,int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};

    while(!pq.empty())
    {   
        triplet curr = pq.top();
        pq.pop();
        int w;
        int i;
        int j;
        std::tie(w,i,j) = curr;
        int id = number(curr);
        closed[id] = true;
        for(pair<int,int> dir : dirs){
            
            int row = i + dir.first;
            int col = j + dir.second;
            if(!(0 <= row && row < H && 0 <= col && col < W))
                continue;
            triplet temp = make_tuple(grid[row][col],row,col);
            int id2 = number(temp);
            
            if(!closed[id2]){
                if(dist[id] + grid[row][col] < dist[id2]){
                    dist[id2] = dist[id] + grid[row][col];
                    pred[id2] = id;
                    pq.push(make_tuple(dist[id2],i+dir.first,j+dir.second));
                }
            }
        }

    }
    cout << dist[H*W-1]<<endl;
}

void tokenize(string &str, char delim, vector<vector<int>> &dp)
{
    stringstream ss(str);
    std::string s;
    std::getline(ss,s,delim);
    int n = s.length();
    char arr[n+1];
    strcpy(arr,s.c_str());
    vector<int> row;
    for(int i = 0; i < n; i++){
        row.push_back(arr[i] - '0');
    }
    dp.push_back(row);
}
int min4(int a, int b){
    return a > b ? b : a;
}

int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<vector<int>> grid; 
    for(string line; getline(input_file,line);){
       tokenize(line, ' ', grid);
    }
    int H = grid.size();
    int W = grid[0].size();
        vector<vector<int>> newGrid(5*H, vector<int>(5*W));

    for(int HighRow = 0; HighRow < 5; HighRow ++){
        for(int HighCol = 0; HighCol < 5; HighCol++){
            int mod = 9;
            int adder = HighRow+HighCol;
            for(int i = HighRow*H; i < (HighRow+1)*H; i++){
                for(int j = HighCol*W; j < (HighCol+1) * W; j++){
                    int row = i - (HighRow * H);
                    int col = j - (HighCol * W);
                    int temp = grid[row][col];
                    newGrid[i][j] = (grid[row][col] + adder);
                    if(newGrid[i][j] > 9){
                        newGrid[i][j] = (newGrid[i][j]) % 9 ;
                    }
                }
            }
        }
    }
    H = 5*H;
    W = 5*W;
    assert(H == W);
    int V = H*W;
    Graph g(H,W,newGrid);
    g.shortestPath(0);

}
