#ifndef __UIRICHEDIT_H__
#define __UIRICHEDIT_H__

#include <richole.h>

namespace duisharp {

	class CTxtWinHost;
	class CImageDataObject;
	class CGifOleObject;

	class DUISHARP_API CUIRichEdit : public CUIContainer, public IUISubMessageFilter
	{
	public:
		class IRichEditOleExCallback : public IRichEditOleCallback
		{
		public :
			IRichEditOleExCallback();
			virtual ~ IRichEditOleExCallback();
			int m_iNumStorages;
			IStorage * pStorage;
			DWORD m_dwRef;

			virtual HRESULT STDMETHODCALLTYPE GetNewStorage(LPSTORAGE * lplpstg);
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
			virtual ULONG STDMETHODCALLTYPE AddRef();
			virtual ULONG STDMETHODCALLTYPE Release();
			virtual HRESULT STDMETHODCALLTYPE GetInPlaceContext(LPOLEINPLACEFRAME FAR * lplpFrame, LPOLEINPLACEUIWINDOW FAR * lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo);
			virtual HRESULT STDMETHODCALLTYPE ShowUIContainer(BOOL fShow);
			virtual HRESULT STDMETHODCALLTYPE QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp);
			virtual HRESULT STDMETHODCALLTYPE DeleteObject(LPOLEOBJECT lpoleobj);
			virtual HRESULT STDMETHODCALLTYPE QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT FAR * lpcfFormat, DWORD reco, BOOL fReally, HGLOBAL hMetaPict);
			virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);
			virtual HRESULT STDMETHODCALLTYPE GetClipboardData(CHARRANGE FAR * lpchrg, DWORD reco, LPDATAOBJECT FAR * lplpdataobj);
			virtual HRESULT STDMETHODCALLTYPE GetDragDropEffect(BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect);
			virtual HRESULT STDMETHODCALLTYPE GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE FAR * lpchrg, HMENU FAR * lphmenu);
		};

	public:
		CUIRichEdit();
		~CUIRichEdit();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		bool IsWantTab() const;
		void SetWantTab(bool bWantTab = true);
		bool IsWantReturn() const;
		void SetWantReturn(bool bWantReturn = true);
		bool IsWantCtrlReturn() const;
		void SetWantCtrlReturn(bool bWantCtrlReturn = true);
		bool IsRich() const;
		void SetRich(bool bRich = true);
		bool IsReadOnly() const;
		void SetReadOnly(bool bReadOnly = true);
		bool GetWordWrap() const;
		void SetWordWrap(bool bWordWrap = true);
		LPCTSTR GetFont();
		void SetFont(LPCTSTR pstrFont);
		void SetFont(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		LONG GetWinStyle();
		void SetWinStyle(LONG lStyle);
		DWORD GetTextColor();
		void SetTextColor(DWORD dwTextColor);
		DWORD GetBkColor();
		void SetBkColor(DWORD dwBkColor);
		int GetLimitText();
		void SetLimitText(int iChars);
		long GetTextLength(DWORD dwFlags = GTL_DEFAULT) const;
		CStdString GetText() const;
		void SetText(LPCTSTR pstrText);
		bool GetModify() const;
		void SetModify(bool bModified = true) const;
		void GetSel(CHARRANGE &cr) const;
		void GetSel(long& nStartChar, long& nEndChar) const;
		int SetSel(CHARRANGE &cr);
		int SetSel(long nStartChar, long nEndChar);
		void ReplaceSel(LPCTSTR lpszNewText, bool bCanUndo);
		void ReplaceSelW(LPCWSTR lpszNewText, bool bCanUndo = false);
		CStdString GetSelText() const;
		int SetSelAll();
		int SetSelNone();
		WORD GetSelectionType() const;
		bool GetZoom(int& nNum, int& nDen) const;
		bool SetZoom(int nNum, int nDen);
		bool SetZoomOff();
		bool GetAutoURLDetect() const;
		bool SetAutoURLDetect(bool bAutoDetect = true);
		DWORD GetEventMask() const;
		DWORD SetEventMask(DWORD dwEventMask);
		CStdString GetTextRange(long nStartChar, long nEndChar) const;
		void HideSelection(bool bHide = true, bool bChangeStyle = false);
		void ScrollCaret();
		int InsertText(long nInsertAfterChar, LPCTSTR lpstrText, bool bCanUndo = false);
		int AppendText(LPCTSTR lpstrText, bool bCanUndo = false);
		DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;
		bool SetDefaultCharFormat(CHARFORMAT2 &cf);
		DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;
		bool SetSelectionCharFormat(CHARFORMAT2 &cf);
		bool SetWordCharFormat(CHARFORMAT2 &cf);
		DWORD GetParaFormat(PARAFORMAT2 &pf) const;
		bool SetParaFormat(PARAFORMAT2 &pf);
		bool Redo();
		bool Undo();
		void Clear();
		void Copy();
		void Cut();
		void Paste();
		int GetLineCount() const;
		CStdString GetLine(int nIndex, int nMaxLength) const;
		int LineIndex(int nLine = -1) const;
		int LineLength(int nLine = -1) const;
		bool LineScroll(int nLines, int nChars = 0);
		CStdPoint GetCharPos(long lChar) const;
		long LineFromChar(long nIndex) const;
		CStdPoint PosFromChar(UINT nChar) const;
		int CharFromPos(CStdPoint pt) const;
		void EmptyUndoBuffer();
		UINT SetUndoLimit(UINT nLimit);
		long StreamIn(int nFormat, EDITSTREAM &es);
		long StreamOut(int nFormat, EDITSTREAM &es);

		void DoInit();
		bool SetDropAcceptFile(bool bAccept);
		// 注意：TxSendMessage和SendMessage是有区别的，TxSendMessage没有multibyte和unicode自动转换的功能，
		// 而richedit2.0内部是以unicode实现的，在multibyte程序中，必须自己处理unicode到multibyte的转换
		virtual HRESULT TxSendMessage(UINT msg, WPARAM wparam, LPARAM lparam, LRESULT *plresult) const; 
		IDropTarget* GetTxDropTarget();
		virtual bool OnTxViewChanged();
		virtual void OnTxNotify(DWORD iNotify, void *pv);

		void SetScrollPos(SIZE szPos);
		void LineUp();
		void LineDown();
		void PageUp();
		void PageDown();
		void HomeUp();
		void EndDown();
		void LineLeft();
		void LineRight();
		void PageLeft();
		void PageRight();
		void HomeLeft();
		void EndRight();

		void SetPos(RECT rc);
		void DoEvent(TUIEvent& event);
		void DoPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

		// OLEObject对象接口回调
		IRichEditOle* GetIRichEditOle();
		BOOL SetOLECallback(IRichEditOleCallback* pCallback);

		// 插入OLE对象
		BOOL InsertImage(LPCTSTR szFilePath, DWORD dwUserData, LPCTSTR sType = NULL);
		BOOL InsertGIF(LPCTSTR szFilePath, DWORD dwUserData, LPCTSTR sType = NULL);

		void BuildMemDC(HDC hDC, int cx, int cy);
		HDC GetMemDC();
	protected:
		IRichEditOleCallback* m_pIRichEditOleCallback;
		CTxtWinHost* m_pTwh;
		bool m_bVScrollBarFixing;
		bool m_bWantTab;
		bool m_bWantReturn;
		bool m_bWantCtrlReturn;
		bool m_bRich;
		bool m_bReadOnly;
		bool m_bWordWrap;
		DWORD m_dwTextColor;
		CStdString m_sFont;
		int m_iFont;
		int m_iLimitText;
		LONG m_lTwhStyle;
		HDC m_hMemDC;
		HBITMAP m_hMemBmp;
		HGDIOBJ m_hOldBmp;
	};

} // namespace duisharp

#endif // __UIRICHEDIT_H__
