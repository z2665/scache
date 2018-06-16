#pragma once
#include<string>
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
  int depth;
  bool ishasing;
  item** hashmap;
  
public:
    cache(int size=200,int dep=6):cap(size),depth(dep),ishasing(false){
        hashmap = new item*[size];
    };
    ~cache(){
        
    };
    //hash函数，后续更换为实现更优秀版本
    int hash(std::string& key){
        int tmp=0;
        for (auto& ch : key){
            tmp += ch&0xf00000;
        }
        return tmp%cap;
    }
    //放大hashmap大小并重新hash
    void rehash(){
        int oldcap = cap;
        cap *= 2;
        item** newmap = new item *[cap];
        for (int i = 0; i != oldcap;++i){
            item *oldone = hashmap[i];
            //如果当前位置不为空，则遍历链表并重新hash所有的项
            while(oldone!=nullptr){
                set(oldone->Key(), oldone->Value());
                oldone = oldone->Next();
            }
        }
        ishasing = false;
        delete[] hashmap;
        hashmap = newmap;
    }
    void set(std::string key, std::string value){
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
            //如果链尾不为空，则插入
            if (next->Next()==nullptr ){
                next->SetNext(tmp);
                return;
            }
            next = next->Next();
            len++;
            if (len>=depth && !ishasing){
                //如果链表深度大于限制
                ishasing = true;
                rehash();
                len = 0;
                goto rehashpoint;
            }
        }
    }
};

}

