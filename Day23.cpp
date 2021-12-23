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

vector<string> doneState;
map<char, int> costs = {{'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};
map<char, int> doorWayM = {{'A', 2}, {'B', 4}, {'C', 6}, {'D', 8}};
map<char, int> orderMap = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}};
int validPos[] = {0, 1, 3, 5, 7, 9, 10};
int doorWays[] = {2, 4, 6, 8};

struct State
{
    lld energy;
    vector<string> rooms;
    string hallway;
    vector<int> moves;
};
struct stackOverFlow
{
    bool operator()(const State &a, const State &b) { return a.energy > b.energy; };
};

string hashState(State s)
{
    stringstream SS;
    SS << s.energy << "," << s.hallway << "," << s.rooms[0] << "," << s.rooms[1] << "," << s.rooms[2] << "," << s.rooms[3];
    return SS.str();
}
bool isDone(State s)
{
    for (int i = 0; i < 4; i++)
        if (s.rooms[i] != doneState[i])
            return false;
    return true;
}
bool isValid(State s)
{
    for (string r : s.rooms)
        if (r.size() > doneState[0].size())
            return false; // smth went horribly wrong
    if (s.energy < 0)
        return false; // invalid because of cost
    return true;
}
bool wrongRoom(State s, int pos)
{
    string validOrder = "ABCD";
    for (char room : s.rooms[pos])
        if (room != validOrder[pos])
            return true;
    return false; // in the sense that we are wrong Room
}
bool dfsHall(State s, int from, int where)
{
    int temp = from;
    int i = min(from, where);
    int j = max(from, where);
    for (int k = i; k <= j; k++)
    {
        if (k == temp || k == 2 || k == 4 || k == 6 || k == 8)
            continue; // we are at doorway
        if (s.hallway[k] != '.')
            return false; // something is in tha way
    }
    return true;
}
int solve()
{
    string in = "inputPartOne.txt";
    ifstream input(in);
    State baseState;
    baseState.energy = 0;
    baseState.hallway = "...........";
    for (int i = 0; i < 4; i++)
    {
        baseState.rooms.push_back("");
        doneState.push_back(""); // initialize empty
    }
    string line;
    getline(input, line);
    getline(input, line);
    getline(input, line);
    for (int i = 0; i < 4; i++)
    {
        baseState.rooms[0].push_back(line[3]);
        baseState.rooms[1].push_back(line[5]);
        baseState.rooms[2].push_back(line[7]);
        baseState.rooms[3].push_back(line[9]);
        getline(input, line);
        string order = "ABCD";
        for (int j = 0; j < 4; j++)
            doneState[j].push_back(order[j]);
    }
    int roomDepth = baseState.rooms[0].size();
    vector<State> que;

    int check = 0;
    set<string> vis;

    que.push_back(baseState);
    make_heap(que.begin(), que.end(), stackOverFlow());
    while (!que.empty())
    {
        State s = que.front();
        pop_heap(que.begin(), que.end(), stackOverFlow());
        que.pop_back();
        string hashOfS = hashState(s);
        if (vis.find(hashOfS) != vis.end())
            continue;
        vis.insert(hashOfS);
        if (isDone(s))
        {
            printf("Found one. Energy is: %lld\n", s.energy);
            return 0;
        }
        if (++check % 100000 == 0) // debug
            printf("Checked %10d States, Queue has %ld elements \n", check, que.size());
        for (int i = 0; i < 4; i++) // generate moves for animals in rooms
        {
            if (!wrongRoom(s, i))
            {
                continue; // already good position
            }
            char c = s.rooms[i][0]; // only this one can move, it is right by the hallway
            // Room to Room
            if (!wrongRoom(s, orderMap[c]) && dfsHall(s, doorWays[i], doorWays[orderMap[c]]))
            {
                State next = s;
                next.rooms[i].erase(0, 1); // delete first one
                int temp = roomDepth - next.rooms[i].size();
                temp += roomDepth - next.rooms[orderMap[c]].size();
                temp += std::abs(doorWays[i] - doorWays[orderMap[c]]);
                next.rooms[orderMap[c]] = c + next.rooms[orderMap[c]];
                next.energy += temp * costs[c];
                next.moves.push_back(temp);
                que.push_back(next);
                push_heap(que.begin(), que.end(), stackOverFlow());
            }

            // leave from Room to HallWays
            for (int j = 0; j < 7; j++)
            {
                if (dfsHall(s, doorWays[i], validPos[j])) // State from to where
                {
                    State next = s;
                    next.rooms[i].erase(0, 1); // we delete the one who goes ou
                    int temp = roomDepth - next.rooms[i].size();
                    next.hallway[validPos[j]] = c;
                    temp += std::abs(doorWays[i] - validPos[j]);
                    next.energy += temp * costs[c];
                    next.moves.push_back(temp);
                    que.push_back(next);
                    push_heap(que.begin(), que.end(), stackOverFlow());
                }
            }
        }
        // Seach all the ones in the Hallways and look if they can fit somewhere
        for (int i = 0; i < s.hallway.size(); i++)
        {
            char c = s.hallway[i];
            if (c == '.')
                continue; // no Animal
            if (!wrongRoom(s, orderMap[c]) && dfsHall(s, i, doorWays[orderMap[c]]))
            {
                State next = s;
                next.hallway[i] = '.'; // we moved the Animal away
                int temp = roomDepth - next.rooms[orderMap[c]].size();
                temp += std::abs(doorWays[orderMap[c]] - i);
                next.rooms[orderMap[c]] = c + next.rooms[orderMap[c]]; // moved into first slot
                next.energy += temp * costs[c];
                next.moves.push_back(temp);
                que.push_back(next);
                push_heap(que.begin(), que.end(), stackOverFlow());
            }
        }
    }
    return -1;
}
int main()
{
    solve();
}