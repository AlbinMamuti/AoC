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
typedef long long lld;
//Dirac do all three;
map<string, vector<lld> > gameStates;

vector<lld> rec(int whoTurn, int turn, int P1, int P2, int S1, int S2)
{
    if (S1 >= 21 || S2 >= 21)
    {
        vector<lld> one = {1, 0};
        vector<lld> two = {0, 1};
        if (S1 >= 21)
            return one;
        return two;
    }
    string s = to_string(whoTurn) + "," + to_string(turn) + "," + to_string(P1) + "," + to_string(P2) + "," + to_string(S1) + "," + to_string(S2);
    if (gameStates.find(s) != gameStates.end())
        return gameStates[s];
    vector<long long> arr(2, 0);
    for (int firstDie = 1; firstDie <= 3; firstDie++)
    {
        for (int secDie = 1; secDie <= 3; secDie++)
        {
            for (int thirdDie = 1; thirdDie <= 3; thirdDie++)
            {
                int move = firstDie + secDie + thirdDie;
                int n1 = ((P1 + move - 1) % 10) + 1;
                int n2 = ((P2 + move - 1) % 10) + 1;
                vector<long long> res;
                if (whoTurn == 1)
                {
                    res = rec(2, (turn + 1), n1, P2, (S1 + n1), S2);
                }
                else
                {
                    res = rec(1, (turn + 1), P1, n2, S1, (S2 + n2));
                }
                arr[0] += res[0];
                arr[1] += res[1];
            }
        }
    }
    gameStates[s] = arr;
    return arr;
}
int main()
{
    int play1Pos = 5;
    int play2Pos = 6;
    int play1Points = 0;
    int play2Points = 0;
    int turn = 1;
    int playerTurn = 1;
    vector<lld> result = rec(playerTurn, 1, 5, 6, 0, 0);
    cout << result[0] << ", " << result[1] << endl;
}