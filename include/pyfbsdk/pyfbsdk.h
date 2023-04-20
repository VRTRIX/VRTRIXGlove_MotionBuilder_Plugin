#ifndef pyfbsdk_h__
#define pyfbsdk_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>

#ifndef PYSDK_DLL
#define PYSDK_DLL K_DLLIMPORT
#endif

#ifdef _MSC_VER
	// Suppress warnings from boost header files.
	#pragma warning(disable:4005) // 'BOOST_NO_AUTO_PTR': macro redefinition
	#pragma warning(disable:4100) // Unreferenced formal parameter.
	#pragma warning(disable:4244) // Conversion from 'long double' to 'double', possible loss of data.
	#pragma warning(disable:4459) // declaration of 'xxxx' hides global declaration
#endif

#include <boost/python.hpp>
using namespace boost::python;

#include <fbsdk/fbsdk.h>

#if !defined(K_NO_UNDO)
#include <fbsdk/fbundomanager.h>
#endif

#ifdef FB_KERNEL
#include <fbkernel/fbkernel.h>
#endif

#include <fbsdk/fbmultilang.h>
#if !defined(K_NO_PROJECTSETTINGS)
#include <fbsdk/fbprojectsettings.h>
#endif

#ifndef PYFBSDKNamespace
#define PYFBSDKNamespace                PYFBSDK
#define PYFBSDKNamespaceFunc( Name )    PYFBSDKNamespace::Name
#endif

namespace PYFBSDKNamespace {

// TODO:
// o Que faire des operator =??? <<<<IMPORTANT>>>>>
// o Pass by ref
// o Pass by ptr
// o Property 'OnUIIdle'
// o Method taking lists as arguments
// o Method returning a list of elements ( such as FBCamera::GetMatrix() )
// o how to deal with methods 'operator ()', 'operator TYPE*()', 'operator =()', etc...

#include "pyfbutils.h"
#include "pyfbcallback.h"
#include "pyfbpythonwrapper.h"
#include "pyfbwrapperfactory.h"

//////////////////////////////////////////////////////////////////
//
// CLASS: FBTime
//
//////////////////////////////////////////////////////////////////

#include "pyfbtime.h"
#include "pyfbtimespan.h"

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// CLASS: FBMath
//
//////////////////////////////////////////////////////////////////

#include "pyfbvector.h"

//////////////////////////////////////////////////////////////////

#include "pyfbplug.h"

//////////////////////////////////////////////////////////////////
//
// CLASS: FBProperty
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "pyfbproperty.h"
#include "pyfbpropertylist.h"

#if !defined(K_NO_PROJECTSETTINGS)
	class FBProjectSettings_Wrapper;
	FBProjectSettings_Wrapper* FBProjectSettings_Wrapper_Factory(FBProjectSettings*);
#endif

//////////////////////////////////////////////////////////////////

#include "pyfbpropertymanager.h" 
#include "pyfbcomponent.h" 

#if !defined(K_NO_PROJECTSETTINGS)
#include "pyfbprojectsettings.h"
#endif

#ifdef FB_KERNEL 
#include "pyfbkernel.h"
#endif

#include "pyfbenum.h"

#include "pyfbmatrix.h"
#include "pyfbmath.h"

#include "pyfbstringlist.h"

#include "pyfbconfigfile.h"
#include "pyfbplotoptions.h"
#if !defined(K_NO_RENDERER)
	#include "pyfbvideograboptions.h"
	#include "pyfbaudiorenderoptions.h"
#endif

#include "pyfbmultilangmanager.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurvekey.h"
#include "pyfbviewingoptions.h"
#include "pyfbconstraintinfo.h"

#include "pyfbaudioin.h"
#include "pyfbaudioout.h"
#include "pyfbaudioclip.h"
#include "pyfbmotionclip.h"
#include "pyfbimage.h"
#if !defined(K_NO_RENDERER)
	#include "pyfbvideograbber.h"
	#include "pyfbvideocodecmanager.h"
#endif

#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#if !defined(K_NO_DECK)
	#include "pyfbdeck.h"
#endif

#include "pyfbdeformer.h"
#include "pyfbpointcachefile.h"
#include "pyfbdeformerpointcache.h"
#include "pyfbgloballight.h"
#include "pyfbreferencetime.h"
#include "pyfbanimationlayer.h"
#include "pyfbtake.h"
#if !defined(K_NO_UNDO)
	#include "pyfbundomanager.h"
	#if !defined(K_NO_CONSTRUCTION_HISTORY)
		#include "pyfbconstructionhistory.h"
	#endif
#endif

#include "pyfbplayercontrol.h"
#include "pyfbcyclecreator.h"
#include "pyfbevaluatemanager.h"
#include "pyfbkeycontrol.h"
#include "pyfbboxplaceholder.h"
#if !defined(K_NO_MANIPULATOR)
	#include "pyfbhandle.h"
#endif
#if !defined(K_NO_NOTE)
	#include "pyfbnote.h"
#endif
#ifndef FB_KERNEL 
	#include "pyfbuserobject.h"
#endif

#include "pyfbvideo.h"
#include "pyfbvideoclip.h"
#include "pyfbvideoin.h"
#include "pyfbvideoout.h"
#include "pyfbtexture.h"
#include "pyfblayeredtexture.h"
#include "pyfbmaterial.h"
#include "pyfbgeometry.h"
#include "pyfbmesh.h"
#include "pyfbsurface.h"
#include "pyfbnurbs.h"
#include "pyfbpatch.h"

#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"	// Requires FBModel_Wrapper from class_f_b_model_gen.h.

#include "pyfbmodelplaceholder.h"
#include "pyfbpose.h"
#include "pyfbshadermodelinfo.h"
#include "pyfbmodeltemplate.h"
#include "pyfbconstraint.h"
#include "pyfbconstraintrelation.h"
#include "pyfbconstraintsolver.h"
#include "pyfbconstraintmanager.h"
#include "pyfbphysicalproperties.h"
#include "pyfbdevicenotifyinfo.h"
#include "pyfbdevice.h"
#include "pyfbdeviceinstrument.h"
#include "pyfbfilter.h"
#include "pyfbfiltermanager.h"
#include "pyfbcluster.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelnull.h"
#include "pyfbmodelplane.h"
#include "pyfbmodelroot.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmodelpath3d.h"

#ifndef K_NO_OPTICAL
	#include "pyfbmodeloptical.h"
	#include "pyfbopticalsegment.h"
	#include "pyfbopticalgap.h"
	#include "pyfbmodelmarkeroptical.h"
	#include "pyfbrigidbody.h"
	#include "pyfbdeviceoptical.h"
	#include "pyfbdeviceopticalmarker.h"
	#include "pyfbmodelopticaladvanced.h"
#endif

#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h
#include "pyfbcharacterposeoptions.h"
#include "pyfbcharacterpose.h"
#include "pyfbcycleanalysisnode.h"

#include "pyfbcontrolset.h"
#include "pyfbmodelcube.h"
#include "pyfbcamera.h"
#include "pyfbcamerastereo.h"
#include "pyfbcameraswitcher.h"
#include "pyfblight.h"
#include "pyfbshader.h"
#include "pyfbshaderlighted.h"
#include "pyfbshadershadowlive.h"
#include "pyfbshadermanager.h"
#include "pyfbgroup.h"
#include "pyfbfolder.h"
#include "pyfbset.h"
#include "pyfbfilereference.h"
#include "pyfbscene.h"
#include "pyfbhud.h"
#include "pyfbhudmanager.h"
#include "pyfbrenderer.h"					// Requires FBPickListInfo_Wrapper from pyfbarraytemplate.h
#include "pyfbrenderoptions.h"

#include "pyfbbatchoptions.h"
#include "pyfbfbxoptions.h"
#include "pyfbmotionfileoptions.h"
#include "pyfbapplication.h"
#include "pyfbstoryfolder.h"
#include "pyfbstorytrack.h"
#include "pyfbstoryclip.h"
#include "pyfbstorygroupclip.h"
#include "pyfbstory.h"
#include "pyfbdirmap.h"

#if defined(KPROFILING_CODE_ENABLE)
	#include "pyfbprofiler.h"
	#include "pyfbprofiletaskcycle.h"
	#include "pyfbprofiletimeevent.h"
#endif

#if !defined(K_NO_ASSETMNG)
	#include "pyfbassetitem.h"
	#include "pyfbassetfile.h"
	#include "pyfbassetfolder.h"
	#include "pyfbassetmng.h"
#endif
#include "pyfbsystem.h"
#include "pyfbpointcachemanager.h"
#include "pyfbtimewarpmanager.h"
#include "pyfbfilemonitoringmanager.h"

	#if !defined(K_DISABLE_UI)
	#include "pyfbprogress.h"
	#include "pyfbgenericmenuitem.h"
	#include "pyfbgenericmenu.h"
	#include "pyfbmenumanager.h"
	#include "pyfbvisualcomponent.h"
	#include "pyfbfilepopup.h"
	#include "pyfbfolderpopup.h"
	#include "pyfblayout.h"
	#include "pyfbtool.h"
	#include "pyfbbutton.h"
	#include "pyfbbrowsingproperty.h"
	#include "pyfbarrowbutton.h"
	#include "pyfbscrollbox.h"
	#include "pyfbedit.h"
	#include "pyfbeditnumber.h"
	#include "pyfblabel.h"
	#include "pyfbspreadpart.h"
	#include "pyfbspreadrow.h"
	#include "pyfbspreadcolumn.h"
	#include "pyfbspreadcell.h"
	#include "pyfbspread.h"
	#include "pyfbtabpanel.h"
	#include "pyfbslider.h"
	#include "pyfbthermometer.h"
	#include "pyfblayoutregion.h"
	#include "pyfbimagecontainer.h"
	#include "pyfbeditcolor.h"
	#include "pyfbeditvector.h"
	#include "pyfblist.h"
	#include "pyfbtreenode.h"
	#include "pyfbtree.h"
	#include "pyfbeditproperty.h"
	#include "pyfbeditpropertymodern.h"
	#include "pyfbview.h"
	#include "pyfbmemo.h"
	#include "pyfbfcurveeditor.h"
	#include "pyfbpropertyconnectioneditor.h"
	#include "pyfbvisualcontainer.h"
	#include "pyfbtimecode.h"
	#include "pyfbpopup.h"
	#include "pyfbplotpopup.h"
	#include "pyfbpropertyviewmanager.h"
	#include "pyfbpropertyviewlist.h"
	#include "pyfbpropertyviewdefinition.h"
	#include "pyfbfcurveeditorutility.h"
#endif

#include "pyfbglobal.h"


#include "pyfbmanipulator.h"

};

using namespace PYFBSDKNamespace;
#endif // pyfbsdk_h__