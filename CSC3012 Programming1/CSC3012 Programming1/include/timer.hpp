/*
 *  timer.h
 *	returs elapsed time in micro-sec
 */

#ifndef TIMER_H
#define TIMER_H

#if defined(WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif


#if defined(WIN32)
typedef struct 
{
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;
#endif

class CStopWatch 
{	
private:
#if defined(WIN32)
	stopWatch timer;
	LARGE_INTEGER frequency;
	double LIToSecs( LARGE_INTEGER & L);
#else
	struct timeval start,end;
	struct timezone tz;
	double time_total;
#endif
public:
	CStopWatch();
	void startTimer( );
	void stopTimer( );
	double getElapsedTime();
	void refreshTimer( );
};

#endif
