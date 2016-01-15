/*
    @file unit_test_ProcessLogger.cpp

    @autor William Batista Aguiar Motta
    @email yosoyninja@gmail.com

    @attention Copyright (C) 2013
    @attention UnBall Robot Soccer Team

       Este programa é um software livre; você pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opnião) qualquer versão.

    Este programa é distribuido na esperança que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
    Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
#define BOOST_TEST_DYN_LINK

#include <ProcessLogger.h>

#include <boost/test/unit_test.hpp>

void f()
{
    LOG(LEVEL_ERROR) << "Functions called can use the logger as well";
}

void foo(int id)
{
    for (int ii = 0; ii < 2000; ++ii)
    {
        LOG(LEVEL_DEBUG) << id << ": " << ii;
    }
}
BOOST_AUTO_TEST_SUITE (unit_test_shared)
BOOST_AUTO_TEST_CASE(unit_test_processlogger)
{
	using namespace std;    
    
    LOG(LEVEL_VERBOSE) << "random";
    LOG(LEVEL_DEBUG) << "text";
    LOG(LEVEL_INFO) << "logged";
    LOG(LEVEL_WARN) << "to";
    LOG(LEVEL_ERROR) << "cerr:";
    LOG(LEVEL_FATAL) << "no problem!";

    BOOST_CHECK_EQUAL(ProcessLogger::open("test.log"),true);
    
    //Trying to write to a log before log/print levels are defined
    LOG(LEVEL_ERROR) << "No levels defined!";
    LOG(LEVEL_VERBOSE) << "Levels default to LEVEL_VERBOSE";

    ProcessLogger::setLogLevel(LEVEL_VERBOSE);
    ProcessLogger::setPrintLevel(LEVEL_INFO);

    int var = 42;
    string string1 = "Read";
    string string2 = "able";

    LOG(LEVEL_VERBOSE) << "I can write literal strings";
    LOG(LEVEL_DEBUG) << "I can write the value of variable var:" << var;
    LOG(LEVEL_INFO) << "Syntax is " << string1 + string2;
    LOG(LEVEL_WARN) << "There is no need for endl, as it is built-in";
    LOG(LEVEL_ERROR) << "Level filtering works, and we have easy macros";
    LOG(LEVEL_FATAL) << "And it is thread-safe... I think";

    BOOST_CHECK_EQUAL(ProcessLogger::close(),true);
    
    LOG_INIT(".","test2",LEVEL_WARN,LEVEL_ERROR);

    f();

    BOOST_CHECK_EQUAL(ProcessLogger::close(),true);
    
        LOG_INIT2("test3.log",LEVEL_DEBUG,LEVEL_FATAL);

    boost::thread thrd1(boost::bind(&foo, 1));
    boost::thread thrd2(boost::bind(&foo, 2));
    thrd1.join();
    thrd2.join();

    BOOST_CHECK_EQUAL(ProcessLogger::close(),true);

    //Trying to write to a closed log, just outputs do cerr
    LOG(LEVEL_FATAL) << "hello cerr";

    //Trying to open a log to a inexistent directory
    BOOST_CHECK_EQUAL(ProcessLogger::open("./inexistent","someProcess"),false);

    //Trying to open a log where you do not have permissions
    BOOST_CHECK_EQUAL(ProcessLogger::open("/home/root","anotherProcess"),false);

    //Adding a trailing '/' to the directory name (fopen is flexible enough to accept both styles)
    BOOST_CHECK_EQUAL(ProcessLogger::open(".///","test4"),true);

    //Logging with endl results in duplicate endl
    LOG(LEVEL_FATAL) << "Using endl is not necessary!!!" << endl;
    LOG(LEVEL_ERROR) << "Why did you do that?";
    LOG(LEVEL_FATAL) << "logLevel and printLevel persist with old values";
    LOG(LEVEL_ERROR) << "it is better to always set levels when you open a new log";

    ProcessLogger::setLogLevel(LEVEL_FATAL);
    ProcessLogger::setPrintLevel(LEVEL_ERROR);

    LOG(LEVEL_ERROR) << "See how it works?";

    BOOST_CHECK_EQUAL(ProcessLogger::close(),true);

}
BOOST_AUTO_TEST_SUITE_END ()
