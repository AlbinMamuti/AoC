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

int d = 1;

int Roll()
{
    return d++ + d++ + d++;
}

int main()
{

    int scorePlay1 = 0;
    int scorePlay2 = 0;
    int posPlay1 = 5;
    int posPlay2 = 6; //0,...,9

    for (int i = 1; i < 2500; i++)
    {
        int move = Roll();
        if (i % 2 == 1)
        {
            posPlay1 = ((posPlay1 + move - 1) % 10) + 1;
            scorePlay1 += (posPlay1);
            printf("Player %d: rolls %d, Space: %d, Score: %d\n", i % 2, i, posPlay1, scorePlay1);
        }
        else
        {
            posPlay2 = ((posPlay2 + move - 1) % 10) + 1;
            scorePlay2 += (posPlay2);
            printf("Player %d: rolls %d, Space: %d, Score: %d\n", i % 2, i, posPlay2, scorePlay2);
        }
        if (scorePlay1 >= 1000)
        {
            cout << (scorePlay2 * 3 * i) << endl;
            break;
        }
        if (scorePlay2 >= 1000)
        {
            cout << (scorePlay1 * 3 * i) << endl;
            break;
        }
    }
}