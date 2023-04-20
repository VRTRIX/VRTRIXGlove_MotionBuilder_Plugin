#ifndef __FBKERNEL_H__
#define __FBKERNEL_H__
/**************************************************************************
 Copyright (c) 1994 - 2006 Autodesk, Inc. and/or its licensors.
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

/**	\file fbkernel.h
*	FiLMBOX kernel header file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbrenderer.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBKernel );

#if defined(KARCH_ENV_WIN32)
	typedef struct TOpaqueInstance*		TInstance;
#endif

/**	The MotionBuilder kernel
*	This class permits launching the MotionBuilder engine on its own.
*/
class FBSDK_DLL FBKernel : public FBComponent
{
	__FBClassDeclare( FBKernel, FBComponent );
  public:
	//! Constructor.
	FBKernel();

	/**	Initialization.
	*	\param	pLibraryDirectory	Library directory (for *.dlls).
	*	\return	\b true if successful.
	*/
	virtual bool Init  (const char *pLibraryDirectory);

	/** Initialise the kernel opengl.
	*	\return	\b true if successful.
	*/
	bool InitOpenGL();

	/** Close the kernel.
	*	\return	\b true if successful.
	*/
	virtual bool Close ();

#if defined(FB_KERNEL) && !defined(K_NO_UI) 
	void InitKernelUI();
#endif

	/**	Notification of Keyboard input.
	*	\param	pKey	Actual key pressed.
	*	\param	pState	true when key is down.
	*	\return	\b true if handled.
	*/
	virtual bool OnDeviceKeyboardInput( FBDeviceKeyboardKey pKey, bool pState );

	/**	Hook to keyboard manager to steal key from hooked application.
	*	\param	pActive	set to true to activate hook.
	*	\param	pModuleHandle or pWindowRef	depending on the platform.
	*	\return	\b true if successful.
	*/
	#if defined(KARCH_ENV_WIN32)
	    /**	Hook to keyboard manager to steal key from hooked application.
	    *	\param	pActive	set to true to activate hook.
	    *	\param	pModuleHandle client dll handle.
	    *	\return	\b true if successful.
	    */
		bool	HookKeyboard(bool pActive, TInstance pModuleHandle);
	#endif

	/**	Get the global FBKernel object
	*	\return	the global object.
	*/
	static FBKernel& TheOne();
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* this must be the last line of this file */
