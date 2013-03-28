/*
 * =====================================================================================
 *
 *       Filename:  twoset.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/03/13 16:28:25
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zex (zex), top_zlynch@yahoo.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "common.h"

//struct ltstr
//{
//  bool operator()( const char* s1, const char* s2 ) const
//	{
//        	return std::strcmp(s1, s2) < 0;
//	}
//};

//std::set<char*, ltstr> logdb_one;

namespace log_service {

	#define LOG_FILE "./twoset.log"
	#define LOG_REST_FILE "./twoset.rest.log"
	#define DEBUG_FILE "./twoset.debug"

	void cleanupdb()
	{
		std::copy( logdb_one.begin(), logdb_one.end(),
			std::inserter( logdb_two, logdb_two.end() ) );
	
		logdb_one.clear();
	}

	void flushlog()
	{
		std::ofstream o( LOG_FILE, std::ios::app );
		std::copy( logdb_two.begin(), logdb_two.end(),
			std::ostream_iterator<std::string>( o, "\n") );
		o.close();

		logdb_two.clear();
	}

	void watchlog()
	{
		if ( DEBUGGING ) {
			std::ofstream o( DEBUG_FILE, std::ios::app );
			o << "logdb_one size :::::::::: "
			 << logdb_one.size() << '\n';
			o.close();
		}

		if ( logdb_one.size() < MAX_ONE_LOG ) return;
	
		std::thread( cleanupdb ).join();	
		std::thread( flushlog ).join();
	}

	void insertlog( std::string pri, std::string usrmsg )
	{
//		std::this_thread::sleep_for( std::chrono::milliseconds( 3 ) );
		std::string msg = 
			composelog( pri, usrmsg );
		logdb_one.insert( msg );

		std::thread( watchlog ).join();
	}
}

using namespace log_service;

int main( int argc, const char *argv[] )
{
	int i = 0;
	int total;

	if ( argc > 1 ) {
		total = atoi( argv[1] );
	} else {
		total = 1024;
	}

	if ( argc > 2 ) {
		DEBUGGING = true;
	}

	while ( i++ < total ) {
		std::thread( insertlog, "<Warning>", "Fly to the Pluto" ).join();
	}

	if ( DEBUGGING )
		printlogdb<LogDB>( logdb_one, LOG_REST_FILE );
	
	return 0;
}
