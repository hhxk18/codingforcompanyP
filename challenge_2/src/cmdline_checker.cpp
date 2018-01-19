#include "cmdline_checker.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

static const char DELIMITER = ',';
static const int EXP_NUM_DELIMITER = 1; //Expected number of delimiter

bool isDelimiter( char c )
{
    return c == DELIMITER;
}

RCode CmdlineParser::parse( int argc, char** args, Results& r )
{
    if( argc < 2 || argc > 4 )
    {
	cerr << "Unexpected number of arguments!" << endl;	
	return RCODE_INVALID_ARGS;
    }

    if( strcmp( args[1], "-h" ) == 0
	|| strcmp( args[1], "--help" ) == 0 )
    {
	return RCODE_PRINT_USAGE;
    }

    try
    {
	r.balance = stoull( args[2] );
    }
    catch( const out_of_range& ex )
    {
	cerr << "Balance is Out of Range: " << ex.what() << endl;
	return RCODE_INVALID_ARGS;
    }

    //number of people
    r.n = argc == 4 ? atoi( args[3] ) : 2; // default to 2 people
    
    string fileName = args[1];
    ifstream fs( fileName );
    if( !fs.is_open() )
    {
	cerr << "Unable to open file <" << fileName << ">" << endl;
	return RCODE_UNABLE_OPEN_FILE;
    }

    string line;
    while( getline( fs, line ) )
    {
	int delimiterCount = count_if( line.begin(), line.end(), isDelimiter );
	if( EXP_NUM_DELIMITER != delimiterCount )
	{
	    cerr << "Unexpected line <" << line << ">. Expect num of delimiter <"
		 << EXP_NUM_DELIMITER << "> found <" << delimiterCount << ">"
		 << endl;
	    
	    return RCODE_INVALID_FILE_CONTENT;
	}
	size_t i = line.find( DELIMITER );
	if( i == 0 )
	{
	    cerr << "Unexpected line <" << line << ">. Empty gift name." << endl;
	    return RCODE_INVALID_FILE_CONTENT;
	}
	string itemName = line.substr( 0, i );
	string priceStr = line.substr( i+1 );
	unsigned long long price = 0;
	try
	{
	    price = stoull( priceStr );
	}
	catch( const out_of_range& ex )
	{
	    cerr << "Price is out of Range: " << ex.what() << " line <"
		 << line << ">" << endl;
	    
	    return RCODE_INVALID_FILE_CONTENT;
	}
	if( price == 0 )
	{
	    cerr << "Unexpected: price is zero: line <" << line << ">" << endl;
	    return RCODE_INVALID_FILE_CONTENT;
	}
	
	if( price < r.balance )
	{
	    r.gifts.push_back( Gift( price, itemName ) );
	}	
    }    
    fs.close();

    if( r.gifts.empty() )
    {
	return RCODE_OK;
    }

    int prev = 0;
    for( int i = 1; i < r.gifts.size(); ++i )
    {
	if( r.gifts[i].price >= r.gifts[prev].price )
	{
	    ++prev;	    
	}
	else
	{
	    cerr << "Unexpected: gift items are not sorted in ascending order:"
		 << "previous <" << r.gifts[prev] << "> current <" << r.gifts[i]
		 << ">" << endl;
	    return RCODE_INVALID_FILE_CONTENT;
	}
    }
    return RCODE_OK;
}
