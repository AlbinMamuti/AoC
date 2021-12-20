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
typedef pair<int,int> PairI;

class Graph
{
    int H; //Matrix Graph
    int W;
    vector<vector<int>> grid;
  
public:
    Graph(int H, int W,vector<vector<int>> grid);  // Constructor
    // ID for Day15
    int number(triplet t);
    // Dijkstra Day15
    void shortestPath(int s);
    vector<int> Dijkstra(int src);
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
vector<int> Graph::Dijkstra(int src){
    priority_queue<PairI, vector<PairI>, greater<PairI> > pq;
    vector<int> dist(H,INF);
    vector<bool> closed(H,false);
    vector<int> pred(H,-1);
    pq.push(make_pair(src,0));
    dist[src] = 0;
    while(!pq.empty()){
        int curr = pq.top().second;
        pq.pop();
        if(closed[curr])
            continue;
        closed[curr] = true;
        for(int i = 0; i < H; i++){
            if(grid[curr][i] != -1 && !closed[i]){
                if(dist[curr] + grid[curr][i] < dist[i]){
                    dist[i] = dist[curr] + grid[curr][i];
                    pred[i] = curr;
                    pq.push(make_pair(i, dist[i]));
                }
            }
        }
    }
    return dist;
}
// Day15 Djikstra
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