//
//  searching_trees.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 3/15/24.
//

#include <iostream>
#include <vector>
#include "BST.hpp"

// Recursive implementation of binary search
size_t bin_search(const std::vector<int>& v, size_t s, size_t e, int t){
    if (s > e){
        std::cout << "Target " << t << " not found!\n";
        return v.size();
    }
    else{
        size_t m = (e + s)/2;
        if (t<v[m]){
            e = m-1;
            return bin_search(v, s, e, t);
        }
        else if (t>v[m]){
            s = m+1;
            return bin_search(v, s, e, t);
        }
        else{
            std::cout << "Target " << t << " identified at index " << m << "\n";
            return m;
        }
    }
}

int main(){
    
    // Binary search:
    {
        std::vector<int> v = {2,3,4,5,6,70,80,91,101};
        int t = 3;
        size_t loc = bin_search(v, 0, v.size()-1, t);
    }
    
    
    // BST
    {
        BST bst;
        bst.insert(10, "Eric", bst.root);
        bst.insert(2, "Min", bst.root);
        bst.insert(5, "Jen", bst.root);
        bst.insert(1, "Cole", bst.root);
        bst.insert(11, "Joan", bst.root);
        bst.insert(12, "Rishi", bst.root);
        bst.insert(21, "Harlin", bst.root);
        bst.insert(19, "Jeremy", bst.root);
        std::cout << bst.search(19, bst.root) << std::endl;
        std::cout << bst.search(10, bst.root) << std::endl;
        std::cout << bst.search(1, bst.root) << std::endl;
        std::cout << bst.search(76, bst.root) << std::endl;
    }
    return 0;
}
