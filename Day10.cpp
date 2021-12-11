#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

void tokenize(string &str, char delim, vector<vector<char>> &out)
{
    stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim))
    {
        int n = s.length();
        char c_a[n+1];
        strcpy(c_a,s.c_str());
        vector<char> temp;
        for(int i = 0; i < n; i++){
            temp.push_back(c_a[i]);
        }
        out.push_back(temp);
    }
}

int main(){
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);
    vector<vector<char>> input;
    for(string line; getline(input_file,line);){
        tokenize(line, ' ', input);
    }
    vector<vector<char>> inc;
    for(int i = 0; i < input.size(); i++){
        int ans = 0;
        stack<char> stack;
        for(int j = 0; j < input[i].size(); j++){          
            if(input[i][j] == '('){
                stack.push('(');
            }
            else if(input[i][j] == '['){
                stack.push('[');
            }
            else if(input[i][j] == '{'){
                stack.push('{');
            }
            else if(input[i][j] == '<'){
                stack.push('<');
            }
            else if(input[i][j] == ')'){
                char temp = stack.top();
                stack.pop();
                if(temp != '('){
                    ans += 3;
                    break;
                }
            }
            else if(input[i][j] == '}'){
                char temp = stack.top();
                stack.pop();
                if(temp != '{'){
                    ans += 1197;
                    break;
                }
            }
            else if(input[i][j] == ']'){
                char temp = stack.top();
                stack.pop();
                if(temp != '['){
                    ans += 57;
                    break;
                }
            }else if(input[i][j] == '>'){
                char temp = stack.top();
                stack.pop();
                if(temp != '<'){
                    ans += 25137;
                    break;
                }
            }

        }
        if(ans == 0){
            inc.push_back(input[i]);
        }
    }
    vector<long long> score;
    for(int i = 0; i < inc.size(); i++){
        stack<char> stack;
        for(int j = 0; j < inc[i].size(); j++){
            if(inc[i][j] == '('){
                stack.push('(');
            }
            else if(inc[i][j] == '['){
                stack.push('[');
            }
            else if(inc[i][j] == '{'){
                stack.push('{');
            }
            else if(inc[i][j] == '<'){
                stack.push('<');
            }
            else if(inc[i][j] == ')'){
                char temp = stack.top();
                stack.pop();
            }
            else if(inc[i][j] == '}'){
                char temp = stack.top();
                stack.pop();
            }
            else if(inc[i][j] == ']'){
                char temp = stack.top();
                stack.pop();
            }else if(inc[i][j] == '>'){
                char temp = stack.top();
                stack.pop();
            }
        }
        long long ans = 0;
        while(!stack.empty()){
            char temp = stack.top();
            stack.pop();
            if(temp == '('){
                ans *= 5;
                ans += 1;
            }
            else if(temp == '['){
                ans *= 5;
                ans += 2;
            }
            else if(temp == '{'){
                ans *= 5;
                ans += 3;
            }
            else if(temp == '<'){
                ans *= 5;
                ans += 4;
            }
        }
        score.push_back(ans);
    }
    sort(score.begin(),score.end());
    int n = score.size();
    cout << score[n/2] << endl;
}