#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
#include <chrono>
using namespace std::chrono;
using namespace std;
typedef unsigned long long lld;

bool move(vector<string> &state)
{
    int H, W;
    H = state.size();
    W = state[0].size();
    bool moved = false;

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == '>' && state[i][(j + 1) % W] == '.')
                state[i][j] = 'M';

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'M')
            {
                moved = true;
                state[i][j] = '.';
                state[i][(j + 1) % W] = '>';
            }
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'v' && state[(i + 1) % H][j] == '.')
                state[i][j] = 'M';
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'M')
            {
                moved = true;
                state[i][j] = '.';
                state[(i + 1) % H][j] = 'v';
            }
    return moved;
}

void print(vector<string> &state)
{
    for (int i = 0; i < state.size(); i++)
    {
        cout << state[i] << endl;
    }
}

int main()
{
    ifstream input("inputPartOne.txt");
    vector<string> state;
    for (string line; getline(input, line);)
    {
        state.push_back(line);
    }
    int steps = 0;
    // print(state);
    while (move(state))
    {
        // print(state);
        // cout << endl;
        steps++;
    }
    cout << ++steps << endl;
    return 0;
}