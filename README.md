# codingforcompanyP
solutions for coding challenges from company P.

On Windows:

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
