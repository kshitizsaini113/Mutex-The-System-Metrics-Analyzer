#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <string>
// Importing the required headers.

using std::string;
// Importing the contents of string part of std namespace.

enum CPU_States
{
    S_USER = 1,
    S_NICE,
    S_SYSTEM,
    S_IDLE,
    S_IOWAIT,
    S_IRQ,
    S_SOFTIRQ,
    S_STEAL,
    s_GUEST,
    S_GUEST_NICE
};
// Enumerated DataType for CPU States

class Path
{
    // Defining the path functions so that we need to define the path again and again and it become 
    // easy to access the path in form of functions and make the documentation easy.
    // 
    // All the functions are static as we need not to create extra instances of the functions, because
    // we need not to create multiple instances.

    public:

        static string basePath()
        {
            return "/proc/";
        }

        static string cmdPath()
        {
            return "/cmdline";
        }

        static string cpuinfo()
        {
            return "cpuinfo";
        }

        static string statusPath()
        {
            return "/status";
        }

        static string statPath()
        {
            return "stat";
        }

        static string upTimePath()
        {
            return "uptime";
        }

        static string memInfoPath()
        {
            return "meminfo";
        }

        static string versionPath()
        {
            return "version";
        }

        static string passwdFile()
        {
            return "/etc/passwd";
        }

};

#endif