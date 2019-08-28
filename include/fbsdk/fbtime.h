#ifndef __FBTIME_H__
#define __FBTIME_H__
/**************************************************************************
 Copyright (c) 1994 - 2009 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.
 
 The coded instructions, statements, computer programs, and/or related 
 material (collectively the "Data") in these files contain unpublished 
 information proprietary to Autodesk, Inc. and/or its licensors, which is 
 protected by Canada and United States of America federal copyright law 
 and by international treaties.
 
 The Data may not be disclosed or distributed to third parties, in whole 
 or in part, without the prior written consent of Autodesk, Inc. 
 ("Autodesk").
 
 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO 
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR 
 ARISING BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES 
 OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT 
 WARRANT THAT THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR 
 FREE.
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS 
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR 
 EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE 
 DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS 
 OF PROFITS, REVENUE OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR 
 DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF 
 LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT 
 LIMITED TO, NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE 
 DATA OR ITS USE OR ANY OTHER PERFORMANCE, WHETHER OR NOT AUTODESK HAS 
 BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.
 
**************************************************************************/

/**	\file fbtime.h
*	Time classes.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
  #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbstring.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBTime
////////////////////////////////////////////////////////////////////////////////////

//! Different time modes available.
enum FBTimeMode {	
	kFBTimeModeDefault, 		//!< Default Time Mode
	kFBTimeMode1000Frames,		//!< 1000 : 1 millisecond
	kFBTimeMode120Frames, 		//!< 120
	kFBTimeMode100Frames,		//!< 100
	kFBTimeMode96Frames,		//!< 96
	kFBTimeMode72Frames,		//!< 72
	kFBTimeMode60Frames,		//!< 60
	kFBTimeMode5994Frames,		//!< ~59.94
	kFBTimeMode50Frames,		//!< 50
	kFBTimeMode48Frames,		//!< 48
	kFBTimeMode30Frames,		//!< 30 
	kFBTimeMode2997Frames_Drop,	//!< ~29.97 drop
	kFBTimeMode2997Frames,		//!< ~29.97 full
	kFBTimeMode25Frames,		//!< 25 
	kFBTimeMode24Frames,		//!< 24 
	kFBTimeMode23976Frames,		//!< ~23.976
    kFBTimeModeCustom           //!< Custom framerate
};

FB_FORWARD( FBTime );

//! Time data structure.
class FBSDK_DLL FBTime 
{
  private:
	kLongLong	mTime;			//!< Time member.
  public:

	//! Different time format available.
	enum ETimeFormats
	{
		eSMPTE,			//!< format as SMPTE
		eFrame,			//!< format as numeric frame
		eDefaultFormat	//!< Default Time format
	};
 
	/*	Constructor.
	*	\param	pTime	Time to initialize with(default=0).
	*/
    FBTime( kLongLong pTime=0);

	/**	Constructor.
	*	\param	pHour		Hour value.
	*	\param	pMinute		Minute value.
	*	\param	pSecond		Second value.
	*	\param	pFrame		Frame value.
	*	\param	pField		Field value.
	*	\param	pTimeMode	Time mode(default=kFBTimeModeDefault).
	*/
	FBTime (int pHour,int pMinute,int pSecond=0,int pFrame=0,int pField=0, FBTimeMode pTimeMode=kFBTimeModeDefault);

	/**	Get time as a string.
	*	\param	pMode		Time mode (default=kFBTimeModeDefault) to use (call FBSystem().GetTransportFps() to the the current UI displayed mode).
	*	\param	pFormat		Format to use for the returned string(default=FBTime::eDefaultFormat).
	*	\return String value of time.
	*/
	FBString GetTimeString(FBTimeMode pMode=kFBTimeModeDefault, ETimeFormats pFormat = eDefaultFormat);

	/**	Set time from string.
	*	\param	pTime	String to set time from.
	*/
    void SetTimeString(const char *pTime);

	/**	Get time (filling separate values)
	*	\retval	pHour			Hour value.
	*	\retval	pMinute			Minute value.
	*	\retval	pSecond			Second value.
	*	\retval	pFrame			Frame value.
	*	\retval	pField			Field value.
	*	\retval	pMilliSecond	MilliSecond value.
	*	\param	pTimeMode		Time mode to get time as.
	*	\return	\b true if an acceptable \e TimeMode value was chosen.
	*/
	bool		GetTime(int &pHour,  int &pMinute, int &pSecond, int &pFrame, int &pField,  int &pMilliSecond, FBTimeMode pTimeMode=kFBTimeModeDefault );
	/**	Get milliseconds for time.
	*	\return	MilliSeconds value.
	*/
	kLongLong	GetMilliSeconds();

	/**	Set milliseconds time.
	*	\param	pMilliSeconds	MilliSeconds value.
	*/
	void		SetMilliSeconds(kLongLong pMilliSeconds);

	/**	Get time value (long)
	*	\return Time value as long.
	*/
    kLongLong&	Get();

	/**	Get time value (long)
	*	\return Time value as long.
	*/
    const kLongLong& Get() const;

	/** Set time value from a long.
	*	\param	pTime	Time value to set.
	*/
    void		Set( kLongLong pTime );

	/**	Get seconds as double.
	*	\return Seconds in double form.
	*/
	double		GetSecondDouble();

	/**	Set seconds from double.
	*	\param	pTime	Time to set seconds from.
	*/
	void		SetSecondDouble(double pTime);

	/**	Set time (from separate values)
	*	\param	pHour			Hour value.
	*	\param	pMinute			Minute value(default=0).
	*	\param	pSecond			Second value(default=0).
	*	\param	pFrame			Frame value(default=0).
	*	\param	pField			Field value(default=0).
	*	\param	pTimeMode		Time mode to get time as(default=kFBTimeModeDefault).
	*/
	void		SetTime (int pHour,int pMinute=0,int pSecond=0,int pFrame=0,int pField=0, FBTimeMode pTimeMode=kFBTimeModeDefault);

	//@{
	/**	Overloaded assignment operators with FBTime objects.
	*	\param	pTime	Time to assign with operator.
	*	\return	Resulting time from operation.
	*/
	FBTime& operator=	(const FBTime& pTime);
	FBTime& operator+=	(const FBTime& pTime);
	FBTime& operator-=	(const FBTime& pTime);
	FBTime&	operator*=	(const FBTime& pTime);
	FBTime&	operator/=	(const FBTime& pTime);
	//@}

	//@{
	/**	Overloaded assignment operators with constants.
	*	\param	pConstant	Time to assign with operator.
	*	\return	Resulting time from operation.
	*/
	FBTime& operator=	(double pConstant);
	FBTime& operator+=	(double pConstant);
	FBTime& operator-=	(double pConstant);
	FBTime&	operator*=	(double pConstant);
	FBTime&	operator/=	(double pConstant);
	//@}

	//@{
	/**	Overloaded arithmetic operators with FBTime objects.
	*	\param	pTime	Time to use in operation.
	*	\return	Result in FBTime data.
	*/
    FBTime	operator- (const FBTime &pTime);
    FBTime	operator+ (const FBTime &pTime);
	FBTime	operator/ (const FBTime &pTime);
	FBTime	operator* (const FBTime &pTime);
	//@}

	//@{
	/**	Overloaded arithmetic operators with constants.
	*	\param	pConstant	Double constant to add to time.
	*	\return	Result in FBTime data.
	*/
    FBTime	operator- (double pConstant);
    FBTime	operator+ (double pConstant);
	FBTime	operator/ (double pConstant);
	FBTime	operator* (double pConstant);
	//@}

	//@{
	/** Overloaded comparison operators.
	*	\param	pTime	Time to compare with.
	*	\return	Result of comparison.
	*/
	bool	operator==	(const FBTime& pTime);
	bool	operator!=	(const FBTime& pTime);
	bool	operator>=	(const FBTime& pTime);
	bool	operator<=	(const FBTime& pTime);
	bool	operator>	(const FBTime& pTime);
	bool	operator<	(const FBTime& pTime);
	//@}

	/**	Get the frame count.
	*	With this function, it is possible to obtain the cumulative and local frame counts.
	*	\param	pTimeMode	Time mode to get the constant (default is kFBTimeModeDefault).
	*	\return	Frames per second constant for the specified time mode.
	*/
	kLongLong	GetFrame(FBTimeMode pTimeMode=kFBTimeModeDefault);

	/** Set time in frame format.
      * \param pFrames The number of frames.
      * \param pTimeMode The time mode identifier which will dictate the extraction algorithm.
	  */
	void SetFrame(kLongLong pFrames, FBTimeMode pTimeMode=kFBTimeModeDefault);

	//! Time constant: Infinity, the largest time value.
	static const FBTime Infinity;

	//! Time constant: Minus Infinity, the lowest negative time value.
	static const FBTime MinusInfinity;

	//! Time constant: Zero.
	static const FBTime Zero;

	//! Time constant: Epsilon, the smallest time increment.
	static const FBTime Epsilon;

	//! Time constant: One Second.
	static const FBTime OneSecond;

	//! Time constant: One Minute.
	static const FBTime OneMinute;

	//! Time constant: One Hour.
	static const FBTime OneHour;
};

FB_FORWARD( FBTimeCode );

//! TimeCode data structure.
class FBSDK_DLL FBTimeCode 
{
  private:
	double mSecond;	//!< in HH:MM:SS:FF.ff, it correspond to HH*60*60+MM*60+SS so the total number of seconds
	double mFrame;	//!< in HH:MM:SS:FF.ff, it correspond to FF.ff
	double mRate;	//!< Frame rate where the minus (-) is used for non-drop
  public:

	/**	Constructor.
    *	\param	pRate		Framerate value.
	*/
	FBTimeCode(float pRate=NTSC_DROP);

	/**	Set timecode.
	*	\param	pHour		Hour value.
	*	\param	pMinute		Minute value.
	*	\param	pSecond		Second value.
	*	\param	pFrame		Frame value.
	*/
	void SetTimeCode(int pHour,int pMinute=0,int pSecond=0,float pFrame=0);

	/**	Get time as a string.
	*	\param	pFormat		Format to use for the returned string(default=FBTime::eDefaultFormat).
	*	\return String value of time.
	*/
	FBString GetTimeCodeString(FBTime::ETimeFormats pFormat = FBTime::eDefaultFormat);

	/**	Set time from string.
	*	\param	pTime	String to set time from.
	*	\param	pFormat		Format to use for the string(default=FBTime::eDefaultFormat).
	*/
    void SetTimeCodeString(const char *pTime, FBTime::ETimeFormats pFormat = FBTime::eDefaultFormat);

	/** Return a Time corresponding to the timecode.
	*/
	FBTime GetTime() const;

	/** Set TimeCode according to the given time.
      * \param pTime Time value to set.
	*/
	void SetTime(FBTime pTime);

	/** Return a frame number corresponding to the timecode.
	*/
	double GetFrame() const;

	/** Set Frame according to the given time.
      * \param pFrame Frame value to set.
	*/
	void SetFrame(double pFrame);

	/** Return the rate of the timecode.
	*/
	float GetFrameRate() const;

    /** Get the raw value for the second.
      * \return raw value for the second.
      */
	double GetRawSecond() const;

    /** Get the raw value for the frame.
      * \return raw value for the frame.
      */
	double GetRawFrame() const;

    /** Get the raw value for the rate.
      * \return raw value for the rate.
      */
	double GetRawRate() const;

    /** Equality operator.
      *	\param	pTimeCode time code to compare with.
      *	\return	true if time codes are equal.
      */
	bool operator==(const FBTimeCode& pTimeCode)const;

	/** Inequality operator.
      *	\param	pTimeCode time code to compare with.
      *	\return	true if time codes are not equal.
      */
	bool operator!=(const FBTimeCode& pTimeCode)const;


//! Rates
	static const float NTSC_DROP;	//!<  29.97f
	static const float NTSC_FULL;	//!< -29.97f
	static const float PAL_25;		//!< -25.0f
	static const float MPAL_30;		//!< -29.971f Currently not supported : "1" is added just to differentiate from NTSC_FULL(-29.97f)
	static const float FILM_24;		//!< -24.0f
	static const float FILM_23976;	//!< -23.976f
	static const float FRAMES_30;	//!< -30.0f
	static const float FRAMES_5994;	//!< -59.94f
};

////////////////////////////////////////////////////////////////////////////////////
// FBTimeSpan
////////////////////////////////////////////////////////////////////////////////////

FB_FORWARD( FBTimeSpan );

//! TimeSpan class.
class FBSDK_DLL FBTimeSpan 
{
  private:
    FBTime       mStart;		//!< Start time.
    FBTime       mStop;			//!< Stop time.
  public:
	/**	Constructor.
	*	\param	pStart	Start time(default=0).
	*	\param	pStop	Stop time(default=0).
	*/
    FBTimeSpan( FBTime pStart=0,FBTime pStop=0);

	//@{
	/**	Get the start/stop time.
	*	\return Start/Stop time.
	*/
	FBTime& GetStart();
	FBTime& GetStop();
	const FBTime& GetStart() const;
	const FBTime& GetStop() const;
	//@}

	/**	Set the TimeSpan
	*	\param	pStart	Start time.
	*	\param	pStop	Stop time.
	*/
	void	Set( FBTime pStart, FBTime pStop );

	/**	Get the unsigned duration value of a timespan.
	*	\return \b Unsigned duration of the timespan.
	*/
	FBTime	GetDuration();		

	/**	Get the signed duration value of a timespan.
	*	\return \b Signed duration of the timespan.
	*/
	FBTime	GetSignedDuration(); 

	/**	Get the direction of the timespan.
	*	Returns 1 if positive, -1 otherwise.
	*	\return Direction of timespan.
	*/
	int		GetDirection();

	/**	Verify if \e pTime is contained within the timespan.
	*	\param	pTime Time to verify if within the timespan.
	*	\return \b true if \e pTime is within the timespan.
	*/
	bool	operator& (FBTime &pTime);
	
	/**	Calculate the intersection of two timespans.
	*	\return	Timespan representing the intersection of the two timespans.
	*/
	FBTimeSpan operator& (FBTimeSpan &pTimeSpan);	
};
///////////////////////////////////////////////////////////////////////////////////
// Global
////////////////////////////////////////////////////////////////////////////////////
#ifdef FBSDKUseNamespace
	}
#endif

#endif

