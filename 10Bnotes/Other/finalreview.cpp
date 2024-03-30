//
//  finalreview.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/13/24.
//

#include <vector>
#include <iostream>

void insertionSort(std::vector<int> v){
    size_t N = v.size();
    for (size_t i = 1; i < N; i++){
        size_t j = i-1;
        while ((j>=0)&&(v[j]>v[j+1])){
            std::swap(v[j],v[j+1]);
            j--;
        }
        for (int i: v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

struct B{
    int i;
    B(int _i):i(_i){}
    ~B(){std::cout << "Destructor called for B with i = " << i << "\n";}
};

struct C{
    C(int i1,int i2):p(std::make_shared<int>(i1)), i(i2){}
    
    ~C(){std::cout << "Destructor called\n";}
    
    C (const C& r):C(*(r.p),r.i){}
    
    C (C&& r):p(nullptr),i(0){
        i = r.i;
        std::swap(p,r.p);
    }
    
    C& operator = (const C& r){
        i = r.i;
        p = r.p;
        return *this;
    }
    
    C& operator = (C&& r){
        i = r.i;
        std::swap(p,r.p);
        return *this;
    }
    
    std::shared_ptr<int> p;
    int i;
    
};

int main(){
    {
        std::shared_ptr<B> p1 = std::make_shared<B>(1);
        std::shared_ptr<B> p2 = std::make_shared<B>(2);
        std::shared_ptr<B> p3 = std::make_shared<B>(3);
        p2 = p1;
        p1 = p3;
        
        //p2 holds B(1), p3 and p1 hold B(3)
        
        //destroy p3 --> p2 --> p1?
    }
    
    {
        std::cout << "\n4C\n";
        C c1(1,2);
        std::cout << c1.i << "\n";
        C c2(c1);
        std::cout << c2.i << "\n";
        c1.i += 1;
        std::cout << c2.i << "\n";
        int* p = c1.p.get();
        *p += 4;
        std::cout << c2.i << " " << *(c2.p) << "\n";
    }
    
    {
        std::cout <<"\n4D\n";
        C c1(1,2);
        C c2(0,0);
        c2 = c1;
        c1.i += 1;
        int* p = c1.p.get();
        *p += 4;
        std::cout << c2.i << " " << *(c2.p) << "\n";
    }
    
    {
        std::cout << "\n4E\n";
        C c1(C(1,2));
        std::cout << c1.i << " " << *(c1.p) << "\n";
    }
    
    {
        std::cout << "\n4F\n";
        C c1(1,2);
        C c2(0,0);
        c2 = std::move(c1);
        std::cout << *(c2.p) << " " << *(c2.p) << "\n";
    }
    
    {
        std::cout << "\n5D\n";
        std::vector v = {3,2,4,1,5};
        insertionSort(v);
    }
    return 0;
}
