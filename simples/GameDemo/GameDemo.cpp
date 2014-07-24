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
		skin.sFile = _T("skin\\GameRes");
		skin.sType = _T("");
#endif
		LoadSkin(skin);

		return TRUE;
	}

	virtual int Run()
	{
		// 添加消息链
		CUIMessageLoop msgLoop;
		_App->AddMessageLoop(&msgLoop);

		CMainFrame* pFrame = new CMainFrame();
		if( pFrame == NULL ) return 0;
		pFrame->Create(NULL, _T("TroyGame"), WS_OVERLAPPEDWINDOW, 0L, 0, 0, 296, 573);
		
		pFrame->CenterWindow();
		::ShowWindow(*pFrame, SW_SHOW);

		// 消息运行
		msgLoop.Run();

		// 移除消息链
		_App->RemoveMessageLoop();

		return 0;
	}

	virtual void Term()
	{
		CUIApp::Term();
	}
};

CMyApp myApp;

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	myApp.Init(hInstance);
	myApp.Run();
	myApp.Term();

	return 0;
}