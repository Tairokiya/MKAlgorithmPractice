//
//  main.cpp
//  rangeTree
//
//  Created by Mike on 16/4/24.
//  Copyright © 2016年 陈 俊达. All rights reserved.
//

#include <iostream>
#include "temperature.h"
#include "ranget.h"
#include "MKVector.h"

#define LR_VISUALIZE


int main(){
    
    int n = GetNumOfStation();
    rangetree<int, int> tree = rangetree<int, int>();
    int vx,vy;
    int *x = &vx, *y = &vy, **cur;
    for (int i = 0; i<n; i++) {
        cur = new int*();
        *cur = new int();
        GetStationInfo(i, x, y, *cur);
        tree.add(*x, *y, *cur);// shallow copy
    }
    
    tree.finalize();
    
    
    
    long long tempave = 0;
    int xx1,xx2,yy1,yy2;
    int *x1 = &xx1,*x2= &xx2,*y1 = &yy1,*y2 = &yy2;
    
    
    while (GetQuery(x1, y1, x2, y2)) {
        MKVector<int*> *foundPoints = tree.search(*x1, *x2, *y1, *y2 );
        for (int i = 0; i < foundPoints->size(); i++){
            tempave += *foundPoints->operator[](i);
            printf("%d\t",*foundPoints->operator[](i));
        }
        printf("\n");
        tempave /= foundPoints->size();
        Response(tempave); tempave = 0;
        delete foundPoints;
        
    }
    
    return 0;
    
    
    
}