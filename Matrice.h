#ifndef MATRICE_H
#define MATRICE_H
#include<bits/stdc++.h>

/*****
Matrix class by Etienne JACOB
Copy-on-write is used when shallow copy is used
******/

namespace tpmatrice {

    static bool SHALLOW_COPY = true;

    template <class T>
    class Matrice
    {
        public:
            /* constructor and destructor */
            Matrice();
            Matrice(const int& n,const int& m);
            ~Matrice();

            /* get/set */
            T get(const int& i,const int& j);
            void set(const int& i,const int& j,const T& value);

            /* operators */
            T operator()(const int& i,const int& j);
            Matrice<T> operator + (const Matrice<T>& m);
            Matrice<T> operator - (const Matrice<T>& m);
            Matrice<T> operator * (const Matrice<T>& m);
            Matrice<T> operator = (const Matrice<T>& m);

            /* copy */
            Matrice<T> copy();

            /* useful functions */
            void setRandomValues();
            void print();

        private:
            T * tab;
            int cols;
            int rows;
            int * copy_count;
            Matrice(T * tab_,int * copy_count_,const int& n,const int& m);
            Matrice<T> shallowCopy();
            Matrice<T> normalCopy();
        protected:
    };

    template <class T>
    Matrice<T>::Matrice()
    {
    }

    template <class T>
    Matrice<T>::~Matrice()
    {
        if(SHALLOW_COPY && ((*copy_count)>1)){
            (*copy_count)--;
        }
        else {
            delete[] tab;
        }
    }

    template <class T>
    Matrice<T>::Matrice(const int& n,const int& m)
    {
        tab = new T [n*m];
        rows = n;
        cols = m;
        copy_count = new int;
        *copy_count = 1;
    }

    template <class T>
    Matrice<T>::Matrice(T * tab_,int * copy_count_,const int& n,const int& m)
    {
        tab = tab_;
        rows = n;
        cols = m;
        copy_count = copy_count_;
    }

    template <class T>
    void Matrice<T>::set(const int& i,const int& j,const T& value){
        assert(i>=0&&j>=0&&i<rows&&j<cols);

        T * prevTab = tab;

        if(SHALLOW_COPY){
            tab = new T[rows*cols];

            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    tab[i + j*rows] = prevTab[i+j*rows];
                }
            }
        }

        if(SHALLOW_COPY){
            if((*copy_count)>1){
                (*copy_count)--;
            }
            else {
                delete[] prevTab;
            }

            copy_count = new int;
            *copy_count = 1;
        }

        tab[i + j*rows] = value;
    }

    template <class T>
    T Matrice<T>::get(const int& i,const int& j){
        assert(i>=0&&j>=0&&i<rows&&j<cols);

        return tab[i + j*rows];
    }

    template <class T>
    void Matrice<T>::setRandomValues(){

        T * prevTab = tab;

        if(SHALLOW_COPY){
            tab = new T[rows*cols];
        }

        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                tab[i + j*rows] = 1.0*std::rand()/RAND_MAX;
            }
        }

        if(SHALLOW_COPY){
            if((*copy_count)>1){
                (*copy_count)--;
            }
            else {
                delete[] prevTab;
            }

            copy_count = new int;
            *copy_count = 1;
        }
    }

    template <class T>
    T Matrice<T>::operator()(const int& i,const int& j){
        return get(i,j);
    }

    template <class T>
    Matrice<T> Matrice<T>::shallowCopy(){
        (*copy_count)++;

        Matrice<T> res(tab,copy_count,rows,cols);

        return res;
    }

    template <class T>
    Matrice<T> Matrice<T>::normalCopy(){
        Matrice<T> res = Matrice<T>(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                res.tab[i + j*rows] = tab[i + j*rows];
            }
        }
        return res;
    }

    template <class T>
    Matrice<T> Matrice<T>::copy(){
        if(SHALLOW_COPY){
            return shallowCopy();
        } else {
            return normalCopy();
        }
    }

    template <class T>
    Matrice<T> Matrice<T>::operator = (const Matrice<T>& m){
        return m.copy();
    }

    template <class T>
    Matrice<T> Matrice<T>::operator + (const Matrice<T>& m){
        assert((cols == m.cols) && (rows == m.rows));
        Matrice<T> res = Matrice<T>(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<m.cols;j++){
                res.tab[i + j*rows] = tab[i + j*rows] + m.tab[i + j*rows];
            }
        }
        return res;
    }

    template <class T>
    Matrice<T> Matrice<T>::operator - (const Matrice<T>& m){
        assert((cols == m.cols) && (rows == m.rows));
        Matrice<T> res = Matrice<T>(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<m.cols;j++){
                res.tab[i + j*rows] = tab[i + j*rows] - m.tab[i + j*rows];
            }
        }
        return res;
    }

    template <class T>
    Matrice<T> Matrice<T>::operator * (const Matrice<T>& m){
        assert(cols == m.rows);
        Matrice<T> res = Matrice<T>(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<m.cols;j++){
                T sum = 0;
                for(int k=0;k<cols;k++){
                    sum += tab[i + k*rows]*m.tab[k + j*m.rows];
                }
                res.tab[i + j*rows] = sum;
            }
        }
        return res;
    }

    template <class T>
    void Matrice<T>::print(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                std::cout<<tab[i + rows*j]<<"\t";
            }
            std::cout<<std::endl;
        }
    }
}

#endif // MATRICE_H
