// DSString.h

#define DSSTRING_H

class DSString {
private:
    char* str;      // pointer to character array
    int length;     // length of string (excluding null terminator)

public:
    // Constructors
    DSString();
    DSString(const char* s);
    DSString(const DSString& s);  // copy constructor
    
    // Destructor
    ~DSString();
    
    // Assignment operator
    DSString& operator=(const DSString& s);
    
    // Relational operators
    bool operator==(const DSString& s) const;
    bool operator<(const DSString& s) const;
    bool operator>(const DSString& s) const;
    
    // Concatenation
    DSString operator+(const DSString& s) const;
    
    // Accessors
    int getLength() const;
    char* c_str() const;  // returns C-style string
    
    // Substring
    DSString substring(int start, int numChars) const;
    
    // Modifier
    DSString& operator+=(const DSString& s);
    
    // Access operator
    char& operator[](int index);
    const char& operator[](int index) const;
};
