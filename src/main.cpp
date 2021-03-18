#include <iostream>
#include "processParcer.h"
// Importing the required headers.

#include "processParcer.h"

using std::cout;
using std::string;
using std::endl;
// Using the specific part of std namespace rather than including the whole namespace.

int main()
{
    vector <string> processId = ProcessParcer::getProcessIdList();

    cout << "SYSTEM DETAILS" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "OS Installed: \t\t\t" + ProcessParcer::getOsName() << endl;
    cout << "Kernel Version: \t\t" + ProcessParcer::getSystemKernelVersion() << endl;
    cout << "Number of CPU Core: \t\t" + to_string(ProcessParcer::getNumberOfCores()) <<endl;
    cout << "System Up Time: \t\t" + to_string(ProcessParcer::getSystemUpTime()) + " sec" << endl;
    cout << "System Ram Usage: \t\t" + to_string(ProcessParcer::getSystemRamPercent()) + "%" << endl;
    cout << "Total Processes: \t\t" + to_string(ProcessParcer::getTotalNumberOfProcesses()) << endl;
    cout << "Total Threads: \t\t\t" + to_string(ProcessParcer::getTotalThreads()) << endl;
    cout << "Total Running Process: \t\t" + to_string(ProcessParcer::getNumberOfRunningProcesses()) << endl;

    cout << "====================================================================================================" << endl;

    cout << endl << endl << endl;

    cout<<"PID\tRAM Size(GB)\tProcessUP(s)\tCPU Percent(%)\tUser"<<endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    for(int i=0; i<processId.size()-1; i++)
    {
        cout<<processId.at(i)<<"\t";
        cout<<ProcessParcer::getProcessRamPercent(processId.at(i))<<"\t";
        cout<<ProcessParcer::getProcessUpTime(processId.at(i))<<"\t";
        cout<<ProcessParcer::getProcessCpuPercent(processId.at(i))<<"\t";
        cout<<ProcessParcer::getProcessUser(processId.at(i))<<endl;
        // cout<<ProcessParcer::getProcessCommand(processId.at(i))<<endl<<endl;
    }

    return 0;
}