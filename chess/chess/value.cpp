//
//  value.cpp
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//
#include <iostream>
#include "value.h"

Value::Value(){}
Value::Value(std::string v) : v_string(v), type(STRING) {}
Value::Value(float v) : v_float(v), type(FLOAT) {}
Value::Value(int v) : v_int(v), type(INT) {}
Value::Value(bool v) : v_bool(v), type(BOOL) {}
Value::Value(Object v) : v_object(v), type(OBJECT) {}
Value::Value(Array v) : v_array(v), type(ARRAY) {}

std::string & Value::to_string() {
    return v_string;
}
float & Value::to_float() {
    return v_float;
}
int & Value::to_int() {
    return v_int;
}
bool & Value::to_bool() {
    return v_bool;
}
Object & Value::to_object() {
    return v_object;
}
Array & Value::to_array() {
    return v_array;
}

Value & Value::operator=(const std::string & val) {
    v_string = val;
    type = STRING;
    return *this;
}
Value & Value::operator=(const float & val) {
    v_float = val;
    type = FLOAT;
    return *this;
}
Value & Value::operator=(const int & val) {
    v_int = val;
    type = INT;
    return *this;
}
Value & Value::operator=(const bool & val) {
    v_bool = val;
    type = BOOL;
    return *this;
}
Value & Value::operator=(const Object & val) {
    v_object = val;
    type = OBJECT;
    return *this;
}
Value & Value::operator=(const Array & val) {
    v_array = val;
    type = ARRAY;
    return *this;
}

std::string Value::to_json() {
    std::string result = "";
    std::ostringstream ostr;
    switch (type) {
        case INT: {
            ostr << to_int();
            result = ostr.str();
            break;
        }
        case FLOAT: {
            ostr << to_float();
            result = ostr.str();
            break;
        }
        case BOOL: {
            result = to_bool()?"true":"false";
            break;
        }
        case STRING: {
            result = "\"" + to_string() + "\"";
            break;
        }
        case OBJECT: {
            result = to_object().to_json();
            break;
        }
        case ARRAY: {
            result = to_array().to_json();
            break;
        }
        case NIL:break;
    }
    return result;
}

ValueType Value::get_type() {
    return type;
}

void Value::set_type(ValueType t) {
    type = t;
}

void Value::push_back(Value val) {
    v_array.push_back(val);
}

Value & Value::operator[] (const int &key) {
    return v_array[key];
}

Value & Value::operator[] (const std::string & key) {
    return v_object[key];
}
