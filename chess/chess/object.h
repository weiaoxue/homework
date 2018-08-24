//
//  object.h
//  json
//
//  Created by 魏傲雪 on 2017/3/29.
//  Copyright © 2017年 魏傲雪. All rights reserved.
//

#ifndef object_h
#define object_h

#pragma once
#include <map>
#include <sstream>

class Value;
class Array;

class Object {
    std::map<std::string, Value> obj_map;
public:
    Object();
    
    Object(std::string s);
    
    Value & operator[] (const std::string & key);
    
    Object & operator= (const Object & obj);
    
    int size() const;
    
    std::string to_json();
    
    Object read_object(const std::string & str, int & p);
    
    Value read_value(const std::string & str, int & p);
    
    Array read_array(const std::string & str, int & p);
    
    std::string read_string(const std::string & str, int & p);
    
    bool read_bool(const std::string & str, int & p);
    
    Value read_number(const std::string & str, int & p);
    
    void read_char(const std::string & str, int & p, const char ch);
    
    std::map<std::string, Value>::iterator begin();
    
    std::map<std::string, Value>::iterator end();
    
    std::map<std::string, Value>::iterator find(std::string str);
    
    void insert(std::pair<std::string, Value> val);
    
    void erase(std::map<std::string, Value>::iterator pos);
    
    void clear();
    
    bool empty();
};

#endif /* object_h */
