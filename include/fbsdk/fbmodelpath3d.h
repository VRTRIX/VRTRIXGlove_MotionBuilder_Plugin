#ifndef __FBMODEL_PATH3D_H__
#define __FBMODEL_PATH3D_H__
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

/** \file fbmodelpath3d.h
*    for model path3d class.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL 
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcore.h>
#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbmodel.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBModelPath3D
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelPath3D );

//! Path 3D model class.
class FBSDK_DLL FBModelPath3D : public FBModel
{
    __FBClassDeclare(FBModelPath3D, FBModel);

public:
    /**    Constructor.
    *    \param    pName    Name of Path 3D.
    *    \param    pObject    For internal use only(default=NULL).
    *
    *
    *   Python sample code:
    *    @code
        from pyfbsdk import *

        path = FBModelPath3D("Test")
        ## After creation, a path always contain two default keys.
        ## At this point, path.PathKeyGetCount() will be 2.
        path.Show = True
        ## Reposition the two default keys
        path.PathKeySet(0,FBVector4d(0,0,50,0))
        path.PathKeySet(1,FBVector4d(50,0,0,0))
        ## Add new keys at start and end of the path
        path.PathKeyStartAdd(FBVector4d(0,0,100,0))
        path.PathKeyEndAdd(FBVector4d(100,0,0,0))
        ## Insert keys inbetween existing keys
        path.PathKeyInsertAfter(1,FBVector4d(0,25,50,0))
        path.PathKeyInsertAfter(2,FBVector4d(50,25,0,0))
    *   @endcode
    */
    FBModelPath3D(const char* pName, HIObject pObject=NULL);

    //! Key property behavior.
    enum EKeyPropertyBehavior
    {
        eLegacyVector4, //!< 2014, 2015, 2016. Key property type is Vector4.
        eVector         //!< Introduced after 2016. Key property type is Vector, has improved control node behavior and support for auto control node.
    };
    typedef FBPropertyBaseEnum<EKeyPropertyBehavior> PropertyKeyPropertyBehavior;

    //! Path Length Unit enum. 
    enum ELengthUnitType 
    {
        eArchitectural = 0,
        eMI,
        eCM,
        eM,
        eKM
    };
    typedef FBPropertyBaseEnum<ELengthUnitType> PropertyUnitType;

    //! Path end cap style enum.
    enum EPathEndCapStyle
    {
        eNone, 
        eArrow
    };

    typedef FBPropertyBaseEnum<EPathEndCapStyle> PropertyPathEndCapStyle;  

    PropertyKeyPropertyBehavior KeyPropertyBehavior; //!< <b>Read Only Property:</b> Key property behavior.
    FBPropertyBool   AutoControlNode;           //!< <b>Read Write Property:</b> Automatically create key control nodes.
    FBPropertyDouble PathLength;                //!< <b>Read Only Property:</b> Path Length In Centimeter.
    FBPropertyString PathLengthInString;        //!< <b>Read Only Property:</b> Path Length Display String According To The Current Unit.
    PropertyUnitType PathLengthUnit;            //!< <b>Read Write Property:</b> Path Length Unit.
    FBPropertyBool   PathLengthShow;            //!< <b>Read Write Property:</b> Path length label display or not.
    FBPropertyDouble TextScale;                 //!< <b>Read Write Property:</b> Path Length label display scale.
    FBPropertyColorAndAlpha TextBackground;     //!< <b>Read Write Property:</b> Path Length label display background color.
    PropertyPathEndCapStyle PathEndCapStyle;    //!< <b>Read Write Property:</b> Path end cap display style.
    FBPropertyDouble PathEndCapScale;           //!< <b>Read Write Property:</b> Path end cap display scale.
    FBPropertyAnimatableColor Color;            //!< <b>Read Write Property:</b> Path display color in viewport.

    //--- Visual ------------------------------------------------------------------------------------------------------------------------

    /** Enable or disable displaying Curve Controls for the 3D model path.
    *    \param  pShow        \b true if curve controls are to be displayed \b false if not required
    */
    void        ShowCurveControls(bool pShow);

    /** Enable or disable displaying Curve Points for the 3D model path. 
    *    \param  pShow        \b true if curve points are to be displayed \b false if not required
    */
    void        ShowCurvePoints(bool pShow);


    //--- Key Manipulation --------------------------------------------------------------------------------------------------------------
    /** Query the number of keys present in the path. 
    *    \return  Number of keys present in the path 
    */
    int         PathKeyGetCount();

    /** Get path's key vector for at a particular key index. 
    *    \param  pKeyIndex         Key ID to set with
    *    \return Return the vector containing the value of the path key.
    */
    FBVector4d  PathKeyGet(int pKeyIndex);

    /** Set the local coordinate vector values for path at a particular key index.  
    *    \param  pKeyIndex       Key ID to set with
    *    \param  pTLocal         Vector to use to set values to Key
    *    \param  pUpdate         \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySet(int pKeyIndex, FBVector4d pTLocal, bool pUpdate=true);

    /** Set path's vectors for key, left tangent and right tangent at a particular key index. 
    *    \param  pKeyIndex                 Key ID to set key for left and right tangents
    *    \param  pKeyTLocal                Vector to use to set values to Key
    *    \param  pLeftTangentTLocal        Vector to use to set values to Key Left Tangent
    *    \param  pRightTangentTLocal       Vector to use to set values to Key Right Tangent
    *    \param  pUpdate                   \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetLeftRightTangent(int pKeyIndex, FBVector4d pKeyTLocal, FBVector4d pLeftTangentTLocal, FBVector4d pRightTangentTLocal, bool pUpdate=true); 

    /** Remove key at a particular index. 
    *    \param  pKeyIndex        Key ID at which key is to be removed.
    */
    void        PathKeyRemove(int pKeyIndex);

    /** Clear the path keys
    */
    void        PathKeyClear();

    //--- Tangent ----------------------------------------------------------------------------------------------------------------------

    /** Set path's key left tangent vector for designated index. 
    *    \param  pKeyIndex        Key ID at which left tangent is to be set
    *    \param  pTLocal       Vector to use to set values to Key
    *    \param    pUpdate        \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetLeftTangent(int pKeyIndex, FBVector4d pTLocal, bool pUpdate=true);

    /** Set 3D path's key right tangent vector for designated index. 
    *    \param  pKeyIndex        Key ID at which right tangent is to be set
    *    \param  pTLocal       Vector to use to set values to Key
    *    \param    pUpdate        \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetRightTangent(int pKeyIndex, FBVector4d pTLocal, bool pUpdate=true);

    /**  Get the path key left tangent's vector value for designated index.
    *    \param  pKeyIndex        Key ID at which left tangent value is required
    *    \return Vector containing value of left tangent
    */
    FBVector4d  PathKeyGetLeftTangent(int pKeyIndex);

    /** Get the path key right tangent's vector value for designated index.
    *    \param  pKeyIndex        Key ID to set with
    *    \return Vector containing value of left tangent
    */
    FBVector4d  PathKeyGetRightTangent(int pKeyIndex);

    /** Set derivative in X coordinate for a path tangent. This works only if key interpolation type is CUBIC and tangent mode is User, Break or Auto.
    *    \param  pKeyIndex        Key ID to set with
    *    \param  pDerivative      Value of the derivative to apply to tangent
    *    \param  pUpdate          \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetXDerivative(int pKeyIndex, double pDerivative, bool pUpdate);

    /** Set derivative in Y coordinate for a path tangent. This works only if key interpolation type is CUBIC and tangent mode is User, Break or Auto.     
    *    \param  pKeyIndex        Key ID to set with
    *    \param  pDerivative      Value of the derivative to apply to tangent
    *    \param  pUpdate          \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetYDerivative(int pKeyIndex, double pDerivative, bool pUpdate);

    /** Set derivative in Z coordinate for a path tangent. This works only if key interpolation type is CUBIC and tangent mode is User, Break or Auto. 
    *    \param  pKeyIndex        Key ID to set with
    *    \param  pDerivative      Value of the derivative to apply to tangent
    *    \param  pUpdate          \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetZDerivative(int pKeyIndex, double pDerivative, bool pUpdate);

    /** Set derivative in XYZ coordinates for a path tangent. This works only if key interpolation type is CUBIC and tangent mode is User, Break or Auto. 
    *    \param  pKeyIndex        Key ID to set with
    *    \param  pDerivative      Value of the derivative to apply to tangent
    *    \param  pUpdate          \b true if geometry update is required, \b false if not required (default=true)
    */
    void        PathKeySetXYZDerivative(int pKeyIndex, FBVector4d pDerivative, bool pUpdate);

    /** Get vector in XYZ coordinates for a path tangent. This works only if key interpolation type is CUBIC and tangent mode is User, Break or Auto. 
    *    \param   pKeyIndex        Key ID to set with
    *    \return  Vector with value for path's tangent XYZ derivatives
    */
    FBVector4d  PathKeyGetXYZDerivative(int pKeyIndex);

    /** Query the length of the left tangent.
    *    \param     pKeyIndex        Key ID to set with
    *    \return    Double value of the length of left tangent
    */
    double      PathKeyGetLeftTangentLength(int pKeyIndex);

    /** Query the value of the right tangent.
    *    \param     pKeyIndex        Key ID to set with
    *    \return    Double value of the length of right tangent 
    */
    double      PathKeyGetRightTangentLength(int pKeyIndex);

    //--- Path remove keys (editing) ----------------------------------------------------------------------------------------------------

    /** Query the number of keys present in the selected path. 
    *    \return Returns the number of keys in the selected path   
    */
    int         GetSelectedPathKeyCount();

    /** Remove the selected keys from the path. 
    */
    void        PathKeyRemoveSelected();

    //--- Keys Helpers ------------------------------------------------------------------------------------------------------------------

    /** Insert a new key at the start of the path.
    *    \return    Returns 0 since the new key becomes the first key. If path is invalid, returns 0.
    */
    int        InsertNewStartKey();

    /** Insert a new key at the end of the path.
    *    \return    Returns (N) where (N+1) is the new total number of keys, and since the new key becomes the Nth key (index starts from 0). If path is invalid, returns 0.
    */
    int        InsertNewEndKey();

    /** Adds a new key to the start of the path (with time gap of 1 sec). The derivative value for the new key is copied from the right tangent of the first key. 
    *    \param  pTLocal        Vector value for the new added Key
    *    \return    Returns 0 since the new key becomes the first key. If path is invalid, returns 0.
    */
    int        PathKeyStartAdd(FBVector4d pTLocal);

    /** Adds a new key to the end of the path (with time gap of 1 sec). The derivative value for the new key is copied from the left tangent of the last key. 
    *    \param  pTLocal        Vector value for the new added Key
    *    \return    Returns (N) where (N+1) is the new total number of keys, and since the new key becomes the Nth key (index starts from 0). If path is invalid, returns 0.
    */
    int        PathKeyEndAdd(FBVector4d pTLocal);

    /** Adds a new key immediately after the specified key ID (with time gap of 1 sec). The following keys are all shifted by 1 sec.
    *    \param  pKeyIndex      Key ID to insert after. If key ID < 0 then the behavior is the same as PathKeyStartAdd. If key ID >= PathKeyGetCount-1 then the behavior is the same as PathKeyEndAdd.
    *    \param  pTLocal        Vector value for the new added Key
    *    \return    Returns the newly inserted key ID.
    */
    int        PathKeyInsertAfter(int pKeyIndex, FBVector4d pTLocal);

    //--- Animated Keys - Properties and Control Nodes ----------------------------------------------------------------------------------

    /** Get the path key's corresponding property. Only works when KeyPropertyBehavior is eVector.
    *    \param  pKeyIndex        Key ID to get
    *    \return Path key's corresponding property if successful, otherwise NULL.
    */
    FBProperty* PathKeyGetProperty(int pKeyIndex);

    /** Get the path key's control node. Only works when KeyPropertyBehavior is eVector.
    *    \param  pKeyIndex        Key ID to get
    *    \return Path key's corresponding control node if successful, otherwise NULL.
    */
    FBModel*   PathKeyGetControlNode(int pKeyIndex);

    /** Set the path key's control node. Only works when KeyPropertyBehavior is eVector and AutoControlNode is disabled.
    *    \param  pKeyIndex        Key ID to set
    *    \param  pControlNode     Model to set as path key's control node.
    *    \return True if successful, otherwise false.
    */
    bool       PathKeySetControlNode(int pKeyIndex, FBModel* pControlNode);

    //--- Curve -------------------------------------------------------------------------------------------------------------------------
    /** Adds a new key either at the start, end or along the path as per specified. 
    *    \param  pTotalPercent     Double value indicating where the key is to be added. If < 0, key added before start of the path,
    *                              if > 0, key added at end of path, otherwise it is added somewhere along the path depending on value specified
    *    \param  pTLocal        Vector to use to set values to Key
    *    \return  Index as integer for the path key added 
    *    \deprecated use PathKeyStartAdd(), PathKeyEndAdd(), PathKeyInsertAfter(), or PathKeySet() instead.
    */
    K_DEPRECATED_2017 int Total_PathKeyAdd(double pTotalPercent, FBVector4d pTLocal, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Query whether a percentage value has a key associated at that point in the path.
    *    \param  pTotalPercent        Double value (as percentage) at which the path would be queried for existence of key
    *    \return A valid key index in integer if key is present, otherwise -1
    */
    int        Total_IsPathKey(double pTotalPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's vector at a particular point within the curve, in global coordinates.  
    *    \param  pTotalPercent        Double value (as percentage) at which the path vector would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Total_GlobalPathEvaluate(double pTotalPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's vector at a particular point within the curve, in local coordinates.  
    *    \param  pTotalPercent        Double value (as percentage) at which the path vector would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Total_LocalPathEvaluate(double pTotalPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's derivative at a particular point within the curve, in global coordinates.  
    *    \param  pTotalPercent        Double value (as percentage) at which the path derivative would be computed
    *    \return    Derivative value at the required point in the path
    */
    FBVector4d Total_GlobalPathEvaluateDerivative(double pTotalPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's derivative at a particular point within the curve, in local coordinates.  
    *    \param  pTotalPercent        Double value (as percentage) at which the path derivative would be computed
    *    \return    Derivative value at the required point in the path
    */
    FBVector4d Total_LocalPathEvaluateDerivative(double pTotalPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Adds a new key either at the start, end or along the path as per specified. 
    *    \param  pSegmentPercent     Double value indicating where the key is to be added. If < 0, key added before start of the path,
    *                              if > 0, key added at end of path, otherwise it is added somewhere along the path depending on value specified
    *    \param  pTLocal           Vector to use to set values to Key
    *    \return    Vector value at the required point in the path
    *    \deprecated use PathKeyStartAdd(), PathKeyEndAdd(), PathKeyInsertAfter(), or PathKeySet() instead.
    */
    K_DEPRECATED_2017 int Segment_PathKeyAdd(double pSegmentPercent, FBVector4d pTLocal, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Query whether a percentage value has a key associated at that point in the path.
    *    \param  pSegmentPercent        Double value (as time) at which the path would be queried for existence of key
    *    \return A valid key index in integer if key is present, otherwise -1
    */
    int        Segment_IsPathKey(double pSegmentPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's vector at a particular point within the curve, in global coordinates.  
    *    \param  pSegmentPercent        Double value (as time) at which the path vector would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Segment_GlobalPathEvaluate(double pSegmentPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's vector at a particular point within the curve, in local coordinates.  
    *    \param  pSegmentPercent        Double value (as time) at which the path vector would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Segment_LocalPathEvaluate(double pSegmentPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's derivative at a particular point within the curve, in global coordinates.  
    *    \param  pSegmentPercent        Double value (as time) at which the path derivative would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Segment_GlobalPathEvaluateDerivative(double pSegmentPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get the path's derivative at a particular point within the curve, in local coordinates.  
    *    \param  pSegmentPercent        Double value (as time) at which the path derivative would be computed
    *    \return    Vector value at the required point in the path
    */
    FBVector4d Segment_LocalPathEvaluateDerivative(double pSegmentPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    //--- Key Type Converter ------------------------------------------------------------------------------------------------------------

    /** Converting one key type Total (percent) to Segment (time).
    *    \param  pPercent        Double value (as percentage)
    *    \return  Double value which represents the corresponding time.
    */
    double     ConvertTotalPercentToSegmentPercent(double pPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Converting one key type Segment (time) to Total (percent).
    *    \param  pPercent        Double value (as time) 
    *    \return  Double value which represents the corresponding percentage
    */
    double     ConvertSegmentPercentToTotalPercent(double pPercent, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get factor for multiplying the derivative of a key for segment mode.
    *    \return  Returns the derivative multiplication factor
    */
    double     ConvertToSegmentPercentFactor();

    /** Get factor for multiplying the derivative of a key for total mode. 
    *    \return  Returns the time factor
    */
    double     ConvertToTotalPercentFactor();
    
    /** Update path geometry explicitly
    */
    void      UpdateGeometry();
};

#ifdef FBSDKUseNamespace
}
#endif

#endif