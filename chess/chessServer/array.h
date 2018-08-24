//
//  array.h
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//

#ifndef array_h
#define array_h

#pragma once
#include <vector>

class Value;

class Array {
    std::vector<Value> v_vec;
public:
    Array();
    
    Value & operator[](int index);
    
    Array & operator= (const Array & obj);
    
    int size() const;
    
    void push_back(const Value & val);
    
    std::string to_json();
    
    std::vector<Value>::iterator begin();
    
    std::vector<Value>::iterator end();
    
    void clear();
    
    bool empty();
};

#endif /* array_h */
