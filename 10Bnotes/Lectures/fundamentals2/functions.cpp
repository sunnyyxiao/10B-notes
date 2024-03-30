//
//  functions.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/10/24.
//

#include "functions.hpp"
#include <cmath>

double prob_bday(int n_students){
    return 1-pow(364.0/365, n_students);
}

