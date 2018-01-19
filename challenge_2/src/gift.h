#ifndef INCLUDED_GIFT_H
#define INCLUDED_GIFT_H

#include <string>
#include <iostream>

using namespace std;

struct Gift
{
    unsigned long long price;
    string name;

    Gift()
    :   price( 0 )
    ,   name( "" )
    {
    }

    Gift( unsigned long long a_price,
	  const string& a_name )
    :   price( a_price )
    ,   name( a_name )
    {
    }

    bool operator < ( const Gift& rh );
};

ostream& operator << ( ostream& os, const Gift& g );

#endif
