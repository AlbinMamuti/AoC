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

char MODO[15] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
int main()
{
    ifstream input("inputPartOne.txt");
    lld w, x, y, z;
    string line;
    int pos = 0;
    vector<int> div;
    vector<int> check;
    vector<int> OFFSET;
    for (int k = 0; k < 14; k++)
    {
        for (int i = 0; i < 18; i++)
        {
            getline(input, line);
            if (i == 0)
                continue;
            if (i == 4)
            {
                int temp;
                sscanf(line.c_str(), "div z %d", &temp);
                div.push_back(temp);
            }
            else if (i == 5)
            {
                int temp;
                sscanf(line.c_str(), "add x %d", &temp);
                check.push_back(temp);
            }
            else if (i == 15)
            {
                int temp;
                sscanf(line.c_str(), "add y %d", &temp);
                OFFSET.push_back(temp);
            }
        }
    }
    printf("DIV | CHE | OFF\n");
    for (int i = 0; i < 14; i++)
    {
        printf("%3d | %3d | %3d \n", div[i], check[i], OFFSET[i]);
    }
    MODO[4] = '9'; // p1
    MODO[3] = '8';

    MODO[6] = '2';
    MODO[5] = '9';

    MODO[8] = '9';
    MODO[9] = '4';

    MODO[7] = '9';
    MODO[10] = '6';

    MODO[2] = '9';
    MODO[11] = '1';

    MODO[1] = '5';
    MODO[12] = '9';

    MODO[0] = '4';
    MODO[13] = '9';
    printf("Sol P1: %s\n", MODO);

    MODO[4] = '2'; // p2
    MODO[3] = '1';

    MODO[6] = '1';
    MODO[5] = '8';

    MODO[8] = '6';
    MODO[9] = '1';

    MODO[7] = '4';
    MODO[10] = '1';

    MODO[2] = '9';
    MODO[11] = '1';

    MODO[1] = '1';
    MODO[12] = '5';

    MODO[0] = '1';
    MODO[13] = '6';
    printf("Sol P2: %s\n", MODO);
}