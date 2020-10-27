/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxmemoryfile.h
#ifndef _FBXSDK_FILEIO_FBX_MEMORYFILE_H_
#define _FBXSDK_FILEIO_FBX_MEMORYFILE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxfile.h>
#include <fbxsdk/core/base/fbxstring.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FBXSDK_DLL FbxMemoryFile : public FbxFile
{
public:
	FbxMemoryFile();
    virtual ~FbxMemoryFile();

	bool				Open(void* pMemPtr, const size_t pSize);
    virtual bool		Close();

    virtual void		Seek(const FbxInt64 pOffset, const ESeekPos pSeekPos=eBegin);
    virtual FbxInt64	Tell() const;

    virtual	size_t		Read(void* pDstBuf, const size_t pSize);
	virtual char*		ReadString(char* pDstBuf, const size_t pDstSize, bool pStopAtFirstWhiteSpace=false);
    virtual size_t		Write(const void* pSrcBuf, const size_t pSize);
    virtual bool		WriteFormat(const char* pFormat, ...);

    virtual bool		EndOfFile() const;
	virtual FbxInt64	GetSize();
	virtual void		GetMemoryFileInfo(void** pMemPtr, size_t pSize);

private:
    virtual bool		Open(const char* pFileName, const EMode pMode=eCreateReadWrite, const bool pBinary=true);
    virtual bool        Open(FbxStream* pStream, void* pStreamData, const char* pMode);
    virtual bool		Truncate(const FbxInt64 pSize);

	void*				mData;			//Buffer.
    size_t				mSize;			//Maximum position which can be written without reallocation.
    size_t				mCurPos;		//Current position.
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_FILEIO_FBX_MEMORYFILE_H_ */
