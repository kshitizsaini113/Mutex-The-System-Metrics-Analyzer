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

string Util::convertToTime( long int epoch_time )
{
    long minutes = epoch_time / 60;
    long hours = minutes / 60;
    long seconds = int( epoch_time % 60 );
    minutes = ( minutes % 60 );
    // Converts the epoch time to minutes, hours and seconds by performing the arithmetic operations.

    string time_string = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    // Converts the stored resut to string.

    return time_string;
    // Returns the converted time as string.
}

string Util::getProgressBar( string percent )
{
    string progress_bar = "0% ";
    int size = 50;
    int boundaries = ( ( stoi(percent) * size ) / 100);
    // Converts the percentage to boundary so as to use the bounday accordingly.

    for( int i = 0; i < size; i++ )
    {
        if( i<= boundaries )
        {
            progress_bar += "|";
        }
        else
        {
            progress_bar += " ";
        }
    }
    // Stores the result as either " " or "|" to display the characterstics accordingly.

    progress_bar += " " + percent.substr( 0, 5 ) + "%/100%";
    // Adds the final result.

    return progress_bar;
    // Returnd the full fledged progress bar.
}

ifstream Util::getStream( string path )
{
    ifstream file_present(path);
    // Opens the path and stored the refrence in stream variable.

    if( !file_present )
    {
        throw runtime_error( "Non - Existing PID" );
    }
    // Prompts a runtime error if the the file isn't present at the path.

    return file_present;
    // Returns the refrence to the file.
}

#endif