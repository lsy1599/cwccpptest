//---------------------------------------------------------------------------
#include <map>
#include <iostream>
#pragma hdrstop
// ref: http://www.codeproject.com/cpp/FastDelegate.asp
//---------------------------------------------------------------------------
class A;
typedef int (A::*CAL_FUNCTOR)(int, int);
typedef std::map<int, CAL_FUNCTOR> M_TBL;
class A{
public:
    A(){
        _tbl[0] = &A::add;
        _tbl[1] = &A::sub;
        _tbl[2] = &A::div;
    }

    int DoIt(int method, int a, int b){
//        CAL_FUNCTOR f =_tbl[method];
        return (this->*(_tbl[method]))(a, b);
    }
private:
    int add(int a, int b){
        return a+b;
    }
    int sub(int a, int b){
        return a-b;
    }
    int div(int a, int b){
        return a/b;
    }

    M_TBL _tbl;
//    CAL_FUNCTOR f;
};
#pragma argsused
int main(int argc, char* argv[])
{
    A pa;
    for(int i = 0; i<3; ++i){
        std::cout << pa.DoIt(i, 10, 2) << std::endl;
    }
    return 0;
}
//---------------------------------------------------------------------------
 