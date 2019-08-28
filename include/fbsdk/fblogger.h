#ifndef __FBLOGGER_H__
#define __FBLOGGER_H__
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

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//! Forwarding of class and type declaration.
__FB_FORWARD(FBLogger);
__FB_FORWARD(FBUnion);

////////////////////////////////////////////////////////////////////////////////////
// FBLogger
////////////////////////////////////////////////////////////////////////////////////
/**	FBLogger.
*	Central place to query profiling results and change profiling options.
*   Internal Debug only. Users shouldn't use this code. 
*/
class FBSDK_DLL FBLogger : public FBComponent {
	__FBClassDeclare( FBLogger,FBComponent );
public:
	/**	Constructor.
	*	\param	pObject	For internal use only.
	*/
	FBLogger(HIObject pObject=NULL);

	/**	Get the size of the log.
    *   \return size of the log
	*/
    int GetCount() const;

	/**	GetAt - return a log entry
	*	\param	pIndex - the index (< LogSize) into the log
    *	\return FBUnion value from the log
	*/
    FBUnion GetAt(int pIndex) const;

	/**	Enable - enable logging for a specific type
	*	\param	pTypeInfo - the static TypeInfo value for the FB class we're interested in
	*   \param  pEnable
    *   \return True if the class could be found. 
    */
    bool Enable(int pTypeInfo, bool pEnable);

    /** Enable logging for a specific class ID
    *   \param pClassName The internal ID of class to be traced.
	*   \param pEnable
    *   \return True if the class could be found. 
    */
    bool Enable(const char* pClassName, bool pEnable);

	/** DisableClear - disable and clear the log
	*/
    void DisableClear();

	
	/**	Get the global object for this class
	*	\return	the global object.
	*/
	static FBLogger&		TheOne();
};

#endif // DOXYGEN_SHOULD_SKIP_THIS

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBLOGGER_H__ */
