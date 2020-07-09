// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.
#include <vector>
#include <iostream>
int main()
{
    std::vector<int*> v;
    
    int* i1 = new int;
    int* i2 = new int;
    int* i3 = new int;
    int* i4 = new int;
    
    *i1 = 1;
    *i2 = 2;
    *i3 = 3;
    *i4 = 4;

    v.push_back(i1);
    v.push_back(i2);
    v.push_back(i3);
    v.push_back(i4);

    delete v.back();
    v.pop_back();

    std::cout << *v.back() << std::endl;
    return 0;
}

