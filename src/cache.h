#pragma once
#include<string>

class item
{
    public:
        item(std::string key, std::string  value): _key(std::move(key)), _value(std::move(value)),next(nullptr) {
        }
        void SetNext(item *v){
            next = v;
        }
        item* Next(){
            return next;
        }
        std::string& Key(){
            return _key;
        }
        std::string Value(){
            return _value;
        }
    private:
    std::string _key;
    std::string _value;
    item *next;


};

class cache
{
private:
    //hash数组总容量
  int cap;
  item* hashmap[];
  
public:
    cache(int size=200):cap(size){
        hashmap = new item*[size];
    };
    ~cache(){
        
    };
};

