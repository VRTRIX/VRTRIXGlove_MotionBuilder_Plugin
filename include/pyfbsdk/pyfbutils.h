#ifndef pyfbutils_h__
#define pyfbutils_h__
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

template<class T>
void ValidateIndexAccess( int pIndex, T* pObject, int (T::*pGetCountAccessor)() )
{
    assert( pObject );
    if ( pIndex < 0 || pIndex >= (pObject->*pGetCountAccessor)() )
    {
        PyErr_SetString(PyExc_IndexError,"index out of range");
        throw_error_already_set();
    }
}

template<class T>
list ArrayToPyList(const T* pArray, int pStride, int pComponentCount, int pArrayCount)
{
    list lRes;

    if (pArray && pStride > 0 && pComponentCount > 0 && pArrayCount > 0)
    {
        for (int lIndex = 0; lIndex < pArrayCount; lIndex++)
        {
            for (int lCompIndex = 0; lCompIndex < pComponentCount; lCompIndex++)
                lRes.append(pArray[lIndex * pStride + lCompIndex]);
        }
    }

    return lRes;
}

template<class T>
bool PyListToArray(list pList, T* pArray, int pStride, int pComponentCount, int pArrayCount)
{
    if (pArray == NULL)
    {
        PyErr_WarnEx( PyExc_UserWarning, "Data array to be filled is NULL", 1 ); 
        return false;
    }

    if (pStride < 1 || pComponentCount < 1)
    {
        PyErr_WarnEx( PyExc_UserWarning, "Invalid pStride or pComponentCount input", 1 ); 
        return false;
    }

    if (len(pList) != (pArrayCount * pComponentCount))
    {
        PyErr_WarnEx( PyExc_UserWarning, "List length doesn't match requirement", 1 ); 
        return false;
    }

    for (int lIndex = 0; lIndex < pArrayCount; lIndex++)
    {        
        for (int lCompIndex = 0; lCompIndex < pComponentCount; lCompIndex++)
            pArray[lIndex * pStride + lCompIndex] = extract<T>(pList[lIndex * pComponentCount + lCompIndex]);
    }

    return true;
}

#endif // pyfbutils_h__