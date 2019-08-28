#ifndef pyfbvector_h__
#define pyfbvector_h__
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
// CLASS: FBVector2d
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBVector2d_Init();
class FBVector2d_Wrapper;
PYSDK_DLL FBVector2d_Wrapper* FBVector2d_Wrapper_Factory( const FBVector2d& pFBVector2d );
class PYSDK_DLL FBVector2d_Wrapper {

public:
    FBVector2d* mFBVector2d;

    // CTOR
    FBVector2d_Wrapper() : mFBVector2d( new FBVector2d())
    {
    };
    // CTOR
    FBVector2d_Wrapper( const FBVector2d& pFBVector2d ) : mFBVector2d( new FBVector2d( pFBVector2d ))
    {
    };
    // CTOR
    FBVector2d_Wrapper( const FBVector2d_Wrapper& pFBVector2d ) : mFBVector2d( new FBVector2d( *( pFBVector2d.mFBVector2d )))
    {
    };
    // CTOR
    FBVector2d_Wrapper( double p1, double p2 ) : mFBVector2d( new FBVector2d( p1, p2 ))
    {
    };

    //CTOR 
    FBVector2d_Wrapper( list pList ) : mFBVector2d( new FBVector2d()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBVector2d_Wrapper* CopyFrom (const FBVector2d_Wrapper &pVector2d) 
    { 
        *mFBVector2d = *(pVector2d.mFBVector2d); 
        return new FBVector2d_Wrapper(*mFBVector2d); 
    } 
  
    FBVector2d_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[2]; 
        if ( len( pData ) == 2 )         
        { 
            for ( int item = 0; item < 2; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
            } 
            mFBVector2d->Set( (double*)lValues ); 
        } 
        return new FBVector2d_Wrapper(*mFBVector2d); 
    } 
  
    FBVector2d_Wrapper*    operator+ (const FBVector2d_Wrapper &pVector2d) {return new FBVector2d_Wrapper(this->Get(0)+pVector2d.Get(0),this->Get(1)+pVector2d.Get(1));} 
    FBVector2d_Wrapper*    operator- (const FBVector2d_Wrapper &pVector2d) {return new FBVector2d_Wrapper(this->Get(0)-pVector2d.Get(0),this->Get(1)-pVector2d.Get(1));} 
    FBVector2d_Wrapper*    operator* (const FBVector2d_Wrapper &pVector2d) {return new FBVector2d_Wrapper(this->Get(0)*pVector2d.Get(0),this->Get(1)*pVector2d.Get(1));} 
    FBVector2d_Wrapper*    operator/ (const FBVector2d_Wrapper &pVector2d) {return new FBVector2d_Wrapper(this->Get(0)/pVector2d.Get(0),this->Get(1)/pVector2d.Get(1));} 
  
    FBVector2d_Wrapper* operator+ (double pD) {return new FBVector2d_Wrapper(this->Get(0)+pD,this->Get(1)+pD);} 
    FBVector2d_Wrapper* operator- (double pD) {return new FBVector2d_Wrapper(this->Get(0)-pD,this->Get(1)-pD);} 
    FBVector2d_Wrapper* operator* (double pD) {return new FBVector2d_Wrapper(this->Get(0)*pD,this->Get(1)*pD);} 
    FBVector2d_Wrapper* operator/ (double pD) {return new FBVector2d_Wrapper(this->Get(0)/pD,this->Get(1)/pD);} 
  
    FBVector2d_Wrapper& operator+= (const FBVector2d_Wrapper &pVector2d) { (*mFBVector2d)[0] += pVector2d.Get(0); (*mFBVector2d)[1] += pVector2d.Get(1); return *this; } 
    FBVector2d_Wrapper& operator-= (const FBVector2d_Wrapper &pVector2d) { (*mFBVector2d)[0] -= pVector2d.Get(0); (*mFBVector2d)[1] -= pVector2d.Get(1); return *this; } 
    FBVector2d_Wrapper& operator*= (const FBVector2d_Wrapper &pVector2d) { (*mFBVector2d)[0] *= pVector2d.Get(0); (*mFBVector2d)[1] *= pVector2d.Get(1); return *this; } 
    FBVector2d_Wrapper& operator/= (const FBVector2d_Wrapper &pVector2d) { (*mFBVector2d)[0] /= pVector2d.Get(0); (*mFBVector2d)[1] /= pVector2d.Get(1); return *this; } 
   
    FBVector2d_Wrapper& operator+= (double pD) { (*mFBVector2d)[0] += pD; (*mFBVector2d)[1] += pD; return *this; } 
    FBVector2d_Wrapper& operator-= (double pD) { (*mFBVector2d)[0] -= pD; (*mFBVector2d)[1] -= pD; return *this; } 
    FBVector2d_Wrapper& operator*= (double pD) { (*mFBVector2d)[0] *= pD; (*mFBVector2d)[1] *= pD; return *this; } 
    FBVector2d_Wrapper& operator/= (double pD) { (*mFBVector2d)[0] /= pD; (*mFBVector2d)[1] /= pD; return *this; } 
  
    FBVector2d_Wrapper* operator- () { return new FBVector2d_Wrapper( -(*mFBVector2d)[0], -(*mFBVector2d)[1]); } 
  
    bool NotEqual (const FBVector2d_Wrapper &pVector2d) 
    { 
        return mFBVector2d->operator != (*(pVector2d.mFBVector2d)); 
    } 
  
    bool IsEqual (const FBVector2d_Wrapper &pVector2d) 
    { 
        return ! NotEqual(pVector2d); 
    } 
   
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBVector2d->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 3; i++) 
        { 
            lReturnList.append((*mFBVector2d) [i]); 
        } 
        return lReturnList; 
    } 
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBVector2d_Wrapper( boost::python::object pObject ) : mFBVector2d( new FBVector2d())
    {
        if( extract<int>( pObject.attr("__len__")()) == 2 ) {
            (mFBVector2d->operator double*())[0] = extract<double>( pObject[0] );
            (mFBVector2d->operator double*())[1] = extract<double>( pObject[1] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBVector2d_Wrapper()
    {
        delete mFBVector2d;
    };

    int GetCount() const
    {
        return 2;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBVector2d)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBVector2d)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBVector2d_Wrapper* FBVector2d_Wrapper_Factory( const FBVector2d& pFBVector2d )
{
	return new FBVector2d_Wrapper( pFBVector2d );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBVector3d
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBVector3d_Init();
class FBVector3d_Wrapper;
PYSDK_DLL FBVector3d_Wrapper* FBVector3d_Wrapper_Factory( const FBVector3d& pFBVector3d );
class PYSDK_DLL FBVector3d_Wrapper {

public:
    FBVector3d* mFBVector3d;

    // CTOR
    FBVector3d_Wrapper() : mFBVector3d( new FBVector3d())
    {
    };
    // CTOR
    FBVector3d_Wrapper( const FBVector3d& pFBVector3d ) : mFBVector3d( new FBVector3d( pFBVector3d ))
    {
    };
    // CTOR
    FBVector3d_Wrapper( const FBVector3d_Wrapper& pFBVector3d ) : mFBVector3d( new FBVector3d( *( pFBVector3d.mFBVector3d )))
    {
    };
    // CTOR
    FBVector3d_Wrapper( double p1, double p2, double p3 ) : mFBVector3d( new FBVector3d( p1, p2, p3 ))
    {
    };

    //CTOR 
    FBVector3d_Wrapper( list pList ) : mFBVector3d( new FBVector3d()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBVector3d_Wrapper* CopyFrom (const FBVector3d_Wrapper &pVector3d) 
    { 
        *mFBVector3d = *(pVector3d.mFBVector3d); 
        return new FBVector3d_Wrapper(*mFBVector3d); 
    } 
    FBVector3d_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[3]; 
        if ( len( pData ) == 3 )         
        { 
            for ( int item = 0; item < 3; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
            } 
            mFBVector3d->Set( (double*)lValues ); 
        } 
        return new FBVector3d_Wrapper(*mFBVector3d); 
    } 
  
    FBVector3d_Wrapper*    operator+ (const FBVector3d_Wrapper &pVector3d) {return new FBVector3d_Wrapper(this->Get(0)+pVector3d.Get(0),this->Get(1)+pVector3d.Get(1),this->Get(2)+pVector3d.Get(2));} 
    FBVector3d_Wrapper*    operator- (const FBVector3d_Wrapper &pVector3d) {return new FBVector3d_Wrapper(this->Get(0)-pVector3d.Get(0),this->Get(1)-pVector3d.Get(1),this->Get(2)-pVector3d.Get(2));} 
    FBVector3d_Wrapper*    operator* (const FBVector3d_Wrapper &pVector3d) {return new FBVector3d_Wrapper(this->Get(0)*pVector3d.Get(0),this->Get(1)*pVector3d.Get(1),this->Get(2)*pVector3d.Get(2));} 
    FBVector3d_Wrapper*    operator/ (const FBVector3d_Wrapper &pVector3d) {return new FBVector3d_Wrapper(this->Get(0)/pVector3d.Get(0),this->Get(1)/pVector3d.Get(1),this->Get(2)/pVector3d.Get(2));} 
  
    FBVector3d_Wrapper* operator+ (double pD) {return new FBVector3d_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD);} 
    FBVector3d_Wrapper* operator- (double pD) {return new FBVector3d_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD);} 
    FBVector3d_Wrapper* operator* (double pD) {return new FBVector3d_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD);} 
    FBVector3d_Wrapper* operator/ (double pD) {return new FBVector3d_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD);} 
   
    FBVector3d_Wrapper& operator+= (const FBVector3d_Wrapper &pVector3d) { (*mFBVector3d) [0] += pVector3d.Get(0); (*mFBVector3d) [1] += pVector3d.Get(1); (*mFBVector3d) [2] += pVector3d.Get(2); return *this; } 
    FBVector3d_Wrapper& operator-= (const FBVector3d_Wrapper &pVector3d) { (*mFBVector3d) [0] -= pVector3d.Get(0); (*mFBVector3d) [1] -= pVector3d.Get(1); (*mFBVector3d) [2] -= pVector3d.Get(2); return *this; } 
    FBVector3d_Wrapper& operator*= (const FBVector3d_Wrapper &pVector3d) { (*mFBVector3d) [0] *= pVector3d.Get(0); (*mFBVector3d) [1] *= pVector3d.Get(1); (*mFBVector3d) [2] *= pVector3d.Get(2); return *this; } 
    FBVector3d_Wrapper& operator/= (const FBVector3d_Wrapper &pVector3d) { (*mFBVector3d) [0] /= pVector3d.Get(0); (*mFBVector3d) [1] /= pVector3d.Get(1); (*mFBVector3d) [2] /= pVector3d.Get(2); return *this; } 
   
    FBVector3d_Wrapper& operator+= (double pD) { (*mFBVector3d) [0] += pD; (*mFBVector3d) [1] += pD; (*mFBVector3d) [2] += pD; return *this; } 
    FBVector3d_Wrapper& operator-= (double pD) { (*mFBVector3d) [0] -= pD; (*mFBVector3d) [1] -= pD; (*mFBVector3d) [2] -= pD; return *this; } 
    FBVector3d_Wrapper& operator*= (double pD) { (*mFBVector3d) [0] *= pD; (*mFBVector3d) [1] *= pD; (*mFBVector3d) [2] *= pD; return *this; } 
    FBVector3d_Wrapper& operator/= (double pD) { (*mFBVector3d) [0] /= pD; (*mFBVector3d) [1] /= pD; (*mFBVector3d) [2] /= pD; return *this; } 
	
	bool operator==(const FBVector3d_Wrapper& pVector3d)const{ return *mFBVector3d  == *pVector3d.mFBVector3d; } 
	bool operator!=(const FBVector3d_Wrapper& pVector3d)const{ return *mFBVector3d  != *pVector3d.mFBVector3d; } 

    FBVector3d_Wrapper* operator- () { return new FBVector3d_Wrapper( -(*mFBVector3d) [0], -(*mFBVector3d) [1], -(*mFBVector3d) [2]); } 
   
    bool NotEqual (const FBVector3d_Wrapper &pVector3d) 
    { 
        return mFBVector3d->operator != (*(pVector3d.mFBVector3d)); 
    } 
    bool IsEqual (const FBVector3d_Wrapper &pVector3d) 
    { 
        return ! NotEqual(pVector3d); 
    } 
  
    double Length () 
    { 
        double X, Y, Z; 
  
        X = (*mFBVector3d) [0]; 
        Y = (*mFBVector3d) [1]; 
        Z = (*mFBVector3d) [2]; 
 
		        return sqrt(X * X + Y * Y + Z * Z); 
    } 
  
    double SquareLength () 
    { 
        double X, Y, Z; 
  
        X = (*mFBVector3d) [0]; 
        Y = (*mFBVector3d) [1]; 
        Z = (*mFBVector3d) [2]; 
   
        return X * X + Y * Y + Z * Z; 
    } 
    double Distance (const FBVector3d_Wrapper &pVector3d) 
    { 
   
        double    X, Y, Z; 
  
        X = (*mFBVector3d) [0] - pVector3d.Get(0); 
        Y = (*mFBVector3d) [1] - pVector3d.Get(0); 
        Z = (*mFBVector3d) [2] - pVector3d.Get(0); 
  
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    FBVector3d_Wrapper* Normalize() 
    { 
        double Len = Length(); 
        if (Len==0.0) { 
            (*mFBVector3d) [0] = 0.0; 
            (*mFBVector3d) [1] = 0.0; 
            (*mFBVector3d) [2] = 0.0; 
        } else { 
            (*mFBVector3d) [0] /= Len; 
            (*mFBVector3d) [1] /= Len; 
            (*mFBVector3d) [2] /= Len; 
        } 
        return new FBVector3d_Wrapper(*mFBVector3d); 
    } 
   
    double DotProduct (const FBVector3d_Wrapper &pVector3d) {return this->Get(0)*pVector3d.Get(0)+this->Get(1)*pVector3d.Get(1)+this->Get(2)*pVector3d.Get(2);} 
    FBVector3d_Wrapper* CrossProduct (const FBVector3d_Wrapper &pVector3d) 
    { 
        double Ax = (*mFBVector3d) [0]; 
        double Ay = (*mFBVector3d) [1]; 
        double Az = (*mFBVector3d) [2]; 
 
        double Bx = pVector3d.Get(0); 
        double By = pVector3d.Get(1);  
        double Bz = pVector3d.Get(2); 
  
        double Cx = Ay*Bz - Az*By;  
        double Cy = Az*Bx - Ax*Bz;  
        double Cz = Ax*By - Ay*Bx;  
 
        return new FBVector3d_Wrapper(Cx, Cy, Cz);     
    } 
  
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBVector3d->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 3; i++) 
        { 
            lReturnList.append((*mFBVector3d) [i]); 
        } 
        return lReturnList; 
    } 

    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBVector3d_Wrapper( boost::python::object pObject ) : mFBVector3d( new FBVector3d())
    {
        if( extract<int>( pObject.attr("__len__")()) == 3 ) {
            (mFBVector3d->operator double*())[0] = extract<double>( pObject[0] );
            (mFBVector3d->operator double*())[1] = extract<double>( pObject[1] );
            (mFBVector3d->operator double*())[2] = extract<double>( pObject[2] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBVector3d_Wrapper()
    {
        delete mFBVector3d;
    };

    int GetCount() const
    {
        return 3;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBVector3d)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBVector3d)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBVector3d_Wrapper* FBVector3d_Wrapper_Factory( const FBVector3d& pFBVector3d )
{        
    return new FBVector3d_Wrapper( pFBVector3d );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBSVector
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBSVector_Init();
class FBSVector_Wrapper;
PYSDK_DLL FBSVector_Wrapper* FBSVector_Wrapper_Factory( const FBSVector& pFBSVector );
class PYSDK_DLL FBSVector_Wrapper {

public:
    FBSVector* mFBSVector;

    // CTOR
    FBSVector_Wrapper() : mFBSVector( new FBSVector())
    {
    };
    // CTOR
    FBSVector_Wrapper( const FBSVector& pFBSVector ) : mFBSVector( new FBSVector( pFBSVector ))
    {
    };
    // CTOR
    FBSVector_Wrapper( const FBSVector_Wrapper& pFBSVector ) : mFBSVector( new FBSVector( *( pFBSVector.mFBSVector )))
    {
    };
    // CTOR
    FBSVector_Wrapper( double p1, double p2, double p3 ) : mFBSVector( new FBSVector( p1, p2, p3 ))
    {
    };

    //CTOR 
    FBSVector_Wrapper( list pList ) : mFBSVector( new FBSVector()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBSVector_Wrapper* CopyFrom (const FBSVector_Wrapper &pFBSVector) 
    { 
        *mFBSVector = *(pFBSVector.mFBSVector); 
        return new FBSVector_Wrapper(*mFBSVector); 
    } 
    FBSVector_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[3]; 
        if ( len( pData ) == 3 )         
        { 
            for ( int item = 0; item < 3; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
	            } 
            mFBSVector->Set( (double*)lValues ); 
        } 
        return new FBSVector_Wrapper(*mFBSVector); 
    } 
  
    FBSVector_Wrapper*    operator+ (const FBSVector_Wrapper &pFBSVector) {return new FBSVector_Wrapper(this->Get(0)+pFBSVector.Get(0),this->Get(1)+pFBSVector.Get(1),this->Get(2)+pFBSVector.Get(2));} 
    FBSVector_Wrapper*    operator- (const FBSVector_Wrapper &pFBSVector) {return new FBSVector_Wrapper(this->Get(0)-pFBSVector.Get(0),this->Get(1)-pFBSVector.Get(1),this->Get(2)-pFBSVector.Get(2));} 
    FBSVector_Wrapper*    operator* (const FBSVector_Wrapper &pFBSVector) {return new FBSVector_Wrapper(this->Get(0)*pFBSVector.Get(0),this->Get(1)*pFBSVector.Get(1),this->Get(2)*pFBSVector.Get(2));} 
    FBSVector_Wrapper*    operator/ (const FBSVector_Wrapper &pFBSVector) {return new FBSVector_Wrapper(this->Get(0)/pFBSVector.Get(0),this->Get(1)/pFBSVector.Get(1),this->Get(2)/pFBSVector.Get(2));} 
  
    FBSVector_Wrapper* operator+ (double pD) {return new FBSVector_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD);} 
    FBSVector_Wrapper* operator- (double pD) {return new FBSVector_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD);} 
    FBSVector_Wrapper* operator* (double pD) {return new FBSVector_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD);} 
    FBSVector_Wrapper* operator/ (double pD) {return new FBSVector_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD);} 
  
    FBSVector_Wrapper& operator+= (const FBSVector_Wrapper &pFBSVector) { (*mFBSVector)[0] += pFBSVector.Get(0); (*mFBSVector)[1] += pFBSVector.Get(1); (*mFBSVector)[2] += pFBSVector.Get(2); return *this; } 
    FBSVector_Wrapper& operator-= (const FBSVector_Wrapper &pFBSVector) { (*mFBSVector)[0] -= pFBSVector.Get(0); (*mFBSVector)[1] -= pFBSVector.Get(1); (*mFBSVector)[2] -= pFBSVector.Get(2); return *this; } 
    FBSVector_Wrapper& operator*= (const FBSVector_Wrapper &pFBSVector) { (*mFBSVector)[0] *= pFBSVector.Get(0); (*mFBSVector)[1] *= pFBSVector.Get(1); (*mFBSVector)[2] *= pFBSVector.Get(2); return *this; } 
    FBSVector_Wrapper& operator/= (const FBSVector_Wrapper &pFBSVector) { (*mFBSVector)[0] /= pFBSVector.Get(0); (*mFBSVector)[1] /= pFBSVector.Get(1); (*mFBSVector)[2] /= pFBSVector.Get(2); return *this; } 
   
    FBSVector_Wrapper& operator+= (double pD) { (*mFBSVector)[0] += pD; (*mFBSVector)[1] += pD; (*mFBSVector)[2] += pD; return *this; } 
    FBSVector_Wrapper& operator-= (double pD) { (*mFBSVector)[0] -= pD; (*mFBSVector)[1] -= pD; (*mFBSVector)[2] -= pD; return *this; } 
    FBSVector_Wrapper& operator*= (double pD) { (*mFBSVector)[0] *= pD; (*mFBSVector)[1] *= pD; (*mFBSVector)[2] *= pD; return *this; } 
    FBSVector_Wrapper& operator/= (double pD) { (*mFBSVector)[0] /= pD; (*mFBSVector)[1] /= pD; (*mFBSVector)[2] /= pD; return *this; } 
   
    FBSVector_Wrapper* operator- () { return new FBSVector_Wrapper( -(*mFBSVector)[0], -(*mFBSVector)[1], -(*mFBSVector)[2]); } 
      
    bool NotEqual (const FBSVector_Wrapper &pFBSVector) 
    { 
        return mFBSVector->operator != (*(pFBSVector.mFBSVector)); 
    } 
    bool IsEqual (const FBSVector_Wrapper &pFBSVector) 
    { 
        return ! NotEqual(pFBSVector); 
    } 
   
    double Length () 
    { 
        double X, Y, Z; 
  
        X = (*mFBSVector)[0]; 
        Y = (*mFBSVector)[1]; 
        Z = (*mFBSVector)[2]; 
  
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    double SquareLength () 
    { 
        double X, Y, Z; 
  
        X = (*mFBSVector)[0]; 
        Y = (*mFBSVector)[1]; 
        Z = (*mFBSVector)[2]; 
  
        return X * X + Y * Y + Z * Z; 
    } 
    FBSVector_Wrapper* Normalize() 
    { 
        double Len = Length(); 
        if (Len==0.0) { 
            (*mFBSVector)[0] = 0.0; 
            (*mFBSVector)[1] = 0.0; 
            (*mFBSVector)[2] = 0.0; 
        } else { 
            (*mFBSVector)[0] /= Len; 
            (*mFBSVector)[1] /= Len; 
            (*mFBSVector)[2] /= Len; 
        } 
        return new FBSVector_Wrapper(*mFBSVector); 
    } 
  
    double DotProduct (const FBSVector_Wrapper &pFBSVector) {return this->Get(0)*pFBSVector.Get(0)+this->Get(1)*pFBSVector.Get(1)+this->Get(2)*pFBSVector.Get(2);} 
    FBSVector_Wrapper* CrossProduct (const FBSVector_Wrapper &pFBSVector) 
    { 
        double Ax = (*mFBSVector)[0]; 
        double Ay = (*mFBSVector)[1]; 
        double Az = (*mFBSVector)[2]; 
  
        double Bx = pFBSVector.Get(0); 
        double By = pFBSVector.Get(1);  
        double Bz = pFBSVector.Get(2); 
 
	    double Cx = Ay*Bz - Az*By;  
        double Cy = Az*Bx - Ax*Bz;  
        double Cz = Ax*By - Ay*Bx;  
   
        return new FBSVector_Wrapper(Cx, Cy, Cz);     
    } 
  
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBSVector->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 3; i++) 
        { 
            lReturnList.append((*mFBSVector)[i]); 
        } 
        return lReturnList; 
    } 
  
	/////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBSVector_Wrapper( boost::python::object pObject ) : mFBSVector( new FBSVector())
    {
        if( extract<int>( pObject.attr("__len__")()) == 3 ) {
            (mFBSVector->operator double*())[0] = extract<double>( pObject[0] );
            (mFBSVector->operator double*())[1] = extract<double>( pObject[1] );
            (mFBSVector->operator double*())[2] = extract<double>( pObject[2] );
        }
        else{
            // ???
        }
    };
    // DTOR
    ~FBSVector_Wrapper()
    {
        delete mFBSVector;
    };

    int GetCount() const
    {
        return 3;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
            return 0;
        }
        return (*mFBSVector)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
            return;
        }
        (*mFBSVector)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBSVector_Wrapper* FBSVector_Wrapper_Factory( const FBSVector& pFBSVector )
{        
    return new FBSVector_Wrapper( pFBSVector );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBVector4d
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBVector4d_Init();
class FBVector4d_Wrapper;
PYSDK_DLL FBVector4d_Wrapper* FBVector4d_Wrapper_Factory( const FBVector4d& pFBVector4d );
class PYSDK_DLL FBVector4d_Wrapper {

public:
    FBVector4d* mFBVector4d;

    // CTOR
    FBVector4d_Wrapper() : mFBVector4d( new FBVector4d())
    {
    };
    // CTOR
    FBVector4d_Wrapper( const FBVector4d& pFBVector4d ) : mFBVector4d( new FBVector4d( pFBVector4d ))
    {
    };
    // CTOR
    FBVector4d_Wrapper( const FBVector4d_Wrapper& pFBVector4d ) : mFBVector4d( new FBVector4d( *( pFBVector4d.mFBVector4d )))
    {
    };
    // CTOR
    FBVector4d_Wrapper( double p1, double p2, double p3, double p4 ) : mFBVector4d( new FBVector4d( p1, p2, p3, p4 ))
    {
    };

    //CTOR 
    FBVector4d_Wrapper( list pList ) : mFBVector4d( new FBVector4d()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBVector4d_Wrapper* CopyFrom (const FBVector4d_Wrapper &pVector4d) 
    { 
        *mFBVector4d = *(pVector4d.mFBVector4d); 
        return new FBVector4d_Wrapper(*mFBVector4d); 
    } 
    FBVector4d_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[4]; 
        if ( len( pData ) == 4 )         
        { 
            for ( int item = 0; item < 4; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
            } 
            mFBVector4d->Set( (double*)lValues ); 
        } 
        return new FBVector4d_Wrapper(*mFBVector4d); 
    } 

    FBVector4d_Wrapper*    operator+ (const FBVector4d_Wrapper &pVector4d) {return new FBVector4d_Wrapper(this->Get(0)+pVector4d.Get(0),this->Get(1)+pVector4d.Get(1),this->Get(2)+pVector4d.Get(2),this->Get(3)+pVector4d.Get(3));} 
    FBVector4d_Wrapper*    operator- (const FBVector4d_Wrapper &pVector4d) {return new FBVector4d_Wrapper(this->Get(0)-pVector4d.Get(0),this->Get(1)-pVector4d.Get(1),this->Get(2)-pVector4d.Get(2),this->Get(3)-pVector4d.Get(3));} 
    FBVector4d_Wrapper*    operator* (const FBVector4d_Wrapper &pVector4d) {return new FBVector4d_Wrapper(this->Get(0)*pVector4d.Get(0),this->Get(1)*pVector4d.Get(1),this->Get(2)*pVector4d.Get(2),this->Get(3)*pVector4d.Get(3));} 
    FBVector4d_Wrapper*    operator/ (const FBVector4d_Wrapper &pVector4d) {return new FBVector4d_Wrapper(this->Get(0)/pVector4d.Get(0),this->Get(1)/pVector4d.Get(1),this->Get(2)/pVector4d.Get(2),this->Get(3)/pVector4d.Get(3));} 
   
    FBVector4d_Wrapper* operator+ (double pD) {return new FBVector4d_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD,this->Get(3)+pD);} 
    FBVector4d_Wrapper* operator- (double pD) {return new FBVector4d_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD,this->Get(3)-pD);} 
    FBVector4d_Wrapper* operator* (double pD) {return new FBVector4d_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD,this->Get(3)*pD);} 
    FBVector4d_Wrapper* operator/ (double pD) {return new FBVector4d_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD,this->Get(3)-pD);} 
  
    FBVector4d_Wrapper& operator+= (const FBVector4d_Wrapper &pVector4d) { (*mFBVector4d)[0] += pVector4d.Get(0); (*mFBVector4d)[1] += pVector4d.Get(1); (*mFBVector4d)[2] += pVector4d.Get(2); (*mFBVector4d)[3] += pVector4d.Get(3); return *this; } 
    FBVector4d_Wrapper& operator-= (const FBVector4d_Wrapper &pVector4d) { (*mFBVector4d)[0] -= pVector4d.Get(0); (*mFBVector4d)[1] -= pVector4d.Get(1); (*mFBVector4d)[2] -= pVector4d.Get(2); (*mFBVector4d)[3] -= pVector4d.Get(3); return *this; } 
    FBVector4d_Wrapper& operator*= (const FBVector4d_Wrapper &pVector4d) { (*mFBVector4d)[0] *= pVector4d.Get(0); (*mFBVector4d)[1] *= pVector4d.Get(1); (*mFBVector4d)[2] *= pVector4d.Get(2); (*mFBVector4d)[3] *= pVector4d.Get(3); return *this; } 
    FBVector4d_Wrapper& operator/= (const FBVector4d_Wrapper &pVector4d) { (*mFBVector4d)[0] /= pVector4d.Get(0); (*mFBVector4d)[1] /= pVector4d.Get(1); (*mFBVector4d)[2] /= pVector4d.Get(2); (*mFBVector4d)[3] /= pVector4d.Get(3); return *this; } 
  
    FBVector4d_Wrapper& operator+= (double pD) { (*mFBVector4d)[0] += pD; (*mFBVector4d)[1] += pD; (*mFBVector4d)[2] += pD; (*mFBVector4d)[3] += pD; return *this; } 
    FBVector4d_Wrapper& operator-= (double pD) { (*mFBVector4d)[0] -= pD; (*mFBVector4d)[1] -= pD; (*mFBVector4d)[2] -= pD; (*mFBVector4d)[3] -= pD; return *this; } 
    FBVector4d_Wrapper& operator*= (double pD) { (*mFBVector4d)[0] *= pD; (*mFBVector4d)[1] *= pD; (*mFBVector4d)[2] *= pD; (*mFBVector4d)[3] *= pD; return *this; } 
    FBVector4d_Wrapper& operator/= (double pD) { (*mFBVector4d)[0] /= pD; (*mFBVector4d)[1] /= pD; (*mFBVector4d)[2] /= pD; (*mFBVector4d)[3] /= pD; return *this; } 
  
    FBVector4d_Wrapper* operator- () { return new FBVector4d_Wrapper( -(*mFBVector4d)[0], -(*mFBVector4d)[1], -(*mFBVector4d)[2], -(*mFBVector4d)[3]); } 
  
    bool NotEqual (const FBVector4d_Wrapper &pVector4d) 
    { 
        return mFBVector4d->operator != (*(pVector4d.mFBVector4d)); 
    } 
    bool IsEqual (const FBVector4d_Wrapper &pVector4d) 
    { 
        return ! NotEqual(pVector4d); 
    } 
  
   double Length () 
    { 
        double X, Y, Z; 
  
        X = (*mFBVector4d)[0]; 
        Y = (*mFBVector4d)[1]; 
        Z = (*mFBVector4d)[2]; 
  
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    double SquareLength () 
    { 
        double X, Y, Z; 
   
        X = (*mFBVector4d)[0]; 
        Y = (*mFBVector4d)[1]; 
        Z = (*mFBVector4d)[2]; 
   
        return X * X + Y * Y + Z * Z; 
    } 
    double Distance (const FBVector4d_Wrapper &pVector4d) 
    { 
  
        double    X, Y, Z; 
  
        X = (*mFBVector4d)[0] - pVector4d.Get(0); 
        Y = (*mFBVector4d)[1] - pVector4d.Get(0); 
        Z = (*mFBVector4d)[2] - pVector4d.Get(0); 
   
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    FBVector4d_Wrapper* Normalize() 
    { 
        double Len = Length(); 
        if (Len==0.0) { 
            (*mFBVector4d)[0] = 0.0; 
            (*mFBVector4d)[1] = 0.0; 
            (*mFBVector4d)[2] = 0.0; 
        } else { 
            (*mFBVector4d)[0] /= Len; 
            (*mFBVector4d)[1] /= Len; 
            (*mFBVector4d)[2] /= Len; 
        } 
        return new FBVector4d_Wrapper(*mFBVector4d); 
    } 
  
    double DotProduct (const FBVector4d_Wrapper &pVector4d) {return this->Get(0)*pVector4d.Get(0)+this->Get(1)*pVector4d.Get(1)+this->Get(2)*pVector4d.Get(2);} 
    FBVector4d_Wrapper* CrossProduct (const FBVector4d_Wrapper &pVector4d) 
    { 
        double Ax = (*mFBVector4d)[0]; 
        double Ay = (*mFBVector4d)[1]; 
        double Az = (*mFBVector4d)[2]; 
  
        double Bx = pVector4d.Get(0); 
        double By = pVector4d.Get(1);  
        double Bz = pVector4d.Get(2); 
 
        double Cx = Ay*Bz - Az*By;  
        double Cy = Az*Bx - Ax*Bz;  
        double Cz = Ax*By - Ay*Bx;  
  
        return new FBVector4d_Wrapper(Cx, Cy, Cz, 0.0);     
    } 
 
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBVector4d->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 4; i++) 
        { 
            lReturnList.append((*mFBVector4d)[i]); 
        } 
        return lReturnList; 
    } 

    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBVector4d_Wrapper( boost::python::object pObject ) : mFBVector4d( new FBVector4d())
    {
        if( extract<int>( pObject.attr("__len__")()) == 4 ) {
            (mFBVector4d->operator double*())[0] = extract<double>( pObject[0] );
            (mFBVector4d->operator double*())[1] = extract<double>( pObject[1] );
            (mFBVector4d->operator double*())[2] = extract<double>( pObject[2] );
            (mFBVector4d->operator double*())[3] = extract<double>( pObject[3] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBVector4d_Wrapper()
    {
        delete mFBVector4d;
    };

    int GetCount() const
    {
        return 4;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBVector4d)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBVector4d)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBVector4d_Wrapper* FBVector4d_Wrapper_Factory( const FBVector4d& pFBVector4d )
{	
	return new FBVector4d_Wrapper( pFBVector4d );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBNormal
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBNormal_Init();

class PYSDK_DLL FBNormal_Wrapper {

public:
    FBNormal* mFBNormal;

    // CTOR
    FBNormal_Wrapper() : mFBNormal( new FBNormal())
    {
    };
    // CTOR
    FBNormal_Wrapper( const FBNormal& pFBNormal ) : mFBNormal( new FBNormal( pFBNormal ))
    {
    };
    // CTOR
    FBNormal_Wrapper( const FBNormal_Wrapper& pFBNormal ) : mFBNormal( new FBNormal( *( pFBNormal.mFBNormal )))
    {
    };
    // CTOR
    FBNormal_Wrapper( float p1, float p2, float p3 ) : mFBNormal( new FBNormal( p1, p2, p3 ))
    {
    };

    //CTOR 
    FBNormal_Wrapper( list pList ) : mFBNormal( new FBNormal()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBNormal_Wrapper* CopyFrom (const FBNormal_Wrapper &pNormal) 
    { 
        *mFBNormal = *(pNormal.mFBNormal); 
        return new FBNormal_Wrapper(*mFBNormal); 
    } 
    FBNormal_Wrapper* CopyFrom (list pData) 
    { 
        float lValues[4]; 
        if ( len( pData ) == 4 )         
        { 
            for ( int item = 0; item < 4; ++item ) 
            { 
                lValues[item] = extract<float>( pData[item] ); 
            } 
            mFBNormal->Set( (float*)lValues ); 
        } 
        return new FBNormal_Wrapper(*mFBNormal); 
    } 
  
    FBNormal_Wrapper*    operator+ (const FBNormal_Wrapper &pFBNormal) {return new FBNormal_Wrapper(this->Get(0)+pFBNormal.Get(0),this->Get(1)+pFBNormal.Get(1),this->Get(2)+pFBNormal.Get(2));} 
    FBNormal_Wrapper*    operator- (const FBNormal_Wrapper &pFBNormal) {return new FBNormal_Wrapper(this->Get(0)-pFBNormal.Get(0),this->Get(1)-pFBNormal.Get(1),this->Get(2)-pFBNormal.Get(2));} 
    FBNormal_Wrapper*    operator* (const FBNormal_Wrapper &pFBNormal) {return new FBNormal_Wrapper(this->Get(0)*pFBNormal.Get(0),this->Get(1)*pFBNormal.Get(1),this->Get(2)*pFBNormal.Get(2));} 
    FBNormal_Wrapper*    operator/ (const FBNormal_Wrapper &pFBNormal) {return new FBNormal_Wrapper(this->Get(0)/pFBNormal.Get(0),this->Get(1)/pFBNormal.Get(1),this->Get(2)/pFBNormal.Get(2));} 
  
    FBNormal_Wrapper* operator+ (double pD) {return new FBNormal_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD);} 
    FBNormal_Wrapper* operator- (double pD) {return new FBNormal_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD);} 
    FBNormal_Wrapper* operator* (double pD) {return new FBNormal_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD);} 
    FBNormal_Wrapper* operator/ (double pD) {return new FBNormal_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD);} 
  
    FBNormal_Wrapper& operator+= (const FBNormal_Wrapper &pFBNormal) { (*mFBNormal)[0] += pFBNormal.Get(0); (*mFBNormal)[1] += pFBNormal.Get(1); (*mFBNormal)[2] += pFBNormal.Get(2); return *this; } 
    FBNormal_Wrapper& operator-= (const FBNormal_Wrapper &pFBNormal) { (*mFBNormal)[0] -= pFBNormal.Get(0); (*mFBNormal)[1] -= pFBNormal.Get(1); (*mFBNormal)[2] -= pFBNormal.Get(2); return *this; } 
    FBNormal_Wrapper& operator*= (const FBNormal_Wrapper &pFBNormal) { (*mFBNormal)[0] *= pFBNormal.Get(0); (*mFBNormal)[1] *= pFBNormal.Get(1); (*mFBNormal)[2] *= pFBNormal.Get(2); return *this; } 
    FBNormal_Wrapper& operator/= (const FBNormal_Wrapper &pFBNormal) { (*mFBNormal)[0] /= pFBNormal.Get(0); (*mFBNormal)[1] /= pFBNormal.Get(1); (*mFBNormal)[2] /= pFBNormal.Get(2); return *this; } 
  
    FBNormal_Wrapper& operator+= (float pD) { (*mFBNormal)[0] += pD; (*mFBNormal)[1] += pD; (*mFBNormal)[2] += pD; return *this; } 
    FBNormal_Wrapper& operator-= (float pD) { (*mFBNormal)[0] -= pD; (*mFBNormal)[1] -= pD; (*mFBNormal)[2] -= pD; return *this; } 
    FBNormal_Wrapper& operator*= (float pD) { (*mFBNormal)[0] *= pD; (*mFBNormal)[1] *= pD; (*mFBNormal)[2] *= pD; return *this; } 
    FBNormal_Wrapper& operator/= (float pD) { (*mFBNormal)[0] /= pD; (*mFBNormal)[1] /= pD; (*mFBNormal)[2] /= pD; return *this; } 
  
    FBNormal_Wrapper* operator- () { return new FBNormal_Wrapper( -(*mFBNormal)[0], -(*mFBNormal)[1], -(*mFBNormal)[2]); } 
  
    bool NotEqual (const FBNormal_Wrapper &pFBNormal) 
    { 
        return mFBNormal->operator != (*(pFBNormal.mFBNormal)); 
    } 
    bool IsEqual (const FBNormal_Wrapper &pFBNormal) 
    { 
        return ! NotEqual(pFBNormal); 
    } 
  
    float Length () 
    { 
        float X, Y, Z; 
 
        X = (*mFBNormal)[0]; 
        Y = (*mFBNormal)[1]; 
        Z = (*mFBNormal)[2]; 
  
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    float SquareLength () 
    { 
        float X, Y, Z; 
  
        X = (*mFBNormal)[0]; 
        Y = (*mFBNormal)[1]; 
        Z = (*mFBNormal)[2]; 
  
        return X * X + Y * Y + Z * Z; 
    } 
  
    FBNormal_Wrapper* Normalize() 
    { 
        float Len = Length(); 
        if (Len==0.0) { 
            (*mFBNormal)[0] = 0.0; 
            (*mFBNormal)[1] = 0.0; 
            (*mFBNormal)[2] = 0.0; 
        } else { 
            (*mFBNormal)[0] /= Len; 
            (*mFBNormal)[1] /= Len; 
            (*mFBNormal)[2] /= Len; 
        } 
        return new FBNormal_Wrapper(*mFBNormal); 
    } 
  
    float DotProduct (const FBNormal_Wrapper &pFBNormal) {return this->Get(0)*pFBNormal.Get(0)+this->Get(1)*pFBNormal.Get(1)+this->Get(2)*pFBNormal.Get(2);} 
    FBNormal_Wrapper* CrossProduct (const FBNormal_Wrapper &pFBNormal) 
    { 
        float Ax = (*mFBNormal)[0]; 
        float Ay = (*mFBNormal)[1]; 
        float Az = (*mFBNormal)[2]; 
  
        float Bx = pFBNormal.Get(0); 
        float By = pFBNormal.Get(1);  
        float Bz = pFBNormal.Get(2); 
  
        float Cx = Ay*Bz - Az*By;  
        float Cy = Az*Bx - Ax*Bz;  
        float Cz = Ax*By - Ay*Bx;  
  
        return new FBNormal_Wrapper(Cx, Cy, Cz);     
    } 
  
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBNormal->operator float*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 4; i++) 
        { 
            lReturnList.append((*mFBNormal)[i]); 
        } 
         return lReturnList; 
    } 
 
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBNormal_Wrapper( boost::python::object pObject ) : mFBNormal( new FBNormal())
    {
        if( extract<int>( pObject.attr("__len__")()) == 3 ) {
            (mFBNormal->operator float*())[0] = extract<float>( pObject[0] );
            (mFBNormal->operator float*())[1] = extract<float>( pObject[1] );
            (mFBNormal->operator float*())[2] = extract<float>( pObject[2] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBNormal_Wrapper()
    {
        delete mFBNormal;
    };

    int GetCount() const
    {
        return 3;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    float Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBNormal)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, float lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBNormal)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBNormal_Wrapper* FBNormal_Wrapper_Factory( const FBNormal& pFBNormal )
{
	return new FBNormal_Wrapper( pFBNormal );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBVertex
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBVertex_Init();

class PYSDK_DLL FBVertex_Wrapper {

public:
    FBVertex* mFBVertex;

    // CTOR
    FBVertex_Wrapper() : mFBVertex( new FBVertex())
    {
    };
    // CTOR
    FBVertex_Wrapper( const FBVertex& pFBVertex ) : mFBVertex( new FBVertex( pFBVertex ))
    {
    };
    // CTOR
    FBVertex_Wrapper( const FBVertex_Wrapper& pFBVertex ) : mFBVertex( new FBVertex( *( pFBVertex.mFBVertex )))
    {
    };
    // CTOR
    FBVertex_Wrapper( float p1, float p2, float p3, float p4 ) : mFBVertex( new FBVertex( p1, p2, p3, p4 ))
    {
    };

    //CTOR 
    FBVertex_Wrapper( list pList ) : mFBVertex( new FBVertex()) 
    { 
        CopyFrom( pList ); 
    }; 
   
    FBVertex_Wrapper* CopyFrom (const FBVertex_Wrapper &pFBVertex) 
    { 
        *mFBVertex = *(pFBVertex.mFBVertex); 
        return new FBVertex_Wrapper(*mFBVertex); 
    } 
    FBVertex_Wrapper* CopyFrom (list pData) 
    { 
        float lValues[4]; 
        if ( len( pData ) == 4 )         
        { 
            for ( int item = 0; item < 4; ++item ) 
            { 
                lValues[item] = extract<float>( pData[item] ); 
            } 
            mFBVertex->Set( (float*)lValues ); 
        } 
        return new FBVertex_Wrapper(*mFBVertex); 
    } 
  
    FBVertex_Wrapper*    operator+ (const FBVertex_Wrapper &pFBVertex) {return new FBVertex_Wrapper(this->Get(0)+pFBVertex.Get(0),this->Get(1)+pFBVertex.Get(1),this->Get(2)+pFBVertex.Get(2),this->Get(2)+pFBVertex.Get(3));} 
    FBVertex_Wrapper*    operator- (const FBVertex_Wrapper &pFBVertex) {return new FBVertex_Wrapper(this->Get(0)-pFBVertex.Get(0),this->Get(1)-pFBVertex.Get(1),this->Get(2)-pFBVertex.Get(2),this->Get(2)+pFBVertex.Get(3));} 
    FBVertex_Wrapper*    operator* (const FBVertex_Wrapper &pFBVertex) {return new FBVertex_Wrapper(this->Get(0)*pFBVertex.Get(0),this->Get(1)*pFBVertex.Get(1),this->Get(2)*pFBVertex.Get(2),this->Get(2)+pFBVertex.Get(3));} 
    FBVertex_Wrapper*    operator/ (const FBVertex_Wrapper &pFBVertex) {return new FBVertex_Wrapper(this->Get(0)/pFBVertex.Get(0),this->Get(1)/pFBVertex.Get(1),this->Get(2)/pFBVertex.Get(2),this->Get(2)+pFBVertex.Get(3));} 
  
    FBVertex_Wrapper* operator+ (double pD) {return new FBVertex_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD,this->Get(3)+pD);} 
    FBVertex_Wrapper* operator- (double pD) {return new FBVertex_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD,this->Get(3)+pD);} 
    FBVertex_Wrapper* operator* (double pD) {return new FBVertex_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD,this->Get(3)+pD);} 
    FBVertex_Wrapper* operator/ (double pD) {return new FBVertex_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD,this->Get(3)+pD);} 
   
    FBVertex_Wrapper& operator+= (const FBVertex_Wrapper &pFBVertex) { (*mFBVertex)[0] += pFBVertex.Get(0); (*mFBVertex)[1] += pFBVertex.Get(1); (*mFBVertex)[2] += pFBVertex.Get(2); (*mFBVertex)[3] += pFBVertex.Get(3); return *this; } 
    FBVertex_Wrapper& operator-= (const FBVertex_Wrapper &pFBVertex) { (*mFBVertex)[0] -= pFBVertex.Get(0); (*mFBVertex)[1] -= pFBVertex.Get(1); (*mFBVertex)[2] -= pFBVertex.Get(2); (*mFBVertex)[3] += pFBVertex.Get(3); return *this; } 
    FBVertex_Wrapper& operator*= (const FBVertex_Wrapper &pFBVertex) { (*mFBVertex)[0] *= pFBVertex.Get(0); (*mFBVertex)[1] *= pFBVertex.Get(1); (*mFBVertex)[2] *= pFBVertex.Get(2); (*mFBVertex)[3] += pFBVertex.Get(3); return *this; } 
    FBVertex_Wrapper& operator/= (const FBVertex_Wrapper &pFBVertex) { (*mFBVertex)[0] /= pFBVertex.Get(0); (*mFBVertex)[1] /= pFBVertex.Get(1); (*mFBVertex)[2] /= pFBVertex.Get(2); (*mFBVertex)[3] += pFBVertex.Get(3); return *this; } 
   
    FBVertex_Wrapper& operator+= (float pD) { (*mFBVertex)[0] += pD; (*mFBVertex)[1] += pD; (*mFBVertex)[2] += pD; (*mFBVertex)[3] += pD; return *this; } 
    FBVertex_Wrapper& operator-= (float pD) { (*mFBVertex)[0] -= pD; (*mFBVertex)[1] -= pD; (*mFBVertex)[2] -= pD; (*mFBVertex)[3] += pD; return *this; } 
    FBVertex_Wrapper& operator*= (float pD) { (*mFBVertex)[0] *= pD; (*mFBVertex)[1] *= pD; (*mFBVertex)[2] *= pD; (*mFBVertex)[3] += pD; return *this; } 
    FBVertex_Wrapper& operator/= (float pD) { (*mFBVertex)[0] /= pD; (*mFBVertex)[1] /= pD; (*mFBVertex)[2] /= pD; (*mFBVertex)[3] += pD; return *this; } 
  
    FBVertex_Wrapper* operator- () { return new FBVertex_Wrapper( -(*mFBVertex)[0], -(*mFBVertex)[1], -(*mFBVertex)[2], -(*mFBVertex)[3]); } 
  
    bool NotEqual (const FBVertex_Wrapper &pFBVertex) 
     { 
        return mFBVertex->operator != (*(pFBVertex.mFBVertex)); 
    } 
     bool IsEqual (const FBVertex_Wrapper &pFBVertex) 
    { 
        return ! NotEqual(pFBVertex); 
    } 
   
    float Length () 
    { 
        float X, Y, Z; 
  
        X = (*mFBVertex)[0]; 
        Y = (*mFBVertex)[1]; 
        Z = (*mFBVertex)[2]; 
   
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    float SquareLength () 
     { 
        float X, Y, Z; 
  
        X = (*mFBVertex)[0]; 
        Y = (*mFBVertex)[1]; 
        Z = (*mFBVertex)[2]; 
 
        return X * X + Y * Y + Z * Z; 
    } 
    float Distance (const FBVertex_Wrapper &pFBVertex) 
    { 
  
        float    X, Y, Z; 
  
        X = (*mFBVertex)[0] - pFBVertex.Get(0); 
        Y = (*mFBVertex)[1] - pFBVertex.Get(0); 
        Z = (*mFBVertex)[2] - pFBVertex.Get(0); 
  
        return sqrt(X * X + Y * Y + Z * Z); 
    } 
    FBVertex_Wrapper* Normalize() 
    { 
        float Len = Length(); 
        if (Len==0.0) { 
            (*mFBVertex)[0] = 0.0; 
            (*mFBVertex)[1] = 0.0; 
            (*mFBVertex)[2] = 0.0; 
        } else { 
            (*mFBVertex)[0] /= Len; 
            (*mFBVertex)[1] /= Len; 
            (*mFBVertex)[2] /= Len; 
        } 
        return new FBVertex_Wrapper(*mFBVertex); 
    } 
   
    float DotProduct (const FBVertex_Wrapper &pFBVertex) {return this->Get(0)*pFBVertex.Get(0)+this->Get(1)*pFBVertex.Get(1)+this->Get(2)*pFBVertex.Get(2);} 
    FBVertex_Wrapper* CrossProduct (const FBVertex_Wrapper &pFBVertex) 
    { 
        float Ax = (*mFBVertex)[0]; 
        float Ay = (*mFBVertex)[1]; 
        float Az = (*mFBVertex)[2]; 
  
        float Bx = pFBVertex.Get(0); 
        float By = pFBVertex.Get(1);  
        float Bz = pFBVertex.Get(2); 
  
        float Cx = Ay*Bz - Az*By;  
        float Cy = Az*Bx - Ax*Bz;  
        float Cz = Ax*By - Ay*Bx;  
  
        return new FBVertex_Wrapper(Cx, Cy, Cz, (*mFBVertex)[3]);     
   } 
    
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBVertex->operator float*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 4; i++) 
        { 
            lReturnList.append(mFBVertex->operator float*()[i]); 
        } 
        return lReturnList; 
    } 
  
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBVertex_Wrapper( boost::python::object pObject ) : mFBVertex( new FBVertex())
    {
        if( extract<int>( pObject.attr("__len__")()) == 4 ) {
            (mFBVertex->operator float*())[0] = extract<float>( pObject[0] );
            (mFBVertex->operator float*())[1] = extract<float>( pObject[1] );
            (mFBVertex->operator float*())[2] = extract<float>( pObject[2] );
            (mFBVertex->operator float*())[3] = extract<float>( pObject[3] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBVertex_Wrapper()
    {
        delete mFBVertex;
    };

    int GetCount() const
    {
        return 4;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    float Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBVertex)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, float lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBVertex)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBVertex_Wrapper* FBVertex_Wrapper_Factory( const FBVertex& pFBVertex )
{	
	return new FBVertex_Wrapper( pFBVertex );
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBUV
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBUV_Init();

class PYSDK_DLL FBUV_Wrapper {

public:
    FBUV* mFBUV;

    // CTOR
    FBUV_Wrapper() : mFBUV( new FBUV())
    {
    };
    // CTOR
    FBUV_Wrapper( const FBUV& pFBUV ) : mFBUV( new FBUV( pFBUV ))
    {
    };
    // CTOR
    FBUV_Wrapper( const FBUV_Wrapper& pFBUV ) : mFBUV( new FBUV( *( pFBUV.mFBUV )))
    {
    };
    // CTOR
    FBUV_Wrapper( float p1, float p2 ) : mFBUV( new FBUV( p1, p2 ))
    {
    };

    FBUV_Wrapper( list pList ) : mFBUV( new FBUV()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBUV_Wrapper* CopyFrom (const FBUV_Wrapper &FBUV) 
    { 
        *mFBUV = *(FBUV.mFBUV); 
        return new FBUV_Wrapper(*mFBUV); 
    } 
    FBUV_Wrapper* CopyFrom (list pData) 
    { 
        float lValues[2]; 
        if ( len( pData ) == 2 )         
        { 
            for ( int item = 0; item < 2; ++item ) 
            { 
                lValues[item] = extract<float>( pData[item] ); 
            } 
            mFBUV->Set( (float*)lValues ); 
        } 
        return new FBUV_Wrapper(*mFBUV); 
    } 
 
    FBUV_Wrapper*    operator+ (const FBUV_Wrapper &pFBUV) {return new FBUV_Wrapper(this->Get(0)+pFBUV.Get(0),this->Get(1)+pFBUV.Get(1));} 
    FBUV_Wrapper*    operator- (const FBUV_Wrapper &pFBUV) {return new FBUV_Wrapper(this->Get(0)-pFBUV.Get(0),this->Get(1)-pFBUV.Get(1));} 
    FBUV_Wrapper*    operator* (const FBUV_Wrapper &pFBUV) {return new FBUV_Wrapper(this->Get(0)*pFBUV.Get(0),this->Get(1)*pFBUV.Get(1));} 
    FBUV_Wrapper*    operator/ (const FBUV_Wrapper &pFBUV) {return new FBUV_Wrapper(this->Get(0)/pFBUV.Get(0),this->Get(1)/pFBUV.Get(1));} 
  
    FBUV_Wrapper* operator+ (double pD) {return new FBUV_Wrapper(this->Get(0)+pD,this->Get(1)+pD);} 
    FBUV_Wrapper* operator- (double pD) {return new FBUV_Wrapper(this->Get(0)-pD,this->Get(1)-pD);} 
    FBUV_Wrapper* operator* (double pD) {return new FBUV_Wrapper(this->Get(0)*pD,this->Get(1)*pD);} 
    FBUV_Wrapper* operator/ (double pD) {return new FBUV_Wrapper(this->Get(0)/pD,this->Get(1)/pD);} 
  
    FBUV_Wrapper& operator+= (const FBUV_Wrapper &pFBUV) { (*mFBUV) [0] += pFBUV.Get(0); (*mFBUV) [1] += pFBUV.Get(1); return *this; } 
    FBUV_Wrapper& operator-= (const FBUV_Wrapper &pFBUV) { (*mFBUV) [0] -= pFBUV.Get(0); (*mFBUV) [1] -= pFBUV.Get(1); return *this; } 
    FBUV_Wrapper& operator*= (const FBUV_Wrapper &pFBUV) { (*mFBUV) [0] *= pFBUV.Get(0); (*mFBUV) [1] *= pFBUV.Get(1); return *this; } 
    FBUV_Wrapper& operator/= (const FBUV_Wrapper &pFBUV) { (*mFBUV) [0] /= pFBUV.Get(0); (*mFBUV) [1] /= pFBUV.Get(1); return *this; } 
   
    FBUV_Wrapper& operator+= (float pD) { (*mFBUV) [0] += pD; (*mFBUV) [1] += pD; return *this; } 
    FBUV_Wrapper& operator-= (float pD) { (*mFBUV) [0] -= pD; (*mFBUV) [1] -= pD; return *this; } 
    FBUV_Wrapper& operator*= (float pD) { (*mFBUV) [0] *= pD; (*mFBUV) [1] *= pD; return *this; } 
    FBUV_Wrapper& operator/= (float pD) { (*mFBUV) [0] /= pD; (*mFBUV) [1] /= pD; return *this; } 
  
    FBUV_Wrapper* operator- () { return new FBUV_Wrapper( -(*mFBUV) [0], -(*mFBUV) [1]); } 
   
    bool NotEqual (const FBUV_Wrapper &pFBUV) 
    { 
        return mFBUV->operator != (*(pFBUV.mFBUV)) ; 
    } 
    bool IsEqual (const FBUV_Wrapper &pFBUV) 
    { 
        return ! NotEqual(pFBUV); 
    } 
 
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBUV->operator float*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 2; i++) 
        { 
            lReturnList.append(mFBUV->operator float*()[i]); 
        } 
        return lReturnList; 
    } 

    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBUV_Wrapper( boost::python::object pObject ) : mFBUV( new FBUV())
    {
        if( extract<int>( pObject.attr("__len__")()) == 2 ) {
            (mFBUV->operator float*())[0] = extract<float>( pObject[0] );
            (mFBUV->operator float*())[1] = extract<float>( pObject[1] );
        }
        else{
            // ???
        }
    };
    // DTOR
    ~FBUV_Wrapper()
    {
        delete mFBUV;
    };

    int GetCount() const
    {
        return 2;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    float Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
            return 0;
        }
        return (*mFBUV)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, float lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
            return;
        }
        (*mFBUV)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBUV_Wrapper* FBUV_Wrapper_Factory( const FBUV& pFBUV )
{	
    return new FBUV_Wrapper( pFBUV );
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBColor
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBColor_Init();

class PYSDK_DLL FBColor_Wrapper {

public:
    FBColor* mFBColor;

    // CTOR
    FBColor_Wrapper() : mFBColor( new FBColor())
    {
    };
    // CTOR
    FBColor_Wrapper( const FBColor& pFBColor ) : mFBColor( new FBColor( pFBColor ))
    {
    };
    // CTOR
    FBColor_Wrapper( const FBColor_Wrapper& pFBColor ) : mFBColor( new FBColor( *( pFBColor.mFBColor )))
    {
    };
    // CTOR
    FBColor_Wrapper( double p1, double p2, double p3 ) : mFBColor( new FBColor( p1, p2, p3 ))
    {
    };

    //CTOR 
    FBColor_Wrapper( list pList ) : mFBColor( new FBColor()) 
    { 
        CopyFrom( pList ); 
    }; 
   
    FBColor_Wrapper* CopyFrom (const FBColor_Wrapper &pFBColor) 
    { 
        *mFBColor = *(pFBColor.mFBColor); 
        return new FBColor_Wrapper(*mFBColor); 
    } 
    FBColor_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[3]; 
        if ( len( pData ) == 3 )         
        { 
            for ( int item = 0; item < 3; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
            } 
            mFBColor->Set( (double*)lValues ); 
        } 
        return new FBColor_Wrapper(*mFBColor); 
    } 
   
    FBColor_Wrapper*    operator+ (const FBColor_Wrapper &pFBColor) {return new FBColor_Wrapper(this->Get(0)+pFBColor.Get(0),this->Get(1)+pFBColor.Get(1),this->Get(2)+pFBColor.Get(2));} 
    FBColor_Wrapper*    operator- (const FBColor_Wrapper &pFBColor) {return new FBColor_Wrapper(this->Get(0)-pFBColor.Get(0),this->Get(1)-pFBColor.Get(1),this->Get(2)-pFBColor.Get(2));} 
    FBColor_Wrapper*    operator* (const FBColor_Wrapper &pFBColor) {return new FBColor_Wrapper(this->Get(0)*pFBColor.Get(0),this->Get(1)*pFBColor.Get(1),this->Get(2)*pFBColor.Get(2));} 
    FBColor_Wrapper*    operator/ (const FBColor_Wrapper &pFBColor) {return new FBColor_Wrapper(this->Get(0)/pFBColor.Get(0),this->Get(1)/pFBColor.Get(1),this->Get(2)/pFBColor.Get(2));} 
  
    FBColor_Wrapper* operator+ (double pD) {return new FBColor_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD);} 
    FBColor_Wrapper* operator- (double pD) {return new FBColor_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD);} 
    FBColor_Wrapper* operator* (double pD) {return new FBColor_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD);} 
    FBColor_Wrapper* operator/ (double pD) {return new FBColor_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD);} 
  
    FBColor_Wrapper& operator+= (const FBColor_Wrapper &pFBColor) { (*mFBColor)[0] += pFBColor.Get(0); (*mFBColor)[1] += pFBColor.Get(1); (*mFBColor)[2] += pFBColor.Get(2); return *this; } 
    FBColor_Wrapper& operator-= (const FBColor_Wrapper &pFBColor) { (*mFBColor)[0] -= pFBColor.Get(0); (*mFBColor)[1] -= pFBColor.Get(1); (*mFBColor)[2] -= pFBColor.Get(2); return *this; } 
    FBColor_Wrapper& operator*= (const FBColor_Wrapper &pFBColor) { (*mFBColor)[0] *= pFBColor.Get(0); (*mFBColor)[1] *= pFBColor.Get(1); (*mFBColor)[2] *= pFBColor.Get(2); return *this; } 
    FBColor_Wrapper& operator/= (const FBColor_Wrapper &pFBColor) { (*mFBColor)[0] /= pFBColor.Get(0); (*mFBColor)[1] /= pFBColor.Get(1); (*mFBColor)[2] /= pFBColor.Get(2); return *this; } 
  
    FBColor_Wrapper& operator+= (double pD) { (*mFBColor)[0] += pD; (*mFBColor)[1] += pD; (*mFBColor)[2] += pD; return *this; } 
    FBColor_Wrapper& operator-= (double pD) { (*mFBColor)[0] -= pD; (*mFBColor)[1] -= pD; (*mFBColor)[2] -= pD; return *this; } 
    FBColor_Wrapper& operator*= (double pD) { (*mFBColor)[0] *= pD; (*mFBColor)[1] *= pD; (*mFBColor)[2] *= pD; return *this; } 
    FBColor_Wrapper& operator/= (double pD) { (*mFBColor)[0] /= pD; (*mFBColor)[1] /= pD; (*mFBColor)[2] /= pD; return *this; } 
  
    FBColor_Wrapper* operator- () { return new FBColor_Wrapper( -(*mFBColor)[0], -(*mFBColor)[1], -(*mFBColor)[2]); } 

    bool operator ==(const FBColor_Wrapper &pFBColor) const { return mFBColor->operator == (*(pFBColor.mFBColor)); }
    bool operator !=(const FBColor_Wrapper &pFBColor) const { return mFBColor->operator != (*(pFBColor.mFBColor)); }
 
    bool NotEqual (const FBColor_Wrapper &pFBColor) 
    { 
        return mFBColor->operator != (*(pFBColor.mFBColor)); 
    } 
    bool IsEqual (const FBColor_Wrapper &pFBColor) 
    { 
        return ! NotEqual(pFBColor); 
    } 

    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBColor->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 3; i++) 
        { 
            lReturnList.append((*mFBColor)[i]); 
        } 
        return lReturnList; 
    } 

    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBColor_Wrapper( boost::python::object pObject ) : mFBColor( new FBColor())
    {
        int lArgs = extract<int>( pObject.attr("__len__")());
        if( lArgs == 3 ) {
            (mFBColor->operator double*())[0] = extract<double>( pObject[0] );
            (mFBColor->operator double*())[1] = extract<double>( pObject[1] );
            (mFBColor->operator double*())[2] = extract<double>( pObject[2] );
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBColor_Wrapper()
    {
        delete mFBColor;
    };

    int GetCount() const
    {
        return 3;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBColor)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBColor)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBColor_Wrapper* FBColor_Wrapper_Factory( const FBColor& pFBColor )
{
	return new FBColor_Wrapper( pFBColor );
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBColorAndAlpha
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBColorAndAlpha_Init();

class PYSDK_DLL FBColorAndAlpha_Wrapper {

public:
    FBColorAndAlpha* mFBColorAndAlpha;

    // CTOR
    FBColorAndAlpha_Wrapper() : mFBColorAndAlpha( new FBColorAndAlpha())
    {
    };
    // CTOR
    FBColorAndAlpha_Wrapper( const FBColorAndAlpha& pFBColorAndAlpha ) : mFBColorAndAlpha( new FBColorAndAlpha( pFBColorAndAlpha ))
    {
    };
    // CTOR
    FBColorAndAlpha_Wrapper( const FBColorF& pColorF ) : mFBColorAndAlpha( new FBColorAndAlpha( pColorF ))
    {
    };
    // CTOR
    FBColorAndAlpha_Wrapper( const FBColorAndAlpha_Wrapper& pFBColorAndAlpha ) : mFBColorAndAlpha( new FBColorAndAlpha( *( pFBColorAndAlpha.mFBColorAndAlpha )))
    {
    };
    // CTOR
    FBColorAndAlpha_Wrapper( double p1, double p2, double p3, double p4 = 1.0 ) : mFBColorAndAlpha( new FBColorAndAlpha( p1, p2, p3, p4 ))
    {
    };

    //CTOR 
    FBColorAndAlpha_Wrapper( list pList ) : mFBColorAndAlpha( new FBColorAndAlpha()) 
    { 
        CopyFrom( pList ); 
    }; 
  
    FBColorAndAlpha_Wrapper* CopyFrom (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) 
    { 
        *mFBColorAndAlpha = *(pFBColorAndAlpha.mFBColorAndAlpha); 
        return new FBColorAndAlpha_Wrapper(*mFBColorAndAlpha); 
    } 
    FBColorAndAlpha_Wrapper* CopyFrom (list pData) 
    { 
        double lValues[4]; 
        if ( len( pData ) == 4 )         
        { 
            for ( int item = 0; item < 4; ++item ) 
            { 
                lValues[item] = extract<double>( pData[item] ); 
            } 
            mFBColorAndAlpha->Set( (double*)lValues ); 
        } 
        return new FBColorAndAlpha_Wrapper(*mFBColorAndAlpha); 
    } 
  
    FBColorAndAlpha_Wrapper*    operator+ (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) {return new FBColorAndAlpha_Wrapper(this->Get(0)+pFBColorAndAlpha.Get(0),this->Get(1)+pFBColorAndAlpha.Get(1),this->Get(2)+pFBColorAndAlpha.Get(2),this->Get(3)+pFBColorAndAlpha.Get(3));} 
    FBColorAndAlpha_Wrapper*    operator- (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) {return new FBColorAndAlpha_Wrapper(this->Get(0)-pFBColorAndAlpha.Get(0),this->Get(1)-pFBColorAndAlpha.Get(1),this->Get(2)-pFBColorAndAlpha.Get(2),this->Get(3)-pFBColorAndAlpha.Get(3));} 
    FBColorAndAlpha_Wrapper*    operator* (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) {return new FBColorAndAlpha_Wrapper(this->Get(0)*pFBColorAndAlpha.Get(0),this->Get(1)*pFBColorAndAlpha.Get(1),this->Get(2)*pFBColorAndAlpha.Get(2),this->Get(3)*pFBColorAndAlpha.Get(3));} 
    FBColorAndAlpha_Wrapper*    operator/ (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) {return new FBColorAndAlpha_Wrapper(this->Get(0)/pFBColorAndAlpha.Get(0),this->Get(1)/pFBColorAndAlpha.Get(1),this->Get(2)/pFBColorAndAlpha.Get(2),this->Get(3)/pFBColorAndAlpha.Get(3));} 
  
    FBColorAndAlpha_Wrapper* operator+ (double pD) {return new FBColorAndAlpha_Wrapper(this->Get(0)+pD,this->Get(1)+pD,this->Get(2)+pD,this->Get(3)+pD);} 
    FBColorAndAlpha_Wrapper* operator- (double pD) {return new FBColorAndAlpha_Wrapper(this->Get(0)-pD,this->Get(1)-pD,this->Get(2)-pD,this->Get(3)-pD);} 
    FBColorAndAlpha_Wrapper* operator* (double pD) {return new FBColorAndAlpha_Wrapper(this->Get(0)*pD,this->Get(1)*pD,this->Get(2)*pD,this->Get(3)*pD);} 
    FBColorAndAlpha_Wrapper* operator/ (double pD) {return new FBColorAndAlpha_Wrapper(this->Get(0)/pD,this->Get(1)/pD,this->Get(2)/pD,this->Get(3)-pD);} 
  
    FBColorAndAlpha_Wrapper& operator+= (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) { (*mFBColorAndAlpha)[0] += pFBColorAndAlpha.Get(0); (*mFBColorAndAlpha)[1] += pFBColorAndAlpha.Get(1); (*mFBColorAndAlpha)[2] += pFBColorAndAlpha.Get(2); (*mFBColorAndAlpha)[3] += pFBColorAndAlpha.Get(3); return *this; } 
    FBColorAndAlpha_Wrapper& operator-= (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) { (*mFBColorAndAlpha)[0] -= pFBColorAndAlpha.Get(0); (*mFBColorAndAlpha)[1] -= pFBColorAndAlpha.Get(1); (*mFBColorAndAlpha)[2] -= pFBColorAndAlpha.Get(2); (*mFBColorAndAlpha)[3] -= pFBColorAndAlpha.Get(3); return *this; } 
    FBColorAndAlpha_Wrapper& operator*= (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) { (*mFBColorAndAlpha)[0] *= pFBColorAndAlpha.Get(0); (*mFBColorAndAlpha)[1] *= pFBColorAndAlpha.Get(1); (*mFBColorAndAlpha)[2] *= pFBColorAndAlpha.Get(2); (*mFBColorAndAlpha)[3] *= pFBColorAndAlpha.Get(3); return *this; } 
    FBColorAndAlpha_Wrapper& operator/= (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) { (*mFBColorAndAlpha)[0] /= pFBColorAndAlpha.Get(0); (*mFBColorAndAlpha)[1] /= pFBColorAndAlpha.Get(1); (*mFBColorAndAlpha)[2] /= pFBColorAndAlpha.Get(2); (*mFBColorAndAlpha)[3] /= pFBColorAndAlpha.Get(3); return *this; } 
   
    FBColorAndAlpha_Wrapper& operator+= (double pD) { (*mFBColorAndAlpha)[0] += pD; (*mFBColorAndAlpha)[1] += pD; (*mFBColorAndAlpha)[2] += pD; (*mFBColorAndAlpha)[3] += pD; return *this; } 
    FBColorAndAlpha_Wrapper& operator-= (double pD) { (*mFBColorAndAlpha)[0] -= pD; (*mFBColorAndAlpha)[1] -= pD; (*mFBColorAndAlpha)[2] -= pD; (*mFBColorAndAlpha)[3] -= pD; return *this; } 
    FBColorAndAlpha_Wrapper& operator*= (double pD) { (*mFBColorAndAlpha)[0] *= pD; (*mFBColorAndAlpha)[1] *= pD; (*mFBColorAndAlpha)[2] *= pD; (*mFBColorAndAlpha)[3] *= pD; return *this; } 
    FBColorAndAlpha_Wrapper& operator/= (double pD) { (*mFBColorAndAlpha)[0] /= pD; (*mFBColorAndAlpha)[1] /= pD; (*mFBColorAndAlpha)[2] /= pD; (*mFBColorAndAlpha)[3] /= pD; return *this; } 
   
    FBColorAndAlpha_Wrapper* operator- () { return new FBColorAndAlpha_Wrapper( -(*mFBColorAndAlpha)[0], -(*mFBColorAndAlpha)[1], -(*mFBColorAndAlpha)[2], -(*mFBColorAndAlpha)[3]); } 
  
    bool operator ==(const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) const { return mFBColorAndAlpha->operator == (*(pFBColorAndAlpha.mFBColorAndAlpha)); }
    bool operator !=(const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) const { return mFBColorAndAlpha->operator != (*(pFBColorAndAlpha.mFBColorAndAlpha)); }

    bool NotEqual (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) 
    { 
        return mFBColorAndAlpha->operator != (*(pFBColorAndAlpha.mFBColorAndAlpha)); 
    } 
    bool IsEqual (const FBColorAndAlpha_Wrapper &pFBColorAndAlpha) 
    { 
        return ! NotEqual(pFBColorAndAlpha); 
    } 
  
    kReference GetBufferAddress() const 
    { 
        return (kReference)mFBColorAndAlpha->operator double*();
    }

    list GetList () 
    { 
        list lReturnList; 
        for(int i = 0; i < 4; i++) 
        { 
            lReturnList.append((*mFBColorAndAlpha)[i]); 
        } 
        return lReturnList; 
   } 
 
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    // CTOR
    FBColorAndAlpha_Wrapper( boost::python::object pObject ) : mFBColorAndAlpha( new FBColorAndAlpha())
    {
        int lArgs = extract<int>( pObject.attr("__len__")());
        if( lArgs == 3 || lArgs == 4 ) {
            (mFBColorAndAlpha->operator double*())[0] = extract<double>( pObject[0] );
            (mFBColorAndAlpha->operator double*())[1] = extract<double>( pObject[1] );
            (mFBColorAndAlpha->operator double*())[2] = extract<double>( pObject[2] );
            if( lArgs == 4 )
            {
                (mFBColorAndAlpha->operator double*())[3] = extract<double>( pObject[3] );
            }
            else
            {
                (mFBColorAndAlpha->operator double*())[3] = 1.0;
            }
        }
        else{
            // ???
        }
     };
    // DTOR
    ~FBColorAndAlpha_Wrapper()
    {
        delete mFBColorAndAlpha;
    };

    int GetCount() const
    {
        return 4;
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    double Get( int lIdx ) const
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return 0;
        }
        return (*mFBColorAndAlpha)[lIdx];
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    void Set( int lIdx, double lValue )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"vector index out of range");
            throw_error_already_set();
			return;
        }
        (*mFBColorAndAlpha)[lIdx] = lValue;
    };
};

PYSDK_DLL inline FBColorAndAlpha_Wrapper* FBColorAndAlpha_Wrapper_Factory( const FBColorAndAlpha& pFBColorAndAlpha )
{
	return new FBColorAndAlpha_Wrapper( pFBColorAndAlpha );
}

PYSDK_DLL inline FBColorAndAlpha_Wrapper* FBColorAndAlpha_Wrapper_Factory( const FBColorF& pFBColorF )
{
	return new FBColorAndAlpha_Wrapper( pFBColorF );
}

#endif // pyfbvector_h__