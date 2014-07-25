#if defined(DUISHARP_DLL)
#if defined(DUISHARP_EXPORTS)
#if defined(_MSC_VER)
#define DUISHARP_API __declspec(dllexport)
#else
#define DUISHARP_API 
#endif
#else
#if defined(_MSC_VER)
#define DUISHARP_API __declspec(dllimport)
#else
#define DUISHARP_API 
#endif
#endif
#else
#define DUISHARP_API
#endif

// Remove pointless warning messages
#ifdef _MSC_VER
#pragma warning (disable : 4511) // copy operator could not be generated
#pragma warning (disable : 4512) // assignment operator could not be generated
#pragma warning (disable : 4702) // unreachable code (bugs in Microsoft's STL)
#pragma warning (disable : 4786) // identifier was truncated
#pragma warning (disable : 4996) // function or variable may be unsafe (deprecated)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // eliminate deprecation warnings for VS2005
#endif
#endif // _MSC_VER
#ifdef __BORLANDC__
#pragma option -w-8027		   // function not expanded inline
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <atlconv.h>
#include <olectl.h>

#include <uxtheme.h>
#include <vsstyle.h>
#include <dwmapi.h>

#include <GdiPlus.h>
#include <Gdiplusgraphics.h >
using namespace Gdiplus;

#include "UIBase.h"
#include "UIBufferedPaint.h"
#include "UIMarkup.h"
#include "UIRes.h"
#include "UIShadow.h"
#include "UIManager.h"
#include "UIRender.h"
#include "UIBitmap.h"
#include "UIApp.h"
#include "UIDelegate.h"

#include "UIControl.h"
#include "UIControls.h"
#include "UIContainer.h"
#include "UILayouts.h"
#include "UIGif.h"
#include "UIList.h"
#include "UITree.h"
#include "UICombo.h"
#include "UICalendar.h"
#include "UIActiveX.h"
#include "UIWebBrowser.h"
#include "UIRichEdit.h"

#include "UIBuilder.h"
#include "UIWindow.h"
#include "UIObserver.h"
#include "UIMenu.h"

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "dwmapi.lib" )
#pragma comment( lib, "Uxtheme.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "GdiPlus.lib" )
#pragma comment( lib, "shlwapi.lib" )

