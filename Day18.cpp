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
#include "Graph.h"
#include "BST.h"
using namespace std;
#define INF 0x3f3f3f3f
typedef tuple<int,int,int> triplet;



bool read_input(vector<string> &input){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    for(string line;getline(input_file, line);){
        input.push_back(line);
    }
    return false;
}

int main(){
    
    vector<string> input;
    read_input(input);
    int max = -100;
    int n = input.size();
    for(int i = 0; i < input.size(); i++){
        for(int j = i+1; j < input.size(); j++){
            for(int k = 0; k < 2; k++){
                if(k == 0){
                    struct nodePair * start = (struct nodePair *)calloc(1,sizeof (struct nodePair));;
                    BST Orig(*start);
                    Orig.fillBst(input[i]);
                    Orig.addBst(input[j]);
                    int temp = Orig.mag();
                    if(temp >= max)
                        max = temp;
                }

            }

                

        }
    }

    cout << max << endl;
}
