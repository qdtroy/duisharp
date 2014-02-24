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

	typedef std::pair<unsigned long, unsigned long> PairRes;
	typedef std::map<CStdString, PairRes> MapRes;

	typedef std::map<CStdString, CStdString> MapString;
	typedef std::map<CStdString, TFontInfo*> MapFont;
	typedef std::map<CStdString, TImageInfo*> MapImage;

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CUIResManager
	{
	public:
		CUIResManager();
		~CUIResManager();

	public:
		bool LoadRes(STRINGorID sResID, LPCTSTR lpszType = NULL, bool bZip = true);
		void ClearRes();
	
	public:
		TImageInfo* GetImage(const STRINGorID sResID, LPCTSTR lpszType = NULL, DWORD dwMask = 0);
		TImageInfo* GetImage(LPCTSTR pstrImage);
		bool GetXml(LPCTSTR pstrResID, std::string& strXml);
		HFONT GetFont(LPCTSTR pstrResID);
		TFontInfo* GetFontInfo(LPCTSTR pstrResID);
		LPCTSTR GetStyle(LPCTSTR pstrResID);

	public:
		TImageInfo* LoadImage(const STRINGorID sResID, LPCTSTR lpszType = NULL, DWORD dwMask = 0);
		TImageInfo* LoadImage(const void* pData, const int nLen, DWORD dwMask = 0);
		void RemoveImage(const STRINGorID sResID);

		bool ReadData(CStdString sResID, void** ppBuffer, DWORD& dwSize, LPCTSTR lpstrType = NULL);
		void FreeData(void* pBuffer);

	private:
		bool LoadStringRes(CUIMarkupNode root);
		bool LoadImageRes(CUIMarkupNode root);
		bool LoadXmlRes(CUIMarkupNode root);
		bool LoadFontRes(CUIMarkupNode root);
		bool LoadStyleRes(CUIMarkupNode root);

	private:
		MapRes m_mapRes;
		MapString m_mapImage;
		MapString m_mapXml;
		MapFont m_mapFont;
		MapString m_mapStyle;

		MapImage m_mapImageCache;
		
		bool m_bZip;
		CStdString m_strResName;
		HANDLE m_hResHandle;
		CStdFile m_memZipRes;
		void* m_pResPackData;
		CRITICAL_SECTION m_cs;
	};
} // namespace duisharp

#endif // __UIRES_H__
