#ifndef pyfbtree_h__
#define pyfbtree_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbvisualcomponent.h"
#include "pyfbtreenode.h"

// =======================================================================================
// FBTree
// =======================================================================================
void FBTree_Init();

class PYSDK_DLL FBTree_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBTree* mFBTree;
public:
	FBTree_Wrapper( FBComponent* pFBComponent );
	FBTree_Wrapper();
	virtual ~FBTree_Wrapper( ) {  }
	void Clear() { mFBTree->Clear(  ); }
	object GetRoot() { return FBWrapperFactory::TheOne().WrapFBObject( mFBTree->GetRoot(  )); }
	object InsertLast(FBTreeNode_Wrapper& pNode, const char * pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTree->InsertLast( pNode.mFBTreeNode, pName )); }
	void SetAllowCollapse( bool pAllowCollapse ) { mFBTree->AllowCollapse = pAllowCollapse; }
	bool GetAllowCollapse(  ) { return mFBTree->AllowCollapse; }
	void SetAllowExpansion( bool pAllowExpansion ) { mFBTree->AllowExpansion = pAllowExpansion; }
	bool GetAllowExpansion(  ) { return mFBTree->AllowExpansion; }
	void SetAutoExpandOnDblClick( bool pAutoExpandOnDblClick ) { mFBTree->AutoExpandOnDblClick = pAutoExpandOnDblClick; }
	bool GetAutoExpandOnDblClick(  ) { return mFBTree->AutoExpandOnDblClick; }
	void SetAutoExpandOnDragOver( bool pAutoExpandOnDragOver ) { mFBTree->AutoExpandOnDragOver = pAutoExpandOnDragOver; }
	bool GetAutoExpandOnDragOver(  ) { return mFBTree->AutoExpandOnDragOver; }
	void SetAutoScroll( bool pAutoScroll ) { mFBTree->AutoScroll = pAutoScroll; }
	bool GetAutoScroll(  ) { return mFBTree->AutoScroll; }
	void SetAutoScrollOnExpand( bool pAutoScrollOnExpand ) { mFBTree->AutoScrollOnExpand = pAutoScrollOnExpand; }
	bool GetAutoScrollOnExpand(  ) { return mFBTree->AutoScrollOnExpand; }
	void SetCheckBoxes( bool pCheckBoxes ) { mFBTree->CheckBoxes = pCheckBoxes; }
	bool GetCheckBoxes(  ) { return mFBTree->CheckBoxes; }
	void SetDeselectOnCollapse( bool pDeselectOnCollapse ) { mFBTree->DeselectOnCollapse = pDeselectOnCollapse; }
	bool GetDeselectOnCollapse(  ) { return mFBTree->DeselectOnCollapse; }
	void SetEditNodeOn2Select( bool pEditNodeOn2Select ) { mFBTree->EditNodeOn2Select = pEditNodeOn2Select; }
	bool GetEditNodeOn2Select(  ) { return mFBTree->EditNodeOn2Select; }
	void SetHighlightOnRightClick( bool pHighlightOnRightClick ) { mFBTree->HighlightOnRightClick = pHighlightOnRightClick; }
	bool GetHighlightOnRightClick(  ) { return mFBTree->HighlightOnRightClick; }
	void SetIndent( int pIndent ) { mFBTree->Indent = pIndent; }
	int GetIndent(  ) { return mFBTree->Indent; }
	void SetItemHeight( int pItemHeight ) { mFBTree->ItemHeight = pItemHeight; }
	int GetItemHeight(  ) { return mFBTree->ItemHeight; }
	void SetMultiDrag( bool pMultiDrag ) { mFBTree->MultiDrag = pMultiDrag; }
	bool GetMultiDrag(  ) { return mFBTree->MultiDrag; }
	void SetMultiSelect( bool pMultiSelect ) { mFBTree->MultiSelect = pMultiSelect; }
	bool GetMultiSelect(  ) { return mFBTree->MultiSelect; }
	void SetNoSelectOnDrag( bool pNoSelectOnDrag ) { mFBTree->NoSelectOnDrag = pNoSelectOnDrag; }
	bool GetNoSelectOnDrag(  ) { return mFBTree->NoSelectOnDrag; }
	void SetNoSelectOnRightClick( bool pNoSelectOnRightClick ) { mFBTree->NoSelectOnRightClick = pNoSelectOnRightClick; }
	bool GetNoSelectOnRightClick(  ) { return mFBTree->NoSelectOnRightClick; }
	int GetSelectedCount(  ) { return mFBTree->SelectedCount; }
	void SetSelectionActive( bool pSelectionActive ) { mFBTree->SelectionActive = pSelectionActive; }
	bool GetSelectionActive(  ) { return mFBTree->SelectionActive; }
	void SetShowLines( bool pShowLines ) { mFBTree->ShowLines = pShowLines; }
	bool GetShowLines(  ) { return mFBTree->ShowLines; }
	int GetTreeHeight(  ) { return mFBTree->TreeHeight; }
	int GetTreeWidth(  ) { return mFBTree->TreeWidth; }
	int GetVisibleItemCount(  ) { return mFBTree->VisibleItemCount; }

    object GetSelectedNodes( void );

    object OnChange();
    object OnClick();
    object OnClickCheck();
    object OnDblClick();
    object OnCollapsed();
    object OnCollapsing();
    object OnExpanded();
    object OnExpanding();
    object OnSelect();
    object OnDragAndDrop();

protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbtree_h__