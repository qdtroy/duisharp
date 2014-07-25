#ifndef __UIRES_H__
#define __UIRES_H__

namespace duisharp {

	/////////////////////////////////////////////////////////////////////////////////////
	//
	// Structure for Skin
	typedef struct tagTUISkin
	{
		int nType;	
		CStdString sFile;
		CStdString sType;
	} TUISkin;

	typedef struct tagTFontInfo
	{
		HFONT hFont;
		CStdString sFontName;
		CStdString sFaceName;
		int iSize;
		bool bBold;
		bool bUnderline;
		bool bItalic;
		TEXTMETRIC tm;
	} TFontInfo;

	typedef struct tagTImageInfo
	{
		int nWidth;
		int nHeight;
		Bitmap* pBitmap;
		HBITMAP hBitmap;
		DWORD dwMask;
		bool bAlpha;
		CStdString sResType;
	} TImageInfo;

	typedef struct tagTPairInfo
	{
		unsigned long ulVal1;
		unsigned long ulVal2;
	} TPairInfo;

	typedef CStdStringPtrMapImpl<TPairInfo*> MapRes;
	typedef CStdStringPtrMapImpl<TFontInfo*> MapFont;
	typedef CStdStringPtrMapImpl<TImageInfo*> MapImage;
	typedef CStdStringPtrMapImpl<CStdString*> MapString;
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CUIRes
	{
	public:
		CUIRes();
		~CUIRes();

	public:
		bool LoadRes(HINSTANCE hRes, STRINGorID sResID, LPCTSTR lpszType = NULL, bool bZip = true);
		void ClearRes();
	
	public:
		TImageInfo* GetImage(const STRINGorID sResID, LPCTSTR lpszType = NULL, DWORD dwMask = 0);
		TImageInfo* GetStrImage(LPCTSTR pstrImage);
		bool GetXml(LPCTSTR pstrResID, char** xml, int &len);
		HFONT GetFont(LPCTSTR pstrResID);
		TFontInfo* GetFontInfo(LPCTSTR pstrResID);
		bool GetStyle(LPCTSTR pstrResID, CStdString& sStyle);
		TImageInfo* GetColor(DWORD dwColor);

	public:
		TImageInfo* LoadImage(const STRINGorID ResID, LPCTSTR lpszType = NULL, DWORD dwMask = 0, int nFlag = 0);
		TImageInfo* LoadImage(const void* pData, const int nLen, DWORD dwMask = 0, int nFlag = 0);
		bool ReadXmlData(const STRINGorID ResID, void** ppBuffer, DWORD& dwBuffer, LPCTSTR lpstrType = NULL);
		bool ReadImageData(const STRINGorID ResID, void** ppBuffer, DWORD& dwBuffer, LPCTSTR lpstrType = NULL);
		void FreeData(void* pBuffer);

	private:
		bool LoadStringRes(CUIMarkupNode root);
		bool LoadImageRes(CUIMarkupNode root);
		bool LoadXmlRes(CUIMarkupNode root);
		bool LoadFontRes(CUIMarkupNode root);
		bool LoadStyleRes(CUIMarkupNode root);
		bool ParseRes(const STRINGorID ResID, LPCTSTR lpszType = NULL);

	private:
		bool m_bZip;
		HINSTANCE m_hRes;
		CStdString m_strResName;
		CStdFile m_memZipRes;
		void* m_pResPackData;
		
		MapRes m_mapRes;
		MapString m_mapImage;
		MapString m_mapXml;
		MapString m_mapStyle;
		MapFont m_mapFont;
		MapImage m_mapImageCache;
		MapImage m_mapColorCache;
	};
} // namespace duisharp

#endif // __UIRES_H__
