#ifndef ItemType_hpp
#define ItemType_hpp

#include <iostream>

struct ItemType
{    
    unsigned char ascii;
    unsigned int weight;
    
    ItemType(); // constructor
    ItemType(const ItemType &); // copy constructor

    void operator =(ItemType &);
    void operator =(unsigned char);
    void operator =(unsigned int);
    bool operator ==(ItemType &);
    bool operator >(ItemType &);
    bool operator <(ItemType &);
    bool operator !=(ItemType &);
    bool operator <=(ItemType &);
    bool operator >=(ItemType &);
    ItemType& operator++();       // Prefix increment operator
    ItemType& operator--();       // Prefix decrement operator

    friend std::ostream &operator << (std::ostream &, const ItemType &);
};

#endif // ItemType_hpp //
