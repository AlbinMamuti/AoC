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
typedef unsigned long long lld;
int maxInfMinus = 0;
class Triplet;
class Triplet
{
public:
    int x1, x2, y1, y2, z1, z2;
    int time;
    bool on;
    lld volume;
    Triplet();

    Triplet(int _x1, int _x2, int _y1, int _y2, int _z1, int _z2, bool _on, int _time)
    {
        x1 = _x1;
        x2 = _x2;
        y1 = _y1;
        y2 = _y2;
        z1 = _z1;
        z2 = _z2;
        on = _on;
        time = _time;
    }
    lld _volume()
    {
        lld xL = x2 - x1 + 1;
        lld yL = y2 - y1 + 1;
        lld zL = z2 - z1 + 1;
        volume = xL * yL * zL;
        return volume;
    }
};
bool intersect(Triplet A, Triplet B)
{ // might be wrong
    if (A.x2 < B.x1 || B.x2 < A.x1)
        return false;
    if (A.y2 < B.y1 || B.y2 < A.y1)
        return false;
    if (A.z2 < B.z1 || B.z2 < A.z1)
        return false;
    return true;
}
void subtract(Triplet &A, Triplet &B, vector<Triplet> &queue)
{
    if (!intersect(A, B))
        return;
    int x1, x2, y1, y2, z1, z2;
    x1 = max(A.x1, B.x1);
    x2 = min(A.x2, B.x2);
    y1 = max(A.y1, B.y1);
    y2 = min(A.y2, B.y2);
    z1 = max(A.z1, B.z1);
    z2 = min(A.z2, B.z2);
    Triplet c(x1, x2, y1, y2, z1, z2, false, -1);
    if (A.z1 < c.z1)
        queue.emplace_back(Triplet(A.x1, A.x2, A.y1, A.y2, A.z1, c.z1 - 1, false, -1)); // ?
    if (c.z2 < A.z2)
        queue.emplace_back(Triplet(A.x1, A.x2, A.y1, A.y2, c.z2 + 1, A.z2, false, -1));
    if (A.x1 < c.x1)
        queue.emplace_back(Triplet(A.x1, c.x1 - 1, A.y1, A.y2, c.z1, c.z2, false, -1));
    if (c.x2 < A.x2)
        queue.emplace_back(Triplet(c.x2 + 1, A.x2, A.y1, A.y2, c.z1, c.z2, false, -1));
    if (A.y1 < c.y1)
        queue.emplace_back(Triplet(c.x1, c.x2, A.y1, c.y1 - 1, c.z1, c.z2, false, -1));
    if (c.y2 < A.y2)
        queue.emplace_back(Triplet(c.x1, c.x2, c.y2 + 1, A.y2, c.z1, c.z2, false, -1));
}

Triplet read_input(string line)
{
    int x1, x2, y1, y2, z1, z2, time;
    bool on;
    string first = line.substr(0, 2);
    if (first == "on")
        sscanf(line.c_str(), "on x=%d..%d,y=%d..%d,z=%d..%d", &x1, &x2, &y1, &y2, &z1, &z2);
    else
        sscanf(line.c_str(), "off x=%d..%d,y=%d..%d,z=%d..%d", &x1, &x2, &y1, &y2, &z1, &z2);
    on = first == "on" ? true : false;
    Triplet t(x1, x2, y1, y2, z1, z2, on, -1);
    t._volume();
    return t;
}

int main()
{
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<Triplet> input;
    lld ans = 0;
    for (string line; getline(input_file, line);)
    { // read only as it goes, because we dont consider every pair with every pair, but only if time allows it
        Triplet current = read_input(line);
        vector<Triplet> temp;
        for (auto &c : input)
        {
            if (!intersect(c, current))
                temp.push_back(c);
            else
                subtract(c, current, temp);
        }
        if (current.on)
            temp.push_back(current);
        input = std::move(temp);
    }
    for (auto &c : input)
    {
        ans += c._volume();
    }
    cout << ans << endl;
}