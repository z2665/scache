#pragma once
#include<string>
#include<iostream>
namespace Scache{


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
        std::string Key(){
            return _key;
        }
        std::string Value(){
            return _value;
        }
        void SetValue(std::string value){
            _value = std::move(value);
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
  long long cap;
  int depth;
  item** _hashmap;
  
public:
    cache(int size=200,int dep=6):cap(size),depth(dep){
        _hashmap = new item*[size];
    };
    ~cache(){
       
    };
    //hash函数，后续更换为实现更优秀版本
    long long hash(std::string& key){
        long long  tmp=0;
        int count = 0;
        for (auto& ch : key){
          if(count%2==0){
              tmp += (tmp << 5) + ch;
          }
        }
        return tmp%cap;
    }
    //放大hashmap大小并重新hash
    item** rehash(){
        std::cout << "rehashing" <<std::endl;
        long long oldcap = cap;
        cap *= 2;
        std::cout << "new cap is " <<cap<< std::endl;
        item** newmap = new item *[cap];
        for (int i = 0; i != oldcap;++i){
            item *oldone = _hashmap[i];
            //如果当前位置不为空，则遍历链表并重新hash所有的项
            while(oldone!=nullptr){
                _set(newmap,oldone->Key(), oldone->Value(),true);
                oldone = oldone->Next();
            }
        }
        delete[] _hashmap;
        _hashmap = newmap;
        return _hashmap;
    }
    void set(std::string key, std::string value){
        _set(_hashmap, std::move(key), std::move(value),false);
    }
    void _set(item** hashmap,std::string key, std::string value,bool ishasing){
        int p=hash(key);
        item * tmp=new item(key,value);
        //如果这个位置没有被占用，则直接插入
        rehashpoint:
        if (hashmap[p]==nullptr){
            hashmap[p]=tmp;
           return; 
        }
        //否则进入冲突处理逻辑
        item* next=hashmap[p];
        int len = 0;
        while (true){
            //比较key是否一致,如果一致则修改value
            if(next->Key()==key){
                next->SetValue(value);
                return;
            }
            //如果链尾不为空，则插入
            if (next->Next()==nullptr ){
                next->SetNext(tmp);
                return;
            }
            next = next->Next();
            len++;
            if (len>=depth && !ishasing){
                //如果链表深度大于限制
                hashmap= rehash();
                len = 0;
                goto rehashpoint;
            }
        }
    }
};

}

