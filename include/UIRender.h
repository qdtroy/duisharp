#ifndef __UIRENDER_H__
#define __UIRENDER_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CRenderClip
	{
	public:
		~CRenderClip();
		RECT rcItem;
		HDC hDC;
		HRGN hRgn;
		HRGN hOldRgn;

		static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);
		static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
		static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
		static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIRender
	{
	public:
		static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
		// GDI
		static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
			const RECT& rcBmpPart, const RECT& rcCorners, bool bAlpha, BYTE uFade = 255, 
			bool hole = false, bool xtiled = false, bool ytiled = false);
		static bool DrawImageString(HDC hDC, CUIManager* pManager, const RECT& rcItem, const RECT& rcPaint, 
			LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
		// GDIPlus
		static void DrawImage(Graphics& graphics, Bitmap *pImage, int x, int y, int cx, int cy, const RECT& rcSrc, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(Graphics& graphics, Bitmap *pImage, const RECT& rc, const RECT& rcSrc, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(Graphics& graphics, Bitmap *pImage, int x, int y, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(HDC hDC, Bitmap* pBitmap, const RECT& rcDest, const RECT& rcPaint, RECT& rcSrc, RECT& rcCorners, bool bHole = false, DWORD dwMask = 0, float fFade = 1.0f, bool xtiled = false, bool ytiled = false);
		
		// 绘制颜色
		static void DrawColor(HDC hDC, const RECT& rc, DWORD color);
		static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

		// 以下函数中的颜色参数alpha值无效
		static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void DrawRect(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void DrawText(HDC hDC, CUIManager* pManager, RECT& rcDestArea, LPCTSTR pstrText, DWORD dwTextColor, LPCTSTR pstrFont, UINT uStyle, int nGlowSize = -1);
		static void DrawHtmlText(HDC hDC, CUIManager* pManager, RECT& rc, LPCTSTR pstrText, 
			DWORD dwTextColor, RECT* pLinks, CStdString* sLinks, int& nLinkRects, LPCTSTR pstrFont, UINT uStyle, int nGlowSize = -1);
		static HBITMAP GenerateBitmap(CUIControl* pControl, UINT uType = 0);
	};

} // namespace duisharp

#endif // __UIRENDER_H__
