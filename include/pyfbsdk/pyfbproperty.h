#ifndef pyfbproperty_h__
#define pyfbproperty_h__
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

#include "pyfbstringlist.h"
//////////////////////////////////////////////////////////////////
//
// CLASS: FBProperty
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBProperty_Wrapper : public FBPlug_Wrapper
{
public:
	FBProperty* mFBProperty;
	FBProperty_Wrapper( FBProperty* pFBProperty );
	virtual ~FBProperty_Wrapper( );
	const char* GetName();
    void SetName(const char *pName);
    FBPropertyType GetPropertyType();
    void ModifyPropertyFlag(FBPropertyFlag pFlag, bool pValue);
    bool GetPropertyFlag(FBPropertyFlag pFlag);
    int GetPropertyFlags();
    const char* GetPropertyTypeName();
    const char* GetDataTypeName();

    virtual object GetData() const;
    virtual void SetData( object pData );

    const char* AsString( FBDataAsStringFlag pFlag = kFBDataAsStringUI );
    const char* OriValueAsString();
	bool SetString(const char* pValue );	

    bool IsAnimatable();
	bool IsInternal();
	bool IsList();
	bool IsObjectList();
	bool IsReadOnly();
	bool IsTextureConnectableProperty();
	bool IsReferenceProperty();
	bool IsMinClamp();
	bool IsMaxClamp();
	bool IsUserProperty();

	void	SetMin( double pMin, bool pForceMinClamp = false  );
	void	SetMax( double pMax, bool pForceMaxClamp = false  );
	double	GetMin();
	double	GetMax();

	bool	AllowsLocking() const;
	bool	HasSomethingLocked() const;
	bool	IsLocked() const;
	bool	IsMemberLocked( int pIndex ) const;
	void	SetLocked( bool pLocked );
	void	SetMemberLocked( int pIndex , bool pLocked );

    int 	GetSubMemberCount() const;
    const char* EnumList( int pIndex );
    FBStringList_Wrapper* GetEnumStringList(bool pCreateIt = true);
    FBStringList_Wrapper* GetEnumStringList1() { return GetEnumStringList(); }
    void NotifyEnumStringListChanged();
};

PYSDK_DLL object FBProperty_Wrapper_Factory( FBProperty& pFBProperty );
PYSDK_DLL inline object FBProperty_Wrapper_Factory( FBProperty* pFBProperty ) { return pFBProperty ? FBProperty_Wrapper_Factory(*pFBProperty) : object();}
void FBProperty_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyEnum
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyEnum_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyEnum* mFBPropertyEnum;
public:
	FBPropertyEnum_Wrapper( FBPropertyEnum* pFBPropertyEnum );
	virtual ~FBPropertyEnum_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyEnum_Wrapper_Factory( FBPropertyEnum& pFBPropertyEnum );
void FBPropertyEnum_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyComponent
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyComponent_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyComponent* mFBPropertyComponent;
public:
	FBPropertyComponent_Wrapper( FBPropertyComponent* pFBPropertyComponent );
	virtual ~FBPropertyComponent_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyComponent_Wrapper_Factory( FBPropertyComponent& pFBPropertyComponent );
void FBPropertyComponent_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyString
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyString_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyString* mFBPropertyString;
public:
	FBPropertyString_Wrapper( FBPropertyString* pFBPropertyString );
	virtual ~FBPropertyString_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyString_Wrapper_Factory( FBPropertyString& pFBPropertyString );
void FBPropertyString_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAction
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAction_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyAction* mFBPropertyAction;
public:
	FBPropertyAction_Wrapper( FBPropertyAction* pFBPropertyAction );
	virtual ~FBPropertyAction_Wrapper( );

    virtual object Call();
};
PYSDK_DLL object FBPropertyAction_Wrapper_Factory( FBPropertyAction& pFBPropertyAction );
void FBPropertyAction_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyBool
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyBool_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyBool* mFBPropertyBool;
public:
	FBPropertyBool_Wrapper( FBPropertyBool* pFBPropertyBool );
	virtual ~FBPropertyBool_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyBool_Wrapper_Factory( FBPropertyBool& pFBPropertyBool );
void FBPropertyBool_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyInt
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyInt_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyInt* mFBPropertyInt;
public:
	FBPropertyInt_Wrapper( FBPropertyInt* pFBPropertyInt );
	virtual ~FBPropertyInt_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyInt_Wrapper_Factory( FBPropertyInt& pFBPropertyInt );
void FBPropertyInt_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyDouble
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyDouble_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyDouble* mFBPropertyDouble;
public:
	FBPropertyDouble_Wrapper( FBPropertyDouble* pFBPropertyDouble );
	virtual ~FBPropertyDouble_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
object FBPropertyDouble_Wrapper_Factory( FBPropertyDouble& pFBPropertyDouble );
void FBPropertyDouble_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyFloat
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyFloat_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyFloat* mFBPropertyFloat;
public:
	FBPropertyFloat_Wrapper( FBPropertyFloat* pFBPropertyFloat );
	virtual ~FBPropertyFloat_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyFloat_Wrapper_Factory( FBPropertyFloat& pFBPropertyFloat );
void FBPropertyFloat_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyVector2d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyVector2d_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyVector2d* mFBPropertyVector2d;
public:
    FBPropertyVector2d_Wrapper( FBPropertyVector2d* pFBPropertyVector2d );
    virtual ~FBPropertyVector2d_Wrapper( );
    operator FBVector2d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};
PYSDK_DLL object FBPropertyVector2d_Wrapper_Factory( FBPropertyVector2d& pFBPropertyVector2d );
void FBPropertyVector2d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyVector3d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyVector3d_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyVector3d* mFBPropertyVector3d;
public:
    FBPropertyVector3d_Wrapper( FBPropertyVector3d* pFBPropertyVector3d );
    virtual ~FBPropertyVector3d_Wrapper( );
    operator FBVector3d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};
PYSDK_DLL object FBPropertyVector3d_Wrapper_Factory( FBPropertyVector3d& pFBPropertyVector3d );
void FBPropertyVector3d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyVector4d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyVector4d_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyVector4d* mFBPropertyVector4d;
public:
    FBPropertyVector4d_Wrapper( FBPropertyVector4d* pFBPropertyVector4d );
    virtual ~FBPropertyVector4d_Wrapper( );
    operator FBVector4d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};
PYSDK_DLL object FBPropertyVector4d_Wrapper_Factory( FBPropertyVector4d& pFBPropertyVector4d );
void FBPropertyVector4d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyColor
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyColor_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyColor* mFBPropertyColor;
public:
    FBPropertyColor_Wrapper( FBPropertyColor* pFBPropertyColor );
    virtual ~FBPropertyColor_Wrapper( );
    operator FBColor() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

PYSDK_DLL object FBPropertyColor_Wrapper_Factory( FBPropertyColor& pFBPropertyColor );
void FBPropertyColor_Init();
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyColorAndAlpha
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyColorAndAlpha_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyColorAndAlpha* mFBPropertyColorAndAlpha;
public:
    FBPropertyColorAndAlpha_Wrapper( FBPropertyColorAndAlpha* pFBPropertyColor );
    virtual ~FBPropertyColorAndAlpha_Wrapper( );
    operator FBColorAndAlpha() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

PYSDK_DLL object FBPropertyColorAndAlpha_Wrapper_Factory( FBPropertyColorAndAlpha& pFBPropertyColor );
void FBPropertyColorAndAlpha_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyTime
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyTime_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyTime* mFBPropertyTime;
public:
	FBPropertyTime_Wrapper( FBPropertyTime* pFBPropertyTime );
	virtual ~FBPropertyTime_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyTime_Wrapper_Factory( FBPropertyTime& pFBPropertyTime );
void FBPropertyTime_Init();

//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyTimeCode
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyTimeCode_Wrapper : public FBProperty_Wrapper
{
protected:
	FBPropertyTimeCode* mFBPropertyTimeCode;
public:
	FBPropertyTimeCode_Wrapper( FBPropertyTimeCode* pFBPropertyTimeCode );
	virtual ~FBPropertyTimeCode_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );

	bool operator==(const FBPropertyTimeCode_Wrapper& pTimeCode)const;
	bool operator!=(const FBPropertyTimeCode_Wrapper& pTimeCode)const;
};
PYSDK_DLL object FBPropertyTimeCode_Wrapper_Factory( FBPropertyTimeCode& pFBPropertyTimeCode );
void FBPropertyTimeCode_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatable
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatable_Wrapper : public FBProperty_Wrapper {
protected:
    FBPropertyAnimatable* mFBPropertyAnimatable;
public:
    FBPropertyAnimatable_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatable_Wrapper();
    object GetAnimationNode();
    object GetBox();
    bool IsAnimated();
	bool OriIsAnimated() const;
    bool IsFocused();
    void Key();
    void KeyAt( FBTime_Wrapper& pTime );
	void KeyRemoveAt( FBTime_Wrapper& pTime );
    void SetAnimated( bool pValue, bool pCheckLocked = false );
    void SetFocus( bool pValue );

    bool AllowsMuting() const;
    bool HasSomethingMuted() const;
    bool IsMuted() const;
    bool IsMemberMuted( int pIndex ) const;
    void SetMuted( bool pMuted );
    void SetMemberMuted( int pIndex , bool pMuted );

    virtual object GetData() const;
    virtual void SetData( object pData );
	const char* GetDataTypeName();
};
PYSDK_DLL object FBPropertyAnimatable_Wrapper_Factory( FBPropertyAnimatable& pFBPropertyAnimatable );
void FBPropertyAnimatable_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableEnum
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableEnum_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableEnum* mFBPropertyAnimatableEnum;
public:
    FBPropertyAnimatableEnum_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableEnum_Wrapper( );
    operator int() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableEnum_Wrapper_Factory( FBPropertyAnimatableEnum& pFBPropertyAnimatableEnum );
void FBPropertyAnimatableEnum_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableAction
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableAction_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableAction* mFBPropertyAnimatableAction;
public:
    FBPropertyAnimatableAction_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableAction_Wrapper( );
    operator bool() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableAction_Wrapper_Factory( FBPropertyAnimatableAction& pFBPropertyAnimatableAction );
void FBPropertyAnimatableAction_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableBool
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableBool_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableBool* mFBPropertyAnimatableBool;
public:
    FBPropertyAnimatableBool_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableBool_Wrapper( );
    operator bool() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};

void FBPropertyAnimatableBool_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableInt
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableInt_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableInt* mFBPropertyAnimatableInt;
public:
    FBPropertyAnimatableInt_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableInt_Wrapper( );
    operator int() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableInt_Wrapper_Factory( FBPropertyAnimatableInt& pFBPropertyAnimatableInt );
void FBPropertyAnimatableInt_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableInt64
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableInt64_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableInt64* mFBPropertyAnimatableInt64;
public:
    FBPropertyAnimatableInt64_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableInt64_Wrapper( );
    operator long long() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableInt64_Wrapper_Factory( FBPropertyAnimatableInt64& pFBPropertyAnimatableInt64 );
void FBPropertyAnimatableInt64_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableUInt64
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableUInt64_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableUInt64* mFBPropertyAnimatableUInt64;
public:
    FBPropertyAnimatableUInt64_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableUInt64_Wrapper( );
    operator unsigned long long() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableUInt64_Wrapper_Factory( FBPropertyAnimatableUInt64& pFBPropertyAnimatableUInt64 );
void FBPropertyAnimatableUInt64_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableDouble
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableDouble_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableDouble* mFBPropertyAnimatableDouble;
public:
    FBPropertyAnimatableDouble_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableDouble_Wrapper( );
    operator double() const;

    virtual object GetData() const;
    virtual void SetData( object pData );
};

void FBPropertyAnimatableDouble_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableVector2d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableVector2d_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableVector2d* mFBPropertyAnimatableVector2d;
public:
    FBPropertyAnimatableVector2d_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableVector2d_Wrapper( );
    operator FBVector2d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

void FBPropertyAnimatableVector2d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableVector3d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableVector3d_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableVector3d* mFBPropertyAnimatableVector3d;
public:
    FBPropertyAnimatableVector3d_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableVector3d_Wrapper( );
    operator FBVector3d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

void FBPropertyAnimatableVector3d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableVector4d
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableVector4d_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableVector4d* mFBPropertyAnimatableVector4d;
public:
    FBPropertyAnimatableVector4d_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableVector4d_Wrapper( );
    operator FBVector4d() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};
PYSDK_DLL object FBPropertyAnimatableVector4d_Wrapper_Factory( FBPropertyAnimatableVector4d& pFBPropertyAnimatableVector4d );
void FBPropertyAnimatableVector4d_Init();


//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableColor
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableColor_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableColor* mFBPropertyAnimatableColor;
public:
    FBPropertyAnimatableColor_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableColor_Wrapper( );
    operator FBColor() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

void FBPropertyAnimatableColor_Init();

//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyAnimatableColorAndAlpha
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyAnimatableColorAndAlpha_Wrapper : public FBPropertyAnimatable_Wrapper {
protected:
    FBPropertyAnimatableColorAndAlpha* mFBPropertyAnimatableColor;
public:
    FBPropertyAnimatableColorAndAlpha_Wrapper( FBProperty* pFBProperty );
    virtual ~FBPropertyAnimatableColorAndAlpha_Wrapper( );
    operator FBColorAndAlpha() const;

    virtual object GetData() const;
    virtual void SetData( object pData );

    int GetCount() const;
    double Get( int lIdx ) const;
    void Set( int lIdx, double lValue );
};

void FBPropertyAnimatableColorAndAlpha_Init();

class PYSDK_DLL FBPropertyAnimatableTime_Wrapper : public FBPropertyAnimatable_Wrapper
{
protected:
    FBPropertyAnimatableTime* mFBPropertyTime;
public:
    FBPropertyAnimatableTime_Wrapper( FBPropertyAnimatableTime* pFBPropertyTime );
    virtual ~FBPropertyAnimatableTime_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableTime_Wrapper_Factory( FBPropertyTime& pFBPropertyTime );
void FBPropertyAnimatableTime_Init();

class PYSDK_DLL FBPropertyAnimatableTimeCode_Wrapper : public FBPropertyAnimatable_Wrapper
{
protected:
    FBPropertyAnimatableTimeCode* mFBPropertyTimeCode;
public:
    FBPropertyAnimatableTimeCode_Wrapper( FBPropertyAnimatableTimeCode* pFBPropertyTimeCode );
    virtual ~FBPropertyAnimatableTimeCode_Wrapper( );

    virtual object GetData() const;
    virtual void SetData( object pData );
};
PYSDK_DLL object FBPropertyAnimatableTimeCode_Wrapper_Factory( FBPropertyTimeCode& pFBPropertyTimeCode );
void FBPropertyAnimatableTimeCode_Init();

#endif // pyfbproperty_h__