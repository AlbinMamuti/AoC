#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lld;
vector<vector<vector<bool>>> grid(101, vector<vector<bool>>(101, vector<bool>(101, false)));

class Triplet;
class Triplet
{
public:
    bool on;
    int x1, x2, y1, y2, z1, z2;
    Triplet(){};
    Triplet(int _x1, int _x2, int _y1, int _y2, int _z1, int _z2, bool _on)
    {
        x1 = _x1;
        x2 = _x2;
        y1 = _y1;
        y2 = _y2;
        z1 = _z1;
        z2 = _z2;
        on = _on;
    }
    void turnOn(vector<vector<vector<bool>>> &grid)
    {
        for (int i = x1 + 50; i <= x2 + 50; i++)
            for (int j = y1 + 50; j <= y2 + 50; j++)
                for (int k = z1 + 50; k <= z2 + 50; k++)
                    grid[i][j][k] = on;
    }
};
bool check(Triplet t){
    if(-50 <= (t.x1) && (t.x2) <= 50)
        if(-50 <= (t.y1) && (t.y2) <= 50)
            if(-50 <= (t.z1) && (t.z2) <= 50)
                return true;
    return false;
}
int main(int argc, char *argv[])
{

    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    string line;
    vector<Triplet> instr;
    while (!input_file.eof())
    {
        std::getline(input_file, line);
        int t1 = line.find(" ");
        const char * c_line = line.c_str();
        char a,b,c;
        int x1,x2,y1,y2,z1,z2;
        sscanf(c_line, "%c%c x=%d..%d,y=%d..%d,z=%d..%d",&a,&b,&x1,&x2,&y1,&y2,&z1,&z2);
        string s = string() + a + b;
        if(s == "of"){
            sscanf(c_line, "%c%c%c x=%d..%d,y=%d..%d,z=%d..%d",&a,&b,&c,&x1,&x2,&y1,&y2,&z1,&z2);
        }
        bool on = s == "on" ? true : false;
        Triplet t = Triplet(x1, x2, y1, y2, z1, z2, on);
        if(check(t))
            instr.push_back(t);
    }
    lld ans = 0;

    for(Triplet t: instr){
        t.turnOn(grid);
    }
    for(int i = 0; i < 101; i++){
        for(int j = 0; j < 101; j++){
            for(int k = 0; k < 101; k++){
                ans += grid[i][j][k] ? 1 : 0;
            }
        }
    }
    cout << ans  << endl;

}