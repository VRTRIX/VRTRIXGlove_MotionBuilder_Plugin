/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxrenamingstrategymaya.h
#ifndef _FBXSDK_UTILS_RENAMINGSTRATEGY_MAYA_H_
#define _FBXSDK_UTILS_RENAMINGSTRATEGY_MAYA_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/utils/fbxrenamingstrategybase.h>
#include <fbxsdk/utils/fbxrenamingstrategyutilities.h>
#include <fbxsdk/scene/fbxscene.h>
#include <fbxsdk/utils/fbxnamehandler.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FBXSDK_DLL FbxRenamingStrategyMaya : public FbxRenamingStrategyBase
{
public:

    FbxRenamingStrategyMaya();
    virtual ~FbxRenamingStrategyMaya();

    bool DecodeScene(FbxScene* pScene) override;
    bool EncodeScene(FbxScene* pScene) override;
    bool DecodeString(FbxNameHandler& pName) override;
    bool EncodeString(FbxNameHandler& pName, bool pIsPropertyName=false) override;
    void CleanUp() override;
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_RENAMINGSTRATEGY_MAYA_H_ */
