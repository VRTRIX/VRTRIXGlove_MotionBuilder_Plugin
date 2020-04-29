#ifndef pyfbtime_h__
#define pyfbtime_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBTime
// =======================================================================================
void FBTime_Init();

class FBTime_Wrapper;
PYSDK_DLL FBTime_Wrapper* FBTime_Wrapper_Factory( const FBTime& pFBTime );
class PYSDK_DLL FBTime_Wrapper {
public:
	FBTime* mFBTime;
public:
    FBTime_Wrapper( const FBTime& pFBTime ) : mFBTime( new FBTime( pFBTime ) ) {  }
    FBTime_Wrapper( kLongLong pTime = 0 ) : mFBTime( new FBTime( pTime ) ) {}
    FBTime_Wrapper( int pHour, int pMinute, int pSecond=0, kLongLong pFrame=0, int pField=0, FBTimeMode pTimeMode=kFBTimeModeDefault ) : mFBTime( new FBTime( pHour, pMinute, pSecond, pFrame, pField, pTimeMode )) {}    
    FBTime_Wrapper( const FBTime_Wrapper& pFBTime ) : mFBTime( new FBTime( *( pFBTime.mFBTime ) ) )
    {
    }
    virtual ~FBTime_Wrapper( ) { delete mFBTime; }
	kLongLong Get()const { return mFBTime->Get(  ); }
	kLongLong GetFrame(FBTimeMode pTimeMode = kFBTimeModeDefault) { return mFBTime->GetFrame( pTimeMode ); }
	void SetFrame(kLongLong pFrames, FBTimeMode pTimeMode = kFBTimeModeDefault) { mFBTime->SetFrame( pFrames, pTimeMode ); }
	kLongLong GetMilliSeconds() { return mFBTime->GetMilliSeconds(  ); }
	double GetSecondDouble() { return mFBTime->GetSecondDouble(  ); }
    const char* GetTimeString(FBTimeMode pMode=kFBTimeModeDefault, FBTime::ETimeFormats pFormat = FBTime::eDefaultFormat) { static FBString lString; lString = mFBTime->GetTimeString( pMode, pFormat ); return lString; }
	void Set(kLongLong pTime) { mFBTime->Set( pTime ); }
	void SetMilliSeconds(kLongLong pMilliSeconds) { mFBTime->SetMilliSeconds( pMilliSeconds ); }
	void SetSecondDouble(double pTime) { mFBTime->SetSecondDouble( pTime ); }
	void SetTime(int pHour, int pMinute = 0, int pSecond = 0, kLongLong pFrame = 0, int pField = 0, FBTimeMode pTimeMode = kFBTimeModeDefault) { mFBTime->SetTime( pHour, pMinute, pSecond, pFrame, pField, pTimeMode ); }
	void SetTimeString(const char * pTime) { mFBTime->SetTimeString( pTime ); }
	FBTime_Wrapper	operator+ (const FBTime_Wrapper &pTime);
	FBTime_Wrapper operator+ (kLongLong pTime);
	FBTime_Wrapper operator- (const FBTime_Wrapper &pTime);
	FBTime_Wrapper operator- (kLongLong pTime);

	bool operator==(const FBTime_Wrapper& pTime)const;
	bool operator!=(const FBTime_Wrapper& pTime)const;
    bool operator>(const FBTime_Wrapper& pTime)const;
    bool operator>=(const FBTime_Wrapper& pTime)const;
    bool operator<(const FBTime_Wrapper& pTime)const;
    bool operator<=(const FBTime_Wrapper& pTime)const;

	static FBTime_Wrapper Infinity;
	static FBTime_Wrapper MinusInfinity;
	static FBTime_Wrapper Zero;
	static FBTime_Wrapper OneSecond;
	static FBTime_Wrapper OneMinute;
	static FBTime_Wrapper OneHour;
};

PYSDK_DLL inline FBTime_Wrapper* FBTime_Wrapper_Factory( const FBTime& pFBTime )
{
	return new FBTime_Wrapper( pFBTime );
}

// =======================================================================================
// FBTimeCode
// =======================================================================================
void FBTimeCode_Init();

class PYSDK_DLL FBTimeCode_Wrapper {
public:
	FBTimeCode* mFBTimeCode;
public:
    FBTimeCode_Wrapper( const FBTimeCode& pFBTimeCode ) : mFBTimeCode( new FBTimeCode( pFBTimeCode ) ) {  }
    FBTimeCode_Wrapper( float pRate=FBTimeCode::FRAMES_30 ) : mFBTimeCode( new FBTimeCode(pRate) ) {}
    FBTimeCode_Wrapper( const FBTimeCode_Wrapper& pFBTimeCode ) : mFBTimeCode( new FBTimeCode( *( pFBTimeCode.mFBTimeCode ) ) )
    {
    }
    virtual ~FBTimeCode_Wrapper( ) { delete mFBTimeCode; }

	void SetTimeCode( int pHour, int pMinute=0, int pSecond=0, float pFrame=0 ) { mFBTimeCode->SetTimeCode( pHour, pMinute, pSecond, pFrame ); }    
    const char* GetTimeCodeString(FBTime::ETimeFormats pFormat = FBTime::eDefaultFormat) { static FBString lString; lString = mFBTimeCode->GetTimeCodeString( pFormat ); return lString; }
	void SetTimeCodeString(const char * pTime,FBTime::ETimeFormats pFormat = FBTime::eDefaultFormat) { mFBTimeCode->SetTimeCodeString( pTime, pFormat ); }
    double GetFrame() { return mFBTimeCode->GetFrame(); }
	void SetFrame(double pValue) { mFBTimeCode->SetFrame( pValue ); }
	float GetFrameRate() const { return mFBTimeCode->GetFrameRate( ); }
	void SetTime(const FBTime_Wrapper& pTime) { mFBTimeCode->SetTime(*pTime.mFBTime); }
	FBTime_Wrapper* GetTime() const { return FBTime_Wrapper_Factory( mFBTimeCode->GetTime() ); }

	double GetRawSecond() const { return mFBTimeCode->GetRawSecond(); }
	double GetRawFrame() const { return mFBTimeCode->GetRawFrame(); }
	double GetRawRate() const { return mFBTimeCode->GetRawRate(); }

	bool operator==(const FBTimeCode_Wrapper& pTimeCode)const{ return *mFBTimeCode == *pTimeCode.mFBTimeCode; }
	bool operator!=(const FBTimeCode_Wrapper& pTimeCode)const{ return *mFBTimeCode != *pTimeCode.mFBTimeCode; }
};

PYSDK_DLL inline FBTimeCode_Wrapper* FBTimeCode_Wrapper_Factory( const FBTimeCode& pFBTimeCode )
{
	return new FBTimeCode_Wrapper( pFBTimeCode );
}

#endif // pyfbtime_h__