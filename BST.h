#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h> 
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
using namespace std;

bool checkNumber(char a){
    switch(a){
        case '0' : return true;
        case '1' : return true;
        case '2' : return true;
        case '3' : return true;
        case '4' : return true;
        case '5' : return true;
        case '6' : return true;
        case '7' : return true;
        case '8' : return true;
        case '9' : return true;
    }
    return false;
}

struct nodePair {
    long long value;
    long long  depth;
    struct nodePair * parent;
    struct nodePair * left;
    struct nodePair * right;
};

class BST{
    nodePair root;
    vector<nodePair*> inOrd;
    public:
        BST(nodePair root);
        void fillBst(string s);
        void addBst(string s);
        bool action();
        long long mag();
    private:
        void dfs(nodePair * curr,long long  height);
        bool bomb(nodePair * curr);
        nodePair* findBomb(nodePair * curr);
        nodePair* fillnew(string s);
        bool split();
        void inorder(nodePair * curr);
        long long magRec(nodePair * curr);
        
};
void printBST(nodePair * root){
    if(root == NULL)
        return;
    if(root->value != -1){
        cout << root->value;
        return;
    }
    cout << "[";
    printBST(root->left);
    cout << ",";
    printBST(root->right);
    cout << "]";
}

long long BST::magRec(nodePair * curr){
    if(curr->value != -1)
        return curr->value;
    return ((3 * BST::magRec(curr->left)) + (2 * BST::magRec(curr->right)));  
}

long long BST::mag(){
    printBST(&this->root);
    cout<<endl;
    return BST::magRec(&this->root);
}


nodePair * findSplit(nodePair * curr){
    if(curr == NULL){
        return NULL;
    }
    if(curr->value >= 10){
        return curr; //we hit leaf!
    }
    nodePair* left = findSplit(curr->left);
    nodePair* right = findSplit(curr->right);
    if(left != NULL)
        return left;
    return right;
}
bool BST::split(){
    nodePair * splitter = findSplit(&this->root);
    if(splitter == NULL)
        return false;
    long long currVal = splitter->value;
    long long  rightVal = currVal % 2 == 1 ? (currVal+1)/2 : currVal/2;
    long long  leftVal = currVal/2;
    nodePair * left = (struct nodePair *)calloc(1,sizeof (struct nodePair));
    nodePair * right = (struct nodePair *)calloc(1,sizeof (struct nodePair));
    left->value = leftVal;
    right->value = rightVal;
    long long  height = splitter->depth +1;
    left->depth = height;
    right->depth = height;
    left->parent = splitter;
    right->parent = splitter;

    splitter->value = -1;
    splitter->left = left;
    splitter->right = right;
    splitter->depth++;
    return true;
}

bool BST::action(){
    while(BST::bomb(&this->root) || BST::split());
    return false;
}

nodePair* BST::findBomb(nodePair * curr){
    if(curr == NULL)
        return NULL;
    if(curr->value != -1){
        return NULL; //we hit leaf!
    }
    if(curr->depth >= 4){
        return curr; // we hit pair with depth 4
    }
    nodePair* left = BST::findBomb(curr->left);
    nodePair* right = BST::findBomb(curr->right);
    if(left != NULL)
        return left;
    return right;
}

void BST::inorder(nodePair * curr){
    if(curr == NULL)
        return;
    inorder(curr->left);
    inOrd.push_back(curr);
    inorder(curr->right);
}


nodePair* Sdfs(nodePair * curr){
    if(curr == NULL)
        return NULL;
    if(curr->value != -1)
        return curr;
    nodePair * leftest = Sdfs(curr->left);
    if(leftest != NULL)
        return leftest;
    return Sdfs(curr->right);
}

bool BST::bomb(nodePair * curr){
    curr = &this->root;
    nodePair* temp = BST::findBomb(curr);
    if(temp == NULL)
        return false;
    inOrd.clear();
    inorder(&this->root);
    long long  pos = -1;
    for(long long  i = 0; i<  inOrd.size(); i++){
        if(inOrd[i] == temp){
            pos = i;
            break;
        }
    }
    long long  lPos = pos-1;
    long long  rPos = pos+1;
    nodePair* left = NULL;
    nodePair* right = NULL;;
    for(long long  i = lPos-1; i >= 0; i--){
        if(inOrd[i]->value != -1){
            left = inOrd[i];
            break;
        }
    }
    for(long long  i = rPos+1; i< inOrd.size(); i++){
        if(inOrd[i]->value != -1){
            right = inOrd[i];
            break;
        }
    }
    if(left != NULL && right != NULL){ // FIX THIS
        right->value += temp->right->value;
        left->value += temp->left->value;
    }
    else if(right != NULL){
        right->value += temp->right->value;
    }
    else if(left != NULL){
        left->value += temp->left->value;
    }
    else{
        cout << "INSANITY" << endl;
    } 
    temp->value = 0;
    temp->left =NULL;
    temp->right = NULL;   
}

BST::BST(nodePair root){
    this->root = root;
}

void BST::addBst(string s){
    struct nodePair * newMiddleNode = (struct nodePair *)calloc(1,sizeof (struct nodePair));
    nodePair * rootToAdd = BST::fillnew(s);
    newMiddleNode->left = this->root.left;
    newMiddleNode->right = this->root.right;    
    newMiddleNode->parent = &this->root;
    newMiddleNode->value = -1;
    this->root.right->parent = newMiddleNode;
    this->root.left->parent = newMiddleNode;
    this->root.left = newMiddleNode;
    this->root.right = rootToAdd;
    rootToAdd->parent = &this->root;
    //printBST(&this->root);
    //cout << endl;
    //cout << endl;
    dfs(&this->root, 0);
    BST::action();
    //printBST(&this->root);
    //cout << endl;
}

void BST::dfs(nodePair * curr, long long  height){
    if(curr == NULL){
        return;
    }
    if(curr->value != -1){
        long long  h = curr->parent->depth;
        curr->depth = h;
        return;
    }
    curr->depth = height;
    height++;
    dfs(curr->left,height);
    dfs(curr->right,height);

}

nodePair * BST::fillnew(string s){
    long long  n = s.length();
    char arr[n+1];
    strcpy(arr,s.c_str());
    nodePair * curr = (struct nodePair *)calloc(1,sizeof (struct nodePair));
    for(int i = 0; i < n; i++){
        if(arr[i] == '['){
            curr->value = -1;
            if(curr->left != NULL){
                curr->left->parent = curr;
                curr = curr->left;
            }
            else{
                curr->left = (struct nodePair *)calloc(1,sizeof (struct nodePair));
                curr->left->parent = curr;
                curr = curr->left;
            }
        }
        else if(arr[i] == ','){
            curr->value = -1;
            if(curr->right !=NULL ){
                curr->right->parent = curr;
                curr = curr->right;
            }
            else{
                curr->right = (struct nodePair *)calloc(1,sizeof(struct nodePair));
                curr->right->parent = curr;
                curr = curr->right;
            }
        }
        else if(checkNumber(arr[i])){
            curr->value = arr[i] - '0';
            curr = curr->parent;
        }
        else if(arr[i] == ']' && i < n-1){
            curr = curr->parent;
        }
        else if(arr[i] == ']' && i == n-1)
            break;
        else{
            cout << "Insanity Check" << endl;
        }
    }
    BST::dfs(curr,0);

    BST::action();
    return curr;
}

void BST::fillBst(string s){
    int n = s.length();
    char arr[n+1];
    strcpy(arr,s.c_str());
    nodePair * curr = &this->root;
    for(int i = 0; i < n; i++){
        if(arr[i] == '['){
            curr->value = -1;
            if(curr->left != NULL){
                curr->left->parent = curr;
                curr = curr->left;
            }
            else{
                curr->left = (struct nodePair *)calloc(1,sizeof (struct nodePair));
                curr->left->parent = curr;
                curr = curr->left;
            }
        }
        else if(arr[i] == ','){
            curr->value = -1;
            if(curr->right !=NULL ){
                curr->right->parent = curr;
                curr = curr->right;
            }
            else{
                curr->right = (struct nodePair *)calloc(1,sizeof(struct nodePair));
                curr->right->parent = curr;
                curr = curr->right;
            }
        }
        else if(checkNumber(arr[i])){
            curr->value = arr[i] - '0';
            curr = curr->parent;
        }
        else if(arr[i] == ']'){
            curr = curr->parent;
        }
        else{
            cout << "Insanity Check" << endl;
        }
    }
    dfs(&root,0);

    BST::action();
    //TODO it is not correct the bomb method, because the pair is broken
    // its something like [9,[3]] or [[9],3]
}
