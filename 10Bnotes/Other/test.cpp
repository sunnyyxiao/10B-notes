//
//  test.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/16/24.
//

#include <iostream>

using namespace std;

void printArray(int* p, size_t index){
    for (size_t i = 0; i < index; i++){
        cout << *p << " ";
        p++;
    } cout << endl;
}

void printArray (const array <int,4>& a){
    for (int val : a){
        cout << val << " ";
    }
    cout << endl;
}

int main(){
    int x = 3;
    int y = 4;
    
    int* p1 = &x;
    int* p2 = &y;
    
    cout << p1 << " " << *p1 << " " << p2 << " " << *p2 << endl;
    
    swap(p1,p2);
    
    cout << p1 << " " << *p1 << " " << p2 << " " << *p2 << endl;
    
    swap(*p1,*p2);
    
    cout << p1 << " " << *p1 << " " << p2 << " " << *p2 << endl;
    
    const size_t N = 4;
    int a[N] {2,4,5,6};
    int* p = a;
    
    cout << *p << " " << *(p+1) << endl;
    
    printArray(a,N);
    
    array<int, 4> sarray {10,6,5,4};
    sort(sarray.begin(),sarray.end());
    
    printArray(sarray);
    
    return 0;
}
