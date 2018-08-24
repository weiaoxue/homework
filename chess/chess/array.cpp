//
//  array.cpp
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//

#include "value.h"
#include "array.h"

Array::Array(){}

Value & Array::operator[](int index) {
    return v_vec[index];
}

Array & Array::operator= (const Array & ary) {
    v_vec = ary.v_vec;
    return *this;
}

int Array::size() const {
    return v_vec.size();
}

void Array::push_back(const Value & val) {
    v_vec.push_back(val);
}

std::string Array::to_json() {
    std::string result = "";
    result += "[";
    for(int i = 0; i < v_vec.size(); ++i) {
        if(i == 0) result += v_vec[i].to_json();
        else result += "," + v_vec[i].to_json();
    }
    result += "]";
    return result;
}

std::vector<Value>::iterator Array::begin() {
    return v_vec.begin();
}

std::vector<Value>::iterator Array::end() {
    return v_vec.end();
}

void Array::clear() {
    v_vec.clear();
}

bool Array::empty() {
    return v_vec.empty();
}
