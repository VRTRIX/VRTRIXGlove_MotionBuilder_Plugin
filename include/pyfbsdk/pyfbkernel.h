// =======================================================================================
// FBKernel
// =======================================================================================
void FBKernel_Init();

class FBKernel_Wrapper : public FBComponent_Wrapper {
public:
	FBKernel* mFBKernel;
public:
	FBKernel_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBKernel = (FBKernel*)pFBComponent; }	
	FBKernel_Wrapper(  ) : FBComponent_Wrapper( new FBKernel(  )) { mFBKernel = (FBKernel*)mFBComponent; }
	virtual ~FBKernel_Wrapper( ) {}
	bool Init(char *pLibraryDirectory) { return mFBKernel->Init( pLibraryDirectory ); }
	bool InitOpenGL() { return mFBKernel->InitOpenGL(); }
	bool Close() { return mFBKernel->Close(); }
};
