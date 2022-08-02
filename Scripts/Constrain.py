# -*- coding: utf-8 -*-
from pyfbsdk import *
#选取数据对象  
lModelList = FBModelList()
FBGetSelectedModels(lModelList)

#选取编辑对象
senderModelList = FBModelList()
FBGetSelectedModels(senderModelList)

###创建约束节点
lMgr = FBConstraintManager()
lScene = FBSystem().Scene
lCnst = lMgr.TypeCreateConstraint('Relation')

###添加对象约束
for i in lModelList:
    senderModel = i
    print i.Name
    for a in senderModelList:
        if i.Name == a.Name:
            recvModel = a
            recv = lCnst.ConstrainObject( recvModel )
            sender = lCnst.SetAsSource( senderModel )
            recv.UseGlobalTransforms= False
            sender.UseGlobalTransforms= False
            senderRotation = None
            for each in sender.AnimationNodeOutGet().Nodes:
                if each.Name == 'Lcl Rotation':
                    senderRotation = each
            recvRotation = None
            for each in recv.AnimationNodeInGet().Nodes:
                if each.Name == 'Lcl Rotation':
                    recvRotation = each
                   
            FBConnect(senderRotation, recvRotation)