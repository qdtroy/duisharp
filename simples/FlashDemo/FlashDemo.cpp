#include "stdafx.h"
#include "MainfFrame.h"
//#define USE_ZIP
class CMyApp : public CUIApp
{
public:
	CMyApp()
	{

	}
	~CMyApp()
	{

	}

public:
	virtual BOOL Init(HINSTANCE hInstance)
	{
		CUIApp::Init(hInstance);
		CUIShadow::Initialize(hInstance);

#ifdef USE_ZIP
		TUISkin skin;
		skin.nType = 0;
		skin.sFile = _T("IDR_SKIN");
		skin.sType = _T("SKIN");
#else
		TUISkin skin;
		skin.nType = 2;
		skin.sFile = _T("skin\\FlashRes");
		skin.sType = _T("SKIN");
#endif
		LoadSkin(skin);

		CQQFrame* pFrame = new CQQFrame();
		if( pFrame == NULL ) return 0;
		pFrame->Create(NULL, _T("FlashDemo"), WS_OVERLAPPEDWINDOW, 0L, 0, 0, 296, 573);
		
		pFrame->CenterWindow();
		::ShowWindow(*pFrame, SW_SHOW);


		return TRUE;
	}

	virtual int Run()
	{
		return CUIApp::Run();
	}

	virtual void Term()
	{
		CUIApp::Term();
	}
};

CMyApp myApp;