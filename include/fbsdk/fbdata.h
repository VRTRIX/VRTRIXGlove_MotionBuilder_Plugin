#ifndef __FBDATA_H__
#define __FBDATA_H__
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

/**	\file fbdata.h
*	Animation data types.
*	This file contains the definitions for various animation data
*	types in the Open Reality SDK.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
    /** \def FBSDK_DLL
    *	Be sure that FBSDK_DLL is defined only once...
    */
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#include <fbxsdk/fbxsdk_nsbegin.h>
	class FbxAnimCurveNode;
	class FbxScene;
	class FbxAnimStack;
	class FbxProperty;
	class FbxObject;
#include <fbxsdk/fbxsdk_nsend.h>

//@{
//! Animation node data types.
// Basic types
#define ANIMATIONNODE_TYPE_NUMBER               "Number"
#define ANIMATIONNODE_TYPE_TIME                 "Time"
#define ANIMATIONNODE_TYPE_TIMECODE             "TimeCode"
#define ANIMATIONNODE_TYPE_VECTOR               "Vector"
#define ANIMATIONNODE_TYPE_VECTOR_4             "Vector4"
#define ANIMATIONNODE_TYPE_OBJECT               "Object"
#define ANIMATIONNODE_TYPE_REFERENCE            "Reference"
#define ANIMATIONNODE_TYPE_EVENT				"Event"
#define ANIMATIONNODE_TYPE_STRING				"String"

// Types which are numbers
#define ANIMATIONNODE_TYPE_ACTION               "Action"
#define ANIMATIONNODE_TYPE_BOOL                 "Bool"
#define ANIMATIONNODE_TYPE_ENUM                 "Enum"
#define ANIMATIONNODE_TYPE_INTEGER              "Integer"
#define ANIMATIONNODE_TYPE_OCCLUSION            "Occlusion"
#define ANIMATIONNODE_TYPE_FIELDOFVIEWX         "FieldOfViewX"
#define ANIMATIONNODE_TYPE_FIELDOFVIEWY         "FieldOfViewY"
#define ANIMATIONNODE_TYPE_OPTICALCENTERX       "OpticalCenterX"
#define ANIMATIONNODE_TYPE_OPTICALCENTERY       "OpticalCenterY"
#define ANIMATIONNODE_TYPE_IKREACHTRANSLATION	"IK Reach Translation"
#define ANIMATIONNODE_TYPE_IKREACHROTATION		"IK Reach Rotation"

// Types which are vectors (3 members)
#define ANIMATIONNODE_TYPE_COLOR                "Color"
#define ANIMATIONNODE_TYPE_LOCAL_TRANSLATION    "Lcl Translation"
#define ANIMATIONNODE_TYPE_LOCAL_ROTATION       "Lcl Rotation"
#define ANIMATIONNODE_TYPE_LOCAL_SCALING        "Lcl Scaling"
#define ANIMATIONNODE_TYPE_TRANSLATION          "Translation"
#define ANIMATIONNODE_TYPE_ROTATION             "Rotation"
#define ANIMATIONNODE_TYPE_SCALING              "Scaling"

// Types which are vectors (4 members)
#define ANIMATIONNODE_TYPE_COLOR_RGBA           "ColorAndAlpha"

//@}

class KFCurve;

#include <fbxsdk/fbxsdk_nsbegin.h>
	class FbxAnimCurve;
#include <fbxsdk/fbxsdk_nsend.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    FB_FORWARD( FBEvaluateInfo );
    FB_FORWARD( FBPlotOptions );

    //! Types of interpolation for an FCurve.
    enum FBInterpolation	{	
        kFBInterpolationInvalid  = -1, 	//!< Invalid interpolation.
        kFBInterpolationConstant = 0,  	//!< Constant interpolation.
        kFBInterpolationLinear,			//!< Linear interpolation.
        kFBInterpolationCubic,		   	//!< Cubic interpolation.
		kFBInterpolationCustom,		   	//!< Custom interpolation.
        kFBInterpolationCount		   	//!< Number of interpolation types.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, Interpolation ); 

    //! Types of interpolator for an FCurve.
    enum FBInterpolatorCurveType {
        kFBInterpolatorCurveLinearIn, 
        kFBInterpolatorCurveLinearOut, 
        kFBInterpolatorCurveSmoothIn, 
        kFBInterpolatorCurveSmoothOut, 
        kFBInterpolatorCurveSlowIn, 
        kFBInterpolatorCurveSlowOut, 
        kFBInterpolatorCurveFastIn, 
        kFBInterpolatorCurveFastOut, 
        kFBInterpolatorCurveLast 
    };

    /** Methods of tangent calculation.
    *	This is only relevant when interpolation is CUBIC.
    */
    enum FBTangentMode	{
        kFBTangentModeAuto,		        //!< This is the equivalent to a cardinal spline with no parametrization. In the UI, it is identified as Smooth.
        kFBTangentModeTCB,		        //!< TCB spline (3 parameters: TENSION, CONTINUITY, BIAS)
        kFBTangentModeUser,		        //!< Used to represent all splines with no lost data (HERMITE, BEZIER, CATMUL, etc.) 
        kFBTangentModeBreak,		    //!< Like USER but left slope may differ from right.
        kFBTangentModeTimeIndependent,  //!< Time independent, is calculated based upon the slope between the previous and next key values. In the UI, it is identified as Spline.
        kFBTangentModeClampProgressive  //!< Time independent, will flatten the tangent handles when the key value goes over or under the previous and next key values. In the UI, it is identified as Auto.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, TangentMode );

    /**
    *	Different clamping modes for the tangents.
    */
    enum FBTangentClampMode	{
        kFBTangentClampModeNone,	//!< The tangent will act normally.
        kFBTangentClampModeClamped	//!< The tangent will be flattened when the key is placed at the same value as an adjacent key.
        //Add other clamping methods here...
    };
    FB_DEFINE_ENUM( FBSDK_DLL, TangentClampMode );

    /**
    *	Different constant modes for the tangents.
    */
    enum FBTangentConstantMode {
        kFBTangentConstantModeNormal,	//!< The tangent will contain the value of the current keyframe until the next keyframe.
        kFBTangentConstantModeNext		//!< The tangent will contain the value of the next keyframe.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, TangentConstantMode );

    /**
    *	Modes for pre / post extrapolation
    */
    enum FBExtrapolationMode {
        kFCurveExtrapolationConst = 1,
        kFCurveExtrapolationRepetition = 2,
        kFCurveExtrapolationMirrorRepetition = 3,
        kFCurveExtrapolationKeepSlope = 4,
        kFCurveExtrapolationRelativeRepetition = 5
    };
    FB_DEFINE_ENUM( FBSDK_DLL, ExtrapolationMode );

	/**
	*	Different types for the animation node connectors.
	*/
	enum FBAnimationNodeConnectorType {
		kFBAnimationNodeConnectorTypeNone,			//!< The animation node connector is not connected and doesn't have a constant value set to it.
		kFBAnimationNodeConnectorTypeConnectedIn,	//!< The animation node input connector is connected to an animation node output connector (valid for input connector only).
		kFBAnimationNodeConnectorTypeConnectedOut,	//!< The animation node output connector is connected to at least one animation node input connector (valid for output connector only).
		kFBAnimationNodeConnectorTypeConstantIn,	//!< The animation node input connector has a constant value set to it (valid for input connector only).
	};
	FB_DEFINE_ENUM( FBSDK_DLL, AnimationNodeConnectorType );

	/**
	*	Custom tangent index for the tangents.
	*/
	enum FBTangentCustomIndex {
		kFBTangentCustomIndex0,		//!< First custom tangent type registered in the system.
		kFBTangentCustomIndex1,		//!< Second custom tangent type registered in the system.
		kFBTangentCustomIndex2,		//!< Third custom tangent type registered in the system.
	};
	FB_DEFINE_ENUM( FBSDK_DLL, TangentCustomIndex );

	/**
	*	Active tangent weight, no/one/both side are active on a key. Please note, the left value is for the next key, as the current key contains the tangent weight information for the next key. To disable the weight on the left side of a key at index "i", you need to disable "kFBTangentWeightModeNextLeft" the "i-1" key.
	*/
	enum FBTangentWeightMode {
		kFBTangentWeightModeNone,		//!< Tangent weight disabled.
		kFBTangentWeightModeRight,		//!< Right tangent weight active.
		kFBTangentWeightModeNextLeft,	//!< Next key left tangent weight active.
		kFBTangentWeightModeBoth		//!< Right tangent and next key left tangent weight are active
	};
	FB_DEFINE_ENUM( FBSDK_DLL, TangentWeightMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBFCurveKey
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBFCurve );
    __FB_FORWARD( FBFCurveKey );
    FB_FORWARD( FBPropertyListFCurveKey );

    //! KeyFrame for an FCurve.
    class FBSDK_DLL FBFCurveKey
    {
    private:
        DataFBFCurveKey* mLocalPtr;
        void FBFCurveKeyInitProperties();
        //! Empty function to avoid creating property container object.
        void PropertyAdd( FBProperty* ) {};
    public:
        /**	Constructor
        *	\param	pFCurve		Parent FCurve (default is NULL).
        *	\param	pKeyIndex	Key frame index (default is 1).
        */
        FBFCurveKey( ::KFCurve* pFCurve=NULL, int pKeyIndex=1 );

        /**	Constructor
        *	\param	pFCurveKey	FCurveKey to copy information from.
        */
        FBFCurveKey( const FBFCurveKey &pFCurveKey );

        /**	Destructor.
        */
        ~FBFCurveKey();

        /**	Overloaded == operator.
        *	\param	pValue	FCurveKey to compare with.
        *	\return	\b true if equal.
        *	\warning.	The overload of the == operator will always return \b false.
        */
        bool operator==(const FBFCurveKey &pValue) const;

        // To convert the derivative values to degrees (as shown in Exact mode):
        //    degrees( atan( RightDerivative ))
        //    -1 * degrees( atan( LeftDerivative )) 
        //
        // To convert from the exact degree in Exact mode in the GUI to the corresponding
        // derivative:
        //    tan( radians( RightDerivative ))
        //    tan( radians( -1 * LeftDerivative ))
        FBPropertyFloat	Value;				//!< <b>Read Write Property:</b> Value of Key
        FBPropertyFloat	LeftDerivative;		//!< <b>Read Write Property:</b> Left derivative, in units/seconds.
        FBPropertyFloat	RightDerivative;	//!< <b>Read Write Property:</b> Right derivative, in units/seconds.
        FBPropertyFloat LeftTangentWeight;	//!< <b>Read Write Property:</b> Left tangent weight
        FBPropertyFloat RightTangentWeight;	//!< <b>Read Write Property:</b> Right tangent weight
        FBPropertyFloat LeftBezierTangent;	//!< <b>Read Write Property:</b> Left bezier tangent
        FBPropertyFloat RightBezierTangent;	//!< <b>Read Write Property:</b> Right bezier tangent

        // TCB
        FBPropertyFloat	Tension;			//!< <b>Read Write Property:</b> Tension (TCB).
        FBPropertyFloat	Continuity;			//!< <b>Read Write Property:</b> Continuity (TCB).
        FBPropertyFloat	Bias;				//!< <b>Read Write Property:</b> Bias (TCB).

        FBPropertyTime					Time;					//!< <b>Read Write Property:</b> Time of key.
        FBPropertyInterpolation			Interpolation;			//!< <b>Read Write Property:</b> Type of interpolation.
        FBPropertyTangentMode			TangentMode;			//!< <b>Read Write Property:</b> Tangent calculation method.
        FBPropertyTangentClampMode		TangentClampMode;		//!< <b>Read Write Property:</b> Tangent's clamp method.
        FBPropertyBool					TangentBreak;			//!< <b>Read Write Property:</b> Tangent's break status
        FBPropertyTangentConstantMode	TangentConstantMode;	//!< <b>Read Write Property:</b> Tangent's constant mode
        FBPropertyTangentWeightMode		TangentWeightMode;		//!< <b>Read Write Property:</b> Tangent's weight mode. Setting the value for LeftTangentWeight/RightTangentWeight will also activate the weight for that part. Please see the note provided with FBTangentWeightMode for the left weight of a key.
        FBPropertyExtrapolationMode		ExtrapolationMode;		//!< <b>Read Write Property:</b> Extrapolation mode
        FBPropertyTangentCustomIndex	TangentCustomIndex;		//!< <b>Read Write Property:</b> Tangent's custom index

        FBPropertyBool  Selected;               //!< <b>Read Write Property:</b> Is the key selected.
        FBPropertyBool  MarkedForManipulation;  //!< <b>Read Write Property:</b> Is the key marked for manipulation.

        friend class FBFCurve;
        friend class FBPropertyListFCurveKey;
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListFCurveKey
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBFCurveKey );

    //! List of FCurveKey
    class FBSDK_DLL FBPropertyListFCurveKey : public FBPropertyBaseList< FBFCurveKey >
    {
    private:
        /**	Add an FCurveKey.
        *	\param		pItem	Key to add.
        *	\return		Number of keys in list.
        *	\warning	This function is private.
        */
        virtual int	 Add	( FBFCurveKey pItem );

        /**	Remove an FCurveKey.
        *	\param		pItem	Key to remove.
        *	\return		Number of keys in list.
        *	\warning	This function is private.
        */
        virtual int  Remove	( FBFCurveKey pItem );

    public:

        /**	Remove an FCurveKey.
        *	\param		pIndex	Index of key to remove.
        */
        virtual void RemoveAt( int pIndex );

        /**	Overloaded [] operator.
        *	\param	pIndex	Index of key to access.
        *	\return Key at \e pIndex.
        */
        virtual FBFCurveKey operator[](int pIndex);

        /**	Get a count of the number of keys in list.
        *	\return	Number of keys in list.
        */
        virtual int  GetCount();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBFCurve
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBFCurve);

    //! FCurve class.
    class FBSDK_DLL FBFCurve : public FBComponent {
        __FBClassDeclare( FBFCurve,FBComponent );
    public:
        /**	Constructor.
        *	\param	pObject	For internal use only (default is NULL).
        */
        FBFCurve(HIObject pObject=NULL);

        /** Virtual FBDelete function.
        */
        virtual void FBDelete() override;

        /**	Evaluate FCurve at \e pTime.
        *	\param	pTime	Time at which FCurve is to be evaluated.
        *	\return	Value of FCurve at \e pTime.
        */
        float	Evaluate(FBTime &pTime);

        /**	Setup function to begin adding keys.
        *	\param	pKeyCount	Key to begin adding at(default is -1).
        */
        void	EditBegin(int pKeyCount=-1);

        /**	End key adding sequence.
        *	\param	pKeyCount	Key to finish adding at (default is -1).
        */
        void	EditEnd(int pKeyCount=-1);

        //!	Empty FCurve of all keys.
        void	EditClear();

        /** Add a key at the specified time.
        *   @param pTime            Time at which to insert the key.
        *   @param pValue           Value of the key.
        *   @param pInterpolation   Interpolation type of the inserted key, default value is Cubic interpolation.
        *   @param pTangentMode     Tangent calculation method of the inserted key, default value is Auto (Smooth).
        *   @return     The position of the new key in the list of FCurve keys.
        */
        int KeyAdd( FBTime &pTime, double pValue, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto );

		/** Add at once multiple keys at different specified times.
		*   The array size of pTimes and pValues must match. If pInterpolations and pTangentModes parameters are specified, their array sizes must also match the array size of pTimes.
		*   The value of each index of each input array will be used together to form a key data to add.
		*   
		*   \par Python
		*   Each parameter of KeysAdd is a Python list. ex : KeysAdd( [time1, time2], [value1, value2] )
		*   
		*   @param pTimes           Times at which to insert the keys.
		*   @param pValues          Values of the keys.
		*   @param pInterpolations  Interpolation types of the inserted keys, default value is Cubic interpolation for all the keys if this parameter is omitted.
		*   @param pTangentModes    Tangent calculation methods of the inserted keys, default value is Auto (Smooth) for all the keys if this parameter is omitted.
		*   @return     True if the operation is successful, false otherwise.
		*/
		bool KeysAdd( const FBArrayTemplate<FBTime>&			pTimes,
					  const FBArrayDouble&						pValues,
					  const FBArrayTemplate<FBInterpolation>&	pInterpolations = FBArrayTemplate<FBInterpolation>(),
					  const FBArrayTemplate<FBTangentMode>&		pTangentModes = FBArrayTemplate<FBTangentMode>() );

		/** Set at once multiple existing keys values.
		*   The array size of pIndices and pValues must match. If pInterpolations and pTangentModes parameters are specified, their array sizes must also match the array size of pIndices.
		*   The value of each index of each input array (except for pIndices) will be used together to modify the key data of the key specified by the key index of pIndices.
		*   
		*   \par Python
		*   Each parameter of KeysSetValues is a Python list. ex : KeysSetValues( [index1, index2], [value1, value2] )
		*   
		*   @param pIndices         Indices of existing keys to modify.
		*   @param pValues          New values of the keys to modify.
		*   @param pInterpolations  New interpolation types of the keys to modify if specified, otherwise the interpolation types are untouched.
		*   @param pTangentModes    New tangent calculation methods of the keys to modify if specified, otherwise the tangent calculation methods are untouched.
		*   @return     True if the operation is successful (at least one key is modified), false otherwise.
		*/
		bool KeysSetValues( const FBArrayUInt&						pIndices,
							const FBArrayDouble&					pValues,
							const FBArrayTemplate<FBInterpolation>&	pInterpolations = FBArrayTemplate<FBInterpolation>(),
							const FBArrayTemplate<FBTangentMode>&	pTangentModes = FBArrayTemplate<FBTangentMode>() );

        /** Remove key at index.
        *   @param  pIndex  Index of the key to remove.
        *   @return         If the removal was successful or not.
        */
        bool KeyRemove( int pIndex );

        /** Delete keys within an index range.
        *	This function is much faster than multiple removes.
        *	@param pStartIndex Index of first deleted key.
        *	@param pStopIndex Index of last deleted key.
		*	@return \c True if the delete operation is successful, \c false otherwise (e.g. the FCurve is locked, the index range is invalid, etc.).
        */
        bool KeyDelete( int pStartIndex, int pStopIndex );	

        /** Delete keys within a time range.
        *	This function is much faster than multiple removes.
        *	@param pStart Start of time range.
        *	@param pStop End of time range.
		*	@param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*	@return \c True if the delete operation is successful, \c false otherwise (e.g. the FCurve is locked, no keys found within the time range, etc.).
        */	
        bool KeyDelete( FBTime pStart = FBTime::MinusInfinity, FBTime pStop = FBTime::Infinity, bool pInclusive = false );

        /**	Insert a key without affecting the curve shape
        *	\param pTime            Time at which the key is to be inserted.
        *   \param pInterpolation   Interpolation type of the inserted key, default value is Cubic interpolation.
        *   \param pTangentMode     Tangent calculation method of the inserted key, default value is Auto (Smooth).
        */
        void KeyInsert( FBTime &pTime, FBInterpolation pInterpolation = kFBInterpolationCubic, FBTangentMode pTangentMode = kFBTangentModeAuto );

        /**	Replace keys within a range in current function curve with keys found in a source function curve.
        *   \param pSource Source function curve.
        *   \param pStart Start of time range.
        *   \param pStop End of time range.
        *   \param pUseExactGivenSpan When \c false, the time of the first and last key in the range will be used.
        *   \param pKeyStartEndOnNoKey When \c true, inserts a key at the beginning and at the end of the range if there is no key to insert.
        */
        void KeyReplaceBy( FBFCurve& pSource, FBTime pStart = FBTime::MinusInfinity, FBTime pStop = FBTime::Infinity, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true );

		/**	Offset keys within an index range by a given offset time.
		*   When offsetting many keys at once, all non-moving keys that are situated in the target range are deleted automatically, to preserve the animation being offset.
		*   \param pOffsetTime The offset time to apply on keys.
		*   \param pStartIndex Index of first key to be offset.
		*   \param pStopIndex Index of last key to be offset.
		*   \return	\c True if the offset operation is successful, \c false otherwise (e.g. the FCurve is locked, the index range is invalid, etc.).
		*/
		bool KeyOffset(
			FBTime& pOffsetTime,
			int		pStartIndex,
			int		pStopIndex );

		/**	Offset keys within a time range by a given offset time.
		*   Non-moving keys that are situated in the target range are deleted automatically, to preserve the animation being offset.
		*   \param pOffsetTime The offset time to apply on keys.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \return	\c True if the offset operation is successful, \c false otherwise (e.g. the FCurve is locked, no keys found within the time range, etc.).
		*/
		bool KeyOffset(
			FBTime& pOffsetTime,
			FBTime	pStartTime = FBTime::MinusInfinity,
			FBTime	pStopTime = FBTime::Infinity,
			bool	pInclusive = true );

        /**	Create and interpolator curve.
        *   \param pCurveType Interpolator curve type to create.
        */
        static FBFCurve* CreateInterpolatorCurve( FBInterpolatorCurveType pCurveType );

        /**	Get modes for post extrapolation
        */
        FBExtrapolationMode GetPostExtrapolationMode();

        /**	Set modes for post extrapolation
        */
        void SetPostExtrapolationMode(FBExtrapolationMode pExtrapolationMode);

        /**	Get count for post extrapolation
        */
		int GetPostExtrapolationCount();

        /**	Set count for post extrapolation
        */
        void SetPostExtrapolationCount(int pCount);

        /**	Get modes for pre extrapolation
        */
        FBExtrapolationMode GetPreExtrapolationMode();

        /**	Set modes for pre extrapolation
        */
        void SetPreExtrapolationMode(FBExtrapolationMode pExtrapolationMode);

        /**	Get count for pre extrapolation
        */
		int GetPreExtrapolationCount();

        /**	Set count for pre extrapolation
        */
        void SetPreExtrapolationCount(int pCount);

        FBPropertyListFCurveKey GetKeys(){ return Keys; };
        void SetKeys(FBPropertyListFCurveKey pKeys){ Keys = pKeys; };
        FBPropertyListFCurveKey	Keys;		//!< <b>List:</b> Keys.
		
	    /** Get the key value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return         Value of the key.
	    */
		float KeyGetValue(int pIndex);

		/** Set the key value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue  Value of the key.
	    */
		void KeySetValue(int pIndex, float pValue);

	    /** Get the key left derivative value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return         Left derivative value, in units/seconds.
	    */
		float KeyGetLeftDerivative(int pIndex);

	    /** Set the key left derivative value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param  pValue	Left derivative value, in units/seconds.
	    */
		void KeySetLeftDerivative(int pIndex, float pValue);

	    /** Get the key right derivative value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return         Right derivative value, in units/seconds.
	    */
		float KeyGetRightDerivative(int pIndex);

	    /** Set the key right derivative value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param  pValue	Right derivative value, in units/seconds.
	    */
		void KeySetRightDerivative(int pIndex, float pValue);

	    /** Get the key left tangent weight at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Left tangent weight.
	    */
		float KeyGetLeftTangentWeight(int pIndex);

	    /** Set the key left tangent weight at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Left tangent weight.
	    */
		void KeySetLeftTangentWeight(int pIndex, float pValue);

	    /** Get the key right tangent weight at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Right tangent weight.
	    */
		float KeyGetRightTangentWeight(int pIndex);

	    /** Set the key right tangent weight at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Right tangent weight.
	    */
		void KeySetRightTangentWeight(int pIndex, float pValue);

	    /** Get the key left bezier tangent value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Left bezier tangent.
	    */
		float KeyGetLeftBezierTangent(int pIndex);

	    /** Set the key left bezier tangent value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Left bezier tangent.
	    */
		void KeySetLeftBezierTangent(int pIndex, float pValue);

	    /** Get the key right bezier tangent value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Right bezier tangent.
	    */
		float KeyGetRightBezierTangent(int pIndex);

	    /** Set the key right bezier tangent value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Right bezier tangent.
	    */
		void KeySetRightBezierTangent(int pIndex, float pValue);

	    /** Get the key tension value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tension value.
	    */
		float KeyGetTCBTension(int pIndex);

	    /** Set the key tension value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tension value.
	    */
		void KeySetTCBTension(int pIndex, float pValue);

	    /** Get the key continuity value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Continuity value.
	    */
		float KeyGetTCBContinuity(int pIndex);

	    /** Set the key continuity value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Continuity value.
	    */
		void KeySetTCBContinuity(int pIndex, float pValue);

	    /** Get the key bias value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Bias value.
	    */
		float KeyGetTCBBias(int pIndex);

	    /** Set the key bias value at the specified index (TCB key).
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Bias value.
	    */
		void KeySetTCBBias(int pIndex, float pValue);

	    /** Get the key time value at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Time of key.
	    */
		FBTime KeyGetTime(int pIndex);
	
	    /** Set the key time value at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Time of key.
	    */
		void KeySetTime(int pIndex, FBTime pValue);

	    /** Get the key interpolation type at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Type of interpolation.
	    */
		FBInterpolation KeyGetInterpolation(int pIndex);

	    /** Set the key interpolation type at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Type of interpolation.
	    */
		void KeySetInterpolation(int pIndex, FBInterpolation pValue);

	    /** Get the key tangent mode at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tangent calculation method.
	    */
		FBTangentMode KeyGetTangentMode(int pIndex);

	    /** Set the key tangent mode at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tangent calculation method.
	    */
		void KeySetTangentMode(int pIndex, FBTangentMode pValue);

		/** Get the key tangent's clamp method at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tangent's clamp method.
	    */
		FBTangentClampMode KeyGetTangentClampMode(int pIndex);

		/** Set the key tangent's clamp method at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tangent's clamp method.
	    */
		void KeySetTangentClampMode(int pIndex, FBTangentClampMode pValue);

		/** Get the key tangent's break status at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tangent's break status.
	    */
		bool KeyGetTangentBreak(int pIndex);

		/** Set the key tangent's break status at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tangent's break status.
	    */
		void KeySetTangentBreak(int pIndex, bool pValue);

		/** Get the key tangent's constant mode at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tangent's constant mode.
	    */
		FBTangentConstantMode KeyGetTangentConstantMode(int pIndex);

		/** Set the key tangent's constant mode at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tangent's constant mode.
	    */
		void KeySetTangentConstantMode(int pIndex, FBTangentConstantMode pValue);

		/** Get the key tangent's custom index at the specified index.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Tangent's custom index.
	    */
		FBTangentCustomIndex KeyGetTangentCustomIndex(int pIndex);

		/** Set the key tangent's custom index at the specified index.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Tangent's custom index.
	    */
		void KeySetTangentCustomIndex(int pIndex, FBTangentCustomIndex pValue);

		/** Get the tangent weight mode for a key.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			Current weight mode.
	    */
		FBTangentWeightMode KeyGetTangentWeightMode(int pIndex);

		/** Change the tangent weight for a key. Setting the value for LeftTangentWeight/RightTangentWeight will also activate the weight for that part. Please see the note provided with FBTangentWeightMode for the left weight of a key.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	Set the pValue according to the desired mode, kFBTangentWeightModeNone to disable it.
	    */
		void KeySetTangentWeightMode(int pIndex, FBTangentWeightMode pValue);

		/** Get the key selected state.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			True if the key is selected, false otherwise.
	    */
		bool KeyGetSelected(int pIndex);

		/** Set the key selected state.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	New selection state.
		*   @return	True if the operation was successful, false otherwise.
	    */
		bool KeySetSelected(int pIndex, bool pValue);

		/** Get the key manipulation state.
	    *   @param  pIndex  Index of the key to query.
	    *   @return			True if the key is being manipulated, false otherwise.
	    */
		bool KeyGetMarkedForManipulation(int pIndex);

		/** Set the key manipulation state.
	    *   @param  pIndex  Index of the key to set.
	    *   @param	pValue	New manipulation state.
	    *   @return	True if the operation was successful, false otherwise.
	    */
		bool KeySetMarkedForManipulation(int pIndex, bool pValue);
    };

    FB_DEFINE_COMPONENT( FBSDK_DLL, FCurve );

	////////////////////////////////////////////////////////////////////////////////////
	// FBFCurveCustomTangent
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBFCurveCustomTangent);

	//! This class represents a custom tangents object in the system.
	class FBSDK_DLL FBFCurveCustomTangent : public FBComponent {
		__FBClassDeclare( FBFCurveCustomTangent,FBComponent );
	public:
		/**	Constructor.
		*	\param	pObject	For internal use only (default is NULL).
		*/
		FBFCurveCustomTangent(HIObject pObject=NULL);

		/** Virtual FBDelete function.
		*/
		virtual void FBDelete() override;

		FBPropertyString			CustomTangentName;			//!< <b>Read Only Property:</b> Name of custom tangent, will be displayed in the interface.
		FBPropertyString			CustomTangentFBXName;		//!< <b>Read Only Property:</b> Name of custom tangent, will be used in the FBX file to identify custom key type.
		FBPropertyInt				CustomTangentIndex;			//!< <b>Read Only Property:</b> Index of the custom tangent in the system. When you will evaluate a key with your evaluator, match the index of the key with this index to know which tangent type is on the key.
	};

	FB_DEFINE_COMPONENT( FBSDK_DLL, FBFCurveCustomTangent );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! <b>List:</b> Custom Tangent
	class FBSDK_DLL FBPropertyListCustomTangent : public FBPropertyListComponent
	{
	public:
		/** Constructor */
		FBPropertyListCustomTangent();

		/**	Get the custom tangent at \e pIndex.
		*	\param	pIndex	Index of custom tangent to get.
		*	\return Custom tangent at \e pIndex.
		*/
		FBFCurveCustomTangent* operator[](int pIndex);
	};

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListAnimationNode
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBAnimationNode);
    __FB_FORWARD( FBPropertyListAnimationNode);
    FB_DEFINE_LIST( FBSDK_DLL, AnimationNode );

    //! List of animation nodes
    class FBSDK_DLL FBPropertyListAnimationNode : public FBPropertyBaseList< FBAnimationNode* >
    {
    public:
        /**	Add an animation node to the list.
        *	\param		pItem	Animation node to add.
        *	\return		Number of animation nodes in list after operation.
        */
        virtual int	 Add	( FBAnimationNode* pItem );
        /**	Remove an animation node from the list.
        *	\param		pItem	Animation Node to remove.
        *	\return		Number of animation nodes in list after operation.
        */
        virtual int  Remove	( FBAnimationNode* pItem );
        /**	Remove an animation node from \e pIndex.
        *	\param	pIndex	Index of animation node to remove.
        */
        virtual void RemoveAt( int pIndex );
        /**	Overloaded [] operator.
        *	\param	pIndex	Index of animation node to access.
        *	\return Animation node at \e pIndex.
        */
        virtual FBAnimationNode* operator[](int pIndex);
        /**	Get a count of the number of animation nodes in list.
        *	\return	Number of animation nodes in list.
        */
        virtual int  GetCount();
        /**	Find an animation node.
        *	\param	pOriginalOwner	Original Owner of the AnimationNode.
        *	\param	pDataType	DataType of the AnimationNode.
        *	\return	Handle to the animation node with the Given DataType and Owner.
        */
        FBAnimationNode* Find( FBBox *pOriginalOwner, const char* pDataType );
        /**	Find an animation node.
        *	\param	pNodeName	String name of animation node to find.
        *	\return	Handle to the animation node by the name of \e pNodeName.
        */
        FBAnimationNode* Find( const char* pNodeName );
        /**	Find an animation node by label name.
        *	\param	pNodeLabel	UI name of animation node to find.
        *	\return	Handle to the animation node by the label of \e pNodeName.
        */
        FBAnimationNode* FindByLabel( const char* pNodeLabel );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBEventAnimationNode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Event based on animation node 

    //! Types of transformation.
    enum FBEventAnimationNodeType {
        kFBEventAnimationNodeDataChange,
        kFBEventAnimationNodeConstraintChange,
        kFBEventAnimationNodeNone
    };

    FB_DEFINE_ENUM( FBSDK_DLL, EventAnimationNodeType );

    __FB_FORWARD( FBEventAnimationNode );

    /** The transform manipulator has begun doing modifications
    *	This event occurs every time a manipulator:
    *	- receives mouse input
    *	- begins/ends a transaction
    *	- manipulates/moves and object
    */
    class FBSDK_DLL FBEventAnimationNode: public FBEvent
    {
    public:
        /**	Constructor.
        *	\param pEvent Base event (internal) to obtain information from.
        */
        FBEventAnimationNode( HKEventBase pEvent );		

        FBPropertyEventAnimationNodeType		Type;	//!< <b>Read Only Property:</b> Type of selection event.
    };

    ////////////////////////////////////////////////////////////////////////////////////
	// FBCurveEvaluationEvent
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBCurveEvaluationEvent );

	//! This class is used when an evaluation must be done on your custom tangents. It contains the necessary information to do the evaluation. 
	class FBSDK_DLL FBCurveEvaluationEvent : public FBEvent 
	{
	public:
	    /**	Constructor.
	    *	\param pEvent Base event (internal) to obtain information from.
		*	\note Both Time and KeyIndex are valid and can be used to determine where to evaluate.
	    */
	    FBCurveEvaluationEvent( HKEventBase pEvent );

		/**	Get the FbxAnimCurve to evaluate, used in story tool for read-only clip.
		*	\return \b Curve to evaluate if successful, NULL otherwise.
		*/
		FBXSDK_NAMESPACE::FbxAnimCurve*	GetFBXCurve();

	    FBPropertyDouble KeyIndex;				//!< <b>Read Only Property:</b> Index of the key to evaluate, a decimal value indicates an evaluation between two keys (e.g.: 1.25 -> between key 1 and 2 at 25% of the time between key 1 and 2).
	    FBPropertyTime   Time;					//!< <b>Read Only Property:</b> Time to evaluate.
	    FBPropertyFCurve Curve;					//!< <b>Read Only Property:</b> Curve to evaluate.
	    FBPropertyDouble Result;				//!< <b>Read Write Property:</b> Write the resulting value in that prorperty.

	    FBPropertyInt LeftCustomTangentTypeIndex;		//!< <b>Read Only Property:</b> FbxAnimCurveOnly - Type of the left key custom tangent type, -1 if not a custom tangent.
	    FBPropertyInt RightCustomTangentTypeIndex;		//!< <b>Read Only Property:</b> FbxAnimCurveOnly - Type of the right key custom tangent type, -1 if not a custom tangent.
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBCurveCustomKeyAddEvent
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBCurveCustomKeyAddEvent );

	//! This class is used when adding a key with a custom tangent to a curve. It contains the necessary information for the user to specify the properties of the key.
	class FBSDK_DLL FBCurveCustomKeyAddEvent : public FBEvent 
	{
	public:
	    /**	Constructor.
	    *	\param pEvent Base event (internal) to obtain information from.
	    */
	    FBCurveCustomKeyAddEvent( HKEventBase pEvent );
	
		/**	Return the parent FBAnimationNode of the curve if possible.
		*	\return	FBAnimationNode of the curve if possible, NULL otherwise.
		*/
		FBAnimationNode*		GetParentAnimationNode();

		/**	Return the parent object holding the FBAnimationNode of the curve if possible.
		*	\return	Parent (FBComponent) of the curve if possible, NULL otherwise.
		*/
		FBComponent*			GetParentComponent();

	    FBPropertyInt			KeyIndex;		//!< <b>Read Only Property:</b> Index of the new key that will be added
	    FBPropertyTime			Time;			//!< <b>Read Only Property:</b> Time where the key will be added.
	    FBPropertyFCurve		Curve;			//!< <b>Read Only Property:</b> Curve that will receive the new key.
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBCurveCustomKeyChangeEvent
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBCurveCustomKeyChangeEvent );

	//! Indicate if the interpolation or the custom index of the key will be/was modified.
	enum FBCustomKeyChangeType
	{
		kFBNoChange,				//!< No change to the key.
		kFBInterpolationChange,		//!< The interpolation of the key was/will be modified (FBInterpolation).
		kFBCustomTangentChange		//!< The custom tangent value was/will be modified (FBTangentCustomIndex).
	};
	FB_DEFINE_ENUM( FBSDK_DLL, CustomKeyChangeType );

	//! This class is used when changing the interpolation type/custom tangent index of a key with a custom tangent. It contains the necessary information for the user to identify the key.
	class FBSDK_DLL FBCurveCustomKeyChangeEvent : public FBEvent 
	{
	public:
	    /**	Constructor.
	    *	\param pEvent Base event (internal) to obtain information from.
	    */
	    FBCurveCustomKeyChangeEvent( HKEventBase pEvent );

		/**	Return the parent FBAnimationNode of the curve if possible.
		*	\return	FBAnimationNode of the curve if possible, NULL otherwise.
		*/
		FBAnimationNode*		        GetParentAnimationNode();

		/**	Return the parent object holding the FBAnimationNode of the curve if possible.
		*	\return	Parent (FBComponent) of the curve if possible, NULL otherwise.
		*/
		FBComponent*			        GetParentComponent();

		FBPropertyBool					IsPreCall;	//!< <b>Read Only Property:</b> True before the value is actually changed (allowing you to cache the current state if needed), false otherwise.
		FBPropertyCustomKeyChangeType	ChangeType;	//!< <b>Read Write Property:</b> Indicate which setting of the key was/will be changed.

	    FBPropertyInt					KeyIndex;	//!< <b>Read Only Property:</b> Index of the key with the custom tangent type.
	    FBPropertyTime					Time;		//!< <b>Read Only Property:</b> Time of the key.
	    FBPropertyFCurve				Curve;		//!< <b>Read Only Property:</b> Curve with the key set to the custom tangent type.			
	};

	////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyEventAnimationNode
    ////////////////////////////////////////////////////////////////////////////////////
    //! \b PropertyEvent: UI idle event.
    class FBSDK_DLL FBPropertyEventAnimationNode : public FBPropertyEvent
    {
    public:
        /** Add/Remove a callback.
        *	\param	pOwner		Callback owner.
        *	\param	pHandler	Callback handler.
        */
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };
    /**	kFBDataHandler
    *	\param pBuffer
    *	\param pEvaluateInfo
    *	\param pAnimationNode
    *	\param p1
    *	\param p2
    */
    typedef bool (* kFBDataHandler )(void* pBuffer,FBEvaluateInfo* pEvaluateInfo,FBAnimationNode* pAnimationNode,void* p1,void* p2);

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyEventAnimationNodeEvaluate
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a custom tangent that needs to be evaluated.
	class FBSDK_DLL FBPropertyEventAnimationNodeEvaluate : public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyEventAnimationNodeKeyAdd
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a key that doesn't have a custom tangent is added.
	class FBSDK_DLL FBPropertyEventAnimationNodeKeyAdd : public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyEventAnimationNodeCustomKeyAdd
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a key with a custom tangent that needs some of its parameters to be specified is added.
	class FBSDK_DLL FBPropertyEventAnimationNodeCustomKeyAdd : public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyEventAnimationNodeCustomKeyChange
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a key tangent is changed to a custom tangent/changed to another type from a custom tangent or the custom tangent index is changed.
	class FBSDK_DLL FBPropertyEventAnimationNodeCustomKeyChange : public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

    ////////////////////////////////////////////////////////////////////////////////////
    // FBAnimationNode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Animation node class.
    FB_DEFINE_COMPONENT( FBSDK_DLL, AnimationNode );

    class FBSDK_DLL FBAnimationNode : public FBComponent
    {
        __FBClassDeclare( FBAnimationNode,FBComponent );
    public:
        /**	Constructor.
        *	\param	pName		Name of animation node (default is NULL).
        *	\param	pObject		For internal use only (default is NULL).
        */
        FBAnimationNode(const char *pName = NULL, HIObject pObject=NULL);

        /**	Add a key to the animation node.
        *	\param	pTime	        Time to add key at.
        *	\param	pData	        Value of data to add at \e pTime.
        *   \param  pInterpolation  Interpolation type of the inserted key, default value is Cubic interpolation.
        *   \param  pTangentMode    Tangent calculation method of the inserted key, default value is Auto (Smooth).
        */
        void KeyAdd( const FBTime &pTime, double *pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto );

        /**	Add a key to the animation node at current time.
        *	\param	pData	        Value of data to add.
        *   \param pInterpolation   Interpolation type of the inserted key, default value is Cubic interpolation.
        *   \param pTangentMode     Tangent calculation method of the inserted key, default value is Auto (Smooth).
        */
        void KeyAdd( double *pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto );

        /**	Set the current candidate values for current time.
        *   \param	pCheckLocked Decides whether to check the locked status.
        *	\return \b true if successful.
        */
        bool SetCandidate( double* Data, bool pCheckLocked = false );

        /**	Set buffer type for ANIMATIONNODE_TYPE_LOCAL_TRANSLATION, ANIMATIONNODE_TYPE_LOCAL_ROTATION and ANIMATIONNODE_TYPE_LOCAL_SCALE.
        *	\param	pGlobal	Is buffer local or global.
        */
        void SetBufferType( bool pGlobal );

        /**	Keys the current candidate values if no time is specified, at current time.
        *   @param pTime    Time at which to insert the key.
        */
        void KeyCandidate( FBTime pTime = FBTime::Infinity );

        /**	Get sizeof void Data Ptr
        */
        int GetSizeOfData();

        /**	If the DataPtr is of numeric value type ... get the size of the array ex: Light Intensity:1, Translation 3
        *	\return	Size of DataPtr array.
        */
        int GetDataDoubleArrayCount();

        /**	Write data to animation node.
        *	\param	Data			Data to write to animation node.
        *	\param	pEvaluateInfo	Node evaluation information (access to system and local time).
        *	\return	\b true if successful.
        */
        bool WriteData( double* Data,FBEvaluateInfo* pEvaluateInfo );

        /**	Write global data to animation node.
        *	\param	Data			Data to write to animation node.
        *	\param	pEvaluateInfo	Node evaluation information (access to system and local time).
        *	\return	\b true if successful.
        */
        bool WriteGlobalData( double* Data,FBEvaluateInfo* pEvaluateInfo );

        /**	Read data from animation node.
        *	\param	Data	Data to read from animation node.
        *	\param	pEvaluateInfo	Node evaluation information (access to system and local time).
        *	\param	pConvertGlobalToLocal	If global transform data is read, convert it to local data.
        *	\return	\b true if successful.
        */
        bool ReadData( double* Data,FBEvaluateInfo* pEvaluateInfo, bool pConvertGlobalToLocal = false );

        /**	Read data from animation node.
        *	\param	Data	Data to read from animation node.
        *	\param	pTime	Time to read. 
        *	\param	pConvertGlobalToLocal	If global transform data is read, convert it to local data.
        *	\return	\b true if successful.
        *
        *   This will launch a new evaluation buffer to read the data and 
        *   therefore this call is only safe if it is executed from the 
        *   main thread, e.g. within a tool.  In all other cases, 
        *   you should use ReadData( double *Data, FBEvaluateInfo* pEvalInfo ); 
        */
        bool ReadData( double *Data, FBTime pTime, bool pConvertGlobalToLocal = false );

        /**	Read the last data evaluated for this animation node ... 
        *	this call doesn't generate a pull on the connection attached to this
        *   AnimationNode. No validation is done on the pointer size.
        *	You must provide a buffer that is at least GetSizerOfData() size.
        *	\param	Data	Data to read from animation node.
        *	\return	\b true if successful.
        */
        bool ReadData( double* Data );

        /**	Evaluate the animation node data for a given time.
        *	\param	Data	Data to read from animation node.
        *	\param	pTime	Time to evaluate the node.
        *	\param	pEvaluateCandidate	Do evaluate the candidate or not.
        *	\return	Status of animation node.
        */
        bool Evaluate( double* Data, FBTime pTime, bool pEvaluateCandidate = true );

        //! Return true if the animation node had valid data for pEvaluateInfo and read from this connector caused recursion for owner of this evaluation (works only for background evaluation)
        bool IsEvaluationRecursive( FBEvaluateInfo* pEvaluateInfo );

        /**	AnimationNodeNotify is called on FBBox for every animation node that data was pulled by system.
        *	Typically constraints are performing one evaluation per cycle (pEvaluationInfo->GetEvaluationID()) and write to output animation nodes.
        *	In case when not all output animation nodes were written, system may call AnimationNodeNotify again for unwritten animation nodes.
        *	To prevent this, we can call DisableIfNotWritten, which will make sure that AnimationNodeNotify not to be called again for give pEvaluationInfo (based on GetEvaluationID())
        *	\param	pEvaluateInfo	Evaluation synchronization object (contains evaluation id).
        *	\note Disabling of animation nodes that were not write is performed to save performance.
        */
        void DisableIfNotWritten( FBEvaluateInfo* pEvaluateInfo );

        /**	Verifies if there is a key at the current.
        *	\return	\b true if there is a key at the current time.
        */
        bool IsKey();

        /**	Remove key at current time
        */
        void KeyRemove();

        /**	Remove key at the specified time
        *   \param pTime Time for the key
        */
        void KeyRemoveAt( FBTime pTime );

        /**	Get animation node to record to.
        *	\return	Animation node to record to.
        */
        FBAnimationNode* GetAnimationToRecord();

        /**	Get animation node to play from.
        *	\return	Animation node to be played.
        */
        FBAnimationNode* GetAnimationToPlay();

        /**	Convert global time to node time. (NOTE: Only used in the context of a story clip)
        *	\param	pKeyTime	Time of the key to convert.
        */
        FBTime ConvertGlobalToNodeTime(FBTime& pKeyTime);

        /**	Convert node time to global time. (NOTE: Only used in the context of a story clip)
        *	\param	pKeyTime	Time of the key to convert.
        */
        FBTime ConvertNodeToGlobalTime(FBTime& pKeyTime);

        FBPropertyString			Label;			//!< <b>Read Write Property:</b> Label (UI Name).
        FBPropertyString			UserName;		//!< <b>Read Only Property:</b> Name of animation node.
        FBPropertykReference		Reference;		//!< <b>Read Write Property:</b> User-defined reference.
        FBPropertyInt				KeyCount;		//!< <b>Read Only Property:</b> Number of keys.
        FBPropertyFCurve			FCurve;			//!< <b>Read Write Property:</b> FCurve for animation.
        FBPropertyBool				Live;			//!< <b>Read Write Property:</b> Is animation live?
        FBPropertyBool				RecordMode;		//!< <b>Read Write Property:</b> Is the node in recording mode (device connectors)?
        FBPropertyAnimationNode		Parent;			//!< <b>Read Only Property:</b> Parent animation node.
        FBPropertyInterpolation		DefaultInterpolation;	//!< <b>Read Write Property:</b> Default type of interpolation.
		FBPropertyAnimationNodeConnectorType		ConnectorType;	//!< <b>Read Only Property:</b> Animation node connector type.

        FBPropertyListAnimationNode	Nodes;			//!< <b>List:</b> List of animation nodes.

        FBPropertyEventAnimationNode	OnChange;		//!< <b>Event:</b> Called when the value of this property is modified

        friend class FBBox;
    };
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FBAnimationStack
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	__FB_FORWARD( FBAnimationStack );

    /** Used to access animation stack.
    *	Class under development
    */

    class FBSDK_DLL FBAnimationStack : public FBComponent
    {
        //--- Open Reality declaration.
        __FBClassDeclare(FBAnimationStack, FBComponent);
    public:

        /**	Constructor.
        *	\param	pName		Name of the animation stack.
        *	\param	pObject		For internal use only.
        */
        FBAnimationStack(const char *pName, HIObject pObject=NULL);

        /** Virtual FBDelete function.
        */
        virtual void FBDelete() override;

	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBFCurveCustomTangentManager
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBFCurveCustomTangentManager );

	/**	Custom Tangent Manager
	*	Interface to the Custom Tangent Manager.
	*/
	class FBSDK_DLL FBFCurveCustomTangentManager : public FBComponent
	{
	    __FBClassDeclare(FBFCurveCustomTangentManager, FBComponent);

	    //! Constructor. protected 
	    FBFCurveCustomTangentManager();

	public:

		/** Register a new custom tangent in the system.
		*   \param		pTangentName		Name to display in the FCurve Editor and in the Key Control UI.
		*   \param		pTangentFBXName		String to identify the custom tangent in the FBX file.
		*	\return		Index of the custom tangent in the system.
	  	*	\note Only 3 different custom tangents are currently supported.
	    */
		int AddCustomTangentType(const char* pTangentName, const char* pTangentFBXName);

		/** Remove a custom tangent from the system.
		*   \param		pTangentName		Name of the custom tangent to remove, use the UI name that was used when the tangent was registered.
		*	\return		True if the tangent was removed, false otherwise.
		*	\note Custom tangent can only be removed when the scene is empty (after a file new). Be sure to update the index of the remaining tangent, since they might have changed.
	    */
		bool RemoveCustomTangentType(const char* pTangentName);
	
		/** Return the number of tangent currently registered in the system.
		*	\return		Number of custom tangent in the system.
	    */
		int GetCustomTangentTypeCount();

		/** Return the UI name of the custom tangent at the specified index.
		*   \param		pIndex		Index of the custom tangent to query.
		*	\return		UI Name of the custom tangent.
	    */
		const char* GetCustomTangentTypeName(int pIndex);

		FBPropertyEventAnimationNodeEvaluate				OnEvaluate;		//!< <b>Event:</b> Called when evaluating the node, you must evaluate your curve and return the computed value.

		FBPropertyEventAnimationNodeKeyAdd					OnKeyAdd;			//!< <b>Event:</b> Called when adding a key that doesn't have a custom tangent, you can specify some of its parameters if needed. NOTE: you will also receive callbacks for keys added by internal Mobu process, be sure to manage only your curves.
		FBPropertyEventAnimationNodeCustomKeyAdd			OnCustomKeyAdd;		//!< <b>Event:</b> Called when adding a key with a custom tangent, you must specify some of its parameters.

		FBPropertyEventAnimationNodeCustomKeyChange			OnCustomKeyChange;	//!< <b>Event:</b> Called when the interpolation/tangent of a key is changed to/from a custom tangent or custom tangent index is modified.

		/**	Get the global object for this class
	    *	\return	The global object.
	    */
	    static FBFCurveCustomTangentManager& TheOne();
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyStateEvent
	////////////////////////////////////////////////////////////////////////////////////

    /**
    *	This enum indicates what modification was made to the animation of a tracked property.
    */
    enum FBPropertyStateEventType	{
        kFBPropertyStateEventTypeUnknownOperation = 0,  //!< Invalid event
		kFBPropertyStateEventTypeAttached = 1 << 0,		//!< Property connector was added (can happen when undoing a delete operation, which set back the property active in the scene)
		kFBPropertyStateEventTypeDetached = 1 << 1,		//!< Property connector was detached (property animation was delete from the scene, but it still keep in case an undo operation is done)
        kFBPropertyStateEventTypeDestroyed = 1 << 2,	//!< Property connector was destroyed (property animation was deleted)
        kFBPropertyStateEventTypeMassOperation = 1 << 3,//!< Property was heavily modified (switching to story tool, story clip deleted...)
    };
    FB_DEFINE_ENUM( FBSDK_DLL, PropertyStateEventType );

	__FB_FORWARD( FBPropertyStateEvent );

	//! This class is used when the state of a property tracked by the FBFCurveEventManager is changed.
	class FBSDK_DLL FBPropertyStateEvent : public FBEvent 
	{
	public:
	    /**	Constructor.
	    *	\param pEvent Base event (internal) to obtain information from.
	    */
	    FBPropertyStateEvent( HKEventBase pEvent );
	
		/**	Return the FBProperty related to the event
		*	\return	FBProperty of the event.
		*/
		FBProperty*				GetProperty();

		/**	Return the parent object holding the property if possible.
		*	\return	Parent (FBComponent) of the property if possible, NULL otherwise.
		*/
		FBComponent*			GetParentComponent();

		FBPropertyPropertyStateEventType	EventType;    //!< <b>Read Only Property:</b> Event type, please see the FBPropertyStateEventType for the possible types.
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBFCurveEvent
	////////////////////////////////////////////////////////////////////////////////////

    /**
    *	This enum indicates what modification was made to a tracked FCurve.
    */
    enum FBFCurveEventType	{
        kFBFCurveEventTypeUnknownOperation = 0,                     //!< Invalid event
		kFBFCurveEventTypeKeyAdded = 1 << 0,						//!< A new key was added
        kFBFCurveEventTypeKeyRemoved = 1 << 1,						//!< A key was removed
        kFBFCurveEventTypeKeyTimeChanged = 1 << 2,					//!< A key time was changed
        kFBFCurveEventTypeKeyValueChanged = 1 << 3,					//!< A key value was changed
		kFBFCurveEventTypeDerivativedChanged = 1 << 4,				//!< A key left/right/both derivative was changed, please note that this event can affect the key specified in the event index and the following key
		kFBFCurveEventTypeKeyInterpolationChanged = 1 << 5,			//!< A key interpolation mode was changed
		kFBFCurveEventTypeKeyTangentChanged = 1 << 6,				//!< A key tangent was changed
		kFBFCurveEventTypeKeyTangentBreakChanged = 1 << 7,			//!< A key break mode was changed
		kFBFCurveEventTypeKeyTangentClampModeChanged = 1 << 8,		//!< A key clamping mode was changed
		kFBFCurveEventTypeKeyTangentConstantChanged = 1 << 9,		//!< A key constant mode was changed
		kFBFCurveEventTypeKeyVelocityChanged = 1 << 10,				//!< A key velocity was changed
		kFBFCurveEventTypeKeyWeightChanged = 1 << 11,				//!< A key left/right weight was changed, please note that this event can affect the key specified in the event index and the following key
		kFBFCurveEventTypeKeyTensionChanged = 1 << 12,				//!< A key tension was changed (only valid on TCB key)
		kFBFCurveEventTypeKeyContinuityChanged = 1 << 13,			//!< A key continuity was changed (only valid on TCB key)
		kFBFCurveEventTypeKeyBiasChanged = 1 << 14,					//!< A key bias was changed (only valid on TCB key)
		kFBFCurveEventTypeKeyPreExtrapolationChanged = 1 << 15,		//!< A curve pre-extrapolation value was changed
		kFBFCurveEventTypeKeyPostExtrapolationChanged = 1 << 16,	//!< A curve post-extrapolation value was changed
		kFBFCurveEventTypeKeyMassOperation = 1 << 17,				//!< An operation affecting multiple keys was made
    };
    FB_DEFINE_ENUM( FBSDK_DLL, FCurveEventType );

	__FB_FORWARD( FBFCurveEvent );

	//! This class is used when a modification is made on a FCurve. It contains the necessary information to identify the owner of the curve and what modification was made. 
	class FBSDK_DLL FBFCurveEvent : public FBEvent 
	{
	public:
	    /**	Constructor.
	    *	\param pEvent Base event (internal) to obtain information from.
	    */
	    FBFCurveEvent( HKEventBase pEvent );
	
		/**	Return the parent FBProperty of the curve if possible.
		*	\return	FBProperty of the curve if possible, NULL otherwise.
		*/
		FBProperty*				GetParentProperty();

		/**	Return the parent FBAnimationNode of the curve if possible.
		*	\return	FBAnimationNode of the curve if possible, NULL otherwise.
		*/
		FBAnimationNode*		GetParentAnimationNode();

		/**	Return the parent object holding the FBAnimationNode of the curve if possible.
		*	\return	Parent (FBComponent) of the curve if possible, NULL otherwise.
		*/
		FBComponent*			GetParentComponent();

		FBPropertyFCurveEventType	EventType;			//!< <b>Read Only Property:</b> Type of fcurve event.
	    FBPropertyInt				KeyIndexStart;		//!< <b>Read Only Property:</b> Index of the first key which is involved in the event.
	    FBPropertyInt				KeyIndexStop;		//!< <b>Read Only Property:</b> Index of the last key which is involved in the event.
	    FBPropertyFCurve			Curve;				//!< <b>Read Only Property:</b> Curve that will receive the new key.
		FBPropertyString			CurveName;			//!< <b>Read Only Property:</b> Name of curve.
		FBPropertyInt				CurveIndex;			//!< <b>Read Only Property:</b> Index of curve.
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyChanged
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a property is modified, to be used with the FBFCurveEventManager.
	class FBSDK_DLL FBPropertyChanged: public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBFCurveChanged
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyEvent: Event when a fcurve is changed.
	class FBSDK_DLL FBFCurveChanged: public FBPropertyEvent
	{
	public:
	    /** Add/Remove a callback.
		*	\param	pOwner		Callback owner.
		*	\param	pHandler	Callback handler.
		*/
		virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
		virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBFCurveEventManager
	////////////////////////////////////////////////////////////////////////////////////
	__FB_FORWARD( FBFCurveEventManager );

	/**	FCurve Event Manager
	*	Interface to the FBFCurveEventManager. This class is used to track the changes on a FCurve of a property.
	*/
	class FBSDK_DLL FBFCurveEventManager : public FBComponent
	{
	    __FBClassDeclare(FBFCurveEventManager, FBComponent);

	    //! Constructor. protected 
	    FBFCurveEventManager();

	public:

		/**	Register a property to the FCurve Event Manager. Properties that are registered will receive events with the OnFCurveEvent/OnPropertyEvent 
        *   properties when their FCurves are modified.
		*	\param	pProperty		The property to track.
		*	\return	True if the registration was successful, False otherwise.
		*/
		bool RegisterProperty(FBPropertyAnimatable* pProperty);

		/**	Unregister a property from the FCurve Event Manager. Those properties will not be tracked and no update will be sent with the 
        *   OnFCurveEvent/OnPropertyEvent properties anymore.
		*	\param	pProperty		The property to stop tracking.
		*	\return	True if the unregistration was successful, False otherwise.
		*/
		bool UnregisterProperty(FBPropertyAnimatable* pProperty);

		FBFCurveChanged			OnFCurveEvent;	//!< <b>Event:</b> Called when a registered FCurve is modified.
		FBPropertyChanged		OnPropertyEvent;//!< <b>Event:</b> Called when a registered property state is modified (detached, destroyed...).

		/**	Get the global object for this class
	    *	\return	The global object.
	    */
	    static FBFCurveEventManager& TheOne();
	};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FBAnimationLayer
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
    *	Layer mode.
    */
    enum FBLayerMode	{
        kFBLayerModeInvalidIndex = -1,	//!< Invalid value
        kFBLayerModeAdditive = 0,		//!< Layer value will be added to the other layers to computed the final value.
        kFBLayerModeOverride,			//!< Layer value will override the value of the other precedent layers.
        kFBLayerModeOverridePassthrough	//!< If the layer has a weight of 75%, the precedent layers will have a combined effect of 25% on the final value. Setting the weight to 100% is similar to setting the layer in override.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, LayerMode );

    /**
    *	Rotation mode for layer.
    */
    enum FBLayerRotationMode	{
        kFBLayerRotationModeInvalidIndex = -1,		//!< Invalid value
        kFBLayerRotationModeEulerRotation = 0,	//!< The rotation will be computed component by component.
        kFBLayerRotationModeQuaternionRotation	//!< The rotation will be computed using quaternion.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, LayerRotationMode );


    __FB_FORWARD( FBAnimationLayer );

    /** Used to access animation layer properties and modify them.
    *	Changing the various properties of the layers will modify how the animation
    *	will be interpreted. For example, muting a layer will mute all the animation
    *	contained on the layer. You can access the animation layer object from the take,
    *	usign the FBTake::GetLayer() and FBTake::GetLayerByName(). See the FBTake class for more details.
    */

    class FBSDK_DLL FBAnimationLayer : public FBComponent
    {
        //--- Open Reality declaration.
        __FBClassDeclare(FBAnimationLayer, FBComponent);
    public:

        /**	Constructor.
        *	\param	pName		Name of the animation layer.
        *	\param	pLayerID	ID to set for the new layer.
        *	\param	pObject		For internal use only.
        */
        FBAnimationLayer(const char *pName, int pLayerID, HIObject pObject=NULL);

        /** Virtual FBDelete function.
        */
        virtual void FBDelete() override;

        FBPropertyColor				Color;				//!< <b>Read Write Property:</b> The animation layer color.
        FBPropertyBool				Solo;				//!< <b>Read Write Property:</b> If true, the layer is soloed. When you solo a layer, you mute other layers that are at the same level in the hierarchy, as well as the children of those layers. Cannot be applied to the BaseAnimation Layer.
        FBPropertyBool				Mute;				//!< <b>Read Write Property:</b> If true, the layer is muted. A muted layer is not included in the result animation. Cannot be applied to the BaseAnimation Layer.
        FBPropertyBool				Lock;				//!< <b>Read Write Property:</b> If true, the layer is locked. You cannot modify keyframes on a locked layer.
        FBPropertyAnimatableDouble	Weight;				//!< <b>Read Write Property:</b> The weight value of a layer determines how much it is present in the result animation. Takes a value from 0 (the layer is not present) to 100. The weighting of a parent layer is factored into the weighting of its child layers, if any. BaseAnimation Layer always has a Weight of 100. 
        FBPropertyLayerMode			LayerMode;			//!< <b>Read Write Property:</b> Layer mode. By default, the layer is in kFBLayerModeAdditive mode. Cannot be applied to the BaseAnimation Layer.
        FBPropertyLayerRotationMode	LayerRotationMode;	//!< <b>Read Only Property:</b> Layer rotation mode. Cannot be applied to the BaseAnimation Layer.

        /** Add a child to the layer. Layer ID of the new child layer might change after parenting depending where the child layer was originally located.
        *   \param		pAnimationLayer		Layer to set as a child.
        */
        void	AddChildLayer( FBAnimationLayer* pAnimationLayer );

        /** Get the nth child layer of this layer.
        *   \param		pIndex		Index of the child layer to get.
        *	\return		Child animation layer located at pIndex
        */
        FBAnimationLayer*	GetChildLayer( int pIndex );

        /** Get the child layer count of this layer. The count will only includes direct child of the layer.
        *   \return		Child layer count, or -1 if unsuccessful
        */
        int		GetChildCount();

        /** Get the all the children hierarchy of the layer, including children not directly connected to this layer
        *	\par Python
        *	The function takes no parameter and returns a Python list. ex : lArray = lAnimationLayer.GetCompleteChildHierarchy()  
        *
        *	\param	pChildArray	Array of child layers, will be filled by the function.
        */
        void	GetCompleteChildHierarchy(FBArrayTemplate<FBAnimationLayer*>* pChildArray);

        /** Set the parent layer.
        *   \param	pParentLayer A pointer to the parent layer or NULL if you want to unparent the layer.
        */
        void SetParentLayer(FBAnimationLayer* pParentLayer);

        /** Get the parent layer.
        *   \return		A pointer to the parent layer or NULL if the layer doesn't have a parent.
        */
        FBAnimationLayer*	GetParentLayer();

        /** Get the layer index.
        *   \return		The layer index in the current layer hierarchy. This value will change if the hierarchy is modified. Return -1 if unsuccessful.
        */
        int	GetLayerIndex();

        /** Select the layer. This is the equivalent of selecting the layer in the UI in the Animation Layer Editor tool
        *   \param	pValue	True if the layer will be selected, false otherwise.
        *   \param	pExclusiveSelect	If pValue is true, passing true will deselect all the other layers, creating an exclusive selection, it will also set the layer as the current layer.
        */
        void SelectLayer(bool pValue, bool pExclusiveSelect);

        /** Verify if the layer is selected.
        *   \return	True if the layer is selected, false otherwise. 
        */
        bool IsSelected();
    };


    __FB_FORWARD( FBTake);
    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListTake
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //! <b>List:</b> Take
    class FBSDK_DLL FBPropertyListTake : public FBPropertyListComponent
    {
    public:
        FBPropertyListTake();
        /**	Get the take at \e pIndex.
        *	\param	pIndex	Index of the take to get.
        *	\return the take at \e pIndex.
        */
        FBTake* operator[](int pIndex);

        /**	Add a component to the list.
        *	\param	pItem	Component to add to list.
        *	\return Number of components in list after operation.
        */
        virtual int Add( FBComponent* pItem ) override;

        /**	Remove the component at \e pIndex from list.
        *	\param	pIndex	Index of Component to remove.
        */
        virtual void RemoveAt( int pIndex ) override;
    };

    //! Merge option for animation layers.
    enum FBAnimationLayerMergeOptions	{	
        kFBAnimLayerMerge_SelectedLayers_SelectedProperties,//!< Merge the animation of the selected properties of the selected models from the selected layers to the selected layer with the lowest index.
        kFBAnimLayerMerge_AllLayers_SelectedProperties,		//!< Merge the animation of the selected properties of the selected models from all the layers to the BaseAnimation layer.
        kFBAnimLayerMerge_SelectedLayers_AllProperties,		//!< Merge the animation of all properties of the selected models from the selected layers to the selected layer with the lowest index.
        kFBAnimLayerMerge_AllLayers_AllProperties,			//!< Merge the animation of all properties of the selected models from all the layers to the BaseAnimation layer.
        kFBAnimLayerMerge_SelectedLayers_CompleteScene,		//!< Merge the animation of all properties from the selected layers to the selected layer with the lowest index.
        kFBAnimLayerMerge_AllLayers_CompleteScene,			//!< Merge the animation of all properties from all the layers to the BaseAnimation layer.
    };

    //! Merge layer mode for animation layers. This will specify the mode of the resulting merged layer, if applicable (To BaseAnimation layer mode cannot be modified). 
    enum FBMergeLayerMode	{	
        kFBMergeLayerModeAutomatic,	//!< The resulting layer will be in override mode if one of the source layer is in override, otherwise, it will be in additive mode.
        kFBMergeLayerModeAdditive,	//!< The resulting layer will be in additive mode, if possible.
        kFBMergeLayerModeOverride,	//!< The resulting layer will be in override mode, if possible.
    };

//! Time (Global & Take) Mark assigned action
enum FBTimeMarkAction
{
	kFBTimeMarkAction_None,			//!< No action. The mark is just visual hint.
	kFBTimeMarkAction_Stop,			//!< When reaching the mark, the playback stops.
	kFBTimeMarkAction_Loop,			//!< When reaching the mark, the playback loops to previous global mark (or start frame if any).
};

//! Property Components Bit Field (XYZ, RGB, RGBA, UV, XYZW, etc.).
enum FBPropertyComponents {	
	kFBPropertyComponent0	= 1 << 0,	//!< First component (e.g.: X, Red, etc.).
	kFBPropertyComponent1	= 1 << 1,	//!< Second component (e.g.: Y, Green, etc.).
	kFBPropertyComponent2	= 1 << 2,	//!< Third component (e.g.: Z, Blue, etc.).
	kFBPropertyComponent3	= 1 << 3,	//!< Fourth component (e.g.: W, Alpha, etc.).
	kFBPropertyComponentAll	=	kFBPropertyComponent0 |
								kFBPropertyComponent1 |
								kFBPropertyComponent2 |
								kFBPropertyComponent3	//!< All components.
};	

    ////////////////////////////////////////////////////////////////////////////////////
    // FBTake
    ////////////////////////////////////////////////////////////////////////////////////

    /** A take is a container for animation in a scene.

    A take stores data about animation for objects. The transport controls (FBPlayerControl) act on the current take.

    In the UI transport controls, a take's start and end determine when the Timeline indicator starts and stops.

    You get the current take with FBSystem::CurrentTake, as in the following Python sample:

    \code
    for myTake in FBSystem().Scene.Takes:
    print myTake.Name
    \endcode

    To create a take and have it accessible in the Transport control you could use CopyTake (called Duplicate in the UI):

    Python sample code:    
    @code
    from pyfbsdk import *    
    newTake = FBSystem().CurrentTake.CopyTake("my new take name")
    @endcode    

    C++ sample code:
    @code
    FBTake* lTake = FBSystem::ThenOne().CurrentTake->CopyTake( "my new take" );    
    @endcode

    Or simply create a new empty take like the following:

    Python sample code:    
    @code
    from pyfbsdk import *    
    newTake = FBTake("my new take name")
    FBSystem().Scene.Takes.append(newTake)
    @endcode    

    C++ sample code:
    @code
    FBSystem::TheOne()::Scene.Takes.Add( new FBTake( "my new take" ));
    @endcode

    */
    class FBSDK_DLL FBTake : public FBComponent {
        __FBClassDeclare( FBTake,FBComponent );
    public:
        /**	Constructor.
        *	\param	pName		Name of take.
        *	\param	pObject		For internal use only (default is NULL).
        */
        FBTake(const char* pName, HIObject pObject=NULL);

        /** Deletion method.
        *   Using this method to delete the take insure that the destruction process
        *   follows the same path as if the GUI had been used.
        */
        virtual void FBDelete() override;

        /**	Copy the take.
        *	Will create a copy of the current take, with the current take data.
        *	This is analogous to creating a new take, and copying the current take data into it.
        *	The Layers data and the TimeWarp date will be copied. The newly created take will be set as the current take.
        *	The newly created take is automatically added to the scene and available in the Transport control.
        *	\param	pNewTakeName	The name for the new take.
        *	\return	Handle to the newly created take.
        */
        FBTake*	CopyTake( const char *pNewTakeName );

        /** Create a new layer.
        */
        void CreateNewLayer();    

        /** Remove a layer.
        *   \param pLayerIndex Layer with at the specified index will be removed.
        */
        void RemoveLayer(int pLayerIndex);  

        /** Get the layer object that have the specified ID.
        *   \param pLayerIndex The index of the layer that will be returned.
        *   \return Layer with the specified ID.
        */
        FBAnimationLayer* GetLayer(int pLayerIndex);  

        /** Get the layer object that have the specified name.
        *   \param pName The name of the animation layer to get.
        *   \return Layer with the specified name or NULL if no layer has been found.
        */
        FBAnimationLayer* GetLayerByName(const char* pName);  

        /** Set the current layer for the take. Note that this will not deselect the other layers.
        *	\param	pLayerIndex   The layer index to be set as the current one.
        */
        void SetCurrentLayer(int pLayerIndex);

        /** Get the current layer for the take.
        *	\return The current layer index.
        */
        int GetCurrentLayer();

        /** Get the layer count.
        *	\return The layer count.
        */
        int GetLayerCount();

        /** Move the current layer up, similar to using the button to move the layer in the Animation Layer tool. Use the SetCurrentLayer to specify the current layer.
        *	\return True if successful.
        */
        bool MoveCurrentLayerUp();

        /** Move the current layer down, similar to using the button to move the layer in the Animation Layer tool. Use the SetCurrentLayer to specify the current layer.
        *	\return True if successful.
        */
        bool MoveCurrentLayerDown();

        /** Duplicate the selected layers. This is equivalent of doing a copy-paste.
        */
        void DuplicateSelectedLayers();

        /** Merge the selected layers. This is equivalent of pressing the merge button in the Animation Layer editor.
        *	\param	pMergeOptions   Indicate which objects, layers and properties (selected or all) should be merged.
        *	\param	pDeleteMergedLayers   The source layer will be deleted after the merge if no animation is left on those layers, or if those layers are not parent of another layer.
        *	\param	pMergeMode   Set the layer mode of the resulting layer, if possible (the BaseAnimation layer cannot be modified).
        *	\param	pMergeLockedProperties   The properties will be merged even if they are locked.
        */
        void MergeLayers(FBAnimationLayerMergeOptions pMergeOptions, bool pDeleteMergedLayers, FBMergeLayerMode pMergeMode, bool pMergeLockedProperties = false);

// COMMENT MERGE PREIVEW
#ifdef MERGE_PREVIEW
        /** Can start merge preview for a layer?  That must satisfy all the conditions below:
        *   1) Current take has at least 2 animation layers;
        *   2) No layer's type is solo;
        *   3) Only select ONE layer;
        *   4) Selected layer CANNOT be muted nor locked.
        *   \return True if the answer is yes.
        */
        bool CanDoMergePreview();

        /** Is in Merge Preview mode?
        *   \return True if the answer is yes.
        */
        bool IsInMergePreviewMode();

        /** Start Merge Preview, or go into Merge Preview mode.
        *   \return True if successful.
        */
        bool DoMergePreview();

        /** End Merge Preview, or quit Merge Preview mode.
        */
        void QuitMergePreview();
#endif

        /**	Plot the animation on selected models.
        *	Will plot the animation of the take in question on the selected models in the scene.
        *   \param pPlotOptions Option parameters for plotting
        */
        void PlotTakeOnSelected(FBPlotOptions* pPlotOptions);

        /**	Plot the animation on selected properties.
        *	Will plot the animation of the take in question on the selected properties in the scene.
        *   \param pPlotOptions Option parameters for plotting
        */
        void PlotTakeOnSelectedProperties(FBPlotOptions* pPlotOptions);

        /**	Plot the animation on selected models.
        *	Will plot the animation of the take in question on the selected models in the scene.
        *	\param	pPlotPeriod		Period for the plot.
        */
        void PlotTakeOnSelected(FBTime pPlotPeriod);

        /** Plot the animation on selected models for all takes.
        *	Will plot the animation for all takes on the selected models in the scene.
        *	\param	pPlotPeriod		Period for the plot.
        */
        void PlotAllTakesOnSelected(FBTime pPlotPeriod);

        /**	Plot the animation on selected properties.
        *	Will plot the animation of the take in question on the selected properties in the scene.
        *	\param	pPlotPeriod		Period for the plot.
        */
        void PlotTakeOnSelectedProperties(FBTime pPlotPeriod);

        /**	Plot the animation on selected properties for all takes.
        *	Will plot the animation for all takes on the selected properties in the scene.
        *	\param	pPlotPeriod		Period for the plot.
        */
        void PlotAllTakesOnSelectedProperties(FBTime pPlotPeriod);

        /** Clear the animation on all the properties.
        *	\param	pOnSelectedObjectsOnly		Specify if clear will be performed on all objects or only on the one that are currently selected.
        *	\param	pOnLockedProperties			Specify if clear will be performed on locked properties as well.
        */
        void ClearAllProperties(bool pOnSelectedObjectsOnly, bool pOnLockedProperties = false);

        /** Clear all the animation on the current layer.
        */
        void ClearAllPropertiesOnCurrentLayer();

        FBPropertyTimeSpan	ReferenceTimeSpan;		//!< <b>Read Write Property:</b> Reference time span.
        FBPropertyTimeSpan	LocalTimeSpan;			//!< <b>Read Write Property:</b> Local time span.
        FBPropertyString	Comments;				//!< <b>Read Write Property:</b> Take comments.

        /**	Plot the animation on given objects.
        *	This method will plot the animation of the take to the specified objects. 
        *	Although the method supports boxes, the most common use case it to specify 
        *	FBModels that have been cast to boxes.
        *   \param  pPlotOptions Option parameters for plotting
        *	\param	pObjectsToPlot	Objects to plot.
        */
        void PlotTakeOnObjects( FBPlotOptions* pPlotOptions, FBArrayTemplate<FBBox *> *pObjectsToPlot );

        /**	Plot the animation on given objects.
        *	This method will plot the animation of the take to the specified objects. 
        *	Although the method supports boxes, the most common use case it to specify 
        *	FBModels that have been cast to boxes.
        *	\param	pPlotPeriod		Period for the plot.
        *	\param	pObjectsToPlot	Objects to plot.
        */
        void PlotTakeOnObjects( FBTime pPlotPeriod, FBArrayTemplate<FBBox *> *pObjectsToPlot );

        /** Plot the animation on given objects for all takes.
        *	This method will plot the animation of all takes to the specified objects. 
        *	Although the method supports boxes, the most common use case it to specify 
        *	FBModels that have been cast to boxes.
        *	\param	pPlotPeriod		Period for the plot.
        *	\param	pObjectsToPlot	Objects to plot.
        */
        void PlotAllTakesOnObjects( FBTime pPlotPeriod, FBArrayTemplate<FBBox *> *pObjectsToPlot );

        /**	Plot the animation on given properties.
        *	Will plot the animation of the take in question on the given properties in the scene.
        *	\param	pPlotPeriod			Period for the plot.
        *	\param	pPropertiesToPlot	Properties to plot.
        */
        void PlotTakeOnProperties( FBTime pPlotPeriod, FBArrayTemplate<FBProperty *> *pPropertiesToPlot );

        /**	Plot the animation on given properties for all takes.
        *	Will plot the animation for all takes on the given properties in the scene.
        *	\param	pPlotPeriod			Period for the plot.
        *	\param	pPropertiesToPlot	Properties to plot.
        */
        void PlotAllTakesOnProperties( FBTime pPlotPeriod, FBArrayTemplate<FBProperty *> *pPropertiesToPlot );


		/** Add a time mark to the take. It doesn't allow creating a time mark at the same time of another time mark.
		*   Note: Internally, the time marks are stored in time order. Adding a time mark before other existing time marks will modify the index of these other time marks.
		*   \param pTime Time where to add the time mark on the take.
		*   \param pName Name of the time mark to add.
		*   \return The index of the time mark added if the operation is successful, -1 otherwise.
		*/
		int AddTimeMark( FBTime pTime, const char* pName = NULL );

		/** Delete a time mark from the take.
		*   Note: Internally, the time marks are stored in time order. Deleting a time mark will modify the index of time marks laying after the deleted time mark.
		*   \param pIndex Index of the time mark to delete.
		*   \return True if the operation is successful, false otherwise.
		*/
		bool DeleteTimeMark( int pIndex );

		/** Delete all time marks from the take.
		*/
		void DeleteAllTimeMarks();

		/** Returns the number of time marks on the take.
		*   \return The number of time marks on the take.
		*/
		int GetTimeMarkCount();

		/** Returns the time associated with a time mark.
		*   \param pIndex Index of the time mark.
		*   \return The time associated with the time mark.
		*/
		FBTime GetTimeMarkTime( int pIndex );

		/** Sets a new time for an existing time mark.
		*   Note: Internally, the time marks are stored in time order. Modifying the time of a time mark may modify the index of all time marks.
		*   \param pIndex Index of the time mark.
		*   \param pTime The new time for the time mark.
		*   \return The new index of the modified time mark.
		*/
		int SetTimeMarkTime( int pIndex, FBTime pTime );

		/** Returns the name associated with a time mark.
		*   \param pIndex Index of the time mark.
		*   \return The name associated with the time mark.
		*/
		const char* GetTimeMarkName( int pIndex );

		/** Sets a new name for an existing time mark.
		*   \param pIndex Index of the time mark.
		*   \param pName The new name for the time mark.
		*   \return True if the operation is successful, false otherwise.
		*/
		bool SetTimeMarkName( int pIndex, const char* pName );

		/** Returns the action associated with a time mark.
		*   \param pIndex Index of the time mark.
		*   \return The action associated with the time mark.
		*/
		FBTimeMarkAction GetTimeMarkAction( int pIndex );

		/** Sets a new action for an existing time mark.
		*   \param pIndex Index of the time mark.
		*   \param pAction The new action for the time mark.
		*   \return True if the operation is successful, false otherwise.
		*/
		bool SetTimeMarkAction( int pIndex, FBTimeMarkAction pAction );

		/** Returns the color associated with a time mark.
		*   \param pIndex Index of the time mark.
		*   \return The color associated with the time mark.
		*/
		FBColor GetTimeMarkColor( int pIndex );

		/** Sets a new color for an existing time mark.
		*   \param pIndex Index of the time mark.
		*   \param pColor The new color for the time mark.
		*   \return True if the operation is successful, false otherwise.
		*/
		bool SetTimeMarkColor( int pIndex, FBColor pColor );

		/** Set real selection for layer.
		*	This method is used to specify if using the SelectLayer method of the FBAnimationLayer object will also select the FBComponent object. 
		*	In previous version of MotionBuilder, an animation layer was always selected, causing the layer to be displayed in the property editor. 
		*	Also, when parsing the selected objects in the SDK, a layer would always be there. 
		*	Setting this value to false will prevent this.
		*   \param pValue	True if future layer selection will also select the FBComponent object. 
    	*/
		void SetLayerRealSelection(bool pValue);

		/** Real selection for layer.
		*	Check the SetLayerRealSelection function for more information about this.
		*   \return	True if selecting a layer will also select the FBComponent of that layer. 
    	*/
		bool GetLayerRealSelection();

		/** Returns the next time mark index, based on the current local time.
		*   \return The next time mark index, -1 if any next time mark is available.
		*/
		int GetNextTimeMarkIndex();

		/** Returns the previous time mark index, based on the current local time.
		*   \return The previous time mark index, -1 if any previous time mark is available.
		*/
		int GetPreviousTimeMarkIndex();

		/** Offset the animation (FCurve keys) of this take object within a time range by a given offset time.
		*   Non-moving FCurve keys that are situated in the target range are deleted automatically, to preserve the animation being offset.
		*   \param pOffsetTime The offset time to apply.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the offset operation, -1 to offset the animation of all animations layers.
		*   \param pOnLockedProperties \c True to offset animation on locked properties, \c false to skip offsetting animation on locked properties.
		*   \return	\c True if the offset operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool OffsetAnimation(
			FBTime&							pOffsetTime,
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false );

		/** Offset the animation (FCurve keys) of this take object on given objects within a time range by a given offset time.
		*   Non-moving FCurve keys that are situated in the target range are deleted automatically, to preserve the animation being offset.
		*   \param pObjects Objects affected by the offset operation.
		*   \param pOffsetTime The offset time to apply.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the offset operation, -1 to offset the animation of all animations layers.
		*   \param pOnLockedProperties \c True to offset animation on locked properties, \c false to skip offsetting animation on locked properties.
		*   \return	\c True if the offset operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool OffsetAnimationOnObjects(
			FBArrayTemplate<FBBox*>*		pObjects,
			FBTime&							pOffsetTime,
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false );
	
		/** Offset the animation (FCurve keys) of this take object on given properties within a time range by a given offset time.
		*   Non-moving FCurve keys that are situated in the target range are deleted automatically, to preserve the animation being offset.
		*   \param pProperties Properties affected by the offset operation.
		*   \param pOffsetTime The offset time to apply.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the offset operation, -1 to offset the animation of all animations layers.
		*   \param pOnLockedProperties \c True to offset animation on locked properties, \c false to skip offsetting animation on locked properties.
		*   \param pPropertyComponents The component bit field considered when performing the offset operation, for properties having such components. By default, all components are considered. If a property don't have any component, this parameter is not affecting that property.
		*   \return	\c True if the offset operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool OffsetAnimationOnProperties(
			FBArrayTemplate<FBProperty*>*	pProperties,
			FBTime&							pOffsetTime,
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false,
			FBPropertyComponents			pPropertyComponents = kFBPropertyComponentAll );

		/** Delete animation (FCurve keys) of this take object within a time range.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the delete operation, -1 to delete the animation of all animations layers.
		*   \param pOnLockedProperties \c True to delete animation on locked properties, \c false to skip deleting animation on locked properties.
		*   \return \c True if the delete operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool DeleteAnimation(
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false );

		/** Delete animation (FCurve keys) of this take object on given objects within a time range.
		*   \param pObjects Objects affected by the delete operation.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the delete operation, -1 to delete the animation of all animations layers.
		*   \param pOnLockedProperties \c True to delete animation on locked properties, \c false to skip deleting animation on locked properties.
		*   \return \c True if the delete operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool DeleteAnimationOnObjects(
			FBArrayTemplate<FBBox*>*		pObjects,
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false );

		/** Delete animation (FCurve keys) of this take object on given properties within a time range.
		*   \param pProperties Properties affected by the delete operation.
		*   \param pStartTime Start of time range.
		*   \param pStopTime End of time range.
		*   \param pInclusive \c True to include within the time range the keys at pStartTime and pStopTime, \c false otherwise.
		*   \param pLayerID The animation layer ID being affected by the delete operation, -1 to delete the animation of all animations layers.
		*   \param pOnLockedProperties \c True to delete animation on locked properties, \c false to skip deleting animation on locked properties.
		*   \param pPropertyComponents The component bit field considered when performing the delete operation, for properties having such components. By default, all components are considered. If a property don't have any component, this parameter is not affecting that property.
		*   \return \c True if the delete operation is successful (at least one FCurve has been modified), \c false otherwise (e.g. no keys found within the time range, invalid layer ID, etc.).
		*/
		bool DeleteAnimationOnProperties(
			FBArrayTemplate<FBProperty*>*	pProperties,
			FBTime							pStartTime = FBTime::MinusInfinity,
			FBTime							pStopTime = FBTime::Infinity,
			bool							pInclusive = true,
			int								pLayerID = -1,
			bool							pOnLockedProperties = false,
			FBPropertyComponents			pPropertyComponents = kFBPropertyComponentAll );
    };

    FB_DEFINE_COMPONENT( FBSDK_DLL, Take );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBTimeWarpManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBTimeWarpManager );

    /**	Time Warp Manager
    *	Interface to the Time Warp Manager.
    */
    class FBSDK_DLL FBTimeWarpManager : public FBComponent
    {
        __FBClassDeclare(FBTimeWarpManager, FBComponent);

    public:
        typedef void (*TimeWarpChangeCallback)(void* pObject);

        /**	Constructor.
        *   \note   protect
        */
        FBTimeWarpManager();


        /** Call registered callbacks when changes related to TimeWarp happen.
        */
        void TimeWarpTakeChange();

        /** Clear all TimeWarp in a Take, and removed from the DataSet.
        *   \param pTake The Take to be cleared.
        */
        void TimeWarpClearTake(FBTake* pTake);

        /** Allocate container for the TimeWarp in one Take.
        *   \param pTake The Take allocated for.
        */
        void TimeWarpInitTake(FBTake* pTake);

        /** Copy all the TimeWarp in one Take, add to another Take.
        *   \param pDstTake Copy all TimeWarp to.
        *   \param pSrcTake Copy all TimeWarp from.
        */
        void TimeWarpCopyTake(FBTake* pDstTake, FBTake* pSrcTake );


        /** Add one TimeWarp to a Take.
        *   \param pTake The Take one TimeWarp added to.
        *   \param pTimeWarp The TimeWarp to be added.
        *   \param pNickNumber The Nick Number for the TimeWarp.
        */
        void TimeWarpAddToTake(FBTake* pTake, FBAnimationNode* pTimeWarp, int pNickNumber=0);

        /** Destroy the TimeWarp in a Take, and removed from the DataSet. Deprecated, use the RemoveTimeWarpFromScene method (the one with two parameters) instead.
	    *   This one should be called after calling the RemoveTimeWarpFromScene method (the one with one parameter).
        *   \param pTake The Take where the TimeWarp in.
        *   \param pTimeWarp The TimeWarp to be Destroyed.
        */
        K_DEPRECATED_2023 void DestroyTimeWarpFromTake(FBTake* pTake, FBAnimationNode* pTimeWarp);

        /** Remove a TimeWarp from Scene. Deprecated, use the RemoveTimeWarpFromScene method (the one with two parameters) instead.
        *   Any locked properties affected by this TimeWarp will be modified as well.
        *   \param pTimeWarp The TimeWarp to be Removed.
        */	
        K_DEPRECATED_2023 void RemoveTimeWarpFromScene(FBAnimationNode* pTimeWarp);

        /** Remove the given TimeWarp from scene and delete it from the given Take.
        *   Any locked properties affected by this TimeWarp will be modified as well.
        *   \param pTake The Take where the TimeWarp is in.
        *   \param pTimeWarp The TimeWarp to be removed and deleted.
        */	
        void RemoveTimeWarpFromScene( FBTake* pTake, FBAnimationNode* pTimeWarp );

        /** Get the count of TimeWarp in a Take.
        *   \param pTake The Take queried.
        *   \return the TimeWarp count.
        */
        kLong GetTimeWarpCount(FBTake* pTake);

        /** Get the TimeWarp in a Take At specific Index.
        *   \param pTake The Take queried.
        *   \param pIndex The index of the TimeWarp.
        *   \return TimeWarp at specific Index in a Take.
        */
        FBAnimationNode* GetTimeWarpAtIndex(FBTake* pTake, kLong pIndex);


        /** Get the Nick Number of one TimeWarp in a Take
        *   \param pTake The Take queried.
        *   \param pTimeWarp The TimeWarp queried.
        *   \return the Nick Number of one TimeWarp.
        */
        int GetTimeWarpNickNumber(FBTake* pTake, FBAnimationNode* pTimeWarp);

        /** Set the Nick Number of one TimeWarp in a Take.
        *   \param pTake The Take specific.
        *   \param pTimeWarp The TimeWarp specific.
        *   \param pNumber The Nick Number to set.
        *   \return True if set successfully.
        */
        bool SetTimeWarpNickNumber(FBTake* pTake, FBAnimationNode* pTimeWarp, int pNumber);

        /** Get the Nick Number of one TimeWarp At specific index in a Take
        *   \param pTake The Take queried.
        *   \param pIndex The index a TimeWarp at.
        *   \return the Nick Number of one TimeWarp At specific index.
        */
        int GetTimeWarpNickNumberAtIndex(FBTake* pTake, kLong pIndex);

        /** Get the timeWarp of specific Nick Number in a Take
        *   \param pTake The Take queried.
        *   \param pNumber the Nick Number of one TimeWarp.
        *   \return the TimeWarp of specific Nick Number.
        */
        FBAnimationNode* GetTimeWarpFromNickNumber(FBTake* pTake, int pNumber);

        /**. Find the Nick Number of one timewarp globally
        *   \param pTimeWarp The TimeWarp queried.
        *   \return the Nick Number of the timewarp.
        */	
        int FindTimeWarpNickNumberGlobal(FBAnimationNode* pTimeWarp);


        /** Apply the TimeWarp in a Take to an evaluation property, just connect the storing property for the TimeWarp to the evaluation property.
        *   \param pTake The Take where the TimeWarp in.
        *   \param pEvalProp The evaluation property to be applied on.
        *   \param pTimeWarp The TimeWarp to apply.
        *   \return True if apply successfully.
        */	
        bool ApplyTimeWarp(FBTake* pTake, FBProperty* pEvalProp, FBAnimationNode* pTimeWarp);

        /** Undo apply a timeWarp in a Take to an evaluation property, just disconnect the evaluation property from storing property.
        *   \param pTake The Take where the TimeWarp evaluation property connected is in.
        *   \param pEvalProp The evaluation property connected a TimeWarp in the storing property of one take.
        */	
        void RemoveTimeWarp(FBTake* pTake, FBProperty* pEvalProp );


        /** Register a callback Called when some changes related to TimeWarp happen.
        *   \param pCallback The callback to register.
        *   \param pObject The Parameter for the callback.
        */	
        void TimeWarpRegisterChangeEvent(TimeWarpChangeCallback pCallback, void* pObject);

        /** Unregister a call registered.
        *   \param pCallback The callback to be unregister.
        *   \param pObject The Parameter for the callback.
        */	
        void TimeWarpUnregisterChangeEvent(TimeWarpChangeCallback pCallback, void* pObject);


        /**. Create a TimeWarp with a specific name on the current Take.
        *   \param pName The name for the TimeWarp.
        *   \return the TimeWarp created.
        */	
        FBAnimationNode* TimeWarpCreateNew( const char* pName );


        /**. Rename a TimeWarp
        *   \param pTake The Take where the timeWarp is in.
        *   \param pTimeWarp The TimeWarp to be renamed.
        *   \param pNewName The new name for the TimeWarp.
        */	
        void TimeWarpRename( FBTake* pTake, FBAnimationNode* pTimeWarp, const char* pNewName );

        /**. Merge the TimeWarp to a function curve, and Remove the connection between the storing property and the evaluation property for the TimeWarp
        *   \param pTake The Take that the TimeWarp is in.
        *   \param pEvalProp the evaluation property the TimeWarp connected.
        *   \param pNode The function curve to merge on.
        *   \param pTimeWarpNode The TimeWarp to be merged.
        */	
        void TimeWarpMergeCurveNode( FBTake* pTake,FBProperty* pEvalProp, FBAnimationNode*  pNode, FBAnimationNode*  pTimeWarpNode );

        /**	Get the global object for this class
        *	\return	the global object.
        */
        static FBTimeWarpManager& TheOne();
    };

/**  Convert a FBProperty to a FbxProperty, useful to extract some properties to a FBX file. 
    *   \param pSourceProperty Property that will be exported.
    *   \param pSourceTake Exported animation data will be taken from this take.
    *   \param pDestinationObject The FbxObject object that will hold the FbxProperty.
    *   \param pDestinationScene The FbxScene object containing the FbxObject object.
    *   \param pDestinationStack The FbxAnimStack object that will contain the animation data.
    *   \param pCopyAnimation If set to true, the animation will be copied (default is true).
    *	\return	The newly created FbxProperty if the property didn't exist on the pDestinationObject, or the existing property that was used to receive the data.
*/
FBSDK_DLL FBXSDK_NAMESPACE::FbxProperty FBtoFBXProperty(FBProperty* pSourceProperty, FBTake* pSourceTake, FBXSDK_NAMESPACE::FbxObject* pDestinationObject, FBXSDK_NAMESPACE::FbxScene* pDestinationScene, FBXSDK_NAMESPACE::FbxAnimStack* pDestinationStack, bool pCopyAnimation=true);

/**  Convert a FbxProperty to a FBProperty, useful to extract some properties from a FBX file to a MotionBuilder scene. 
    *   \param pSourceProperty Property that will be imported.
    *   \param pSourceStack FbxAnimStack source object where the animation data will be taken.
    *   \param pDestinationObject The FBComponent object that will hold the FBProperty.
    *   \param pDestinationTake The FBTake object that will contain the animation data.
    *   \param pCopyAnimation If set to true, the animation will be copied (default is true).
    *   \param pLimitStart If set to a specific time, will remove the keys before that time (default is MinusInfinity).
    *   \param pLimitEnd If set to a specific time, will remove the keys after that time  (default is Infinity).
    *	\return	The newly created FBProperty if the property didn't exist on the pDestinationObject, or the existing property that was used to receive the data
*/
FBSDK_DLL FBProperty* FBXtoFBProperty(FBXSDK_NAMESPACE::FbxProperty* pSourceProperty, FBXSDK_NAMESPACE::FbxAnimStack* pSourceStack, FBComponent* pDestinationObject, FBTake* pDestinationTake, bool pCopyAnimation=true, FBTime pLimitStart=FBTime::MinusInfinity, FBTime pLimitEnd=FBTime::Infinity);

#ifdef FBSDKUseNamespace
}
#endif

#endif

