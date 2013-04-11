#pragma once

namespace O2
{
	template<typename T>
		static __forceinline bool isPO2(T n)
	{
		return (n & (n-1)) == 0;
	}


	static unsigned int gnSeed = 0;
	
	//////////////////////////////////////////////////////////////////////////
	// ������ʱ�����
	//////////////////////////////////////////////////////////////////////////
	class AndroidTimer
	{
	public:
		//
		static AndroidTimer&		GetSingleton()
		{
			static AndroidTimer instance;
			return instance;
		}
		
		/*
		*
		*/
		static float				rdft(float Min, float Max)
		{
			if (gnSeed == 0)
			{
				gnSeed = ::GetTickCount();
			}

			gnSeed = 214013 * gnSeed + 2531011;

			return Min+(gnSeed >> 16) * (1.0f / 65535.0f) * (Max-Min);
		}

		/*
		*
		*/
		static INT64				rdit(INT64 dwMin, INT64 dwMax)
		{
			if (dwMax < dwMin)
				return dwMax;

			return (rand() % (dwMax - dwMin)) + dwMin;
		}
	public:
		/*
		*
		*/
		AndroidTimer(void);
		/*
		*
		*/		
		virtual ~AndroidTimer(void);

		/*
		*
		*/
		virtual BOOL			SetOption( const CString& strKey, const void* pValue );

		/** Resets timer */
		/*
		*
		*/		
		virtual void			Reset();

		/** Returns milliseconds since initialisation or last reset */
		/*
		*
		*/
		virtual ULONG			GetMilliseconds();

		/** Returns microseconds since initialisation or last reset */
		/*
		*
		*/		
		virtual ULONG			GetMicroseconds();

		/** Returns milliseconds since initialisation or last reset, only CPU time measured */
		/*
		*
		*/		
		virtual ULONG			GetMillisecondsCPU();

		/** Returns microseconds since initialisation or last reset, only CPU time measured */
		/*
		*
		*/		
		virtual ULONG			GetMicrosecondsCPU();

		/*
		*
		*/
		virtual double			GetElapsed();
	private:
		clock_t					mZeroClock;

		DWORD					mStartTick;
		LONGLONG				mLastTime;
		LARGE_INTEGER			mStartTime;
		LARGE_INTEGER			mFrequency;

		DWORD_PTR				mTimerMask;
	};
}

