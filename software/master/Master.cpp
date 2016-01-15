/**
 * @file      Master.cpp
 * @author    George Andrew Brindeiro
 * @date      07/08/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#include <Master.h>
#include <Config.h>
#include <Communicator.h>
#include <ProcessLogger.h>

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <curses.h>

map< string, vector<Communicator*> > connections;

int main(int argc, char* argv[])
{
    // Read processes and connection information from config
    Config master_cfg("master.config");

    // Processes are keys in master config
    vector<string> processes = master_cfg.keys();

    // Iterate through processes to create connections
    for(vector<string>::iterator ip = processes.begin(); ip != processes.end(); ip++)
    {
        // Process name
        string from_process = *ip;
        
        LOG(LEVEL_DEBUG) << "Creating connections for '" << from_process << "' module...";
        
        // Number of connections
        int num_connections = master_cfg.getSize(from_process);
        
        LOG(LEVEL_DEBUG) << "Number of connections found: " << num_connections;
        
        // Resize connections vector
        connections[from_process].resize(num_connections);
        
        // Create connections
        for(int i = 0; i < num_connections; i++)
        {
            string to_process = master_cfg.get(from_process,i);
            
            LOG(LEVEL_DEBUG) << "#" << i << ": " << from_process << "->" << to_process;
            
            connections[from_process][i] = new Communicator(from_process, to_process, WRITE, true);
        }
    }
    
    // Spawn processes
    for(vector<string>::iterator ip = processes.begin(); ip != processes.end(); ip++)
    {
        // Process Name
        string process = *ip;
        
        // Get lowercase version of process name for directory name
        string directory = process;
        directory[0] = tolower(directory[0]);
        
        // Get current directory
        char cwd[256];
        getcwd(cwd, 255);
        
        LOG(LEVEL_DEBUG) << "Current Path: " << cwd << endl;
        
        // Get location of the process
        string path = cwd + string("/../") + directory + string("/");
        
        LOG(LEVEL_DEBUG) << "Process path: " << path;
        
        // Corresponding execution command
        string command = string("gnome-terminal --working-directory=") + path + string(" --command=\"./") + process + string("\"");
        
        LOG(LEVEL_DEBUG) << command.c_str();
        LOG(LEVEL_INFO) << "Executing '" << process << "'";
        system(command.c_str());
    }
    
    // Wait in infinite loop? Launch GUI?    
    // Create GUI for Master.cpp including visualization
    // Include field and ball visualization
    // One GUI that will manage the whole system

    //while(true){ std::cout << "Beep" << std::endl; sleep(1);}
    
    // Clean exit?
}
