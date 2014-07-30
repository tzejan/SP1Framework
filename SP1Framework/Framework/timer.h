#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     void stopTimer();
     double getElapsedTime(); // time returned in seconds
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H