#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> Indicies;

static void printString( string& str, Indicies& indicies, int n );
static void printUsage();
static const int MIN_NUM_ARGC = 2;
int main( int argc, char** argv )
{
    if( argc < MIN_NUM_ARGC )
    {
	printUsage();
	return 1;
    }
    
    if( strcmp( argv[1], "-h" ) == 0
	|| strcmp( argv[1], "--help" ) == 0 )
    {
	printUsage();
	return 0;
    }
    string str = argv[1];
    
    Indicies xIndicies;

    for( int i = 0; i < str.length(); ++i )
    {
	if( str[i] == 'X' )
	{
	    xIndicies.push_back( i );
	    //every X will be replaced by '0' first
	    str[i] = '0';
	}
    }
    if( xIndicies.empty() )
    {
	cout << str << endl;
	return 0;
    }
    
    printString( str, xIndicies, 0 );
    return 0;
}

void flipChar( string& str, int index )
{
    str[index] = str[index] == '0' ? '1' : '0';
}

/**
 *@brief This function is to recursively print out combinations where we replace X with 0 and 1.
 *       The main idea is to print all combinations in a particular sequence where there is only 1 character difference
 *       between the ith combination and the i+1 th combination ( 0<=i<=2^(number of Xs)-1 ).
 *       The motivation is to optimize time complexity. Note there are multiple sequences that satisfy the requirement.  
 *       The time complexity of the algo is O( n*2^k ), where n is the length of the input string, k is the number of Xs. 
 */
void printString( string& str, Indicies& indicies, int n )
{
    //Flip character starting from the last 'X' while keeping other characters unchanged.
    if( n == indicies.size()-1 )
    {	
	cout << str << endl;
	flipChar( str, indicies[n] );
	cout << str << endl;
	return;
    }
    
    printString( str, indicies, n+1 );
    flipChar( str, indicies[n] );
    printString( str, indicies, n+1 );
}

void printUsage()
{
    cout << "Usage: " << endl;
    cout << "main -h" << endl;
    cout << "main <string>" << endl;
    
}
