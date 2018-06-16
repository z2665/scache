
#include <iostream>
#include<string>
#include"cache.h"

using namespace std;

// TDOO: emmmmm
int main(int argc, char const *argv[])
{   
    cout<<"hello"<<endl;
    cout<<"world"<<endl;
    Scache::cache c(2000);
    c.set(string("hello"), string("world"));
    return 0;
}
