#ifndef __UIBUILDER_H__
#define __UIBUILDER_H__



namespace duisharp {

	class IUIBuilderCallback
	{
	public:
		virtual CUIControl* CreateControl(LPCTSTR pstrClass) = 0;
	};


	class DUISHARP_API CUIBuilder
	{
	public:
		CUIBuilder();

	public:
		bool LoadXml(STRINGorID xml, LPCTSTR type = NULL, IUIBuilderCallback* pCallback = NULL);
		CUIMarkup* GetXml();

		CUIControl* Create(STRINGorID xml, LPCTSTR type = NULL, IUIBuilderCallback* pCallback = NULL, CUIManager* pManager = NULL, CUIControl* pParent = NULL, LPCTSTR name = NULL);
		CUIControl* Create(CUIManager* pManager = NULL, CUIControl* pParent = NULL, LPCTSTR name = NULL);
		
		void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
		void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

	protected:
		CUIControl* _Parse(CUIMarkupNode* parent, CUIControl* pParent = NULL, CUIManager* pManager = NULL);

	protected:
		CUIMarkup m_xml;
		IUIBuilderCallback* m_pCallback;
		LPCTSTR m_pstrtype;
	};

} // namespace duisharp

#endif // __UIBUILDER_H__
