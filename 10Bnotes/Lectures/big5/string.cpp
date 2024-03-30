//
//  string.cpp
//  PIC10B
//
//  Created by Sunny Xiao on 2/28/24.
//

#include "string.hpp"

namespace basic {


string::string() : siz(0), ptr(new char[1]{'\0'}) {}

string::string(const char* sl) : siz(0), ptr(nullptr) {
    // we set siz to the index of the null character
    while (sl[siz] != '\0') { ++siz; }

    // we make enough space for the characters
    // including the null character
    ptr = new char[siz + 1];

    // we copy the characters of the string literal
    // (including the null character)
    // to the newly allocated memory
    for (size_t i = 0; i <= siz; ++i) {
        ptr[i] = sl[i];
    }
}

string::string(size_t n, char c) : siz(n), ptr(new char[n + 1]) {
    for (size_t i = 0; i < siz; ++i) {
        ptr[i] = c;
    }
    ptr[siz] = '\0';
}

string::~string() {
    std::cout << "destructor called" << std::endl;
    delete[] ptr;
}


size_t string::size()   const { return siz; }
size_t string::length() const { return siz; }

char& string::operator[](size_t i)       { return ptr[i]; }
char  string::operator[](size_t i) const { return ptr[i]; }

std::ostream& operator<<(std::ostream& out, const string& s) {
    for (size_t i = 0, N = s.size(); i < N; ++i) {
        out << s[i];
    }
    return out;
}


string::string(const string& other) : siz(other.siz), ptr(new char[other.siz + 1]) {
    std::cout << "copy constructor called" << std::endl;

    // we copy the characters of the string literal
    // (including the null character)
    // to the newly allocated memory
    for (size_t i = 0; i <= siz; ++i) {
        ptr[i] = other.ptr[i];
    }
}

string::string(string&& other) : string() {
    // we call the default constructor to create
    // the smallest object that is in a valid state

    std::cout << "move constructor called" << std::endl;

    std::swap(siz, other.siz); // we exchange sizes
    std::swap(ptr, other.ptr); // and resources
}


string& string::operator=(const string& other) {
    std::cout << "copy assignment operator called" << std::endl;

    // this tests whether the address of the
    // assigned-from and assigned-to objects
    // are the same; if so, we avoid the work
    // of extra copying
    if (this == &other) {
        return *this;
    }


    // some implementations would 'delete[] ptr' here
    // and would not need to 'delete[] old' below;
    // in such cases, the self-assignment check is necessary
    // to avoid destroying the object under self-assignment
    char* old = ptr;


    siz = other.siz;
    ptr = new char[other.siz + 1];

    // we copy the characters of the string literal
    // (including the null character)
    // to the newly allocated memory
    for (size_t i = 0; i <= siz; ++i) {
        ptr[i] = other.ptr[i];
    }


    delete[] old;
    return *this;
}

string& string::operator=(string&& other) {
    std::cout << "move assignment operator called" << std::endl;

    // swap the state of the two objects so the
    // assigned-to object takes ownership of other.ptr
    std::swap(siz, other.siz);
    std::swap(ptr, other.ptr);

    return *this;
}


string& string::operator=(const char* sl) {
    return *this = string(sl);
}
string& string::operator=(char c) {
    return *this = string(1, c);
}


void string::resize(size_t n, char c) {
    // this could be improved if we stored
    // 'capacity' and 'size' as separate values

    if (siz < n) {
        char* old = ptr;
        ptr = new char[n + 1];

        for (size_t i = 0; i < siz; ++i) {
            ptr[i] = old[i];
        }
        delete[] old;

        for (size_t i = siz; i < n; ++i) {
            ptr[i] = c;
        }
    }
    siz = n;
    ptr[siz] = '\0';
}
void string::resize(size_t n) {
    if (siz < n) {
        char* old = ptr;
        ptr = new char[n + 1](); // value initialize

        for (size_t i = 0; i < siz; ++i) {
            ptr[i] = old[i];
        }
        delete[] old;
    }
    siz = n;
    ptr[siz] = '\0';
}


string::string(size_t _siz, char* _ptr) : siz(_siz), ptr(_ptr) {}

string operator+(const string& l, const string& r) {
    char* ptr = new char[l.siz + r.siz + 1];

    for (size_t i = 0; i < l.siz; ++i) {
        ptr[i] = l.ptr[i];
    }
    for (size_t i = 0; i <= r.siz; ++i) {
        ptr[l.siz + i] = r.ptr[i];
    }

    return string(l.siz + r.siz, ptr);
}

string& string::operator+=(const string& other) {
    return *this = *this + other;
}


void swap(string& s1, string& s2) {
    std::swap(s1.siz, s2.siz);
    std::swap(s1.ptr, s2.ptr);
}


}
