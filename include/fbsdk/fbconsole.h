#ifndef __FBCONSOLE_H__
#define __FBCONSOLE_H__
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

/**	\file fbconsole.h
*	Generic Console interface.
*	Generic class to communicate with a console.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

//! Console channel types.
enum FBConsoleChannelType {
	kFBConsoleNull,				//!< Generic type.
	kFBConsoleButton,			//!< Button.			
	kFBConsoleSlider,			//!< Slider.			
	kFBConsoleTransport,		//!< Transport.			
	kFBConsoleEncoder,			//!< Generic encoder.	
	kFBConsoleKey,				//!< Key.				
	kFBConsoleDisplay,			//!< Display.			
	kFBConsoleJoystick			//!< Joystick.			
};
FB_DEFINE_ENUM( FBSDK_DLL, ConsoleChannelType );

__FB_FORWARD( FBConsoleChannel );

//! Console data channel.
class FBSDK_DLL FBConsoleChannel : public FBComponent {
	__FBClassDeclare( FBConsoleChannel,FBComponent );
public:
	/**	Constructor.
	*	\param pName Channel name.
	*/
	FBConsoleChannel(const char *pName);

	//--- Properties ---
	FBPropertyString				Name;			//!< <b>Property:</b> Name of channel.
	FBPropertyString				Description;	//!< <b>Property:</b> Description of channel.
	FBPropertyString				Group;			//!< <b>Property:</b> Group that channel is part of.
	FBPropertyConsoleChannelType 	Type;			//!< <b>Property:</b> Type of channel.
	FBPropertyDouble				Value;			//!< <b>Property:</b> Current value of channel.
	FBPropertyDouble				Min;			//!< <b>Property:</b> Minimum value.
	FBPropertyDouble				Max;			//!< <b>Property:</b> Maximum value.
	FBPropertyDouble				Step;			//!< <b>Property:</b> Stepping value of channel.
};
FB_DEFINE_ARRAY	( FBSDK_DLL, ConsoleChannel );

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListConsoleChannel
////////////////////////////////////////////////////////////////////////////////////

//! \b PropertyList: Data Channels.
class FBSDK_DLL FBPropertyListConsoleChannel : public FBPropertyBaseList< FBConsoleChannel* >
{
private:
    FBArrayTemplate<FBConsoleChannel*> mItems;			//!< List of data channels.

	/**	Add a data channel.
	*	\param pItem Channel to add.
	*	\return Index where \e pItem was inserted.
	*/
	virtual int	 Add	( FBConsoleChannel* pItem );	

public:
	/** Remove a data channel at \e pIndex
	*	\param pIndex Index of channel to remove.
	*/
    virtual void RemoveAt( int pIndex );				

	/** Overloaded [] operator.
	*	Get channel at \e pIndex.
	*	\param pIndex Index of channel to access.
	*	\return Handle to channel at \e pIndex.
	*/
	virtual FBConsoleChannel* operator[](int pIndex);	

	/** Get channel count
	*	\return Number of channels.
	*/
	virtual int  GetCount();							

public:
	/** Add a channel by name.
	*	There is a defined list of channels for the console.
	*	\param pName Name of channel to add.
	*	\return Index where channel was inserted.
	*/
	virtual int	 Add	( const char *pName );
   
	/** Find a channel by name.
	*	There is a defined list of channels for the console.
	*	\param pName Name of channel to find.
	*	\return Pointer to the console channel found.
	*/
	FBConsoleChannel* Find(const char *pName);
};

/*-------------------------------------------------------------------------
  Class FBConsole: Console base class
 -------------------------------------------------------------------------*/
__FB_FORWARD( FBConsole );
FB_FORWARD( FBFbxObject );

/**	Console base class.
*/
class FBSDK_DLL FBConsole : public FBComponent {
	__FBClassDeclare( FBConsole,FBComponent );
  private:

  public:
	/**	Constructor
	*	\param pName	Name of console.
	*	\param pObject	Owner of FBComponent (default is NULL).
	*/
	FBConsole(const char *pName=NULL, HIObject pObject=NULL);

	FBPropertyListConsoleChannel		Channels;			//!< <b>List:</b> Data Channels.
	FBPropertyBool						IsTransportControl;	//!< <b>Property:</b> Is the console able to interface transport controls (true/false)?

	//@{
	/** Store/Retrieve data to/from FBX files.
	*	\param pFbxObject	Interface to FBX format.
	*	\param pStoreWhat	Attributes to store in file.
	*	\return \b true if successful.
	*/
    virtual bool FbxStore(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat);
	virtual bool FbxRetrieve(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat);
	//@}

	// Re-implemented from FBComponent.
    virtual bool FBCreate() override;
    virtual void FBDestroy() override;

	/** Open console.
	*	\return \b true if successful.
	*/
	virtual bool Open()			= 0;

	/** Close console.
	*	\return \b true if successful.
	*/
	virtual bool Close()		= 0;

	/** Initialize console.
	*	\return \b true if successful.
	*/
	virtual bool Initialize()	= 0;

	/** Fetch data from console.
	*	\return \b true if successful.
	*/
	virtual bool FetchData()	= 0;
};
/** \def IJLCooper_Declare(IsPure)
*		LCD screen related function
*/
#define IJLCooper_Declare(IsPure)\
  public:\
	/* LCD screen */	\
	/** Clear LCD screen */ \
	virtual void LCDClearScreen		( )												IsPure;\
	/** Send a string to the LCD screen */ \
	virtual void LCDSendString		( const char* pMessage, int pX = 0, int pY = 0 )IsPure;\
	/** Send a string to the LCD screen */ \
	virtual void LCDSendChar		( char pChar, int pX = 0, int pY = 0 )			IsPure;\
	/**	Blinking cursor */ \
	virtual void LCDSetCursorBlink	( bool pState = true )							IsPure;\
	/* TimeCode */	\
	/** Set time */ \
	virtual void TCSetTime			( FBTime pTime )								IsPure;\


K_INTERFACE( IJLCooper, 100103033 );

__FB_FORWARD( FBJLCooper );

/** JL Cooper interface class.
*	Small API to interface a tool with a JLCooper console.
*/
class FBSDK_DLL FBJLCooper : public FBComponent, public IJLCooper
{
  private:
	__FBClassDeclare( FBJLCooper, FBComponent );
  public:
	/**	Constructor.
	*	\param	pIndex	Index value (default is 0).
	*/
	FBJLCooper			( int pIndex = 0 );

	IJLCooper_Declare	( override );
    IObject_Declare     ( override );
};

    
#ifdef FBSDKUseNamespace
}
#endif
#endif
