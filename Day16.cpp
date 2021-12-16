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
#include <bitset>
#include <numeric>
#include <functional>
using namespace std;
#define INF 0x3f3f3f3f
typedef tuple<int,int,int> triplet;
long long versionControl = 0;
int lengthOfInput = 5480;
const char* hex_char_to_bin(char c)
{
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
    return NULL;
}


bool read_input(vector<int> &input){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    for(string line;getline(input_file, line);){
        int n = line.length();
        char arr[n];
        strncpy(arr, line.c_str(),n);
        for(int i = 0; i < n; i++){
            int temp = stoi( hex_char_to_bin(arr[i]) );
            int last = temp % 10;
            temp /= 10;
            int bef = temp % 10;
            temp/= 10;
            int prev = temp % 10;
            temp /= 10;
            int msb = temp % 10;
            input.push_back(msb);
            input.push_back(prev);
            input.push_back(bef);
            input.push_back(last);
        }
        //assert(arr[n-1] == '8');
    }
    
    return false;
}
long long max(vector<long long> input){
    long ans = LLONG_MIN;
    for(long long x : input){
        ans = ans < x ? x : ans;
    }
    return ans;
}
long long min(vector<long long> input){
    long long ans = LLONG_MAX;
    for(long long x : input){
        ans = ans > x ? x : ans;
    }
    return ans;
}
long long add(vector<long long> input){
    long long ans = 0;
    for(long long x : input)
        ans += x;
    return ans;
}
long long mult(vector<long long> input){
    long long acc = 1;
    for(long long x : input){
        acc *= x;
    }
    return acc;
}

long long parse_array(vector<int> input,int &whereAmI){
    //gonna be relevant
    
    string v = std::string() + std::to_string(input[whereAmI]) 
             + std::to_string(input[whereAmI+1]) + std::to_string(input[whereAmI+2]);
    int version = stoi(v,0,2);
    versionControl += version;
    string t = std::string() + std::to_string(input[whereAmI+3]) 
    + std::to_string(input[whereAmI+4]) + std::to_string(input[whereAmI+5]);
    int type = stoi(t,0,2);
    // 6 pos advanced
    whereAmI += 6;
    if(type == 4){
        int i;
        string WholeNumber = "";
        do{
            vector<int>::const_iterator first = input.begin() + whereAmI;
            vector<int>::const_iterator last = input.begin()  + whereAmI +5;
            vector<int> currPacket(first, last);
            
            i = currPacket[0];
            string number = std::string() + std::to_string(currPacket[1]) + std::to_string(currPacket[2]) 
                            + std::to_string(currPacket[3]) + std::to_string(currPacket[4]);
            string temp = WholeNumber + number;
            WholeNumber = temp;                
            whereAmI += 5;  
        }while(i);
        return stoll(WholeNumber,0,2); //does work
    }
    else{
        vector<long long> output;
        int labelI = input[whereAmI];
        whereAmI++;
        if(labelI == 0) {
            char bytes[15];
            int length = 0;
            for(int i = whereAmI; i < whereAmI + 15; i++){
                int temp = input[i];
                bytes[i-whereAmI] = temp + '0';
            }
            for(int i = 0; i < 15; i++){
                length |= (bytes[i] - '0') << (15-i);
            }
            length /=2;
            whereAmI += 15;
            int hardlimit = whereAmI + length;
            assert(hardlimit <= lengthOfInput);           
            while(whereAmI < hardlimit && hardlimit - whereAmI > 10){               
                long long temp = parse_array(input,whereAmI);
                output.push_back(temp);
            }
        }
        else{
            char bytes[11];
            int length = 0;
            for(int i = whereAmI; i < whereAmI + 11; i++){
                int temp = input[i];
                bytes[i-whereAmI] = temp + '0';
            }
            for(int i = 0; i < 11; i++){
                length |= (bytes[i] - '0') << (11-i);
            }
            length /=2;
            whereAmI+= 11;
            int numSubPack = length;
            for(int i = 0; i < numSubPack; i++){
                long long temp = parse_array(input,whereAmI);
                output.push_back(temp);
            }
        }
        switch(type){
            case 0:
                return add(output);
            case 1:
                return mult(output);
            case 2:
                return min(output);
            case 3:
                return max(output);
            case 5:
                assert(output.size() == 2);
                return output[0] > output[1] ? 1 : 0;
            case 6:
                assert(output.size() == 2);
                return output[0] < output[1] ? 1 : 0;    
            case 7:
                assert(output.size() == 2);
                return output[0] == output[1] ? 1 : 0;
        }
        cout << "Fishy" << endl;
    }
}

int main(){
    vector<int> input;
    read_input(input);
    int size = input.size();
    int num = 0;
    long long num2 = parse_array(input,num);
    cout << num2 << endl;
}
