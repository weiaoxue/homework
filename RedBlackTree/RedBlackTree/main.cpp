//
//  main.cpp
//  RedBlackTree
//
//  Created by 魏傲雪 on 2018/8/19.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#include <iostream>
#include "RedBlackTree.h"
using namespace std;

class Node {
public:
    Node *p, *q;
    int data;

    Node(){
        p = nullptr;
        q = nullptr;
    }
};

class A {
public:
    Node *r;

    A() {
        //r = new Node();
    }
    
    void op1() {
        Node *w = new Node();
        
        this->r = w;
        w->data = 1;
        //op2(w);
    }
    
    void op2(Node *w) {
        w->data = 2;
    }
};

int main(int argc, const char * argv[]) {
//    A *a = new A();
//    //Node *mynull = new Node();
//    a->op1();
//    std::cout << a->r->data << std::endl;
    RedBlackTree *tree = new RedBlackTree();
    int a[20];
    for (int i = 0; i < 20; ++i) {
        cin >> a[i];
        tree->Insert(a[i]);
        cout << "after insert " << a[i] << endl;
        tree->InOrderTraverse(tree->GetRoot());
        cout << endl;
    }
    for (int i = 0; i < 20; ++i) {
        tree->Delete(a[i]);
        cout << "after delete " << a[i] << endl;
        tree->InOrderTraverse(tree->GetRoot());
        cout << endl;
    }
    return 0;
}
