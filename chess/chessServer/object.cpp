//
//  object.cpp
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//

#include <iostream>
#include "value.h"
#include "object.h"

Object::Object(){}

Object::Object(std::string s) {
    int p = 0;
    *this = read_object(s, p);
}

Value & Object::operator[] (const std::string & key) {
    return obj_map[key];
}

Object & Object::operator= (const Object & obj) {
    obj_map = obj.obj_map;
    return *this;
}

int Object::size() const {
    return obj_map.size();
}

std::string Object::to_json() {
    std::string result = "";
    result += "{";
    for(auto it = obj_map.begin(); it != obj_map.end(); ++it) {
        if(it != obj_map.begin()) result += ",";
        result += "\"" + it->first + "\":" + it->second.to_json();
    }
    result += "}";
    return result;
}

Object Object::read_object(const std::string & str, int & p) {
    Object obj;
    read_char(str, p, '{');
    while (1) {
        std::string key = read_string(str, p);
        read_char(str, p, ':');
        Value val = read_value(str, p);
        obj[key] = val;
        if (str[p] == '}') {
            read_char(str, p, '}');
            break;
        }
        else {
            read_char(str, p, ',');
        }
    }
    return obj;
}

void Object::read_char(const std::string & str, int & p, const char ch) {
    p++;
}

std::string Object::read_string(const std::string & str, int & p) {
    read_char(str, p, '\"');
    std::string result = "";
    while(1) {
        if(str[p] == '\"') {
            read_char(str, p, '\"');
            break;
        } else {
            result += str[p];
            read_char(str, p, str[p]);
        }
    }
    return result;
}

Value Object::read_value(const std::string & str, int & p) {
    Value val;
    if (str[p] == '{') {
        val = read_object(str, p);
    }
    else if (str[p] == '\"') {
        val = read_string(str, p);
    }
    else if (str[p] == '[') {
        val = read_array(str, p);
    }
    else if (str[p] == 't' || str[p] == 'f') {
        val = read_bool(str, p);
    }
    else if (str[p] == '-' || isdigit(str[p])) {
        val = read_number(str, p);
    }
    else{
        val.set_type(NIL);
    }
    return val;
}

Array Object::read_array(const std::string & str, int & p) {
    Array ary = Array();
    Value val;
    val.set_type(NIL);
    read_char(str, p, '[');
    while(1) {
        if(str[p] == ']') {
            ary.push_back(val);
            read_char(str, p, ']');
            break;
        } else if (str[p] == ',') {
            ary.push_back(val);
            read_char(str, p, ',');
        } else {
            val = read_value(str, p);
        }
    }
    return ary;
}

bool Object::read_bool(const std::string &str, int & p) {
    std::string result = "";
    for(int i = 0; i < 4; i++) {
        result += str[p];
        read_char(str, p, str[p]);
    }
    if(result == "true") return true;
    else {
        result += str[p];
        read_char(str, p, str[p]);
        return false;
    }
}

Value Object::read_number(const std::string & str, int & p) {
    bool sign = true;
    std::string res1 = "";
    if(str[p] == '-') {
        sign = false;
        read_char(str, p, '-');
    }
    while(isdigit(str[p])) {
        res1 += str[p];
        read_char(str, p, str[p]);
    }
    int base1 = 1, ans1 = 0;
    for(int i = res1.length() - 1; i >= 0; --i) {
        ans1 += base1 * (res1[i] - '0');
        base1 *= 10;
    }
    //std::cout << "ans1 = " << ans1 << std::endl;
    if(str[p] == '.') {
        read_char(str, p, '.');
        float base = 0.1, ans2 = (float)ans1;
        while(isdigit(str[p])) {
            ans2 += base * (str[p] - '0');
            base *= 0.1;
            read_char(str, p, str[p]);
        }
        if(!sign) ans2 = -ans2;
        Value val(ans2);
        return val;
    } else {
        if(!sign) ans1 = -ans1;
        Value val(ans1);
        return val;
    }
}

std::map<std::string, Value>::iterator Object::begin() {
    return obj_map.begin();
}

std::map<std::string, Value>::iterator Object::end() {
    return obj_map.end();
}

std::map<std::string, Value>::iterator Object::find(std::string str) {
    return obj_map.find(str);
}

void Object::insert(std::pair<std::string, Value> val) {
    obj_map.insert(val);
}

void Object::erase(std::map<std::string, Value>::iterator pos) {
    obj_map.erase(pos);
}

void Object::clear() {
    obj_map.clear();
}

bool Object::empty() {
    return obj_map.empty();
}
