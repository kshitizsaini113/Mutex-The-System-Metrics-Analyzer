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

        static bool testProgressBar()
        {
            assert( Util::getProgressBar("0") == "0% |                                                  0%/100%");
            assert( Util::getProgressBar("5") == "0% |||                                                5%/100%");
            assert( Util::getProgressBar("10") == "0% ||||||                                             10%/100%");
            assert( Util::getProgressBar("30") == "0% ||||||||||||||||                                   30%/100%");
            assert( Util::getProgressBar("50") == "0% ||||||||||||||||||||||||||                         50%/100%");
            assert( Util::getProgressBar("70") == "0% ||||||||||||||||||||||||||||||||||||               70%/100%");
            assert( Util::getProgressBar("90") == "0% ||||||||||||||||||||||||||||||||||||||||||||||     90%/100%");
            assert( Util::getProgressBar("100") == "0% |||||||||||||||||||||||||||||||||||||||||||||||||| 100%/100%");

            return true;
        }

        static bool testGetStream()
        {
            system("touch /tmp/testFile.txt");
            Util::getStream("/tmp/testFile.txt");

            return true;
        }

};