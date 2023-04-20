/*!	\file hikdump.h
 *	\brief Header file for saving and loading objects.
 *
 *	This file contains a set of utility functions for saving HumanIK objects to files on disk,
 *	and for loading HumanIK objects into memory from saved files. 
 */

/**************************************************************************************

Copyright � 2009 Autodesk, Inc.
All Rights Reserved.

The coded instructions, statements, computer programs, and/or related material (collectively "Data")
in these files contain unpublished information proprietary to Autodesk, Inc., ("Autodesk") which is
protected by Canada and United States of America federal copyright law and by international treaties.

The Data may not be disclosed or distributed to third parties, in whole or in part, without the prior
written consent of Autodesk.

THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED.
AUTODESK MAKES NO WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING BY CUSTOM
OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
FITNESS FOR A PARTICULAR PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT
THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE.

IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS OR SUPPLIERS ("AUTODESK GROUP")
BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR
MULTIPLE DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS
OF THE THEORY OF LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO,
NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.

**************************************************************************************/

#ifndef HUMANIK_DUMP
#define HUMANIK_DUMP

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "humanik.h"
#include "hikproperty.h"

#include <stdio.h>
#include <stddef.h>

#if defined(_MSC_VER) || defined(__INTEL_COMPILER) || defined(__ICL)
	#define attribute_align(a)		__declspec(align(a))
#elif defined(__GNUC__) || defined(__SNC__)
	#define attribute_align(a)		__attribute__ ((aligned(a)))
#endif



/* *********************************************** */
/**	\defgroup File Load/Store HumanIK Objects 
 *	\ingroup Object
 *	This section describes the functions provided for saving HumanIK objects to files on disk, and for loading
 *	HumanIK objects into memory from saved files. 
 *
 *	See also ~{ Saving and Loading HumanIK Objects }~.
 */

/*!	\ingroup File
 *	\brief Load file \p pFileName, and create an HIKCharacter object from its contents.
 *
 *	\param pFileName		Path and file name of the file to load.
 *	\param		pValidationString		The customer identification string given to you by Autodesk to license the use of HumanIK in your project.
 *	\param		pValidationKey			The license key given to you by Autodesk to license the use of HumanIK in your project.
 *	\return					An HIKCharacter object if the file is valid, otherwise NULL.
 */
HIKCharacter*			HIKLoadCharacter(const char* pFileName,
										 char* pValidationString, 
										 unsigned int pValidationKey);

/*!	\ingroup File
 *	\brief Save HIKCharacter \p pCharacter to file \p pFileName.
 *
 *	Where possible, it is recommended that you use the HIKWriteToStream() function to export your HIKCharacter instead, as it saves
 *	more information about your character. See HIKWriteToStream() and HIKReadFromStream().
 *	\param pFileName		Path and file name of the file to create. If the file already exists, it is overwritten.
 *	\param pCharacter		HIKCharacter to be saved.
 *	\return					True if the operation was succesful, otherwise false.
 */
bool					HIKSaveCharacter(const char* pFileName, HIKCharacter* pCharacter);

/*!	\ingroup File
 *	\brief Load file \p pFileName, and create an HIKCharacterState object from its contents.
 *
 *	\param pFileName		Path and file name of the file to load.
 *	\param pCharacter		HIKCharacter used to create the HIKCharacterState loaded from the file.
 *	\return					An HIKCharacterState if the file is valid, otherwise NULL.
 */
HIKCharacterState*		HIKLoadCharacterState(const char* pFileName, HIKCharacter* pCharacter);

/*!	\ingroup File
 *	\brief Save HIKCharacterState \p pState to file \p pFileName.
 *	\param pFileName		Path and file name of the file to create. If the file already exists, it is overwritten.
 *	\param pCharacter		The HIKCharacter used to create the HIKCharacterState being saved.
 *	\param pState			HIKCharacterState to save.
 *	\param pTransformMode	Determines whether the Node transforms in the saved HIKCharacterState will be expressed
 *							in global space or local space. 0 = global space, 1 = local space.
 *	\return					True if the operation was succesful, otherwise false.
 */
bool					HIKSaveCharacterState(const char* pFileName, HIKCharacter* pCharacter, HIKCharacterState* pState, int pTransformMode);

/*!	\ingroup File
 *	\brief Load file \p pFileName, and create an HIKEffectorSetState object from its contents.
 *
 *	\param pFileName		Path and file name of the file to load.
 *	\return					An HIKEffectorSetState if the file is valid, otherwise NULL.
 */
HIKEffectorSetState*	HIKLoadEffectorState(const char* pFileName);

/*!	\ingroup File
 *	\brief Save HIKEffectorSetState \p pState to file \p pFileName.
 *	\param pFileName		Path and file name of the file to create. If the file already exists, it is overwritten.
 *	\param pState			HIKEffectorSetState to save.
 *	\return					True if the operation was succesful, otherwise false.
 */
bool					HIKSaveEffectorState(const char* pFileName, HIKEffectorSetState* pState);

/*!	\ingroup File
 *	\brief Load file \p pFileName, and create an HIKPropertySetState object from its contents.
 *
 *	\param pFileName		Path and file name of the file to load.
 *	\return					An HIKPropertySetState if the file is valid, otherwise NULL.
 */
HIKPropertySetState*	HIKLoadPropertySetState(const char* pFileName);

/*!	\ingroup File
 *	\brief Save HIKPropertySetState \p pState to file \p pFileName.
 *	\param pFileName		Path and file name of the file to create. If the file already exists, it is overwritten.
 *	\param pState			HIKPropertySetState to save.
 *	\return					True if the operation was succesful, otherwise false.
 */
bool					HIKSavePropertySetState(const char* pFileName, HIKPropertySetState* pState);

/*!	\ingroup File
 *	\brief Load file \p pFileName, and create a data set from its contents according to the data description provided in the \p pDataDesc argument.
 *						
 *	For more information about data sets, see ~{ Setting and Retrieving Animation Data }~.
 *
 *	\param pFileName		Path and file name of the file to load.
 *	\param pDataDesc		Data description that defines the memory layout of the data set contained in the file.
 *	\return					A void pointer to the new data set.
 */
void*					HIKLoadDataBlock(const char* pFileName, HIKDataDescription& pDataDesc);

/*!	\ingroup File
 *	\brief Save the data set located in memory at \p pDataBlock to file \p pFileName. 
 *
 *	For more information about data sets, see ~{ Setting and Retrieving Animation Data }~.
 *
 *	\param pFileName		Path and file name of the file to create. If the file already exists, it is overwritten.
 *	\param pDataDesc		Data description that defines the memory layout of the data set to be saved.
 *	\param pDataBlock		Pointer to the beginning of the data set in memory.
 */
void					HIKSaveDataBlock(const char* pFileName, const HIKDataDescription& pDataDesc, const void* pDataBlock);

//Headers are 16 characters long
#define HEADERLENGTH 16
                                           //123456789012345
const char HIKCHARACTER_HEADER[] =			"HIKCHARACTER000\0";
const char HIKCHARACTERSTATE_HEADER[] =		"HIKSTATE0000000\0";
const char HIKCHARACTEREFFECTOR_HEADER[] =	"HIKEFFECTOR0000\0";
const char HIKCHARACTERPROPERTY_HEADER[] =	"HIKPROPERTY0000\0";
const char HIKCHARACTERDATABLOCK_HEADER[] =	"HIKDATABLOCK000\0";
const int MagicNumber = 0xabcdef12;

class Header
{
	char HeaderStr[HEADERLENGTH];

public:
	bool bSwap;

	Header():bSwap(false) {}
	inline void Init(const char *_Header)			{ strcpy(HeaderStr, _Header); }
	inline bool Write(FILE* pFile) const	
	{
		bool status;
		status = fwrite( (void *)&HeaderStr[0], sizeof(char), HEADERLENGTH, pFile) == HEADERLENGTH;
		status = (status && (fwrite( (void *)&MagicNumber, sizeof(int), 1, pFile) == 1));
		return status;
	}
	inline bool Read(FILE* pFile) 			
	{ 
		char ReadBuf[HEADERLENGTH];
		if(fread( (void *)&ReadBuf[0], sizeof(char), HEADERLENGTH, pFile) == HEADERLENGTH)
		{
			if(strcmp(HeaderStr,ReadBuf) == 0)
			{
				int ReadMagicNumber;
				if(fread( (void *)&ReadMagicNumber, sizeof(int), 1, pFile) == 1)
				{
					bSwap = !(ReadMagicNumber == MagicNumber);
					return true;
				}
			}
		}

		return 	false;
	}
};

template<typename type> bool Write(const char* pFileName, const type& pStream)
{
	// Save all the collected data
	FILE* lFile = fopen(pFileName, "wb+");
	if(lFile != NULL)
	{
		pStream.Write(lFile);
		fclose(lFile);
		return true;
	}
	return false;
}

template<typename type> bool Read(const char* pFileName, type& pStream)
{
	// Read all the data
	bool bResult = false;
	FILE* lFile = fopen(pFileName, "rb");
	if(lFile != NULL)
	{
		bResult = pStream.Read(lFile);
		fclose(lFile);
	}
	
	return bResult;
}

inline void SwapBytes4(char* ToSwap)
{
	char temp;

	temp = ToSwap[0];
	ToSwap[0] = ToSwap[3];
	ToSwap[3] = temp;
	temp = ToSwap[1];
	ToSwap[1] = ToSwap[2];
	ToSwap[2] = temp;
}

template<typename type, int count> class Field
{
public:
	typedef type FieldType;
	enum{
		eCount = count
	};
	FieldType mField[eCount];

	inline void Init(FieldType pValue)		{ memset(mField, (int)pValue, sizeof(FieldType)*eCount); }
	inline bool Write(FILE* pFile) const	{ return fwrite( (void *)&mField[0], sizeof(FieldType), eCount, pFile) == eCount;	}
	inline bool Read(FILE* pFile, bool bSwap) 			
	{
		bool Result = fread( (void *)&mField[0], sizeof(FieldType), eCount, pFile) == eCount;
		
		if(bSwap)
		{
			for(int i = 0; i < eCount; i++)
			{
				SwapBytes4((char*)&mField[i]);
			}
		}

		return Result;
	}
};

template<typename type, int count1, int count2> class Field2D
{
public:
	typedef type FieldType;
	enum{
		eCount1 = count1,
		eCount2 = count2,
		eCount  = eCount1*eCount2,
	};
	FieldType mField[eCount1][eCount2];

	inline void Init(FieldType pValue)		{	memset(mField, (int)pValue, sizeof(FieldType)*eCount);	}
	inline bool Write(FILE* pFile) const	{	return fwrite( (void *)&mField[0][0], sizeof(FieldType), eCount, pFile) == eCount; }
	inline bool Read(FILE* pFile, bool bSwap)			
	{
		bool Result = fread( (void *)&mField[0][0], sizeof(FieldType), eCount, pFile) == eCount;

		if(bSwap)
		{
			for(int i = 0; i < eCount1; i++)
				for(int j = 0; j < eCount2; j++)
				{
					SwapBytes4((char*)&mField[i][j]);
				}
		}

		return Result;
	}
};

class HIKCharacterStream
{
public:
	Field<int, LastNodeId>			mNodeFlag;
	Field2D<float, LastNodeId, 4>	mTOffset;
	Field2D<float, LastNodeId, 4>	mQOffset;
	Field2D<float, LastNodeId, 4>	mSOffset;
	Field2D<float, LastNodeId, 4>	mParentTOffset;
	Field2D<float, LastNodeId, 4>	mParentQOffset;
	Field2D<float, LastNodeId, 4>	mParentSOffset;
	Header							HIKCharHeader;

	inline void Init()
	{
		HIKCharHeader.Init(HIKCHARACTER_HEADER);

		mNodeFlag.Init(HIKNodeNotUsed);
		mTOffset.Init(0.0f);
		mQOffset.Init(0.0f);
		mSOffset.Init(0.0f);
		mParentTOffset.Init(0.0f);
		mParentQOffset.Init(0.0f);
		mParentSOffset.Init(0.0f);
	}

	inline bool Write(FILE* pFile) const
	{
		bool lFlag = false;

		lFlag = HIKCharHeader.Write(pFile);
		lFlag = lFlag && mNodeFlag.Write(pFile);		
		lFlag = lFlag && mTOffset.Write(pFile);
		lFlag = lFlag && mQOffset.Write(pFile);
		lFlag = lFlag && mSOffset.Write(pFile);
		lFlag = lFlag && mParentTOffset.Write(pFile);
		lFlag = lFlag && mParentQOffset.Write(pFile);
		lFlag = lFlag && mParentSOffset.Write(pFile);

		return lFlag;
	}

	inline bool Read(FILE* pFile)
	{
		bool lFlag = false;

		if(HIKCharHeader.Read(pFile))
		{
			lFlag = mNodeFlag.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mTOffset.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mQOffset.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mSOffset.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mParentTOffset.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mParentQOffset.Read(pFile, HIKCharHeader.bSwap);
			lFlag = lFlag && mParentSOffset.Read(pFile, HIKCharHeader.bSwap);
		}

		return lFlag;
	}
};

inline bool HIKGetCharacterDefinitionFromDump(const char* pFileName, HIKCharacterDefinition& pDef)
{
	// First let retrieve data
	// We need characterization flag, Default stance pose and Parent offset
	HIKCharacterStream	lStream;
	
	lStream.Init();
	
	// Load all the data
	if(Read(pFileName, lStream))
	{	
		memcpy(pDef.mUsedNodes, lStream.mNodeFlag.mField, sizeof(int)*lStream.mNodeFlag.eCount);
		return true;
	}
	return false;
}

inline HIKCharacter* HIKLoadCharacter(const char* pFileName,
									  char* pValidationString, 
									  unsigned int pValidationKey)
{
	// First let retrieve data
	// We need characterization flag, Default stance pose and Parent offset
	HIKCharacterStream	lStream;
	HIKCharacter*		lCharacter = NULL;

	lStream.Init();

	// Load all the data
	if(Read(pFileName, lStream))
	{	
		HIKCharacterDefinition lDef;
	
		memcpy(lDef.mUsedNodes, lStream.mNodeFlag.mField, sizeof(int)*lStream.mNodeFlag.eCount);

		lCharacter = HIKCharacterCreate(&lDef, &malloc, pValidationString, pValidationKey);
		if (!lCharacter)
			return NULL;
		int i;
		for(i=0;i<LastNodeId;i++)
		{
			if(lDef.mUsedNodes[i] & HIKNodeUsed)
			{
				HIKSetCharacterizeNodeStateTQSfv(lCharacter, i, &lStream.mTOffset.mField[i][0], &lStream.mQOffset.mField[i][0], &lStream.mSOffset.mField[i][0]);
			}

			if(lDef.mUsedNodes[i] & HIKNodeParentOffset)
			{
				HIKSetParentOffsetfv(lCharacter, i, &lStream.mParentTOffset.mField[i][0], &lStream.mParentQOffset.mField[i][0], &lStream.mParentSOffset.mField[i][0]);
			}
		}

		HIKCharacterizeGeometry(lCharacter);
	}
	return lCharacter;
}

inline bool HIKSaveCharacter(const char* pFileName, HIKCharacter* pCharacter)
{
	// First let prepare data to save
	// We need characterization flag, Default stance pose and Parent offset
	HIKCharacterStream lStream;

	lStream.Init();

	int i;
	for(i=0;i<LastNodeId;i++)
	{
		lStream.mNodeFlag.mField[i] = HIKGetNodeUse(pCharacter, i);
	}

	for(i=0;i<LastNodeId;i++)
	{
		if(lStream.mNodeFlag.mField[i] & HIKNodeParentOffset)
		{
			HIKGetParentOffsetfv(pCharacter, i, &lStream.mParentTOffset.mField[i][0], &lStream.mParentQOffset.mField[i][0], &lStream.mParentSOffset.mField[i][0]);
		}
	}

	HIKCharacterState* lState = HIKCharacterStateCreate(pCharacter, &malloc); 
	HIKGetDefaultState(pCharacter, lState);

	for(i=0;i<LastNodeId;i++)
	{
		if(lStream.mNodeFlag.mField[i] & HIKNodeUsed)
		{
			HIKGetNodeStateTQSfv(pCharacter, lState, i, &lStream.mTOffset.mField[i][0], &lStream.mQOffset.mField[i][0], &lStream.mSOffset.mField[i][0]);
		}
	}

	HIKCharacterStateDestroy(lState , &free);

	return Write(pFileName, lStream);
}

class HIKCharacterStateStream
{
public:
	Field<int, 1>			mTransformMode;
	Field<int, LastNodeId>	mNodeId;
	attribute_align(16)	Field2D<float, LastNodeId, 12> mTransformData;
	Header					HIKCharStateHeader;

	inline void Init()
	{
		mTransformMode.Init(0);
		mNodeId.Init(HIKLastNode);
		mTransformData.Init(0.0f);
		HIKCharStateHeader.Init(HIKCHARACTERSTATE_HEADER);
	}

	inline bool Write(FILE* pFile) const
	{
		bool lFlag = false;

		lFlag = HIKCharStateHeader.Write(pFile);
		lFlag = lFlag && mTransformMode.Write(pFile);
		lFlag = lFlag && mNodeId.Write(pFile);
		lFlag = lFlag && mTransformData.Write(pFile);
		
		return lFlag;
	}

	inline bool Read(FILE* pFile)
	{
		bool lFlag = false;

		if(HIKCharStateHeader.Read(pFile))
		{
			lFlag = mTransformMode.Read(pFile, HIKCharStateHeader.bSwap);
			lFlag = lFlag && mNodeId.Read(pFile, HIKCharStateHeader.bSwap);
			lFlag = lFlag && mTransformData.Read(pFile, HIKCharStateHeader.bSwap);
		}

		return lFlag;
	}
};


inline HIKCharacterState* HIKLoadCharacterState(const char* pFileName, HIKCharacter* pCharacter)
{
	HIKCharacterStateStream lStateStream;
	HIKCharacterState*		lState = NULL;

	lStateStream.Init();

	if(Read(pFileName, lStateStream))
	{
		lState = HIKCharacterStateCreate(pCharacter, &malloc);

		HIKDataDescription      lDataDesc;	
	
		lDataDesc.mTransformSpace	= lStateStream.mTransformMode.mField[0] == HIKDataDescription::HIKLocalSpace ? HIKDataDescription::HIKLocalSpace : HIKDataDescription::HIKGlobalSpace;
		lDataDesc.mTOffset			= 0;
		lDataDesc.mQOffset			= 16; 
		lDataDesc.mSOffset			= 32;
		lDataDesc.mStride			= 48;
		lDataDesc.mHIKNodeId		= &lStateStream.mNodeId.mField[0];

		HIKSetCharacterStateTransformTQS(pCharacter, lState, &lDataDesc, &lStateStream.mTransformData);
	}	
	return lState;	
}

inline bool HIKSaveCharacterState(const char* pFileName, HIKCharacter* pCharacter, HIKCharacterState* pState, int pTransformMode)
{
	HIKCharacterStateStream lStateStream;
	HIKDataDescription      lDataDesc;	

	lStateStream.Init();
	
	lDataDesc.mTransformSpace	= pTransformMode == HIKDataDescription::HIKLocalSpace ? HIKDataDescription::HIKLocalSpace : HIKDataDescription::HIKGlobalSpace;
	lDataDesc.mTOffset			= 0;
	lDataDesc.mQOffset			= 16; 
	lDataDesc.mSOffset			= 32;
	lDataDesc.mStride			= 48;
	lDataDesc.mHIKNodeId		= &lStateStream.mNodeId.mField[0];
	
	// First let prepare data to save
	// We need transform mode and all joint transform	
	int i, lLastId = 0;
	for(i=0;i<LastNodeId;i++)
	{
		if( HIKGetNodeUse(pCharacter, i) & HIKNodeUsed)
		{
			lStateStream.mNodeId.mField[lLastId++] = i;
		}
	}

	lStateStream.mNodeId.mField[lLastId]  = HIKLastNode;	
	lStateStream.mTransformMode.mField[0] = pTransformMode;

	HIKGetCharacterStateTransformTQS(pCharacter, pState, &lDataDesc, &lStateStream.mTransformData);	

	return Write(pFileName, lStateStream);
}

class HIKEffectorSetStateStream
{
public:
	Field<float, LastEffectorId> mReachT;
	Field<float, LastEffectorId> mReachR;
	Field<float, LastEffectorId> mResist;
	Field<float, LastEffectorId> mPull;
	Field<float, 2>				 mHandPullHips;

	Field2D<float, LastEffectorId, 12> mTQS;
	Field2D<float, HIKLastFloorId, 16> mFloorTQS;
	Header	HIKEffectorHeader;
	
	inline void Init()
	{		
		mReachT.Init(0.0f);
		mReachR.Init(0.0f);
		mResist.Init(0.0f);
		mPull.Init(0.0f);
		mHandPullHips.Init(0.0f);
		mTQS.Init(0.0f);
		mFloorTQS.Init(0.0f);		
		HIKEffectorHeader.Init(HIKCHARACTEREFFECTOR_HEADER);
	}

	inline bool Write(FILE* pFile) const
	{
		bool lFlag = false;

		lFlag = HIKEffectorHeader.Write(pFile);
		lFlag = lFlag && mReachT.Write(pFile);
		lFlag = lFlag && mReachR.Write(pFile);
		lFlag = lFlag && mResist.Write(pFile);
		lFlag = lFlag && mPull.Write(pFile);
		lFlag = lFlag && mHandPullHips.Write(pFile);
		lFlag = lFlag && mTQS.Write(pFile);
		lFlag = lFlag && mFloorTQS.Write(pFile);
		return lFlag;
	}

	inline bool Read(FILE* pFile)
	{
		bool lFlag = false;

		if(HIKEffectorHeader.Read(pFile))
		{
			lFlag = mReachT.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mReachR.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mResist.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mPull.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mHandPullHips.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mTQS.Read(pFile, HIKEffectorHeader.bSwap);
			lFlag = lFlag && mFloorTQS.Read(pFile, HIKEffectorHeader.bSwap);
		}

		return lFlag;
	}
};

inline HIKEffectorSetState* HIKLoadEffectorState(const char* pFileName)
{
	HIKEffectorSetStateStream lEffectorStream;
	HIKEffectorSetState*      lState = NULL;

	lEffectorStream.Init();

	if(Read(pFileName, lEffectorStream))
	{
		lState = HIKEffectorSetStateCreate(&malloc);

		int i;
		for(i=0;i<LastEffectorId;i++)
		{
			HIKSetTranslationActive(lState, i, lEffectorStream.mReachT.mField[i]);
			HIKSetRotationActive(lState, i, lEffectorStream.mReachR.mField[i]);
			HIKSetResist(lState, i, lEffectorStream.mResist.mField[i]);
			HIKSetPull(lState, i, lEffectorStream.mPull.mField[i]);
			HIKSetEffectorStateTQSfv(lState, i, &lEffectorStream.mTQS.mField[i][0],&lEffectorStream.mTQS.mField[i][4], &lEffectorStream.mTQS.mField[i][8]);		
		}

		HIKSetHandPullHips(lState, 0, lEffectorStream.mHandPullHips.mField[0]);
		HIKSetHandPullHips(lState, 1, lEffectorStream.mHandPullHips.mField[1]);

		for(i=0;i<HIKLastFloorId;i++)
		{
			HIKSetEffectorFloorStatefv(lState, i, &lEffectorStream.mFloorTQS.mField[i][0]);
		}

	}
	return lState;
}

inline bool HIKSaveEffectorState(const char* pFileName, HIKEffectorSetState* pState)
{
	HIKEffectorSetStateStream lEffectorStream;
	lEffectorStream.Init();

	int i;
	for(i=0;i<LastEffectorId;i++)
	{
		lEffectorStream.mReachT.mField[i] = HIKGetTranslationActive(pState, i);
		lEffectorStream.mReachR.mField[i] = HIKGetRotationActive(pState, i);
		lEffectorStream.mResist.mField[i] = HIKGetResist(pState, i);
		lEffectorStream.mPull.mField[i]   = HIKGetPull(pState, i);

		HIKGetEffectorStateTQSfv(pState, i, &lEffectorStream.mTQS.mField[i][0], &lEffectorStream.mTQS.mField[i][4], &lEffectorStream.mTQS.mField[i][8]);		
	}

	lEffectorStream.mHandPullHips.mField[0] = HIKGetHandPullHips(pState, 0);
	lEffectorStream.mHandPullHips.mField[1] = HIKGetHandPullHips(pState, 1);

	for(i=0;i<HIKLastFloorId;i++)
	{
		HIKGetEffectorFloorStatefv(pState, i, &lEffectorStream.mFloorTQS.mField[i][0]);
	}

	return Write(pFileName, lEffectorStream);	
}

class HIKPropertySetStream
{
public:
	Field<int,   HIKLastPropertyId> mMode;
	Field<float, HIKLastPropertyId> mValue;
	Header							HIKPropertySetHeader;

	inline void Init()
	{
		mMode.Init(0);
		mValue.Init(0.0f);
		HIKPropertySetHeader.Init(HIKCHARACTERPROPERTY_HEADER);
	}

	inline bool Write(FILE* pFile) const
	{
		bool lFlag = false;

		lFlag = HIKPropertySetHeader.Write(pFile);
		lFlag = lFlag && mMode.Write(pFile);
		lFlag = lFlag && mValue.Write(pFile);		

		return lFlag;
	}

	inline bool Read(FILE* pFile)
	{
		bool lFlag = false;
		
		if(HIKPropertySetHeader.Read(pFile))
		{
			lFlag = mMode.Read(pFile, HIKPropertySetHeader.bSwap);
			lFlag = lFlag && mValue.Read(pFile, HIKPropertySetHeader.bSwap);		
		}

		return lFlag;
	}

};

inline HIKPropertySetState* HIKLoadPropertySetState(const char* pFileName)
{
	HIKPropertySetStream lStream;
	HIKPropertySetState* lState = NULL;

	lStream.Init();

	if(Read(pFileName, lStream))
	{
		lState = HIKPropertySetStateCreate(&malloc);

		int i;
		for(i=0;i<HIKLastPropertyId;i++)
		{
			HIKSetPropertyMode(lState, i, lStream.mMode.mField[i]);
			HIKSetPropertyValue(lState, i, lStream.mValue.mField[i]);
		}
	}
	
	return lState;	
}

inline bool HIKSavePropertySetState(const char* pFileName, HIKPropertySetState* pState)
{
	HIKPropertySetStream lStream;
	lStream.Init();

	int i;
	for(i=0;i<HIKLastPropertyId;i++)
	{
		lStream.mMode.mField[i]  = HIKGetPropertyMode(pState, i);
		lStream.mValue.mField[i] = HIKGetPropertyValue(pState, i);
	}

	return Write(pFileName, lStream);
}

class HIKDataDescriptionStream
{
public:
	Field<int, 1>			mTransformSpace;
	Field<int, 1>			mTOffset;
	Field<int, 1>			mQOffset;
	Field<int, 1>			mSOffset;
	Field<int, 1>			mStride;
	Field<int, LastNodeId>	mHIKNodeId;
	Header					HIKDataBlockHeader;

	inline void Init()
	{
		mTransformSpace.Init(0);
		mTOffset.Init(0);
		mQOffset.Init(0);
		mSOffset.Init(0);
		mStride.Init(0);
		mHIKNodeId.Init(0);
		HIKDataBlockHeader.Init(HIKCHARACTERDATABLOCK_HEADER);
	}

	inline bool Write(FILE* pFile) const
	{
		bool lFlag = false;

		lFlag = HIKDataBlockHeader.Write(pFile);
		lFlag = lFlag && mTransformSpace.Write(pFile);
		lFlag = lFlag && mTOffset.Write(pFile);		
		lFlag = lFlag && mQOffset.Write(pFile);
		lFlag = lFlag && mSOffset.Write(pFile);		
		lFlag = lFlag && mStride.Write(pFile);
		lFlag = lFlag && mHIKNodeId.Write(pFile);		

		return lFlag;
	}

	inline bool Read(FILE* pFile)
	{
		bool lFlag = false;

		if(HIKDataBlockHeader.Read(pFile))
		{
			lFlag = mTransformSpace.Read(pFile, HIKDataBlockHeader.bSwap);
			lFlag = lFlag && mTOffset.Read(pFile, HIKDataBlockHeader.bSwap);		
			lFlag = lFlag && mQOffset.Read(pFile, HIKDataBlockHeader.bSwap);
			lFlag = lFlag && mSOffset.Read(pFile, HIKDataBlockHeader.bSwap);		
			lFlag = lFlag && mStride.Read(pFile, HIKDataBlockHeader.bSwap);
			lFlag = lFlag && mHIKNodeId.Read(pFile, HIKDataBlockHeader.bSwap);
		}

		return lFlag;
	}
};

inline void* HIKLoadDataBlock(const char* pFileName, HIKDataDescription& pDataDesc)
{
	void *lDataBlock = NULL;
	HIKDataDescriptionStream lStream;
	lStream.Init();
	FILE* lFile = fopen(pFileName, "rb");
	if(lFile != NULL)
	{
		lStream.Read(lFile);

		pDataDesc.mTransformSpace = lStream.mTransformSpace.mField[0] == HIKDataDescription::HIKLocalSpace ? HIKDataDescription::HIKLocalSpace : HIKDataDescription::HIKGlobalSpace;;
		pDataDesc.mTOffset = (size_t)lStream.mTOffset.mField[0];
		pDataDesc.mQOffset = (size_t)lStream.mQOffset.mField[0];
		pDataDesc.mSOffset = (size_t)lStream.mSOffset.mField[0];
		pDataDesc.mStride  = (size_t)lStream.mStride.mField[0];	

		int i = 0;
		do
		{
			pDataDesc.mHIKNodeId[i] = lStream.mHIKNodeId.mField[i];
		}
		while(lStream.mHIKNodeId.mField[i++] != HIKLastNode);

		const size_t align = 16;

		lDataBlock = malloc( (pDataDesc.mStride*i-1) + align);
		lDataBlock = (void *)((size_t)lDataBlock + align - ((size_t)lDataBlock) % align);

		fread(lDataBlock, (size_t)pDataDesc.mStride, (size_t)(i-1), lFile);
		fclose(lFile);
	}
	return lDataBlock;
}

inline void HIKSaveDataBlock(const char* pFileName, const HIKDataDescription& pDataDesc, const void* pDataBlock)
{
	HIKDataDescriptionStream lStream;
	lStream.Init();

	lStream.mTransformSpace.mField[0] = pDataDesc.mTransformSpace;
	lStream.mTOffset.mField[0] = (int)pDataDesc.mTOffset;
	lStream.mQOffset.mField[0] = (int)pDataDesc.mQOffset;
	lStream.mSOffset.mField[0] = (int)pDataDesc.mSOffset;
	lStream.mStride.mField[0]  = (int)pDataDesc.mStride;

	int i = 0;
	do
	{
		lStream.mHIKNodeId.mField[i] = pDataDesc.mHIKNodeId[i];
	}
	while(pDataDesc.mHIKNodeId[i++] != HIKLastNode);

	// Save all the collected data
	FILE* lFile = fopen(pFileName, "wb+");
	if(lFile != NULL)
	{
		lStream.Write(lFile);
		fwrite(pDataBlock, (size_t)pDataDesc.mStride, (size_t)(i-1), lFile);

		fclose(lFile);		
	}	
}

#endif