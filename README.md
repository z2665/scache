# scache
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
用于查看函数执行耗时
```
     perf record ./a.out
     perf report
```