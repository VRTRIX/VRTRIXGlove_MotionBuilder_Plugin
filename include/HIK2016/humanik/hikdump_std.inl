/*!	\file hikdump_std.inl
 *	\brief Inline file containing default implementation to save and load HIK objects.
 *
 *	This file contains default implementations of write/read methods used to save and load HIK objects.
 */

/**************************************************************************************

Copyright (C) 2009 Autodesk, Inc.
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

template<typename HIKFile>
inline bool Header::Write(HIKFile pFile) const	
{
	bool status;
	status = fwrite( (void *)&HeaderStr[0], sizeof(char), HEADERLENGTH, pFile) == HEADERLENGTH;
	status = (status && (fwrite( (void *)&MagicNumber, sizeof(int), 1, pFile) == 1));
	return status;
}

template<typename HIKFile>
inline bool Header::Read(HIKFile pFile) 		
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

template<typename type, int count>
template<typename HIKFile>
inline bool Field<type, count>::Write(HIKFile pFile) const	
{ 
	return fwrite( (void *)&mField[0], sizeof(FieldType), eCount, pFile) == eCount;	
}

template<typename type, int count>
template<typename HIKFile>
inline bool Field<type, count>::Read(HIKFile pFile, bool bSwap) 			
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

template<typename type, int count1, int count2>
template<typename HIKFile>
inline bool Field2D<type, count1, count2>::Write(HIKFile pFile) const	
{	
	return fwrite( (void *)&mField[0][0], sizeof(FieldType), eCount, pFile) == eCount; 
}

template<typename type, int count1, int count2>
template<typename HIKFile>
inline bool Field2D<type, count1, count2>::Read(HIKFile pFile, bool bSwap)			
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

template<typename type> bool Write(const char* pFileName, const type& pStream)
{
	// Save all the collected data
	FILE* lFile = NULL;
#if !defined(_MSC_VER) || (_MSC_VER == 1500)
	lFile = fopen(pFileName, "wb+");
#else
	fopen_s(&lFile, pFileName, "wb+");
#endif
	if(lFile != NULL)
	{
		pStream.Write(lFile);
		fclose(lFile);
		return true;
	}
	return false;
}

template<typename type> bool WriteBlock(const char* pFileName, const size_t& pElementSize, const size_t& pElementCount, type& pStream)
{
	// Save all the collected data
	FILE* lFile = NULL;
#if !defined(_MSC_VER) || (_MSC_VER == 1500)
	lFile = fopen(pFileName, "ab+");
#else
	fopen_s(&lFile, pFileName, "ab+");
#endif
	if(lFile != NULL)
	{
		fwrite(pStream, pElementSize, pElementCount, lFile);
		fclose(lFile);
		return true;
	}
	return false;
}

template<typename type> bool Read(const char* pFileName, type& pStream)
{
	// Read all the data
	bool bResult = false;
	FILE* lFile = NULL;
#if !defined(_MSC_VER) || (_MSC_VER == 1500)
	lFile = fopen(pFileName, "rb");
#else
	fopen_s(&lFile, pFileName, "rb");
#endif
	if(lFile != NULL)
	{
		bResult = pStream.Read(lFile);
		fclose(lFile);
	}

	return bResult;
}

template<typename type> bool ReadBlock(const char* pFileName, const size_t pOffset, const size_t& pElementSize, const size_t& pElementCount, type& pStream)
{
	// Read all the data
	bool bResult = false;
	FILE* lFile = NULL;
#if !defined(_MSC_VER) || (_MSC_VER == 1500)
	lFile = fopen(pFileName, "rb");
#else
	fopen_s(&lFile, pFileName, "rb");
#endif
	if(lFile != NULL)
	{
		fseek(lFile, pOffset, 0);
		bResult = fread(pStream, pElementSize, pElementCount, lFile) > 0 ;
		fclose(lFile);
	}

	return bResult;
}

