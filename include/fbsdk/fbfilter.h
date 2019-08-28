#ifndef __FBFILTER_H__
#define __FBFILTER_H__
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

/**	\file fbfilter.h
*	Derive new filters using the FBFilter class.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBFilter				);
__FB_FORWARD( FBPropertyListFilter	);

FB_DEFINE_COMPONENT( FBSDK_DLL, Filter		);
FB_DEFINE_COMPONENT( FBSDK_DLL, FilterLayout	);

/** Filter types.
*	A filter can be of one or both types in order to process data
*	on single or multiple curves of data.
*	Ex: a gimble killer filter needs to be of type vector because
*	the three curves are inter-dependant.
*/
enum FBFilterType { 
	kFBFilterNumber = 1 << 0,	//!< Filter single FCurves.
	kFBFilterVector = 1 << 1,	//!< Filter a vector (3 FCurves).
};

/**	Filter class registration.
*	\param	ClassName			Filter class name.
*	\param	Label				Short description.
*	\param	Description			Long description.
*	\param	FilterType			Type of filter (see FBFilterType).
*	\param	FilterErrorTable	Error strings for filter operations.
*	\param	FilterErrorCount	Number of elements in FilterErrorTable.
*	\param	IconFilename		Filename of associated icon.
*/
#define FBRegisterFilter( ClassName, Label, Description, FilterType, FilterErrorTable, FilterErrorCount, IconFilename ) \
	HIObject RegisterFilter##ClassName( HIObject pOwner,const char * /*pName*/,void * /*pData*/) \
	{ \
	    ClassName *Class = new ClassName( ); \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		int lFilterType = FilterType; \
		if( (lFilterType) & kFBFilterNumber )	FBRegisterObject( ClassName,"Filter/DataType/Number",Label,Description,RegisterFilter##ClassName,true, IconFilename );	\
		if( (lFilterType) & kFBFilterVector )	FBRegisterObject( ClassName,"Filter/DataType/Vector",Label,Description,RegisterFilter##ClassName,true, IconFilename );	\
	}

/**	Filter class declaration.
*	\param	ClassName	Filter class name.
*	\param	Parent		Parent class name.
*/
#define FBFilterDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName( HIObject pO = NULL ):Parent(pO) { FBClassInit; } \
  private:

/**	Filter class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBFilterImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )



////////////////////////////////////////////////////////////////////////////
// FBFilterManager
////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBFilterManager );
FB_FORWARD( FBFilter );

/** Filter manager.
*   This class provides list of all available filter types and a factory
*   method in order to create an instance of the desired filter type.
*
*   This manager will list both built-in and plug-in filters.
*
*   See the class FBFilter for more details.
*
*   @note   Filter type names are not localised, and are the same as
*           presented in the GUI.
*
*   The following sample code shows how to use C++ or Python to create
*   an instance of the orfilter_template filter and set one of its property.
*   For the sample code to work, the plugin must have been compiled 
*   and copied in the plugins folder prior to the application startup.
*
*   Sample C++ code:
*   
*   @code

    // Create a filter of a known type. In this case the sample filter
    // provided with the samples: orfilter_template.

    FBFilterManager lFilterManager;

    FBFilter* lFilter = lFilterManager.CreateFilter( "OR - Filter Template" );

    // Set one of the filter property:
    FBPropertyDouble* lPropDouble = (FBPropertyDouble*)lFilter->PropertyList.Find( "Test Double" );
    if( lPropDouble )
    {
        (*lPropDouble) = 2.0;
    }

    // Now we can apply the filter on an FCurve.
    // ...

    // And when we are done, destroy it.
    lFilter->FBDelete();
    lFilter = NULL;

*   @endcode
*  
*
*
*   Sample Python code:
*
*   @code

    from pyfbsdk import *

    # Create a filter of a known type. In this case the sample filter
    # provided with the samples: orfilter_template.

    lFilterManager = FBFilterManager()

    lFilter = lFilterManager.CreateFilter( 'OR - Filter Template' );

    # Set one of the filter property:
    lPropDouble = lFilter.PropertyList.Find( 'Test Double' );
    if lPropDouble: lPropDouble.Data = 2.0

    # Now we can apply the filter on an FCurve.
    # ...

    # And when we are done, destroy it.
    lFilter.FBDelete()

*   @endcode
*/
class FBSDK_DLL FBFilterManager
{
    /** Disabled copy constructor.
    *
    *   Voluntarily making the copy constructor unavailable.
    */
    FBFilterManager( const FBFilterManager& );

    /** Disabled assignment operator.
    *
    *   Voluntarily making the assignment operator unavailable.
    */
    FBFilterManager& operator=( const FBFilterManager& );

public:

    //! Constructor.
    FBFilterManager();

    /** Destructor.
    *
    *   @warning    The destructor is non-virtual, meaning that this class is not
    *               meant to be used as a base class.
    */
    ~FBFilterManager();

    /** Create a filter instance according to the filter type requested.
    *   @param  pFilterTypeName String describing the type of the desired filter, as obtained from list FilterTypeNames.
    *   @return A pointer to a filter instance, or a NULL if the type name was invalid.
    */
    FBFilter* CreateFilter( const char* pFilterTypeName );

    /** List of available filters.
    *
    *   This list does provide the complete list of available filters, both
    *   system defined and user defined.
    *
    *   @warning    This list should not be modified. Changes to its value
    *               will not affect the shaders supported.
    */
    FBStringList FilterTypeNames;
};


////////////////////////////////////////////////////////////////////////////////////
// FBFilter - Filter layer on top of internals.
////////////////////////////////////////////////////////////////////////////////////
/** Filters are used to modify motion capture data.
*   Filters are objects which can be applied on a FCurve, or the animation node 
*   associated with an animated object property, to modify shape and number of keys.
*   Filters can be created from the GUI, using the Filters tool, or programmatically
*   with an instance of a FBFilterManager.
*
*   The filter properties can be found in the object's PropertyList data member. They
*   will use the same name, and be of the same type, as what can be seen in the GUI.
*
*   @warning    Instances of FBFilter should be created with the help of the class
*               FBFilterManager. Only internal application code should call the
*               FBFilter's class constructor.
*
*   Sample C++ code:
*   
*   @code

    FBFilterManager lFilterManager;

    // Create a filter instace.
    FBFilter* lFilter = lFilterManager.CreateFilter( "Key Reducing" );

    if( lFilter )
    {
        // Create a FCurve and populate it with keys.
        FBFCurve lCurve( "Temp Curve" );
        for( int lIdx = 1; lIdx < 10; ++lIdx )
        {
            FBTime lTime( 0, 0, 0, lIdx * 5 );
            lCurve.KeyAdd( lTime, lIdx * 5 );
        }

        FBTrace( "Keys before: %d\n", lCurve.Keys.GetCount() ); // Should be 9.

        // Apply the key reducing filter.
        lFilter->Apply( &lCurve );

        FBTrace( "Keys after: %d\n", lCurve.Keys.GetCount() ); // Should be 2.
    }

*   @endcode
*  
*
*
*   Sample Python code:
*
*   @code

    from pyfbsdk import *

    # Find a given model in the scene.
    lModel = FBFindModelByLabelName( 'Cube' )

    if lModel:
        # Create a Key Reducing filter.
        lFilter = FBFilterManager().CreateFilter( 'Key Reducing' )

        if lFilter:
            # Set the filter's precision to 2.0, and apply it to
            # the object's translation animation.
            lFilter.PropertyList.Find( 'Precision' ).Data = 2.0
            lFilter.Apply( lModel.Translation.GetAnimationNode(), True )

*   @endcode
*/
class FBSDK_DLL FBFilter : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBFilter, FBComponent );
public:
	/** Constructor.
	*	\param	pObject				For internal use only (default is NULL).
	*/
	FBFilter( HIObject pObject = NULL  );

    /**	Apply the filter to an FCurve.
    *   This is one of the two apply method that is meant to be called by client code.
    *   The FCurve can be a standalone independant FCurve, or can be associated to
    *   an object's animated property.
	*	\param	pCurve	FCurve to apply filter to.
	*	\return	\b true if successful.
	*/
	virtual bool Apply( FBFCurve* pCurve );

    /**	Apply the filter to an animation node.
    *   This is the other apply method and it can be used on an object's animation node.
	*	\param	pNode		Node to apply filter to.
	*	\param	pRecursive	Recursively apply filter on child nodes?
	*	\return	\b true if successful.
	*/
	virtual bool Apply( FBAnimationNode* pNode, bool pRecursive );

	/** Reset properties.
    *   @warning    This method will only work on plug-in filters, not built-in types.
    */
	virtual void Reset();


	FBPropertyTime Start;	//!< <b>Read Write Property:</b> Start time of the filtering region
	FBPropertyTime Stop;	//!< <b>Read Write Property:</b> Stop time of the filtering region
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* _FB_FILTER_H_ */
