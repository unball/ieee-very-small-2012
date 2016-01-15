/**
 * @file      Communicator.h
 * @author    George Andrew Brindeiro
 * @date      24/10/2010
 *
 * @attention Copyright (C) 2010
 * @attention UnBall Robot Soccer Team
 */

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include <ProcessLogger.h>

using namespace std;
namespace bip = boost::interprocess;
namespace b = boost;

// We need to define a string implementation that is compatible with Boost Interprocess...
// http://stackoverflow.com/questions/4278627/c-boostinterprocess-simple-application/4540790#4540790
#include <boost/interprocess/containers/string.hpp>

typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> msg_string;

#define WRITE	true
#define READ	false

#define IN(varName,in)		(make_pair(varName,in))
#define OUT(varName,out)	(make_pair(varName,out))

/**
 * @brief Comunicação inter-processos de módulos de software UnBall
 *
 * Communicator é a classe responsável pela criação de um elo de comunicação
 * confiável para transmissão de mensagens, configurações e dados entre os
 * diversos módulos de software da UnBall.
 *
 */
class Communicator
{
public:
    Communicator () {}

    /**
     * @brief Constructor
     * @param writer 	Name of the process writing to the communication channel
     * @param reader	Name of the process reading to the communication channel
     * @param mode		Mode to be used: READ or WRITE (see macros above)
     * @param master	Flag to signal if master started this communicator and should cleanup
     */
    Communicator (const string & writer, const string & reader, bool mode, bool master = false, int size = 2048);

    /**
     * @brief Destructor
     */
    ~Communicator ();

    /**
     * @brief Connect to communication channel
     * @param name
     * @return String stream to which apply the insertion operator
     */
    bool connect (const string & name, bool mode, bool master = false, int size = 2048);

    bool disconnect ();

    void create (const string varName);

    void destroy (const string varName);

    string read (const string varName);

    void write (const string varName, const string & value);

    bool ready ();

    void done ();

    void operator>> (const pair<string, string *> varName_in);

    void operator<< (const pair<string, string> varName_out);

    bool connected ()
    {
        return isConnected;
    }

    string & name ()
    {
        return connectionName;
    }

    bool getMode ()
    {
        return mode;
    }

    bip::managed_shared_memory msm;

private:
    // Disallowing copy/assignment
    Communicator (const Communicator &);
    Communicator & operator= (const Communicator & other);

    bool isConnected;
    bool mode;
    bool master;

    string connectionName;
    string writer;
    string reader;

    bip::interprocess_mutex dataMutex;	// trava do tipo Mutex anônimo.
};

#endif // COMMUNICATOR_H

