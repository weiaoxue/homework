//
//  RedBlackTree.cpp
//  RedBlackTree
//
//  Created by 魏傲雪 on 2018/8/19.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#include <stdio.h>
#include "RedBlackTree.h"

RedBlackNode *RedBlackTree::GetRoot() {
    return this->root;
}

bool RedBlackTree::RotateLeft(RedBlackNode *p) {
    if (p == nullptr) return false;
    RedBlackNode *rc = p->GetRightChild();
    if (rc == nullptr) return false;
    
    //process p and the left child of rc
    p->SetRightChild(rc->GetLeftChild());
    if (rc->GetLeftChild() != nullptr)
        rc->GetLeftChild()->SetParent(p);
    
    //process rc and the parent of p
    rc->SetParent(p->GetParent());
    if (p->GetParent() == nullptr)
        root = rc;
    else if (p == p->GetParent()->GetLeftChild())
        p->GetParent()->SetLeftChild(rc);
    else
        p->GetParent()->SetRightChild(rc);
    
    //process p and rc
    rc->SetLeftChild(p);
    p->SetParent(rc);
    return true;
}

bool RedBlackTree::RotateRight(RedBlackNode *p) {
    if (p == nullptr) return false;
    RedBlackNode *lc = p->GetLeftChild();
    if (lc == nullptr) return false;
    
    //process p and the right child of lc
    p->SetLeftChild(lc->GetRightChild());
    if (lc->GetRightChild() != nullptr)
        lc->GetRightChild()->SetParent(p);
    
    //process rc and the parent of p
    lc->SetParent(p->GetParent());
    if (p->GetParent() == nullptr)
        root = lc;
    else if (p == p->GetParent()->GetLeftChild())
        p->GetParent()->SetLeftChild(lc);
    else
        p->GetParent()->SetRightChild(lc);
    
    //process p and rc
    lc->SetRightChild(p);
    p->SetParent(lc);
    return true;
}

bool RedBlackTree::Insert(int d) {
    RedBlackNode *r = this->root, *s = nullptr;
    while (r != nullptr) {
        s = r;
        if (r->GetData() > d)
            r = r->GetLeftChild();
        else if (r->GetData() < d)
            r = r->GetRightChild();
        else
            return false;
    }
    RedBlackNode *p = new RedBlackNode();
    p->SetParent(s);
    p->SetData(d);
    p->SetColor(RED);
    if (s == nullptr)
        this->root = p;
    else if (s->GetData() > d)
        s->SetLeftChild(p);
    else
        s->SetRightChild(p);
    InsertFixUp(p);
    return true;
}

void RedBlackTree::InsertFixUp(RedBlackNode *p) {
    RedBlackNode *pa, *gpa, *uc;
    while (true) {
        pa = p->GetParent();
        if (pa == nullptr) break;
        if (pa->GetColor() == BLACK) break;
        gpa = pa->GetParent();
        if (gpa->GetLeftChild() == pa) {
            uc = gpa->GetRightChild();
            if (uc == nullptr || uc->GetColor() == BLACK) {
                if (p == pa->GetRightChild()) {
                    p = pa;
                    RotateLeft(p);
                }
                pa = p->GetParent();
                pa->SetColor(BLACK);
                gpa = pa->GetParent();
                gpa->SetColor(RED);
                RotateRight(gpa);
            } else {
                pa->SetColor(BLACK);
                uc->SetColor(BLACK);
                gpa->SetColor(RED);
                p = gpa;
            }
        } else {
            uc = gpa->GetLeftChild();
            if (uc == nullptr || uc->GetColor() == BLACK) {
                if (p == pa->GetLeftChild()) {
                    p = pa;
                    RotateRight(p);
                }
                pa = p->GetParent();
                pa->SetColor(BLACK);
                gpa = pa->GetParent();
                gpa->SetColor(RED);
                RotateLeft(gpa);
            } else {
                pa->SetColor(BLACK);
                uc->SetColor(BLACK);
                gpa->SetColor(RED);
                p = gpa;
            }
        }
    }
    this->root->SetColor(BLACK);
}

RedBlackNode *RedBlackTree::Find(int d) {
    RedBlackNode *p = this->root;
    while (p) {
        if (p->GetData() == d)
            return p;
        else if (p->GetData() > d)
            p = p->GetLeftChild();
        else
            p = p->GetRightChild();
    }
    return p;
}

bool RedBlackTree::Delete(int d) {
    RedBlackNode *p = Find(d), *dd, *ddc;
    if (p == nullptr) return false;
    
    //dd is the node to be deleted
    //ddc is the node to replace dd
    if (p->GetLeftChild() == nullptr) {
        dd = p;
        ddc = p->GetRightChild();
    } else if (p->GetRightChild() == nullptr) {
        dd = p;
        ddc = p->GetLeftChild();
    } else {
        dd = GetInOrderSuccessor(p);
        p->SetData(dd->GetData());
        ddc = dd->GetRightChild();
    }
    
    if (dd->GetParent() == nullptr) {
        this->root = ddc;
        if (ddc == nullptr) {
            delete dd;
            return true;
        }
        else ddc->SetParent(dd->GetParent());
    }
    else {
        if (dd == dd->GetParent()->GetLeftChild())
            dd->GetParent()->SetLeftChild(ddc);
        else
            dd->GetParent()->SetRightChild(ddc);
        if (ddc != nullptr)
            ddc->SetParent(dd->GetParent());
    }
    if (dd->GetColor() == BLACK)
        DeleteFixUp(ddc, dd->GetParent());
    delete dd;
    return true;
}

void RedBlackTree::DeleteFixUp(RedBlackNode *p, RedBlackNode *pa) {
    RedBlackNode *bro, *brolc, *brorc;
    while (p != this->root && (p == nullptr || p->GetColor() == BLACK)) {
        if (p == pa->GetLeftChild()) {
            bro = pa->GetRightChild();
            //dd is black, so bro(the brother of dd) cannot be null
            //if bro is red, the new bro(the left child of the old bro) cannot be null
            if (bro->GetColor() == RED) {
                bro->SetColor(BLACK);
                pa->SetColor(RED);
                RotateLeft(pa);
                bro = pa->GetRightChild();
            }
            brolc = bro->GetLeftChild();
            brorc = bro->GetRightChild();
            if ((brolc == nullptr || brolc->GetColor() == BLACK) && (brorc == nullptr || brorc->GetColor() == BLACK)) {
                bro->SetColor(RED);
                p = pa;
                //p is not root, so pa is not null
                pa = p->GetParent();
            } else {
                if (brorc == nullptr || brorc->GetColor() == BLACK) {
                    //now brolc is not null and is red
                    brolc->SetColor(BLACK);
                    bro->SetColor(RED);
                    RotateRight(bro);
                    bro = pa->GetRightChild();
                }
                bro->SetColor(pa->GetColor());
                pa->SetColor(BLACK);
                brorc = bro->GetRightChild();
                brorc->SetColor(BLACK);
                RotateLeft(pa);
                p = this->root;
            }
        } else {
            bro = pa->GetLeftChild();
            if (bro->GetColor() == RED) {
                bro->SetColor(BLACK);
                pa->SetColor(RED);
                RotateRight(pa);
                bro = pa->GetLeftChild();
            }
            brolc = bro->GetLeftChild();
            brorc = bro->GetRightChild();
            if ((brolc == nullptr || brolc->GetColor() == BLACK) && (brorc == nullptr || brorc->GetColor() == BLACK)) {
                bro->SetColor(RED);
                p = pa;
                //p is not root, so pa is not null
                pa = p->GetParent();
            } else {
                if (brolc == nullptr || brolc->GetColor() == BLACK) {
                    //now brorc is not null and is red
                    brorc->SetColor(BLACK);
                    bro->SetColor(RED);
                    RotateLeft(bro);
                    bro = pa->GetLeftChild();
                }
                bro->SetColor(pa->GetColor());
                pa->SetColor(BLACK);
                brolc = bro->GetLeftChild();
                brolc->SetColor(BLACK);
                RotateRight(pa);
                p = this->root;
            }
        }
    }
    if (p != nullptr)
        p->SetColor(BLACK);
}

RedBlackNode *RedBlackTree::GetInOrderSuccessor(RedBlackNode *p) {
    RedBlackNode *q = p->GetRightChild();
    while (q->GetLeftChild())
        q = q->GetLeftChild();
    return q;
}

void RedBlackTree::InOrderTraverse(RedBlackNode *p) {
    if (p == nullptr) return;
    InOrderTraverse(p->GetLeftChild());
    printf("(%d %d) ", p->GetData(), p->GetColor());
    InOrderTraverse(p->GetRightChild());
}
