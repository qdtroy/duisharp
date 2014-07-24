#ifndef _UIBITMAP_H_
#define _UIBITMAP_H_

namespace duisharp
{
	class DUISHARP_API CUIBitmap
	{
	public:
		// 构造函数
		CUIBitmap();
		~CUIBitmap();

	public:
		bool IsNull();
		void Destroy();
		void Backup(){};

	public:
		bool Load(LPCTSTR pstrFileName);
		bool Load(HINSTANCE hInstance, LPCTSTR pstrResName, LPCTSTR pstrResType);
		bool Load(LPBYTE pData, DWORD dwSize);
		bool Load(IStream* pStream);

		bool Save(IStream** pStream, LPCTSTR MimeType, LPRECT lpRcSrc = NULL);
		bool Save(LPCTSTR pstrFileName, LPCTSTR MimeType, LPRECT lpRcSrc = NULL);
		
		virtual bool Create(DWORD dwWidth, DWORD dwHeight);
		virtual bool Create(IStream* pStream);
		virtual bool Create(HBITMAP hBitmap);

	public:
		HBITMAP GetHBITMAP();
		Bitmap* GetBitmap();

		int GetWidth();
		int GetHeight();

	public:
		virtual bool Clear(Color color);
		virtual bool Draw(HDC hDC, int nX, int nY, int nWidth, int nHeight, double fAlpha = 255.0f, double fRotate = 0.0f, double fXScale = 1.0f, double fYScale = 1.0f);
		virtual bool Draw(Graphics& g, int nX, int nY, int nWidth, int nHeight, double fAlpha = 255.0f, double fRotate = 0.0f, double fXScale = 1.0f, double fYScale = 1.0f);

		virtual bool Draw(HDC hDC, RECT rcDest, LPCRECT pRcSrc = NULL, double fAlpha = 255.0f, bool bXTiled = true, bool bYTiled = true);
		virtual bool Draw(Image* pImage, RECT rcDest, LPCRECT pRcSrc = NULL, double fAlpha = 255.0f, bool bXTiled = true, bool bYTiled = true);
		virtual bool Draw(CUIBitmap* pImage, RECT rcDest, LPCRECT pRcSrc = NULL, double fAlpha = 255.0f, bool bXTiled = true, bool bYTiled = true);
		virtual bool DrawImage(Graphics& g, int nLeft, int nTop, int nWidth, int nHeight, int nSrcLeft, int nSrcTop, int nSrcWidth, int nSrcHeight, double fAlpha);
		virtual bool DrawEx(HDC hDC, RECT rcDest, LPCRECT pRcSrc = NULL, LPCRECT pRcCorner = NULL, double fAlpha = 255.0f, bool bXTiled = false, bool bYTiled = false);
	
	public:
		// 失败返回 -1 ： image/bmp image/jpeg image/gif image/tiff image/png 
		static int GetEncoderClsid(LPCTSTR MimeType, CLSID* pClsid);

	protected:
		Bitmap* m_pBitmap;
	};
}

#endif // _UIBITMAP_H_