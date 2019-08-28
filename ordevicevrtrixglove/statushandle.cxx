/***************************************************************************************
Autodesk(R) Open Reality(R) Samples

(C) 2013 Autodesk, Inc. and/or its licensors
All rights reserved.

AUTODESK SOFTWARE LICENSE AGREEMENT
Autodesk, Inc. licenses this Software to you only upon the condition that 
you accept all of the terms contained in the Software License Agreement ("Agreement") 
that is embedded in or that is delivered with this Software. By selecting 
the "I ACCEPT" button at the end of the Agreement or by copying, installing, 
uploading, accessing or using all or any portion of the Software you agree 
to enter into the Agreement. A contract is then formed between Autodesk and 
either you personally, if you acquire the Software for yourself, or the company 
or other legal entity for which you are acquiring the software.

AUTODESK, INC., MAKES NO WARRANTY, EITHER EXPRESS OR IMPLIED, INCLUDING BUT 
NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
PURPOSE REGARDING THESE MATERIALS, AND MAKES SUCH MATERIALS AVAILABLE SOLELY ON AN 
"AS-IS" BASIS.

IN NO EVENT SHALL AUTODESK, INC., BE LIABLE TO ANYONE FOR SPECIAL, COLLATERAL, 
INCIDENTAL, OR CONSEQUENTIAL DAMAGES IN CONNECTION WITH OR ARISING OUT OF PURCHASE 
OR USE OF THESE MATERIALS. THE SOLE AND EXCLUSIVE LIABILITY TO AUTODESK, INC., 
REGARDLESS OF THE FORM OF ACTION, SHALL NOT EXCEED THE PURCHASE PRICE OF THE 
MATERIALS DESCRIBED HEREIN.

Autodesk, Inc., reserves the right to revise and improve its products as it sees fit.

Autodesk and Open Reality are registered trademarks or trademarks of Autodesk, Inc., 
in the U.S.A. and/or other countries. All other brand names, product names, or 
trademarks belong to their respective holders. 

GOVERNMENT USE
Use, duplication, or disclosure by the U.S. Government is subject to restrictions as 
set forth in FAR 12.212 (Commercial Computer Software-Restricted Rights) and 
DFAR 227.7202 (Rights in Technical Data and Computer Software), as applicable. 
Manufacturer is Autodesk, Inc., 10 Duke Street, Montreal, Quebec, Canada, H3C 2L7.
***************************************************************************************/

#include "stdafx.h"
#include "statushandle.h"

StatusHandle* StatusHandle::mInstance = 0;
StatusHandle* StatusHandle::One()
{
    if( !mInstance )
    {
        mInstance = new StatusHandle();
    }
    return mInstance;
}

StatusHandle::StatusHandle()
{
}

StatusHandle::~StatusHandle()
{
    mInstance = NULL;
}

void StatusHandle::PopMessage(eMessageType pStatus)
{   
    switch (pStatus)
    {
    case eSTATUS_SENSOR_RUNTIME_DLL_MISSING:
        FBMessageBox( "Mocap Device Error:", 
            "The Kinect Windows SDK doesn't work, Please try to reinstall the SDK to fix this problem",
            "OK");
        break;
    case eSTATUS_SENSOR_INITIALIZING:
        FBMessageBox( "Mocap Device Error:", 
            "The device is connected, but still initializing",
            "OK");
        break;
    case eSTATUS_SENSOR_NOTCONNECTED:
        FBMessageBox( "Mocap Device Error:", 
            "The device is not connected",
            "OK");
        break;
    case eSTATUS_SENSOR_NOTGENUINE:
        FBMessageBox( "Mocap Device Error:", 
            "The device is not a valid Kinect",
            "OK");
        break;
    case eSTATUS_SENSOR_NOTSUPPORTED:
        FBMessageBox( "Mocap Device Error:", 
            "The device is an unsupported model",
            "OK");
        break;
    case eSTATUS_SENSOR_INSUFFICIENTBANDWIDTH:
        FBMessageBox( "Mocap Device Error:", 
            "The device is connected to a hub without the necessary bandwidth requirements",
            "OK");
        break;
    case eSTATUS_SENSOR_NOTPOWERED:
        FBMessageBox( "Mocap Device Error:", 
            "The device is connected, but unpowered",
            "OK");
        break;
    case eSTATUS_SENSOR_NOTREADY:
        FBMessageBox( "Mocap Device Error:", 
            "There was some other unspecified error",
            "OK");
        break;
    default:
        break;
    }
}
