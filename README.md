# scache
[![Build Status](https://travis-ci.org/z2665/scache.svg?branch=master)](https://travis-ci.org/z2665/scache)
[![CodeFactor](https://www.codefactor.io/repository/github/z2665/scache/badge)](https://www.codefactor.io/repository/github/z2665/scache)  


A simple cache for study


## 编译方式
* 需要支持c++ 17的编译器，虽然并没有用到相应特性噗（比如GCC 7.3，clang 6）
* Cmake 2.8以上版本
* 目前并不需要其他额外库

输入如下命令编译
```
    mkdir build
    cd build
    cmake ../
    make
```
之后build目录下会生成目标文件a.out

## 有用的一些命令
* 用于查看函数执行耗时
```
     perf record ./a.out
     perf report
```
* 检查检查内存泄漏
```
    valgrind --leak-check=yes ./a.out
output like:
    ==29549== HEAP SUMMARY:
    ==29549==     in use at exit: 0 bytes in 0 blocks
    ==29549==   total heap usage: 100,009 allocs, 100,009 frees, 9,305,272 bytes allocated
    ==29549== 
    ==29549== All heap blocks were freed -- no leaks are possible
    ==29549== 
    ==29549== For counts of detected and suppressed errors, rerun with: -v
    ==29549== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
## 开发建议
* 建议使用clang-format来格式化代码
* 建议安装valgrind用于内存泄漏检查