//
//  ds_intro.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/1/24.
//

#include <iostream>
#include <vector>


// The purpose of this class is just to be a noisy int, in the sense that it wraps an int and prints statements to the console when various functions are called.
struct A{
    A(int _i):i(_i){}
    //std::cout << "Destroying " << &i <<"\n";
    ~A(){}
    A(const A& a){
        //std::cout<<"Copy constructing " << i << "<-" << a.i << " at " << &i << "<-" << &a.i <<"\n";
        i = a.i;}
    A(A&& a) noexcept {
        //std::cout<<"Move constructing " << i << "<-" << a.i << " at " << &i << "<-" << &a.i <<"\n";
        i = a.i;
    }
    A& operator=(const A& right){
        std::cout << "Copy assigning " << i << "<-" << right.i << " at " << &i << "<-" << &right.i <<"\n";
        i = right.i;
        return *this;}
    A& operator=(A&& right) noexcept {
        std::cout << "Move assigning " << i << "<-" << right.i << " at " << &i << "<-" << &right.i <<"\n";
        i = right.i;
        return *this;}
    int i;
};

void print_Avec(const std::vector<A>& v){
    for(size_t j=0; j<v.size(); j++){
        std::cout<< v[j].i << " at " <<&v[j] << "\n";
    }
}


int main(){
    
    // Illustration of why inserting and removing elements in a vector is not very efficient!
    {
        // Lets first create a vector of A objects
        std::cout << "Creating vector of A objects\n";
        std::vector<A> v {1,2,3,4,5,6,7,8,9};
        v.reserve(20);
        print_Avec(v);

        /* One of the key strengths of a vector or array structure is the speed with which object access can take place.
         */
        std::cout << v[0].i << "\n";

        // Now lets insert an element somewhere
        size_t insert_point = 2;
        // Recall v.begin() returns an 'iterator' to the beginning of the vector. For now we can think of this like a pointer to the first location, when we add insert_point then we move access the inser_point th element in the array underlying the vector.1
        
        v.insert(v.begin() + insert_point, A(-18));
//        v.insert(v.begin() + insert_point, A(-18));
        // Lets now view the structure...
        print_Avec(v);

        // This resulted in us moving all the elements of the vector from index insert_point onwards!
        // Likewise we can do something similar with erase
        size_t erase_point = 5;
        v.erase(v.begin() + erase_point);

        /* Clearly inserting and removing elements from the middle of vectors is expensive... Lets pause here and try and work out how expensive! Suppose there are n elements in the vector currently.
         - If you insert at element n   then # elements moved = 0
         - If you insert at element n-1 then # elements moved = 1
         - If you insert at element n-2 then # elements moved = 2
         - If you insert at element n-3 then # elements moved = 3
         ...     ...       ...       ...        ...           ...
         - If you insert at element 0   then # elements moved = n
         So it really depends on where the insert takes place: if it takes place near the end of the vector then pretty cheap to perform! However insertion towards the middle and even worse the beginning is expensive. One common measure is to take the average assuming a unifom distribution over the insertion points. This gives (1/n)*(1 + 2 + 3 + 4... n) = (1/n)*(n(n+1)/2) = (n+1)/2 = O(n)

         So the expected number of operations to insert or move scales with the size of the vector
         */
    }
    
    
    return 0;
}
