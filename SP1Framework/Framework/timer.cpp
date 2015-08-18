#include "timer.h"

//--------------------------------------------------------------
// Purpose  : Constructor, We will set the timer intervals here
// Input    : Void
// Output   : Nil
//--------------------------------------------------------------
CStopWatch::CStopWatch( void )
{    
    QueryPerformanceFrequency( &m_liFrequency ) ;

    #define TARGET_RESOLUTION 1         // 1-millisecond target resolution
    TIMECAPS tc;

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
        // Error; application can't continue.
    }

    m_uTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);

    // requests a minimum resolution for periodic timers.
    // goto https://msdn.microsoft.com/en-us/library/windows/desktop/dd757624(v=vs.85).aspx for more info
    timeBeginPeriod(m_uTimerRes); 
}

//--------------------------------------------------------------
// Purpose  : Destructor
// Input    : Void
// Output   : Nil
//--------------------------------------------------------------
CStopWatch::~CStopWatch( void )
{
    // clear the resolution
    // goto https://msdn.microsoft.com/en-us/library/windows/desktop/dd757626(v=vs.85).aspx for more info
    timeEndPeriod(m_uTimerRes);
}

//--------------------------------------------------------------
// Purpose  : Convert the time to seconds
// Input    : Long integer
// Output   : Double
//--------------------------------------------------------------
double CStopWatch::LiToSecs( LARGE_INTEGER & liInput) {
     return ((double)liInput.QuadPart /(double)m_liFrequency.QuadPart) ;
 }
 
//--------------------------------------------------------------
// Purpose  : Start the timer by getting current time and store
// Input    : void
// Output   : void
//--------------------------------------------------------------
void CStopWatch::startTimer( void )
{
    QueryPerformanceCounter(&m_liPrevTime) ;
}
 
//--------------------------------------------------------------
// Purpose  : Get the elapsed time by getting current time 
//            and minus stored value
// Input    : void
// Output   : void
//--------------------------------------------------------------
double CStopWatch::getElapsedTime( void ) 
{
    LARGE_INTEGER llTime;
    // obtain current time
    QueryPerformanceCounter(&m_liCurrTime) ;
    // Calculate elapsed time
    llTime.QuadPart = m_liCurrTime.QuadPart - m_liPrevTime.QuadPart;
    // Store current time for next elapsed time calculation
    m_liPrevTime = m_liCurrTime;
    return LiToSecs( llTime) ;
}

//--------------------------------------------------------------
// Purpose  : Sleep the system till llTime has reached
// Input    : time to sleep (long long)
// Output   : void
//--------------------------------------------------------------
void CStopWatch::waitUntil(long long llTime)
{
    LARGE_INTEGER liCurTime;
    LONGLONG llTimeElapsed;
    while (true)
    {
        // get current time
        QueryPerformanceCounter(&liCurTime);
        // Calculate time elapsed
        llTimeElapsed = ((liCurTime.QuadPart - m_liPrevTime.QuadPart) * 1000 / m_liFrequency.QuadPart);
        // llTime has passed, return and end sleep
        if (llTimeElapsed > llTime)
            return;
        else if (llTime - llTimeElapsed > 1)
            Sleep(1);
    }
}