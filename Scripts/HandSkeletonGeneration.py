from pyfbsdk import *
import json
import io
try:
    to_unicode = unicode
except NameError:
    to_unicode = str
    
def SetupLHandHierachy(pModel, pParentIdx, pNextIndex, pHierarchy):
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
    temp_dict = {}
    temp_dict['mIndex'] = lIdx
    temp_dict['mName'] = pModel.Name
    temp_dict['mLocalTranslationL'] = [lT[0], lT[1], lT[2]]
    pHierarchy.append(temp_dict)
    
    for lChild in pModel.Children:
        if len(lChild.Children)==0:
            continue;
        pNextIndex = SetupLHandHierachy(lChild,lIdx,pNextIndex,pHierarchy)
    return pNextIndex

def SetupRHandHierachy(pModel, pParentIdx, pNextIndex, pHierarchy):
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
    temp_dict = {}
    temp_dict['mIndex'] = lIdx
    temp_dict['mName'] = pModel.Name
    temp_dict['mLocalTranslationR'] = [lT[0], lT[1], lT[2]]
    pHierarchy.append(temp_dict)
    
    for lChild in pModel.Children:
        if len(lChild.Children)==0:
            continue;
        pNextIndex = SetupRHandHierachy(lChild,lIdx,pNextIndex,pHierarchy)
    return pNextIndex

lModels = FBModelList()
FBGetSelectedModels(lModels)

if len(lModels) == 2:
    HandHierarchy = []
    data = {'HandHierarchy': HandHierarchy}
    SetupRHandHierachy(lModels[0],-1,0, HandHierarchy)
    SetupLHandHierachy(lModels[1],-1,0, HandHierarchy)
    
    with io.open('./HandHierarchy.json', 'w', encoding='utf8') as f:
        str_ = json.dumps(data,indent=4, sort_keys=True,separators=(',', ': '), ensure_ascii=False)
        f.write(to_unicode(str_))
