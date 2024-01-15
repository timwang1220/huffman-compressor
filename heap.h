#ifndef Heap_H
#define Heap_H
#include<queue>
#include<vector>


struct Node{
    int c;
    unsigned long long val;
    Node *left,*right;
    Node(const int &_c,const long long &_val):c(_c),val(_val),left(nullptr),right(nullptr){};
    Node(const int &_c,const long long &_val,Node *&_left,Node *&_right):c(_c),val(_val),left(_left),right(_right){};
  
};  

struct cmp{
    bool operator() (const Node *a,const Node *b) 
         {return a->val>b->val;}
};
typedef std::priority_queue<Node*,std::vector<Node*>,cmp> NodeHeap;


#endif