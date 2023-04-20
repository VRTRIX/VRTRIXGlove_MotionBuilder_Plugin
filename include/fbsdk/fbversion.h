#ifndef __FBVERSION_H__
#define __FBVERSION_H__
/**************************************************************************
 Copyright (c) 1994 - 2017 Autodesk, Inc. and/or its licensors.
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

#include <karch/arch.h>

// Here we must set the namespace name to reflect the
// current version of the sdk.
//! FBSDKUseNamespace define
#define FBSDKUseNamespace 
//! FBSDKNamespace define
#define FBSDKNamespace             ORSDK2022
//! FBSDKNamespaceFunc define
#define FBSDKNamespaceFunc( Name ) FBSDKNamespace::Name

/**
*	\mainpage	Open Reality SDK for MotionBuilder 2022 - Reference Guide
*	\section	intro	Introduction
*		\subsection	welcome		Welcome To Open Reality
*	The Open Reality SDK is a C++ software development kit (SDK) that lets you 
*	easily integrate new components into the application.
*	<p>
*	The architecture is open, modular, and fully scalable - integrating 3D 
*	elements (scenes and characters), audio/video streams, and motion capture hardware 
*	seamlessly at the architecture level. The software development kit is tightly 
*	coupled with this architecture, making it the ideal platform on which to develop fully 
*	vertical tools, or to integrate new custom hardware devices.
*	<p>
*	\section	plugin	Plug-in Development
*		\subsection	what		What can you do with Open Reality?
*	With Open Reality, you can develop plugins of the following types:
*	<ul>
*		<li>Boxes
*		<li>Devices
*		<li>Constraints
*		<li>Tools
*		<li>Import/Export
*		<li>Manipulators
*		<li>Commands
*		<li>Shaders
*		<li>Filters
*	</ul>
*	You can also create many other utility plugins to automate actions, or extend
*	different services provided by the application.
*	<p>
*		\subsection	box			Boxes and Operators
*	MotionBuilder's technology is built upon the concept of a 'box', essentially connecting inputs 
*	on one side, processing the information (calculations, transformations, etc.), 
*	and sending the data on to outputs on the other side. 
*	<p>
*	This process is at the base of the real-time evaluation engine. Whenever the real-time 
*	engine is called to evaluate a frame to be displayed, it explores the network of boxes 
*	that exist within the structure of the scene, running through the different 
*	calculations that it needs in order to display the current status of that scene. 
*	<p>
*	Creating a box within the Open Reality SDK has the effect of adding an operator that 
*	can be manipulated in the Relations constraint pane. 
*	<p>
*		\subsection	device		Devices
*	This section details the specifics of writing a device based on the base class 
*	FBDevice. The FBDevice class derives from FBBox, it therefore inherits all the 
*	behaviors of an operator, including the evaluation of input and output animation nodes, 
*	as described in the previous section. 
*	<p>
*	Devices can easily be added to in order to bring in data from an external source
*	or to send out data to a receiver to control a device. In both situations, a
*	new device permits a plugin to have access to synchronous evaluation callbacks, 
*	providing the application with sampled information from the external device. 
*	Sufficient layers of abstraction are provided, separating the different layers of
*	communication, isolating time-critical operations (such as I/O) in different threads
*	to optimize performance.
*	<p>
*	With Open Reality, you can create many different types of devices, based 
*	upon the needs of the developer. Devices can essentially be classified into four 
*	different categories:
*	<dl>
*		<dt><b>Input devices (FBDevice)</b></dt>
*			<dd>An external data source, feeding in sampled data.
*			</dd>
*		<dt><b>Optical devices (FBDeviceOptical)</b></dt>
*			<dd>An extension of of the input device class. These devices are oriented
*				specifically towards optical tracking technology and deal with optical 
*				markers, occlusions, rigid bodies, etc.
*			</dd>
*		<dt><b>Synced devices (FBDeviceSync, FBDeviceCamera)</b></dt>
*			<dd>Some devices require synchronization with an external signal (video sync,
*				genlock, etc. The FBDeviceSync class are oriented to
*				provide the necessary buffer/synchronization functionality in order to
*				synchronize the real-world and virtual-world data. The FBDeviceCamera class
*				is a derivative of this, and provides a generic camera tracker template for
*				virtual set technologies.
*			</dd>
*		<dt><b>Output devices (FBDevice)</b></dt>
*			<dd>Data can be streamed out through any means desired by developing
*				an output device plugin. The real-time I/O callbacks can be used to send
*				evaluated data to an external destination (i.e. via the communications classes).
*			</dd>
*	</dl>
*	<p>
*		\subsection	constraint	Constraints
*	Constraints are real-time evaluation conditions for elements in a scene. 
*	They constrain the movement and/or behavior of objects in a scene, based on input 
*	criteria. This can be expressed by formulate, positional information, 
*	hierarchal relationships, or many other different forms. 
*	<p>
*	Deformation constraints can also be developed in order to deform meshes using 
*	the real-time deformation engine. The Open Reality SDK opens up the creation of constraints 
*	to the developer, exporting the necessary creation, management, and evaluation routines 
*	needed to add a constraint plugin. 
*	<p>
*		\subsection	tool		Tools
*	A tool is a new user-interface layout adding to the current functionality 
*	of the software. With the extensive user-interface elements available with Open Reality,
*	the possibilities are limitless as to what tools can be added. 
*	<p>
*		\subsection	impexp		Import/Export
*	MotionBuilder is a hub for data, processing seamlessly many different types of data
*	(motion files, model geometry, constraints, and so on.) Using the different 
*	hooks available in Open Reality, you can support many different kinds of 
*	custom data formats to bring the data inside the application. Exporters can then be  
*	written to send the data to the desired platform.
*	<p>
*		\subsection	manip		Manipulators
*	A manipulator is similar to a tool in usage, but bridges the gap between a tool's 
*	functionality and Viewer window interactivity. Manipulators define how the input
*	from the mouse in the Viewer window is used in order to select and 
*	manipulate the scene (and the objects in it).
*	<p>
*	With Open Reality, you can add a new type of manipulator for custom 
*	interaction with the Viewer window (selection, viewing, etc.).
*	<p>
*		\subsection command		Commands
*	A command is an action that is performed at a specific time in the scene. Commands can
*	be accessed in the Transport controls.
*	<p>
*		\subsection	filter		Filters
*	A filter is used to adjust or modify
*	animation keyframes on a function curve. The existing set of filters can be extended by
*	deriving new filters from the FBFilter class. These
*	filters can be applied either in the user interface or within the scope of another
*	plugin.
*	<p>
*		\subsection	utility		Utility Classes
*	Along with the data structures necessary to interact with the application, the Open Reality 
*	SDK is distributed with a series of utility classes that are useful to manipulate 
*	data, interact with hardware or work with any of the normal functions that might be needed in 
*	the course of developing a plugin. In addition to the functionality 
*	they provide, they also give the developer the ability to create scalable 
*	cross-platform code, as they are supported in all versions of the SDK. This 
*	eliminates any unnecessary modifications for cross-platform development.
*	<p>
*/
#endif



