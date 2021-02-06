#include <iostream>
#include <assert.h>

#include "../utils.h"

class TestUtils
{
    public:
        static bool testConvertToTime()
        {
            assert( Util::convertToTime(0) == "0:0:0");
            assert( Util::convertToTime(59) == "0:0:59");
            assert( Util::convertToTime(60) == "0:1:0");
            assert( Util::convertToTime(61) == "0:1:1");
            assert( Util::convertToTime(3599) == "0:59:59");
            assert( Util::convertToTime(3600) == "1:0:0");
            assert( Util::convertToTime(3601) == "1:0:1");

            return true;
        }
};