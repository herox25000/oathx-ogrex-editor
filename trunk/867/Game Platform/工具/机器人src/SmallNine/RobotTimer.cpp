#include "StdAfx.h"
#include ".\robottimer.h"


RobotTimer::RobotTimer()
	: mTimerMask( 0 )
{
	Reset();
}


RobotTimer::~RobotTimer()
{
}

BOOL	RobotTimer::SetOption( const CString& key, const void * val )
{
	if ( key == "QueryAffinityMask" )
	{
		DWORD newTimerMask = * static_cast < const DWORD * > ( val );

		DWORD_PTR procMask;
		DWORD_PTR sysMask;
		GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);

		if( ( newTimerMask == 0 ) ||
			( ( ( newTimerMask & procMask ) != 0 ) && isPO2( newTimerMask ) ) )
		{
			mTimerMask = newTimerMask;
			return TRUE;
		}
	}

	return 0;
}

void	RobotTimer::Reset()
{
    // Get the current process core mask
	DWORD_PTR procMask;
	DWORD_PTR sysMask;
	GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);

	// If procMask is 0, consider there is only one core available
	// (using 0 as procMask will cause an infinite loop below)
	if (procMask == 0)
		procMask = 1;

	// Find the lowest core that this process uses
	if( mTimerMask == 0 )
	{
		mTimerMask = 1;
		while( ( mTimerMask & procMask ) == 0 )
		{
			mTimerMask <<= 1;
		}
	}

	HANDLE thread = GetCurrentThread();

	// Set affinity to the first core
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

	// Get the constant frequency
	QueryPerformanceFrequency(&mFrequency);

	// Query the timer
	QueryPerformanceCounter(&mStartTime);
	mStartTick = GetTickCount();

	// Reset affinity
	SetThreadAffinityMask(thread, oldMask);

	mLastTime = 0;
	mZeroClock = clock();
}


unsigned long RobotTimer::GetMilliseconds()
{
    LARGE_INTEGER curTime;

	HANDLE thread = GetCurrentThread();

	// Set affinity to the first core
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

	// Query the timer
	QueryPerformanceCounter(&curTime);

	// Reset affinity
	SetThreadAffinityMask(thread, oldMask);

    LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
    
    // scale by 1000 for milliseconds
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);

    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;

        // Re-calculate milliseconds
        newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
    }

    // Record last time for adjust
    mLastTime = newTime;

    return newTicks;
}

ULONG		RobotTimer::GetMicroseconds()
{
    LARGE_INTEGER curTime;

	HANDLE thread = GetCurrentThread();

	// Set affinity to the first core
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

	// Query the timer
	QueryPerformanceCounter(&curTime);

	// Reset affinity
	SetThreadAffinityMask(thread, oldMask);

	LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
    
    // get milliseconds to check against GetTickCount
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
    
    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;
    }

    // Record last time for adjust
    mLastTime = newTime;

    // scale by 1000000 for microseconds
    unsigned long newMicro = (unsigned long) (1000000 * newTime / mFrequency.QuadPart);

    return newMicro;
}

ULONG		RobotTimer::GetMillisecondsCPU()
{
	clock_t newClock = clock();
	return (unsigned long)( (float)( newClock - mZeroClock ) / ( (float)CLOCKS_PER_SEC / 1000.0 ) ) ;
}

ULONG		RobotTimer::GetMicrosecondsCPU()
{
	clock_t newClock = clock();
	return (unsigned long)( (float)( newClock - mZeroClock ) / ( (float)CLOCKS_PER_SEC / 1000000.0 ) ) ;
}

double		RobotTimer::GetElapsed()
{
	return GetMilliseconds() / 1000.0f;
}
