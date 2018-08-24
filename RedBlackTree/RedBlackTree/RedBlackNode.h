//
//  RedBlackNode.h
//  RedBlackTree
//
//  Created by 魏傲雪 on 2018/8/19.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#ifndef RedBlackNode_h
#define RedBlackNode_h

enum Color {
    RED, BLACK
};

class RedBlackNode {
    Color color;
    RedBlackNode *parent, *left, *right;
    int data;
    
public:
    RedBlackNode();
    int GetData();
    Color GetColor();
    RedBlackNode *GetParent();
    RedBlackNode *GetLeftChild();
    RedBlackNode *GetRightChild();
    void SetData(int d);
    void SetColor(Color c);
    void SetParent(RedBlackNode *p);
    void SetLeftChild(RedBlackNode *p);
    void SetRightChild(RedBlackNode *p);
};

#endif /* RedBlackNode_h */
