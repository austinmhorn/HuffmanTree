#include "ItemType.hpp"
#include <iostream>

ItemType::ItemType()
{
    this->ascii = '~';
    this->weight = 0;
}

ItemType::ItemType(const ItemType &i)
{
    this->ascii = i.ascii;
} // copy constructor

void ItemType::operator =(ItemType &i)
{
    this->ascii  = i.ascii;
    this->weight = i.weight;
}

bool ItemType::operator ==(ItemType &i)
{
    return ascii==i.ascii;
}

bool ItemType::operator >(ItemType &i)
{
    return ascii>i.ascii;
}

bool ItemType::operator <(ItemType &i)
{
    return ascii<i.ascii;
}

bool ItemType::operator !=(ItemType &i)
{
    return ascii!=i.ascii;
}

bool ItemType::operator >=(ItemType &i)
{
    return ascii>=i.ascii;
}

bool ItemType::operator <=(ItemType &i)
{
    return ascii<=i.ascii;
}

void ItemType::operator =(unsigned char c)
{
    this->ascii = c;
}

void ItemType::operator =(unsigned int i)
{
    this->weight = i;
}

ItemType& ItemType::operator++()
{
    this->weight++;
    return *this;
}

ItemType& ItemType::operator--()
{
    this->weight--;
    return *this;
}

std::ostream &operator << (std::ostream &out, const ItemType &i)
{
    out << "|   " << "'" << i.ascii << "'   |    " << i.weight << "    |";
    return out;
}



