#include "stdafx.h"
#include "ordevicevrtrixglove_device.h"


//--- Registration defines
#define ORDEVICEVRTRIXGLOVE_CLASS		    ORDEVICEVRTRIXGLOVE_CLASSNAME
#define ORDEVICEVRTRIXGLOVE_NAME		    ORDEVICEVRTRIXGLOVE_CLASSSTR
#define ORDEVICEVRTRIXGLOVE_LABEL		    "VRTRIX Data Gloves"
#define ORDEVICEVRTRIXGLOVE_DESC		    "VRTRIX Data Gloves"
#define ORDEVICEVRTRIXGLOVE_PREFIX			"VRTRIXGloveDevice"
#define ORDEVICEVRTRIXGLOVE_ICON		    "devices_gloves-l.png"

//--- FiLMBOX implementation and registration
FBDeviceImplementation	(	ORDEVICEVRTRIXGLOVE_CLASSNAME	);
FBRegisterDevice		(	ORDEVICEVRTRIXGLOVE_NAME,
                         ORDEVICEVRTRIXGLOVE_CLASSNAME,
                         ORDEVICEVRTRIXGLOVE_LABEL,
                         ORDEVICEVRTRIXGLOVE_DESC,
                         ORDEVICEVRTRIXGLOVE_ICON	);

/************************************************
*	FiLMBOX Constructor.
************************************************/
bool ORDeviceVRTRIXGlove::FBCreate()
{
	mDeviceID = 0;
	mDeviceIP = "127.0.0.1";

    // Add model templates
    mRootTemplate =  new FBModelTemplate(ORDEVICEVRTRIXGLOVE_PREFIX, "Reference", kFBModelTemplateRoot);
    ModelTemplate.Children.Add(mRootTemplate);
    mHierarchyIsDefined = false;
    mHasAnimationToTranspose = false;
    mPlotting = false;
    mMocapCharacter = NULL;
    mTargetCharacter = NULL;

    // Setup recording
    mClipDirectory = "";
    mReadyToSetupRecording = false;
    mMocapCharacterName = "MocapDeviceCharacter";

    // Device sampling information
    SamplingMode = kFBHardwareTimestamp;
	SamplingPeriod = FBTime(0,0,1)/120;
    FBPropertyPublish( this, UseReferenceTransformation, "UseReferenceTransformation", NULL, NULL );
    UseReferenceTransformation = true;

    // Operation status
    mOperationState = eAskForCreateModelBinding;

    // Event
    FBSystem().TheOne().OnUIIdle.Add( this,(FBCallback) &ORDeviceVRTRIXGlove::EventUIIdle );
    
    return true;
}


/************************************************
*	FiLMBOX Destructor.
************************************************/
void ORDeviceVRTRIXGlove::FBDestroy()
{
    delete mMocapCharacter;
    mMocapCharacter = NULL;

    // Propagate to parent
    ParentClass::FBDestroy();
    FBSystem().TheOne().OnUIIdle.Remove( this,(FBCallback) &ORDeviceVRTRIXGlove::EventUIIdle );
}

/************************************************
*	Device operation.
************************************************/
bool ORDeviceVRTRIXGlove::DeviceOperation( kDeviceOperations pOperation )
{
    // Must return the online/offline status of device.
    switch (pOperation)
    {
    case kOpInit:	return Init();
    case kOpStart:	return Start();
    case kOpAutoDetect:	break;
    case kOpStop:	return Stop();
    case kOpReset:	return Reset();
    case kOpDone:	return Done();
    }
    return ParentClass::DeviceOperation(pOperation);
}


/************************************************
*	Initialize the device.
************************************************/
bool ORDeviceVRTRIXGlove::Init()
{
    if(!mHardware.GetSetupInfo())
    {
        UpdateInfo("Error:", "Cannot Setup Device");
        return false;
    }

	for (int i = 0; i < GetChannelCount(); ++i) {
		DataChannel channel;
		mChannels.push_back(channel);
	}
	SetOperationState(eAskForCreateModelBinding);
    mHierarchyIsDefined = false;
    Bind();
    return true;
}


/************************************************
*	Removal of device.
************************************************/
bool ORDeviceVRTRIXGlove::Done()
{
    UnBind();

    /*
    *	Add device removal code here.
    */

    return true;
}

void ORDeviceVRTRIXGlove::SetServerIP(std::string IP)
{
	mDeviceIP = IP;
	mHardware.SetServerIP(IP);
}

void ORDeviceVRTRIXGlove::SetDeviceID(int deviceID)
{
	mDeviceID = deviceID;
	mHardware.SetDeviceID(deviceID);

	UnBind();
	mChannels.clear();

	mHardware.GetSetupInfo();
	for (int i = 0; i < GetChannelCount(); ++i) {
		DataChannel channel;
		mChannels.push_back(channel);
	}

	mHierarchyIsDefined = false;
	Bind();
}

/************************************************
*	Reset of the device.
************************************************/
bool ORDeviceVRTRIXGlove::Reset()
{
    Stop();
    return Start();
}

/************************************************
*	Device is started (online).
************************************************/
bool ORDeviceVRTRIXGlove::Start()
{

    if( !mHardware.Init() )
    {
        UpdateInfo("Error:", "Cannot Initialize Device");
        return false;
    }

    FBProgress	lProgress;

    //// Step 0: Setup character
    //lProgress.Caption	= "Mocap Device";
    //lProgress.Text = "Create Mocap Character";
    //if( !SetupMocapCharacter() )
    //{
    //    UpdateInfo("Error: Failed ", "To Create Mocap Character");
    //    return false;
    //}

    // Step 1: Open device
    lProgress.Caption	= "Mocap Device";
    lProgress.Text = "Open Device";
    if( !mHardware.Open() )
    {
        UpdateInfo("Error:", "Couldn't Start Device");
        return false;
    }

    // Step 2: Start data stream
    lProgress.Caption	= "Mocap Device";
    lProgress.Text = "Start Data Stream";
    if( !mHardware.StartDataStream() )
    {
        UpdateInfo("Error:", "Couldn't Get Data");
        return false;
    }
    UpdateInfo("Status:", "Glove Connected");
    return true; // if true the device is online
}

/************************************************
*	Device is stopped (offline).
************************************************/
bool ORDeviceVRTRIXGlove::Stop()
{
         //Step 1: Stop data
        if(! mHardware.StopDataStream() )
        {
            UpdateInfo("Error:", "Cannot Stop Data");
            return false;
        }

        // Step 2: Close down device
        if(! mHardware.Close() )
        {
            UpdateInfo("Error:", "Cannot Stop Device");
            return false;
        }

    UpdateInfo("Status:", "Glove Disconnected");
    return true;
}

/************************************************
*	Define model template hierarchy.
************************************************/
void ORDeviceVRTRIXGlove::DefineHierarchy()
{
    if( !mHierarchyIsDefined && GetChannelCount() > 0 )
    {
        int lParent;
        for(int i=0; i< GetChannelCount(); i++)
        {
            lParent = GetChannelParent(i);
            if(lParent == -1)
            {
                mRootTemplate->Children.Add(mChannels[i].mModelTemplate);
            }
            else
            {
                mChannels[lParent].mModelTemplate->Children.Add(mChannels[i].mModelTemplate);
            }
        }

        mHierarchyIsDefined = true;
    }
}

/************************************************
*	Process global data on template models to local.
************************************************/
void ORDeviceVRTRIXGlove::ProcessGlobalToLocal()
{
    SetupLocalGlobal(true);

    int i;
    FBModelList lModels;
    FBModel* lModel;

    FBGetSelectedModels(lModels);
    for(i = 0; i < lModels.GetCount(); i++)
        lModels[i]->Selected = false;

    lModels.Clear();
    for(i = 0; i < GetChannelCount(); i++)
    {
        if(mChannels[i].mModelTemplate && (lModel = mChannels[i].mModelTemplate->Model) != NULL)
        {
            lModel->Selected = true;
            lModels.Add(lModel);
        }
    }

    mPlotting = true;
    FBSystem().CurrentTake->PlotTakeOnSelected(SamplingPeriod);
    mPlotting = false;

    for(i = 0; i < lModels.GetCount(); i++)
        lModels[i]->Selected = false;	

    SetupLocalGlobal(false);

    bool ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;

    // Clear Translation and Rotation
    if(ApplyReferenceTransformation)
    {
        FBVector4d x;
        mRootTemplate->Model->Translation.SetData(&x);
        mRootTemplate->Model->Rotation.SetData(&x);
    }
}

void ORDeviceVRTRIXGlove::SetupLocalGlobal(bool pGlobal)
{
    for( int i = 0; i < GetChannelCount(); i++ )
    {
        if( mChannels[i].mTAnimNode )
        {
            mChannels[i].mTAnimNode->SetBufferType(pGlobal);
        }

        if( mChannels[i].mRAnimNode )
        {
            mChannels[i].mRAnimNode->SetBufferType(pGlobal);
        }
    }
}

/************************************************
*	Model Template unbinding notification callback
************************************************/
bool ORDeviceVRTRIXGlove::ModelTemplateUnBindNotify( int pIndex, FBModelTemplate* pModelTemplate)
{
    // Reset skeleton by reevaluating a candidate because of Local/Global animation conversion
   bool ObjectInProcess = GetObjectStatus(kFBStatusCreating) || GetObjectStatus(kFBStatusDestroying) || GetObjectStatus(kFBStatusMerging);
	if(pModelTemplate->Model && pModelTemplate->Model == mRootTemplate->Model && !ObjectInProcess)
    {
        FBPlayerControl().TheOne().EvaluationPause();
        for( int i = 0; i < GetChannelCount(); i++ )
        {
            // Create new translation and rotation animation nodes if necessary
            if(mChannels[i].mTAnimNode)
            {
                mChannels[i].mModelTemplate->Model->Translation.SetAnimated(true);
                FBAnimationNode* lNode = mChannels[i].mModelTemplate->Model->Translation.GetAnimationNode();
                FBVector3d  lVector(mChannels[i].mModelTemplate->Model->Translation);
                lNode->SetCandidate(lVector.mValue);
            }

            if(mChannels[i].mRAnimNode)
            {
                mChannels[i].mModelTemplate->Model->Rotation.SetAnimated(true);
                FBAnimationNode* lNode = mChannels[i].mModelTemplate->Model->Rotation.GetAnimationNode();
                FBVector3d  lVector(mChannels[i].mModelTemplate->Model->Rotation);
                lNode->SetCandidate(lVector.mValue);
            }
        }
        FBPlayerControl().TheOne().EvaluationResume();
    }

    // Show info after model created.
    SetOperationState(eAskForPressOnline);

    return true;
}

//simple name mapping.
static void SetupMapping(FBCharacter* pCharacter, FBModel* pParent)
{
    FBString lName = (const char*)pParent->Name; lName += "Link";
    FBProperty* lLink = pCharacter->PropertyList.Find(lName,false);
    if(lLink && lLink->IsList())
    {
        ((FBPropertyListComponent*)lLink)->Add(pParent);
    }

    //do the same for children
    for(int i = 0; i < pParent->Children.GetCount(); i++)
    {
        SetupMapping(pCharacter,pParent->Children[i]);
    }
}

/************************************************
*	Characterize
************************************************/
bool ORDeviceVRTRIXGlove::SetupMocapCharacter()
{
    // Character already setup
    if( mMocapCharacter )
        return true;        

    // Skeleton is not ready to setup character
    if( !mHierarchyIsDefined || GetChannelCount() <= 0 || !mRootTemplate->Model )
        return false;

    // Map the skeleton to character and characterize
    mMocapCharacter = new FBCharacter("GloveDeviceCharacter");
    SetupMapping(mMocapCharacter, mRootTemplate->Model);
    mMocapCharacter->SetCharacterizeOn(true);
    mMocapCharacter->SetExternalSolver(2); // Using MB Character Solver currently
    mMocapCharacter->Active = true;

    //// Set the device info to character
    //FBBodyNodeId* pSkeletonJointsOrder = NULL;
    //mHardware.GetSkeletonJointsOrder(pSkeletonJointsOrder);
    //mMocapCharacter->SetupDeviceMocap((FBDevice*)this, VRTRIX::Joint_MAX*2+22, pSkeletonJointsOrder);
    //delete pSkeletonJointsOrder;

    //// No need the data input from channel.  Note: mChannel and mChannels will be removed late.
    //UnBind();
    
    return true;
}

bool ORDeviceVRTRIXGlove::ModelTemplateBindNotify( FBModel* pModel,int pIndex, FBModelTemplate* pModelTemplate )
{
    return true;    // Will fail if do characterization here
}

/************************************************
*	End the channel set definition.
************************************************/
void ORDeviceVRTRIXGlove::Bind()
{
    int i;
    // Exit edit mode:
    // All used channels: if already defined, don't touch, if new: create animation node and model template
    // All unused channels: delete animation nodes and associated model template
    for( i = 0; i < GetChannelCount(); i++ )
    {
        // Create new translation and rotation animation nodes if necessary
        if( !mChannels[i].mTAnimNode )
        {
            // We must use a unique name for our connector.
            FBString lName( GetChannelName(i), " T" );
            mChannels[i].mTAnimNode = AnimationNodeOutCreate( 10000+i, lName, ANIMATIONNODE_TYPE_LOCAL_TRANSLATION	);
        }

        if( !mChannels[i].mRAnimNode )
        {
            // We must use a unique name for our connector.
            FBString lName( GetChannelName(i), " R" );
            mChannels[i].mRAnimNode = AnimationNodeOutCreate( 10000+i, lName, ANIMATIONNODE_TYPE_LOCAL_ROTATION	);
        }

        // Create new model templates
        if(!mChannels[i].mModelTemplate)
        {
            mChannels[i].mModelTemplate = new FBModelTemplate(ORDEVICEVRTRIXGLOVE_PREFIX, GetChannelName(i), kFBModelTemplateSkeleton);
            // Bind model template to T and R animation nodes
            mChannels[i].mModelTemplate->Bindings.Add(mChannels[i].mTAnimNode);
            mChannels[i].mModelTemplate->Bindings.Add(mChannels[i].mRAnimNode);

            // Setting global values makes weird value when not live
			FBVector3d globalTranslation = mHardware.GetDefaultT(i);
			FBVector3d globalTranslationParent = mHardware.GetDefaultT(mHardware.GetChannelParent(i));
			FBVector3d localTranslation(globalTranslation.mValue[0]- globalTranslationParent.mValue[0], globalTranslation.mValue[1] - globalTranslationParent.mValue[1], globalTranslation.mValue[2] - globalTranslationParent.mValue[2]);
             mChannels[i].mModelTemplate->DefaultTranslation = localTranslation;
             mChannels[i].mModelTemplate->DefaultRotation = mHardware.GetDefaultR(i);
        }
    }

    //Define hierarchy if needed
    DefineHierarchy();
}

void ORDeviceVRTRIXGlove::UnBind()
{
    int i;
    for( i = 0; i < GetChannelCount(); i++ )
    {
        // Unbind model templates from T and R animation nodes
        if( mChannels[i].mTAnimNode )
        {
            if( mChannels[i].mModelTemplate )
            {
                mChannels[i].mModelTemplate->Bindings.Remove(mChannels[i].mTAnimNode);
            }
        }

        if( mChannels[i].mRAnimNode )
        {
            if( mChannels[i].mModelTemplate )
            {
                mChannels[i].mModelTemplate->Bindings.Remove(mChannels[i].mRAnimNode);
            }
        }

        // Remove as child of root template
        if( mRootTemplate->Children.Find(mChannels[i].mModelTemplate) >= 0 )
        {
            mRootTemplate->Children.Remove(mChannels[i].mModelTemplate);
        }

        // Destroy unused animation nodes
        if( mChannels[i].mTAnimNode )
        {
            AnimationNodeDestroy(mChannels[i].mTAnimNode);
        }

        if( mChannels[i].mRAnimNode )
        {
            AnimationNodeDestroy(mChannels[i].mRAnimNode);
        }

        mChannels[i].mTAnimNode = NULL;
        mChannels[i].mRAnimNode = NULL;

        if( mChannels[i].mModelTemplate )
        {
            mChannels[i].mModelTemplate->Children.RemoveAll();
        }
    }

    for( i = 0; i < GetChannelCount(); i++ )
    {
        // Delete model template
        delete mChannels[i].mModelTemplate;
        mChannels[i].mModelTemplate = NULL;
    }
}

/************************************************
*	Real-time Evaluation Engine.
************************************************/
bool ORDeviceVRTRIXGlove::AnimationNodeNotify(FBAnimationNode* pAnimationNode ,FBEvaluateInfo* pEvaluateInfo)
{
    kReference lReference = pAnimationNode->Reference;

    if (lReference>=10000)
    {
        FBTVector	Pos;
        FBRVector	Rot;
        FBSVector	Scal;
        FBMatrix	GlobalNodeTransformation, GlobalReferenceTransformation;
        bool		ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;

        if(ApplyReferenceTransformation)
        {
            mRootTemplate->Model->GetMatrix(GlobalReferenceTransformation,kModelTransformation,true,pEvaluateInfo);
        }

        for(int i=0;i<GetChannelCount();i++)
        {
            if(mChannels[i].mTAnimNode && mChannels[i].mRAnimNode)
            {
                bool lDontWrite = false;
                if ((!pAnimationNode->Live || mPlotting) && mChannels[i].mModelTemplate->Model)
                {
                    mChannels[i].mModelTemplate->Model->Translation.GetAnimationNode()->Evaluate(Pos.mValue,pEvaluateInfo->GetLocalTime(),false);
                    mChannels[i].mModelTemplate->Model->Rotation.GetAnimationNode()->Evaluate(Rot.mValue,pEvaluateInfo->GetLocalTime(),false);
                } else if (pAnimationNode->Live)
                {
                    Pos[0] = mHardware.GetDataTX(i);
                    Pos[1] = mHardware.GetDataTY(i);
                    Pos[2] = mHardware.GetDataTZ(i);
                    Rot[0] = mHardware.GetDataRX(i);
                    Rot[1] = mHardware.GetDataRY(i);
                    Rot[2] = mHardware.GetDataRZ(i);
                } else
                {
                    lDontWrite = true; // Nothing to do 
                }

                if(ApplyReferenceTransformation)
                {
                    FBTRSToMatrix(GlobalNodeTransformation,Pos,Rot,Scal);
                    FBGetGlobalMatrix(GlobalNodeTransformation,GlobalReferenceTransformation,GlobalNodeTransformation);
                    FBMatrixToTranslation(Pos,GlobalNodeTransformation);
                    FBMatrixToRotation(Rot,GlobalNodeTransformation);
                }

                if(!lDontWrite)
                {
                    if (!pAnimationNode->Live || mPlotting)
                    {
                        mChannels[i].mRAnimNode->WriteData( Rot.mValue, pEvaluateInfo);
                        mChannels[i].mTAnimNode->WriteData( Pos.mValue, pEvaluateInfo);
                    }  else
                    {
                        mChannels[i].mRAnimNode->WriteGlobalData( Rot.mValue, pEvaluateInfo );
                        mChannels[i].mTAnimNode->WriteGlobalData( Pos.mValue, pEvaluateInfo );
                    }
                }
            }
        }
    }
    return ParentClass::AnimationNodeNotify( pAnimationNode , pEvaluateInfo);
}

/************************************************
*	Transport notication.
*	Useful to compute time offset between Hardware time and System time
*  PreparePlay is called just before play
************************************************/
void ORDeviceVRTRIXGlove::DeviceTransportNotify( kTransportMode pMode, FBTime pTime, FBTime pSystem )
{
}

/************************************************
*	Real-Time Synchronous Device IO.
************************************************/
void ORDeviceVRTRIXGlove::DeviceIONotify( kDeviceIOs pAction,FBDeviceNotifyInfo &pDeviceNotifyInfo)
{
    switch (pAction)
    {
    case kIOPlayModeWrite:
    case kIOStopModeWrite:
        {
            // Output devices
        }
        break;

    case kIOStopModeRead:
    case kIOPlayModeRead:
        {
                // Skeleton devices
                FBTime		lEvalTime;
                lEvalTime = pDeviceNotifyInfo.GetLocalTime();
				while (mHardware.FetchMocapData(lEvalTime))
				{
					//if (mHardware.mKinectMocapJointsState->mSkeletonTrackingState == kFBSkeletonTracked)
					//{
					//	if (mMocapCharacter)
					//	{
					//		mMocapCharacter->PassDeviceMocapData(mHardware.mKinectMocapJointsState);
					//	}
					//}
					DeviceRecordFrame(lEvalTime, pDeviceNotifyInfo);
					AckOneSampleReceived();
				}
        }
        break;
    }
}

void ORDeviceVRTRIXGlove::RecordingDoneAnimation( FBAnimationNode* pAnimationNode )
{
    // Parent call
    FBDevice::RecordingDoneAnimation( pAnimationNode );
    mHasAnimationToTranspose = true;
}

/************************************************
*	Record a frame of the device (recording).
************************************************/
void ORDeviceVRTRIXGlove::DeviceRecordFrame(FBTime &pTime,FBDeviceNotifyInfo &pDeviceNotifyInfo)
{
    if( mPlayerControl.GetTransportMode() == kFBTransportPlay )
    {
        int i;
        FBAnimationNode* Data;

        FBTVector	Pos;
        FBRVector	Rot;
        bool		ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;

        FBMatrix	GlobalReferenceTransformation;
        if(ApplyReferenceTransformation)
            mRootTemplate->Model->GetMatrix(GlobalReferenceTransformation,kModelTransformation,true);

        for (i=0; i<GetChannelCount(); i++)
        {
            // Translation information.
            if (mChannels[i].mTAnimNode)
            {
                Data = mChannels[i].mTAnimNode->GetAnimationToRecord();
                if (Data)
                {
                    Pos[0] = mHardware.GetDataTX(i);
                    Pos[1] = mHardware.GetDataTY(i);
                    Pos[2] = mHardware.GetDataTZ(i);

                    if(ApplyReferenceTransformation)
                        FBVectorMatrixMult(Pos,GlobalReferenceTransformation,Pos);

                    Data->KeyAdd(pTime, Pos);
                }
            }

            // Rotation information.
            if (mChannels[i].mRAnimNode)
            {
                Data = mChannels[i].mRAnimNode->GetAnimationToRecord();
                if (Data)
                {
                    Rot[0] = mHardware.GetDataRX(i);
                    Rot[1] = mHardware.GetDataRY(i);
                    Rot[2] = mHardware.GetDataRZ(i);

                    if(ApplyReferenceTransformation)
                    {
                        FBMatrix GRM;
                        FBRotationToMatrix(GRM,Rot);
                        FBGetGlobalMatrix(GRM,GlobalReferenceTransformation,GRM);
                        FBMatrixToRotation(Rot,GRM);
                    }

                    Data->KeyAdd(pTime, Rot);
                }
            }
        }
    }
}

/************************************************
*	Store data in FBX.
************************************************/
bool ORDeviceVRTRIXGlove::FbxStore(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat)
{
    if (pStoreWhat & kAttributes)
    {
    }
    return true;
}


/************************************************
*	Retrieve data from FBX.
************************************************/
bool ORDeviceVRTRIXGlove::FbxRetrieve(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat)
{
    if( pStoreWhat & kAttributes )
    {
    }
    return true;
}

OperationStatus ORDeviceVRTRIXGlove::GetOperationState()
{
	return mOperationState;
}

void ORDeviceVRTRIXGlove::SetOperationState(OperationStatus pState)
{
    if( mOperationState != pState )
        mOperationState = pState;

    switch (pState)
    {
    case eAskForCreateModelBinding:
        UpdateInfo("Step1:", "Create Model Binding");
        break;
    case eAskForPressOnline:
        UpdateInfo("Step2:", "Press Online");
        break;
    case eAskForPressSetupRecording:
        UpdateInfo("Step3:", "Press Setup Recording");
        break;
    case eAskForPressCalibration:
        UpdateInfo("Step4:", "Press Calibration");
        break;
    case eAskForDoCalibration:
        UpdateInfo("Step5:", "Perform Calibration");
        break;
    case eReadyForRecording:
        UpdateInfo("Step6:", "Ready To Record");
        break;
    default:
        break;
    }
}

void ORDeviceVRTRIXGlove::EventUIIdle( HISender pSender, HKEvent pEvent )
{
    if(mHasAnimationToTranspose)
    {
        mHasAnimationToTranspose = false;

        // Put the animation back on skeleton
        ProcessGlobalToLocal();
    }

    if(mReadyToSetupRecording)
    {
        if( SetupRecording() )
        {
            SetOperationState(eReadyForRecording);
        }
        else
        {
            UpdateInfo("Error:", "Fail To Do Recording");
        }
        mReadyToSetupRecording = false;
    }
}

void ORDeviceVRTRIXGlove::UpdateInfo(FBString pInfo, FBString pStatus)
{
    HardwareVersionInfo = FBString("Name: ") + mHardware.GetHardWareName();
    Information = pInfo;
    Status = pStatus;
}

void ORDeviceVRTRIXGlove::PrepareSetupRecording(FBString pClipDirectory)
{
    mReadyToSetupRecording = true;
    mClipDirectory = pClipDirectory;
}

bool ORDeviceVRTRIXGlove::SetupRecording()
{    
    FBProgress	lProgress;
    lProgress.Caption = "Mocap Device";
    lProgress.Text = "Setup Recording";

    // Get Mocap Character     
    if( mMocapCharacter == NULL )
    {
        for(int i=0; i<FBSystem().Scene->Characters.GetCount(); i++)
        {
            FBString lExpectedName = mMocapCharacterName;
            if( lExpectedName == FBSystem().Scene->Characters[i]->Name) 
                mMocapCharacter = FBSystem().Scene->Characters[i];
        }
        if( mMocapCharacter == NULL )
        {
            UpdateInfo("Error:","Mocap Character Is Invalid.");
            return false;
        }
    }

    // Get Target Character
    if( mTargetCharacter == NULL )
    {
        // Merge target character
        lProgress.Caption = "Mocap Device";
        lProgress.Text = "Retargent Mocap character to Target Character";
        int lCharacterCount = FBSystem().Scene->Characters.GetCount();
        mTargetCharacter = FBSystem().Scene->Characters[lCharacterCount - 1];
        if( mTargetCharacter == NULL || mTargetCharacter == mMocapCharacter )
        {
            UpdateInfo("Error:","Target Character Not Exist.");
            return false;
        }
    }
    if( mTargetCharacter->GetCurrentControlSet(true)==NULL)
        mTargetCharacter->CreateControlRig(true);
    if( mTargetCharacter->ActiveInput )
        mTargetCharacter->ActiveInput = false;
    if( mTargetCharacter->InputCharacter != mMocapCharacter)
        mTargetCharacter->InputCharacter = mMocapCharacter;
    if( mTargetCharacter->InputType != kFBCharacterInputCharacter )
        mTargetCharacter->InputType = kFBCharacterInputCharacter;

    // Set story track    
    bool lTargetCharacterExistingInStoryRoot = false;
    FBStory& lStory = FBStory::TheOne();
    FBStoryFolder*	lActionFolder = lStory.RootFolder;
    FBPropertyListStoryTrack& lTracks = lActionFolder->Tracks;
    for(int i=0; i<lTracks.GetCount(); i++)
    {
        FBStoryTrack* lTrack = lTracks[i];
        if( lTrack->Character == mTargetCharacter && !lTrack->RecordTrack )
        {
            lTrack->RecordTrack = true;
            lTargetCharacterExistingInStoryRoot = true;
        }
    }
    if( !lTargetCharacterExistingInStoryRoot )
    {
        lProgress.Caption = "Mocap Device";
        lProgress.Text = "Creating story track";
        FBStoryTrack* lCurrentStoryTrack = new FBStoryTrack(kFBStoryTrackCharacter);
        lCurrentStoryTrack->Character = mTargetCharacter;
        lCurrentStoryTrack->RecordClipPath = mClipDirectory;
        lCurrentStoryTrack->RecordTrack = true;
    }

    return true;
}

void ORDeviceVRTRIXGlove::ResetRecording()
{
    // Reset the TargetCharacter
    if( mTargetCharacter && mMocapCharacter )
    {
        mTargetCharacter->ActiveInput = true;
        mTargetCharacter->InputCharacter = mMocapCharacter;
        mTargetCharacter->InputType = kFBCharacterInputCharacter;
    }

    // Reset the Story Track
    FBStory& lStory = FBStory::TheOne();
    FBStoryFolder*	lActionFolder = lStory.RootFolder;
    FBPropertyListStoryTrack& lTracks = lActionFolder->Tracks;
    for(int i=0; i<lTracks.GetCount(); i++)
    {
        FBStoryTrack* lTrack = lTracks[i];
        if( lTrack->Character == mTargetCharacter && !lTrack->RecordTrack )
        {
            lTrack->RecordTrack = true;
        }
    }
}
