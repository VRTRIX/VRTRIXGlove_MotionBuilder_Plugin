from pyfbsdk import *

def SetupLHandHierachy(pModel, pParentIdx, pNextIndex):
    lIdx = pNextIndex
    pNextIndex += 1
    lT = FBVector3d()
    lR = FBVector3d()
    if lIdx == 0:
        pModel.GetVector(lT,FBModelTransformationType.kModelTranslation, True)
    else:
        pModel.GetVector(lT,FBModelTransformationType.kModelTranslation, False)
    print '//'+str(lIdx)+':'+pModel.Name
    print 'mLocalTranslationL['+str(lIdx)+'].mValue[0] = ' +  str(lT[0]) + ';'
    print 'mLocalTranslationL['+str(lIdx)+'].mValue[1] = ' +  str(lT[1]) + ';'
    print 'mLocalTranslationL['+str(lIdx)+'].mValue[2] = ' +  str(lT[2]) + ';'
    print ''
    for lChild in pModel.Children:
        if len(lChild.Children)==0:
            continue;
        pNextIndex = SetupLHandHierachy(lChild,lIdx,pNextIndex)
    return pNextIndex

def SetupRHandHierachy(pModel, pParentIdx, pNextIndex):
    lIdx = pNextIndex
    pNextIndex += 1
    lT = FBVector3d()
    lR = FBVector3d()
    if lIdx == 0:
        pModel.GetVector(lT,FBModelTransformationType.kModelTranslation, True)
    else:
        pModel.GetVector(lT,FBModelTransformationType.kModelTranslation, False)
    print '//'+str(lIdx)+':'+pModel.Name
    print 'mLocalTranslationR['+str(lIdx)+'].mValue[0] = ' +  str(lT[0]) + ';'
    print 'mLocalTranslationR['+str(lIdx)+'].mValue[1] = ' +  str(lT[1]) + ';'
    print 'mLocalTranslationR['+str(lIdx)+'].mValue[2] = ' +  str(lT[2]) + ';'
    print ''
    for lChild in pModel.Children:
        if len(lChild.Children)==0:
            continue;
        pNextIndex = SetupRHandHierachy(lChild,lIdx,pNextIndex)
    return pNextIndex

lModels = FBModelList()
FBGetSelectedModels(lModels)

if len(lModels) == 2:
    SetupRHandHierachy(lModels[0],-1,0)
    SetupLHandHierachy(lModels[1],-1,0)
