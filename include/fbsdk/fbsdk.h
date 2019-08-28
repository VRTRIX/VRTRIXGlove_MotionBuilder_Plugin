#ifndef __FBSDK_H__
#define __FBSDK_H__
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

/**	\file fbsdk.h
*	Base Open Reality SDK include file.
*	This file includes all of the Open Reality files required to use the SDK.
*/

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>
#include <fbsdk/fbconfigfile.h>
#include <fbsdk/fbio.h>

#include <fbsdk/fbmath.h>
#include <fbsdk/fbimage.h>
#include <fbsdk/fbmodel.h>
#include <fbsdk/fbcamera.h>
#include <fbsdk/fblight.h>
#include <fbsdk/fbmodelpath3d.h>
#include <fbsdk/fbplug.h>

#include <fbsdk/fbscene.h>
#include <fbsdk/fbshader.h>
#include <fbsdk/fbsystem.h>
#include <fbsdk/fbplayercontrol.h>
#include <fbsdk/fbevaluatemanager.h>
#include <fbsdk/fbapplication.h>
#include <fbsdk/fbactionmanager.h>
#if !defined(K_NO_RENDERER)
#include <fbsdk/fbrenderer.h>
#endif
#include <fbsdk/fbkeyinggroup.h>

#include <fbsdk/fbprofiler.h>
#include <fbsdk/fblogger.h>
#include <fbsdk/fbunion.h>

#if !defined(K_NO_AUDIO)
	#include <fbsdk/fbaudio.h>
#endif

#if !defined(K_NO_DECK)
	#include <fbsdk/fbdeck.h>
#endif

#if !defined(K_NO_CHARACTER)
	#include <fbsdk/fbcharacter.h>
	#include <fbsdk/fbcharacterface.h>
	#include <fbsdk/fbcharacterextension.h>
    #include <fbsdk/fbcharactersolver.h>
#endif

#if !defined(K_NO_FOLDER)
	#include <fbsdk/fbfolder.h>
#endif

#if !defined(K_NO_MANIPULATOR)
	#include <fbsdk/fbmanipulator.h>
#endif

#if !defined(K_NO_NOTE)
	#include <fbsdk/fbnote.h>
#endif

#if !defined(K_NO_OPTICAL)
	#include <fbsdk/fboptical.h>
#endif

#if !defined(K_NO_POSE)
	#include <fbsdk/fbpose.h>
	#include <fbsdk/fbobjectpose.h>
	#if !defined(K_NO_CHARACTER)
		#include <fbsdk/fbcharacterpose.h>
	#endif
#endif

#if !defined(K_NO_STORY)
	#include <fbsdk/fbstory.h>
#endif

#include <fbsdk/fbmotion.h>

#if !defined(K_NO_VIDEO)
	#include <fbsdk/fbvideo.h>
    #include <fbsdk/fbvideocodecmanager.h>
#endif

#if !defined(K_NO_RENDERER)
	#include <fbsdk/fbvideograbber.h>
#endif

#if !defined(K_NO_CONSTRUCTION_HISTORY)
	#include <fbsdk/fbconstructionhistory.h>
#endif

#include <fbsdk/fbconstraint.h>
#include <fbsdk/fbfilter.h>
#include <fbsdk/fbgroup.h>
#include <fbsdk/fbfilereference.h>
#include <fbsdk/fbpython.h>

#if !defined(K_NO_UI)
	// User interface includes
	#include <fbcontrols/fbcontrols.h>
	#include <fbcontrols/fbgenericmenu.h>
	#include <fbcontrols/fbtool.h>
	#include <fbcontrols/fbuiutil.h>
	#include <fbcontrols/fbconstraintlayout.h>
#if !defined(K_NO_DECK)
	#include <fbcontrols/fbdecklayout.h>
#endif
	#include <fbcontrols/fbdevicelayout.h>
#if !defined(K_NO_MANIPULATOR)
	#include <fbcontrols/fbmanipulatorlayout.h>
#endif
	#include <fbcontrols/fbshaderlayout.h>
	#include <fbcontrols/fbrenderercallbacklayout.h>
	#include <fbcontrols/fbmateriallayout.h>
    #include <fbcontrols/fbtexturelayout.h>
#else
// Define at nothing for now
	inline int FBMessageBox( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str=NULL, const char* pButton3Str=NULL, int pDefaultButton=0, int pScrolledMessage=0) { return pDefaultButton; }
	inline int FBMessageBoxWithCheck( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str, const char* pButton3Str, const char* pCheckBoxStr, bool& pCheckBoxValue, int pDefaultButton=0, int pScrolledMessage=0) { return pDefaultButton; }
#endif

#ifdef _MSC_VER
	#pragma warning (disable: 4702) // unreachable code
#endif

#ifdef FBSDKUseNamespace
	using namespace FBSDKNamespace;
#endif

#endif
