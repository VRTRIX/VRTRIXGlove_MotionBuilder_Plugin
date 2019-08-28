#ifndef __FBIO_H__
#define __FBIO_H__
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

/**	\file fbio.h
*	Hardware input and output interfaces.
*	Contains the defintions for the input and output class, such as TCP/IP and communication ports.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBCommPort
////////////////////////////////////////////////////////////////////////////////////
//! FBCOMMPORT_DEFAULT_BLOCKING_TIMEOUT
#define FBCOMMPORT_DEFAULT_BLOCKING_TIMEOUT 500  // Millisecs

//! Parity modes.
enum FBParity	{ 
	kFBParityNone,	//!< No parity.
	kFBParityOdd,	//!< Odd parity.
	kFBParityEven	//!< Even parity.
};

//! RS type for serial port.
enum FBRSType {
	kFBRS232,		//!< RS-232 serial protocol.
	kFBRS422		//!< RS-422 serial protocol.
};
//! Communication port type
enum FBCommPortType	{ 
	kFBPhysical,	//!< Physical
	kFBVirtual,		//!< Virtual
	kFBInternal		//!< Internal
};


FB_DEFINE_ENUM		( FBSDK_DLL, Parity		);
FB_DEFINE_ENUM		( FBSDK_DLL, RSType		);
FB_DEFINE_ENUM		( FBSDK_DLL, CommPortType	);
FB_DEFINE_COMPONENT	( FBSDK_DLL, CommPort	);

__FB_FORWARD( FBCommPort );

//! Comm port class.
class FBSDK_DLL FBCommPort : public FBComponent {
	__FBClassDeclare( FBCommPort,FBComponent );
public:

	//! Constructor.
	FBCommPort();

	/**	Read data from comm port (non-blocking).
	*	\retval lpBuffer				Buffer to fill.
	*	\param	nNumberOfBytesToRead	Number of bytes to read.
	*	\retval	lpNumberOfBytesRead		Number of bytes actually read (if not at NULL).
	*	\return \b true if the number of bytes read is equal to the number of bytes to read.
	*/
    bool Read( void* lpBuffer, int nNumberOfBytesToRead, int* lpNumberOfBytesRead=NULL );

	/**	Read data from comm port (blocking).
	*	\retval	lpBuffer				Buffer to fill.
	*	\param	nNumberOfBytesToRead	Number of bytes to read.
	*	\retval	lpNumberOfBytesRead		Number of bytes actually read (if not at NULL).
	*	\param	pTimeOut				Timeout for operation.
	*	\return \b true if the number of bytes read is equal to the number of bytes to read.
	*	\warning This operation is \b blocking!
	*/
    bool ReadBlocking( void* lpBuffer, int nNumberOfBytesToRead, int* lpNumberOfBytesRead=NULL, kULong pTimeOut = FBCOMMPORT_DEFAULT_BLOCKING_TIMEOUT);

	/**	Write data to comm port (non-blocking).
	*	\param	lpBuffer				Buffer to write.
	*	\param	nNumberOfBytesToWrite	Number of bytes to write.
	*	\retval	lpNumberOfBytesWritten	Number of bytes actually written (if not at NULL).
	*	\return \b true if the number of bytes written is equal to the number of bytes to write.
	*/
    bool Write( void* lpBuffer, int nNumberOfBytesToWrite, int *lpNumberOfBytesWritten=NULL );

	/**	Write data to comm port (blocking).
	*	\param	lpBuffer				Buffer to write.
	*	\param	nNumberOfBytesToWrite	Number of bytes to write.
	*	\retval	lpNumberOfBytesWritten	Number of bytes actually written (if not at NULL).
	*	\param	pTimeOut				Timeout for operation.
	*	\return \b true if the number of bytes written is equal to the number of bytes to write.
	*	\warning This operation is \b blocking!
	*/
    bool WriteBlocking( void* lpBuffer, int nNumberOfBytesToWrite, int* lpNumberOfBytesWritten=NULL, kULong pTimeOut = FBCOMMPORT_DEFAULT_BLOCKING_TIMEOUT);

	/**	Empty comm port buffer.
	*	\return	\b true if successful.
	*/
	bool EmptyBuffer();

	FBPropertyInt		PortNumber;			//!< <b>Property:</b> Port number.
	FBPropertyString	OwnerName;			//!< <b>Property:</b> Owner name.
	FBPropertyInt		BaudRate;			//!< <b>Property:</b> Baud rate.
	FBPropertyBool		UseHardwareFC;		//!< <b>Property:</b> Use hardware flow control?

	FBPropertyParity	Parity;				//!< <b>Property:</b> Parity.
	FBPropertyInt		ByteSize;			//!< <b>Property:</b> Byte size.
	FBPropertyInt		StopBits;			//!< <b>Property:</b> Stop bits.
	FBPropertyRSType	RSType;				//!< <b>Property:</b> Communications protocol (RS232 or RS422)?
	FBPropertyCommPortType	CommPortType;		//!< <b>Property:</b> Comm type (physical, virtual or internal)?

	FBPropertyBool		Active;				//!< <b>Property:</b> Is comm port active?
};

////////////////////////////////////////////////////////////////////////////////////
// Property list Comm Port
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPropertyListCommPort );
//! typedef class FBSDK_DLL FBPropertyBaseList< int > FBPropertyBaseListInt
typedef class FBSDK_DLL FBPropertyBaseList< int > FBPropertyBaseListInt;

//! \b PropertyList: CommPort.
class FBSDK_DLL FBPropertyListCommPort : public FBPropertyBaseList< int >
{
public:
	/**	Add a commport to the property list.
	*	\param	pItem	Comm port to add to list.
	*	\return	Number of items in list after operation.
	*/
	virtual int	 Add	( int pItem );
	/**	Remove Comm Port \e pItem from property list.
	*	\param	pItem	Comm Port to remove from list.
	*	\return Number of items in list after operation.
	*/
    virtual int  Remove	( int pItem );
	/** Remove the comm port at \e pIndex.
	*	\param pIndex	Index of comm port to remove.
	*/
    virtual void RemoveAt( int pIndex );
	/** Get the comm port at \e pIndex.
	*	\param pIndex	Index of commport.
	*	\return Comm Port number.
	*/
	virtual int operator[](int pIndex);
	/**	Get the number of comm ports recognized.
	*	\return Number of comm ports.
	*/
	virtual int  GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBTCPIP
////////////////////////////////////////////////////////////////////////////////////
//! FBTCPIP_DEFAULT_BLOCKING_TIMEOUT define
#define FBTCPIP_DEFAULT_BLOCKING_TIMEOUT 500  // Millisecs

//! Types of TCP/IP Sockets
enum FBTCPIPSocketType { 
	kFBTCPIP_Stream,	//!< Streaming data (TCP).
	kFBTCPIP_DGRAM,		//!< Datagrams (UDP).
	kFBTCPIP_RAW		//!< Raw data (TCP).
};

__FB_FORWARD( FBTCPIP );

//! TCP/IP class.
class FBSDK_DLL FBTCPIP : public FBComponent {
	__FBClassDeclare( FBTCPIP,FBComponent );
public:
	//! Constructor.
	FBTCPIP();

	/**	Read data from a network socket (non-blocking)
	*	\param	pSocket					Network socket.
	*	\retval	lpBuffer				Buffer to fill.
	*	\param	nNumberOfBytesToRead	Number of bytes to read.
	*	\retval	lpNumberOfBytesRead		Number of bytes actually read (if not at NULL).
	*	\return \b true if the number of bytes read is equal to the number of bytes requested.
	*/
    bool Read( int pSocket, void* lpBuffer, int nNumberOfBytesToRead, int* lpNumberOfBytesRead=NULL );

	/**	Read data from a network socket (blocking).
	*	\param	pSocket					Network socket.
	*	\retval	lpBuffer				Buffer to fill.
	*	\param	nNumberOfBytesToRead	Number of bytes to read.
	*	\retval	lpNumberOfBytesRead		Number of bytes actually read (if not at NULL).
	*	\param	pTimeOut				Timeout for operation (default to DEFAULT_BLOCKING).
	*	\return \b true if the number of bytes read is equal to the number of bytes requested.
	*	\warning This operation is \b blocking!
	*/
    bool ReadBlocking( int pSocket, void* lpBuffer, int nNumberOfBytesToRead, int* lpNumberOfBytesRead=NULL, kULong pTimeOut = FBTCPIP_DEFAULT_BLOCKING_TIMEOUT );

	/**	Read datagram from a network socket.
	*	\param	pSocket					Network socket.
	*	\retval	lpBuffer				Buffer to fill.
	*	\param	nNumberOfBytesToRead	Number of bytes to read.
	*	\retval	lpNumberOfBytesRead		Number of bytes actually read (if not at NULL).
	*	\param	pAddr					Address to get datagram.
	*	\param	pPort					Port to access at \e pAddr.
	*	\return \b true if the number of bytes read is equal to the number of bytes requested.
	*/
    bool ReadDatagram( int pSocket, void* lpBuffer,	int nNumberOfBytesToRead, int* lpNumberOfBytesRead=NULL, kULong* pAddr=NULL, unsigned short *pPort=NULL );

	/**	Write data to a network socket (non-blocking)
	*	\param	pSocket					Network socket.
	*	\param	lpBuffer				Buffer to write.
	*	\param	nNumberOfBytesToWrite	Number of bytes to write.
	*	\retval	lpNumberOfBytesWritten	Number of bytes actually written (if not at NULL).
	*	\return \b true if the number of bytes written is equal to the number of bytes to write.
	*/
    bool Write( int pSocket, void* lpBuffer, int nNumberOfBytesToWrite,	int* lpNumberOfBytesWritten=NULL );

	/**	Write data to a network socket (blocking)
	*	\param	pSocket					Network socket.
	*	\param	lpBuffer				Buffer to write.
	*	\param	nNumberOfBytesToWrite	Number of bytes to write.
	*	\retval	lpNumberOfBytesToWrite	Number of bytes actually written (if not at NULL).
	*	\param	pTimeOut				Timeout for operation.
	*	\return \b true if the number of bytes written is equal to the number of bytes to write.
	*	\warning This operation is \b blocking!
	*/
    bool WriteBlocking(	int pSocket, void* lpBuffer, int nNumberOfBytesToWrite, int* lpNumberOfBytesToWrite=NULL, kULong pTimeOut = FBTCPIP_DEFAULT_BLOCKING_TIMEOUT );

	/**	Write a datagram to a network socket.
	*	\param	pSocket					Network socket.
	*	\param	lpBuffer				Buffer to write.
	*	\param	nNumberOfBytesToWrite	Number of bytes to write.
	*	\retval	lpNumberOfBytesToWrite	Number of bytes actually written (if not at NULL).
	*	\param	pAddr					Address to write datagram.
	*	\param	pPort					Port to access at \e pAddr.
	*	\return Number of bytes written.
	*/
    bool WriteDatagram( int pSocket, void* lpBuffer, int nNumberOfBytesToWrite,	int* lpNumberOfBytesToWrite, kULong pAddr, unsigned short pPort );

	/**	Create a network socket.
	*	\retval	pSocket			Network socket created.
	*	\param	pType			Type of network socket.
	*	\param	pProtocol		Protocol to use to communicate.
	*	\param	pNonBlocking	Is socket blocking or non-blocking?
	*	\return	\b true if successful.
	*/
    bool CreateSocket( int &pSocket, FBTCPIPSocketType pType, const char *pProtocol = "ip", bool pNonBlocking=true );

	/**	Bind a socket to an address.
	*	\param	pSocket		Network socket.
	*	\param	pAddr		Address to bind socket to.
	*	\param	pPort		Port of \e pAddr to bind.
	*	\return \b true if successful.
	*/
    bool Bind( int &pSocket, kULong pAddr /*=INADDR_ANY*/, int pPort=0 );

	/**	Connect to address \e pAddr, port \e pPort with socket \e pSocket.
	*	\param	pSocket		Network socket.
	*	\param	pAddr		Address to connect to.
	*	\param	pPort		Port at \e pAddr to use.
	*	\return	\b true if successful.
	*/
    bool Connect( int &pSocket, char *pAddr, int pPort );

	/**	Close a network socket.
	*	\param	pSocket		Network socket.
	*	\return \b true if successful.
	*/
    bool CloseSocket( int &pSocket );

	/**	Place socket in mode to receive data.
	*	\param	pSocket		Network socket.
	*	\param	pBackLog	Maximum length of the queue of pending connections (default is 1).
	*	\return	Error code from operation (returns 0 if no error)
	*/
	int	 Listen( int pSocket, int pBackLog=1 );

	/**	Accepts incoming port access.
	*	\param	pSocket		Network socket.
	*	\retval	pOutAddr	Buffer receiving address of sender.
	*	\return	Error code from operation (returns 0 if no error)
	*/
	int  Accept( int pSocket, kULong *pOutAddr=NULL );

	/**	Test socket status.
	*	\param	pSocket				Network socket to test.
	*	\param	pTestRead			Test for read?
	*	\param	pTestWrite			Test for write?
	*	\param	pTestError			Test for error?
	*	\param	pTimeOutMilisecond	Timeout for operation.
	*	\return	Error code from operation (returns 0 if no error)
	*/
    int  Select( int pSocket, bool pTestRead, bool pTestWrite, bool pTestError, kULong pTimeOutMilisecond=0 );
};

#ifdef FBSDKUseNamespace
	}
#endif


#endif
