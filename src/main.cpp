
#include <iostream>
#include<string>
#include<ctime>
#include"cache.h"


using namespace std;

// TDOO: emmmmm
int main(int argc, char const *argv[])
{    
    clock_t start,finish;
    cout<<"hello"<<endl;
    cout<<"world"<<endl;
    Scache::cache c(2000);
    start=clock();
    //简单的重复插入测试
    for (int i = 0; i != 100000;++i){
        c.set(string("hello"), string("world"));
    }     
    finish=clock();
    
    cout << "\n简单的重复插入运行时间为" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
    return 0;
}
