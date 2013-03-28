/*
 * common.h
 *
 * Author: Zex
 */

#ifndef COMMON_H
#define COMMON_H

#include <set>
#include <ctime>
#include <iostream>
#include <cstring>
#include <iterator>
#include <thread>
#include <chrono>
#include <future>
#include <fstream>
#include <stdlib.h>

namespace log_service {

#define MAX_ONE_LOG 7000

#define DIFF_STEP 0.000001
#define DIFF_STEP_UP do{diff+=DIFF_STEP;}while(0)

  static bool DEBUGGING = false;
	static double diff = 0.00001;

	typedef std::set<std::string> LogDB;

	LogDB logdb_one;
	LogDB logdb_two;

	char* getnow()
	{
		time_t timer;
		time( &timer );
		char *ret = ctime( &timer );
		ret[24] = '\0';
		return ret;
	}

	char* genid()
	{
		char *ret = new char[12];
		memset( ret, 0, 12 );
		sprintf( ret, "%f", diff );
		DIFF_STEP_UP;
		if ( diff == 0 ) DIFF_STEP_UP;
		return ret;
	}
	
	std::string composelog( std::string pri, std::string usrmsg )
	{
		std::string log( genid() );
	//	log += diff++ % 26 + 'A';
		
		log += ' ';
		log += pri;
		log += ' ';
		log += getnow();
		log += ' ';
		log += usrmsg;
		return log;
	}
	
	template<typename T>
	void printlogdb( T db, const char* log_rest_f )
	{
		std::ofstream o( log_rest_f );
//		o << "logdb_::::::::::::::::::::::::\n";
		std::copy( db.begin(), db.end(),
			std::ostream_iterator<std::string>( o, "\n") );
//		o << "logdb_::::::::::::::::::::::::\n";
		o.close();
	}
}

#endif /* COMMON_H */
