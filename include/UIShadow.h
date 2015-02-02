#ifndef __UISHADOW_H__
#define __UISHADOW_H__

namespace duisharp
{
	class CUIManager;
	class DUISHARP_API CUIShadow
	{
	public:
		CUIShadow(void);
		virtual ~CUIShadow(void);

	public:
		static bool Initialize(HINSTANCE hInstance);

		void Create(HWND hParent, CUIManager *pManager = NULL);
		bool IsShadowed(HWND hParent) const;
		bool IsEnable() const;
		void SetEnable(bool bEnable = true);
		CStdString GetImage();
		void SetImage(LPCTSTR pImage);
		RECT GetBorder() const;
		void SetBorder(RECT rcBorder);
		RECT GetOffset() const;
		void SetOffset(RECT rcOffset);
		bool IsTrans() const;
		void SetTrans(bool bTrans = true);
		bool IsPrepared() const;
		void SetPrepared(bool bPrepared = true);

	protected:
		// 父窗口消息处理函数
		static LRESULT CALLBACK ParentProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT OnParentProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		// 刷新
		void Update(HWND hParent);
		// 显示
		void Show(HWND hParent, bool bFast = true);
		void ShowShadow(bool bVisible, bool bFast = false);

	private:
		// 类静态变量：程序实例句柄和所有阴影窗口
		static HINSTANCE s_hInstance;
		static CStdStringPtrMapImpl<CUIShadow*> s_Shadowmap;

	private:
		// 阴影图片
		CStdString m_sImage;
		// UI管理器
		CUIManager* m_pManager;
		// 是否刷新
		bool m_bUpdate;
		// 是否可见
		bool m_bVisible;
		// 是否启用
		bool m_bEnabled;
		// 是否投过鼠标消息
		bool m_bTrans;
		// 是否主动移动
		bool m_bMoving;
		// 阴影大小
		RECT m_rcBorder;
		// 偏移量
		RECT m_rcOffset;
		// 起始位置
		POINT m_ptPos;
		// 窗口大小
		LPARAM m_WndSize;
		// 窗口句柄
		HWND m_hWnd;
		// 父窗口消息处理函数
		WNDPROC m_OriParentProc;
		// 双缓存
		HDC m_hDcPaint;
		HDC m_hDcBuffer;
		HBITMAP m_hBmpBuffer;
		// 父窗口是否布局完毕
		bool m_bPrepared;
	};
}

#endif //__UISHADOW_H__