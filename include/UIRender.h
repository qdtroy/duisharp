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
		// GDI
		static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, const RECT& rcBmpPart, const RECT& rcCorners, bool bAlpha, BYTE uFade = 255, bool hole = false, bool xtiled = false, bool ytiled = false);
		static bool DrawImageString(HDC hDC, CUIManager* pManager, const RECT& rcItem, const RECT& rcPaint, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
		// GDIPlus
		static void DrawImage(Graphics& graphics, Bitmap *pImage, int x, int y, int cx, int cy, const RECT& rcSrc, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(Graphics& graphics, Bitmap *pImage, const RECT& rc, const RECT& rcSrc, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(Graphics& graphics, Bitmap *pImage, int x, int y, DWORD dwMask = 0, float fFade = 1.0f);
		static void DrawImage(HDC hDC, Bitmap* pBitmap, const RECT& rcDest, const RECT& rcPaint, RECT& rcSrc, RECT& rcCorners, bool bHole = false, DWORD dwMask = 0, float fFade = 1.0f, bool xtiled = false, bool ytiled = false);
		// 绘制颜色
		static void DrawColor(HDC hDC, const RECT& rc, DWORD color);
		static void DrawLine(HDC hDC, CUIManager* pManager, const RECT& rc, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void DrawRect(HDC hDC, CUIManager* pManager, const RECT& rc, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void DrawRoundRect(HDC hDC, CUIManager* pManager, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor, UINT uStyle = PS_SOLID);
		static void TextOut(HDC hDC, CUIManager* pManager, RECT& rcDestArea, LPCTSTR pstrText, int nText, HFONT hFont, DWORD dwTextColor, UINT uStyle, int nGlowSize = 0);
		static void DrawText(HDC hDC, CUIManager* pManager, RECT& rcDestArea, LPCTSTR pstrText, DWORD dwTextColor, LPCTSTR pstrFont, UINT uStyle, int nGlowSize = -1);
		static void DrawGlowingText(HDC hDC, CUIManager* pManager, RECT& rcDestArea, LPCTSTR pstrText, int nText, DWORD dwTextColor, HFONT hFont, UINT uStyle, int iGlowSize = 0);
		static void DrawHtmlText(HDC hDC, CUIManager* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, RECT* pLinks, CStdString* sLinks, int& nLinkRects, LPCTSTR pstrFont, UINT uStyle, int nGlowSize = -1);
		// 调整颜色
		static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
		// 截图
		static HBITMAP GenerateBitmap(CUIControl* pControl, LPRECT lpRectSrc = NULL, UINT uType = 0);
		// 图片RGN
		static HRGN GenerateRGN(LPCTSTR pStrImage);
		// 创建位图
		static HBITMAP CreateBitmap(HDC hDC, int nWidth, int nHeight, LPBYTE* ppBits = NULL, UINT nBitCount = 32);
	};

} // namespace duisharp

#endif // __UIRENDER_H__
