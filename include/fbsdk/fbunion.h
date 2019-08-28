#ifndef __FBUNION_H__
#define __FBUNION_H__
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

class KUnion;

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//! Forwarding of class and type declaration.
__FB_FORWARD(FBLogger);
__FB_FORWARD(FBVisitor);

////////////////////////////////////////////////////////////////////////////////////
// FBUnion
////////////////////////////////////////////////////////////////////////////////////
/**	FBUnion.
*	Generic union type for values, arrays, maps of any type.
*   Use Visit(FBVisitor &) to extract the contents of the FBUnion.
*   \note Internal Debug only. Users shouldn't use this code. 
*/
class FBSDK_DLL FBUnion  {
public:
	/**	Constructor.
	*	\param	pValue	For internal use only.
	*/
	FBUnion(KUnion *pValue = NULL);

    /**	Copy Constructor.
	*	\param	pValue - value to be copied.
	*/
    FBUnion(FBUnion const &pValue);

    /**	Assignment operator
	*	\param	pValue - value to be assigned to *this
    *   \return *this reference
	*/
    FBUnion &operator = (FBUnion const &pValue);

    /**	Destructor.
	*/
    ~FBUnion();


   /**	Static method to extract all internal properties and connections from an object
	*	\param	pObject - Object which we're extracting
    *	\param	pDepth - Depth of connections/properties we recurse
    *   \return FBUnion object containing composite of the Object dump.
	*/
    static FBUnion DumpObject (FBPlug const &pObject, int pDepth = 1);

    /* Visit - get the values contained from a FBUnion.
    *  First create a FBVisitor by inheritance and override each function.
    *  Call Visit with your visitor to have the values from the Union pushed to the Visitor.
    *  Each overridden operator () of your visitor will retrieve a value of a different type.
    *  See FBVisitor for details.
    */
	void Visit(FBVisitor &pVisitor) const;

    /**	Trace all the contents of the FBUnion
	*/
    void Trace(int pDepth = 20) const;

private:

    KUnion *mValue;
};



/**	FBVisitor - abstract base class to retrieve contents of a FBUnion.
*   Each operator () returns a different type value to the user.
*/
class FBSDK_DLL FBVisitor 
{
public:
    /**	Handle NULL returned value from the FBUnion
     */
    virtual void operator () ()    = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted int value from the FBUnion
     */
    virtual void operator () (int &pVal)    = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted int 64 value from the FBUnion
     */
    virtual void operator () (long long &pVal)    = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted unsigned int 64 value from the FBUnion
     */
    virtual void operator () (unsigned long long &pVal)    = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted double value from the FBUnion
     */
    virtual void operator () (double &pVal)   = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted float value from the FBUnion
     */
    virtual void operator () (float &pVal)   = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted bool value from the FBUnion
     */
    virtual void operator () (bool &pVal)     = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted FBTime value from the FBUnion
     */
    virtual void operator () (FBTime const &pVal) = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted String value from the FBUnion
     */
    virtual void operator () (const char *pVal) = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted HdlFBPlug from the FBUnion
     *  Handle may possibly be null if the FBPlug has been deleted.
        */
    virtual void operator () (HdlFBPlug const &pVal) = 0;

   /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted FBVector2d value from the FBUnion
     */
    virtual void operator () (FBVector2d const &pVal) = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted FBVector3d value from the FBUnion
     */
    virtual void operator () (FBVector3d const &pVal) = 0;

    /**	Handle returned value from the FBUnion
     *	\param	pVal - extracted FBVector4d value from the FBUnion
     */
    virtual void operator () (FBVector4d const &pVal) = 0;

    /** Handle returned map type stored in the FBUnion 
     *  will be followed by N calls returning (const char *pName, FBUnion& pVal) returning the contents of the map item by item.
     *  finally EndMap() is called to indicate all the contents of the map has been returned.
     */
    virtual void BeginMap() = 0;

    /** Handle returned item stored in a map
     *  \param pName - key name of the item stored in the map
     *  \param pVal  - value of the item stored in the map, 
     *  The value of the item returned is another FBUnion which can be Visited recursively to discover it's content
     */
    virtual void operator () (const char *pName, FBUnion const &pVal) = 0;

    /** Indicate all map content is returned
    */
    virtual void EndMap() = 0;

    /** Handle returned array type stored in the FBUnion 
     *  will be followed by N calls returning (int Index, FBUnion) returning the contents of the array item by item.
     *  finally EndArray() is called to indicate all the contents of the array has been returned.
     */
    virtual void BeginArray() = 0;

    /** Handle returned item stored in an array
     *  \param pIndex - index of the item stored in the array
     *  \param pVal   - value of the item stored in the map, 
     *  The value of the item returned is another FBUnion which can be Visited recursively to discover it's content
     */
    virtual void operator () (int pIndex, FBUnion const &pVal) = 0;

    /** Indicate all array content is returned
    */
    virtual void EndArray() = 0;

    /** Virtual destructor to enable safe inheritance.
    */
    virtual ~FBVisitor() { }
};

#endif // DOXYGEN_SHOULD_SKIP_THIS

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBUNION_H__ */
