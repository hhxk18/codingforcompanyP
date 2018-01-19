#include "cmdline_checker.h"
#include "pick_gifts.h"

#include <iostream>
#include <string>

using namespace std;

static void printUsage();

int main( int argc, char** args )
{
    CmdlineParser::Results res;
    RCode rc = CmdlineParser::parse( argc, args, res );

    if( RCODE_PRINT_USAGE == rc || RCODE_INVALID_ARGS == rc )
    {
	printUsage();
	return 1;
    }

    if( RCODE_UNABLE_OPEN_FILE == rc || RCODE_INVALID_FILE_CONTENT == rc )
    {
	return 1;
    }

    if( RCODE_OK != rc )
    {
	cerr << "Unexpected rcode <" << rc << ">" << endl;
	return 1;
    }

    vector< Gift > selected;
    int startIndex = 0;
    pickGifts( res.balance, res.n, res.gifts, startIndex, selected );
    if( selected.empty() )
    {
	cout << "Not possible" << endl;
    }
    else
    {
	for( int i = 0; i < selected.size() - 1; ++i )
	{
	    cout << selected[i] << ", ";
	}
	cout << selected[ selected.size()-1 ] << endl;
    }
    return 0;
}

void printUsage()
{
    cout << "Usage: " << endl;
    cout << "main -h" << endl;
    cout << "main <filename> <balance> [n]" << endl;
    
}
