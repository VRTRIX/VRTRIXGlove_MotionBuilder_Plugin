#ifndef __FBTRACKER_H__
#define __FBTRACKER_H__
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

/**	\file fbtracker.h
*	Generic camera tracker interface
*/
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

/**************************************************************************
 **************************************************************************/
//!	Returns the time mode for the current system sync.
FBSDK_DLL FBTimeMode FBGetSyncTimeMode();

/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceSyncPacket );
/**	Sync'ed device packet.
*	Data packet base class for packets that correspond
*	to a device that is timestamping the data in order to
*	genlock the application to an incoming data stream.
*/
class FBSDK_DLL FBDeviceSyncPacket : public FBComponent
{
	__FBClassDeclare( FBDeviceSyncPacket, FBComponent );
  public:
	FBDeviceSyncPacket();			//!< Constructor.

  public:
	FBPropertyInt	OriginalSync;	//!< <b>Property:</b> Sync count for packet (from Application).
	FBPropertyInt	CorrectedSync;	//!< <b>Property:</b> Corrected sync count  (from Sync queue).
	FBPropertyInt	DeviceSync;		//!< <b>Property:</b> Sync count for packet (from Device).
};

/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceSync );
/** Sync'ed device class.
*	Base class for devices that are streaming data that will
*	be accessed based upon a sync'ed stream (such as a genlock).
*/
class FBSDK_DLL FBDeviceSync : public FBDevice
{
	__FBClassDeclare( FBDeviceSync, FBDevice );
  public:
	/** Constructor
	*	\param	pName	Name of device sync.
	*	\param	pObject	Internal use only(default=NULL).
	*/
	FBDeviceSync(const char* pName, HIObject pObject=NULL);
	/** Print to screen animation info
	*	\param	pSync			Application sync.
	*	\param	pSyncPacket		Device sync packet.
	*	\param	pEvaluateInfo	Information for evaluation.
	*/
	virtual void PrintDebugAnimInfo		( int pSync, FBDeviceSyncPacket* pSyncPacket, FBEvaluateInfo* pEvaluateInfo );
	/** Print to screen input/output info
	*	\param	pSyncPacket			Device sync packet.
	*	\param	pDeviceNotifyInfo	Device notification info.
	*/
	virtual void PrintDebugIOInfo		( FBDeviceSyncPacket* pSyncPacket, FBDeviceNotifyInfo& pDeviceNotifyInfo );
	/** Print to screen input/output notification info
	*	\param	pInfo			Device sync packet.
	*	\param	pPacketCount	Device notification info.
	*/
	virtual void PrintDebugIONotifyInfo	( FBDeviceNotifyInfo& pInfo, int pPacketCount );

    // Standard device virtual functions creation/destruction
	virtual bool FBCreate	();
	virtual void FBDestroy	();

	// Overloaded FBDevice functions
	virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo	);
    virtual bool FbxStore			( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat	);
	virtual bool FbxRetrieve		( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat	);

	/**	Real-Time synchronous evaluation callback.
	*	Note that this function must be overloaded to instanciate a synchronous device class.
	*	\param	pAnimationNode		Connector being pulled.
	*	\param	pEvaluateInfo		Evaluation information structure.
	*	\param	pCorrectedSync		Corrected sync value.
	*/
	virtual bool DeviceSyncAnimationNodeNotify( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo, int pCorrectedSync ) = 0;

	//--- Packet registration
	/** Register a packet in the buffer.
	*	This will determine the buffer size (based on the number of packets that are added).
	*	Each packet should be allocated dynamically just before being added then registered to the device, 
	*	which will then take complete ownership (and will destroy the packet itself).
	*	\param	pPacket	Newly allocated packet to register in the buffer.
	*/
	virtual void PacketRegister( FBDeviceSyncPacket* pPacket );

	//--- DeviceIONotify() calls
	/**	Lock a packet from the queue.
	*	Locks a packet for modification (write), to be used in the DeviceIONotify Function
	*	\return	A packet in the buffer that is protected for write operations. 
	*	To be used in DeviceIONotify() for locking a packet being read from the device.
	*/
	virtual FBDeviceSyncPacket*	PacketLock ();
	/** Unlock a previously locked packet.
	*	Unlocks a packet \e pPacket, indicating whether or not the packet is valid. If valid,
	*	the packet is kept in the buffer. Otherwise, the packet is listed as being free
	*	for the other write operations. To be used in DeviceIONotify() for unlocking a packet 
	*	being read from the device.
	*	\param	pPacket			Packet to unlock.
	*	\param	pValidPacket	Is the packet valid data or not.
	*/
	virtual void PacketUnlock ( FBDeviceSyncPacket* pPacket, bool pValidPacket );

	//--- AnimationNodeNotify() calls
	/** Fetch the data packet for the requested sync count.
	*	Given a requested sync count, \e pRequestedSync, return the data packet
	*	that corresponds to this count in the queue. This routine will also protect
	*	the packet from write operations, requiring a call to PacketRelease when
	*	the current use is finished. To be used in AnimationNodeNotify() for locking a packet 
	*	being read from the device.
	*	\param	pRequestedSync	Desired packet sync count.
	*	\return	The packet corresponding to the sync count.
	*/
	virtual FBDeviceSyncPacket*	PacketFetch( int pRequestedSync );
	/**	Release a fetched packet.
	*	Finish a read process of a specified packet \e pPacket. This will make the
	*	packet available to be read/modified by other processes. To be used in 
	*	AnimationNodeNotify() for unlocking a packet being read from the device.
	*/
	virtual void PacketRelease( FBDeviceSyncPacket* pPacket	);

	//--- Queue management
	/** Remove a packet from the packet queue.
	*	\param	pPacketIndex	Index of packet to remove.
	*	\return	Newly removed packet.
	*/
	virtual FBDeviceSyncPacket* PacketRemove( int pPacketIndex );
	/** Get the number of packets in the queue.
	*	\return	The current number of packets in the queue.
	*/
	virtual int PacketGetCount();

  public:
	FBPropertyInt		PacketBufferSize;		//!< <b>Property:</b> Packet buffer size(default=100).
	FBPropertyInt		SyncDelay;				//!< <b>Property:</b> Synchronization delay (in sync count units).
	FBPropertyBool		DebugInfo;				//!< <b>Property:</b> Debugging Info?
};

/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceCameraPacket );
/** Camera device packet.
*	Contains information necessary to position a virtual camera in 3D space.
*/
class FBSDK_DLL FBDeviceCameraPacket : public FBDeviceSyncPacket
{
	__FBClassDeclare( FBDeviceCameraPacket, FBDeviceSyncPacket );
public:
	FBDeviceCameraPacket();				//!< Constructor.

	FBPropertyVector3d	Position;		//!< <b>Property:</b> Position of camera.
	FBPropertyVector3d	Rotation;		//!< <b>Property:</b> Orientation of camera.
	FBPropertyVector3d	Offset;			//!< <b>Property:</b> Camera offset.
	FBPropertyVector2d	FieldOfView;	//!< <b>Property:</b> Field of View (X,Y) of camera lens.
	FBPropertyVector2d	OpticalCenter;	//!< <b>Property:</b> Optical Center of camera lens.
	FBPropertyDouble	Focus;			//!< <b>Property:</b> Focus encoder value (relative).
	FBPropertyDouble	Zoom;			//!< <b>Property:</b> Zoom encoder value.
	FBPropertyTime		Time;			//!< <b>Property:</b> Time of packet.
};
FB_DEFINE_COMPONENT( FBSDK_DLL, DeviceCameraPacket );

/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceCameraInstrument );
/**	Instrument for a camera device.
*	This instrument provides the necessary parameters to provide camera
*	tracking support in a device driver (the FBDeviceCamera class
*	and its derivatives).
*	This will also provide a management system for lens look-up tables. Lens
*	tables are used in order to interpret linear encoder values with the non-
*	linear changes in the actual lens.
*/
class FBSDK_DLL FBDeviceCameraInstrument : public FBDeviceInstrument
{
	__FBClassDeclare( FBDeviceCameraInstrument, FBDeviceInstrument );
  public:
	/**	Constructor.
	*	\param	pDevice	Parent device.
	*/
	FBDeviceCameraInstrument( FBDevice* pDevice );

	/**	Load the lens lookup tables.
	*	\param	pFilename	Name of *.klc file with lens values.
	*	\return	\b true if successful.
	*/
	virtual bool LoadLensTables( const char* pFilename );
	/**	Process the lens table data for this data packet.
	*	The actual operation for this will depend on a couple of properties 
	*	for the instrument: \b LensTableLoaded, \b LensMode, as well as the 
	*	invert values and the zoom multiplier.
	*	\param	pDataPacket	Camera data to process with the lens tables.
	*/
	virtual void ProcessLensData( FBDeviceCameraPacket* pDataPacket );

	// See parent class.
	virtual bool InstrumentWriteData( FBEvaluateInfo* pEvaluateInfo ) override;
	virtual void InstrumentRecordFrame( FBTime pRecordTime, FBDeviceNotifyInfo& pNotifyInfo ) override;
    virtual bool FbxStore( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat ) override;
	virtual bool FbxRetrieve( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat ) override;

	// Packet of information
	FBPropertyDeviceCameraPacket	Packet;			//!< \b Property(RW): Used as a buffer to contain the current state of the instrument, use to put data in connector.
    FBPropertyDeviceCameraPacket	RecordPacket;   //!< \b Property(RW): Used as a buffer to contain the record state of the instrument, use to create the keys when recording.
	// Lens options
	FBPropertyBool		LensTableLoaded;			//!< \b Property(R-): Has the lens table been loaded?
	FBPropertyString	LensCalibrationFilename;	//!< \b Property(R-): Lens calibration filename.

	FBPropertyBool		ManualFovMode;				//!< \b Property(RW): In manual mode (not using encoder values to control zoom)?
	FBPropertyDouble	ManualFovX;					//!< \b Property(RW): Manual field of view X value.
	FBPropertyDouble	ManualFovY;					//!< \b Property(RW): Manual field of view Y value.
	FBPropertyBool		ManualCenterMode;			//!< \b Property(RW): Manually  adjust the optical center?
	FBPropertyDouble	ManualCenterX;				//!< \b Property(RW): Manual optical center X coordinate.
	FBPropertyDouble	ManualCenterY;				//!< \b Property(RW): Manual optical center Y coordinate.
	FBPropertyBool		LensFovInDegrees;			//!< \b Property(RW): Is FOV in table in degrees (false)
	FBPropertyBool		InvertZoom;					//!< \b Property(RW): Invert the zoom encoder values?
	FBPropertyBool		InvertFocus;				//!< \b Property(RW): Invert the focus encoder values?
	FBPropertyDouble	ZoomMultiplier;				//!< \b Property(RW): Filmback multiplier.
	FBPropertyDouble	NodalMultiplier;			//!< \b Property(RW): Multiplier for nodal offset.
	FBPropertyVector3d	TranslationOffset;			//!< \b Property(RW): Translation offset;
	FBPropertyVector3d	RotationOffset;				//!< \b Property(RW): Rotation offset.
	FBPropertyDouble	AspectRatio;				//!< \b Property(RW): Aspect ratio for calculating the Field of View X value.
};

/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceCamera );
/** Camera device base class.
*	Based on the FBDeviceSync class, this class generalizes the concept
*	of a virtual set camera driver, permitting synchronization with
*	a genlock source, generic camera connectors, and model templates.
*/
class FBSDK_DLL FBDeviceCamera : public FBDeviceSync
{
	__FBClassDeclare( FBDeviceCamera,FBDeviceSync );
  public:
	/**	Constructor.
	*	\param	pName		Unique name of optical device.
	*	\param	pObject		Internal parent object(default=NULL).
	*/
	FBDeviceCamera(const char* pName, HIObject pObject=NULL);

    // Standard device virtual functions creation/destruction
    virtual bool FBCreate	();
    virtual void FBDestroy	();

	// Overloaded parent functions
	virtual bool DeviceSyncAnimationNodeNotify	( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo, int pCorrectedSync );
	virtual void DeviceIONotify					( kDeviceIOs pAction, FBDeviceNotifyInfo& pDeviceNotifyInfo	);
    virtual bool ModelTemplateBindNotify( FBModel* pModel,int pIndex, FBModelTemplate* pModelTemplate		);
    virtual bool FbxStore				( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat	);
	virtual bool FbxRetrieve			( FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat	);
	virtual void RecordingInitAnimation	( FBAnimationNode* pAnimationNode );
	virtual void RecordingDoneAnimation	( FBAnimationNode* pAnimationNode );

	/**	Evaluation engine callback for camera device.
	*	\param	pEvaluateInfo	Evaluation information structure.
	*	\param	pDstPacket		Destination packet to fill with camera data (will go to connectors).
	*	\param	pSrcPacket		Source packet of information (from Sync buffer).
	*	\return \b true if successful.
	*/
	virtual bool DeviceCameraAnimationNodeNotify( FBEvaluateInfo* pEvaluateInfo, FBDeviceCameraPacket* pDstPacket, FBDeviceSyncPacket* pSrcPacket );
	/**	I/O for camera device.
	*	This synchronous callback is used to fill the device buffer and is not necessary if the
	*	device I/O notify function call is overloaded, as it merely isolates the read operation
	*	from DeviceIONotify().
	*	\param	pNotifyInfo	Device notification information structure.
	*/
	virtual void DeviceCameraEvalData( FBDeviceNotifyInfo& pNotifyInfo );
	/**	Record a frame of data to the FCurves for the camera device.
	*	\param	pRecordTime	Time to record values for.
	*	\param	pNotifyInfo	Device notification structure.
	*/
	virtual void DeviceCameraRecordFrame( FBTime &pRecordTime, FBDeviceNotifyInfo& pNotifyInfo );
	/**	Write data to camera connectors.
	*	\param	pEvaluateInfo	Evaluation information structure.
	*	\return \b true if successful.
	*/
	virtual bool DeviceCameraWriteData( FBEvaluateInfo* pEvaluateInfo );
	/**	Load the lens lookup tables.
	*	\param	pFilename	Name of *.klc file with lens values.
	*	\return	\b true if successfully loaded.
	*/
	virtual bool LoadLensTables( const char* pFilename );
	/**	Process the lens table data for this data packet.
	*	The actual operation for this will depend on a couple of properties 
	*	for the instrument: \b LensTableLoaded, \b LensMode, as well as the 
	*	invert values and the zoom multiplier.
	*	\param	pDataPacket	Camera data to process with the lens tables.
	*/
	virtual void ProcessLensData( FBDeviceCameraPacket* pDataPacket );
  
  public:
	FBPropertyBool		UsingCustomInstruments;	//!< \b Property(RW): Using custom instruments?
	FBPropertyInt		NumberOfInstruments;	//!< \b Property(RW): Number of instruments.
	FBPropertyString	ModelTemplatePrefix;	//!< \b Property(RW): Model template prefix.
};
   
#ifdef FBSDKUseNamespace
}
#endif
#endif
