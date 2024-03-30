//
//  string5.hpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/28/24.
//

#ifndef string_hpp
#define string_hpp

#include <iostream>
#include <utility>


namespace basic {


class string {
public:
    string();                          // default constructor
    /*explicit*/ string(const char*);               // construct using string literal
    string(size_t, char);              // construct using length and character

    ~string();                         // destructor


    size_t size()   const;             // size and length
    size_t length() const;             // are synonyms

    char& operator[](size_t);          // subscript access and modify
    char  operator[](size_t) const;    // subscript access


    string(const string&);             // copy constructor
    string(string&&);                  // move constructor

    string& operator=(const string&);  // copy assignment
    string& operator=(string&&);       // move assignment


    string& operator=(const char*);    // assignment from string literal
    string& operator=(char);           // assignment from char


    void resize(size_t, char);
    void resize(size_t);


    string& operator+=(const string&); // concatenation


private:
    size_t siz;
    char*  ptr;

    string(size_t, char*);


    friend string operator+(const string&, const string&);
    friend void swap(string&, string&);
};


std::ostream& operator<<(std::ostream&, const string&);
void swap(string&, string&);


}


#endif /* string_hpp */
