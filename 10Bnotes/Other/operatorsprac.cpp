//
//  operatorsprac.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/22/24.
//

#include <iostream>
#include <vector>

/*
 Write a class for a d-dimensional vectors
 - constructors (one should map a double to a vector (constant)
 - overload + between vectors, delete between vector and doubles
 - overload * between doubles and vectors, delete * vector and doubles
 - overload [] to access ith element
 - overload << operators
 */

//class DVec {
//public:
//    DVec(int num, double a):{
//        for (size_t i = 0; i < num; i++){
//            v1.push_back(a);
//        }
//    }
//    DVec(int num):{
//        v1.reserve(num);
//    }
//    DVec():v1{}{}
//
//    friend DVec& operator + (const DVec& left, const DVec& right){
//        if (left.v1.size() > right.v1.size()){
//            DVec newVec(right);
//            for (size_t i = newVec.v1.size(); i < left.v1.size(); i++){
//                newVec.v1.push_back(left.v1[i]);
//            }
//            return newVec;
//        } else {
//            DVec newVec(left);
//            for (size_t i = newVec.v1.size(); i < right.v1.size(); i++){
//                newVec.v1.push_back(right.v1[i]);
//            }
//            return newVec;
//        }
//    }
//
//    friend std::ostream& operator << (std::ostream& os, const DVec& right){
//        for (size_t i = 0; i<right.v1.size(); i++){
//            os << right.v1[i] << " ";
//        }
//        os << std::endl;
//        return os;
//    }
//private:
//    std::vector<double> v1;
//};
//
//int main(){
//    return 0;
//}
