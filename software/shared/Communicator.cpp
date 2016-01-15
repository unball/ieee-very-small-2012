/**
 * @file      Communicator.cpp
 * @author    George Andrew Brindeiro
 * @date      24/10/2010
 *
 * @attention Copyright (C) 2010
 * @attention UnBall Robot Soccer Team
 */

#include <Communicator.h>

Communicator::Communicator (const string & writer, const string & reader, bool mode, bool master, int size)
{
	// Name connection (shared memory pool) after writer/reader
	string connectionName = writer + "_" + reader;
	// Remove old shared memory using same identifier
	if (master)
	{
		LOG (LEVEL_DEBUG) << "Cleaning up old shared memory...";
		bip::shared_memory_object::remove (connectionName.c_str ());
	}
	// Try to open a connection and initialize identifier variables
	if (!connect (connectionName, mode, master))
	{
		LOG (LEVEL_ERROR) << "Could not open connection " << connectionName;
	}
	else
	{
		this->writer = writer;
		this->reader = reader;
		this->mode = mode;
		this->master = master;
	}
}

Communicator::~Communicator ()
{
	// Master is responsible for managing the shared memory allocated
	if (master)
	{
		disconnect ();
	}
}

bool Communicator::connect (const string & connectionName, bool mode, bool master, int size)
{
	try
	{
		if (mode == WRITE)
		{
			// If anything has to be done only in write mode, do it here
		}
		else if (mode == READ)
		{
			// If anything has to be done only in read mode, do it here
		}
		// Create or open shared memory
		if (master)
		{
			LOG (LEVEL_VERBOSE) << "Master creating managed shared memory...";
			msm = bip::managed_shared_memory (bip::create_only, connectionName.c_str (), size);
		}
		else
		{
			LOG (LEVEL_VERBOSE) << "Opening managed shared memory...";
			msm = bip::managed_shared_memory (bip::open_only, connectionName.c_str ());
		}
		// Initialize connectionName
		this->connectionName = connectionName;
		// Turn 'isConnected' flag on
		isConnected = true;
		LOG (LEVEL_VERBOSE) << "Checking if control variable exists...";
		// Check if control variable exists
		// Search for string variable with string id "connectionName"
		std::pair<msg_string *, std::size_t> p = msm.find<msg_string> (connectionName.c_str ());
		msg_string * str = p.first;
		LOG (LEVEL_VERBOSE) << "Done.";
		// Check if not master for warning
		if (!master)
		{
			LOG (LEVEL_VERBOSE) << "Not master, shouldn't create control variable";
		}
		// Check if variable already exists
		if (str)
		{
			LOG (LEVEL_VERBOSE) << "Control variable '" << connectionName << "' already exists!";
			LOG (LEVEL_VERBOSE) << connectionName << " = " << *str;
		}
		// If control variable doesn't exist, and you're master, create it
		if (!str && master)
		{
			this->create (connectionName.c_str ());
			this->write (connectionName.c_str (), "WRITE");
		}
	}
	catch (...)
	{
		// If anything fails (i.e. an exception is thrown), remove shared memory
		disconnect ();
		throw;
	}
	return isConnected;
}

bool Communicator::disconnect ()
{
	// Throw error if shared memory cannot be removed for some reason
	if (!bip::shared_memory_object::remove (connectionName.c_str ()))
	{
		LOG (LEVEL_FATAL) << "Could not remove shared memory object " << connectionName.c_str () << "!";
		return false;
	}
	// Reset connectionName
	this->connectionName = "";
	// Turn 'isConnected' flag off
	isConnected = false;
	return true;
}

void Communicator::create (const string varName)
{
	// Create and initialize string variable with string id "varName" to empty string
	msg_string * created = msm.construct<msg_string> (varName.c_str ()) ("", msm.get_segment_manager ());
	if (created)
	{
		LOG (LEVEL_DEBUG) << "Created variable " << varName;
	}
	else
	{
		LOG (LEVEL_ERROR) << "Could not create variable " << varName;
	}
}

void Communicator::destroy (const string varName)
{
	// Destroy string variable with string id "varName"
	msm.destroy<string> (varName.c_str ());
	LOG (LEVEL_DEBUG) << "Destroyed variable " << varName;
}

string Communicator::read (const string varName)
{
	// Use mutex to avoid simultaneous write/read
	bip::scoped_lock<bip::interprocess_mutex> lock (dataMutex);
	// Search for string variable with string id "varName"
	std::pair<msg_string *, std::size_t> p = msm.find<msg_string> (varName.c_str ());
	msg_string * str = p.first;
	// If search returns valid pointer...
	if (str)
	{
		// Variable exists, return its content
		LOG (LEVEL_DEBUG) << "Read " << varName << "=" << *str;
		return string (str->c_str ());
	}
	else
	{
		// Variable not found, return empty string
		LOG (LEVEL_ERROR) << "Variable " << varName << " not found!";
		return string ("");
	}
}

void Communicator::write (const string varName, const string & value)
{
	// Use mutex to avoid simultaneous write/read
	bip::scoped_lock<bip::interprocess_mutex> lock (dataMutex);
	// Search for string variable with string id "varName"
	std::pair<msg_string *, std::size_t> p = msm.find<msg_string> (varName.c_str ());
	msg_string * str = p.first;
	// If search returns valid pointer...
	if (str)
	{
		// Variable exists, write "value" as its content
		str->assign (value.c_str ());
		LOG (LEVEL_DEBUG) << "Wrote " << varName << "=" << *str;
	}
	else
	{
		// Variable not found, do nothing
		LOG (LEVEL_ERROR) << "Variable " << varName << " not found!";
		LOG (LEVEL_ERROR) << "Variable " << varName << " could not be written.";
	}
}

bool Communicator::ready ()
{
	string readyFlag = read (string (connectionName.c_str ()));
	LOG (LEVEL_VERBOSE) << "Mode = " << mode;
	LOG (LEVEL_VERBOSE) << "Ready flag = " << readyFlag;
	if (mode == WRITE)
	{
		return (readyFlag == "WRITE");
	}
	else if (mode == READ)
	{
		return (readyFlag == "READ");
	}
	else
	{
		LOG (LEVEL_FATAL) << "Communicator mode not set: cannot verify if ready!";
		return false;
	}
}

void Communicator::done ()
{
	if (mode == WRITE)
	{
		write (connectionName.c_str (), "READ");
	}
	else if (mode == READ)
	{
		write (connectionName.c_str (), "WRITE");
	}
}

void Communicator::operator>> (const pair<string, string *> varName_in)
{
	* (varName_in.second) = read (varName_in.first);
}

void Communicator::operator<< (const pair<string, string> varName_out)
{
	write (varName_out.first, varName_out.second);
}

