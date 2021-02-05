#ifndef __UTIL__
#define __UTIL__

#include <string>
#include <fstream>
// Importing the required headers.

using std::string;
using std::ifstream;
using std::to_string;
using std::runtime_error;
// Using the specific part of std namespace rather than including the whole namespace.

class Util
{
    // Creating a Util class to create the general functions to reduce the code redundancy and access
    // the reused code again and again.
    // 
    // All the functions are static as we need not to create extra instances of the functions, because
    // we need not to create multiple instances.

    public:

        static string convertToTime( long int epoch_time );
        // This function converts the epoch time (time format for linux which is in seconds) to hour,
        // minutes and seconds.

        static string getProgressBar( string percent );
        // This function displays the progress bar from 0% to 100% using bars(|), each bar represents
        // 2% progress. 

        static ifstream getStream( string path );
        // Checks if a stream exists on a given path and returns the status for the current PID, and
        // returns the refrence location for the file.

};

#endif