#include <iostream>
#include "Matrice.h"

using namespace std;
using namespace tpmatrice;

int main(){

    SHALLOW_COPY = true;

    Matrice<double> m = Matrice<double>(3,3);

    m.setRandomValues();

    Matrice<double> m3 = (m+m)*m - m;
    m3.print();


    Matrice<double> m2 = m.copy();
    Matrice<double> m4 = m2;
    //cout << m2(1,1) << endl;

    return 0;
}
