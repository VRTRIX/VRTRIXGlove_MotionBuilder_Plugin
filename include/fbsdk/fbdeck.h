#ifndef __FBDECK_H__
#define __FBDECK_H__
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

/**	\file fbdeck.h
*	Contains abstract deck class to interface with a deck.
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

/**	Deck class registration.
*	\param	UniqueNameStr	Unique name of deck.
*	\param	ClassName		Name of deck class.
*	\param	Label			Short description.
*	\param	Description		Long description.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterDeck( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterDeck##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName(pName); \
		Class->UniqueName = UniqueNameStr; \
		if (Class->FBCreate()) { \
			Class->ThreadSync();	\
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"Decks",Label,Description,RegisterDeck##ClassName, true, IconFilename );	\
	}

/**	Deck class declaration.
*	\param	ClassName		Name of deck class.
*/
#define FBDeckDeclare( ClassName  ) \
	FBClassDeclare( ClassName,FBDeck ); \
  public: \
	ClassName(const char* pName):FBDeck(pName) { FBClassInit; } \
  private:

/**	Deck class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBDeckImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBDeck
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBDeck );
//

//! FBDeckTransportMode
enum FBDeckTransportMode{	
	kFBDeckTransportNone,		//!< No transport interaction.
	kFBDeckTransportSync,		//!< Sync to transport controls.
    kFBDeckTransportSlave= kFBDeckTransportSync,		//!< K_DEPRECATED_2021, use kFBDeckTransportSync.
    kFBDeckTransportMain,		//!< Transport main.
    kFBDeckTransportMaster = kFBDeckTransportMain,		//!< K_DEPRECATED_2021, use kFBDeckTransportMain.
};

FB_DEFINE_ENUM		( FBSDK_DLL, DeckTransportMode );
FB_DEFINE_COMPONENT	( FBSDK_DLL, Deck );

//! Interface to a tape deck.
class FBSDK_DLL FBDeck : public FBComponent {
	__FBClassDeclare( FBDeck,FBComponent );
public:
	const char* UniqueName;							//!< internal Unique name.
	void	ThreadSync();

	/**	Constructor.
	*	\param	pName		Name of deck.
	*	\param	pObject		Internal parent object (default is NULL).
	*/
	FBDeck(const char* pName, HIObject pObject=NULL);	

    IObject_Declare(override);			//! Interface to IObject

	//--- Real-Time deck callback
	virtual void	DeckStatusUpdateNotify();			//!< Deck status update notification.
	virtual void	DeckAutoCommandsNotify();			//!< Deck auto commands notification.

	//--- Operations
	virtual void	Rewind		();						//!< Rewind.
	virtual void	Stop		();						//!< Stop.
	/**	Play forwards.
	*	\param	pSpeed	Playback speed (default is 1.0).
	*/
	virtual void	Play		(double pSpeed = 1.0);	
	virtual void	Forward		();						//!< Fast forward.
	/** Play backwards.
	*	\param	pSpeed	Playback speed(default is 1.0).
	*/
	virtual void	ReversePlay	(double pSpeed = 1.0);	
	virtual void	StepBack	();						//!< Step backwards.
	virtual void	StepForward	();						//!< Step forwards.
	virtual void	Eject		();						//!< Eject tape.
	/** Cue deck at a given time.
	*	\param	pTime	Time to cue deck at.
	*/
	virtual void	CueAt		(FBTime	pTime);

	//--- Time
	/**	Get the deck's time.
	*	\return Time of deck.
	*/
	virtual FBTime	GetTime		();

	//--- FBX store/retrieve
	//@{
	//! FBX Store/Retrieval functions.
	virtual bool	FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	virtual bool	FbxRetrieve	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	//@}

	//--- Icon
	FBPropertyString				IconFilename;			//!< <b>Read Write Property:</b> Filename of icon for deck.

	//--- Settings
	FBPropertyBool					Online;					//!< <b>Read Write Property:</b> Is deck online?
	FBPropertyTime					Offset;					//!< <b>Read Write Property:</b> Current offset for the TC.
	FBPropertyTime					Latency;				//!< <b>Read Write Property:</b> Latency of response for the deck;
	FBPropertyTime					PreRoll;				//!< <b>Read Write Property:</b> Pre-Roll.
	FBPropertyTime					PostRoll;				//!< <b>Read Write Property:</b> Post-Roll.
	FBPropertyDeckTransportMode		TransportControl;		//!< <b>Read Write Property:</b> Mode w/r to TC (None, Sync, Main );

	//--- State
	FBPropertyBool					CassetteInside;			//!< <b>Read Only Property:</b> Is the cassette inside?
	FBPropertyBool					PlayingForward;			//!< <b>Read Only Property:</b> Playing forward?
	FBPropertyBool					PlayingBackward;		//!< <b>Read Only Property:</b> Playing backwards?
	FBPropertyBool					EE;						//!< <b>Read Write Property:</b> Is EE on?
	FBPropertyBool					StandBy;				//!< <b>Read Write Property:</b> In standby mode?
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListDeck
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Deck
class FBSDK_DLL FBPropertyListDeck : public FBPropertyListComponent
{
public:
	FBPropertyListDeck();
	/**	Get the deck at \e pIndex.
	*	\param	pIndex	Index of deck.
	*	\return Handle to deck at \e pIndex.
	*/
	FBDeck* operator[](int pIndex);
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
