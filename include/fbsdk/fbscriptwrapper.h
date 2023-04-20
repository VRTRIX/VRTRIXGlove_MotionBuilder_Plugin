#ifndef __FBSCRIPT_WRAPPER_H__
#define __FBSCRIPT_WRAPPER_H__
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

/**	\file fbtrigger.h
*	Basic classes for trigger tree manipulation.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbdefines.h>
#include <fbsdk/fbarray.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBWrapperInterface
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBScriptWrapper );
/**
    This interface is used to bridge ORSDK and Python exposition.
    It allows each FBObject to notify its wrapper about its destruction.
    It also allows a Python Exposition code to know if a particular FBObject
    is already wrapped.
*/

class FBScriptWrapper
{
public:
    virtual ~FBScriptWrapper() = default;
    virtual void ContentDestroy() = 0;    
};

FB_FORWARD( FBWrapperHolder );
class FBSDK_DLL FBWrapperHolder
{
public:
    FBWrapperHolder();
    virtual ~FBWrapperHolder();

    //! Return the wrapper interface of this FBObject
    FBScriptWrapper* GetWrapper();
    void AddWrapper( FBScriptWrapper* );
    void RemoveWrapper( FBScriptWrapper* );
private:
    FBArrayTemplate<FBScriptWrapper*>  mWrapperArray;
};


#ifdef FBSDKUseNamespace
}
#endif
#endif /* _FB_SCRIPT_WRAPPER_H_ */
