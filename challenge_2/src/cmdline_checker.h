#ifndef INCLUDED_CMDLINE_PARSER_H
#define INCLUDED_CMDLINE_PARSER_H

#include "gift.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

enum RCode
{
    RCODE_OK = 0,
    RCODE_PRINT_USAGE = 1,
    RCODE_INVALID_ARGS = 2,
    RCODE_UNABLE_OPEN_FILE = 3,
    RCODE_INVALID_FILE_CONTENT = 4
};

class CmdlineParser
{
  public:
    struct Results
    {
	unsigned long long balance;
	int n;
	vector< Gift > gifts;

	Results()
	:   balance( 0 )
	,   n( 0 )
	    {
		gifts.reserve( 1000 );
	    }
    };
    
    static RCode parse( int argc, char** argv, Results& r );
};

#endif
