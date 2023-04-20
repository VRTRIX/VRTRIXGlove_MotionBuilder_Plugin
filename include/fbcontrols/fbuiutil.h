#ifndef __FBUIUTIL_H__
#define __FBUIUTIL_H__
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

/**	\file fbuiutil.h
*	Contains a few user-interface utilities.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbcontrols/fbcontrols.h>
class QMainWindow;

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyInspector
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPropertyInspector );

/** Property inspector class.
*	This class is used to inspect the properties of a component (including events) and
*	display the information in a spreadsheet form.
*/
class FBSDK_DLL FBPropertyInspector : public FBSpread {
	__FBClassDeclare( FBPropertyInspector,FBSpread );
public:
	//! Constructor.
	FBPropertyInspector();

	FBPropertyComponent	Component;		//!< <b>Property:</b>	Component to inspect.
	FBStringList*		Components;		//!< <b>List:</b>		Child components.
	FBStringList*		Events;			//!< <b>List:</b>		Events associated.
};

/** Return the MotionBuilder main window.
*	\return	The MotionBuilder main window.

	The following Python snippet shows how to get the MotionBuilder main window.
    \code
        from PySide2 import QtWidgets
        import shiboken2

        def getMainWindow():
            ptr = FBGetMainWindow()
            if ptr is not None:
                return shiboken2.wrapInstance(ptr, QtWidgets.QWidget)

        mainWindow = getMainWindow()
        if mainWindow is not None:
            print( mainWindow.windowTitle() )
        else:
            print( "MotionBuilder main window not found!" )
    \endcode
*/
FBSDK_DLL QMainWindow* FBGetMainWindow();

/** Return a platform-specific native window handle for the specified widget. It is similar of calling QWidget::effectiveWinId().
*	\param	pWidget		Widget whose native window handle is to be returned.
*	\return	The native window handle of the specified widget. On Linux this will be an Xlib 'Window'. On Microsoft Windows it will be an 'HWND'.

	The following C++ snippet shows how to get the MotionBuilder main window native window handle.
    \code
        QMainWindow* lMainWindow = FBGetMainWindow();
        #ifdef KARCH_ENV_WIN
            HWND lMainWindowHWND = (HWND)FBGetNativeWindowHandle( lMainWindow );
        #else
            // typedef unsigned long XID;
            // typedef XID Window;
            Window lMainWindowHWND = (Window)FBGetNativeWindowHandle( lMainWindow );
        #endif
    \endcode
*/
FBSDK_DLL void* FBGetNativeWindowHandle( QWidget* pWidget );

#ifdef FBSDKUseNamespace
	}
#endif
#endif
