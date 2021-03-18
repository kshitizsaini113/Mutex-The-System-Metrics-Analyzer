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

    std::cout<<"PID\tRAM Size\tProcessUP\tSystemUP\tCPU Percent\tUser\tCommand"<<std::endl;

    for(int i=0; i<processId.size(); i++)
    {
        std::cout<<processId.at(i)<<"\t";
    }

    return 0;
}