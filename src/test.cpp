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

    return 0; 
}