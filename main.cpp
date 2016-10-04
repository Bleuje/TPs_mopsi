#include <iostream>
#include "Matrice.h"

using namespace std;
using namespace tpmatrice;

int main(){

    tpmatrice::SHALLOW_COPY = true;

    Matrice<double> m = Matrice<double>(3,3);
    m.setRandomValues();

    Matrice<double> identity = Matrice<double>(3,3);

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            identity(i,j) = (i==j);
        }
    }

    Matrice<double> m3 = ((m+m)*m - (m+m)*m + m)*identity;

    m3.print();
    m3(0,0) = 5;
    cout<<m3;

    Matrice<double> m2 = m.copy();

    cout<<"m has "<<m.shallowCopies()<<" copies."<<endl;

    Matrice<double> m4;
    m4 = m2;

    cout<<"m has "<<m.shallowCopies()<<" copies."<<endl;

    Matrice<double> m5;
    m5 = m4;
    m5 = m4;
    m5 = m4;

    cout<<"m has "<<m.shallowCopies()<<" copies."<<endl;

    for(int i=0;i<5;i++){
        Matrice<double> m6 = m5.copy();
    }

    cout<<"m has "<<m.shallowCopies()<<" copies."<<endl;
}
