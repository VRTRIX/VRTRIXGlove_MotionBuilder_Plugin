/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file kfcurve.h
#ifndef _FBXSDK_SCENE_ANIMATION_KFCURVE_H_
#define _FBXSDK_SCENE_ANIMATION_KFCURVE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxarray.h>
#include <fbxsdk/core/base/fbxtime.h>
#include <fbxsdk/scene/animation/kfcurve/keventbase.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxIO;
class KDataType;

#define KFCURVE_FLOAT
#ifdef KFCURVE_FLOAT
	typedef float kFCurveDouble;
#else
	typedef double kFCurveDouble;
#endif


class KFCurve;

#define IKFCurveID 43763635

typedef KFCurve* HIKFCurve;

// Recording memory functions declaration
FBXSDK_DLL FbxULong GetRecordingMemory();
FBXSDK_DLL void WatchFree(void* pPtr, FbxULong pSize);
FBXSDK_DLL void* WatchMalloc(FbxULong pSize);

///! Key interpolation type.
enum
{
	//! Constant value until next key.
	KFCURVE_INTERPOLATION_CONSTANT    = 0x00000002,	
	//! Linear progression to next key.
	KFCURVE_INTERPOLATION_LINEAR	  = 0x00000004,		
	//! Cubic progression to next key.
	KFCURVE_INTERPOLATION_CUBIC		  = 0x00000008,		
	//! Any interpolation (Constant, Linear, Cubic)
	KFCURVE_INTERPOLATION_ALL		  =	KFCURVE_INTERPOLATION_CONSTANT|KFCURVE_INTERPOLATION_LINEAR|KFCURVE_INTERPOLATION_CUBIC,
	//! Number of interpolation defined.
	KFCURVE_INTERPOLATION_COUNT		  = 3
};												  

//! Key constant mode.
enum
{
	//! Curve value is constant between this key and the next
	KFCURVE_CONSTANT_STANDARD		  =	0x00000000,
	//! Curve value is constant, with next key's value
	KFCURVE_CONSTANT_NEXT			  =	0x00000100,
	//! Mask of constant mode (standard or next)
	KFCURVE_CONSTANT_ALL			  =	KFCURVE_CONSTANT_STANDARD | KFCURVE_CONSTANT_NEXT,
	//! Number of interpolation defined
	KFCURVE_CONSTANT_COUNT			  = 2
};

//! Key tangent mode for cubic interpolation.
enum
{
	//! Auto key (spline cardinal).
	KFCURVE_TANGEANT_AUTO			  =	0x00000100, 	
	//! Spline TCB (Tension, Continuity, Bias)
	KFCURVE_TANGEANT_TCB			  =	0x00000200,	
	//! Next slope at the left equal to slope at the right.
	KFCURVE_TANGEANT_USER			  =	0x00000400, 	
	//! Independent left and right slopes.
	KFCURVE_GENERIC_BREAK			  =	0x00000800, 	
	//! Clamp: key should be flat if next or previous key has the same value (overrides tangent mode).
    KFCURVE_GENERIC_CLAMP			  =	0x00001000, 
	//! Time independent tangent (overrides tangent mode).
    KFCURVE_GENERIC_TIME_INDEPENDENT  = 0x00002000,
	//! Clamp dynamic: key should be flat if tangent control point is outside [next-previous key] range (overrides tangent mode).
    KFCURVE_GENERIC_CLAMP_PROGRESSIVE = 0x00004000|KFCURVE_GENERIC_TIME_INDEPENDENT, // this is the AUTOKEY tangent mode and can only work if time-independent
	//! Independent left and right slopes, with next slope at the left equal to slope at the right.
	KFCURVE_TANGEANT_BREAK			  = KFCURVE_TANGEANT_USER|KFCURVE_GENERIC_BREAK,
	//! Independent left and right slopes, with auto key.
	KFCURVE_TANGEANT_AUTO_BREAK	      = KFCURVE_TANGEANT_AUTO|KFCURVE_GENERIC_BREAK,
	//! Any defined tangent mode
    KFCURVE_TANGEANT_ALL			  = KFCURVE_TANGEANT_AUTO|KFCURVE_TANGEANT_TCB|KFCURVE_TANGEANT_USER|KFCURVE_GENERIC_BREAK|KFCURVE_GENERIC_CLAMP|KFCURVE_GENERIC_CLAMP_PROGRESSIVE|KFCURVE_GENERIC_TIME_INDEPENDENT,
	//! Tangent modes only (no overrides)
    KFCURVE_TANGEANT_TYPE_MASK 		  = KFCURVE_TANGEANT_AUTO|KFCURVE_TANGEANT_TCB|KFCURVE_TANGEANT_USER|KFCURVE_TANGEANT_BREAK,
	//! Override modes (Clamp, Clamp progressive, Time-Independent) only
	KFCURVE_TANGEANT_OVERRIDES_MASK   = KFCURVE_GENERIC_CLAMP|KFCURVE_GENERIC_CLAMP_PROGRESSIVE|KFCURVE_GENERIC_TIME_INDEPENDENT
};

//! Selection mode.
enum 
{
	//! Key is selected (it has its selection flag set to true).
	KFCURVE_SELECT_POINT			  =	0x00010000, 
	//! Left tangent is selected
	KFCURVE_SELECT_LEFT				  =	0x00020000, 
	//! Right tangent is selected
	KFCURVE_SELECT_RIGHT			  =	0x00040000, 
	//! Key and tangents are selected
	KFCURVE_SELECT_ALL				  =	KFCURVE_SELECT_POINT|KFCURVE_SELECT_LEFT|KFCURVE_SELECT_RIGHT
};

//! Manipulation flag.
enum
{
	//! Animation curve is currently manipulated.
	KFCURVE_MARKED_FOR_MANIP          = 0x00080000,
	//! Animation curve is currently marked.
	KFCURVE_MARKED_ALL                = KFCURVE_MARKED_FOR_MANIP
};

/** Tangent visibility.
*/
enum 
{
	//! No tangent is visible.
	KFCURVE_TANGEANT_SHOW_NONE		  = 0x00000000, 
	//! Left tangent is visible.
	KFCURVE_TANGEANT_SHOW_LEFT		  = 0x00100000, 
	//! Right tangent is visible.
	KFCURVE_TANGEANT_SHOW_RIGHT		  = 0x00200000, 
	//! Both left and right tangents are visible.
	KFCURVE_TANGEANT_SHOW_BOTH		  = KFCURVE_TANGEANT_SHOW_LEFT|KFCURVE_TANGEANT_SHOW_RIGHT
};

/** Continuity of the curve before and after the key, in the case of a TCB tangent mode
*/
enum
{
	//! Smooth animation curve
    KFCURVE_CONTINUITY				  = 0x00000000,
	//! Flat continuity
    KFCURVE_CONTINUITY_FLAT           = 0x00100000,
	//! Break in continuity
    KFCURVE_CONTINUITY_BREAK          = 0x00200000,
	//! Used to prevent the curve shape from changing when inserting a key
    KFCURVE_CONTINUITY_INSERT         = 0x00400000  
};


//! Weighted mode.
enum 
{
	//! Tangent has default weights of 0.333; we define this state as not weighted.
	KFCURVE_WEIGHTED_NONE			  =	0x00000000, 
	//! Right tangent is weighted.
	KFCURVE_WEIGHTED_RIGHT			  =	0x01000000, 
	//! Left tangent is weighted.
	KFCURVE_WEIGHTED_NEXT_LEFT		  =	0x02000000, 
	//! Both left and right tangents are weighted.
	KFCURVE_WEIGHTED_ALL			  =	KFCURVE_WEIGHTED_RIGHT|KFCURVE_WEIGHTED_NEXT_LEFT
};

//! Velocity mode. Velocity settings speed up or slow down animation on either side of a key without changing the trajectory of the animation. Unlike Auto and Weight settings, Velocity changes the animation in time, but not in space.
enum
{
	//! No velocity (default).
	KFCURVE_VELOCITY_NONE			  = 0x00000000,
	//! Right tangent has velocity.
	KFCURVE_VELOCITY_RIGHT			  = 0x10000000,
	//! Left tangent has velocity.
	KFCURVE_VELOCITY_NEXT_LEFT		  = 0x20000000,
	//! Both left and right tangents have velocity.
	KFCURVE_VELOCITY_ALL			  = KFCURVE_VELOCITY_RIGHT | KFCURVE_VELOCITY_NEXT_LEFT
};

#define KFCURVE_WEIGHT_DIVIDER       9999       // precise enough and can be divided by 3 without error
#define KFCURVE_DEFAULT_WEIGHT       ((kFCurveDouble)(1.0/3.0))
#define KFCURVE_MIN_WEIGHT           ((kFCurveDouble)(1.0/KFCURVE_WEIGHT_DIVIDER))
#define KFCURVE_MAX_WEIGHT           ((kFCurveDouble)0.99)
#define KFCURVE_DEFAULT_VELOCITY	 0.0 

//! KFCurveKey data indices for cubic interpolation tangent information.
enum EKFCurveDataIndex
{
	//! User and Break tangent mode (data are doubles).
	//! Index of the right derivative
	KFCURVEKEY_RIGHT_SLOPE			= 0, 
	//! Index of the left derivative for the next key
	KFCURVEKEY_NEXT_LEFT_SLOPE		= 1, 

	//! User and Break tangent break mode (data are FbxInt16 tokens from weight and converted to doubles).
	//! Start index of weight values
	KFCURVEKEY_WEIGHTS				= 2, 
	//! Index of weight on right tangent
	KFCURVEKEY_RIGHT_WEIGHT			= 2, 
	//! Index of weight on next key's left tangent
	KFCURVEKEY_NEXT_LEFT_WEIGHT		= 3, 

	//! Velocity mode
	//! Start index of velocity values
	KFCURVEKEY_VELOCITY				= 4,
	//! Index of velocity on right tangent
	KFCURVEKEY_RIGHT_VELOCITY		= 4,
	//! Index of velocity on next key's left tangent
	KFCURVEKEY_NEXT_LEFT_VELOCITY	= 5, 

	//! TCB tangent mode (data are floats).
	//! Index of Tension
	KFCURVEKEY_TCB_TENSION			= 0, 
	//! Index of Continuity
	KFCURVEKEY_TCB_CONTINUITY		= 1, 
	//! Index of Bias
	KFCURVEKEY_TCB_BIAS				= 2,

	//! Index of the right derivative, when the tangent is in KFCURVE_TANGEANT_AUTO mode
	KFCURVEKEY_RIGHT_AUTO			= 0,
	//! Index of the left derivative for the next key, when the tangent is in KFCURVE_TANGEANT_AUTO mode
	KFCURVEKEY_NEXT_LEFT_AUTO		= 1
};

//! Extrapolation modes, for animation curve extremities, before the first key (pre-extrapolation) or after the last key (post-extrapolation).
enum 
{
	//! Constant: The curve is flat at extrapolation site
	KFCURVE_EXTRAPOLATION_CONST				= 1, 
	//! Repetition: The extrapolated curve is the same as the curve between the first and last keys, and repeated a number of times.
	KFCURVE_EXTRAPOLATION_REPETITION		= 2, 
	//! Mirror Repetition: Same as Repetition mode, but the curve is mirrored
	KFCURVE_EXTRAPOLATION_MIRROR_REPETITION	= 3, 
	//! Keep Slope: The slope of the extrapolated curve is the same as the slope on the first (or last) key of the curve.
	KFCURVE_EXTRAPOLATION_KEEP_SLOPE		= 4,
	//! Relative Repetition: Same as Repetition mode, but the curve is relative to last curve
	KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION = 5
};

enum 
{
	KFCURVE_BEZIER	= 0, 
	KFCURVE_SAMPLE	= 1, 
	KFCURVE_ISO		= 2
};

typedef FbxUInt kFCurveInterpolation;
typedef FbxUInt kFCurveConstantMode;
typedef FbxUInt kFCurveTangeantMode;
typedef FbxUInt kFCurveTangeantWeightMode;
typedef FbxUInt kFCurveTangeantVelocityMode;
typedef FbxUInt kFCurveExtrapolationMode;
typedef FbxUInt kFCurveTangeantVisibility;
typedef int kFCurveIndex;

/** Curve event type.
* - \e KFCURVEEVENT_NONE		    default event value
* - \e KFCURVEEVENT_CANDIDATE	    curve value (not candidate) changed
* - \e KFCURVEEVENT_UNUSED1    
* - \e KFCURVEEVENT_UNUSED2    
* - \e KFCURVEEVENT_UNUSED3    
* - \e KFCURVEEVENT_KEY		        key changed (add, removed, edited); see bits 11-15 for precisions
* - \e KFCURVEEVENT_DEPRECATED5 
* - \e KFCURVEEVENT_UNUSED6    
* - \e KFCURVEEVENT_UNUSED7    
* - \e KFCURVEEVENT_SELECTION	    key selection changed
* - \e KFCURVEEVENT_DESTROY	        animation curve destruction
* - \e KFCURVEEVENT_DEPRECATED10
* - \e KFCURVEEVENT_KEYADD    
* - \e KFCURVEEVENT_KEYREMOVE  
* - \e KFCURVEEVENT_EDITVALUE  
* - \e KFCURVEEVENT_EDITTIME   
* - \e KFCURVEEVENT_EDITOTHER  
*/
enum 
{
    KFCURVEEVENT_NONE		=0, // default event value
    KFCURVEEVENT_CANDIDATE	=1 << 0, // curve value (not candidate) changed
    KFCURVEEVENT_UNUSED1    =1 << 1,
    KFCURVEEVENT_UNUSED2    =1 << 2,
    KFCURVEEVENT_UNUSED3    =1 << 3,
    KFCURVEEVENT_KEY		=1 << 4, // key changed (add, removed, edited); see bits 11-15 for precisions
    KFCURVEEVENT_DEPRECATED5 =1 << 5,
    KFCURVEEVENT_UNUSED6    =1 << 6,
    KFCURVEEVENT_UNUSED7    =1 << 7,
    KFCURVEEVENT_SELECTION	=1 << 8, // key selection changed
    KFCURVEEVENT_DESTROY	=1 << 9, // animation curve destruction
    KFCURVEEVENT_DEPRECATED10 =1 << 10,
    KFCURVEEVENT_KEYADD     =1 << 11,
    KFCURVEEVENT_KEYREMOVE  =1 << 12,
    KFCURVEEVENT_EDITVALUE  =1 << 13,
    KFCURVEEVENT_EDITTIME   =1 << 14,
    KFCURVEEVENT_EDITOTHER  =1 << 15,
};


/** Animation curve event class. An animation curve event happens when there is some action performed on a curve through a graphical interface.
  * The FBX SDK doesn't have such an interface, and this class is not used in the SDK.
  * An example of animation curve event would be a key value modification through the interface.
  */
class FBXSDK_DLL KFCurveEvent : public KEventBase
{
public:
	// Curve event type, the enum stated above allow composition of type (bitfield). 
	// Stored in mType
	
	//! Index of the key where the event begins
	int mKeyIndexStart;
	//! Index of the key where the event ends
	int mKeyIndexStop;
	//! Number of events, can be reset to 0 with KFCurveEvent::Clear
	int mEventCount;

	//! Reset the count of events (KFCurveEvent::mEventCount) to 0
    inline void Clear (); 
	
	/** Add a curve event of type given pWhat to a curve event object.
	  * \param pWhat Type of event, for example: KFCURVEEVENT_NONE, KFCURVEEVENT_CANDIDATE, KFCURVEEVENT_KEY.
	  * \param pIndex Index of the key for which the event occurred
	  */
    inline void Add (int pWhat, int pIndex);
};

typedef void (*kFCurveCallback) (KFCurve *pFCurve, KFCurveEvent *FCurveEvent, void* pObject);

/** Defines a tangent derivative and weight
*	\remarks Implementation was made for performance.
* \nosubgrouping
*/
class FBXSDK_DLL KFCurveTangeantInfo 
{
public:
	inline KFCurveTangeantInfo();

	kFCurveDouble mDerivative;
	kFCurveDouble mWeight;
	kFCurveDouble mVelocity;
	kFCurveDouble mAuto;  // The auto parameter!
	bool         mWeighted;
	bool		  mHasVelocity;
};

class KFCurveKey;

/**
* class KFCurveKeyAttrManager: Memory manager for KFCurveKey attributes.
*/
class KFCurveKeyAttrManager;


/**
* class KMemoryBlockQueue: Memory queue for KFCurveKey attributes.
*/
class KMemoryBlockQueue;

/**
* KPriFCurveKeyAttr stores the additional attributes for KFCurveKey. For most motion capture curves,
* all the keys will have default attribute values. It is not necessary
* to store those default value for each key. See KFCurveKey for all function 
* documentation.
*/
struct KPriFCurveKeyAttr
{
    KPriFCurveKeyAttr() : mFlags(0) {}

	inline void Set 
		(
		kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
		kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
		kFCurveDouble pData0 = 0.0,
		kFCurveDouble pData1 = 0.0,
		kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
		kFCurveDouble pWeight0   = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pWeight1   = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
		kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
		);

	inline void SetTCB (float pData0 = 0.0f, float pData1 = 0.0f, float pData2 = 0.0f);
	inline void Set(KFCurveKey& pSource);
	inline kFCurveInterpolation GetInterpolation() const;
	inline void SetInterpolation(kFCurveInterpolation pInterpolation);
	inline kFCurveConstantMode GetConstantMode() const;
	inline kFCurveTangeantMode GetTangeantMode( bool pIncludeOverrides = false ) const;
	inline kFCurveTangeantWeightMode GetTangeantWeightMode() const;
	inline kFCurveTangeantVelocityMode GetTangeantVelocityMode() const;
	inline void SetConstantMode(kFCurveConstantMode pMode);
	inline void SetTangeantMode(kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);
	inline void SetTangeantWeightMode(kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );
	inline void SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight );
	inline void SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );
	inline kFCurveDouble GetDataDouble(EKFCurveDataIndex pIndex) const;
	inline void SetDataDouble(EKFCurveDataIndex pIndex, kFCurveDouble pValue);
	inline float GetDataFloat(EKFCurveDataIndex pIndex) const;
	inline void SetDataFloat(EKFCurveDataIndex pIndex, float pValue);
	inline float* GetDataPtr() const;
	inline void SetSelected(bool pSelected);	
	inline bool GetSelected() const;
	inline void SetMarkedForManipulation(bool pMark);	
	inline bool GetMarkedForManipulation() const;
	inline void	SetTangeantVisibility (kFCurveTangeantVisibility pVisibility);	
	inline kFCurveTangeantVisibility GetTangeantVisibility () const;
	inline void SetBreak(bool pVal); 
	inline bool GetBreak() const; 
	inline bool IsEqual(const KPriFCurveKeyAttr& pRsh) const;
	inline void IncRefCount();
	inline void DecRefCount();
	inline FbxUInt32 GetRefCount() const;

    FbxUInt32 mFlags;
#ifdef KFCURVE_FLOAT
	float  mData[4];
#else 
	double	mData[2];
	FbxInt16	mWeight[2];
	FbxInt16	mVelocity[2];
#endif 	
	FbxUInt32 mRefCount;

};

/**
* KPriFCurveKey is used as the internal storage format for motion data. 
* We need to make its size as small as possible, so we carefully play with
* the pack, alignment for VC,GCC on 32/64-bit OS.
*/
struct KPriFCurveKey
{
	KPriFCurveKey()
	{
		Init();
	}

	inline void Init();
	inline void Set (FbxTime pTime, kFCurveDouble pValue);
	inline kFCurveDouble GetValue() const;
	inline void SetValue(kFCurveDouble pValue);
	inline void IncValue(kFCurveDouble pValue);
	inline void MultValue(kFCurveDouble pValue);
	inline FbxTime GetTime() const;
	inline void SetTime(FbxTime pTime);
	inline void IncTime(FbxTime pTime);

	FbxTime mTime;  //8 Bytes
#ifdef KFCURVE_FLOAT
	KPriFCurveKeyAttr* mAttr; // 4 Bytes on 32-bit OS, 8 Bytes on 64-bit OS
	kFCurveDouble mValue; // 4 Bytes (float) for KFCRVE_FLOAT, 8 Bytes (double) otherwise.
#else
	kFCurveDouble mValue;
	KPriFCurveKeyAttr* mAttr;
#endif
};


/** Defines a key within an animation curve.
*	\remarks Implementation was made for performance.
*	Keep in mind that there is no check for consistency and memory 
* management ever made throughout the methods' code. This class must be 
* used with a good understanding of its interface.
* Default constructor does not initialize data 
* members. If an instance has to be initialized, use function KFCurveKey::Set().
* \nosubgrouping
*/
class FBXSDK_DLL KFCurveKey 
{
public:
	KFCurveKey()
	{
		Init();
	}

public:
	
	/** Set a key.
	*	Use SetTCB() to set a key with cubic interpolation and TCB tangent mode.
	*	\param pTime			Key time.
	*	\param pValue			Key value.
	*	\param pInterpolation	Key interpolation type.	Interpolation types are: 
	*							KFCURVE_INTERPOLATION_CONSTANT, 
	*							KFCURVE_INTERPOLATION_LINEAR,
	*							KFCURVE_INTERPOLATION_CUBIC
	*	\param pTangentMode		Key tangent mode (meaningful for cubic 
	*							interpolation only). Valid tangent modes are:
	*							KFCURVE_TANGEANT_AUTO,
	*							KFCURVE_TANGEANT_USER,
	*							KFCURVE_TANGEANT_BREAK
	*	\param pData0			Right slope.
	*	\param pData1			Next left slope.
	*	\param pTangentWeightMode	Weight mode, if used. Weight modes are:
	*								KFCURVE_WEIGHTED_NONE,
	*								KFCURVE_WEIGHTED_RIGHT,
	*								KFCURVE_WEIGHTED_NEXT_LEFT,
	*								KFCURVE_WEIGHTED_ALL.
	*	\param pWeight0				Right slope weight.
	*	\param pWeight1				Next left slope weight.
	*	\param pVelocity0			Right velocity.
	*	\param pVelocity1			Next left velocity.
	*/
	inline void Set 
	(
		FbxTime pTime, 
		kFCurveDouble pValue, 
		kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
		kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
		kFCurveDouble pData0 = 0.0,
		kFCurveDouble pData1 = 0.0,
		kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
		kFCurveDouble pWeight0                             = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pWeight1                             = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
		kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
	);
	
	/**	Set a key with cubic interpolation, TCB tangent mode.
	*	\param pTime	Key time.
	*	\param pValue	Key value.
	*	\param pData0	Tension.
	*	\param pData1	Continuity.
	*	\param pData2	Bias.
	*/
	inline void SetTCB 
	(
		FbxTime pTime, 
		kFCurveDouble pValue, 
		float pData0 = 0.0f, 
		float pData1 = 0.0f, 
		float pData2 = 0.0f
	);
	
	/** Key assignment.
	*	\param pSource	Source key to be copied.
	*/
	inline void Set(KFCurveKey& pSource);
	
	/** Get key's interpolation type.
    *	Interpolation types are: 
	* \e KFCURVE_INTERPOLATION_CONSTANT Constant value until next key.
    * \e KFCURVE_INTERPOLATION_LINEAR Linear progression to next key.
    * \e KFCURVE_INTERPOLATION_CUBIC Cubic progression to next key.
    *   \return                  Interpolation type of the queried key.
	*/
	inline kFCurveInterpolation GetInterpolation() const;
	
	/** Set key's interpolation type.
	*	\param pInterpolation Key interpolation type.
	*	Interpolation types are: KFCURVE_INTERPOLATION_CONSTANT, 
	*							 KFCURVE_INTERPOLATION_LINEAR,
	*							 KFCURVE_INTERPOLATION_CUBIC
	*/
	inline void SetInterpolation(kFCurveInterpolation pInterpolation);

	/** Get key's constant mode.
    *	\note This method is only relevant if the key's interpolation type is constant (KFCURVE_INTERPOLATION_CONSTANT).
    *	Using this method on a key with an other interpolation type will return unpredictable value.
	* Constant modes are:
	* \e KFCURVE_CONSTANT_STANDARD Curve value is constant between this key and the next
	* \e KFCURVE_CONSTANT_NEXT Curve value is constant, with next key's value
	*	\return Key constant mode.
	*/
	inline kFCurveConstantMode GetConstantMode() const;

	/** Get key's tangent mode.
	*   \param pIncludeOverrides Include override flags: Break, Clamp, Clamp progressive, Time-Independent. 
	*	This method is meaningful for cubic interpolation only.
	*			 Using this method for non cubic interpolated key will return unpredictable value.
	*	Tangent modes are: 
	* \e KFCURVE_TANGEANT_AUTO Auto key (spline cardinal).
	* \e KFCURVE_TANGEANT_TCB Spline TCB (Tension, Continuity, Bias)
	* \e KFCURVE_TANGEANT_USER Next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_BREAK Independent left and right slopes, with next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_AUTO_BREAK Independent left and right slopes, with auto key.
	* \return Key tangent mode.
	*/
	inline kFCurveTangeantMode GetTangeantMode( bool pIncludeOverrides = false ) const;

	/** Get key's tangent weight mode.
	*	This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	
	* \e KFCURVE_WEIGHTED_NONE Tangent has default weights of 0.333; we define this state as not weighted.
	* \e KFCURVE_WEIGHTED_RIGHT Right tangent is weighted.
	* \e KFCURVE_WEIGHTED_NEXT_LEFT Left tangent is weighted.
	* \e KFCURVE_WEIGHTED_ALL Both left and right tangents are weighted.
	*/
	inline kFCurveTangeantWeightMode GetTangeantWeightMode() const;

	/** Get key's tangent velocity mode.
    *	This method is meaningful for cubic interpolation only.
	*	Tangent velocity modes are:	
	* \e KFCURVE_VELOCITY_NONE No velocity (default).
	* \e KFCURVE_VELOCITY_RIGHT Right tangent has velocity.
	* \e KFCURVE_VELOCITY_NEXT_LEFT Left tangent has velocity.
	* \e KFCURVE_VELOCITY_ALL Both left and right tangents have velocity.
	*/
	inline kFCurveTangeantVelocityMode GetTangeantVelocityMode() const;

	/** Set key's constant mode.
	*	This method is meaningful for constant interpolation only.
	*	\param pMode Key constant mode.
	* Constant modes are:
	* \e KFCURVE_CONSTANT_STANDARD Curve value is constant between this key and the next
	* \e KFCURVE_CONSTANT_NEXT Curve value is constant, with next key's value
	*/
	inline void SetConstantMode(kFCurveConstantMode pMode);

	/** Set key's tangent mode.
	*	This method is meaningful for cubic interpolation only.
	*	\param pTangent Key tangent mode.
	*	Tangent modes are: 
	* \e KFCURVE_TANGEANT_AUTO Auto key (spline cardinal).
	* \e KFCURVE_TANGEANT_TCB Spline TCB (Tension, Continuity, Bias)
	* \e KFCURVE_TANGEANT_USER Next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_BREAK Independent left and right slopes, with next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_AUTO_BREAK Independent left and right slopes, with auto key.
	* \param pIgnoreAutoTimeIndepedentConversion \b true ignore the auto time independent conversion flag.
	*/
	inline void SetTangeantMode(kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);
		
	/** Set key's tangent weight mode as double value (cubic interpolation, non TCB tangent mode).
	*	This method is meaningful for cubic interpolation only.
	*	\param pTangentWeightMode	Weight mode. Values are:
	* \e KFCURVE_WEIGHTED_NONE Tangent has default weights of 0.333; we define this state as not weighted.
	* \e KFCURVE_WEIGHTED_RIGHT Right tangent is weighted.
	* \e KFCURVE_WEIGHTED_NEXT_LEFT Left tangent is weighted.
	* \e KFCURVE_WEIGHTED_ALL Both left and right tangents are weighted.
	*	\param pMask				Used to select the affected tangents. Mask values are:
	*								KFCURVE_WEIGHTED_RIGHT,
	*								KFCURVE_WEIGHTED_NEXT_LEFT,
	*								KFCURVE_WEIGHTED_ALL.
	*/

	inline void SetTangeantWeightMode(kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );

	/** Set key's tangent velocity mode as double value (cubic interpolation, non TCB tangent mode).
	*	This method is meaningful for cubic interpolation only.
	*	\param pTangentVelocityMode	Velocity mode. Values are:
	* \e KFCURVE_VELOCITY_NONE No velocity (default).
	* \e KFCURVE_VELOCITY_RIGHT Right tangent has velocity.
	* \e KFCURVE_VELOCITY_NEXT_LEFT Left tangent has velocity.
	* \e KFCURVE_VELOCITY_ALL Both left and right tangents have velocity.
	*	\param pMask				Used to select the affected tangents. Mask values are:
	*								KFCURVE_VELOCITY_RIGHT,
	*								KFCURVE_VELOCITY_NEXT_LEFT,
	*								KFCURVE_VELOCITY_ALL.
	*/

	inline void SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );

	/** Adjust the actual tangent of the key so that the tangent control point (tangent extremity) 
	*   stays closer to where it should be. This is required because the weight value gets imprecise
	*   when it is small (it is stored as a fixed point value). This method must be called when 
	*   setting the weight coming from a source where the precision is the same. It must be called 
	*   after the tangent value has been set. 
    *   \remark Do not use this call repetitively (from an interactive editor for example) because 
	*   this function will create imprecision on the tangent value.
	*   \param pIndex FCurveDataIndex
	*							\e	KFCURVEKEY_RIGHT_SLOPE 
	*							\e	KFCURVEKEY_NEXT_LEFT_SLOPE
	*							\e	KFCURVEKEY_WEIGHTS
	*							\e	KFCURVEKEY_RIGHT_WEIGHT
	*							\e	KFCURVEKEY_NEXT_LEFT_WEIGHT
	*							\e	KFCURVEKEY_VELOCITY
	*							\e	KFCURVEKEY_RIGHT_VELOCITY
	*							\e	KFCURVEKEY_NEXT_LEFT_VELOCITY
	*							\e	KFCURVEKEY_TCB_TENSION
	*							\e	KFCURVEKEY_TCB_CONTINUITY
	*							\e	KFCURVEKEY_TCB_BIAS
	*							\e	KFCURVEKEY_RIGHT_AUTO
	*							\e	KFCURVEKEY_NEXT_LEFT_AUTO
	*   \param pWeight New tangent weight value.
	*/
	inline void SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight );


	/** Get key data as double value (cubic interpolation, non TCB tangent mode).
	* Warning: Slope data is inconsistent for automatic tangent mode.
	*			 Use KFCurve::EvaluateLeftDerivative() and 
	*			 KFCurve::EvaluateRightDerivative() to find
	*			 slope values.
	*	Using this method for other than cubic interpolated 
	*			 key (linear, constant) will return unpredictable values.
        *               For a TCB tangent mode key, use KFCurve::GetDataFloat() instead.
	*	\param pIndex Data index:
	* \e KFCURVEKEY_RIGHT_SLOPE Index of the right derivative.
	* \e KFCURVEKEY_NEXT_LEFT_SLOPE Index of the left derivative for the next key.
	* \e KFCURVEKEY_RIGHT_WEIGHT Index of weight on right tangent.
	* \e KFCURVEKEY_NEXT_LEFT_WEIGHT Index of weight on next key's left tangent.
	* \return Slope value or weight value.
	*/
	inline kFCurveDouble GetDataDouble(EKFCurveDataIndex pIndex) const;
	
	/**	Set data as double value (cubic interpolation, non TCB tangent mode).
	*	Warning: Slope data is inconsistent for automatic tangent mode.
	*			 Therefore, it is irrelevant to use this method on automatic 
	*			 tangent mode keys.
	*	Using this method for other than cubic interpolated 
	* key (linear, constant) is irrelevant. For a TCB tangent mode key, 
        * use KFCurve::SetDataFloat() instead.
	*	\param pIndex Data index:
	* \e KFCURVEKEY_RIGHT_SLOPE Index of the right derivative
	* \e KFCURVEKEY_NEXT_LEFT_SLOPE Index of the left derivative for the next key.
	* \e KFCURVEKEY_RIGHT_WEIGHT Index of weight on right tangent.
	* \e KFCURVEKEY_NEXT_LEFT_WEIGHT Index of weight on next key's left tangent.
	*	\param pValue	The data value to set (a slope or a weight).
	*/
	inline void SetDataDouble(EKFCurveDataIndex pIndex, kFCurveDouble pValue);
	
	/** Get key data in the case of a cubic interpolation with TCB tangent mode.
	*	 Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredictable values.
	*	\param pIndex	Data index: either 
	* \e KFCURVEKEY_TCB_TENSION Tension
	* \e KFCURVEKEY_TCB_CONTINUITY Continuity, or 
	* \e KFCURVEKEY_TCB_BIAS Bias.
	* \return Key data value.
	*/	
	inline float GetDataFloat(EKFCurveDataIndex pIndex) const;

	/**	Set data value in the case of a cubic interpolation with TCB tangent mode.
	*	 Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredictable values.
	*	\param pIndex	Data index, either
	* \e KFCURVEKEY_TCB_TENSION Tension
	* \e KFCURVEKEY_TCB_CONTINUITY Continuity, or 
	* \e KFCURVEKEY_TCB_BIAS Bias.
	*	\param pValue	Data value to set.
	*/
	inline void SetDataFloat(EKFCurveDataIndex pIndex, float pValue);

	/**	Get key data as a pointer.
	* \return Data as a float array.
	*/
	inline float* GetDataPtr() const;

	/**	Get key value.
	* \return Key value.
	* \remark kFCurveDouble is defined as float.
	*/
	inline kFCurveDouble GetValue() const;

	/** Set key value.
    * \param pValue The value to set.
	* \remark kFCurveDouble is defined as float.
	  */
	inline void SetValue(kFCurveDouble pValue);

	/** Increment key value.
	*	\param pValue Value by which key value is incremented.
	*/
	inline void IncValue(kFCurveDouble pValue);

	/** Multiply key value.
	*	\param pValue Value by which the key value is multiplied.
	*/
	inline void MultValue(kFCurveDouble pValue);

	/** Get key time
	*	\return Key time (time at which this key is occurring).
	*/
	inline FbxTime GetTime() const;

	/** Set key time.
	*	\param pTime Key time (time at which this key is occurring).
	*/
	inline void SetTime(FbxTime pTime);

	/** Increment key time.
	*	\param pTime Time value by which the key time is incremented.
	*/
	inline void IncTime(FbxTime pTime);

	/** Set if key is currently selected.
	*	\param pSelected Selection flag.
	*/
	inline void SetSelected(bool pSelected);	

	/** Return if key is currently selected.
	*	\return Selection flag.
	*/
	inline bool GetSelected() const;

	/** Set if key is currently marked for manipulation.
	*	\param pMark Mark flag.
	*/
	inline void SetMarkedForManipulation(bool pMark);	

	/** Return if key is currently marked for manipulation.
	*	\return Mark flag.
	*/
	inline bool GetMarkedForManipulation() const;

    /** Set tangent visibility mode. This would indicate what part of the tangent is visible in a graphical interface.
    *	This method is relevant for cubic interpolation only.
    *	\param pVisibility	Tangent visibility mode.
	*	Tangent visibility modes are: 
	* \e KFCURVE_TANGEANT_SHOW_NONE No tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_LEFT Left tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_RIGHT Right tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_BOTH	Both left and right tangents are visible.
	*/
	inline void	SetTangeantVisibility (kFCurveTangeantVisibility pVisibility);	

	/** Return tangent visibility mode.
	*	This method is relevant for cubic interpolation only.
	*	\return Tangent visibility mode.
	*	Tangent visibility modes are: 
	* \e KFCURVE_TANGEANT_SHOW_NONE No tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_LEFT Left tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_RIGHT Right tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_BOTH	Both left and right tangents are visible.
	*/
	inline kFCurveTangeantVisibility GetTangeantVisibility () const;

    /** Set or unset the tangent break. When this flag is set (KFCURVE_GENERIC_BREAK), the key's left and right slopes are independent.
	* When this flag is off, the key's left and right slope are equal.
    * This method is relevant for User (KFCURVE_TANGEANT_USER) and Auto (KFCURVE_TANGEANT_AUTO) tangent modes only.
    * \param pVal Break flag (\c true or \c false).
    */
	inline void SetBreak(bool pVal); 

    /** Get if the tangent has a break. When this flag is set (KFCURVE_GENERIC_BREAK), the key's left and right slopes are independent.
	* When this flag is off, the key's left and right slope are equal.
    * This method is relevant for User (KFCURVE_TANGEANT_USER) and Auto (KFCURVE_TANGEANT_AUTO) tangent modes only.
	* \return Break flag (\c true or \c false).
    */
	inline bool GetBreak() const; 

	/** Initialize key
	*/
	inline void Init();


private:
	friend class KFCurve;
	inline KFCurveKey(const KPriFCurveKey& pKey, const KPriFCurveKeyAttr& pAttr);
	inline KPriFCurveKeyAttr GetKeyAttr() const;

	FbxTime mTime;
	kFCurveDouble mValue;			
	FbxUInt32 mFlags;

	#ifdef KFCURVE_FLOAT
		float  mData[4];
	#else 
		double	mData[2];
		FbxInt16	mWeight[2];
		FbxInt16	mVelocity[2];
	#endif 	
};

#ifdef KFCURVE_FLOAT
	extern FBXSDK_DLL void TangentWeightAndAdjustTangent(EKFCurveDataIndex pIndex, kFCurveDouble pWeight, float mData[4]);
#else
	extern FBXSDK_DLL void TangentWeightAndAdjustTangent(EKFCurveDataIndex pIndex, kFCurveDouble pWeight, double mData[2], FbxInt16 mWeight[2]);
#endif

const int KEY_BLOCK_SIZE	= 1024;
const int KEY_BLOCK_COUNT	= KEY_BLOCK_SIZE/sizeof (KPriFCurveKey);

const int KEY_LIST_BLOCK_SIZE	= 256;
const int KEY_LIST_BLOCK_COUNT	= KEY_LIST_BLOCK_SIZE/sizeof (KPriFCurveKey *);

/** 
* @note This class is subject to be deprecated in future releases. It is strongly
* suggested to use FbxAnimCurve instead.
*
* An animation curve, defined by a collection of keys (KFCurveKey), and indicating how a value changes over time.
* Since an animation curve is a function, on a given animation curve, only one key per time is
* allowed. The keys are sorted
* in time order. They can be accessed by their index on the curve, from 0 to FbxAnimCurve::KeyGetCount-1.
* The time unit in FBX (FbxTime) is 1/46186158000 of one second. 
*
* Each key defines tangents and interpolation that modify the animation curve.
* Tangents control the way the animation curve enters and exits the keys.
* Interpolation indicates the animation curve's behavior between keys.
*
* Interpolation modes are
* \li Constant - Curve value stays the same until next key
* \li Linear - Animation curve is a straight line
* \li Cubic - Animation curve is a Bezier spline
*
* Tangent modes are
* \li Auto (Spline cardinal)
* \li Spline TCB (Tension, Continuity, Bias)
* \li User (Next slope at the left equal to slope at the right)
*
* Tangent modes can be overridden by more tangent options:
* \li Break (Independent left and right slopes)
* \li Clamp (Key should be flat if next or previous key has the same value)
* \li Clamp progressive (Key should be flat if tangent control point is outside [next-previous key] range)
* \li Time independent
*
* Tangent can be modified some more by adding weights and velocity.
* By default, the weights are 0.333 on either side of the key, and there is 
* no velocity. Velocity settings speed up or slow down animation on either side of 
* a key without changing the trajectory of the animation. Unlike Auto and Weight settings, 
* Velocity changes the animation in time, but not in space.
*
* Extrapolation determines the state of a curve before the first key (pre-extrapolation) and after the last key (post-extrapolation).
* Extrapolation modes are
* \li Constant: The curve is flat at extrapolation site
* \li Repetition: The extrapolated curve is the same as the curve between the first and last keys, and repeated a number of times.
* \li Mirror Repetition: Same as Repetition mode, but the curve is mirrored
* \li Keep Slope: The slope of the extrapolated curve is the same as the slope on the first (or last) key of the curve.
* 
* @note When adding keys to an animation curve, use KFCurve::KeyModifyBegin and KFCurve::KeyModifyEnd.
* @nosubgrouping
*/
class FBXSDK_DLL KFCurve
{

public:

    /**
    * \name Constructor and Destructor
    */
    //@{

    //! Constructor. Use FbxNew<KFCurve> instead, to ensure that the FBX memory allocators are used.
    KFCurve();

    //! Destructor. Use Destroy instead, to ensure that the FBX memory allocators are used.
    virtual ~KFCurve();

	/** Destructor, for KFCurve created using FbxNew.
	 *  \param Local Unused.
	 **/
    void Destroy(int Local=0);

    //@}

    /**
    * \name General curve functions
    */
    //@{
    /**	Get animation curve color.
    *	\return Pointer to an array of 3 elements: RGB values on a scale from 0 to 1.
    */
    float* GetColor();

    /** Set animation curve color.
    *	\param pColor Pointer to an array of 3 elements: RGB values on a scale from 0 to 1.
    */
    void SetColor(const float *pColor);

    /** Set the animation curve's default value.
    * Default value is used when there is no key in the animation curve.
    *	\param pValue Default value.
    */
    void SetValue(kFCurveDouble pValue);

    /** Get the animation curve's default value.
    * Default value is used when there is no key in the animation curve.
    *	\return Default value.
    */
    inline kFCurveDouble GetValue() const;
    //@}

    /**
    * \name Key Management
    */
    //@{

    /** Resize animation curve buffer to hold a certain number of keys.
    * \param pKeyCount Number of keys the animation curve will eventually hold.
    * \param pResetKeyCount If true, key count will be reset to 0
    */
    void ResizeKeyBuffer(int pKeyCount, bool pResetKeyCount = false);

    /** Call this function prior to adding, removing or editing keys of an animation curve.
    * Call function KFCurve::KeyModifyEnd() after modification.
    */
    void KeyModifyBegin ();

    /** Call this function after adding, removing or editing keys of an animation curve.
    * Function KFCurve::KeyModifyBegin() must have been called prior to modifying the keys.
    */
    void KeyModifyEnd ();

    /** Get the number of keys.
          * \return Key count.
          */
    int KeyGetCount () const;

    //! Get the number of selected keys.
    int KeyGetSelectionCount () const;

    //! Select all keys.
    void KeySelectAll ();

    //! All keys become not selected.
    void KeyUnselectAll ();

    /** Get key at given index.
    * \param pIndex Index of the key on the animation curve.
    * \return Pointer to the key at the given index.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    KFCurveKey KeyGet(kFCurveIndex pIndex) const;

    //! Remove all the keys of the animation curve and free buffer memory.
    void KeyClear ();

    /** Minimize use of buffer memory.
	* Use this method after a lot of changes have been made to keys, on an animation curve with a lot of keys.
	*/
    void KeyShrink();

    /** Set (or replace) key at given index with given key. 
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * \param pIndex Index of the key to be set or replaced.
    * \param pKey New key at this index.
    * \return \c true if key time is superior to previous key time
    * and inferior to next key time, \c false otherwise.
    */
    bool	KeySet(kFCurveIndex pIndex, KFCurveKey& pKey);

    /** Set (or replace) key at given index with key from another curve, at given source index.
    * Result is undetermined if one of the animation curves has no key, or if one
	* of the indices is out of bounds.
    * \param pIndex Index of the key to be set or replaced.
    * \param pSourceCurve Source animation curve for the new key.
    * \param pSourceIndex Index to select the new key in the source animation curve.
    * \return \c true if key time is superior to previous key time
    * and inferior to next key time, \c false otherwise.
    */
    bool	KeySet(kFCurveIndex pIndex, KFCurve* pSourceCurve, int pSourceIndex);

    /** Change time of key found at given index. The new key index is computed and returned.
    *	\param pIndex Index of key to move.
    *	\param pTime Destination time.
    *	\return New index of moved key.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    int KeyMove(kFCurveIndex pIndex, FbxTime pTime);

    /** Add time and value offsets to keys (all keys or only keys that are selected).
	*   \note The keys might have different indices after this method is called, but the new
	*   indices are not returned.
    *	\param pSelectedOnly If set to \c true, only keys that have their selection flag set are affected.
    *   If set to \c false, all keys are affected.
    *	\param pDeltaTime Time offset added to keys.
    *	\param pDeltaValue Value offset added to keys.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyMoveOf (bool pSelectedOnly, FbxTime pDeltaTime, kFCurveDouble pDeltaValue);

    /** Set value of keys (all keys or only keys that are selected).
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pValue New key value.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyMoveValueTo (bool pSelectedOnly, kFCurveDouble pValue);

    /** Scale value of keys (all keys or only keys that are selected).
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key values.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyScaleValue (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Scale tangent of keys (all keys or only keys that are selected).
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key tangents.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyScaleTangeant (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Scale value and tangent of keys (all keys or only keys that are selected).
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key values and tangents.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyScaleValueAndTangeant (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Remove key at given index. Other key indices are updated automatically.
    *	\param pIndex Index of key to remove.
    *	\return \c true on success, \c false otherwise.
    */
    bool KeyRemove(kFCurveIndex pIndex);

    /** Insert a key at given time.
    *	This function should be used instead of KFCurve::KeyAdd() if the key 
    * is to be added in the curve and not at the end. It inserts the key in 
    * respect to the interpolation type and tangents of the neighboring keys. 
    * If there is already a key a the given time, the key is modified and no 
    * new key is added.
    *	\param pTime Time of the new key.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was inserted 
    * or already present.
    * Key value must be set explicitly afterwards. The 
    * interpolation type and tangent mode are copied from the previous key.
    */
    int KeyInsert ( FbxTime pTime, kFCurveIndex* pLast = NULL );

    /** Add a given key at given time. The new key is appended after all the other animation curve's keys.
    *	Function KFCurve::KeyInsert() should be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect the interpolation type and tangents of the neighboring keys. 
    * If there is already a key at the given time, the key is modified and no 
    * new key is added.
    *	\param pTime Time of the new key.
    * \param pKey Key to add.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was added 
    * or already present.
    * Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */
    int KeyAdd (FbxTime pTime, KFCurveKey& pKey, kFCurveIndex* pLast = NULL);

    /** Add a key from another curve at given time. The new key is appended after all the other animation curve's keys.
    *	Function KFCurve::KeyInsert() should be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect the interpolation type and tangents of the neighboring keys. 
    * If there is already a key at the given time, the key is modified and no 
    * new key is added.
    * \param pTime Time of the new key.
    * \param pSourceCurve Source animation curve of the new key.
    * \param pSourceIndex Index of the new key in the source animation curve.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    * \return Index of the key at given time, no matter if it was added 
    * or already present.
    * Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */ 
    int KeyAdd(FbxTime pTime, KFCurve* pSourceCurve, int pSourceIndex, kFCurveIndex* pLast = NULL);

    /** Add a key at given time. The new key is appended after all the other animation curve's keys.
    *	Function KFCurve::KeyInsert() should be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect of the interpolation type and tangents of the neighboring keys. 
    * If there is already a key a the given time, no key is added.
    *	\param pTime Time of the new key.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was added 
    * or already present.
    * Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */
    int KeyAdd (FbxTime pTime, kFCurveIndex* pLast = NULL);

    /** Append a key at the end of the animation curve.
    * \param pAtTime Time of appended key, must be superior to the 
    * last key time.
    * \param pSourceCurve Source curve.
    * \param pSourceIndex Index of the source key in the source curve.
    * \return Index of appended key or -1 if pAtTime is inferior to the last key's time.
    */
    int KeyAppend(FbxTime pAtTime, KFCurve* pSourceCurve, int pSourceIndex);

    /** To be deprecated: Append a key at the end of the animation curve
    * \param pTime Time of appended key, must be superior to the 
    * last key time.
    * \param pValue Value of appended key.
    * \return Index of appended key or -1 if pTime is inferior to the last key's time.
    * Interpolation type of the appended key is set to 
    * KFCURVE_INTERPOLATION_CUBIC and tangent mode is set to 
    * KFCURVE_TANGEANT_AUTO.
	* \remarks Subject to become deprecated.
    */
    int KeyAppendFast( FbxTime pTime, kFCurveDouble pValue );

    /** Find key index for a given time.
    *	\param pTime Time of the key looked for.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Key index. The integer part of the key index gives the 
    * index of the closest key with a smaller time. The decimals give
    * the relative position of given time compared to previous and next
    * key times. Returns -1 if animation curve has no key.
	*
	* For example (using seconds for clarity), if there is a key at time 10s with index 5, and a key at
	* time 11s with index 6, KeyFind(10.3s) would return 5.3.
    */
    double KeyFind (FbxTime pTime, kFCurveIndex* pLast = NULL);	

    //@}

    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/


    /**
    * \name Key Manipulation
    */
    //@{

    /** General function to set key properties.
	* The key at index pKeyIndex is retrieved and modified according to the other parameters. 
	* The key must have been previously created, for example using KeyAdd.
    *	Use KFCurve::SetTCB() in the specific case of setting a key with cubic interpolation and TCB tangent mode.
    *   \param pKeyIndex        Index of the key.
    *	\param pTime			Key time.
    *	\param pValue			Key value.
    *	\param pInterpolation	Key interpolation type.	Interpolation types are: 
    *							KFCURVE_INTERPOLATION_CONSTANT, 
    *							KFCURVE_INTERPOLATION_LINEAR,
    *							KFCURVE_INTERPOLATION_CUBIC (default).
    *	\param pTangentMode		Key tangent mode (meaningful for cubic 
    *							interpolation only). Valid tangent modes are: 
    *							KFCURVE_TANGEANT_AUTO (default),
    *							KFCURVE_TANGEANT_USER,
    *							KFCURVE_TANGEANT_BREAK.
    *	\param pRightSlope			Value of right derivative.
    *	\param pNextLeftSlope		Value of next left slope.
    *	\param pTangentWeightMode	Weight mode, if used. Weight modes are:
    *								KFCURVE_WEIGHTED_NONE (default),
    *								KFCURVE_WEIGHTED_RIGHT,
    *								KFCURVE_WEIGHTED_NEXT_LEFT,
    *								KFCURVE_WEIGHTED_ALL.
    *	\param pWeight0				Weight for right slope, if tangent weight mode is KFCURVE_WEIGHTED_RIGHT or KFCURVE_WEIGHTED_ALL.
    *	\param pWeight1				Weight for next left slope, if tangent weight mode is KFCURVE_WEIGHTED_NEXT_LEFT or KFCURVE_WEIGHTED_ALL.
    *	\param pVelocity0			Velocity for right slope, if tangent velocity mode is KFCURVE_VELOCITY_RIGHT or KFCURVE_VELOCITY_ALL.
    *	\param pVelocity1			Velocity for next left slope, if tangent velocity mode is KFCURVE_VELOCITY_NEXT_LEFT or KFCURVE_VELOCITY_ALL.
    */
    inline void KeySet 
        (
        kFCurveIndex pKeyIndex,
        FbxTime pTime, 
        kFCurveDouble pValue, 
        kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
        kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
        kFCurveDouble pRightSlope = 0.0,
        kFCurveDouble pNextLeftSlope = 0.0,
        kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
        kFCurveDouble pWeight0                             = KFCURVE_DEFAULT_WEIGHT,
        kFCurveDouble pWeight1                             = KFCURVE_DEFAULT_WEIGHT,
        kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
        kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
        );

    /**	Set a key with cubic interpolation, TCB tangent mode. 	
	* The key at index pKeyIndex is retrieved and modified according to the other parameters. 
	* The TCB mode controls the tension, continuity,
	* and bias of the curve.
    *   \param pKeyIndex  Index of the key.
    *	\param pTime	Key time.
    *	\param pValue	Key value.
    *	\param pData0	Tension. Controls the amount of curvature in the animation curve. The higher the tension is, the more linear
	* the curve looks. When the tension is low, the curve looks rounder or wider. 
    *	\param pData1	Continuity. Controls the smoothness or singularity of the curve on the key. 
    *	\param pData2	Bias. Controls if the effect of tension and continuity affect the curve before or after the key.
    */
    inline void KeySetTCB 
        (
        kFCurveIndex pKeyIndex,
        FbxTime pTime, 
        kFCurveDouble pValue, 
        float pData0 = 0.0f, 
        float pData1 = 0.0f, 
        float pData2 = 0.0f
        );

    /** Get key's interpolation type.
    *	Interpolation types are: 
	* \e KFCURVE_INTERPOLATION_CONSTANT Constant value until next key.
    * \e KFCURVE_INTERPOLATION_LINEAR Linear progression to next key.
    * \e KFCURVE_INTERPOLATION_CUBIC Cubic progression to next key.
    *   \param pKeyIndex         Index of the queried key.
    *   \return                  Interpolation type of the queried key.
    */
    inline kFCurveInterpolation KeyGetInterpolation(kFCurveIndex pKeyIndex) const;

    /** Set key's interpolation type.
    *	Interpolation types are: 
	* \e KFCURVE_INTERPOLATION_CONSTANT Constant value until next key.
    * \e KFCURVE_INTERPOLATION_LINEAR Linear progression to next key.
    * \e KFCURVE_INTERPOLATION_CUBIC Cubic progression to next key.
    *   \param pKeyIndex      Index of the key.
    *	\param pInterpolation Key interpolation type.
    */
    inline void KeySetInterpolation(kFCurveIndex pKeyIndex, kFCurveInterpolation pInterpolation);

    /** Returns \c true if interpolation is cubic and the tangents and weightings are untouched (default values).
    *	\param	pKeyIndex	Index of the key to test.
    *	\return				Returns \c true if the interpolation is a pure cubic auto.
    */
    bool IsKeyInterpolationPureCubicAuto(kFCurveIndex pKeyIndex);

    /** Get key's constant mode.
    *	\note This method is only relevant if the key's interpolation type is constant (KFCURVE_INTERPOLATION_CONSTANT).
    *	Using this method on a key with an other interpolation type will return unpredictable value.
	* Constant modes are:
	* \e KFCURVE_CONSTANT_STANDARD Curve value is constant between this key and the next
	* \e KFCURVE_CONSTANT_NEXT Curve value is constant, with next key's value
    *   \param pKeyIndex      Index of the queried key.
    *	\return Key constant mode.
    */
    inline kFCurveConstantMode KeyGetConstantMode(kFCurveIndex pKeyIndex) const;

    /** Get key's tangent mode.
    *   \param pKeyIndex The key index.
    *   \param pIncludeOverrides Include override flags: Break, Clamp, Time-Independent.
    *	This method is meaningful for cubic interpolation only.
    *			 Using this method for non cubic interpolated key will return unpredictable value.
	*	Tangent modes are: 
	* \e KFCURVE_TANGEANT_AUTO Auto key (spline cardinal).
	* \e KFCURVE_TANGEANT_TCB Spline TCB (Tension, Continuity, Bias)
	* \e KFCURVE_TANGEANT_USER Next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_BREAK Independent left and right slopes, with next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_AUTO_BREAK Independent left and right slopes, with auto key.
    *	\return Key tangent mode.
    */
    inline kFCurveTangeantMode KeyGetTangeantMode(kFCurveIndex pKeyIndex, bool pIncludeOverrides = false ) const;

    /** Get key's tangent weight mode.
    *	This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	
	* \e KFCURVE_WEIGHTED_NONE Tangent has default weights of 0.333; we define this state as not weighted.
	* \e KFCURVE_WEIGHTED_RIGHT Right tangent is weighted.
	* \e KFCURVE_WEIGHTED_NEXT_LEFT Left tangent is weighted.
	* \e KFCURVE_WEIGHTED_ALL Both left and right tangents are weighted.
    * \param pKeyIndex The key index.
    */
    inline kFCurveTangeantWeightMode KeyGetTangeantWeightMode(kFCurveIndex pKeyIndex) const;

    /** Get key's tangent velocity mode.
    *	This method is meaningful for cubic interpolation only.
    *	Tangent velocity modes are:	
	* \e KFCURVE_VELOCITY_NONE No velocity (default).
	* \e KFCURVE_VELOCITY_RIGHT Right tangent has velocity.
	* \e KFCURVE_VELOCITY_NEXT_LEFT Left tangent has velocity.
	* \e KFCURVE_VELOCITY_ALL Both left and right tangents have velocity.
    * \param pKeyIndex The key index.
    */
    inline kFCurveTangeantVelocityMode KeyGetTangeantVelocityMode(kFCurveIndex pKeyIndex) const;

    /** Set key's constant mode.
    *	This method is meaningful for constant interpolation only.
    *   \param pKeyIndex            Index of the key.
    *	\param pMode Key constant mode.
	* Constant modes are:
	* \e KFCURVE_CONSTANT_STANDARD Curve value is constant between this key and the next
	* \e KFCURVE_CONSTANT_NEXT Curve value is constant, with next key's value
    */
    inline void KeySetConstantMode(kFCurveIndex pKeyIndex, kFCurveConstantMode pMode);

    /** Set key's tangent mode.
    *	This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Index of the key.
    *	\param pTangent Key tangent mode.
	*	Tangent modes are: 
	* \e KFCURVE_TANGEANT_AUTO Auto key (spline cardinal).
	* \e KFCURVE_TANGEANT_TCB Spline TCB (Tension, Continuity, Bias)
	* \e KFCURVE_TANGEANT_USER Next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_BREAK Independent left and right slopes, with next slope at the left equal to slope at the right.
	* \e KFCURVE_TANGEANT_AUTO_BREAK Independent left and right slopes, with auto key.
  * \param pIgnoreAutoTimeIndepedentConversion \b true ignore the auto time independent conversion flag.
    */
	inline void KeySetTangeantMode(kFCurveIndex pKeyIndex, kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);

    /** Set key's tangent weight mode as double value (cubic interpolation, non TCB tangent mode).
    *	This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Index of the key.
    *	\param pTangentWeightMode	Weight mode.
    *								Values are: 
	* \e KFCURVE_WEIGHTED_NONE Tangent has default weights of 0.333; we define this state as not weighted.
	* \e KFCURVE_WEIGHTED_RIGHT Right tangent is weighted.
	* \e KFCURVE_WEIGHTED_NEXT_LEFT Left tangent is weighted.
	* \e KFCURVE_WEIGHTED_ALL Both left and right tangents are weighted.
    *	\param pMask				Used to select the affected tangents
    *								Mask values are: KFCURVE_WEIGHTED_RIGHT,
    *								KFCURVE_WEIGHTED_NEXT_LEFT,
    *								KFCURVE_WEIGHTED_ALL
    */

    inline void KeySetTangeantWeightMode(kFCurveIndex pKeyIndex, kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );

    /** Set key's tangent velocity mode as double value (cubic interpolation, non TCB tangent mode).
    *	This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Index of the key.
    *	\param pTangentVelocityMode	Velocity mode. Values are:
	* \e KFCURVE_VELOCITY_NONE No velocity (default).
	* \e KFCURVE_VELOCITY_RIGHT Right tangent has velocity.
	* \e KFCURVE_VELOCITY_NEXT_LEFT Left tangent has velocity.
	* \e KFCURVE_VELOCITY_ALL Both left and right tangents have velocity.
    *	\param pMask				Used to select the affected tangents. Mask values are:
    *								KFCURVE_VELOCITY_RIGHT,
    *								KFCURVE_VELOCITY_NEXT_LEFT,
    *								KFCURVE_VELOCITY_ALL.
    */

    inline void KeySetTangeantVelocityMode(kFCurveIndex pKeyIndex, kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );


    /** Get key data as double value (cubic interpolation, non TCB tangent mode).
    *	Using this method for other than cubic interpolated 
    *			 key (linear, constant) will return unpredictable values.
    *	Slope data is inconsistent for automatic tangent mode.
    *			 Use KFCurve::EvaluateLeftDerivative() and 
    *			 KFCurve::EvaluateRightDerivative() to find
    *			 slope values.
    *	For a TCB tangent mode key, use KFCurve::KeyGetDataFloat() instead.
    *   \param pKeyIndex   Index of the queried key.
    *	\param pIndex Data index:
	* \e KFCURVEKEY_RIGHT_SLOPE Index of the right derivative
	* \e KFCURVEKEY_NEXT_LEFT_SLOPE Index of the left derivative for the next key.
	* \e KFCURVEKEY_RIGHT_WEIGHT Index of weight on right tangent.
	* \e KFCURVEKEY_NEXT_LEFT_WEIGHT Index of weight on next key's left tangent.
	* \return Slope value or weight value.
    */
    inline kFCurveDouble KeyGetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const;

    /**	Set data as double value (cubic interpolation, non TCB tangent mode).
    *	Slope data is inconsistent for automatic tangent mode.
    *			 Therefore, it is irrelevant to use this method on automatic 
    *			 tangent mode keys.
    *	Using this method for other than cubic interpolated 
    *			 key (linear, constant) is irrelevant.
    *	For a TCB tangent mode key, use KFCurve::SetDataFloat() 
    *			 instead.
    *   \param pKeyIndex   Index of the key.
    *	\param pIndex Data index:
	* \e KFCURVEKEY_RIGHT_SLOPE Index of the right derivative
	* \e KFCURVEKEY_NEXT_LEFT_SLOPE Index of the left derivative for the next key.
	* \e KFCURVEKEY_RIGHT_WEIGHT Index of weight on right tangent.
	* \e KFCURVEKEY_NEXT_LEFT_WEIGHT Index of weight on next key's left tangent.
    *	\param pValue	The data value to set (a slope or a weight).
    */
    inline void KeySetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, kFCurveDouble pValue);

	/** Get key data in the case of a cubic interpolation with TCB tangent mode.
	*	Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredictable values.
    *   \param pKeyIndex   Index of the key.
	*	\param pIndex	Data index: either 
	* \e KFCURVEKEY_TCB_TENSION Tension
	* \e KFCURVEKEY_TCB_CONTINUITY Continuity, or 
	* \e KFCURVEKEY_TCB_BIAS Bias.
	* \return Key data value.
	*/	
    inline float KeyGetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const;

	/**	Set data value in the case of a cubic interpolation with TCB tangent mode.
	*	Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredictable values.
    *   \param pKeyIndex   Index of the key.
	*	\param pIndex	Data index, either
	* \e KFCURVEKEY_TCB_TENSION Tension
	* \e KFCURVEKEY_TCB_CONTINUITY Continuity, or 
	* \e KFCURVEKEY_TCB_BIAS Bias.
	*	\param pValue	Data value to set.
	*/
    inline void KeySetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, float pValue);

    /**	Get key data as a pointer
    * \param pKeyIndex Index of the queried key.
	* \return Data as a float array.
    */
    inline const float* KeyGetDataPtr(kFCurveIndex pKeyIndex) const;

    /**	Get key value.
    * \param pKeyIndex Index of the queried key.
	* \return Key value.
	* \remark kFCurveDouble is defined as float.
    */
    inline kFCurveDouble KeyGetValue(kFCurveIndex pKeyIndex) const;

    /** Set key value.
    * \param pKeyIndex Index of the key.
    * \param pValue The value to set.
	* \remark kFCurveDouble is defined as float.
    */ 
    inline void KeySetValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Increment key value.
    *   \param pKeyIndex   Index of the key.
    *	\param pValue Term added to the key value.
	* \remark kFCurveDouble is defined as float.
    */
    inline void KeyIncValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Multiply key value.
    *   \param pKeyIndex   Index of the key.
    *	\param pValue Factor multiplying the key value.
	* \remark kFCurveDouble is defined as float.
	* \see KFCurve::KeyMultTangent.
    */
    inline void KeyMultValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Multiply key tangents.
    *	\remark When multiplying a key value, tangents must be
    *         multiplied to conserve the same topology.
	* \remark kFCurveDouble is defined as float.
    *   \param pKeyIndex   Index of the key.
    *	\param pValue Factor multiplying the key tangents.
    */
    inline void KeyMultTangeant(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Get key time
    *   \param pKeyIndex   Index of the queried key.
    *	\return Key time (time at which this key is occurring).
    */
    inline FbxTime KeyGetTime(kFCurveIndex pKeyIndex) const;

    /** Set key time.
    *   \param pKeyIndex   Index of the key.
    *	\param pTime Key time (time at which this key is occurring).
	* \remark The new key time might modify the key index.
    */
    inline void KeySetTime(kFCurveIndex pKeyIndex, FbxTime pTime);

    /** Increment key time.
    *   \param pKeyIndex   Index of the key.
    *	\param pTime Time value by which the key time is incremented.
	* \remark The new key time might modify the key index.
    */
    inline void KeyIncTime(kFCurveIndex pKeyIndex, FbxTime pTime);

    /** Select or unselect key. Some functions can modify either all keys or only selected keys: 
	* KFCurve::KeyTangeantSetInterpolation, KFCurve::KeyTangeantSetMode, KFCurve::KeyMoveOf, KFCurve::KeyMoveValueTo,
	* KFCurve::KeyScaleValue, KFCurve::KeyScaleTangeant, KFCurve::KeyScaleValueAndTangeant.
	*   \param pKeyIndex   Index of the key.
    *	\param pSelected Selection flag.
    */
    inline void KeySetSelected(kFCurveIndex pKeyIndex, bool pSelected);	

    /** Return \c true if key is currently selected, \c false otherwise.
    *   \param pKeyIndex   Index of the queried key.
    *	\return Selection flag (\c true or \c false).
    */
    inline bool KeyGetSelected(kFCurveIndex pKeyIndex) const;

    /** Set key's manipulation flag.
	* \remark To mark a key for manipulation makes sense in the context of a graphical interface.
    * The FBX SDK doesn't have such an interface, and this function is not used in the SDK.
    *   \param pKeyIndex   Index of the key.
    *	\param pMark Mark this key for manipulation.
    */
    inline void KeySetMarkedForManipulation(kFCurveIndex pKeyIndex, bool pMark);	

    /** Return \c true if key is currently marked for manipulation, \c false otherwise.
	* \remark To mark a key for manipulation makes sense in the context of a graphical interface.
    * The FBX SDK doesn't have such an interface, and this function is not used in the SDK.
    *   \param pKeyIndex   Index of the queried key.
    *	\return \c true if key is marked for manipulation, \c false otherwise.
    */
    inline bool KeyGetMarkedForManipulation(kFCurveIndex pKeyIndex) const;

    /** Set tangent visibility mode. This would indicate what part of the tangent is visible in a graphical interface.
    *	This method is relevant for cubic interpolation only.
    *   \param pKeyIndex   Index of the key.
    *	\param pVisibility	Tangent visibility mode.
	*	Tangent visibility modes are: 
	* \e KFCURVE_TANGEANT_SHOW_NONE No tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_LEFT Left tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_RIGHT Right tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_BOTH	Both left and right tangents are visible.
    */
    inline void	KeySetTangeantVisibility (kFCurveIndex pKeyIndex, kFCurveTangeantVisibility pVisibility);	

    /** Return tangent visibility mode.
    *	This method is relevant for cubic interpolation only.
    *   \param pKeyIndex   Index of the queried key.
    *	\return Tangent visibility mode.
	*	Tangent visibility modes are: 
	* \e KFCURVE_TANGEANT_SHOW_NONE No tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_LEFT Left tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_RIGHT Right tangent is visible.
	* \e KFCURVE_TANGEANT_SHOW_BOTH	Both left and right tangents are visible.
    */
    inline kFCurveTangeantVisibility KeyGetTangeantVisibility (kFCurveIndex pKeyIndex) const;

    /** Set or unset the tangent break. When this flag is set (KFCURVE_TANGEANT_BREAK), the key's left and right slopes are independent.
	* When this flag is off, the key's left and right slope are equal.
    * This method is relevant for User (KFCURVE_TANGEANT_USER) and Auto (KFCURVE_TANGEANT_AUTO) tangent modes only.
    * \param pKeyIndex Index of the key.
    * \param pVal Break flag (\c true or \c false).
    */
    inline void KeySetBreak(kFCurveIndex pKeyIndex, bool pVal); 

    /** Get if the tangent has a break. When this flag is set (KFCURVE_TANGEANT_BREAK), the key's left and right slopes are independent.
	* When this flag is off, the key's left and right slope are equal.
    * This method is relevant for User (KFCURVE_TANGEANT_USER) and Auto (KFCURVE_TANGEANT_AUTO) tangent modes only.
    * \param pKeyIndex Index of the queried key.
	* \return Break flag (\c true or \c false).
    */
    inline bool KeyGetBreak(kFCurveIndex pKeyIndex) const; 

    //@}

    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/

    /**
    * \name Key Tangent Management
    */
    //@{

    /** Set interpolation type on keys. Modify either all keys or only selected keys.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pInterpolation Interpolation type.
    */
    void KeyTangeantSetInterpolation(bool pSelectedOnly, kFCurveInterpolation pInterpolation);

    /** Set tangent mode on keys. Modify either all keys or only selected keys.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pTangentMode Tangent mode.
    * Tangent mode is only relevant on keys with a cubic interpolation type. 
	* If the key's interpolation type is constant or linear, this function has no effect on the animation curve shape.
    */
    void KeyTangeantSetMode(bool pSelectedOnly, kFCurveTangeantMode pTangentMode);

    /** Get the left derivative of a key.
    *	\param pIndex Index of the queried key.
    *	\return Left derivative (Value over time (s)).
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetLeftDerivative(kFCurveIndex pIndex);

    /** Set the left derivative of a key.
    *	\param pIndex Index of the key.
    *	\param pValue Left derivative.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO. 
    */
    void KeySetLeftDerivative(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** Get the left auto parametric of a key. This is used to compute the slope of Auto and User keys.
    *	\param pIndex Index of the key.
    *	\param pApplyOvershootProtection Clamp flag (KFCURVE_GENERIC_CLAMP) is taken into account.
    *	\return Left auto parametric.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetLeftAuto(kFCurveIndex pIndex, bool pApplyOvershootProtection = false);

    /** Set the left auto parametric of a key. This is used to compute the slope of Auto and User keys.
    *	\param pIndex Index of the key.
    *	\param pValue Left auto parametric.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetLeftAuto(kFCurveIndex pIndex, kFCurveDouble pValue);	

    /** Get the left derivative info (of type KFCurveTangeantInfo) of a key.
    *	\param pIndex Index of the queried key.
    *	\return Left derivative info.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    KFCurveTangeantInfo KeyGetLeftDerivativeInfo(kFCurveIndex pIndex);

    /** Set the left derivative info (of type KFCurveTangeantInfo) of a key.
    *	\param pIndex Index of the key.
    *	\param pValue Left derivative info.
    *   \param pForceDerivative If \c true, assign the tangent info's derivative value to the key derivative.
	* If \c false, use the tangent info's auto parametric value to recompute the key derivative.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetLeftDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false);


    /** Increment the left derivative of a key.
    *	\param pIndex Index of the key.
    *	\param pInc Term to add to the left slope.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyIncLeftDerivative(kFCurveIndex pIndex, kFCurveDouble pInc);

    /** Get the right derivative of a key.
    *	\param pIndex Index of the key.
    *	\return Right derivative (Value over time (s)).
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetRightDerivative(kFCurveIndex pIndex);

    /** Set the right derivative of a key.
    *	\param pIndex Index of the key.
    *	\param pValue Right derivative.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetRightDerivative(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** Get the right auto parametric of a key. This is used to compute the slope of Auto and User keys.
    *	\param pIndex Index of the key.
    *	\param pApplyOvershootProtection Clamp flag (KFCURVE_GENERIC_CLAMP) is taken into account.
    *	\return Right auto parametric.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetRightAuto(kFCurveIndex pIndex, bool pApplyOvershootProtection = false);

    /** Set the right auto parametric of a key. This is used to compute the slope of Auto and User keys.
    *	\param pIndex Index of the key.
    *	\param pValue Right auto parametric.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetRightAuto(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** Get the right derivative info (of type KFCurveTangeantInfo) of a key.
    *	\param pIndex Index of the queried key.
    *	\return Right derivative info.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    KFCurveTangeantInfo KeyGetRightDerivativeInfo(kFCurveIndex pIndex);

    /** Set the right derivative info (of type KFCurveTangeantInfo) of a key.
    *	\param pIndex Index of the key.
    *	\param pValue Right derivative info.
    *   \param pForceDerivative If \c true, assign the tangent info's derivative value to the key derivative.
	* If \c false, use the tangent info's auto parametric value to recompute the key derivative.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetRightDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false);


    /** Increment the right derivative of a key.
    *	\param pIndex Index of the key.
    *	\param pInc Term to add to the right slope.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyIncRightDerivative(kFCurveIndex pIndex, kFCurveDouble pInc);

    /** This function is unsupported and subject to be deprecated.
    * \param pIndex Index of the queried key.
	* \return Unknown.
    */
    kFCurveDouble KeyGetRightBezierTangeant(kFCurveIndex pIndex);

    /** Set the left derivative of a key as a Bezier tangent.
    *	\param pIndex Index of the key.
    *	\param pValue Left derivative as a Bezier tangent.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetLeftBezierTangeant(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** This function is unsupported and subject to be deprecated.
    * \param pIndex Index of the queried key.
	* \return Unknown.
    */
    kFCurveDouble KeyGetLeftBezierTangeant(kFCurveIndex pIndex);

    /** Set the right derivative of a key as a Bezier tangent.
    *	\param pIndex Index of the key.
    *	\param pValue Right derivative as a Bezier tangent.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetRightBezierTangeant(kFCurveIndex pIndex, kFCurveDouble pValue);


    /** Multiply the derivative of a key. Both the left and right derivatives are multiplied.
    *	\param pIndex Index of the key.
    *	\param pMultValue Value that multiply Derivative
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    * This function is only relevant if key tangent type is 
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyMultDerivative(kFCurveIndex pIndex, kFCurveDouble pMultValue);

    /** Get the left tangent weight mode of a key.
    *	\param pIndex Index of queried key.
    *	\return \c true if the key is left weighted (Weight mode is KFCURVE_WEIGHTED_NEXT_LEFT or KFCURVE_WEIGHTED_ALL). \c false otherwise.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    bool KeyIsLeftTangeantWeighted(kFCurveIndex pIndex) const;

    /** Get the right tangent weight mode of a key.
    *	\param pIndex Index of queried key.
    *	\return \c true if the key is right weighted (Weight mode is KFCURVE_WEIGHTED_RIGHT or KFCURVE_WEIGHTED_ALL). \c false otherwise.
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    bool KeyIsRightTangeantWeighted(kFCurveIndex pIndex) const;

    /** Set the left tangent weight mode of a key (KFCURVE_WEIGHTED_NEXT_LEFT).
    *	\param pIndex Index of the key.
    *	\param pWeighted Weighted state of the tangent.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetLeftTangeantWeightedMode( kFCurveIndex pIndex, bool pWeighted);

    /** Set the right tangent weight mode of a key (KFCURVE_WEIGHTED_RIGHT).
    *	\param pIndex Index of the key.
    *	\param pWeighted Weighted state of the tangent.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetRightTangeantWeightedMode( kFCurveIndex pIndex, bool pWeighted);

    /** Get the weight value component of the left tangent of a key.
    *	\param pIndex Index of the key.
    *	\return Left tangent weight, or KFCURVE_DEFAULT_WEIGHT (0.333...) if left tangent is not weighted.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC.
    */
    kFCurveDouble KeyGetLeftTangeantWeight(kFCurveIndex pIndex) const;

    /** Get the weight value component of the right tangent of a key.
    *	\param pIndex Index of the key.
    *	\return Right tangent weight, or KFCURVE_DEFAULT_WEIGHT (0.333...) if right tangent is not weighted.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC.
    */		
    kFCurveDouble KeyGetRightTangeantWeight(kFCurveIndex pIndex) const;

    /** Set the left tangent weight of a key
    *	\param pIndex Index of the key.
    *	\param pWeight Weight to set on the left tangent.
    *   \param pAdjustTan If true, recompute the tangent height to compensate for very small weights.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in weighted mode.
    * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
    * set before calling this function.
    */
    void   KeySetLeftTangeantWeight( kFCurveIndex pIndex, kFCurveDouble pWeight, bool pAdjustTan = false );

    /** Set the right tangent weight of a key
    *	\param pIndex Index of the key.
    *	\param pWeight Weight to set on the right tangent.
    *   \param pAdjustTan If true, recompute the tangent height to compensate for very small weights.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in weighted mode.
    * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
    * set before calling this function.
    */
    void   KeySetRightTangeantWeight( kFCurveIndex pIndex, kFCurveDouble pWeight, bool pAdjustTan = false  );

    /** Get the left tangent velocity mode of a key
    *	\param pIndex Index of the key.
    *	\return \c true if the key's left tangent has velocity (Velocity mode is KFCURVE_VELOCITY_NEXT_LEFT or KFCURVE_VELOCITY_ALL).
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    bool KeyIsLeftTangeantVelocity(kFCurveIndex pIndex) const;

    /** Get the right tangent velocity mode of a key
    *	\param pIndex Index of the key.
    *	\return \c true if the key's right tangent has velocity (Velocity mode is KFCURVE_VELOCITY_RIGHT or KFCURVE_VELOCITY_ALL).
    * Result is undetermined if animation curve has no key or if index 
    * is out of bounds.
    */
    bool KeyIsRightTangeantVelocity(kFCurveIndex pIndex) const;

    /** Set the left tangent velocity mode of a key (KFCURVE_VELOCITY_NEXT_LEFT).
    *	\param pIndex Index of the key.
    *	\param pVelocity Velocity state of the tangent
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetLeftTangeantVelocityMode( kFCurveIndex pIndex, bool pVelocity );

    /** Set the right tangent velocity mode of a key (KFCURVE_VELOCITY_RIGHT).
    *	\param pIndex Index of the key.
    *	\param pVelocity Velocity state of the tangent
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetRightTangeantVelocityMode( kFCurveIndex pIndex, bool pVelocity);

    /** Get the velocity value component of the left tangent of a key
    *	\param pIndex Index of the key.
    *	\return Tangent velocity of the left tangent.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */
    kFCurveDouble KeyGetLeftTangeantVelocity(kFCurveIndex pIndex) const;

    /** Get the velocity value component of the right tangent of a key
    *	\param pIndex Index of the key.
    *	\return Tangent velocity of the right tangent.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */		
    kFCurveDouble KeyGetRightTangeantVelocity(kFCurveIndex pIndex) const;

    /** Set the left tangent velocity of a key
    *	\param pIndex Index of the key.
    *	\param pVelocity Value of the velocity for the left tangent.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in velocity mode.
    */
    void   KeySetLeftTangeantVelocity( kFCurveIndex pIndex, kFCurveDouble pVelocity );

    /** Set the right tangent velocity of a key
    *	\param pIndex Index of the key.
    *	\param pVelocity Value of the velocity for the right tangent.
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in velocity mode.
    */
    void   KeySetRightTangeantVelocity( kFCurveIndex pIndex, kFCurveDouble pVelocity );

    //@}

    /**
    * \name Extrapolation 
    * Extrapolation defines the animation curve value before and after the keys.
    * Pre-extrapolation defines the animation curve value before first key.
    * Post-extrapolation defines the animation curve value after last key.
	* Extrapolation modes are:
    * <ul><li>KFCURVE_EXTRAPOLATION_CONST means a constant value matching the first/last key
    *	    <li>KFCURVE_EXTRAPOLATION_REPETITION means the entire animation curve is looped
    *		<li>KFCURVE_EXTRAPOLATION_MIRROR_REPETITION means the entire animation curve is looped once backward, once forward and so on 
			<li>KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION means the entire animation curve is looped relative to last curve, and so on
    *		<li>KFCURVE_EXTRAPOLATION_KEEP_SLOPE means a linear function with a slope matching the first/last key</ul>
    */
    //@{

    /** Set pre-extrapolation mode.
    * \param pExtrapolation The extrapolation mode to set before the first key.
    */
    inline void SetPreExtrapolation(kFCurveExtrapolationMode pExtrapolation);

    //! Get pre-extrapolation mode.
    inline kFCurveExtrapolationMode GetPreExtrapolation() const;

    /** Set pre-extrapolation count.
    *	\param pCount Number of repetitions if pre-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION or KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION.
    */
    inline void SetPreExtrapolationCount(FbxULong pCount);

    /** Get pre-extrapolation count.
    *	\return Number of repetitions if pre-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION or KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION.
    */
    inline FbxULong GetPreExtrapolationCount() const;

    /** Set post-extrapolation mode.
    * \param pExtrapolation The extrapolation mode to set after the last key.
    */
    inline void SetPostExtrapolation(kFCurveExtrapolationMode pExtrapolation);

    //! Get post-extrapolation mode.
    inline kFCurveExtrapolationMode GetPostExtrapolation() const;

    /** Set post-extrapolation count.
    *	\param pCount Number of repetitions if post-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION or KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION.
    */
    inline void SetPostExtrapolationCount(FbxULong pCount);

    /** Get post-extrapolation count.
    *	\return Number of repetitions if post-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION or KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION.
    */
    inline FbxULong GetPostExtrapolationCount() const;

    /** Get total number of keys, taking extrapolation into account.
    * The total number of keys includes repetitions of the animation 
    * curve if pre-extrapolation and/or post-extrapolation are of
    * mode KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION or KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION.
    *	\return Total number of keys, taking extrapolation into account.
    */
    int KeyGetCountAll() const;

    /** Find key index for a given time taking extrapolation into account.
    *	\param pTime Time of the key looked for.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Key index between 0 and KFCurve::KeyGetCount() - 1.The 
    * integer part of the key index gives the index of the closest key 
    * with a smaller or equal time. The decimals give the relative position of 
    * given time compared to previous and next key times. Return -1 if 
    * animation curve has no key.
    */
    double KeyFindAll(FbxTime pTime, kFCurveIndex* pLast = NULL);

    //@}

    /**
    * \name Evaluation and Analysis
    */
    //@{

    /**	Evaluate animation curve value at a given time.
    *	\param pTime Time of evaluation.
    * If time falls between two keys, animation curve value is 
    * interpolated according to previous key interpolation type and
    * tangent mode if relevant.
    * \param pLast Index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Animation curve value on given time, or animation curve's default value if animation curve
    * has no key.
    * This function takes extrapolation into account.
    */
    kFCurveDouble Evaluate (FbxTime pTime, kFCurveIndex* pLast = NULL);

    /**	Evaluate animation curve value at a given key index.
    *	\param pIndex Any value between 0 and KFCurve::KeyGetCount() - 1.
    * If key index is not an integer value, animation curve value is 
    * interpolated according to previous key interpolation type and
    * tangent mode, if relevant.
    * This function does not take extrapolation into account.
    *	\return Animation curve value, or default value if animation curve
    * has no key. Result is undetermined if index is out of bounds.

    */
    kFCurveDouble EvaluateIndex( double pIndex);

    /**	Evaluate function left derivative at given time.
    *	\param pTime Time of evaluation.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Left derivative at given time.
    * This function does not take extrapolation into account. Result is undetermined if index is out of bounds.
    */
    kFCurveDouble EvaluateLeftDerivative (FbxTime pTime, kFCurveIndex* pLast = NULL);

    /**	Evaluate function right derivative at given time.
    *	\param pTime Time of evaluation.
    * \param pLast Key index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Right derivative at given time.
    * This function does not take extrapolation into account. Result is undetermined if index is out of bounds.
    */
    kFCurveDouble EvaluateRightDerivative (FbxTime pTime, kFCurveIndex* pLast = NULL);

    /**	Find the peak times between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeakTime1 First peak time (output).
    *	\param pPeakTime2 Second peak time (output).
    *	\return Number of peaks found.
    * Result is undetermined if animation curve has no key or 
    * if index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, FbxTime& pPeakTime1, FbxTime& pPeakTime2);

    /**	Find the peak values between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeak1 First peak value (output).
    *	\param pPeak2 Second peak value (output).
    *	\return Number of peaks found.
    * Result is undetermined if animation curve has no key or 
    * if index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, kFCurveDouble& pPeak1, kFCurveDouble& pPeak2);

    /**	Find the peak times and values between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeakTime1 First peak time (output).
    *	\param pPeak1 First peak value (output).
    *	\param pPeakTime2 Second peak time (output).
    *	\param pPeak2 Second peak value (output).
    *	\return Number of peaks found.
    * Result is undetermined if animation curve has no key or 
    * if index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, FbxTime& pPeakTime1, kFCurveDouble& pPeak1, FbxTime& pPeakTime2, kFCurveDouble& pPeak2);

    /** Get period statistics for keys on this curve. If pAveragePeriod == pMinPeriod, the data is iso-sampled: the keys are spaced
	* evenly.
    *	\param pAveragePeriod Average key period (output).
    *	\param pMinPeriod Minimum period found (output).
    *	\param pMaxPeriod Maximum period found (output).
    */
    void KeyGetPeriods(FbxTime& pAveragePeriod, FbxTime& pMinPeriod, FbxTime& pMaxPeriod);

    //@}

    /**
    * \name Copy, Insert, Replace and Delete Functions
    */
    //@{

    /** Create a new animation curve and copy keys.
    *	\param pStart Beginning of time range (not used).
    *	\param pStop End of time range (not used).
    *	\return Created animation curve.
    *   \remarks All keys are always copied. To copy keys in a specific time range, use Replace().
    */
    KFCurve* Copy(FbxTime pStart = FBXSDK_TIME_MINUS_INFINITE, FbxTime pStop = FBXSDK_TIME_INFINITE);

    /** Clear the current animation curve's keys, and then copy source animation curve content into current animation curve.
    *	\param pSource Source animation curve.
    *	\param pWithKeys If \c true, copy
    * keys from source animation curve. If \c false, only the parameters specific to the animation curve (default value, extrapolation and color) are copied.
    */
    void CopyFrom(KFCurve& pSource, bool pWithKeys = true);

    /**	Replace keys within a range in current animation curve with keys found in a source animation curve for the same time range.
    * \param pSource Source animation curve.
    * \param	pStart Start of time range.
    * \param	pStop End of time range.
    * \param pUseExactGivenSpan If \c false, time of first and last keys is used (original behavior). If \c true, pStart and pStop are enforced.
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert.
    * \param pTimeSpanOffset Time offset to be added: Keys from pSource between pStart and pStop are copied to the 
	* current curve between pStart+pTimeSpanOffset and pStop+pTimeSpanOffset.
    */
    void Replace(KFCurve* pSource, FbxTime pStart = FBXSDK_TIME_MINUS_INFINITE, FbxTime pStop = FBXSDK_TIME_INFINITE, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, FbxTime pTimeSpanOffset = FBXSDK_TIME_ZERO );

    /**	Replace keys within a range in current animation curve with keys found in a source animation curve.
    * The copied keys have their value scaled with a factor varying 
    * linearly in time within the given time range.
    * \param pSource Source animation curve.
    * \param pStart Start of time range.
    * \param pStop End of time range.
    * \param pScaleStart Scale factor applied at start of time range. 
    * \param pScaleStop Scale factor applied at end of time range. 
    * \param pUseExactGivenSpan If \c false, time of first and last keys is used (original behavior). If \c true, pStart and pStop are enforced.
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert.
    * \param pTimeSpanOffset Time offset to be added: Keys from pSource between pStart and pStop are copied to the 
	* current curve between pStart+pTimeSpanOffset and pStop+pTimeSpanOffset.
    */
    void ReplaceForQuaternion(KFCurve* pSource, FbxTime pStart, FbxTime pStop, kFCurveDouble pScaleStart, kFCurveDouble pScaleStop, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, FbxTime pTimeSpanOffset = FBXSDK_TIME_ZERO );

    /**	Replace keys within a range in current animation curve with keys found in a source animation curve.
    * \param pSource Source animation curve.
    * \param pStart Start of time range.
    * \param pStop End of time range.
    * \param pAddFromStart Offset applied to copied key values within the time range.
    * \param pAddAfterStop Offset applied to key values after the time range.
    * \param pValueSubOffsetAfterStart If \c true, copied key values within 
	* the time range are subtracted from time offset specified by parameter
    * \c pAddFromStart. If \c false, copied key values within the time range are 
    * added to time offset specified by parameter \c pAddFromStart. 
    * \param pValueSubOffsetAfterStop If \c true, key values after 
	* the time range are subtracted from time offset specified by parameter
    * \c pAddAfterStop. If \c false, key values after the time range are 
    * added to time offset specified by parameter \c pAddAfterStop. 
    * \param pUseExactGivenSpan If \c false, time of first and last keys is used (original behavior). If \c true, pStart and pStop are enforced.
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert
    * \param pTimeSpanOffset Time offset to be added: Keys from pSource between pStart and pStop are copied to the 
	* current curve between pStart+pTimeSpanOffset and pStop+pTimeSpanOffset.
    */
    void ReplaceForEulerXYZ(KFCurve* pSource, FbxTime pStart, FbxTime pStop, kFCurveDouble pAddFromStart, kFCurveDouble pAddAfterStop, bool pValueSubOffsetAfterStart, bool pValueSubOffsetAfterStop, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, FbxTime pTimeSpanOffset = FBXSDK_TIME_ZERO );	

    /**	Insert all keys found in a source animation curve in current animation curve.
    * A time offset is added to copied keys so that the first copied key occurs 
    * at the given insertion time. Keys from the source animation curve are merged into 
    * the current animation curve. In other words, no existing key in the current function
    * curve is destroyed unless there is an overlap with a copied key.
    * \param pSource Source animation curve.
    * \param pInsertTime Insert time of the first key found in the source animation curve.
    * \param pFirstKeyLeftDerivative First key left derivative.
    * \param pFirstKeyIsWeighted  First key left weighted state (true if weighted).
    * \param pFirstKeyWeight First key left weight
    */

    void Insert(KFCurve* pSource, FbxTime pInsertTime, kFCurveDouble pFirstKeyLeftDerivative, bool pFirstKeyIsWeighted = false, kFCurveDouble pFirstKeyWeight = KFCURVE_DEFAULT_WEIGHT);

    /**	Insert all keys found in a source animation curve in current animation curve.
    * A time offset is added to copied keys so that the first copied key occurs 
    * at the given insertion time. Keys from the source animation curve are merged into 
    * the current animation curve. In other words, no existing key in the current function
    * curve is destroyed unless there is an overlap with a copied key.
    * \param pSource Source animation curve.
    * \param pInsertTime Insert time of the first key found in the source animation curve.
    * \param pFirstKeyLeftDerivative First key left derivative info.
    */
    void Insert(KFCurve* pSource, FbxTime pInsertTime, KFCurveTangeantInfo pFirstKeyLeftDerivative );

    /** Delete keys within an index range.
    * Index range is inclusive.
    * This function is much faster than multiple removes.
    *	\param pStartIndex Index of first deleted key.
    *	\param pStopIndex Index of last deleted key.
    *	\return \c true if the animation curve contains keys, \c false otherwise.
    * Result is undetermined if animation curve has keys but an 
    * index is out of bounds.
    */
    bool Delete(kFCurveIndex pStartIndex , kFCurveIndex pStopIndex);									

    /** Delete keys within a time range.
    * This function is much faster than multiple removes.
    *	\param pStart Start of time range.
    *	\param pStop End of time range.
  * \param pInclusive Time range includes the keys at pStart and pStop if true.
    *	\return \c true if the animation curve contains keys, \c false otherwise.
    */	
	bool Delete (FbxTime pStart = FBXSDK_TIME_MINUS_INFINITE, FbxTime pStop = FBXSDK_TIME_INFINITE, bool pInclusive = false);

    /** Extract all keys in the given selection span
    *	\param	pArray	    Array where to stored found keys.
    *	\param	pMinIndex	Index where to start the search (the key at this index is tested).
    *	\param	pMaxIndex	Index where to stop the search (the last index is the limit, the key at this index is not tested).
    *	\param	pMinValue	Minimal value to consider the key. Keys under that value are not extracted to the array.
    *	\param	pMaxValue	Maximal value to consider the key. Keys over that value are not extracted to the array.
    */
    void ExtractKeysIndex( FbxArray<int> &pArray, int pMinIndex, int pMaxIndex, double pMinValue =  -FBXSDK_DOUBLE_MAX, double pMaxValue =  FBXSDK_DOUBLE_MAX);

    //@}

    typedef enum {
        V8   = 4009,
        V7   = 4008,
        V71  = 4007,
        V6   = 4005,
        V5   = 4004
    } FbxStoreVersionID;

    bool	FbxStore (FbxIO* pFbx, bool pOnlyDefaults = false, bool pColor = true, FbxStoreVersionID pVersionID = V8);
    bool	FbxRetrieve (FbxIO* pFbx, bool pOnlyDefaults = false, bool pColor = false );
    bool	FbxInternalRetrieve (FbxIO* pFbx, bool pOnlyDefaults = false, bool pColor = false );

	void	FbxStorePriKeyAndAttrArrays(FbxIO* pFbx, FbxStoreVersionID pVersionID = V8);
	void	FbxRetrievePriKeyAndAttrArrays(FbxIO* pFbx, int pKeyVersion);
    void	FbxRetrievePrePostExtrapolation(FbxIO* pFbx);

    double CandidateEvaluate (FbxTime pTime, kFCurveIndex* pLast = NULL);
    bool CandidateClear ();
    bool CandidateSet (FbxTime pTime, double pValue);
    bool IsCandidate ();
    double CandidateGet ();
    FbxTime CandidateGetTime ();

    bool IsLocked() const;
    bool IsLockedByLayer() const;
    bool IsLockedByProperty() const;
    void SetLockedByLayer(bool pLocked);
    void SetLockedByProperty(bool pLocked);

    bool CandidateKey
        (
        kFCurveIndex	*pLast				= NULL, 
        int	pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
        int	pTanMode = KFCURVE_TANGEANT_USER, 
        int pContinuity = KFCURVE_CONTINUITY,
        bool			pTangeantOverride	= true,
        FbxTime			pCandidateTime		= FBXSDK_TIME_INFINITE,
        double			pKeyIndexTolerance  = 0.0
        );

    bool NormalsSeemsToComeFromAPlot();

    void SetWasData (int pType);
    int GetWasData () const;
    int GuessWasData (FbxTime* pStart = NULL, FbxTime* pStep = NULL);

    void KeyTangeantHide ();

    int GetUpdateId () const;
    int GetValuesUpdateId () const;

    void CallbackRegister (kFCurveCallback pCallback, void* pObject);
    void CallbackUnregister (kFCurveCallback pCallback, void* pObject);
    void CallbackEnable (bool pEnable);
    void CallbackClear ();

public:
	//! Automatically convert KFCURVE_INTERPOLATION_CUBIC type auto tangent key to Time-Independent.
	static const bool sConvertAutoTimeIndepedent;

	/** Function for faster data transfer between MotionBuilder and FBX SDK.
	*	As of 2009-10-29, MotionBuilder and Fbx (2011 - Turnpike) have the same internal data structure for 
	*   KFCurve, KPriFCurveKey, and KPriFCurveKeyAttr classes. CopyExternalPriKeyAndAttr takes advantage of this information
	*	to move data faster between MotionBuilder and FBX SDK. If there is any internal data structure change for those 
	*	classes, this function must be modified accordingly.
	* @param pSourceFCurveKeysList List of keys (KFCurveKey) to be copied
	* @param pSourceFCurveKeyCount Number of keys to be copied
	*/
	void CopyExternalPriKeyAndAttr(void** pSourceFCurveKeysList, int pSourceFCurveKeyCount); 

	KPriFCurveKey** GetPriFCurveKeysList() const { return mFCurveKeysList; }

private:
	void KeyAttrSet(kFCurveIndex pKeyIndex, const KPriFCurveKeyAttr& pKeyAttr);

	/** Separate key attribute at the given index.
	* Result is undetermined if animation curve has no key or if index
	* is out of bounds.
	*/
	void KeyAttrSeparate(kFCurveIndex pKeyIndex);
	
	/** Inline lightweight function to check if the key has separate attribute, if not
	 * then call KeyAttrSeparate()
	 */
	inline void KeyAttrSeparateCheck(kFCurveIndex pKeyIndex);

	/* Control optimization flag, when enable, we will perform KeyAttrShrink() operation
	 * when call KeyModifyEnd().
	 */ 
	void KeySetOptimizeEnable(bool pEnable); 
	void KeySetOptimizeThreshold(int pThreshold);

	/** Compress the keyAttr, let the key share the same instances of the attribute if 
	 * they have the same attribute value.
	 */
	void KeyAttrShrink(kFCurveIndex pStartIndex, kFCurveIndex pStopIndex);

    void IncrementUpdateId(int pInc);
    void CallbackAddEvent (int pWhat, int pIndexStart);

    int MapIndexAll (int pIndex, int &pWhere);
	void InitBuffers (int pKeyCount, bool pResetKeyCount = false );

    bool CheckCurve();

	//! Return true if the specified key is an auto clamp that is currently clamped
    void IsClamped( int pIndex, bool &pLeftClamped, bool &pRightClamped ) const;

public:
	/** Static method to allocate and initialize global variables
	  * used for KFCurveKey attribute management.
	  * Must be called after the FbxManager is initialized.
	  */
	static void AllocateGlobals();

	/** Static method to delete global variables
	  * used for KFCurveKey attribute management.
	  * Must be called when the last FbxManager is deleted.
	  */
	static void FreeGlobals();

public:
	static	KFCurveKeyAttrManager*	smGlobalKeyAttrMemoryPool;
	// Recording Memory global var
	static	FbxULong					smGlobalRecordingMemory;
	static	KMemoryBlockQueue*		smGlobalKeyBufferQueue;

private:

    float mColor[3];

    kFCurveDouble mValue;

    int mUpdateId;
	int mFlags;
	int mOptimizationThreshold;
    int mKeyModifyGuard;

	KPriFCurveKey** mFCurveKeysList;

    int mFCurveKeyCount;	
    int mFCurveKeySize;	
    int mFCurveLastBlockIndex;	


    FbxUInt mPreExtrapolation;
    FbxULong mPreExtrapolationCount;
    FbxUInt mPostExtrapolation;
    FbxULong mPostExtrapolationCount;

    int mWasType;

    kFCurveIndex mLastSearchIndex;

    FbxTime mCandidateTime;
    kFCurveDouble mCandidateValue;

    KFCurveEvent mEvent;
    FbxArray<FbxHandle> mCallbackFunctions;   // no delete on object must use array ul
    FbxArray<FbxHandle> mCallbackObjects;	   // no delete on object must use array ul

	inline KPriFCurveKey* InternalPriKeyGetPtr (kFCurveIndex pIndex) const;
    inline KPriFCurveKeyAttr* InternalPriKeyAttrGetPtr(kFCurveIndex pIndex) const;
};

// Allocate memory blocks for animation curve to give room for recording.
FBXSDK_DLL void KFCURVE_SetFCurveRecordMemoryBlockCount ( int pBlockCount );
FBXSDK_DLL int KFCURVE_GetFCurveMemoryBlockSize ( );
FBXSDK_DLL void KFCURVE_ClearMemoryBlockQueue ();

//
// class KFCurveEvent
//
inline void KFCurveEvent::Clear () 
{
    mType = KFCURVEEVENT_NONE;
    mKeyIndexStart = mKeyIndexStop=-1; 
    mEventCount = 0; 
}


inline void KFCurveEvent::Add (int pWhat, int pIndex) 
{		
    mType |= pWhat;
    mEventCount++;
    if ( (pIndex<mKeyIndexStart) || (mKeyIndexStart==-1)) 
    {
        mKeyIndexStart = pIndex;
    }
    if (pIndex>mKeyIndexStop) 
    {
        mKeyIndexStop = pIndex;
    }
}

//
//  class KFCurveKey
//
inline KFCurveTangeantInfo::KFCurveTangeantInfo()
{
    mDerivative = 0.0;
    mWeight     = KFCURVE_DEFAULT_WEIGHT;
    mWeighted   = false;
    mVelocity	= KFCURVE_DEFAULT_VELOCITY;
    mHasVelocity= false;
    mAuto		= 0.0;
}

inline KFCurveKey::KFCurveKey(const KPriFCurveKey& pKey, const KPriFCurveKeyAttr& pAttr)
{
	mTime = pKey.mTime;
	mValue = pKey.mValue;
	mFlags = pAttr.mFlags;
	mData[0] = pAttr.mData[0];
	mData[1] = pAttr.mData[1];
#ifdef KFCURVE_FLOAT
	mData[2] = pAttr.mData[2];
	mData[3] = pAttr.mData[3];
#else
	mWeight[0] = pAttr.mWeight[0];
	mWeight[1] = pAttr.mWeight[1];
	mVelocity[0] = pAttr.mVelocity[0];
	mVelocity[1] = pAttr.mVelocity[1];
#endif
}

inline KPriFCurveKeyAttr KFCurveKey::GetKeyAttr() const
{
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.mFlags = mFlags;
	lKeyAttr.mData[0] = mData[0];
	lKeyAttr.mData[1] = mData[1];
#ifdef KFCURVE_FLOAT
	lKeyAttr.mData[2] = mData[2];
	lKeyAttr.mData[3] = mData[3];
#else
	lKeyAttr.mWeight[0] = mWeight[0];
	lKeyAttr.mWeight[1] = mWeight[1];
	lKeyAttr.mVelocity[0] = mVelocity[0];
	lKeyAttr.mVelocity[1] = mVelocity[1];
#endif
	return lKeyAttr;
}

inline void KPriFCurveKeyAttr::Set 
(
	kFCurveInterpolation pInterpolation /* = KFCURVE_INTERPOLATION_CUBIC*/, 
	kFCurveTangeantMode pTangeantMode /*= KFCURVE_TANGEANT_AUTO*/, 
	kFCurveDouble pData0 /*= 0*/, 
	kFCurveDouble pData1 /*= 0*/,
	kFCurveTangeantWeightMode pTangeantWeightMode /*= KFCURVE_WEIGHT_NONE*/, 
	kFCurveDouble pWeight0 /* = KFCURVE_DEFAULT_WEIGHT */,
	kFCurveDouble pWeight1 /* = KFCURVE_DEFAULT_WEIGHT */,
	kFCurveDouble pVelocity0 /* = KFCURVE_DEFAULT_VELOCITY */,
	kFCurveDouble pVelocity1 /* = KFCURVE_DEFAULT_VELOCITY */
)
{
	FBX_ASSERT (pInterpolation != KFCURVE_INTERPOLATION_CUBIC || pTangeantMode != KFCURVE_TANGEANT_TCB);

	SetInterpolation (pInterpolation);
	SetTangeantMode (pTangeantMode);
	SetDataDouble (KFCURVEKEY_RIGHT_SLOPE, pData0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_SLOPE, pData1);

	SetTangeantWeightMode (pTangeantWeightMode);
	SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, pWeight0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, pWeight1);

	SetDataDouble (KFCURVEKEY_RIGHT_VELOCITY, pVelocity0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_VELOCITY, pVelocity1);

	SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);	
}

inline void KPriFCurveKey::Set 
(
	FbxTime pTime, 
	kFCurveDouble pValue
)
{
	SetTime (pTime);
	SetValue (pValue);
}

//
//  class KFCurveKey
//

inline void KFCurveKey::Set 
    (
    FbxTime pTime, 
    kFCurveDouble pValue, 
    kFCurveInterpolation pInterpolation /* = KFCURVE_INTERPOLATION_CUBIC*/, 
    kFCurveTangeantMode pTangeantMode /*= KFCURVE_TANGEANT_AUTO*/, 
    kFCurveDouble pData0 /*= 0*/, 
    kFCurveDouble pData1 /*= 0*/,
    kFCurveTangeantWeightMode pTangeantWeightMode /*= KFCURVE_WEIGHT_NONE*/, 
    kFCurveDouble pWeight0 /* = KFCURVE_DEFAULT_WEIGHT */,
    kFCurveDouble pWeight1 /* = KFCURVE_DEFAULT_WEIGHT */,
    kFCurveDouble pVelocity0 /* = KFCURVE_DEFAULT_VELOCITY */,
    kFCurveDouble pVelocity1 /* = KFCURVE_DEFAULT_VELOCITY */
    )
{
    FBX_ASSERT (pInterpolation != KFCURVE_INTERPOLATION_CUBIC || pTangeantMode != KFCURVE_TANGEANT_TCB);

    SetTime (pTime);
    SetValue (pValue);
    SetInterpolation (pInterpolation);
    SetTangeantMode (pTangeantMode);
    SetDataDouble (KFCURVEKEY_RIGHT_SLOPE, pData0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_SLOPE, pData1);

    SetTangeantWeightMode (pTangeantWeightMode);
    SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, pWeight0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, pWeight1);

    SetDataDouble (KFCURVEKEY_RIGHT_VELOCITY, pVelocity0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_VELOCITY, pVelocity1);

    SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}

inline void KPriFCurveKeyAttr::SetTCB (float pData1/*=0.0f*/, float pData2/*=0.0f*/, float pData3/*=0.0f*/)
{
	SetInterpolation (KFCURVE_INTERPOLATION_CUBIC);
	SetTangeantMode (KFCURVE_TANGEANT_TCB);
	SetDataFloat (KFCURVEKEY_TCB_TENSION, pData1);
	SetDataFloat (KFCURVEKEY_TCB_CONTINUITY, pData2);
	SetDataFloat (KFCURVEKEY_TCB_BIAS, pData3);
	SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}

inline void KFCurveKey::SetTCB (FbxTime pTime, kFCurveDouble pValue, float pData1/*=0.0f*/, float pData2/*=0.0f*/, float pData3/*=0.0f*/)
{
    SetTime (pTime);
    SetValue (pValue);
    SetInterpolation (KFCURVE_INTERPOLATION_CUBIC);
    SetTangeantMode (KFCURVE_TANGEANT_TCB);
    SetDataFloat (KFCURVEKEY_TCB_TENSION, pData1);
    SetDataFloat (KFCURVEKEY_TCB_CONTINUITY, pData2);
    SetDataFloat (KFCURVEKEY_TCB_BIAS, pData3);
    SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}


inline void KFCurveKey::Set (KFCurveKey& iSource)
{
	memcpy(this, &iSource, sizeof(KFCurveKey));
}

inline kFCurveInterpolation KPriFCurveKeyAttr::GetInterpolation() const
{
	return mFlags & KFCURVE_INTERPOLATION_ALL;
}

inline kFCurveInterpolation KFCurveKey::GetInterpolation () const
{
    return mFlags & KFCURVE_INTERPOLATION_ALL;
}


inline void KPriFCurveKeyAttr::SetInterpolation (kFCurveInterpolation pInterpolation)	
{
    FBX_ASSERT_MSG(	(pInterpolation == KFCURVE_INTERPOLATION_CUBIC) || 
        (pInterpolation == KFCURVE_INTERPOLATION_LINEAR) ||
        (pInterpolation == KFCURVE_INTERPOLATION_CONSTANT) ,"Wrong interpolation type." );

    if( (((mFlags & KFCURVE_INTERPOLATION_ALL)!=KFCURVE_INTERPOLATION_CUBIC)) && pInterpolation == KFCURVE_INTERPOLATION_CUBIC )
    {
        // Clear weighting information
        SetTangeantWeightMode( KFCURVE_WEIGHTED_NONE);
        SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);
        SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);

        SetTangeantVelocityMode(KFCURVE_VELOCITY_NONE);
        SetDataDouble( KFCURVEKEY_RIGHT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
        SetDataDouble( KFCURVEKEY_NEXT_LEFT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
    }

    mFlags = (mFlags & ~KFCURVE_INTERPOLATION_ALL) | (pInterpolation & KFCURVE_INTERPOLATION_ALL); 
}


inline void KFCurveKey::SetInterpolation (kFCurveInterpolation pInterpolation)	
{
	FBX_ASSERT_MSG(	(pInterpolation == KFCURVE_INTERPOLATION_CUBIC) || 
					(pInterpolation == KFCURVE_INTERPOLATION_LINEAR) ||
					(pInterpolation == KFCURVE_INTERPOLATION_CONSTANT) ,"Wrong interpolation type." );

	if( (((mFlags & KFCURVE_INTERPOLATION_ALL)!=KFCURVE_INTERPOLATION_CUBIC)) && pInterpolation == KFCURVE_INTERPOLATION_CUBIC )
	{
		// Clear weighting information
		SetTangeantWeightMode( KFCURVE_WEIGHTED_NONE);
		SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);
		SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);

		SetTangeantVelocityMode(KFCURVE_VELOCITY_NONE);
		SetDataDouble( KFCURVEKEY_RIGHT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
		SetDataDouble( KFCURVEKEY_NEXT_LEFT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
	}

	mFlags = (mFlags & ~KFCURVE_INTERPOLATION_ALL) | (pInterpolation & KFCURVE_INTERPOLATION_ALL); 
}

inline kFCurveConstantMode KPriFCurveKeyAttr::GetConstantMode() const
{
	return mFlags & KFCURVE_CONSTANT_ALL;
}

inline kFCurveConstantMode KFCurveKey::GetConstantMode() const
{
    return mFlags & KFCURVE_CONSTANT_ALL;
}

inline kFCurveTangeantMode KPriFCurveKeyAttr::GetTangeantMode( bool pIncludeOverrides ) const
{
    if( pIncludeOverrides )
    {
        return mFlags & KFCURVE_TANGEANT_ALL;
    }
    else
    {
        return mFlags & KFCURVE_TANGEANT_TYPE_MASK;
    }
}

inline kFCurveTangeantMode KFCurveKey::GetTangeantMode( bool pIncludeOverrides ) const
{
	if( pIncludeOverrides )
	{
		return mFlags & KFCURVE_TANGEANT_ALL;
	}
	else
	{
		return mFlags & KFCURVE_TANGEANT_TYPE_MASK;
	}
}

inline void KPriFCurveKeyAttr::SetConstantMode (kFCurveConstantMode pMode)			
{
    FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) ||
        (pMode == KFCURVE_CONSTANT_STANDARD) ||
        (pMode == KFCURVE_CONSTANT_NEXT),"Wrong constant mode.");

    mFlags = (mFlags & ~KFCURVE_CONSTANT_ALL) | (pMode & KFCURVE_CONSTANT_ALL); 
}

inline void KFCurveKey::SetConstantMode (kFCurveConstantMode pMode)			
{
	FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) ||
					(pMode == KFCURVE_CONSTANT_STANDARD) ||
					(pMode == KFCURVE_CONSTANT_NEXT),"Wrong constant mode.");

	mFlags = (mFlags & ~KFCURVE_CONSTANT_ALL) | (pMode & KFCURVE_CONSTANT_ALL); 
}

inline void KPriFCurveKeyAttr::SetTangeantMode (kFCurveTangeantMode pTangeant, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)			
{
	FBX_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) || !(pTangeant & ~KFCURVE_TANGEANT_ALL), "Wrong tangeant mode." );
	FBX_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) || !(pTangeant & ~KFCURVE_CONSTANT_ALL), "Wrong tangeant mode." );

	// Convert Auto to Time-Independent.
	if (! pIgnoreAutoTimeIndepedentConversion && KFCurve::sConvertAutoTimeIndepedent && (mFlags & KFCURVE_INTERPOLATION_CUBIC) && (pTangeant & KFCURVE_TANGEANT_AUTO))
	{
		pTangeant = pTangeant | KFCURVE_GENERIC_TIME_INDEPENDENT;
	}

	mFlags = (mFlags & ~(KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL)) | (pTangeant & (KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL) ); 
}

inline void KFCurveKey::SetTangeantMode (kFCurveTangeantMode pTangeant, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)			
{
	FBX_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) || !(pTangeant & ~KFCURVE_TANGEANT_ALL), "Wrong tangeant mode." );
	FBX_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) || !(pTangeant & ~KFCURVE_CONSTANT_ALL), "Wrong tangeant mode." );

	// Convert Auto to Time-Independent.
	if (! pIgnoreAutoTimeIndepedentConversion && KFCurve::sConvertAutoTimeIndepedent && (mFlags & KFCURVE_INTERPOLATION_CUBIC) && (pTangeant & KFCURVE_TANGEANT_AUTO))
	{
		pTangeant = pTangeant | KFCURVE_GENERIC_TIME_INDEPENDENT;
	}

    mFlags = (mFlags & ~(KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL)) | (pTangeant & (KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL) ); 
}

inline kFCurveTangeantWeightMode KPriFCurveKeyAttr::GetTangeantWeightMode() const
{
    return mFlags & KFCURVE_WEIGHTED_ALL;
}

inline kFCurveTangeantWeightMode KFCurveKey::GetTangeantWeightMode() const
{
	return mFlags & KFCURVE_WEIGHTED_ALL;
}

inline void KPriFCurveKeyAttr::SetTangeantWeightMode(kFCurveTangeantWeightMode pTangent, kFCurveTangeantWeightMode pMask /* KFCURVE_WEIGHTED_ALL */ )
{
    pMask &= KFCURVE_WEIGHTED_ALL;
    mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

inline void KFCurveKey::SetTangeantWeightMode(kFCurveTangeantWeightMode pTangent, kFCurveTangeantWeightMode pMask /* KFCURVE_WEIGHTED_ALL */ )
{

	pMask &= KFCURVE_WEIGHTED_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

inline kFCurveTangeantVelocityMode KPriFCurveKeyAttr::GetTangeantVelocityMode() const
{
	return mFlags & KFCURVE_VELOCITY_ALL;
}

inline kFCurveTangeantVelocityMode KFCurveKey::GetTangeantVelocityMode() const
{
	return mFlags & KFCURVE_VELOCITY_ALL;
}

inline void KPriFCurveKeyAttr::SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight ) 
{
#ifdef KFCURVE_FLOAT
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData);
#else
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData, mWeight);
#endif
}

inline void KFCurveKey::SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight ) 
{
#ifdef KFCURVE_FLOAT
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData);
#else
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData, mWeight);
#endif
}

inline void KPriFCurveKeyAttr::SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangent, kFCurveTangeantVelocityMode pMask /* KFCURVE_VELOCITY_ALL */ )
{
	pMask &= KFCURVE_VELOCITY_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

inline void KFCurveKey::SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangent, kFCurveTangeantVelocityMode pMask /* KFCURVE_VELOCITY_ALL */ )
{
	pMask &= KFCURVE_VELOCITY_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

inline void KPriFCurveKeyAttr::SetTangeantVisibility (kFCurveTangeantVisibility pVisibility)				
{
	FBX_ASSERT_MSG(	(pVisibility == KFCURVE_TANGEANT_SHOW_NONE) || 
		(pVisibility == KFCURVE_TANGEANT_SHOW_LEFT) ||
		(pVisibility == KFCURVE_TANGEANT_SHOW_RIGHT) ||
		(pVisibility == KFCURVE_TANGEANT_SHOW_BOTH) ,"Wrong visibility type." );
   
	mFlags = (mFlags & ~KFCURVE_TANGEANT_SHOW_BOTH) | (pVisibility & KFCURVE_TANGEANT_SHOW_BOTH); 
}

inline void KFCurveKey::SetTangeantVisibility (kFCurveTangeantVisibility pVisibility)				
{
    FBX_ASSERT_MSG(	(pVisibility == KFCURVE_TANGEANT_SHOW_NONE) || 
        (pVisibility == KFCURVE_TANGEANT_SHOW_LEFT) ||
        (pVisibility == KFCURVE_TANGEANT_SHOW_RIGHT) ||
        (pVisibility == KFCURVE_TANGEANT_SHOW_BOTH) ,"Wrong visibility type." );

    mFlags = (mFlags & ~KFCURVE_TANGEANT_SHOW_BOTH) | (pVisibility & KFCURVE_TANGEANT_SHOW_BOTH); 
}

inline kFCurveTangeantVisibility KPriFCurveKeyAttr::GetTangeantVisibility ()  const
{
	return mFlags & KFCURVE_TANGEANT_SHOW_BOTH;
}

inline kFCurveTangeantVisibility KFCurveKey::GetTangeantVisibility () const
{
    return mFlags & KFCURVE_TANGEANT_SHOW_BOTH;
}

inline kFCurveDouble KPriFCurveKeyAttr::GetDataDouble (EKFCurveDataIndex pIndex)  const
{
	if( pIndex < KFCURVEKEY_WEIGHTS )
	{
		return mData[pIndex];
	}
	else
	{
		#ifdef KFCURVE_FLOAT
			return (kFCurveDouble)(((FbxInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS])/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
		#else		
			return (kFCurveDouble)mWeight[pIndex-KFCURVEKEY_WEIGHTS]/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
		#endif
	}
}

inline kFCurveDouble KFCurveKey::GetDataDouble (EKFCurveDataIndex pIndex) const
{
    if( pIndex < KFCURVEKEY_WEIGHTS )
    {
        return mData[pIndex];
    }
    else
    {
        #ifdef KFCURVE_FLOAT
            return (kFCurveDouble)(((FbxInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS])/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
        #else		
            return (kFCurveDouble)mWeight[pIndex-KFCURVEKEY_WEIGHTS]/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
        #endif
    }
}

inline void KPriFCurveKeyAttr::SetDataDouble (EKFCurveDataIndex pIndex, kFCurveDouble pValue) 
{
	if( pIndex < KFCURVEKEY_RIGHT_WEIGHT )
	{
		mData[pIndex] = pValue;
	}
	else
	{
		if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue > KFCURVE_MAX_WEIGHT )
		{
			pValue = KFCURVE_MAX_WEIGHT;
		}
		else if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue < KFCURVE_MIN_WEIGHT )
		{
			pValue = KFCURVE_MIN_WEIGHT;
		}

		#ifdef KFCURVE_FLOAT
			(((FbxInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS]) = (FbxInt16)(pValue*KFCURVE_WEIGHT_DIVIDER);
		#else		
			mWeight[pIndex-KFCURVEKEY_WEIGHTS] = pValue*KFCURVE_WEIGHT_DIVIDER;
		#endif
	}
}

inline void KFCurveKey::SetDataDouble (EKFCurveDataIndex pIndex, kFCurveDouble pValue) 
{
    if( pIndex < KFCURVEKEY_RIGHT_WEIGHT )
    {
        mData[pIndex] = pValue;
    }
    else
    {
        if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue > KFCURVE_MAX_WEIGHT )
        {
            pValue = KFCURVE_MAX_WEIGHT;
        }
        else if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue < KFCURVE_MIN_WEIGHT )
        {
            pValue = KFCURVE_MIN_WEIGHT;
        }

        #ifdef KFCURVE_FLOAT
            (((FbxInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS]) = (FbxInt16)(pValue*KFCURVE_WEIGHT_DIVIDER);
        #else		
            mWeight[pIndex-KFCURVEKEY_WEIGHTS] = pValue*KFCURVE_WEIGHT_DIVIDER;
        #endif
    }
}

inline float KPriFCurveKeyAttr::GetDataFloat (EKFCurveDataIndex pIndex)  const
{
	return ( (float *)&mData[0])[pIndex];
}

inline float KFCurveKey::GetDataFloat (EKFCurveDataIndex pIndex)  const
{
    return ( (float *)&mData[0])[pIndex];
}

inline void KPriFCurveKeyAttr::SetDataFloat (EKFCurveDataIndex pIndex, float pValue) 
{
	((float *)&mData[0])[pIndex] = pValue;
}

inline void KFCurveKey::SetDataFloat (EKFCurveDataIndex pIndex, float pValue) 
{
    ((float *)&mData[0])[pIndex] = pValue;
}

inline float* KPriFCurveKeyAttr::GetDataPtr() const
{
    return (float*)mData;
}

inline float* KFCurveKey::GetDataPtr() const
{
	return (float*)mData;
}

inline kFCurveDouble KPriFCurveKey::GetValue ()  const
{
    return mValue;
}

inline kFCurveDouble KFCurveKey::GetValue ()  const
{
	return mValue;
}


inline void KPriFCurveKey::SetValue (kFCurveDouble pValue) 
{
    mValue=pValue;
}

inline void KFCurveKey::SetValue (kFCurveDouble pValue) 
{
	mValue=pValue;
}

inline void KPriFCurveKey::IncValue (kFCurveDouble pValue) 
{
	mValue+=pValue;
}

inline void KFCurveKey::IncValue (kFCurveDouble pValue) 
{
    mValue+=pValue;
}

inline void KPriFCurveKey::MultValue (kFCurveDouble pValue) 
{
    mValue*=pValue;
}

inline void KFCurveKey::MultValue (kFCurveDouble pValue) 
{
	mValue*=pValue;
}

inline FbxTime KPriFCurveKey::GetTime ()  const
{
	return mTime;
}

inline FbxTime KFCurveKey::GetTime () const
{
    return mTime;
}

inline void KPriFCurveKey::SetTime (FbxTime pTime) 
{
	FBX_ASSERT_MSG( pTime != FBXSDK_TIME_MINUS_INFINITE && 
	pTime != FBXSDK_TIME_INFINITE, "Key at infinite!" );

	mTime=pTime;
}

inline void KFCurveKey::SetTime (FbxTime pTime) 
{
    FBX_ASSERT_MSG( pTime != FBXSDK_TIME_MINUS_INFINITE && 
        pTime != FBXSDK_TIME_INFINITE, "Key at infinite!" );

    mTime=pTime;
}

inline void KPriFCurveKey::IncTime (FbxTime pTime) 
{
	mTime+=pTime;
}

inline void KFCurveKey::IncTime (FbxTime pTime) 
{
    mTime+=pTime;
}


inline void KPriFCurveKeyAttr::SetSelected (bool pSelected) 
{
    mFlags = pSelected ? (mFlags & ~KFCURVE_SELECT_ALL) | KFCURVE_SELECT_POINT : (mFlags & ~KFCURVE_SELECT_ALL);
}

inline void KFCurveKey::SetSelected (bool pSelected) 
{
	mFlags = pSelected ? (mFlags & ~KFCURVE_SELECT_ALL) | KFCURVE_SELECT_POINT : (mFlags & ~KFCURVE_SELECT_ALL);
}

inline bool KPriFCurveKeyAttr::GetSelected () const
{
    return (mFlags & KFCURVE_SELECT_POINT) ? true : false;
}

inline bool KFCurveKey::GetSelected () const
{
	return (mFlags & KFCURVE_SELECT_POINT) ? true : false;
}

inline void KPriFCurveKeyAttr::SetMarkedForManipulation (bool pSelected) 
{
    mFlags = pSelected ? (mFlags & ~KFCURVE_MARKED_ALL) | KFCURVE_MARKED_FOR_MANIP : (mFlags & ~KFCURVE_MARKED_ALL);
}

inline void KFCurveKey::SetMarkedForManipulation (bool pSelected) 
{
	mFlags = pSelected ? (mFlags & ~KFCURVE_MARKED_ALL) | KFCURVE_MARKED_FOR_MANIP : (mFlags & ~KFCURVE_MARKED_ALL);
}

inline bool KPriFCurveKeyAttr::GetMarkedForManipulation () const
{
	return (mFlags & KFCURVE_MARKED_FOR_MANIP) ? true : false;
}

inline bool KFCurveKey::GetMarkedForManipulation () const
{
    return (mFlags & KFCURVE_MARKED_FOR_MANIP) ? true : false;
}

inline void KPriFCurveKey::Init()
{
    mValue = 0.0;
    mTime = FBXSDK_TIME_ZERO;
	mAttr = NULL;
}

inline void KFCurveKey::Init()
{
    mValue = 0.0;
    mTime = FBXSDK_TIME_ZERO;
    mFlags = 0;
}

inline void KPriFCurveKeyAttr::SetBreak(bool pVal)
{
	FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
		(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
		(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
		(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
		(GetTangeantMode() == KFCURVE_TANGEANT_USER) ,"Wrong tangeant mode." );

	if(pVal)
		mFlags = mFlags |  KFCURVE_GENERIC_BREAK ;
	else
		mFlags = mFlags & ~KFCURVE_GENERIC_BREAK ;	

} 

inline void KFCurveKey::SetBreak(bool pVal)
{
    FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
        (GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
        (GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
        (GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
        (GetTangeantMode() == KFCURVE_TANGEANT_USER) ,"Wrong tangent mode." );

    if(pVal)
        mFlags = mFlags |  KFCURVE_GENERIC_BREAK ;
    else
        mFlags = mFlags & ~KFCURVE_GENERIC_BREAK ;	

} 

inline bool KPriFCurveKeyAttr::GetBreak() const
{
	FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
			(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_USER)  ,"Wrong tangent mode." );

    if( ((mFlags & KFCURVE_GENERIC_BREAK ) == KFCURVE_GENERIC_BREAK))
        return true;
    else
        return false; 

}

inline bool KFCurveKey::GetBreak() const
{
	FBX_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
			(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_USER)  ,"Wrong tangent mode." );

	if( ((mFlags & KFCURVE_GENERIC_BREAK ) == KFCURVE_GENERIC_BREAK))
		return true;
	else
		return false; 

}

inline bool KPriFCurveKeyAttr::IsEqual(const KPriFCurveKeyAttr& pRsh) const
{
	// To Modify, don't need to check the data for some Flags. 
	return (this == &pRsh) ||
       (mFlags == pRsh.mFlags &&
		mData[0] == pRsh.mData[0] &&
		mData[1] == pRsh.mData[1] &&
	#ifdef KFCURVE_FLOAT
		mData[2] == pRsh.mData[2] &&
	    mData[3] == pRsh.mData[3]);
	#else
		mWeight[0] == pRsh.mWeight[0] &&
		mWeight[1] == pRsh.mWeight[1] &&
		mVelocity[0] == pRsh.mVelocity[0] &&
        mVelocity[1] == pRsh.mVelocity[1]);
	#endif
}

inline void KPriFCurveKeyAttr::IncRefCount()
{
	++mRefCount;
}

inline void KPriFCurveKeyAttr::DecRefCount()
{
	--mRefCount;
}

inline FbxUInt32 KPriFCurveKeyAttr::GetRefCount() const
{
	return mRefCount;
}
//****************************************************************************************
// class KFCurve
//****************************************************************************************

inline kFCurveDouble KFCurve::GetValue () const 
{
    return mValue;
}

inline void KFCurve::SetPreExtrapolation (FbxUInt pExtrapolation) 
{
    FBX_ASSERT_MSG(	(pExtrapolation == KFCURVE_EXTRAPOLATION_CONST) || 
        (pExtrapolation == KFCURVE_EXTRAPOLATION_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_MIRROR_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_KEEP_SLOPE) ,"Wrong extrapolation type." );

    mPreExtrapolation = pExtrapolation; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}

inline FbxUInt KFCurve::GetPreExtrapolation () const 
{
    return mPreExtrapolation;
}


inline void KFCurve::SetPreExtrapolationCount (FbxULong pCount) 
{
    mPreExtrapolationCount = pCount; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}


inline FbxULong KFCurve::GetPreExtrapolationCount ()  const
{
    return mPreExtrapolationCount;
}

inline void KFCurve::SetPostExtrapolation (FbxUInt pExtrapolation) 
{
    FBX_ASSERT_MSG(	(pExtrapolation == KFCURVE_EXTRAPOLATION_CONST) || 
        (pExtrapolation == KFCURVE_EXTRAPOLATION_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_MIRROR_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_RELATIVE_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_KEEP_SLOPE) ,"Wrong extrapolation type." );

    mPostExtrapolation = pExtrapolation; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}

inline FbxUInt KFCurve::GetPostExtrapolation () const 
{
    return mPostExtrapolation;
}


inline void KFCurve::SetPostExtrapolationCount (FbxULong pCount) 
{
    mPostExtrapolationCount = pCount; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}


inline FbxULong KFCurve::GetPostExtrapolationCount ()  const
{
    return mPostExtrapolationCount;
}

inline KPriFCurveKey* KFCurve::InternalPriKeyGetPtr (int pIndex) const
{
    FBX_ASSERT_MSG( pIndex >= 0, "Negative indexes are not recommended." );
    FBX_ASSERT_MSG( mFCurveKeysList && mFCurveKeysList[pIndex / KEY_BLOCK_COUNT], "Accessing unallocated buffer." );

    return mFCurveKeysList[pIndex / KEY_BLOCK_COUNT] + (pIndex % KEY_BLOCK_COUNT);
}


inline KPriFCurveKeyAttr* KFCurve::InternalPriKeyAttrGetPtr(kFCurveIndex pIndex) const
{
	#ifdef _DEBUG
		KPriFCurveKey* lKey = InternalPriKeyGetPtr(pIndex);
		FBX_ASSERT_MSG(lKey->mAttr != NULL, "Accessing uninitialized keyattr.");
		return lKey->mAttr;
	#else
		return InternalPriKeyGetPtr(pIndex)->mAttr;
	#endif
}

/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/
inline void KFCurve::KeySet 
    (
    kFCurveIndex pKeyIndex,
    FbxTime pTime, 
    kFCurveDouble pValue, 
    kFCurveInterpolation pInterpolation, 
    kFCurveTangeantMode pTangentMode, 
    kFCurveDouble pRightSlope, 
    kFCurveDouble pNextLeftSlope, 
    kFCurveTangeantWeightMode pTangentWeightMode, 
    kFCurveDouble pWeight0, 
    kFCurveDouble pWeight1, 
    kFCurveDouble pVelocity0, 
    kFCurveDouble pVelocity1
    )
{
	KPriFCurveKey *lPriKey = InternalPriKeyGetPtr(pKeyIndex);
	lPriKey->Set(pTime, pValue);
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.mFlags = 0;
    if (lPriKey->mAttr)
        lKeyAttr.mFlags = lPriKey->mAttr->mFlags;
	lKeyAttr.Set( pInterpolation, pTangentMode, pRightSlope, pNextLeftSlope, pTangentWeightMode, pWeight0, pWeight1, pVelocity0, pVelocity1);

	KeyAttrSet(pKeyIndex, lKeyAttr);
}

inline void KFCurve::KeySetTCB 
    (
    kFCurveIndex pKeyIndex,
    FbxTime pTime, 
    kFCurveDouble pValue, 
    float pData0, 
    float pData1, 
    float pData2
    )
{
	InternalPriKeyGetPtr(pKeyIndex)->Set(pTime, pValue);
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.SetTCB(pData0, pData1, pData2);

	KeyAttrSet(pKeyIndex, lKeyAttr);
}

inline kFCurveInterpolation KFCurve::KeyGetInterpolation(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetInterpolation();
}

inline void KFCurve::KeySetInterpolation(kFCurveIndex pKeyIndex, kFCurveInterpolation pInterpolation)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
	if (lKey->mAttr)
	{
        if ( lKey->mAttr->GetInterpolation() != pInterpolation)
        {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetInterpolation(pInterpolation);
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline kFCurveConstantMode KFCurve::KeyGetConstantMode(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetConstantMode();
}

inline kFCurveTangeantMode KFCurve::KeyGetTangeantMode(kFCurveIndex pKeyIndex, bool pIncludeOverrides ) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantMode( pIncludeOverrides );
}

inline kFCurveTangeantWeightMode KFCurve::KeyGetTangeantWeightMode(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantWeightMode();
}

inline kFCurveTangeantVelocityMode KFCurve::KeyGetTangeantVelocityMode(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantVelocityMode();
}

inline void KFCurve::KeySetConstantMode(kFCurveIndex pKeyIndex, kFCurveConstantMode pMode)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
	if (lKey->mAttr)
    {
        if (lKey->mAttr->GetConstantMode() != pMode)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetConstantMode(pMode);
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline void KFCurve::KeySetTangeantMode(kFCurveIndex pKeyIndex, kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
        FbxUInt32 lFlags = lKey->mAttr->mFlags;
    	lKey->mAttr->SetTangeantMode(pTangent, pIgnoreAutoTimeIndepedentConversion); //only affect mFlags

	    if (lKey->mAttr->mFlags != lFlags)
	    {
		    if (lKey->mAttr->GetRefCount() > 1)
		    {
			    FbxUInt32 lSwapFlags = lKey->mAttr->mFlags;
			    lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
			    KeyAttrSeparate(pKeyIndex);
			    lKey->mAttr->mFlags = lSwapFlags;
		    }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline void KFCurve::KeySetTangeantWeightMode(kFCurveIndex pKeyIndex, kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    FbxUInt32 lFlags = lKey->mAttr->mFlags;
	    lKey->mAttr->SetTangeantWeightMode(pTangentWeightMode, pMask); //only affect mFlags
	    if (lKey->mAttr->mFlags != lFlags)
	    {
	       if (lKey->mAttr->GetRefCount() > 1)
	       {
		      FbxUInt32 lSwapFlags = lKey->mAttr->mFlags;
		      lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
		      KeyAttrSeparate(pKeyIndex);
		      lKey->mAttr->mFlags = lSwapFlags;
	       }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline void KFCurve::KeySetTangeantVelocityMode(kFCurveIndex pKeyIndex, kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    FbxUInt32 lFlags = lKey->mAttr->mFlags;
	    lKey->mAttr->SetTangeantVelocityMode(pTangentVelocityMode, pMask); //only affect mFlags
	    if (lKey->mAttr->mFlags != lFlags)
	    {
	       if (lKey->mAttr->GetRefCount() > 1)
	       {
		      FbxUInt32 lSwapFlags = lKey->mAttr->mFlags;
		      lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
		      KeyAttrSeparate(pKeyIndex);
		      lKey->mAttr->mFlags = lSwapFlags;
	       }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline kFCurveDouble KFCurve::KeyGetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataDouble(pIndex);
}

inline void KFCurve::KeySetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, kFCurveDouble pValue)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetDataDouble(pIndex) != pValue)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetDataDouble(pIndex, pValue);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline float KFCurve::KeyGetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataFloat(pIndex);
}

inline void KFCurve::KeySetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, float pValue)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetDataFloat(pIndex) != pValue)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetDataFloat(pIndex, pValue);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline const float* KFCurve::KeyGetDataPtr(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataPtr();
}

inline kFCurveDouble KFCurve::KeyGetValue(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyGetPtr(pKeyIndex)->GetValue();
}

inline void KFCurve::KeySetValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
	InternalPriKeyGetPtr(pKeyIndex)->SetValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

inline void KFCurve::KeyIncValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->IncValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

inline void KFCurve::KeyMultValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->MultValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

inline void KFCurve::KeyMultTangeant(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	if (pValue == 1.0)
	{
       return;
	}
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex); FBX_ASSERT(lKey->mAttr != NULL);
    KPriFCurveKey* lKeyNext = NULL;
    if (pKeyIndex < KeyGetCount()-1)
    {
        lKeyNext = InternalPriKeyGetPtr(pKeyIndex+1); 
        FBX_ASSERT(lKeyNext->mAttr != NULL);
    }

    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetInterpolation() == KFCURVE_INTERPOLATION_CUBIC)
	    {
            bool lScaleNextLeft = false;
		    switch (lKey->mAttr->GetTangeantMode())
		    {					
		    case KFCURVE_TANGEANT_USER:
		    case KFCURVE_TANGEANT_BREAK:
                lScaleNextLeft = true;
			    KeyAttrSeparateCheck(pKeyIndex);						
			    lKey->mAttr->SetDataDouble(KFCURVEKEY_RIGHT_SLOPE, lKey->mAttr->GetDataDouble(KFCURVEKEY_RIGHT_SLOPE) * pValue);

            case KFCURVE_TANGEANT_AUTO:
		    case KFCURVE_TANGEANT_AUTO_BREAK:
                if (lKeyNext)
                {
                    switch (lKeyNext->mAttr->GetTangeantMode())
                    {
                    case KFCURVE_TANGEANT_USER:
                    case KFCURVE_TANGEANT_BREAK:                    
                        lScaleNextLeft = true;
                    }
                }

                if (lScaleNextLeft)
                {
                    lKey->mAttr->SetDataDouble(KFCURVEKEY_NEXT_LEFT_SLOPE, lKey->mAttr->GetDataDouble(KFCURVEKEY_NEXT_LEFT_SLOPE) * pValue);
			        CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
                }
			    break;

		    case KFCURVE_TANGEANT_TCB:
			    // dunno how to handle this
		    default:
			    // nothing to do
			    break;
		    }
	    }
    }
}

inline FbxTime KFCurve::KeyGetTime(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyGetPtr(pKeyIndex)->GetTime();
}

inline void KFCurve::KeySetTime(kFCurveIndex pKeyIndex, FbxTime pTime)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->SetTime(pTime);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITTIME, pKeyIndex);
}

inline void KFCurve::KeyIncTime(kFCurveIndex pKeyIndex, FbxTime pTime)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->IncTime(pTime);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITTIME, pKeyIndex);
}

inline void KFCurve::KeySetSelected(kFCurveIndex pKeyIndex, bool pSelected)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetSelected() != pSelected)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetSelected(pSelected);
		    CallbackAddEvent(KFCURVEEVENT_SELECTION, pKeyIndex);
	    }
    }
}

inline bool KFCurve::KeyGetSelected(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetSelected();
}

inline void KFCurve::KeySetMarkedForManipulation(kFCurveIndex pKeyIndex, bool pMarked)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetMarkedForManipulation() != pMarked)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetMarkedForManipulation(pMarked);
	    }
    }
}

inline bool KFCurve::KeyGetMarkedForManipulation(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetMarkedForManipulation();
}

inline void	KFCurve::KeySetTangeantVisibility (kFCurveIndex pKeyIndex, kFCurveTangeantVisibility pVisibility)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);	
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetTangeantVisibility() != pVisibility)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetTangeantVisibility(pVisibility);
		    CallbackAddEvent(KFCURVEEVENT_SELECTION, pKeyIndex);
	    }
    }
}

inline kFCurveTangeantVisibility KFCurve::KeyGetTangeantVisibility (kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

    return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantVisibility();
}

inline void KFCurve::KeySetBreak(kFCurveIndex pKeyIndex, bool pVal)
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    FBX_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {	
        if (lKey->mAttr->GetBreak() != pVal)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetBreak(pVal);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

inline bool KFCurve::KeyGetBreak(kFCurveIndex pKeyIndex) const
{
    FBX_ASSERT(pKeyIndex >= 0);
    FBX_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetBreak();
}

inline void KFCurve::KeyAttrSeparateCheck(kFCurveIndex pKeyIndex)
{
	KPriFCurveKeyAttr* lCurKeyAttr = InternalPriKeyAttrGetPtr(pKeyIndex);
	if (! lCurKeyAttr || lCurKeyAttr->GetRefCount() > 1 )
		KeyAttrSeparate(pKeyIndex);
}


/**	Create an animation curve.
*/
FBXSDK_DLL KFCurve* KFCurveCreate();

// Create an animation curve, FBX SDK internal use only.
FBXSDK_DLL KFCurve* KFCurveCreate(FbxIO* pFbx, bool pOnlyDefaults = false, bool pColor = false);

// Create an animation curve, FBX SDK internal use only.
FBXSDK_DLL KFCurve* KFCurveCreate(FbxIO* pFbx, KFCurve* pCurve, bool pOnlyDefaults = false, bool pColor = false);

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_ANIMATION_KFCURVE_H_ */
