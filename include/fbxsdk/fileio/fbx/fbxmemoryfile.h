/****************************************************************************************
 
   Copyright (C) 2095 Autodesk, Inc.
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
/**
   NOTE: Both the FbxReadOnlyMemoryFile and the FbxMemoryFile do not own the
   \c pMemPtr and it is the responsability of the caller to free the memory 
   when this object gets out of scope. See remark in the FbxMemoryFile class.
   */

class FBXSDK_DLL FbxReadOnlyMemoryFile : public FbxFile
{
public:
    FbxReadOnlyMemoryFile();
    FbxReadOnlyMemoryFile(const void* pMemPtr, const size_t pSize);

    virtual ~FbxReadOnlyMemoryFile();

	virtual bool		Open(const void* pMemPtr, const size_t pSize);
			bool		Close() override;

			void		Seek(const FbxInt64 pOffset, const ESeekPos pSeekPos = eBegin) override;
			FbxInt64	Tell() const override;
	
			size_t		Read(void* pDstBuf, const size_t pSize) override;
			char*		ReadString(char* pDstBuf, const size_t pDstSize, bool pStopAtFirstWhiteSpace = false) override;

			bool		EndOfFile() const override;
			FbxInt64	GetSize() override;

protected:
    const void* mData;   // Immutable Buffer.
    size_t      mSize;   // Maximum position which can be written without reallocation.
    size_t      mCurPos; // Current position.

private:
    bool		Open(const char* pFileName, const EMode pMode = eCreateReadWrite, const bool pBinary = true) override;
    bool        Open(FbxStream* pStream, void* pStreamData, const char* pMode) override;
    bool		Truncate(const FbxInt64 pSize) override;
};

class FBXSDK_DLL FbxMemoryFile : public FbxReadOnlyMemoryFile
{
    /** 
    * \remark Since the Write function can re-allocate the memory, it is possible that the pointer to
    * the buffer (pMemPtr) change address. In this case, the old block is automatically
    * deleted. To avoid memory leaks and properly delete the memory, the caller has to:
    *    a) remember the original address (pMemPtr)
    *    b) call GetMemoryFileInfo() to retrieve the current memory block address. This call needs
    *       to happen before this object goes out of scope or a call to Close(),
    *    c) if the two addresses are different, the client needs to delete the new one (the original one
    *       is already deleted). Else, the client is still responsible for deleting pMemPtr.
    */
public:
    FbxMemoryFile();
    FbxMemoryFile(void* pMemPtr, const size_t pSize);

    bool		Open(void* pMemPtr, const size_t pSize);
    bool		Close() override;

    size_t		Write(const void* pSrcBuf, const size_t pSize) override;
    bool		WriteFormat(const char* pFormat, ...) override;

    void		GetMemoryFileInfo(void** pMemPtr, size_t& pSize) override;

private:
    bool		Open(const void* pMemPtr, const size_t pSize) override;

    void*               mMutableData; // Buffer.
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_FILEIO_FBX_MEMORYFILE_H_ */
