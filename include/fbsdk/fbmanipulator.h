#ifndef __FBMANIPULATOR_H__
#define __FBMANIPULATOR_H__
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

/**	\file fbmanipulator.h
*	Create new manipulators using the FBManipulator class.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbcontrols/fbcontrols.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_FORWARD( FBModel );

FB_DEFINE_COMPONENT( FBSDK_DLL, Manipulator );
FB_DEFINE_COMPONENT( FBSDK_DLL, Camera	);

/**	Manipulator class registration.
*	\param	ClassName		Manipulator class name.
*	\param	Label			Short description.
*	\param	Description		Long description.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterManipulator( ClassName, Label, Description, IconFilename ) \
	HIObject RegisterManipulator##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName( Label ); \
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
		FBRegisterObject( ClassName,"Manipulators",Label,Description,RegisterManipulator##ClassName,true, IconFilename );	\
	}

/**	Manipulator class declaration.
*	\param	ClassName	Manipulator class name.
*	\param	Parent		Parent class.
*/
#define FBManipulatorDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/**	Manipulator class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBManipulatorImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBManipulator
////////////////////////////////////////////////////////////////////////////////////
//! Types of manipulator picking.
enum FBManipulatorPickType		{ 
	FBPickObjects,		//!< Pick objects.
	FBPickPoints,		//!< Pick points.
	FBPickSurfaces		//!< Pick surfaces.
};

__FB_FORWARD( FBManipulator );

//! Manipulator class
class FBSDK_DLL FBManipulator : public FBComponent {
	__FBClassDeclare( FBManipulator,FBComponent );
public:
	/**	Constructor.
	*	\param	pName		Name of manipulator.
	*	\param	pObject		Internal parent object(default=NULL).
	*/
	FBManipulator(const char* pName, HIObject pObject=NULL);

	virtual bool FBCreate	() override;

	// ***** Picking routines ******
	//---- Rectangle -----

	/**	Pick rectangle start.
	*	\param	pType	Picking method.
	*/
    void		PickRectStart(FBManipulatorPickType pType);

	//!	Pick rectangle motion.
	void		PickRectMotion();

	//! Stop rectangle pick.
    void		PickRectStop();

	//---- Single Pick -----

	/**	Single pick.
	*	\param	pType	Picking method.
	*/
	void		Pick(FBManipulatorPickType pType);

	//---- Pick Result -----

	/**	Get number of items picked.
	*	\return	Number of items picked.
	*/
	int			PickGetCount();

	/**	Get model at index \e pIndex in list of picked items.
	*	\param	pIndex	Index to get item at.
	*	\return	Handle to model picked at \e pIndex in pick list.
	*/
	FBModel*	PickGetModel(int pIndex);

	/**	Get point at \e pIndex on pick path in 3D.
	*	\param	pIndex	Index of pick point to get.
	*	\return	3D pick point on the surface of the object at \e pIndex along pick path.
	*/
	FBVertex	PickGetPoint(int pIndex);

	/**	Get rendering area width.
	*	\return Render area width.
	*/
	int			GetViewerWidth();

	/**	Get rendering area height.
	*	\return Render area height.
	*/
	int			GetViewerHeight();

	/**	Get sub-pane origin X offset from the viewer origin.
	*	\return Sub-pane X offset.
	*/
	int			GetPanePosX();

	/**	Get sub-pane origin Y offset from the viewer origin.
	*	\return Sub-pane Y offset.
	*/
	int			GetPanePosY();

	/**	Get sub-pane width.
	*	\return Sub-pane area width.
	*/
	int			GetPaneWidth();

	/**	Get sub-pane height.
	*	\return Sub-pane area height.
	*/
	int			GetPaneHeight();

	// Render begin/end 
	/**	Transform the current matrix to the reference of a given model.
	*	This call is used to move into Model space in order to draw with respect
	*	to the model specified by \e pModel.
	*	\param	pModel	Model now at transformation origin.
	*/
	void		FBModelRenderBegin(FBModel* pModel);

	//! End model matrix sequence.
	void		FBModelRenderEnd();

	/**	Input function.
	*	\param	pMouseX		Mouse X position.
	*	\param	pMouseY		Mouse Y position.
	*	\param	pAction		Mouse action.
	*	\param	pButtonKey	Keyboard key pressed.
	*	\param	pModifier	Key modifier (CTRL, ALT, SHIFT)
	*	\return	\b true if successful.
	*	\remarks This function is called by the UI thread.
	*/
	virtual bool	ViewInput(int pMouseX, int pMouseY, FBInputType pAction, int pButtonKey,int pModifier); // same as FBView

	/** Expose function.
	*	\remarks This function is called by the UI thread.
	*/
	virtual void	ViewExpose();

public:
	FBPropertyBool              Active;                     //!< <b>Read Write Property:</b> Is manipulator active?
	FBPropertyBool              AlwaysActive;               //!< <b>Read Write Property:</b> Is manipulator always active?
	FBPropertyBool              Visible;                    //!< <b>Read Write Property:</b> Is manipulator visible?
	FBPropertyBool              DefaultBehavior;            //!< <b>Read Write Property:</b> Using default manipulator behavior?
	FBPropertyString            ViewerText;                 //!< <b>Read Write Property:</b> Text displayed in view.
	FBPropertyCamera            CurrentCamera;              //!< <b>Read Only Property:</b> Current camera.
	FBPropertyBool              ConsumeEvent;               //!< <b>Read Write Property:</b> Is manipulator consuming event? If true, this will prevent other manipulators from being called.
															//								 Custom manipulators will be called first, before the standard MotionBuilder manipulators.
															//								 Remark: If your manipulator consumes an event, it must consumes all the event until the transaction is finished.
															//										 For example, if you consume the mouse down but not the mouse up, the other manipulator might be in an inconsistent state.
};

////////////////////////////////////////////////////////////////////////////////////
// Property list
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_LIST( FBSDK_DLL, Manipulator );

//! \b PropertyList: Manipulator.
class FBSDK_DLL FBPropertyListManipulator : public FBPropertyBaseList< FBManipulator* >
{
	/** Add a manipulator to the list
	*	\param	pItem	Manipulator to add.
	*	\return	Number of manipulators in list after operation.
	*/
	virtual int	 Add	( FBManipulator* pItem );
	/** Remove a manipulator from the list at \e pIndex.
	*	\param	pIndex	Index of manipulator to remove.
	*/    
	virtual void RemoveAt( int pIndex );
public:
	/**	Get the manipulator at a given index.
	*	\param	pIndex	Manipulator index.
	*	\return	Manipulator at index \e pIndex.
	*/
	virtual FBManipulator* operator[](int pIndex);
	/** Get the number of manipulators.
	*	\return	Number of manipulators.
	*/
	virtual int  GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBManipulatorTransform
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBManipulatorTransform );

FB_DEFINE_COMPONENT( FBSDK_DLL, ManipulatorTransform );

//! Manipulator transform stles.
enum FBManipulatorTransformType { 
	kFBManipulatorTransformNone,		//!< No manipulator.
	kFBManipulatorTransformTranslation,	//!< Translation manipulator.
	kFBManipulatorTransformRotation,	//!< Rotation manipulator.
	kFBManipulatorTransformScaling		//!< Scaling manipulator.
};

FB_DEFINE_ENUM( FBSDK_DLL, ManipulatorTransformType );

//! Manipulator class
class FBSDK_DLL FBManipulatorTransform : public FBManipulator {
	__FBClassDeclare( FBManipulatorTransform,FBManipulator );
public:
	/**	Constructor.
	*	\param	pName		Name of manipulator.
	*	\param	pObject		Internal parent object (default is NULL).
	*/
	FBManipulatorTransform(const char *pName,HIObject pObject=NULL);

	FBPropertyManipulatorTransformType		Type;						//!< <b>Property:</b> Type of selection event.
	FBPropertyBool							IconVisible;				//!< <b>Property:</b> Is icon visible?
	FBPropertyBool							VertexSelectionEnabled;		//!< <b>Property:</b> Is vertex selection enabled?
	FBPropertyBool							VertexManipulationEnabled;	//!< <b>Property:</b> Is vertex manipulation enabled?
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
