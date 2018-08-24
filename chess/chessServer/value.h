//
//  value.h
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//

#ifndef value_h
#define value_h

#pragma once
#include <sstream>
#include "object.h"
#include "array.h"

enum ValueType {INT, FLOAT, BOOL, STRING, OBJECT, ARRAY, NIL};

class Value {
    std::string v_string;
    float v_float;
    int v_int;
    bool v_bool;
    Object v_object;
    Array v_array;
    ValueType type;
public:
    Value();
    Value(std::string v);
    Value(float v);
    Value(int v);
    Value(bool v);
    Value(Object v);
    Value(Array v);
    
    std::string & to_string();
    float & to_float();
    int & to_int();
    bool & to_bool();
    Object & to_object();
    Array & to_array();
    
    Value & operator=(const std::string & val);
    Value & operator=(const float & val);
    Value & operator=(const int & val);
    Value & operator=(const bool & val);
    Value & operator=(const Object & val);
    Value & operator=(const Array & val);
    
    std::string to_json();
    
    ValueType get_type();
    
    void set_type(ValueType t);
    
    void push_back(Value val);
    
    Value & operator[] (const int & key);
    
    Value & operator[] (const std::string & key);
};

#endif /* value_h */
