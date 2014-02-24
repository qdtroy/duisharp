#ifndef __UIGIF_H__
#define __UIGIF_H__

namespace duisharp {

	struct GIFFrame    // structure that keeps a single frame info
	{
		TImageInfo* pImage;
		SIZE frameSize;
		SIZE frameOffset;
		UINT nDelay;       // delay (in 1/100s of a second)
		UINT nDisposal;    // disposal method
	};

	typedef std::vector<GIFFrame> GIFFRAME;
	typedef std::vector<GIFFrame>::iterator GIFFRAMEITER;
	
	struct TGIFHeader;
	struct TGIFLSDescriptor;

	enum enGifTimer
	{
		TIMER_GIF = UITIMER_ID_ANIMATION,
	};

	class DUISHARP_API CUIGif : public CUILabel
	{
	public:
		CUIGif();
		~CUIGif();

	public:
		static bool IsGif(const LPBYTE pData, DWORD dwSize);

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		bool Load(const LPBYTE pData, DWORD dwSize, DWORD dwMask = 0);
		void UnLoad();

		bool IsGif();
		bool Play();
		void Stop();
		bool IsPlaying() const;

		SIZE GetSize() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetFrame() const;
		int GetFrames() const;
		COLORREF GetBkColor() const;

		LPCTSTR GetGifImage();
		void SetGifImage(LPCTSTR pStrImage);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TUIEvent& event);

		void PaintBkImage(HDC hDC);

	private:
		int GetNextBlockLen() const;
		BOOL SkipNextBlock();
		BOOL SkipNextGraphicBlock();
		void ResetDataPointer();
		enum GIFBlockTypes GetNextBlock() const;
		UINT GetSubBlocksLen(UINT nStartingOffset) const;
		LPBYTE GetNextGraphicBlock(UINT* pBlockLen, UINT* pDelay, SIZE* pBlockSize, SIZE* pBlockOffset, UINT* pDisposal);

	protected:
		CStdString m_sGifImage;
		bool m_bGifGdi;

	private:
		unsigned char* m_pRawData;		// 解析时用于暂存动画文件数据 解析结束后重置无效
		UINT m_nDataSize;				// GIF文件大小
		TGIFHeader* m_pGIFHeader;		// GIF文件头
		TGIFLSDescriptor* m_pGIFLSDescriptor; // 逻辑屏幕标识符
		UINT m_nGlobalCTSize;			// 全局颜色列表大小
		SIZE m_szGif;					// 图像尺寸
		COLORREF m_clrBackground;		// 背景色
		volatile long m_nCurrFrame;	// 当前帧索引值
		UINT m_nCurrOffset;			// 块读取偏移量

		// 动画数据
		UINT *m_puFrameElapse;			// 帧间隔
		UINT m_nFramePosition;			// 当前帧
		GIFFRAME* m_pvFrames;			// 帧数组
		bool m_bGif;					// 是否Gif图片
		bool m_bPlaying;				// 是否正在播放
	};
} // namespace duisharp

#endif // __UIGIF_H__
