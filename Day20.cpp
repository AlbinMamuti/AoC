#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int getIndex(vector<vector<char>> grid, int x, int y){
    int index = 0;
    for(int i = -1; i<=1; i++)
    for(int j = -1; j<= 1; j++)
        index = (index <<= 1) + (grid[x+i][y+j] == '.' ? 0 : 1);
    return index;
}
void enlarge(vector<vector<char>> &grid, char c){
    for(int i = 0; i < grid.size(); i++){
        grid[i].insert(grid[i].begin(), c);
        grid[i].insert(grid[i].end(), c);
    }
    vector<char> line(grid[0].size(),c);
    grid.insert(grid.begin(),line);
    grid.insert(grid.end(),line);
}
void applyAlgo(char algo[], vector<vector<char>> grid, vector<vector<char>> &output, int row, int col){
    char sequence[9];
    for(int i = row-1; i  < row+2; i++){
        for(int j = col-1; j < col+2; j++){
            int place = 8 - ((i-(row-1))*3 + (j-(col-1)));
            char temp = grid[i][j];
            if(temp == '#'){
                sequence[place] = '1';
            }
            else{
                sequence[place] = '0';
            }
            //sequence[place] = (temp == '#') ? '1' : '0';
        }
    }
    string s = sequence;
    int place = stoi(s,0,2);
    char temp = algo[place-1];
    output[row][col] = temp;
}
void print(vector<vector<char>> grid){
    cout << endl;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
}
int main(int argc, char * argv[]){

    ifstream input; string line;
    if (argc < 2) { 
        input.open("inputPartOne.txt");
    }else
        input.open(argv[1]);
    char algo[512];

    vector<vector<char>> grid;
    int help = 0;
    while (!input.eof()) {
        std::getline(input, line);
        if(help == 0){
            strcpy(algo,line.c_str());
            help++;
            std::getline(input,line);
        } else {            
            char temp[line.size()];
            strcpy(temp,line.c_str());
            vector<char> linie(temp, temp + line.size());
            grid.push_back(linie);
        }
    }
    vector<char> alg(algo, algo+512);

    for(int i = 0; i < 5; i++) enlarge(grid,'.');
    int H = grid.size();
    int W = grid.size();
    for(int rep = 0; rep < 50; rep++){
        //print(grid);
        vector<vector<char>> nextGrid;
        for(int i = 0; i < grid.size(); i++){
            vector<char> thisLine;
            for(int j = 0; j < grid[i].size(); j++){
                if(i == 0 || j == 0 || i == grid.size()-1 || j == grid[i].size()-1)
                    thisLine.push_back(grid[0][0] == '.' ? alg[0] : alg[511]);
                else
                    thisLine.push_back(alg[getIndex(grid,i,j)]);
            }
            nextGrid.push_back(thisLine);
        }
        enlarge(nextGrid, nextGrid[2][2]);
        grid = nextGrid;
    }
    //print(grid);
    long long ans = 0;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid.size(); j++){
            ans += grid[i][j] == '#' ? 1 : 0;
        }
    }
    cout << ans << endl;
}