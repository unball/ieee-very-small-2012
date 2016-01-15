/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 27-09-2012
*/

#include "rsvs.h"

int main (int args, char* argv[])
{
    RSVS rsvs;
    if (!rsvs.Initialized())
        return 0;

    for(;;)
    {
        if (!rsvs.Run()) break;
        //other stuff
    }

    return 0;
}

