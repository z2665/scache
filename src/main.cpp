
#include "cache.h"
#include <ctime>
#include <iostream>
#include <random>
#include <string>

using namespace std;

// TDOO: emmmmm
int main(int argc, char const *argv[])
{
    int a = 0;
    cin >> a;
    clock_t start, finish;
    random_device rd;
    cout << "hello" << endl;
    cout << "world" << endl;
    Scache::cache c(2000);
    string hellostring = string("hello");
    string worldstring = string("world");
    if (a == 0)
    {
        start = clock();
        //简单的重复插入测试
        for (int i = 0; i != 100000; ++i)
        {
            c.set(hellostring, worldstring);
        }
        finish = clock();
        cout << "\n简单的重复插入运行时间为" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
    }
    else if (a == 1)
    {
        start = clock();
        for (int i = 0; i != 100000; ++i)
        {

            c.set(move(to_string(rd())), worldstring);
        }
        finish = clock();
        cout << "\n随机插入运行时间为" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
    }

    return 0;
}
