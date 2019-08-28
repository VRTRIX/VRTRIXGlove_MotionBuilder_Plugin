#ifndef pyfbcharactersolver_h__
#define pyfbcharactersolver_h__
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

#include "pyfbmatrix.h"
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"

// =======================================================================================
// FBCharacterSolver
// =======================================================================================
void FBCharacterSolver_Init();
class FBCharacter_Wrapper;
class PYSDK_DLL FBCharacterSolver_Wrapper : public FBConstraint_Wrapper {
public:
    FBCharacterSolver* mFBCharacterSolver;
public:
	FBCharacterSolver_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBCharacterSolver = (FBCharacterSolver*)pFBComponent; }
	FBCharacterSolver_Wrapper( const char* pName, FBCharacter_Wrapper* pChar, const char* pRegSolver );
	virtual ~FBCharacterSolver_Wrapper( ) { }
    //Target
    object GetTargetCharacter(){ return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterSolver->TargetCharacter ); }
    //void SetTargetCharacter(FBCharacter_Wrapper* pChar){mFBCharacterSolver->TargetCharacter.SetData(pChar);}
    //Source
    object GetSource(){return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterSolver->Source );}
    void SetSource(FBComponent_Wrapper& pComp){mFBCharacterSolver->Source=pComp.mFBComponent;}
    //ExtraFK
    list GetExtraFK() 
    {
        list lReturnList;
        for(int index = 0; index<mFBCharacterSolver->GetExtraFKCount();index++)
        {
            lReturnList.append(FBWrapperFactory::TheOne().WrapFBObject(mFBCharacterSolver->GetExtraFKModelAt(index)));
        }
        return lReturnList;
    }
    void SetExtraFK(list plist)
    {
        int lcount = extract<int>(plist.attr("__len__")()); 
        if(lcount<=mFBCharacterSolver->GetExtraFKCount())
        {
            for ( int i = 0; i < lcount; i++ )
            {
                object lObject = plist[i];
                extract<FBModelMarker_Wrapper*>lExtractor(lObject);
                if(lExtractor.check())
			    {
                    mFBCharacterSolver->SetExtraFKModelAt(lExtractor()->mFBModelMarker,i);				
			    }
                
            }
        }
    }
    //ExtraBones
    list GetExtraBones() 
    {
        list lReturnList;
        for(int index = 0; index<mFBCharacterSolver->GetExtraBoneCount();index++)
        {
            lReturnList.append(FBWrapperFactory::TheOne().WrapFBObject(mFBCharacterSolver->GetExtraBoneModelAt(index)));
        }
        return lReturnList;
    }
    void SetExtraBones(list plist)
    {
        if (plist)
        {
            int lcount = extract<int>(plist.attr("__len__")());
            if (lcount <= mFBCharacterSolver->GetExtraBoneCount())
            {
                for ( int i = 0; i < lcount; i++ )
                {
                    object lObject =plist[i];
                    extract<FBModelSkeleton_Wrapper*>lExtractor(lObject);
                    if (lExtractor.check())
                    {
                        mFBCharacterSolver->SetExtraBoneModelAt(lExtractor()->mFBModelSkeleton, i);
                    }
                }
            }
        }
    }
    int GetExtraBoneIndex(FBModel_Wrapper& pExtraBone)
    {
        int ReturnIndex =-1;
        for(int x=0; x<mFBCharacterSolver->GetExtraBoneCount(); x++)
        {
            if (mFBCharacterSolver->GetExtraBoneModelAt(x)==pExtraBone.mFBModel)
            {
                ReturnIndex = x;
                break;    
            }
        }        
        return ReturnIndex;
    }
    //TransformOffset
    list GetTransformOffset(FBModel_Wrapper& pExtraBone)
    {
        list ReturnList;        
        FBVector3d pT;
        FBRVector pR;
        FBSVector pS;
        mFBCharacterSolver->GetTransformOffset(pT,pR,pS,GetExtraBoneIndex(pExtraBone));
        ReturnList.append(FBVector3d_Wrapper_Factory(pT));
        ReturnList.append(FBVector3d_Wrapper_Factory(pR));
        ReturnList.append(FBVector3d_Wrapper_Factory(pS));
        
        return ReturnList;
    }
    void SetTransformOffset( FBModel_Wrapper& pExtraBone, FBVector3d_Wrapper& pTranslation, FBVector3d_Wrapper& pRotation, FBVector3d_Wrapper& pScaling)
    {
         mFBCharacterSolver->SetTransformOffset(*pTranslation.mFBVector3d, *pRotation.mFBVector3d, *(FBSVector*)pScaling.mFBVector3d, GetExtraBoneIndex(pExtraBone));
    }
    //ParentRotationOffset
    FBVector3d_Wrapper* GetParentRotationOffset(FBModel_Wrapper& pExtraBone)
    {
        FBRVector lParentRot;
        mFBCharacterSolver->GetParentRotationOffset( lParentRot, GetExtraBoneIndex(pExtraBone));
        return FBVector3d_Wrapper_Factory(lParentRot);
    }
    void SetParentRotationOffset(FBModel_Wrapper& pExtraBone, FBVector3d_Wrapper& pRotationOffSet){mFBCharacterSolver->SetParentRotationOffset( *pRotationOffSet.mFBVector3d, GetExtraBoneIndex(pExtraBone) );}
    //RegisteredSolver
    static list GetRegisteredSolverNames()
    {
        list ReturnList;
        for(int x=0; x<FBGetCharacterExternalSolverCount(); x++)
        {
            ReturnList.append(FBGetCharacterExternalSolverName(x));
        }
        return ReturnList;
    }
    int GetRegisteredSolverIndex(const char* pName)
    {
        int lIndex = -1;
        for(int x=0; x<FBGetCharacterExternalSolverCount(); x++)
        {
            if (strcmp(pName,FBGetCharacterExternalSolverName(x))==0)
            {
                lIndex = x;
                break;
            }
        }
        return lIndex;
    }
    
};
#endif // pyfbcharactersolver_h__