#ifndef __UIBUFFEREDPAINT_H__
#define __UIBUFFEREDPAINT_H__

namespace duisharp {

	class DUISHARP_API CUIBufferedPaint
	{
	public:
		CUIBufferedPaint();
		~CUIBufferedPaint();

	public:
		bool IsNull() const;

		HPAINTBUFFER Begin(HDC hdcTarget, const RECT* prcTarget, BP_BUFFERFORMAT dwFormat, BP_PAINTPARAMS* pPaintParams, HDC* phdcPaint);
		HRESULT End(BOOL bUpdate = TRUE);

		HRESULT GetTargetRect(LPRECT pRect) const;
		HDC GetTargetDC() const;
		HDC GetPaintDC() const;
		HRESULT GetBits(RGBQUAD** ppbBuffer, int* pcxRow) const;
		HRESULT Clear(const RECT* pRect = NULL);
		HRESULT SetAlpha(BYTE alpha, const RECT* pRect = NULL);
		HRESULT MakeOpaque(const RECT* pRect = NULL);

		static bool IsBufferedPaintSupported();

	private:
		HPAINTBUFFER m_hPaintBuffer;
		static int m_nIsBufferedPaintSupported;
	};

} // namespace duisharp

#endif // __UIBUFFEREDPAINT_H__