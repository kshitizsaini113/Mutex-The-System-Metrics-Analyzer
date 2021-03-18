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
        static string getCommand( string processId );
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


        static int getOsName();
        // This function works with /etc/os-release and parses the line containing the Operating System Name.


        static string getCpuStatistics(vector<string> values1, vector<string> values2);
        // This function calculates CPU usage, either overall or for a selected core. CPU stats are time-dependent,
        // so the only way to get valid CPU statistics are by specifying a time interval. Therefore, the function
        // accepts two arguments previousTime and currentTime.

        static int getNumberOfCores();
        // This function works with /proc/cpuinfo file and, iterates over all the fields from the files and
        // returns the numbers of cores present in our device. The total number of cores of cpu is stored in 
        // /proc/cpuinfo file and the data is located under cpu cores field.

        static float getSystemActiveCpuTime(vector<string> values);
        // This function works with getSystemCpuPercent function to fetch a specific core output and filters
        // the values based on the index and returns the active cpu time.

        static float getSystemIdleCpuTime(vector<string> values);
        // This function works with getSystemCpuPercent function to fetch a specific core output and filters
        // the values based on the index and returns the idle cpu time.

};

vector<string> ProcessParcer::getProcessIdList()
{
    vector<string> processList;
    DIR* directory;
    // Initializes the basic variables required for the functionality. Here the variable is a directory pointer so
    // we will open the directory and parse the files in it using the directory pointer.

    if(!(directory = opendir("/proc")))
    {
    // Open the directory and throws an error if something is now working fine. 
        throw::runtime_error(strerror(errno));
    }

    while ( dirent* internalFile = readdir(directory) )
    {
    // Uses the dirent structure to read the files inside the directory and uses the loop to iterate through
    // each of the files in the directory.
        
        if ( internalFile->d_type != DT_DIR )
        {
        // Skips the file and continue to next iteration id the file is not a directory as we need only the 
        // directories to process.
            
            continue;
            // Continues to the next iteration.
        }

        if(std::all_of( internalFile->d_name, internalFile->d_name + std::strlen(internalFile->d_name), [](char c){ return std::isdigit(c); } ))
        {
        // Here, we are using the all_of function which checks for a condition for all the files from as specified 
        // in the arguments from first tolast using the given condition for which we have passed the function as an 
        // argument.
        // The function parsed as the argument iterates through the name of the file and checks if each of the character
        // in the directory name is a number.

            processList.push_back(internalFile->d_name);
            // Pushes the directory names in the vector form which are satisfying the condition so that we can access
            // the files in a vector form.
        }
    }

    if(closedir( directory ))
    {
    // Closes the directory and throw a runtime error is something unexpected is observed.
        throw runtime_error(strerror(errno));
    }

    return processList;
    // Returns the vector which contains the list ofall the process id.
}

int ProcessParcer::getNumberOfCores()
{
    string fetchedLine;
    string fieldName = "cpu cores";
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + Path::cpuinfo() ) );
    // Gets the stream of file from the getStream function.

    while( getline( fileStream, fetchedLine ) )
    {
        // Gets a new line everytime and iterates over the file till the field VmData is found.
        if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
        {
        // Processes the given line and stores it in a vector of strings by accessing the element
        // over the index 3 and further converting return the value by converting the string to int.

            istringstream buffer( fetchedLine );
            istream_iterator<string> begin( buffer ), end;
            vector<string> values( begin, end );
            // Processes the given line and stores it in a vector of strings by accessing the element.

            return stoi(values[3]);
            // Returns the number of cores of cpu.
        }
    }

    return 0;
    // Returns 0 if something unexpected has occured.
}

vector<string> ProcessParcer::getSystemCpuPercent( string coreNumber )
{
    string fetchedLine;
    string fieldName = "cpu" + coreNumber;
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + Path::statPath() ) );
    // Gets the stream of file from the getStream function.

    while( getline( fileStream, fetchedLine ) )
    {
        // Gets a new line everytime and iterates over the file till the field VmData is found.
        if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
        {
        // Processes the given line and stores it in a vector of strings by accessing the element
        // over the index 3 and further converting return the value by converting the string to int.

            istringstream buffer( fetchedLine );
            istream_iterator<string> begin( buffer ), end;
            vector<string> values( begin, end );
            // Processes the given line and stores it in a vector of strings by accessing the element.

            return values;
            // Returns the number of cores of cpu.
        }
    }

    return ( vector<string>() );
    // Returns an empty vector is noentry is found for the given core number.
}

float ProcessParcer::getSystemActiveCpuTime( vector<string> values )
{
    return ( stof(values[S_USER]) + 
             stof(values[S_NICE]) + 
             stof(values[S_SYSTEM]) + 
             stof(values[S_IRQ]) + 
             stof(values[S_SOFTIRQ]) + 
             stof(values[S_STEAL]) + 
             stof(values[S_GUEST]) + 
             stof(values[S_GUEST_NICE]) );
}

float ProcessParcer::getSystemIdleCpuTime(vector<string> values)
{
    return ( stof(values[S_IDLE]) + 
             stof(values[S_IOWAIT]) );
}

int ProcessParcer::getTotalThreads()
{
    string fetchedLine;
    int numberOfThreads = 0;
    string fieldName = "Threads:";
    vector<string> processIdList = ProcessParcer::getProcessIdList();
    // Initializes the basic variables required for the functionality.

    for(int process=0; process<processIdList.size(); process++)
    {
        string pid = processIdList[process];

        ifstream fileStream = Util::getStream( ( Path::basePath() + pid + Path::statusPath() ) );
        // Gets the stream of file from the getStream function.

        while( getline( fileStream, fetchedLine ) )
        {
            // Gets a new line everytime and iterates over the file till the field VmData is found.
            if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
            {
            // Processes the given line and stores it in a vector of strings by accessing the element
            // over the index 1 and further increasing the number of threads.

                istringstream buffer( fetchedLine );
                istream_iterator<string> begin( buffer ), end;
                vector<string> values( begin, end );
                // Processes the given line and stores it in a vector of strings by accessing the element.

                numberOfThreads += stoi(values[1]);
                // Increases the number of threads.

                break;
                // Once the thread field is encountered, no reason to search the file further so break
                // the current iteration and procees to next process.
            }
        }
    }

    return numberOfThreads;
}

string ProcessParcer::getProcessUpTime( string processId )
{
    string fetchedLine;
    float processUpTime = 0;
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + processId + "/" + Path::statPath() ) );
    // Gets the stream of file from the getStream function.

    getline( fileStream, fetchedLine );
    // The file is a single line file so we will fetch the file in a single line.

    istringstream buffer( fetchedLine );
    istream_iterator<string> begin( buffer ), end;
    vector<string> values( begin, end );
    // Processes the given line and stores it in a vector of strings by accessing the element.

    processUpTime = float( stof( values[13] ) / sysconf(_SC_CLK_TCK) );
    // values[13] <-> Process UpTime
    //
    // Amount of time that this process has been scheduled in user mode, measured in clock ticks
    // (divide by sysconf(_SC_CLK_TCK)).  This includes guest time, guest_time (time spent running
    // a virtual CPU), so that applications that are not aware of the guest time field
    // do not lose that time from their calculations.
    //
    // REFRENCE: https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat


    return to_string( processUpTime );
    // Return the Process Up Time in form of string.
}

long int ProcessParcer::getSystemUpTime()
{
    string fetchedLine;
    long int systemUpTime;
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + Path::upTimePath() ) );
    // Gets the stream of file from the getStream function.

    getline( fileStream, fetchedLine );
    // The file is a single line file so we will fetch the file in a single line.

    istringstream buffer( fetchedLine );
    istream_iterator<string> begin( buffer ), end;
    vector<string> values( begin, end );
    // Processes the given line and stores it in a vector of strings by accessing the element.

    systemUpTime = stoi( values[0] );
    // Fetches the system up time from the line fetched which was present at the first index.

    return systemUpTime;
    // Return the system up time for the system.
}

string getCpuStatistics(vector<string> values1, vector<string> values2)
{
    float activeTime = ProcessParcer::getSystemActiveCpuTime(values2) - ProcessParcer::getSystemActiveCpuTime(values1);
    // Calculates the system active cpu time by observing two different vector values fetched from
    // the getSystemCpuPercent and applying the getSystemActiveCpuTime filter.
    float idleTime = ProcessParcer::getSystemIdleCpuTime(values2) - ProcessParcer::getSystemIdleCpuTime(values1);
    // Calculates the system idle cpu time by observing two different vector values fetched from
    // the getSystemCpuPercent and applying the getSystemIdleCpuTime filter.
    float totalTime = activeTime + idleTime;
    // Sums up the activeTime and idleTime to calculate totalTime

    float cpuStats = 100.0*(activeTime / totalTime);
    // Uses the formula to calculate CPU Stats.

    return to_string(cpuStats);
    // Returning CPU Stats in form of a string.
}

int ProcessParcer::getNumberOfRunningProcesses()
{
    string fetchedLine;
    int numberOfRunningProcesses = 0;
    string fieldName = "procs_running";
    // Initializes the basic variables required for the functionality.

    ifstream fileStream = Util::getStream( ( Path::basePath() + Path::statPath() ) );
    // Gets the stream of file from the getStream function.

    while( getline( fileStream, fetchedLine ) )
    {
        // Gets a new line everytime and iterates over the file till the field VmData is found.

        if( fetchedLine.compare( 0, fieldName.size(), fieldName ) == 0 )
        {
        // Processes the given line and stores it in a vector of strings by accessing the element
        // over the index 1 and further increasing the number of running processes.

            istringstream buffer( fetchedLine );
            istream_iterator<string> begin( buffer ), end;
            vector<string> values( begin, end );
            // Processes the given line and stores it in a vector of strings by accessing the element.

            numberOfRunningProcesses += stoi(values[1]);
            // Increases the number of processes.

            break;
            // Once the process field is encountered, no reason to search the file further.
        }
    }

    return numberOfRunningProcesses;
}