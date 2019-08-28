#ifndef __FBUSEROBJECT_H__
#define __FBUSEROBJECT_H__
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

__FB_FORWARD(FBUserObject);
FB_DEFINE_COMPONENT(FBSDK_DLL, UserObject);

//////////////////////////////////////////////////////////////////////////////////////
//FBUserObject Register
//////////////////////////////////////////////////////////////////////////////////////
#define FBUserObjectImplement(ClassName, Description, IconFilename)\
	HIObject RegisterUserObject##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
		ClassName* Class = new ClassName(pName);\
		Class->mAllocated = true;\
		if( Class->FBCreate() ){\
			return Class->GetHIObject();\
		} else {\
			delete Class;\
			return NULL;}}\
	FBLibraryModule(ClassName){\
		FBRegisterObject(ClassName##R2, "FbxStorable/User", #ClassName, Description, RegisterUserObject##ClassName##Create, true, IconFilename);}\
	FB_FORWARD(ClassName);\
	int ClassName::ClassId = FBRegister_ClassId(#ClassName);\
	int ClassName::GetUserClassId(){\
		return ClassId; }\
	const char* ClassName::FbxGetObjectSubType(){\
		return #ClassName;}

////////////////////////////////////////////////////////////////////////////////////
// FBUserObject
////////////////////////////////////////////////////////////////////////////////////
class FBSDK_DLL FBUserObject : public FBBox
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBUserObject, FBBox);
	FBDeclareUserObject(FBUserObject);

public:
	/**	Constructor.
	*	\param	pName	User object name.
	*	\param	pObject	For internal use only.
	*/
	FBUserObject(const char* pName, HIObject pObject=NULL);

	/**	Store and Retrieve function that can be overloaded.
	*	\param	pFbxObject	FBX Object that is used to communicate I/O operations.
	*	\param	pStoreWhat	Which attributes are currently stored/retrieved.
	*/
	virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat) override;
	virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat) override;
};

////////////////////////////////////////////////////////////////////////////////////
// FBUserObjectList
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: UserObject.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListUserObject : public FBPropertyListComponent
{
  public:
    FBPropertyListUserObject();
	/**	Get the UserObject at \e pIndex.
	*	\param	pIndex	Index of UserObject to get a handle on.
	*	\return UserObject at \e pIndex.
	*/
	FBUserObject* operator[](int pIndex);
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBUSEROBJECT_H__ */
