//
//  Wk2Discussion.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 1/16/24.
//

#include <iostream>
#include <string>

class Student{
private:
    std::string name;
    size_t id;
    int score_1, score_2, score_3;
    
public:
    Student(std::string _name):name(_name),id(1111), score_1(0), score_2(0), score_3(0){}
    Student(std::string _name, size_t _id, int _score_1, int _score_2, int _score_3):name(_name), id(_id), score_1(_score_1), score_2(_score_2), score_3(_score_3){}
    void display_average(){
        std::cout << "The average of the scores of the three subjects for " << name << " is: " << (score_1+score_2+score_3)/3 << std::endl;
    }
};

int main(){
    Student A("John");
    Student B("Jack", 1234, 50, 60, 70);
    A.display_average();
    B.display_average();
    
}
