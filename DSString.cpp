

// DSString.cpp
#include "DSString.h"
#include <cstring>  // only used in constructor to get string length
#include <stdexcept>

// Default constructor
DSString::DSString() {
    length = 0;
    str = new char[1];
    str[0] = '\0';
}

// Constructor from C-string
DSString::DSString(const char* s) {
    if (s == nullptr) {
        length = 0;
        str = new char[1];
        str[0] = '\0';
        return;
    }
    
    // Calculate length without using strlen
    length = 0;
    while (s[length] != '\0') {
        length++;
    }
    
    str = new char[length + 1];
    // Copy characters manually without strcpy
    for (int i = 0; i <= length; i++) {
        str[i] = s[i];
    }
}

// Copy constructor
DSString::DSString(const DSString& s) {
    length = s.length;
    str = new char[length + 1];
    // Copy characters manually
    for (int i = 0; i <= length; i++) {
        str[i] = s.str[i];
    }
}

// Destructor
DSString::~DSString() {
    delete[] str;
}

// Assignment operator
DSString& DSString::operator=(const DSString& s) {
    if (this != &s) {  // Check for self-assignment
        delete[] str;  // Delete old string
        
        length = s.length;
        str = new char[length + 1];
        // Copy characters manually
        for (int i = 0; i <= length; i++) {
            str[i] = s.str[i];
        }
    }
    return *this;
}

// Equality operator
bool DSString::operator==(const DSString& s) const {
    if (length != s.length) {
        return false;
    }
    
    for (int i = 0; i < length; i++) {
        if (str[i] != s.str[i]) {
            return false;
        }
    }
    return true;
}

// Less than operator
bool DSString::operator<(const DSString& s) const {
    int minLength = (length < s.length) ? length : s.length;
    
    for (int i = 0; i < minLength; i++) {
        if (str[i] < s.str[i]) return true;
        if (str[i] > s.str[i]) return false;
    }
    
    return length < s.length;
}

// Greater than operator
bool DSString::operator>(const DSString& s) const {
    return s < *this;
}

// Concatenation operator
DSString DSString::operator+(const DSString& s) const {
    char* newStr = new char[length + s.length + 1];
    
    // Copy first string
    for (int i = 0; i < length; i++) {
        newStr[i] = str[i];
    }
    
    // Copy second string
    for (int i = 0; i <= s.length; i++) {
        newStr[length + i] = s.str[i];
    }
    
    DSString result(newStr);
    delete[] newStr;
    return result;
}

// Get length
int DSString::getLength() const {
    return length;
}

// Get C-style string
char* DSString::c_str() const {
    char* cstr = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        cstr[i] = str[i];
    }
    return cstr;
}

// Substring
DSString DSString::substring(int start, int numChars) const {
    if (start < 0 || start >= length || numChars <= 0) {
        return DSString();
    }
    
    if (start + numChars > length) {
        numChars = length - start;
    }
    
    char* subStr = new char[numChars + 1];
    for (int i = 0; i < numChars; i++) {
        subStr[i] = str[start + i];
    }
    subStr[numChars] = '\0';
    
    DSString result(subStr);
    delete[] subStr;
    return result;
}

// += operator
DSString& DSString::operator+=(const DSString& s) {
    char* newStr = new char[length + s.length + 1];
    
    // Copy existing string
    for (int i = 0; i < length; i++) {
        newStr[i] = str[i];
    }
    
    // Append new string
    for (int i = 0; i <= s.length; i++) {
        newStr[length + i] = s.str[i];
    }
    
    delete[] str;
    str = newStr;
    length = length + s.length;
    
    return *this;
}

// Array access operator
char& DSString::operator[](int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of bounds");
    }
    return str[index];
}

// Const array access operator
const char& DSString::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of bounds");
    }
    return str[index];
}