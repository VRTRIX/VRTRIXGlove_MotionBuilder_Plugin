#ifndef __FBPYTHON_H__
#define __FBPYTHON_H__
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

/**	\file fbsystem.h
*	Basic system interaction.
*	The FBSystem file contains the necessary data structure to 
*	interface with the underlying system.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <kaydara.h>

#include <fbsdk/fbversion.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

class FBSDK_DLL FBPythonContext
{
public:

    FBPythonContext(const char* pName);
    ~FBPythonContext();

    const char* GetName();

private:

    friend class FBPython;
    struct Data;
    Data* mConcreteContext;
};

/** FBPython is for python users to run python script and communicate with MotionBuilder internal python facility.
    Warning: When the user is calling the methods of FBPython in another thread other than MotionBuilder main thread,
    the user needs to create new thread state because Python internally prevents from illegal access to its internal Python objects 
    if the current thread is not created by Python or has no thread state. In order to address this issue, the user could use the
    following workaround.
    \code
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    FBPython::ParseLine("import sys");
    FBPython::EvalLine(); // MotionBuilder would crash if PyGILState_Ensure is not called before it.

    PyGILState_Release(gstate);
    \endcode
    PyGILState_Ensure will create a new thread state for current calling thread.
*/
class FBSDK_DLL FBPython 
{
public:

    /** Get the version of the Python interpreter.
    *   \return  A string indicating the version of the interpreter.
    */
    static const char* GetVersion();

    /** Get the target platform of the Python interpreter.
    *   \return  A string indicating the platform for which the interpreter was compiled.
    */
    static const char* GetPlatform();

    /** Get the value of stdout.
    *   \param   pPythonContext    Context to get the Stdout from.
    *   \return  A string containing the last stdout output.
    */
    static const char* GetStdout(FBPythonContext* pPythonContext = NULL);

    /** Get the value of stderr.
    *   \param   pPythonContext    Context to get the Stderr from.
    *   \return  A string containing the last stderr output.
    */
    static const char* GetStderr(FBPythonContext* pPythonContext = NULL);

    /** Submit a line of code for parsing.
    *   \param   pLine          Line of code that the Python interpreter should parse.
    *   \param   pPythonContext Context in which the parse will occur.
    *   \return  \b true        If there was a Python interpreter and the line was valid.
    *   \return  \b false       If there were no interpreter or if there was an error parsing the code
    *                           (consult stderr for more infos)
    */
    static bool ParseLine(const char* pLine, FBPythonContext* pPythonContext = NULL);

    /** Submit the last line of code parsed for evaluation.
    *   \param   pPythonContext Context in which the execution will occur.
    *   \return  \b false       If there were no interpreter or there were errors/unhandled exceptions.
    *                           (consult stderr for more infos)
    *   \return  \b true        If there was a Python interpreter and the code ran succesfully.
    *                           (consult stdout for output, if any)
    */
    static bool EvalLine(FBPythonContext* pPythonContext = NULL);

    /**	Execute a python script file within the given context.
	*	\param   pFilename		The script file to execute.
    *   \param   pPythonContext Context in which the parse will occur.
    *   \return  \b false       If there were no interpreter or there were errors/unhandled exceptions.
    *                           (consult stderr for more infos)
    *   \return  \b true        If there was a Python interpreter and the code ran succesfully.
    *                           (consult stdout for output, if any)
	*	\remark					This function can only be used in the UI thread.
	*/
	static bool EvalFile(const char* pFilename, FBPythonContext* pPythonContext = NULL);

    /**	Put a python script file in the execution queue. Clears the current context.
	*	\param   pFilename		The script file to execute.
    *   \return  \b false       If there were no interpreter or there were errors/unhandled exceptions.
    *                           (consult stderr for more infos)
    *   \return  \b true        If there was a Python interpreter and the code ran succesfully.
    *                           (consult stdout for output, if any)
	*	\remark					This function can be used in any thread.
	*/
    static bool ExecuteScript(const char* pFilename);

    /** Clears the python context.
    *   \param   pPythonContext    Context to clear.
    *   \return  \b false        If there were no interpreter or if the context is invalid.
    *   \return  \b true         If there was a Python interpreter and the context was valid.
    */
    static bool ClearContext(FBPythonContext* pPythonContext = NULL);
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
