#ifndef __FBFBX_H__
#define __FBFBX_H__
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

/**	\file fbfbx.h
*	FBX file format interface.
*	This file contains the necessary data structures and classes to
*	interface with the FBX file format, allowing the user to save device
*	settings, tool preferences and other customizable features in a
*	scene.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbfbxoptions.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBFbx
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBScene );
#if !defined(K_NO_CHARACTER)
FB_FORWARD( FBCharacter );
#endif
FB_FORWARD( FBPlotOptions );
FB_DEFINE_COMPONENT( FBSDK_DLL, Scene );

__FB_FORWARD( FBFbxObject );
__FB_FORWARD( FBModel );

/** FBX file interface.
*	When an object is stored/retrieved, it receives a callback 
*	(FbxStore/FbxRetrieve). This callback receives an object of type
*	FBFbxObject as a parameter in order to interact with the FBX file.
*/
class FBSDK_DLL FBFbxObject : public FBComponent {
	__FBClassDeclare( FBFbxObject,FBComponent );
public:
	/**	Constructor.
    *   Client code cannot instantiate objects of this class. Instances of
    *   FBFbxObject are passed as parameters for the methods FbxStore and
    *   FbxRetrieve of some Open Reality classes.
	*	\param	pObject	For internal use only.
	*/
	FBFbxObject(HIObject pObject);

	/**	Begin writing a field named \e pFieldName.
	*	\param	pFieldName	Name to give to field in FBX file.
	*/
	void FieldWriteBegin(const char *pFieldName);

	//!	End of field writing.
	void FieldWriteEnd();

	/**	Begin reading from a field named \e pFieldName.
	*	\param	pFieldName	Name of field to read from.
	*	\return \b true if the field was found.
	*/
	bool FieldReadBegin(const char *pFieldName);
	
	//! End of field reading.
	void FieldReadEnd();

	/**	Get the number of items to read for the current field.
	*	\return The number of field items for the current field.
	*/
	int	 FieldReadGetCount();

	//@{
	/**	Write data to the current field.
	*	\param	pValue	Value (int,char,double) to write to current field.
	*/
	void	FieldWriteI( int pValue );
	void	FieldWriteC( const char *pValue );
	void	FieldWriteD( double pValue );
	//@}

	//@{
	/**	Write data to field \e pFieldName.
	*	\param	pFieldName	Name of the field to write data to.
	*	\param	pValue	Value (int,char,double) to write to field.
	*/
	void	FieldWriteI( const char *pFieldName, int pValue );
	void	FieldWriteC( const char *pFieldName, const char *pValue );
	void	FieldWriteD( const char *pFieldName, double pValue );
	//@}

	//@{
	/**	Read data from the current field.
	*	\return	Value (int,char,double) to read from current field.
	*/
	int		FieldReadI();
	const char* FieldReadC();
	double	FieldReadD();
	//@}

	//@{
	/**	Read data from field \e pFieldName.
	*	\param	pFieldName	Name of the field to read data from.
	*	\return	Value (int,char,double) to read from field.
	*/
	int		FieldReadI(const char *pFieldName);
	const char* FieldReadC(const char *pFieldName);
	double	FieldReadD(const char *pFieldName);
	//@}

	/**	Write an object reference (handle) to the field \e pFieldName.
	*	\param	pFieldName	Field name to assign to handle.
	*	\param	pObject		Handle to object to write to FBX.
	*/
	void   FieldWriteObjectReference (const char* pFieldName,FBComponent* pObject);

	/**	Write an object reference (handle) to the current field.
	*	\param	pObject		Handle to object to write to FBX.
	*/
	void   FieldWriteObjectReference (FBComponent* pObject);

	/**	Read an object reference from the field \e pFieldName.\
    *   The returned reference is a HIObject which is an internal application object.
    *   Calling 'FBGetFBComponent()' will provide a FBComponent wrapper object with which it is possible to interact.
	*	\param	pFieldName	Field name to read from.
	*	\return	Handle to internal object.
	*/
	HIObject FieldReadObjectReference (const char * pFieldName);

	/**	Read an object reference from the current field.
    *   The returned reference is a HIObject which is an internal application object.
    *   Calling 'FBGetFBComponent()' will provide a FBComponent wrapper object with which it is possible to interact.
	*	\return	Handle to internal object.
	*/
	HIObject FieldReadObjectReference ();

	/**	Begin writing a block in the FBX file.
	*	A block in an FBX file is to re-group different field together, in the same way a
	*	a namespace functions in C++. This permits the use of fields with the same name in 
	*	the FBX file, which is impossible unless they are in different blocks of data.
	*/
	void	FieldWriteBlockBegin ();

	/**	Begin writing a block in the FBX file.
	*	A block in an FBX file is to re-group different field together, in the same way a
	*	a namespace functions in C++. This permits the use of fields with the same name in 
	*	the FBX file, which is impossible unless they are in different blocks of data.
	*	\param pFieldName	Name to give to block.
	*/
	void	FieldWriteBlockBegin (const char *pFieldName);

	//!	Finish writing a block of data.
	void	FieldWriteBlockEnd   ();

	/**	Is current reading a block of data?
	*	\return \b true if current data is a block.
	*/	
	bool	FieldReadIsBlock   ();

	/**	Begin reading a block of data.
	*	\return	\b true if current read is from a block.
	*/
	bool	FieldReadBlockBegin();

	//!	Finish reading data from a block
	void	FieldReadBlockEnd  ();

	/**	Get the full file path for \e pFilename.
	*	\param	pFilename	Name of file to get path for.
	*	\return	Path of file \e pFilename.
	*/
	const char* GetFullFilePath(const char *pFilename);
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif
