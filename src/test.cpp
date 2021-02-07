#include <iostream>

#include "./test/testUtils.h"

using std::cout;
using std::endl;

int main()
{
    if ( TestUtils::testConvertToTime() )
    {
        cout << endl;
        cout << "=================================================================" << endl;
        cout << "-------------- Convert to Time  Tested Succesfully --------------" << endl;
        cout << "=================================================================" << endl;
        cout << endl;
    }

    if ( TestUtils::testProgressBar() )
    {
        cout << endl;
        cout << "=================================================================" << endl;
        cout << "---------------- Progress Bar Tested Succesfully ----------------" << endl;
        cout << "=================================================================" << endl;
        cout << endl;
    }

    if ( TestUtils::testGetStream() )
    {
        cout << endl;
        cout << "=================================================================" << endl;
        cout << "----------------- Get Stream Tested Succesfully -----------------" << endl;
        cout << "=================================================================" << endl;
        cout << endl;
    }

    return 0; 
}