#include "pick_gifts.h"
#include <algorithm>

bool compareGift( const Gift& lh, const Gift& rh )
{
    return lh.price < rh.price;
}
void pickGifts( unsigned long long balance,
		int number,
		const vector< Gift >& gifts,
		int startIndex,
		vector< Gift >& selected )
{
    cout << "balance <" << balance << "> number <"
	 << number << "> startIndex <" << startIndex << ">" << endl;
    
    if( gifts.size() - startIndex < number )
    {
	selected.clear();
	return;
    }
    
    if( number == 2 )
    {
	unsigned long long maxValue = 0;
        for ( int i = startIndex; i < gifts.size() - 1; ++i )
	{
	    Gift target( balance - gifts[i].price, "" );
	    vector<Gift>::const_iterator searchBegin = gifts.begin() + i;
	    searchBegin++;
	    vector<Gift>::const_iterator iter = lower_bound( searchBegin,
							     gifts.end(),
							     target,
							     compareGift);
	    int j = 0;
	    if( gifts.end() == iter ) //all prices are lower than target val
	    {
		cout << "case 1" << endl; 
		j = gifts.size() - 1;
	    }
	    else if( iter->price == target.price )
	    {
		selected.clear();
		selected.push_back( gifts[i] );
		selected.push_back( *iter );
		cout << "case 2" << endl; 
		return;
	    }
	    else if( iter == searchBegin ) //all price are higher than target val
	    {
		//this exceeds balance
		cout << "exceeds balance" << endl;
		continue;
	    }
	    else
	    {
		--iter;
		j = iter - gifts.begin();
		cout << "case 3: j <" << j << ">" << endl; 		
	    }
	    unsigned long long temp = gifts[i].price + gifts[j].price;
	    if( temp > maxValue )
	    {
		selected.clear();
		selected.push_back( gifts[i] );
		selected.push_back( gifts[j] );
		maxValue = temp;
	    }
	}
	return;
    }

    unsigned long long localMax = 0;
    for( int j = startIndex; j < gifts.size(); ++j )
    {
	vector<Gift> tempRes;
	pickGifts( balance - gifts[j].price, number-1, gifts, j+1, tempRes );
	if( tempRes.empty() )
	{
	    continue;
	}
	unsigned long long temp = gifts[j].price;
	for( int k = 0; k < tempRes.size(); ++k )
	{
	    temp += tempRes[k].price;
	}
	if( temp > localMax )
	{
	    selected.clear();
	    selected.push_back( gifts[j] );
	    for( int k = 0; k < tempRes.size(); ++k )
	    {
		selected.push_back( tempRes[k] );		
	    }
	    
	    localMax = temp;
	}
    }

    return;
}
