# codingforcompanyP
solutions for coding challenges from company P.

On Windows:

Challenge 2:

To build:
use GNU x86 win32 compiler/linker:
cl /EHs src/main.cpp src/gift.cpp src/cmdline_checker.cpp src/pick_gifts.cpp

To run:
main.exe <file path> <balance> <num of people>

Example:
cd build;
main.exe ../test/test_file.txt 2000
main.exe ../test/test_file.txt 2000 3
main.exe ../test/test_file.txt 2000 4

This solution allows for N people where N >=2 if unspecified.
The time complexity in terms of number of available gifts (k) and number of people (n) is:
n == 2 : O( k   * log(k) )
n == 3 : O( k^2 * log(k) )
Overall: O( k^(n-1) * log(k) )
======================================================================
Challenge 3:

To build:
use GNU x86 win32 compiler/linker:
cl /EHs src/main.cpp

To run:
main.exe <string>

Example:
cd build;
main.exe 0X

The time complexity of the algo is O( n*2^k ), where n is the length of the inptu string and k is the number of Xs. 


