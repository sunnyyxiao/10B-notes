//
//  sort-rec-bs.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/8/24.
//

/*
 Agenda
 - Review of the three key operations: access, mutate, search
 - How good are unsorted arrays and linked lists at search?
 - Implement linear search
 - Sorted arrays ant eh binary search algorithm
 - Recap of recursion (examples: tower of hanoi, fibonacci)
 - Implement binary search algorithm using recursion
 */

#include <vector>
#include <iostream>
#include <cassert>

size_t int_linear_search(std::vector<int> v, int target){
    size_t N = v.size();
    for (size_t i = 0; i < N; i++){
        if (v[i] == target){
            std::cout << "Found " << target << " at location " << i << std::endl;
            return i;
        }
    }
    std::cout << target << " not in vector" << std::endl;
    return N;
}

/*
 2 input
 Move disk 1 from og to spare
 Move disk 2 from og to dest
 move disk 1 from spare to dest
 
 3 input
 Move disk 1 from og to dest
 move disk 2 from og to spare
 Move disk 1 from dest to spare
 move disk 3 from og to dest
 move disk 1 from spare to og
 move disk 2 from spare to dest
 move disk 1 from og to dest
 */

void TowerOfHanoi(int n_disks, char origin, char destination, char spare){
    if (n_disks == 0){
        return;
    }
    //Step 1 moves top n-1 disks from origin to spare
    TowerOfHanoi(n_disks-1,origin,spare,destination);
    std::cout << "Move disk " << n_disks << " from rod " << origin << " to rod " << destination << "\n";
    TowerOfHanoi(n_disks-1,spare,destination,origin);
}

int fib(size_t n){
    //Compues nth fibonacci number, where 0th and 1st are equal to 1
    std::cout << "Fibonacci non recursive: " << std::endl;
    int prev = 1;
    int curr = 1;
    int next;
    for (size_t i = 2; i <= n; i++){
        next = prev + curr;
        std::cout << "Calculated " << next << std::endl;
        prev = curr;
        curr = next;
    }
    return curr;
}

int Fib(size_t n){
    // Computes the nth Fibonacci numbers starting from 1.
    // Note here we index the first and second fibonacci numbers as 1.
    if((n==1)||(n==2)){
        return 1;
    }
    return Fib(n-1) + Fib(n-2);
}

size_t bin_search(const std::vector<int>& v, size_t s, size_t e, int t){
    if (e >= s){
        size_t m = s + (e-s)/2; //(e+s)/2 is same
        if (v[m] == t){
            std::cout << "Target found at location " << m << "\n";
            return m;
        } else if (v[m] > t){
            return bin_search(v, s, m-1, t);
        } else {/* if (v[m] < t){*/
            return bin_search(v, m+1, s, t);
        }
    } else {
        std::cout << "Target not in vector, returning vector size + 1\n";
        return v.size()+1;
    }
}

//Non-recursive variation, recursive variation is similar but either is fine
void selection_sort_nr(std::vector<int>& v, bool print = false){
    size_t N = v.size();
    //At each iteration of outer loop put ihe ith smallest element at index i
    for (size_t i = 0; i < N-1; i++){
        size_t min_pos = i;
        //Pass through the unordered part of the vector to find the smallest unsorted entry
        for (size_t j = i+1; j < N; j++){
            if (v[j]<v[min_pos]){
                min_pos = j;
            }
        }
        std::swap(v[i],v[min_pos]);
        if (print){
            for (int val : v){
                std::cout << val << ' ';
            }
            std::cout << std::endl;
        }
    }
}

void bubble_sort_nr(std::vector<int>& v, bool print=false){
    size_t N = v.size();
    bool updated=true;
    while(updated){
        updated = false;
        for(size_t i =0; i<N-1; i++){
            if(v[i+1]<v[i]){
                std::swap(v[i+1], v[i]);
                updated = true;
            }
            if (print){for (int val : v) {
                std::cout << val << ' ';
            }
            std::cout << std::endl;}
        }
    }
}

void bubble_sort(std::vector<int>& v, bool print=false){
    size_t N = v.size();
    bool updated=true;
    while(updated){
        updated = false;
        for(size_t i =0; i<N-1; i++){
            if(v[i+1]<v[i]){
                std::swap(v[i+1], v[i]);
                updated = true;
            }
        }
    }
}

void merge_sort(std::vector<int>& v, size_t beg = 0, size_t end = -1) {
    // Vectors of size 0 and size 1 are already sorted.
    if (v.size() == 0 || v.size() == 1) { return; }

    // We decrease 'end' to be reasonable
    // in case the default value is being used.
    end = std::min(end, v.size() - 1);

    // We check 'beg' and 'end' are reasonable.
    assert(beg <= end);

    // When beg == end, the range is already sorted.
    if (beg == end) { return; }


    // The elements to be sorted can be divided into two groups:
    // v[beg],     ..., v[mid]
    // v[mid + 1], ..., v[end]
    const size_t mid = beg + ((end - beg) / 2);
    // This formula avoids overflow better than (beg + end) / 2.

    // We sort the first half recursively...
    merge_sort(v, beg, mid);

    // We sort the second half recursively...
    merge_sort(v, mid + 1, end);

    // With the two halves sorted, we just have to implement the merging process.

    // We'll need a temporary vector as we rearrange the numbers.
    // Eventually, it'll have end - beg + 1 elements.
    std::vector<int> tmp;
    tmp.reserve(end - beg + 1);

    // We introduce an index for the first sorted half and an index for the second sorted half.
    size_t idx_1st_half = beg;
    size_t idx_2nd_half = mid + 1;

    // While we still have elements left in the first half and the second half...
    while ((idx_1st_half <= mid) && (idx_2nd_half <= end)) {
        if (v[idx_1st_half] < v[idx_2nd_half]) {
            // if the element from the first half is smaller,
            // add it to tmp and increment the relevant index;
            tmp.push_back(v[idx_1st_half++]);
        }
        else {
            // if the element from the second half is smaller,
            // add it to tmp and increment the relevant index;
            tmp.push_back(v[idx_2nd_half++]);
        }
    }

    // At this point, we have used up all the elements in either the first sorted half or the second sorted half.
    // Only one of the following two while loops will execute anything interesting.
    while (idx_1st_half <= mid) {
        tmp.push_back(v[idx_1st_half++]);
    }
    while (idx_2nd_half <= end) {
        tmp.push_back(v[idx_2nd_half++]);
    }

    // Finally, we place the elements in tmp
    // in their correct position in the original vector.
    for (size_t i = beg; i <= end; ++i) {
        v[i] = tmp[i - beg];
    }
}

int main(){
    //Linear search is O(n)
    std::vector<int> v = {1,3,2,5,6,7,48,12};
    std::cout << int_linear_search(v,3) << "\n";
    std::cout << int_linear_search(v,8) << "\n";
    
    //A recursive function is a function which calls itself
    //Example: Tower of Hanoi
    TowerOfHanoi(4,'a','b','c');
    
    {
        std::vector<int> v = {2,3,4,5,6,70,80,91,101};
        int t = 92;
        size_t loc = bin_search(v,0,v.size()-1,t);
    }
    
    return 0;
}

