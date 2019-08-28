#ifndef pyfbdevicenotifyinfo_h__
#define pyfbdevicenotifyinfo_h__
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

// =======================================================================================
// FBDeviceNotifyInfo
// =======================================================================================
void FBDeviceNotifyInfo_Init();

class PYSDK_DLL FBDeviceNotifyInfo_Wrapper {
public:
	FBDeviceNotifyInfo* mFBDeviceNotifyInfo;
public:
	FBDeviceNotifyInfo_Wrapper() { mFBDeviceNotifyInfo = new FBDeviceNotifyInfo; }
	virtual ~FBDeviceNotifyInfo_Wrapper( ) { delete mFBDeviceNotifyInfo; }
	FBTime_Wrapper* GetLocalTime() { return FBTime_Wrapper_Factory( mFBDeviceNotifyInfo->GetLocalTime(  )); }
	int GetSyncCount() { return mFBDeviceNotifyInfo->GetSyncCount(  ); }
	FBTime_Wrapper* GetSystemTime() { return FBTime_Wrapper_Factory( mFBDeviceNotifyInfo->GetSystemTime(  )); }
};
#endif // pyfbdevicenotifyinfo_h__