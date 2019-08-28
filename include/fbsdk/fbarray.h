#ifndef __FBARRAY_H__
#define __FBARRAY_H__
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

/** \file fbarray.h
*	A template class for arrays.
*/
#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Ensure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbversion.h>

#include <assert.h>
#include <string.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

/**	General allocation function, actually calling standard function "realloc".
*	\param	memblock		Memory block to reallocate.
*	\param	size			Size of block to allocate
*	\return	new allocated or resized block.
*/
FBSDK_DLL void* FBRealloc(void* memblock, size_t size);

/**	General free function, actually calling standard function "free".
*	\param	memblock		Memory block to free.
*/
FBSDK_DLL void FBFree(void* memblock);

////////////////////////////////////////////////////////////////////////////////////
// FBArrayTemplate
////////////////////////////////////////////////////////////////////////////////////
/**	Template class to contain an array of items.
*   \note This utility template array only support plain old data structure (POD). 
*/
template <class Type> class FBArrayTemplate 
{
  public:
	/** Constructor.
	*	\param pItemPerBlock	Number of items per array block (default is 10).
	*/
	inline FBArrayTemplate(int pItemPerBlock=10) 
	{
		mArray          = NULL;
		mArrayCount     = 0;
		mBlockCount     = 0;
		mItemPerBlock   = pItemPerBlock;    
	}

    //! Copy constructor.
    inline FBArrayTemplate(const FBArrayTemplate<Type>& pArrayTemplate)
    { 
        mArray          = NULL;
        mArrayCount     = 0;
        mBlockCount     = 0;
        mItemPerBlock   = 10;    

        *this = pArrayTemplate; 
    }

	//! Destructor.
    inline ~FBArrayTemplate()
	{
		Clear();
	}

	/**	Insert \e pItem at \e pIndex.
	* 	\param pIndex	Index to insert at.
	* 	\param pItem	Item to insert.
	* 	\return Actual insertion index where \e pItem was inserted.
	*/
    inline int InsertAt ( int pIndex, Type pItem)
	{
		if (pIndex>mArrayCount) 
		{
			pIndex = mArrayCount;
		}

		if (mArrayCount>= mBlockCount*mItemPerBlock) 
		{
			 // must allocate or reallocate block of items
			  mBlockCount++;
			  mArray = (Type *)FBRealloc( mArray,(size_t)(mBlockCount*mItemPerBlock*sizeof(Type)));
		}

		if (pIndex<mArrayCount) 
		{
			// This is an insert
			memmove (&(mArray[pIndex+1]),&(mArray[pIndex]),sizeof(Type)*(mArrayCount-pIndex));
		}

		mArray[pIndex] = pItem;
		mArrayCount++;

		return pIndex;
	}

	/**	Remove item at \e pIndex.
	*	\param pIndex Index to remove item from.
	*/
    inline void RemoveAt ( int pIndex )
	{
		assert( pIndex<mArrayCount );
		if (pIndex+1<mArrayCount) {
			memmove (&(mArray[pIndex]),&(mArray[pIndex+1]),sizeof(Type)*(mArrayCount-pIndex-1));
		}
		mArrayCount --;
		memset (&(mArray[mArrayCount]),0,sizeof(Type));	// Cleanup last element to make sure we don't access it later
	}
	
	
	//!	Remove the last item in the array.
    inline void RemoveLast() { RemoveAt( mArrayCount-1 ); }	

	/**	Remove \e pItem from the array.
	*	\param pItem 	Item to remove.
	*	\return	Operation was successful (\b true or \b false).
	*/
    inline bool Remove ( Type &pItem )
	{
	  int Index = Find( pItem );
	    if (Index>=0) {
			RemoveAt( Index );
			return true;
		}
		return false;
	}

	/**	Remove \e pItem from the array.
	*	\param pItem Item to remove.
	*	\return Outcome of removal (true or false).
	*/
    inline bool RemoveIt ( Type pItem )
	{
	  int Index = Find( pItem );
	    if (Index>=0) {
			RemoveAt( Index );
			return true;
		}
		return false;
	}

	//!	Empty the array of all items.
    inline void Clear()
	{
		if (mArray!=NULL) {
			FBFree(mArray);
			mArray = NULL;
		}
		mArrayCount  = 0L;
		mBlockCount  = 0L;
	}

	/**	[] operator overload.
	*	\param pIndex Index of item to access.
	*	\return Item corresponding to \e pIndex.
	*/
    inline Type &operator[](int pIndex) const
	{
		assert( pIndex<mArrayCount );
		return mArray[pIndex];
	}

	/**	Set item at \e pIndex to \e pItem.
	*	\param pIndex	Index of item to set.
	*	\param pItem	Item to copy into the array.
	*/
    inline void SetAt(int pIndex,Type pItem)
	{
		assert( pIndex<mArrayCount );
		mArray[pIndex] = pItem;
	}

	/**	Set the last item of the array.
	*	\param pItem Item to copy as the last item of the array
	*	\warning Will write over last item in the array!
	*/
    inline void SetLast(Type pItem) 
	{ 
		SetAt(mArrayCount-1,pItem ); 
	}

	/** Get the number of items in the array.
	*	\return Number of items in the array.
	*/
	inline int GetCount () const
	{ 
		return mArrayCount; 
	}

	/** Set the number of items in the array.
	*/
	inline void SetCount(int pCount)
	{
		if (pCount > mArrayCount)
		{
			if( pCount )
			{
				const int lTempNewBlockCount = ( (int) (mArrayCount+pCount + mItemPerBlock - 1 ) / mItemPerBlock );
				const int lNewBlockCount = (lTempNewBlockCount > 1 ? lTempNewBlockCount : 1);

				const int lOldArraySize = mArrayCount*sizeof(Type);
				const int lNewArraySize = lNewBlockCount*mItemPerBlock*sizeof(Type);

				if( lNewBlockCount > (int) mBlockCount )
				{			
					mArray = (Type *)FBRealloc( mArray, (size_t) lNewArraySize );
					mBlockCount = lNewBlockCount;
				}
				
				memset( ((char *)mArray) + lOldArraySize, 0, (size_t) (lNewArraySize-lOldArraySize) );
				mArrayCount += pCount;
			}
		} else 
		{
			mArrayCount = pCount;
		}
	}

	/** Get item at \e pIndex.
	*	\param pIndex Index of desired item.
	*	\return Item specified by \e pIndex.
	*/
	inline Type GetAt(int pIndex) 
	{ 		
		assert( pIndex<mArrayCount );
		return mArray[pIndex]; 
	}

	/** Get last item of the array.
	*	\return Last item of the array.
	*/
	inline Type GetLast()			
	{ 
		return mArray[mArrayCount-1]; 
	}

	/**	Find the index of \e pItem in the array.
	*	\param pItem	Item to look for in the array.
	*	\return Index number of element found. Returns -1 if \e pItem was not found.
	*/
    inline int Find( Type pItem )
	{
	  int Count;
		for (Count=0; Count<mArrayCount; Count++) {
			if (mArray[Count]==pItem) {
				return Count;
			}
		}
		return -1;
	}

	/** Add an item to the end of the array.
	*	\param pItem Item to insert into the array.
	*	\return Index where \e pItem was inserted.
	*/
    inline int Add( Type pItem ) 
	{ 
		return InsertAt( mArrayCount,pItem ); 
	}

	/** Get a pointer to the array of items.
	*	\return Pointer to the array of items.
	*	\warning Gives direct access to the array pointer!
	*/
    inline Type *GetArray() 
	{ 
		return mArray; 
	}

	/** Copy array of pointers without copying the associated objects.
	*   \param pArrayTemplate Array to copy from.
	*   \return Pointer to the this class. 
	*/
	inline FBArrayTemplate<Type>& operator=(const FBArrayTemplate<Type>& pArrayTemplate)
    {
        if (this != &pArrayTemplate)
        {
            Clear();

            mItemPerBlock = pArrayTemplate.mItemPerBlock;

            SetCount(pArrayTemplate.GetCount());
            memcpy(mArray, pArrayTemplate.mArray, sizeof(Type) * pArrayTemplate.GetCount());
        }

		return (*this);
	}

  private:
    Type      *mArray;			
    int       mArrayCount;		
    int       mBlockCount;		
    int       mItemPerBlock;
};

/** Pre-defined common used array types. 
*/
typedef class FBSDK_DLL FBArrayTemplate<bool *>	        FBArrayHBool;
typedef class FBSDK_DLL FBArrayTemplate<char *>	        FBArrayHChar;
typedef class FBSDK_DLL FBArrayTemplate<int *>	        FBArrayHkInt;
typedef class FBSDK_DLL FBArrayTemplate<unsigned int *>	FBArrayHkUInt;
typedef class FBSDK_DLL FBArrayTemplate<float *>	    FBArrayHkFloat;
typedef class FBSDK_DLL FBArrayTemplate<double *>	    FBArrayHkDouble;
typedef class FBSDK_DLL FBArrayTemplate<void *>	        FBArrayHVoid;

typedef class FBSDK_DLL FBArrayTemplate<bool>	        FBArrayBool;
typedef class FBSDK_DLL FBArrayTemplate<char>	        FBArrayChar;
typedef class FBSDK_DLL FBArrayTemplate<int>		    FBArrayInt;
typedef class FBSDK_DLL FBArrayTemplate<unsigned int>	FBArrayUInt;
typedef class FBSDK_DLL FBArrayTemplate<float>	        FBArrayFloat;
typedef class FBSDK_DLL FBArrayTemplate<double>	        FBArrayDouble;

/** Define an array (template) for a component (discard the FB..).
*	Define a type corresponding to the array in the header file.
*	\param	DllTag		Associated DLL.
*	\param	Type		Type (component) to register as an array (discard the FB).
*/
#define FB_DEFINE_ARRAY( DllTag, Type ) \
	typedef class DllTag FBArrayTemplate< FB##Type* > FBArray##Type;

/** Implement an array.
*	Instanciates the template class in the *.cxx file.
*	\param	DllTag		Associated DLL.
*	\param	Type		Type to register as an array.
*/
#if defined(KARCH_DEV_INTEL)
	#define FBImplementArray( DllTag, Type ) 
#else
	#define FBImplementArray( DllTag, Type ) \
		template class DllTag FBSDKNamespaceFunc( FBArrayTemplate ) < FB##Type* >;
#endif


#ifdef FBSDKUseNamespace
	}
#endif
#endif // __FBARRAY_H

