#ifndef _PYFBMANIPULATOR_H_
#define _PYFBMANIPULATOR_H_

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBManipulator
// ======================================================================================
void FBManipulator_Init();

class PYSDK_DLL FBManipulator_Wrapper
	: public FBComponent_Wrapper
{
public:
	FBManipulator* mFBManipulator;

public:
	FBManipulator_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBManipulator = (FBManipulator*)pFBComponent; }

	virtual ~FBManipulator_Wrapper( void ) {}

public:
	//void					Pick			( FBManipulatorPickType pPickType );
	//int					PickGetCount	( void );
	//object				PickGetModel	( int pIndex );
	//FBVertex_Wrapper*	PickGetPoint	( int pIndex );

	//int					GetViwerWidth	( void );
	//int					GetViwerHeight	( void );

	//int					GetPanePosX		( void );
	//int					GetPanePosY		( void );
	//int					GetPaneWidth	( void );
	//int					GetPaneHeight	( void );

	//object				GetCurrentCamera( void );

	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Active,			bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( AlwaysActive,		bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Visible,			bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( DefaultBehavior,	bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ViewerText,		const char*);
};


#endif // _PYFBMANIPULATOR_H_