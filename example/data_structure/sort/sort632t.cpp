//---------------------------------------------------------------------------

#pragma hdrstop
#include <stdlib>
#include <stdio>
#include <conio>
#include <iostream>
#include <math>
using namespace std;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[]){
    int *tmp1,*tmp2;
    int m,group,po;
    int *array,*compare[65536];
    bool flag=true;

    //輸入比較元素
    cout<<"請輸入排序元素之數目:";
    cin>>m;

    //floor 無條件捨去
    //ceil 無條件進入
    group=ceil(sqrt(m));

    array=(int *)malloc(sizeof(int)*group*group);
    cout<<"請輸入排序元素:"<<endl;
    for (int i=0; i<(group*group); i++){
        if (i<m){
            cout<<"NO."<<i<<':';
            cin>>*(array+i);
        } else {
            *(array+i)=-65536;
        }//end if 4
    }//end for
    cout<<endl;

    po=0;
    do{
        for (int i=0; i<group; i++){
            tmp1=NULL;
            for (int j=0; j<group; j++){
                tmp2=(array+(i*group)+j);
                if (((tmp1 == NULL) || (*tmp1<*tmp2))){
                    tmp1=tmp2;
                }//end if
            }//end for
            compare[i]=tmp1;
        }//end for

        int *tmp;
        tmp=compare[0];
        for (int i=0; i<group; i++){
            if ((*tmp) < (*compare[i]))
                tmp=compare[i];
            if ((*tmp) == -65536){
                continue;
            }
        }//end for

        if (*tmp != -65536){
            cout<<"("<<po++<<")"<<*tmp<<"   ";
        } else {
            flag=false;
        };
        *tmp=-65536;
    } while (flag == true);
    getch();
    return 0;
}
//---------------------------------------------------------------------------
