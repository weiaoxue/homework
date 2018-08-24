//
//  RedBlackNode.cpp
//  RedBlackTree
//
//  Created by 魏傲雪 on 2018/8/19.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#include <stdio.h>
#include "RedBlackNode.h"

RedBlackNode::RedBlackNode() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

int RedBlackNode::GetData() {
    return this->data;
}

Color RedBlackNode::GetColor() {
    return this->color;
}

RedBlackNode *RedBlackNode::GetParent() {
    return this->parent;
}

RedBlackNode *RedBlackNode::GetLeftChild() {
    return this->left;
}

RedBlackNode *RedBlackNode::GetRightChild() {
    return this->right;
}

void RedBlackNode::SetData(int d) {
    this->data = d;
}

void RedBlackNode::SetColor(Color c) {
    this->color = c;
}

void RedBlackNode::SetParent(RedBlackNode *p) {
    this->parent = p;
}

void RedBlackNode::SetLeftChild(RedBlackNode *p) {
    this->left = p;
}

void RedBlackNode::SetRightChild(RedBlackNode *p) {
    this->right = p;
}
