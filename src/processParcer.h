#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
// Importing the required pre-defined headers.

#include "utils.h"
#include "constants.h"
// Inporting the user-defined headers.

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::istream_iterator;
using std::stof;
using std::strerror;
// Using the specific part of std namespace rather than including the whole namespace.

class ProcessParcer
{
    public:
        static string getProcessCommand( string processId );
        // This function is used to retrive the base command from which the process was executed.


        static vector<string> getProcessIdList();
        // This function works with the /proc directory in our Linux Architecture and uses the 
        // directory pointer to check the directory and then further parses the Process Id and stores
        // them in form of string in a vector.


        static string getProcessRamPercent( string processId );
        // This function works with the status file from the PID folder, iterates over all the feilds
        // from the files and returns the RAM Size from the file. 
        // The RAM data usage is stored in /proc/<PID>/status file and the data is located under 
        // VmData feild and stores the memory usage in kilobytes.

        static long int getSystemUpTime();
        // This function works with the file /proc/uptime, and fetches the first value from the file
        // which contains the uptime of our system.

        static string getProcessUpTime( string processId );
        // This function works with the stat file from the PID folder, this file contains the data
        // in a single line and contains various data as defined in docs folder.
        // The process uptime is stored in /proc/<PID>/stat file and the process uptime is measured in
        // clock tiks. It needs to be devided with the system clock speed for the time to be measured
        // in seconds.

        static string getProcessUser( string processId );
        // This function works first with the status file and then with the passwd file. It first 
        // fetches the UID from status file and stores it in a variable.
        // Further it processes the data fetched with the lines from passwd file to check for the uid
        // and returns the username from the file.

        static string getProcessCpuPercent( string processId );
        // This function works with the stat file from the proc folder, iterates over all the fields from the files and
        // returns the System CPU Percent from the file. The cpu percent is stored in /proc/<PID>/stat file and the
        // data is located under the single line.


        static vector<string> getSystemCpuPercent( string coreNumber = "" );
        // This function works with the stat file from the proc folder, iterates over all the fields from the files and
        // returns the System CPU Percent from the file. The cpu percent is stored in /proc/stat file and the data is
        // located under cpu field.


        static float getSystemRamPercent();
        // This function works with the /proc/memInfo file which contains the three values for the available
        // memory, free memory and buffer memory. The system ram pecent is calculated by performing the
        // operation on the values fetched.


        static string getSystemKernelVersion();
        // This function works with /proc/version file and returns the kernel version for the current operating
        // system in which the program is running.


        static int getTotalThreads();
        // This function works with the total threads rather than working with a specific process. Here, we open
        // the PID folder for each process and reads the thread count for each of the following process.


        static int getTotalNumberOfProcesses();
        // This function works with the /proc/stat file and, iterates over all the fields from the files and
        // returns the Total Numbers of processes from the file. The total number of processes is stored in 
        // /proc/stat file and the data is located under process field.


        static int getNumberOfRunningProcesses();
        // This function works with the /proc/stat file and, iterates over all the fields from the files and
        // returns the Total Numbers of running processes from the file. The total number of processes is stored in 
        // /proc/stat file and the data is located under procs_running field.


        static string getOsName();
        // Thi function works with /etc/os-release and parses the line containing the Operating System Name.


        static string getCpuStatistics(vector<string> values1, vector<string> values2);
        // This function calculates CPU usage, either overall or for a selected core. CPU stats are time-dependent,
        // so the only way to get valid CPU statistics are by specifying a time interval. Therefore, the function
        // accepts two arguments previousTime and currentTime.

};

string ProcessParcer::getProcessCpuPercent( string processId )
{
    string fetchedLine;
    string value;
    float processCpuPercent;
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + processId + "/" + Path::statPath() ) );
    // Gets the stream of file from the getStream function.

    getline( fileStream, fetchedLine );
    // The file is a single line file so we will fetch the file in a single line.

    istringstream buffer( fetchedLine );
    istream_iterator<string> begin( buffer ), end;
    vector<string> values( begin, end );
    // Processes the given line and stores it in a vector of strings by accessing the element.

    float utime = stof(ProcessParcer::getProcessUpTime( processId ));
    float uptime = ProcessParcer::getSystemUpTime();
    // Uses the pre-defined functions to get the values of variables like process uptime and system
    // uptime.

    float stime = stof( values[14] );
    // Measures the amount of time that this process has been scheduled in kernel mode, measured in
    // clock ticks (divide by sysconf(_SC_CLK_TCK)).
    float cutime = stof( values[15] );
    // Measures the amount of time that this process's waited-for children have been scheduled in
    // user mode, measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    float cstime = stof( values[16] );
    // Measures the amount of time that this process's waited-for children have been scheduled in
    // kernel mode, measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    float starttime = stof( values[21] );
    // Measures the time the process started after system boot. The value is expressed in clock ticks
    // (divide by sysconf(_SC_CLK_TCK)).

    float freq = sysconf( _SC_CLK_TCK );
    // Stores the system clock tick frequency. Mostly the System clock tick frequency is 100.

    float totaltime = utime + stime + cutime + cstime;
    // Calculates the total time while the process is running in CPU. The time is in system tick freq.
    float processTotalTime = uptime - ( starttime / freq );
    // Calculates the seconds elapsed since the process was started first.

    processCpuPercent = 100 * ( ( totaltime / freq ) / processTotalTime );
    // Calculates the cpu percent for the current process.

    return to_string( processCpuPercent );
    // Returns the process cpu percent in form of string.
}

string ProcessParcer::getProcessCommand( string processId )
{
    string fetchedLine;
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream(( Path::basePath() + processId + Path::cmdPath()));
    // Gets the stream of file from the getStream function.

    std::getline(fileStream, fetchedLine);
    // Fetches the line from the file.

    return fetchedLine;
    // Return the process command which was fetched.
}

string ProcessParcer::getSystemKernelVersion()
{
    string fetchedLine;
    string fieldName = "Linux version ";
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + Path::versionPath() ) );
    // Gets the stream of file from the getStream function.

    while( getline( fileStream, fetchedLine ) )
    {
    // Gets a new line everytime and iterates over the file till the accepted fields are fetched.

        if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
        {
        // Processes the given line and stores it in a vector of strings by accessing the element
        // over the index 2.

            istringstream buffer( fetchedLine );
            istream_iterator<string> begin( buffer ), end;
            vector<string> values( begin, end );
            // Processes the given line and stores it in a vector of strings by accessing the element.

            return values[2];
            // Returns the SystemKernelVersion.
        }
    }

    return "";
}

string ProcessParcer::getOsName()
{
    string fetchedLine;
    string fieldName = "PRETTY_NAME=";
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( "/etc/os-release" ) );
    // Gets the stream of file from the getStream function.

    while( getline( fileStream, fetchedLine ) )
    {
    // Gets a new line everytime and iterates over the file till the accepted fields are fetched.

        if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
        {
        // Processes the given line and fetches the os version from the line.

            size_t value = fetchedLine.find( "=" );
            value++;
            // Find the index at which the = value is present and stores it's index.

            string osVersion = fetchedLine.substr( value );
            // Fetch the os name from the substring.
            osVersion.erase( remove(osVersion.begin(), osVersion.end(), '"'), osVersion.end() );
            // Removes the " from the parsed string so as to fetch only the OS Version.

            return osVersion;
            // Returns the OS Version.
        }
    }

    return "";
}
