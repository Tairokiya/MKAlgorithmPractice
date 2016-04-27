//
//  MKVector.cpp
//  myVector
//
//  Created by Mike on 16/4/25.
//  Copyright © 2016年 陈俊达. All rights reserved.
//

#include "MKVector.h"

//Copy
template <typename T>
void MKVector<T>::copyFrom( T const * A , Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi-lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

//Copy Constructor
template <typename T>
MKVector<T>& MKVector<T>::operator=(MKVector<T> const &V)
{
    if (_elem) { delete [] _elem;}
    copyFrom( V._elem,  0,  V.size() );
    return *this;
}

//expand
template <typename T>
void MKVector<T>::expand( s32 res  ) {
    if ( _size < _capacity) return;
    if ( _capacity < (res < DEFAULT_CAPACITY? DEFAULT_CAPACITY : res) )
    { _capacity = (res < DEFAULT_CAPACITY? DEFAULT_CAPACITY : res); }
    /*对这个语句存在很深的疑问：地址会连续吗？会出现野指针嘛？*/
    T* oldElem = _elem; _elem = new T[_capacity << 1];
    for (int i = 0;  i < _size ; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
void MKVector<T>::reserve ( s32 res){
    T* oldElem = _elem; _elem = new T[res];
    for (int i = 0;  i < _size ; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

//shrink
template <typename T>
void MKVector<T>::shrink() {
    if ( _capacity < DEFAULT_CAPACITY<<1 ) {return;}
    if ( _size << 2 > _capacity ){return;}
    T *oldElem = _elem; _elem = new T[_capacity >>= 1];
    for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i];
    delete [] oldElem;
}

//Insert
template <typename T>
Rank MKVector<T>::insert ( Rank r, T const& e)
{
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size ++;
    return r;
}

//Remove
template <typename T>
int MKVector<T>::remove ( Rank lo, Rank hi){
    if ( lo == hi ) { return 0;}
    while ( hi < _size) { _elem[lo++] = _elem[hi++];}
    _size = lo;
    shrink();
    return hi-lo;
}

//Remove one element
template <typename T>
T MKVector<T>::remove ( Rank r ){
    T e = _elem[r];
    remove(r,r+1);
    return e;
}

//Uniquify
template <typename T>
int MKVector<T>::uniquify(){
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i]!=_elem[j]) {
            _elem[++i] = _elem[j];
        }
        _size = ++i;
        shrink();
        return j-i;
    }
}

//Sort
template <typename T>
Rank MKVector<T>::search ( T const &e , Rank lo, Rank hi) const {
    return 1%2? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

//BinSearch
template <typename T>
Rank MKVector<T>::binSearch (T *A , T const &e , Rank lo, Rank hi){
    while ( lo < hi ) {
        Rank mi = (lo+hi)>>1;
        e < A[mi] ? hi = mi : lo = mi + 1;
    }//When out, A[lo==hi] > e
    return --lo; // Failed
}

//FibSearch
template <typename T>
Rank MKVector<T>::fibSearch(T *A, T const &e, Rank lo, Rank hi) {
    ;
}

//Sort
template <typename T>
void MKVector<T>::sort( Rank lo, Rank hi ){
    mergeSort(lo, hi);
}

template <typename T>
void MKVector<T>::merge( Rank lo,Rank mi, Rank hi ){
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; i++) {B[i] = A[i];}
    int lc = hi-mi; T *C = _elem + mi;
    for (Rank i=0, j=0, k=0; j<lb; ) {
        //if ( k<lc && (lb <= j || C[k] < B[j]) ) A[i++] = C[k++]; // B[j]null or bigger
        //if ( j<lb && (lc <= k || B[j] < C[k]) ) A[i++] = B[j++]; // C[k]null or not-smaller
    
        if ( k  < lc && C[k] <  B[j]) { A[i++] = C[k++]; }
        if ( lc <= k || B[j] <= C[k]) { A[i++] = B[j++];}
    }
    delete [] B;
}
template <typename T>
void MKVector<T>::mergeSort( Rank lo, Rank hi ){
    if (hi - lo < 2) {return;}
    int mi = ( hi + lo )>>1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}



/*
 //
 //  mkVector.hpp
 //  myVector
 //
 //  Created by Mike on 16/4/25.
 //  Copyright © 2016年 陈俊达. All rights reserved.
 //
 
 #ifndef mkVector_hpp
 #define mkVector_hpp
 
 #include <stdio.h>
 
 typedef int Rank;
 #define DEFAULT_CAPACITY 300
 
 template <typename T>
 class MKVector {
 protected:
 
 Rank _size;
 int _capacity;
 T* _elem;
 
 void copyFrom( T const * A , Rank lo, Rank hi);
 void expand();
 void shrink();
 
 bool bubble( Rank lo, Rank hi );
 void bubbleSort ( Rank lo, Rank hi );
 Rank max ( Rank lo, Rank hi );
 void selectionSort ( Rank lo, Rank hi );
 void merge( Rank lo, Rank hi );
 void mergeSort( Rank lo, Rank hi );
 Rank partition ( Rank lo, Rank hi );
 void quickSort ( Rank lo, Rank hi );
 void heapSort ( Rank lo, Rank hi );
 void shellSort ( Rank lo, Rank hi );
 
 public:
 
 //Constructor
 //value default init
 MKVector (int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
 {   _elem = new T[_capacity = c];
 for(_size = 0; _size < s; _elem[_size++] = v) ;} // s<=c
 //Copy init
 MKVector ( T const* A, Rank n )
 {   copyFrom(A, 0, n);  }
 //Copy Range
 MKVector ( T const *A, Rank lo, Rank hi )
 {  copyFrom(A, lo, hi); }
 //Copy &
 MKVector ( MKVector<T> const &V ) { copyFrom(V._elem, 0, V._size); }
 //Copy Range &
 MKVector ( MKVector<T> const &V, Rank lo, Rank hi ) { copyFrom(V._elem, lo, hi);}
 
 
 
 //Deconstructor
 ~MKVector() { delete [] _elem; }
 
 //RDONLY Access Protocol
 Rank size() const   {return _size;}
 bool empty() const  {return !_size;}
 int disorderer() const;
 //Search unordered vec
 Rank find ( T const &e, Rank lo, Rank hi) const;
 Rank find ( T const &e ) const       { return find( e, 0, _size); }
 //Search ordered vec
 Rank search ( T const &e ) const     { return ( (0 >= _size) ?  -1 : search(e, 0, _size));}
 Rank search ( T const &e , Rank lo, Rank hi) const;
 
 //RDWTAC Access Protocol
 //Call Reference by Rank
 T& operator[] ( Rank r ) const;
 //Clone Vector
 MKVector<T> & operator= (MKVector<T> const& );
 //Remove
 T remove ( Rank r );
 int remove ( Rank lo, Rank hi);
 //Insert
 Rank insert ( Rank r, T const& e); // insert at
 Rank insertAtBack ( T const& e ) { return insert(_size, e);}
 //Sort
 void sort( Rank lo, Rank hi );
 void sort() { sort(0, _size);}
 //Unsort
 void unsort( Rank lo, Rank hi );
 void unsort() { sort(0, _size);}
 //Uniquify
 int deduplicate();//unordered
 int uniquify();//ordered
 
 //Traverse
 void traverse ( void (*) (T&) );//Traverse using funx ptr (RDONLY, Regional fix)
 template <typename VST> void traverse ( VST& ); //Traverse using funx ptr (ALL)
 
 };
 

 */



