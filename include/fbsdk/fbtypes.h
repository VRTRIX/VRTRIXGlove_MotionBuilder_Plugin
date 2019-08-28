#ifndef __FBTYPES_H__
#define __FBTYPES_H__
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

/**	\file fbtypes.h
*	Types & macros.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
  #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbversion.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif


/**	Forwarding of class and typedef declaration.
*	\param	ClassName	Class to be forwarded.
*/
#define FB_FORWARD( ClassName ) class ClassName


/** Forwarding of class and typedef declaration.
*	\param ClassName The name of the class to be forwarded.
*/
#define __FB_FORWARD( ClassName ) \
	FB_FORWARD( ClassName ); \
	class Data##ClassName


//!	Description of the different store/retrieve passes of the FBX format.
enum kFbxObjectStore   { 
	kInit=1,		//!< Initialization before store.
	kAttributes=2,	//!< Attributes.
	kRelations=4,	//!< Relations.
	kAll=7,			//!< Mask for Attributes and Relations (for compatibility with SDK earlier that 6.0).
	kCleanup=8,		//!< Last pass for cleanup (retrieve only).
	kData=16,		//!< Special data pass.
	kMerge=32		//!< Merge pass.
};

////////////////////////////////////////////////////////////////////////////////////
// New classes
////////////////////////////////////////////////////////////////////////////////////
//! Two dimensional vector (template).
template <class tType> class FBSDK_DLL FBVector2
{ 
  private:
  public:
	tType mValue[2]; //!< Values

  public:

    //! Constructor.
	FBVector2();

    //! Copy Constructor
    FBVector2( const FBVector2& pVector );

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBVector2( tType *pValue );

	/**	Constructor.
	*	\param	p1	First element
	*	\param	p2	Second element.
	*/
	FBVector2( tType p1,tType p2 );

	/**	Initialization function.
	*	Clear vector.
	*/
	void Init();

	/**	Overloaded [] operator.
	*	\param	pIndex	Element to access.
	*	\return	Element at \e pIndex.
	*/
	tType &operator[](int pIndex);

	/**	Set vector from an array.
	*	\param	pValue	Array to copy value from.
	*/
	void Set( tType *pValue );

	/**	Overloaded cast to array.
	*	\return	Array of items of \e tType.
	*/
    operator tType *() const;

    /** Overloaded equal operator.
    *   \param  pVector     Vector to copy.
    *   \return this vector as a const.
    */
    const FBVector2& operator = ( const FBVector2& pVector );
    
    /** not equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if not equal.
    */
    bool operator != ( const FBVector2& pVector );

    /** equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if equal.
    */
    bool operator == ( const FBVector2& pVector );
};

//! Three dimensional vector (template).
template <class tType> class FBSDK_DLL FBVector3
{ 
  private:
  public:
	tType mValue[3];	//!< Values

  public:

    //! Constructor.
	FBVector3();

    //! Copy Constructor
    FBVector3( const FBVector3& pVector );

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBVector3( tType *pValue );

	/**	Constructor.
	*	\param	p1	First element
	*	\param	p2	Second element.
	*	\param	p3	Third element(default=0).
	*/
	FBVector3( tType p1,tType p2, tType p3 = 0);

	/**	Initialization function.
	*	Clear vector.
	*/
	void Init();

	/**	Overloaded [] operator.
	*	\param	pIndex	Element to access.
	*	\return	Element at \e pIndex.
	*/
	tType &operator[](int pIndex);

	/**	Set vector from an array.
	*	\param	pValue	Array to copy value from.
	*/
	void Set( tType *pValue );

	/**	Overloaded cast to array.
	*	\return	Array of items of \e tType.
	*/
    operator tType *() const;

    /** Overloaded equal operator.
    *   \param  pVector     Vector to copy.
    *   \return this vector as a const.
    */
    const FBVector3& operator = ( const FBVector3& pVector );

    /** not equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if not equal.
    */
    bool operator != ( const FBVector3& pVector );

    /** equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if equal.
    */
    bool operator == ( const FBVector3& pVector );
};

//! Four dimensional vector (template).
template <class tType> class FBSDK_DLL FBVector4
{ 
  private:
  public:

    tType mValue[4];				//!< Values

	//! Constructor.
	FBVector4();

    //! Copy Constructor
    FBVector4( const FBVector4& pVector );

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBVector4( tType *pValue );

	/**	Constructor.
	*	\param	p1	First element
	*	\param	p2	Second element.
	*	\param	p3	Third element.
	*	\param	p4	Fourth element.
	*/
	FBVector4( tType p1,tType p2, tType p3, tType p4 = 1);

	/**	Initialization function.
	*	Clear vector.
	*/
	void Init();

	/**	Overloaded [] operator.
	*	\param	pIndex	Element to access.
	*	\return	Element at \e pIndex.
	*/
	tType &operator[](int pIndex);

	/**	Set vector from an array.
	*	\param	pValue	Array to copy value from.
	*/
	void Set( tType *pValue );

	/**	Overloaded cast to array.
	*	\return	Array of items of \e tType.
	*/
    operator tType *() const;

    /** Overloaded equal operator.
    *   \param  pVector     Vector to copy.
    *   \return this vector as a const.
    */
    const FBVector4& operator = ( const FBVector4& pVector );

    /** not equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if not equal.
    */
    bool operator != ( const FBVector4& pVector );

    /** equal operator.
    *   \param  pVector Vector to compare.
    *   \return true if equal.
    */
    bool operator == ( const FBVector4& pVector );

};

//! Four x Four (double) Matrix
class FBSDK_DLL FBMatrix
{ 
  private:
	double mValue[4][4];			//!< Matrix

  public:
	/** Constructor
	*	Initializes matrix to identity.
	*/
	FBMatrix();

	/**	Constructor.
	*	\param	pValue	Array to intialize matrix from.
	*/
	FBMatrix( const double *pValue );

    /** Copy Constructor.
    *   \param  pMatrix     Matrix to copy.
    */
    FBMatrix( const FBMatrix& pMatrix );

	//!	Load identity matrix.
	void Identity();

	/**	Set matrix from an array.
	*	\param	pValue	Array to intialize matrix from.
	*/
	void Set( const double *pValue );

	/**	Overloaded double* cast
	*	\return	Matrix as an array.
	*/
    operator double *() const;

	/**	return internal Data
	*	\return	return an array[4][4].
	*/
    double **  GetData() const;

    /** Overloaded operator (,)
    *   \return element at position i,j
    */
    double& operator () ( int i, int j );

    /** Overloaded equal operator.
    *   \param  pMatrix     Matrix to copy.
    *   \return this matrix as a const.
    */
    const FBMatrix& operator = ( const FBMatrix& pMatrix );

    /** assign operator.
    *   \param  pValue     array to assign.
    *   \return this matrix as a const.
    */
    const FBMatrix& operator = ( const double *pValue );

    /** not equal operator.
    *   \param  pMatrix Matrix to compare.
    *   \return true if not equal.
    */
    bool operator != ( const FBMatrix& pMatrix );

    /** equal operator.
    *   \param  pMatrix Matrix to compare.
    *   \return true if equal.
    */
    bool operator == ( const FBMatrix& pMatrix );

    /** add operator.
    *   \param  pMatrix Matrix to add.
    *   \return result Matrix.
    */
    const FBMatrix operator + ( const FBMatrix& pMatrix ) const;

    /** add operator in place.
    *   \param  pMatrix Matrix to add.
    *   \return this matrix as a const.
    */
    FBMatrix &operator += ( const FBMatrix& pMatrix );

    /** unary minus operator.
    *   \return this matrix as a const.
    */
    const FBMatrix operator - ();

    /** minus operator.
    *   \param  pMatrix Matrix to minus.
    *   \return result Matrix.
    */
    const FBMatrix operator - ( const FBMatrix& pMatrix ) const;

    /** minus operator in place.
    *   \param  pMatrix Matrix to minus.
    *   \return this matrix.
    */
    FBMatrix &operator -= ( const FBMatrix& pMatrix );

    /** multiply operator.
    *   \param  pMatrix Matrix to multiply.
    *   \return result Matrix.
    */
    const FBMatrix operator * ( const FBMatrix& pMatrix ) const;

    /** multiply operator in place.
    *   \param  pMatrix Matrix to multiply.
    *   \return this matrix.
    */
    FBMatrix &operator *= ( const FBMatrix& pMatrix );

    /** multiply operator for double.
    *   \param  pN double to multiply.
    *   \return result Matrix.
    */
    const FBMatrix operator * ( const double pN ) const;

    /** multiply operator for double in place.
    *   \param  pN double to multiply.
    *   \return this matrix.
    */
    FBMatrix &operator *= ( const double pN );

    /** Get Inversed matrix.
    *   \return the matrix Inversed.
    */
    FBMatrix &Inverse();

    /** Get Transposed matrix.
    *   \return the matrix Transposed.
    */
    FBMatrix &Transpose();

    /** Validated matrix.
    *   \return true if matrix Validated.
    */
    bool Validate();

    /** InverseProduct Matrix.
    *   \param  pMatrix Matrix to Product.
    *   \return result matrix.
    */
    const FBMatrix InverseProduct( const FBMatrix& pMatrix );

};


//! 2D vector.
typedef class FBSDK_DLL FBVector2<double>	FBVector2d;  

//! 3D vector.
typedef class FBSDK_DLL FBVector3<double>	FBVector3d;  

//! 4D vector
typedef class FBSDK_DLL FBVector4<double>	FBVector4d;

//! Color float
typedef  class FBSDK_DLL FBVector4<float>  FBColorF;  

//! Color vector.
class FBSDK_DLL FBColor : public FBVector3< double >
{
  public:
	//! Constructor.
	FBColor();

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBColor( double *pValue );

	/**	Constructor.
	*	\param	pRed	Red component.
	*	\param	pGreen	Green component.
	*	\param	pBlue	Blue component.
	*/
	FBColor( double pRed, double pGreen, double pBlue);

    //! Copy Constructor
    FBColor( const FBColor& pVector );

	/**	Overloaded [] operator.
	*	\param	pIndex	Element to access.
	*	\return	Element at \e pIndex.
	*/
	double &operator[](int pIndex);

	/**	Overloaded cast to array.
	*	\return	Array of items of \e tType.
	*/
    operator double *() const;

    /** Overloaded equal operator.
    *   \param  pVector     Vector to copy.
    *   \return this vector as a const.
    */
    const FBColor& operator = ( const FBColor& pVector );
	void operator=(double *pValue);
    const FBVector3< double >& operator = ( const FBVector3< double >& pVector );
};

//! Color and alpha vector.
class FBSDK_DLL FBColorAndAlpha : public FBVector4< double >
{
  public:
	//! Constructor.
	FBColorAndAlpha();

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBColorAndAlpha( double *pValue );

	/**	Constructor.
	*	\param	pRed	Red component.
	*	\param	pGreen	Green component.
	*	\param	pBlue	Blue component.
	*	\param	pAlpha	Alpha component(default=1.0).
	*/
	FBColorAndAlpha( double pRed, double pGreen, double pBlue, double pAlpha=1.0);

	/**	Constructor from FBColor.
	*	\param	pValue	FBColor to take values from.
	*/
	FBColorAndAlpha( const FBColor &pValue );

    /** Constructor from FBColorF
    *   \param pValue FBColorF to take values from.
    */
    FBColorAndAlpha( const FBColorF& pValue );

    //! Copy Constructor
    FBColorAndAlpha( const FBColorAndAlpha& pVector );

	/**	Overloaded [] operator.
	*	\param	pIndex	Element to access.
	*	\return	Element at \e pIndex.
	*/
	double &operator[](int pIndex);

	/**	Overloaded cast to array.
	*	\return	Array of items of \e tType.
	*/
    operator double *() const;

    /** Overloaded equal operator.
    *   \param  pVector     Vector to copy.
    *   \return this vector as a const.
    */
    const FBColorAndAlpha& operator = ( const FBColorAndAlpha& pVector );
    const FBColorAndAlpha& operator = ( const FBColor& pVector );
    const FBColorAndAlpha& operator = ( const FBColorF& pVector );
	void operator=(double *pValue);
    const FBVector4< double >& operator = ( const FBVector4< double >& pVector );
};

//! 2D vector.
typedef FBVector2<double> FBVector2d;  

//! 3D vector.
typedef FBVector3<double> FBVector3d;  

//! 4D vector
typedef FBVector4<double> FBVector4d;

//! Rotation vector.
typedef FBVector3<double> FBRVector;

//! Translation vector.
typedef FBVector4<double> FBTVector;  

//! Vector 3 double
typedef class FBSDK_DLL FBVector3< double > FBVector3Double;

//! Vector 4 double
typedef class FBSDK_DLL FBVector4< double > FBVector4Double;

//! Three dimensional scaling vector.
class FBSDK_DLL FBSVector : public FBVector3< double >
{ 
  private:
  public:
	//! Constructor.
	FBSVector();

	/**	Constructor from array.
	*	\param	pValue	Array to take values from.
	*/
	FBSVector( double *pValue );

	/**	Constructor.
	*	\param	p1	First element
	*	\param	p2	Second element.
	*	\param	p3	Third element(default=1.0).
	*/
	FBSVector( double p1,double p2, double p3=1.0 );

	/**	Init
	*	Initialization function.
	*	Clear vector.
	*/
	void Init();
};

//typedef FBVector3<double> FBSVector; 
//! Quaternion
typedef class FBSDK_DLL FBVector4<double>   FBQuaternion;  
//! Represents a UV coordinate as a FBVector2 of floats in the range of 0.0f to 1.0f; value 0 is the U value, and value 1 is the V value.
typedef class FBSDK_DLL FBVector2<float>    FBUV;
//! Vertex
typedef class FBSDK_DLL FBVector4<float>    FBVertex;
//! Normal
typedef class FBSDK_DLL FBVector4<float>	FBNormal;  

////////////////////////////////////////////////////////////////////////////////////
// Global
////////////////////////////////////////////////////////////////////////////////////
#ifdef FBSDKUseNamespace
	}
#endif

#endif

