#include "gift.h"

ostream& operator << (ostream& os, const Gift& g )
{
    os << g.name << " " << g.price;

    return os;
}

bool Gift::operator < ( const Gift& rh )
{
    return price < rh.price;
}
