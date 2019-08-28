#ifndef pyfbshadermanager_h__
#define pyfbshadermanager_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbstringlist.h"

// =======================================================================================
// FBShaderManager
// =======================================================================================
void FBShaderManager_Init();

class PYSDK_DLL FBShaderManager_Wrapper {
public:
	FBShaderManager* mFBShaderManager;
public:
    FBShaderManager_Wrapper(  ) : mFBShaderManager( new FBShaderManager ) {}
	virtual ~FBShaderManager_Wrapper( ) { delete mFBShaderManager; }
	object CreateShader(const char * pShaderTypeName) {
        object lResult;

        FBShader* lShader = mFBShaderManager->CreateShader( pShaderTypeName );
        if( lShader )
        {
            if( lShader->Is( FBShaderLighted::TypeInfo ))
            {
                lResult = FBWrapperFactory::TheOne().WrapFBObject( (FBShaderLighted*) lShader );
            }
            else if( lShader->Is( FBShaderShadowLive::TypeInfo ))
            {
                lResult = FBWrapperFactory::TheOne().WrapFBObject( (FBShaderShadowLive*) lShader );
            }
            else
            {
                lResult = FBWrapperFactory::TheOne().WrapFBObject( lShader );
            }
        }
        return lResult;
    }
	FBStringList_Wrapper* GetShaderTypeNames(  ) { return FBStringList_Wrapper_Factory( &( mFBShaderManager->ShaderTypeNames )); }
	FBStringList_Wrapper* GetShaderTypeNamesLocalized(  ) { return FBStringList_Wrapper_Factory( &( mFBShaderManager->ShaderTypeNamesLocalized )); }
};
#endif // pyfbshadermanager_h__