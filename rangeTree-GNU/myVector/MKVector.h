//
//  MKVector.hpp
//  myVector
//
//  Created by Mike on 16/4/25.
//  Copyright © 2016年 陈俊达. All rights reserved.
//
#ifndef _MKVECTOR_H_
#define _MKVECTOR_H_

#include <stdio.h>
#include "lrtypes.h"

typedef int Rank;
#define DEFAULT_CAPACITY 1000

template <typename T>
class MKVector {
protected:
    
    Rank _size;
    int _capacity;
    T* _elem;
    
    void copyFrom( T const * A , Rank lo, Rank hi);
    void expand( s32 res );
    void shrink();
    
    bool bubble( Rank lo, Rank hi );
    void bubbleSort ( Rank lo, Rank hi );
    Rank max ( Rank lo, Rank hi );
    void selectionSort ( Rank lo, Rank hi );
    void merge( Rank lo, Rank mi, Rank hi );
    void mergeSort( Rank lo, Rank hi );
    Rank partition ( Rank lo, Rank hi );
    void quickSort ( Rank lo, Rank hi );
    void heapSort ( Rank lo, Rank hi );
    void shellSort ( Rank lo, Rank hi );
    
public:
    
//Constructor
    //value default init
    MKVector (int c = 50000, int s = 50000)
    {   _elem = new T[_capacity = c]; _size = s;} // s<=c
    
//    MKVector (int c = 1000, int s = 0, T v = 0)
//    {   _elem = new T[_capacity = c];
//        for(_size = 0; _size < s; _elem[_size++] = v) ;} // s<=c
    //Copy init
//    MKVector ( T const* A, Rank n )
//    {   copyFrom(A, 0, n);  }
//    //Copy Range
//    MKVector ( T const *A, Rank lo, Rank hi )
//    {  copyFrom(A, lo, hi); }
//    //Copy &
//    MKVector ( MKVector<T> const &V ) { copyFrom(V._elem, 0, V._size); }
//    //Copy Range &
//    MKVector ( MKVector<T> const &V, Rank lo, Rank hi ) { copyFrom(V._elem, lo, hi);}
    
    
    
//Deconstructor
    ~MKVector() { delete [] _elem; }
    
//Size Control
    void reserve( s32 res );

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
    static Rank binSearch (T *A , T const &e , Rank lo, Rank hi) ;
    static Rank fibSearch (T *A , T const &e , Rank lo, Rank hi) ;

    
//RDWTAC Access Protocol
    //Call Reference by Rank
    T& operator[] ( Rank r ) const;
    T& begin(){return operator[](0);}
    T& end(){return operator[](_size-1);}
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
    int deduplicate();//ordered
    int uniquify();//unordered
    
//Traverse
    void traverse ( void (*) (T&) );//Traverse using funx ptr (RDONLY, Regional fix)
    template <typename VST> void traverse ( VST& ); //Traverse using funx ptr (ALL)
    
};
#endif
