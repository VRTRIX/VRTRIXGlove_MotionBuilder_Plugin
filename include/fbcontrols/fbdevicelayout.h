#ifndef __FBDEVICELAYOUT_H__
#define __FBDEVICELAYOUT_H__
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

/**	\file fbdevicelayout.h
*	FBDevice layout file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

// Core includes
#include <fbsdk/fbcore.h>	// FBPropertyDevice

// UI includes
#include <fbcontrols/fbcontrols.h>

// Namespace declaration
#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

#ifndef FB_KERNEL
	FB_FORWARD( FBDeviceCameraInstrument );
	FB_FORWARD( FBDeviceCamera );
#endif

#if !defined(K_NO_OPTICAL)
	FB_FORWARD( FBDeviceOptical );
#endif

/** Register a device layout class
*	\param	ClassName		Name of device layout class.
*	\param	UniqueNameStr	Unique name of class.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterDeviceLayout( ClassName,UniqueNameStr, IconFilename ) \
	HIObject RegisterDeviceLayout##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void *pData) \
	{\
		ClassName *Class = new ClassName( (FBDevice*)FBGetFBObject((HIObject)pData) ); \
		Class->mAllocated = true; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"UI_Associated_ClassName",UniqueNameStr,UniqueNameStr" Device Layout",RegisterDeviceLayout##ClassName, true, IconFilename );\
	}

/**	Device layout declaration.
*	\param	ClassName	Name of device layout class.
*	\param	Parent		Parent of device layout class. 
*/
#define FBDeviceLayoutDeclare( ClassName,Parent ) \
	FBClassDeclare( ClassName,Parent ); \
  public: \
    ClassName(FBDevice* pDevice):Parent(pDevice) { FBClassInit; } \
  private:

/** Device layout implementation.
*	\param	ThisComponent	Name of device layout class to implement.
*/
#define FBDeviceLayoutImplementation( ThisComponent ) \
	FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBDeviceLayout
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBDeviceLayout );

/** Device layout class.
*	The registration function associates the layout
*	to the device in the registry.
*/
class FBSDK_DLL FBDeviceLayout :	public FBLayout {
	__FBClassDeclare( FBDeviceLayout,FBLayout );

public:
	/**	Constructor.
	*	\param pDevice Device to associate with device layout.
	*/
	FBDeviceLayout( FBDevice* pDevice = NULL );

	FBPropertyDevice	Device;					//!< <b>Property(R-):</b> Handle on device.
};

#if !defined(K_NO_OPTICAL)
////////////////////////////////////////////////////////////////////////////////////
// FBDeviceOpticalLayout
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBDeviceOpticalLayout);

//! Layout for optical device.
class FBSDK_DLL FBDeviceOpticalLayout :	public FBDeviceLayout
{
    // Basic declaration macros
	__FBClassDeclare( FBDeviceOpticalLayout , FBDeviceLayout);

  public:
	//! Different options for optical device GUI.
	enum FBDeviceOpticalGUIOptions 	{ 
		kGUIModelOpticalList		= 1<<0,		//!< List of optical models (like model templates).
		kGUIModelOpticalCreate		= 1<<1,		//!< Create optical button.
		kGUIModelOpticalDampingTime	= 1<<2,		//!< Damping time (Edit number box).
		kGUIDeviceStatus			= 1<<3,		//!< Device status region.
		kGUIDeviceReset				= 1<<4,		//!< Device reset button.
		kGUIViewer					= 1<<5		//!< Viewer.
	};
	
	/**	Constructor.
	*	\param	pDevice	Parent device(default=NULL).
	*/
	FBDeviceOpticalLayout( FBDevice* pDevice = NULL );

	//---- See base class ----
    // Standard device virtual functions creation
    virtual bool FBCreate();

  public:
    FBDeviceOptical*        mDeviceOptical;			//!< Optical device.
	FBPropertyInt			GenericUIOptions;		//!< <b>Property:</b> GUI options.
};
#endif

#ifndef FB_KERNEL
/**************************************************************************
 **************************************************************************/
__FB_FORWARD( FBDeviceCameraLayout);
//! FBTRACKER_NO_LENSFILE
#define FBTRACKER_NO_LENSFILE	"-- no lens file --"

//! Camera device layout.
class FBSDK_DLL FBDeviceCameraLayout : public FBDeviceLayout
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBDeviceCameraLayout, FBDeviceLayout );
  public: 
    FBDeviceCameraLayout(FBDevice* pDevice);

	//--- Open Reality Creation/Destruction.
	virtual bool FBCreate();		//!< Open Reality Constructor.
	virtual void FBDestroy();		//!< Open Reality Destructor.
													
public:
	//--- UI Management
	virtual void	UICreate							();		//!< Create and assign UI regions
	virtual void		UICreateLayoutInstruments		();		//!< UICreate: Instrument layout.
	virtual void		UICreateLayoutCommunication		();		//!< UICreate: Communication layout.
	virtual void		UICreateLayoutInfo				();		//!< UICreate: Information layout.
	virtual void		UICreateLayoutCustom			();		//!< UICreate: Custom layout.
	virtual void	UIConfigure							();		//!< Configure UI elements
	virtual void		UIConfigureLayoutInstruments	();		//!< UIConfigure: Instrument layout.
	virtual void		UIConfigureLayoutCommunication	();		//!< UIConfigure: Communications layout.
	virtual void		UIConfigureLayoutInfo			();		//!< UIConfigure: Information layout.
	virtual void		UIConfigureLayoutCustom			();		//!< UIConfigure: Custom layout.
	virtual void	UIRefresh							();		//!< Idle refresh
	virtual void		UIRefreshLayoutInstruments		();		//!< UIRefresh: Instrument layout.
	virtual void		UIRefreshLayoutCommunications	();		//!< UIRefresh: Communications layout.
	virtual void		UIRefreshLayoutCustom			();		//!< UIRefresh: Custom layout.
	virtual void	UIUpdateEnabled						();		//!< Update enabled on functions.
	virtual void	UIReset								();		//!< Reset from device values
	virtual void		UIResetLayoutInstruments		();		//!< UIReset: Instrument layout.
	virtual void		UIResetLayoutCommunications		();		//!< UIReset: Communications layout.
	virtual void		UIResetLayoutCustom				();		//!< UIReset: Custom layout.

	/**	Get the current selected instrument.
	*	This function may return NULL if no instrument is selected.
	*	\return Pointer to current device instrument (selected item).
	*/
	virtual FBDeviceCameraInstrument* GetCurrentInstrument();

protected:
	FBTabPanel			mTabPanel;						//!< Main tab panel.

	FBLayout			mLayoutInstruments;				//!< Instrument layout.
		FBList				mListInstruments;			//!< Instrument layout: List of instruments.
		FBButton			mButtonActive;				//!< Instrument layout: Active button.

		// Fov
		FBButton			mButtonManualFov;			//!< Instrument layout: Manual FOV control button.
		FBLabel				mLabelFovX;					//!< Instrument layout: FOV X label.
		FBLabel				mLabelFovY;					//!< Instrument layout: FOV Y label.
		FBSlider			mSliderFovX;				//!< Instrument layout: FOV X slider.
		FBSlider			mSliderFovY;				//!< Instrument layout: FOV Y slider..
		FBEditNumber		mEditNumberFovX;			//!< Instrument layout: FOV X numerical edit box.
		FBEditNumber		mEditNumberFovY;			//!< Instrument layout: FOV Y numerical edit box.

		// Optical Center
		FBButton			mButtonManualCenter;		//!< Instrument layout: Manual optical center button.
		FBLabel				mLabelCenterX;				//!< Instrument layout: Optical center X label.
		FBLabel				mLabelCenterY;				//!< Instrument layout: Optical center Y label.
		FBSlider			mSliderCenterX;				//!< Instrument layout: Optical center X slider.
		FBSlider			mSliderCenterY;				//!< Instrument layout: Optical center Y slider.
		FBEditNumber		mEditNumberCenterX;			//!< Instrument layout: Optical center X numberical edit box.
		FBEditNumber		mEditNumberCenterY;			//!< Instrument layout: Optical center Y numberical edit box.

		// Offsets
		FBLabel				mLabelOffsetT;				//!< Instrument layout: Translation offset label.
		FBLabel				mLabelOffsetR;				//!< Instrument layout: Rotation offset label.
		FBEditVector		mEditVectorOffsetT;			//!< Instrument layout: Translation offset vector edit.
		FBEditVector		mEditVectorOffsetR;			//!< Instrument layout: Rotation offset vector edit.

		// Lens Calibration
		FBButton			mButtonLoadLensfile;		//!< Instrument layout: Load lensfile button.
		FBButton			mButtonResetLensfile;		//!< Instrument layout: Reset lensfile status button.
		FBLabel				mLabelLensfileName;			//!< Instrument layout: Lensfile filename label.
		FBLabel				mLabelInversion;			//!< Instrument layout: Inversion label.
		FBButton			mButtonInvertZoom;			//!< Instrument layout: Invert zoom toggle.
		FBButton			mButtonInvertFocus;			//!< Instrument layout: Invert focus toggle.
		FBLabel				mLabelFovUnits;				//!< Instrument layout: FOV units label.
		FBButton			mButtonFovUnitsDeg;			//!< Instrument layout: FOV in degrees button.
		FBButton			mButtonFovUnitsRad;			//!< Instrument layout: FOV in radians button.
		FBLabel				mLabelNodalX;				//!< Instrument layout: Nodal shift label.
		FBSlider			mSliderNodalX;				//!< Instrument layout: Nodal shift slider.
		FBEditNumber		mEditNumberNodalX;			//!< Instrument layout: Nodal shift numerical edit.
		FBLabel				mLabelZoomX;				//!< Instrument layout: Zoom multiplier label.
		FBSlider			mSliderZoomX;				//!< Instrument layout: Zoom multiplier slider.
		FBEditNumber		mEditNumberZoomX;			//!< Instrument layout: Zomm multiplier numerical edit.

		// Video format
		FBLabel				mLabelAspectRatio;			//!< Instrument layout: Aspect ratio label.
		FBSlider			mSliderAspectRatio;			//!< Instrument layout: Aspect ratio slider.
		FBEditNumber		mEditNumberAspectRatio;		//!< Instrument layout: Aspect ratio edit number.
		FBLabel				mLabelAspectRatioPresets;	//!< Instrument layout: Aspect ratio preset label.
		FBList				mListAspectRatioPresets;	//!< Instrument layout: Aspect ratio preset list.

	FBLayout			mLayoutCommunication;			//!< Communications layout.
		// Sync
		FBLabel				mLabelSyncDelay;			//!< Communications layout: Sync delay label.
		FBSlider			mSliderSyncDelay;			//!< Communications layout: Sync delay slider.
		FBEditNumber		mEditNumberSyncDelay;		//!< Communications layout: Sync delay numerical edit box.
		FBButton			mButtonSyncInfo;			//!< Communications layout: Sync information (debug) button.
	
		// Serial port
		FBButton			mButtonEnableSerial;		//!< Communications layout: Enable serial button.
			FBLabel				mLabelSerialPort;		//!< Communications layout: Serial: Port label.
			FBList				mListSerialPort;		//!< Communications layout: Serial: Port list.
			FBLabel				mLabelSerialBaudRate;	//!< Communications layout: Serial: Baud rate label.
			FBList				mListSerialBaudRate;	//!< Communications layout: Serial: Baud rate list.

		// Network
		FBButton			mButtonEnableNetwork;		//!< Communications layout: Enable network button.
			FBLabel				mLabelNetworkAddress;	//!< Communications layout: Network: Address label.
			FBEdit				mEditNetworkAddress;	//!< Communications layout: Network: Address text edit.
			FBLabel				mLabelNetworkPort;		//!< Communications layout: Network: Port label.
			FBEdit				mEditNetworkPort;		//!< Communications layout: Network: Port text edit.
			FBLabel				mLabelNetworkProtocol;	//!< Communications layout: Network: Protocol label.
			FBList				mListNetworkProtocol;	//!< Communications layout: Network: Protocol list.

		// Shared Memory
		FBButton			mButtonEnableSharedMemory;	//!< Communications layout: Enable shared memory button.
			FBLabel				mLabelHandle;			//!< Communications layout: Shared Memory: Handle label.
			FBEdit				mEditHandle;			//!< Communications layout: Shared Memory: Handle text edit.
			FBLabel				mLabelAddress;			//!< Communications layout: Shared Memory: Address label.
			FBEdit				mEditAddress;			//!< Communications layout: Shared Memory: Address text edit.

		// Simulator
		FBButton			mButtonEnableSimulator;				//!< Communications layout: Enable simulator button.
			FBLabel				mLabelSimulatorFrequency;		//!< Communications layout: Simulator: Frequency label.
			FBSlider			mSliderSimulatorFrequency;		//!< Communications layout: Simulator: Frequency slider.
			FBEditNumber		mEditNumberSimulatorFrequency;	//!< Communications layout: Simulator: Frequency numerical edit.
			FBLabel				mLabelSimulatorAmplitude;		//!< Communications layout: Simulator: Amplitude label.
			FBSlider			mSliderSimulatorAmplitude;		//!< Communications layout: Simulator: Amplitude slider.
			FBEditNumber		mEditNumberSimulatorAmplitude;	//!< Communications layout: Simulator: Amplitude numerical edit.
			FBLabel				mLabelSimulatorZoom;			//!< Communications layout: Simulator: Zoom label.
			FBSlider			mSliderSimulatorZoom;			//!< Communications layout: Simulator: Zoom slider.
			FBEditNumber		mEditNumberSimulatorZoom;		//!< Communications layout: Simulator: Zoom numerical edit.
			FBLabel				mLabelSimulatorFocus;			//!< Communications layout: Simulator: Focus label.
			FBSlider			mSliderSimulatorFocus;			//!< Communications layout: Simulator: Focus slider.
			FBEditNumber		mEditNumberSimulatorFocus;		//!< Communications layout: Simulator: Focus numerical edit.

	FBLayout			mLayoutInfo;					//!< Information layout.
		FBSpread			mSpreadInfo;				//!< Information layout: Spreadsheet.

	FBLayout			mLayoutCustom;					//!< Custom layout.

public:
	// Device/Idle callbacks
	virtual void	OnDeviceStatusChange		( HISender pSender, HKEvent pEvent );		//!< <b>Callback:</b> Device status change .
	virtual void	OnUIIdle					( HISender pSender, HKEvent pEvent );		//!< <b>Callback:</b> UI Idle.

	// Base UI manipulation callbacks
	virtual void	OnTabPanelChange			( HISender pSender, HKEvent pEvent );		//!< <b>Callback:</b> Tab panel selection.
	virtual void	OnListInstrumentsChange		( HISender pSender, HKEvent pEvent );		//!< <b>Callback:</b> Instrument list.

	// Instrument/lens
	// These should be fine
	virtual void	OnButtonActiveClick				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Activate button click.
	virtual void	OnButtonManualChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Manual (FOV or Optical center) button click.
	virtual void		OnButtonManualFovClick					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Manual FOV toggle.
	virtual void		OnButtonManualCenterClick				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Manual Optical center toggle.
	virtual void	OnFovChange						( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> FOV change.
	virtual void		OnFovXSliderChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV X slider change.
	virtual void		OnFovYSliderChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV Y slider change.
	virtual void		OnFovXEditNumberChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV X numerical change.
	virtual void		OnFovYEditNumberChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV Y numerical change.
	virtual void	OnCenterChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Optical center change.
	virtual void		OnCenterXSliderChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Optical center X slider change.
	virtual void		OnCenterYSliderChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Optical center Y slider change.
	virtual void		OnCenterXEditNumberChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Optical center X numerical change.
	virtual void		OnCenterYEditNumberChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Optical center Y numerical change.
	virtual void	OnOffsetChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Offset change.
	virtual void		OnOffsetTChange							( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Translation offset change.
	virtual void		OnOffsetRChange							( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Rotation offset change.
	virtual void	OnLensfileChange				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Lensfile change.
	virtual void	OnButtonLoadLensfileClick		( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Load lensfile button click.
	virtual void	OnButtonResetLensfileClick		( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Reset lensfile button click.
	virtual void	OnInvertChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Invert values change.
	virtual void		OnInvertFocusClick						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Invert focus toggle.
	virtual void		OnInvertZoomClick						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Invert zoom toggle.
	virtual void	OnFovUnitsChange				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> FOV units change.
	virtual void		OnFovUnitsDegClick						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV units to degrees.
	virtual void		OnFovUnitsRadClick						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> FOV units to radians.
	virtual void	OnNodalXChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Nodal shift change.
	virtual void		OnNodalXSliderChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Nodal shift slider change.
	virtual void		OnNodalXEditNumberChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Nodal shift numerical change.
	virtual void	OnZoomXChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Zoom multiplier change.
	virtual void		OnZoomXSliderChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Zoom multiplier slider change.
	virtual void		OnZoomXEditNumberChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Zoom multiplier numerical change.
	virtual void	OnAspectRatioChange				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Aspect ratio change.
	virtual void		OnAspectRatioSliderChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Aspect ratio slider change.
	virtual void		OnAspectRatioEditNumberChange			( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Aspect ratio numerical change.
	virtual void		OnAspectRatioPresetChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Aspect ratio preset selection.

	// Communications
	// These need to be overloaded.
	virtual void	OnSyncDelayChange				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Sync delay change.
	virtual void		OnSyncDelaySliderChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Sync delay slider change.
	virtual void		OnSyncDelayEditNumberChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Sync delay numerical change.
	virtual void	OnButtonSyncInfoClick			( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Sync debug info click.

	virtual void	OnEnableChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Enable comm type change.
	virtual void		OnEnableSerialClick						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Enable serial communication.
	virtual void		OnEnableSimulatorClick					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Enable simulator communication.
	virtual void		OnEnableNetworkClick					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Enable network communication.
	virtual void		OnEnableSharedMemoryClick				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Enable simulator.

	virtual void	OnSerialChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Serial state change.
	virtual void		OnSerialPortChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Serial port change.
	virtual void		OnSerialBaudRateChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Serial baud rate change.
	virtual void	OnNetworkChange					( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Network state change.
	virtual void		OnNetworkAddressChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Network address change.
	virtual void		OnNetworkPortChange						( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Network port change.
	virtual void		OnNetworkProtocolChange					( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Network protocol change.
	virtual void	OnSimulatorChange				( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Simulator state change.
	virtual void		OnSimulatorAmplitudeEditNumberChange	( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator amplitude numerical change.
	virtual void		OnSimulatorAmplitudeSliderChange		( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator amplitude slider change.
	virtual void		OnSimulatorFrequencyEditNumberChange	( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator frequency numerical change.
	virtual void		OnSimulatorFrequencySliderChange		( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator frequency slider change.
	virtual void		OnSimulatorZoomEditNumberChange			( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator zoom numerical change.
	virtual void		OnSimulatorZoomSliderChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator zoom slider change.
	virtual void		OnSimulatorFocusEditNumberChange		( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator focus numerical change.
	virtual void		OnSimulatorFocusSliderChange			( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Simulator focus slider change.
	virtual void	OnSharedMemoryChange			( HISender pSender, HKEvent pEvent );				//!< <b>Callback:</b> Shared memory state change.
	virtual void		OnSharedMemoryHandleChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Shared memory handle change.
	virtual void		OnSharedMemoryAddressChange				( HISender pSender, HKEvent pEvent );	//!< <b>Callback:</b> Shared memory address change.

protected:	
	FBDeviceCamera*		mDeviceCamera;			//!< Handle onto device.
	FBPropertyInt		SupportedCommTypes;		//!< Supported comm types.
	FBPropertyBool		CustomLayout;			//!< Custom layout?
};
#endif

#ifdef FBSDKUseNamespace
	}
#endif
#endif
