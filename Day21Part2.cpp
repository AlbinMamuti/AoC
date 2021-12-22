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
// Dirac do all three;
map<string, vector<lld>> gameStates;
lld recCalls = 0;
vector<lld> rec(int whoTurn, int turn, int P1, int P2, int S1, int S2)
{
    recCalls++;
    auto hash = [whoTurn, turn, P1, P2, S1, S2]()
    {
        stringstream s;
        s << whoTurn << "," << turn << "," << P1 << "," << P1 << "," << P2 << "," << S1 << "," << S2;
        return s.str();
    };
    // return if someone already won
    if (S1 >= 21)
        return {1, 0};
    if (S2 >= 21)
        return {0, 1};
    // string s stores the string index of our current gamestate
    string s = hash();
    // Check if this gameState is reached in memory, if true return
    if (gameStates.find(s) != gameStates.end())
        return gameStates[s];
    // If not try every combination of the dices, 27
    vector<lld> arr(2, 0);
    for (int firstDie = 1; firstDie <= 3; firstDie++)
    {
        for (int secDie = 1; secDie <= 3; secDie++)
        {
            for (int thirdDie = 1; thirdDie <= 3; thirdDie++)
            {
                // calculate and see who's turn it is, start next recursion with updated Values
                int move = firstDie + secDie + thirdDie;
                int n1 = ((P1 + move - 1) % 10) + 1;
                int n2 = ((P2 + move - 1) % 10) + 1;
                vector<lld> res;
                if (whoTurn == 1)
                {
                    res = rec(2, (turn + 1), n1, P2, (S1 + n1), S2);
                }
                else
                {
                    res = rec(1, (turn + 1), P1, n2, S1, (S2 + n2));
                }
                // add the values returned from Recursion , arr[0] == Wins of player 1, arr[1] == Wins of Player2
                arr[0] += res[0];
                arr[1] += res[1];
            }
        }
    }
    // update Gamestate and return
    gameStates[s] = arr;
    return arr;
}
int main()
{
    vector<lld> result = rec(1, 1, 5, 6, 0, 0);
    cout << result[0] << ", " << result[1] << endl;
    cout << "Recursion Calls: " << recCalls << endl;
}