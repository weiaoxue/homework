//
//  RedBlackTree.h
//  RedBlackTree
//
//  Created by 魏傲雪 on 2018/8/19.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#ifndef RedBlackTree_h
#define RedBlackTree_h
#include "RedBlackNode.h"

class RedBlackTree {
    RedBlackNode *root;
    
public:
    RedBlackTree() {}
    RedBlackNode *GetRoot();
    bool RotateLeft(RedBlackNode *p);
    bool RotateRight(RedBlackNode *p);
    RedBlackNode *GetInOrderSuccessor(RedBlackNode *p);
    bool Insert(int d);
    void InsertFixUp(RedBlackNode *p);
    RedBlackNode *Find(int d);
    bool Delete(int d);
    void DeleteFixUp(RedBlackNode *p, RedBlackNode *pa);
    void InOrderTraverse(RedBlackNode *p);
};

#endif /* RedBlackTree_h */
