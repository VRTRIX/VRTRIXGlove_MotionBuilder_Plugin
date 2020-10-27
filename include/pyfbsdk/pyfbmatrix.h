#ifndef pyfbmatrix_h__
#define pyfbmatrix_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBMatrix
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBMatrix_Init();

class FBMatrix_Wrapper {

public:
    FBMatrix* mFBMatrix;

    // CTOR
    FBMatrix_Wrapper(const FBMatrix& pMat) : mFBMatrix( new FBMatrix( pMat ) )
    {
    };

    FBMatrix_Wrapper() : mFBMatrix( new FBMatrix())
    {
    };
    // CTOR
    FBMatrix_Wrapper( list pList ) : mFBMatrix( new FBMatrix())
    {
        Set( pList );
    };
    // CTOR
    FBMatrix_Wrapper( const FBMatrix_Wrapper& pFBMatrix ) : mFBMatrix( new FBMatrix( *( pFBMatrix.mFBMatrix )))
    {
    };

    FBMatrix_Wrapper* CopyFrom (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        *mFBMatrix = *( pFBMatrix.mFBMatrix ); 
        return new FBMatrix_Wrapper(*mFBMatrix); 
    } 
  
    FBMatrix_Wrapper   operator + (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        return FBMatrix_Wrapper(mFBMatrix->operator + (*( pFBMatrix.mFBMatrix ))); 
    } 
  
    FBMatrix_Wrapper   operator - (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        return FBMatrix_Wrapper(mFBMatrix->operator - (*( pFBMatrix.mFBMatrix ))); 
    } 
  
    FBMatrix_Wrapper   operator * (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        return FBMatrix_Wrapper(mFBMatrix->operator * (*( pFBMatrix.mFBMatrix ))); 
    } 
  
    FBMatrix_Wrapper   operator * (const double pN) 
    { 
        return FBMatrix_Wrapper(mFBMatrix->operator * (pN)); 
    } 
 
    FBMatrix_Wrapper& operator += (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        mFBMatrix->operator +=(*( pFBMatrix.mFBMatrix )); 
        return *this;  
    } 
  
    FBMatrix_Wrapper& operator -= (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        mFBMatrix->operator -=(*( pFBMatrix.mFBMatrix )); 
        return *this;  
    } 
  
    FBMatrix_Wrapper& operator *= (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        mFBMatrix->operator *=(*( pFBMatrix.mFBMatrix )); 
        return *this;  
    } 
  
    FBMatrix_Wrapper& operator *= (const double pN) 
    { 
        mFBMatrix->operator *=(pN); 
        return *this;  
    } 
  
    FBMatrix_Wrapper operator- ()  
    { 
        mFBMatrix->operator - (); 
        return FBMatrix_Wrapper(*mFBMatrix); 
    } 
 
    bool NotEqual (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        return mFBMatrix->operator !=(*( pFBMatrix.mFBMatrix )); 
    } 
  
    bool IsEqual (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        return ! NotEqual(*( pFBMatrix.mFBMatrix )); 
    } 
  
    void Transpose () 
    { 
        mFBMatrix->Transpose(); 
    } 
  
    void Inverse() 
    { 
        mFBMatrix->Inverse(); 
    }  
  
    void InverseProduct (const FBMatrix_Wrapper &pFBMatrix) 
    { 
        mFBMatrix->InverseProduct(*( pFBMatrix.mFBMatrix )); 
    } 
   
    bool Validate() 
    { 
        return mFBMatrix->Validate(); 
    }  

    // DTOR
    ~FBMatrix_Wrapper()
    {
        delete mFBMatrix;
    }

    // METHOD: Identity()
    void Identity()
    {
        mFBMatrix->Identity();
    };

    // METHOD: Set()
    void Set( list pMat )
    {
        double lValues[4][4];
        if ( len( pMat ) == 16 )        
        {
            for ( int row = 0; row < 4; ++row )
            {
                for ( int col = 0; col < 4; ++col )
                {
                    lValues[row][col] = extract<double>( pMat[row * 4 + col] );
                }
            }
            mFBMatrix->Set( (double*)lValues );
        }
        else if ( len( pMat ) == 4 )
        {
            for ( int row = 0; row < 4; ++row )
            {
                extract<list> lExtractor( pMat[row] );
                if ( lExtractor.check() )
                {
                    list l = lExtractor();
                    if ( len( l ) == 4 )
                    {
                        for ( int col = 0; col < 4; ++col )
                        {
                            lValues[row][col] = extract<double>( l[col] );
                        }                           
                    }
                    else
                    {
                        // Wrong data type
                        return;
                    }
                }
                else
                {
                    // Wrong data type
                    return;
                }
            }
            mFBMatrix->Set( (double*)lValues );
        }        
    };

    int GetCount() const
    {
        return 16;
    };

    double GetDouble( int lIndex ) const
    {
        /*
        // To be enabled post Hobbes: this is a more python way of setting values using (i, j) subscribing
        if ( len( lIndexes ) == 2 )
        {
            int row = extract<int>( lIndexes[0] );
            int col = extract<int>( lIndexes[1] );
            return mFBMatrix->operator() ( row , col );
        }
        else
        {
            int lIndex = extract<int>( lIndexes );
            return lIndex >= 0 && lIndex < 16 ? (mFBMatrix->operator double*())[lIndex] : 0.0;
        }
        */
		if ( lIndex < 0)
		{
			lIndex += GetCount();
		}
		if ( lIndex <0 || lIndex >= GetCount())
		{
			PyErr_SetString(PyExc_IndexError, "matrix vector index out of range");
			throw_error_already_set();
			return 0;
		}
		return (mFBMatrix->operator double*())[lIndex];
    };

    void SetDouble( int lIndex, double lDouble )
    {
        /*
        // To be enabled post Hobbes: this is a more python way of setting values using (i, j) subscribing
        if ( len( lIndexes ) == 2 )
        {
            int row = extract<int>( lIndexes[0] );
            int col = extract<int>( lIndexes[1] );
            mFBMatrix->operator () ( row , col ) = lDouble;
        }
        else
        {
            int lIndex = extract<int>( lIndexes );
            if ( lIndex >= 0 && lIndex < 16 )            
            {
                (mFBMatrix->operator double*())[lIndex] = lDouble;
            }
        }
        */
        if ( lIndex >= 0 && lIndex < 16 )
        {
            (mFBMatrix->operator double*())[lIndex] = lDouble;
        }        
    }
    
    /** Return Matrix Memory Address to allow ctypes array conversion. 
    */
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBMatrix->operator double*();
    }

    const char* GetRepr()
    {
        char lBuffer[1024];
        double* lDouble = mFBMatrix->operator double*();

        sprintf( lBuffer, "(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)",
                 lDouble[ 0], lDouble[ 1], lDouble[ 2], lDouble[ 3],
                 lDouble[ 4], lDouble[ 5], lDouble[ 6], lDouble[ 7],
                 lDouble[ 8], lDouble[ 9], lDouble[10], lDouble[11],
                 lDouble[12], lDouble[13], lDouble[14], lDouble[15]);

        char* lRepr = new char[ strlen( lBuffer ) + 1 ];
        strcpy( lRepr, lBuffer );

        return lRepr;
    };
};

inline FBMatrix_Wrapper* FBMatrix_Wrapper_Factory( const FBMatrix& pFBMatrix )
{
	return new FBMatrix_Wrapper( pFBMatrix );
}
#endif // pyfbmatrix_h__