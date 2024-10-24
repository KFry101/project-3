#include <iostream>
#include "DSString.h"

int main() {
    // Test constructors
    DSString s1("Hello");
    DSString s2(s1);  // Copy constructor
    DSString s3 = s1;  // Assignment operator
    
    // Test concatenation
    DSString s4 = s1 + " World";
    
    // Test comparison
    if (s1 == s2) {
        std::cout << "Strings are equal\n";
    }
    
    // Test substring
    DSString sub = s4.substring(0, 5);
    
    // Test array access
    char c = s1[0];  // Should be 'H'
    
    return 0;
}