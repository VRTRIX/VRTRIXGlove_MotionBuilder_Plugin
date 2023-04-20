#ifndef __FBMODULEMANAGER_H__
#define __FBMODULEMANAGER_H__
// =======================================================================
// Copyright 2020 Autodesk, Inc. All rights reserved.
//
// This computer source code and related instructions and comments are the
// unpublished confidential  and proprietary information of Autodesk, Inc.
// and are protected under applicable copyright and trade secret law. They 
// may not be disclosed to, copied  or used by any third party without the 
// prior written consent of Autodesk, Inc.
// =======================================================================

/**	\file fbmodulemanager.h
*	
*	The FBModuleManager file contains the necessary declarations to 
*	interface with the underlying module manager.
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
#endif //FBSDKUseNamespace

FB_FORWARD( FBModuleManager );
FB_DEFINE_COMPONENT( FBSDK_DLL, FBModuleManager );

/** Module Manager class.
*   <b>This class is introduced to enable users to access information related to the loaded modules.</b>
*/
class FBSDK_DLL FBModuleManager: public FBComponent
{
    FBClassDeclare( FBModuleManager, FBComponent );

public:
	/** Returns the module search paths where *.mod files can be parsed.
	*
	*	By default, there are two module search paths:
	*	- $(UserConfigDir)/config/Modules
	*	- $(UserConfigDir)/../../Modules
	*	Users can prepend additional module search paths by setting the "MOTIONBUILDER_MODULE_PATH" environment variable before launching the application.
	*
	*	\return The module search paths.
	*/
	FBStringList GetModuleSearchPaths() const;

	/** Returns the loaded module names found in the *.mod files parsed.
	*	\return The loaded module names.
	*/
	FBStringList GetLoadedModuleNames() const;

	/** Returns the module path associated with the provided loaded module name.
	*	\param pModuleName The loaded module name to query.
	*	\return The module path.
	*/
	const char* GetModulePath( const char* pModuleName ) const;

	/** Returns the module version associated with the provided loaded module name.
	*	\param pModuleName The loaded module name to query.
	*	\return The module version.
	*/
	const char* GetModuleVersion( const char* pModuleName ) const;

	/** Returns the *.mod file path containing the definition of the provided loaded module name.
	*	\param pModuleName The loaded module name to query.
	*	\return The *.mod file path.
	*/
	const char* GetModuleModFilePath( const char* pModuleName ) const;

    /** Returns the only instance of FBModuleManager.
    * \return The only instance of FBModuleManager.
    */
    static FBModuleManager& TheOne();

protected:
	/** Constructor.
		Protected constructor, use TheOne() access instead.
	*/
	FBModuleManager();
};

#ifdef FBSDKUseNamespace
}
#endif //FBSDKUseNamespace

#endif //__FBMODULEMANAGER_H__