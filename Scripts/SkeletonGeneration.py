from pyfbsdk import *
import json
import io
try:
    to_unicode = unicode
except NameError:
    to_unicode = str
    
lModels = FBModelList()
FBGetSelectedModels(lModels)

def SetupHierarchy(pModel, pParentIdx, pNextIndex, result):
    lIdx = pNextIndex
    pNextIndex += 1
    lT = FBVector3d()
    lR = FBVector3d()
    pModel.GetVector(lT,FBModelTransformationType.kModelTranslation)
    pModel.GetVector(lR,FBModelTransformationType.kModelRotation)
    print '//'+str(lIdx)+':'+pModel.Name
    print 'mChannel['+str(lIdx)+'].mName = "' + pModel.Name + '";'
    print 'mChannel['+str(lIdx)+'].mParentChannel = ' +  str(pParentIdx) + ';'
    print 'mChannel['+str(lIdx)+'].mT[0] = ' +  str(lT[0]) + ';'
    print 'mChannel['+str(lIdx)+'].mT[1] = ' +  str(lT[1]) + ';'
    print 'mChannel['+str(lIdx)+'].mT[2] = ' +  str(lT[2]) + ';'
    print 'mChannel['+str(lIdx)+'].mR[0] = ' +  str(lR[0]) + ';'
    print 'mChannel['+str(lIdx)+'].mR[1] = ' +  str(lR[1]) + ';'
    print 'mChannel['+str(lIdx)+'].mR[2] = ' +  str(lR[2]) + ';'
    print ''
    temp_dict = {}
    temp_dict['mName'] = pModel.Name
    temp_dict['mParentChannel'] = pParentIdx
    temp_dict['mPose'] = [lT[0], lT[1], lT[2], lR[0], lR[1], lR[2]]
    result.append(temp_dict)
    for lChild in pModel.Children:
        if len(lChild.Children)==0 and lChild.Name != 'Head':
            continue;
        pNextIndex = SetupHierarchy(lChild,lIdx,pNextIndex,result)
    return pNextIndex

if len(lModels) == 1:
    SkeletonHierarchy = []
    data = {'SkeletonHierarchy': SkeletonHierarchy}
    SetupHierarchy(lModels[0],-1,0, SkeletonHierarchy)
    
    with io.open('./SkeletonHierarchy.json', 'w', encoding='utf8') as f:
        str_ = json.dumps(data,indent=4, sort_keys=True,separators=(',', ': '), ensure_ascii=False)
        f.write(to_unicode(str_))
