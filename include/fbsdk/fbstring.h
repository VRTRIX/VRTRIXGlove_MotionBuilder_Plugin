#ifndef __FBSTRING_H__
#define __FBSTRING_H__
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

/**	\file fbstring.h
*	String class.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
  #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbtypes.h>

K_FORWARD( KStringList );

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBString
////////////////////////////////////////////////////////////////////////////////////
/**	Basic string class.
*	Provides basic string manipulation functionality (dynamic sizing, operator overloads).
*/
class FBSDK_DLL FBString
{
private:
	char* mStr;

public:
	//! Constructor.
	FBString();

	/** Constructor from a string.
	*	\param pStr String to copy.
	*/
	FBString(const char* pStr);

	/** Copy constructor.
	*	\param pStr String to copy.
	*/
	FBString(const FBString &pStr);

	/** Constructor from the concatenation of two strings.
	*	\param p1Str	First string to copy.
	*	\param p2Str	Second string to copy.
	*/
	FBString(const char* p1Str,const char* p2Str);

	//! Destructor.
	~FBString();

	//! Overloaded char* conversion operator.
    operator char*() const;
    operator const char*() const;

	/** Overloaded [] operator.
	*	\param pIndex Index to read character from.
	*	\return Character at \e pIndex.
	*/
	char  operator[](unsigned int pIndex) const;

	/** Overloaded = operator with a string.
	*	\param pStr String to copy (char*).
	*	\return Reference to \b this.
	*/
	const FBString& operator=( const char* pStr );

	/** Overloaded = operator with an FBString.
	*	\param pStr String to copy (FBString).
	*	\return Reference to \b this.
	*/
	const FBString& operator=( const FBString &pStr );

	/** Overloaded == operator with a string.
	*	\param pStr String to compare with (char*).
	*	\return Outcome of comparison (true/false).
	*/
	bool  operator == ( const FBString& pStr ) const;
	bool  operator == ( const char* pStr ) const;
	bool  operator == ( char* pStr ) const;

	/** Overloaded != operator with a string.
	*	\param pStr String to compare with (char*)
	*	\return Outcome of comparison (true/false).
	*/
	bool  operator != ( const FBString& pStr ) const;
	bool  operator != ( const char* pStr ) const;
	bool  operator != ( char* pStr ) const;

	/** Overloaded += operator with a string.
	*	\param pStr String to concatenate to \b this.
	*	\return Reference to \b this.
	*/
	const FBString& operator+=( const char* pStr );

	/** Overloaded + operator with a string.
	*	\param pStr String to add.
	*	\return FBString of \e pStr concatenated to \b this.
	*/
	FBString operator+( const char* pStr );

	/** Extracts a substring of length a specified length from a certain position.
	*	\param pStart Index of start.
	*	\param pLen Number of character to extract.
	*/
	FBString Mid( unsigned int pStart, unsigned int pLen ) const;

	/** Extracts the first pLen characters from this string.
	*	\param pLen Number of characters to extract.
	*	\return FBString containing the first \b pLen characters.
	*/
	FBString Left( unsigned int pLen ) const;

	/** Extracts the last pLen characters from this string.
	*	\param pLen Number of characters to extract.
	*	\return FBString containing the last \b pLen characters.
	*/
	FBString Right( unsigned int pLen ) const;

	/** Get the number of characters in this string.
	*	\return Number of characters in this string, excluding the null-terminator.
	*/
	unsigned int GetLen() const;

	/** This method determines whether the string is empty or not.
	*	\return \b true if string is empty, \b false otherwise.
	*/
	bool IsEmpty() const;

	/** Find first occurrence of the specified character.
	*	\param pCar Character to find in the string.
	*	\return Index of the character if found, -1 otherwise.
	*/
	int Find( char pCar ) const;

	/** Find last occurrence of the specified character.
	*	\param pCar Character to find in the string.
	*	\return Index of the character if found, -1 otherwise.
	*/
	int ReverseFind( char pCar ) const;

private:
	/** Copy a string from a char*.
	*	\param pStr String to copy.
	*/
	void Copy( const char* pStr );

	/** Concatenate a string from a char*.
	*	\param pStr String to copy.
	*/
	void Cat( const char* pStr );

	friend FBString operator+( const FBString& p1Str, const char* p2Str );
};

FBString operator+( const FBString& p1Str, const char* p2Str );

//! String list.
class FBSDK_DLL FBStringList	// This class is a direct wrapper it cannot have virtual functions
{
protected:
	//! Internal use only - List of items.
	KStringList* mItems;	
public:
	//! Constructor.
	FBStringList();	

	/**	Constructor.
    *   \param pSeparator the string list separator.
	*	\param	pString String to set for list.
	*/
	FBStringList( const char *pString, const char pSeparator = '~');

	//! Copy constructor.
	FBStringList(const FBStringList& pOther);	

    /** Overload assignment operator to support deep copy 
    *   \param  pOther string list to be copied from. 
    *   \return self reference. 
    */
    FBStringList& operator=	(const FBStringList& pOther);

	//! Destructor.
	~FBStringList();

public:
	/** Get internal variable */
	KStringList*	GetInternal() const;

	/**	Get the reference store with the string at \e pIndex.
	*	\param	pIndex	Index to get reference at.
	*	\return	Reference stored with value at \e pIndex.
	*/
	kReference  GetReferenceAt( int pIndex ) const;

	/**	Set the reference stored with the string at \e pIndex.
	*	\param	pIndex	Index to store reference at.
	*	\param	pRef	Reference to store at \e pIndex.
	*/
    void SetReferenceAt( int pIndex,kReference pRef );

	/**	Find the index where \e pRef is stored.
	*	\param	pRef	Reference to look for.
	*	\return	Index at which \e pRef can be found.
	*/
	int	Find( kReference pRef ) const;

	/**	Find the index with the string \e pString (or start with \e pString)
	*	\param	pString	String to search for.
    *   \param  pCaseSensitive true if considering case.
    *   \param  pStartWith true if to find the index of the string which start with pString.
	*	\return Index where \e S is stored.
	*/
	int	Find( const char *pString, bool pCaseSensitive = true, bool pStartWith = false ) const;

	/**	Get the string at \e pIndex.
	*	\param	pIndex	Index to get string at.
	*	\return	String at \e pIndex.
	*/
	const char *GetAt( int pIndex ) const;

	/**	Overloaded [] operator.
	*	Returns the string at \e pIndex.
	*	\param	pIndex	Index to access.
	*	\return String stored in list at \e pIndex.
	*/
    const char *operator[](int pIndex) const;

	//! Sort the string list (ascending)
	void Sort( );

	/**	Get the number of items in the list.
	*	\return Number of strings stored in the list.
	*/
	int GetCount() const;

	/**	Remove a string from the list.
	*	\param	S	String to remove from the list.
	*	\return	Index where item was found.
	*/
	int	Remove( const char *S );

	/**	Get as string.
    *   \param pSeparator the string list separator. 
	*	\return String list.
	*/
	const char* AsString(const char pSeparator = '~') const;

	/**	Set string for list
    *   \param pSeparator the string list separator.
	*	\param	pString String to set for list.
	*/
	bool SetString( const char *pString, const char pSeparator = '~');

	/**	Add a string to the list.
	*	\param	S		String to add to list.
	*	\param	pRef	Reference to store with string (default = 0)
	*	\return	Index where item was stored.
	*/
	int	 Add( const char *S,kReference pRef = 0 );

	//! Clear the list (remove all the items).
    void Clear();

	/**	Remove an entry at \e pIndex.
	*	\param	pIndex	Index where item is to be removed from.
	*/
    void RemoveAt( int pIndex );
	
	/**	Get the index of a string.
	*	\param	S	String to look for.
	*	\return	Index where string \e S was found.
	*/
    int IndexOf( const char *S ) const;
	
	/**	Insert an entry at \e pIndex.
	*	\param	pIndex	Index where item is to be inserted.
	*	\param	S		String to insert.
	*	\param	pRef	Reference to store with string(default=0).
	*/
    void InsertAt( int pIndex, const char *S,kReference pRef = 0 );

	/**	Set the string at \e pIndex.
	*	\param	pIndex		Index where string is to be set.
	*	\param	pString		String to set value at \e pIndex with.
	*/
	bool SetAt( int pIndex,const char *pString );
};

////////////////////////////////////////////////////////////////////////////////////
// Global
////////////////////////////////////////////////////////////////////////////////////
#ifdef FBSDKUseNamespace
	}
#endif

#endif

