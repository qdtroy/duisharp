#pragma once

#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
////

class CUIEXButton : public CUIButton
{
public:
	typedef CUIButton theBase;

	CUIEXButton()
	{
		m_bHoverOption = false;
	}

	~CUIEXButton()
	{

	}

public:
	LPCTSTR GetClass() const
	{
		return _T("UIEXButton");
	}

	LPVOID GetInterface(LPCTSTR pstrName)
	{
		if( _tcsicmp(pstrName, _T("EXButton")) == 0 ) {
			return static_cast<CUIEXButton*>(this);
		}

		return theBase::GetInterface(pstrName);
	}

	bool IsHoverOption() const
	{
		return m_bHoverOption;
	}

	void SetHoverOption(bool bOption)
	{
		m_bHoverOption = bOption;

		Invalidate();
	}

	void SetArrowImage(LPCTSTR pstrArrow)
	{
		m_sArrowImage = pstrArrow;
	}

	LPCTSTR GetArrowImage()
	{
		return m_sArrowImage;
	}

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcsicmp(pstrName, _T("hoveroption")) == 0 ) SetHoverOption(_tcsicmp(pstrValue, _T("true")) == 0);
		else if( _tcsicmp(pstrName, _T("arrowimage")) == 0 ) SetArrowImage(pstrValue);
		else theBase::SetAttribute(pstrName, pstrValue);
	}

	void DoEvent(TUIEvent& event)
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else theBase::DoEvent(event);
			return;
		}

		if(IsHoverOption() && event.Type == UIEVENT_MOUSEHOVER)
		{
			Activate();
			return;
		}

		theBase::DoEvent(event);
	}
	
	void PaintForeImage(HDC hDC)
	{
		theBase::PaintForeImage(hDC);

		if( !m_sArrowImage.IsEmpty() ) {
			if( !DrawImage(hDC, (LPCTSTR)m_sArrowImage) ) m_sArrowImage.Empty();
		}
	}

protected:
	bool m_bOption;
	bool m_bHoverOption;
	CStdString m_sArrowImage;
};

class CUIQQList : public CUIList
{
public:
	struct NodeData
	{
		int id;
		int _level;
		bool _expand;
		CStdString _text;
		CUIListItem* _pListItem;
	};

	class Node
	{
		typedef std::vector <Node*>	Children;
		Children	_children;
		Node*		_parent;
		NodeData    _data;

	private:
		void set_parent(Node* parent) { _parent = parent; }

	public:
		Node() : _parent (NULL) {}
		explicit Node(NodeData t) : _data (t), _parent (NULL) {}
		Node(NodeData t, Node* parent)	: _data (t), _parent (parent) {}
		~Node() 
		{
			for (int i = 0; i < num_children(); i++)
				delete _children[i]; 
		}
		NodeData& data() { return _data; }	
		int num_children() const { return _children.size(); }
		Node* child(int i)	{ return _children[i]; }
		Node* parent() { return ( _parent);	}
		bool has_children() const {	return num_children() > 0; }
		void add_child(Node* child) 
		{
			child->set_parent(this); 
			_children.push_back(child); 
		}
		void remove_child(Node* child)
		{
			Children::iterator iter = _children.begin();
			for( ; iter < _children.end(); ++iter )
			{
				if( *iter == child ) 
				{
					_children.erase(iter);
					return;
				}
			}
		}
		Node* get_last_child()
		{
			if( has_children() )
			{
				return child(num_children() - 1)->get_last_child();
			}
			else return this;
		}
	};	

	CUIQQList() : _root(NULL), m_dwDelayDeltaY(0), m_dwDelayNum(0), m_dwDelayLeft(0)
	{
		SetItemShowHtml(true);

		_root = new Node;
		_root->data()._level = -1;
		_root->data()._expand = true;
		_root->data()._pListItem = NULL;
	}

	~CUIQQList() { if(_root) delete _root; }

	bool Add(CUIControl* pControl)
	{
		if( !pControl ) return false;
		if( _tcscmp(pControl->GetClass(), _T("ListLabelElementUI")) != 0 ) return false;
		return CUIList::Add(pControl);
	}

	bool AddAt(CUIControl* pControl, int iIndex)
	{
		if( !pControl ) return false;
		if( _tcscmp(pControl->GetClass(), _T("ListLabelElementUI")) != 0 ) return false;
		return CUIList::AddAt(pControl, iIndex);
	}

	bool Remove(CUIControl* pControl)
	{
		if( !pControl ) return false;
		if( _tcscmp(pControl->GetClass(), _T("ListLabelElementUI")) != 0 ) return false;

		if (reinterpret_cast<Node*>(static_cast<CUIListItem*>(pControl->GetInterface(_T("ListLabelElement")))->GetTag()) == NULL)
			return CUIList::Remove(pControl);
		else
			return RemoveNode(reinterpret_cast<Node*>(static_cast<CUIListItem*>(pControl->GetInterface(_T("ListLabelElement")))->GetTag()));
	}

	bool RemoveAt(int iIndex)
	{
		CUIControl* pControl = GetItemAt(iIndex);
		if( !pControl ) return false;
		if( _tcscmp(pControl->GetClass(), _T("ListLabelElementUI")) != 0 ) return false;

		if (reinterpret_cast<Node*>(static_cast<CUIListItem*>(pControl->GetInterface(_T("ListLabelElement")))->GetTag()) == NULL)
			return CUIList::RemoveAt(iIndex);
		else
			return RemoveNode(reinterpret_cast<Node*>(static_cast<CUIListItem*>(pControl->GetInterface(_T("ListLabelElement")))->GetTag()));
	}

	void RemoveAll()
	{
		CUIList::RemoveAll();
		for (int i = 0; i < _root->num_children(); ++i)
		{
			Node* child = _root->child(i);
			RemoveNode(child);
		}
		delete _root;
		_root = new Node;
		_root->data()._level = -1;
		_root->data()._expand = true;
		_root->data()._pListItem = NULL;
	}

	Node* GetRoot() { return _root; }

	Node* AddNode(LPCTSTR text, int id, Node* parent = NULL)
	{
		bool bFirst = parent ? false : true;
		if( !parent ) parent = _root;

		CUIListItem* pListItem = new CUIListItem;
		pListItem->SetName(_T("listitem"));
		if(!bFirst) {
			pListItem->SetFixedHeight(56);
		}
		else {
			pListItem->SetFixedHeight(32);
		}
		Node* node = new Node;
		node->data().id = id;
		node->data()._level = parent->data()._level + 1;
		if( node->data()._level == 0 ) node->data()._expand = true;
		else node->data()._expand = false;
		node->data()._text = text;
		node->data()._pListItem = pListItem;

		if( parent != _root ) {
			if( !(parent->data()._expand && parent->data()._pListItem->IsVisible()) )
				pListItem->SetInternVisible(false);
		}

		CStdString html_text;
		html_text += _T("<x 6>");
		if( node->data()._level < 1 ) {
			if( node->data()._expand ) html_text += _T("<a><i tree_expand.png 2 1></a>");
			else html_text += _T("<a><i tree_expand.png 2 0></a>");
		}
		html_text += node->data()._text;
		pListItem->SetText(html_text);
		pListItem->SetTag((UINT_PTR)node);

		int index = 0;
		if( parent->has_children() ) {
			Node* prev = parent->get_last_child();
			index = prev->data()._pListItem->GetIndex() + 1;
		}
		else {
			if( parent == _root ) index = 0;
			else index = parent->data()._pListItem->GetIndex() + 1;
		}
		if( !CUIList::AddAt(pListItem, index) ) {
			delete pListItem;
			delete node;
			node = NULL;
		}
		parent->add_child(node);
		return node;
	}

	bool RemoveNode(Node* node)
	{
		if( !node || node == _root ) return false;
		for( int i = 0; i < node->num_children(); ++i ) {
			Node* child = node->child(i);
			RemoveNode(child);
		}
		CUIList::Remove(node->data()._pListItem);
		node->parent()->remove_child(node);
		delete node;
		return true;
	}

	void ExpandNode(Node* node, bool expand)
	{
		if( !node || node == _root ) return;

		if( node->data()._expand == expand ) return;
		node->data()._expand = expand;

		CStdString html_text;
		html_text += _T("<x 6>");
		if( node->data()._level < 1 ) {
			if( node->data()._expand ) html_text += _T("<a><i tree_expand.png 2 1></a>");
			else html_text += _T("<a><i tree_expand.png 2 0></a>");
		}
		html_text += node->data()._text;
		node->data()._pListItem->SetText(html_text);

		if( !node->data()._pListItem->IsVisible() ) return;
		if( !node->has_children() ) return;

		Node* begin = node->child(0);
		Node* end = node->get_last_child();
		int nFirst = begin->data()._pListItem->GetIndex();
		for( int i = nFirst; i <= end->data()._pListItem->GetIndex(); ++i ) {
			CUIControl* control = GetItemAt(i);
			if( _tcsicmp(control->GetName(), _T("listitem")) == 0 ) {
				Node* local_parent = ((CUIQQList::Node*)control->GetTag())->parent();
				control->SetInternVisible(local_parent->data()._expand && local_parent->data()._pListItem->IsVisible());
			}
		}

		NeedUpdate();
	}

	SIZE GetExpanderSizeX(Node* node) const
	{
		if( !node || node == _root ) return duisharp::CStdSize();
		if( node->data()._level >= 3 ) return duisharp::CStdSize();

		SIZE szExpander = {0};
		szExpander.cx = 6 + 24 * node->data()._level - 4/*适当放大一点*/;
		szExpander.cy = szExpander.cx + 16 + 8/*适当放大一点*/;
		return szExpander;
	}

private:
	Node* _root;

	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;
};

static CUIControl* CreateControlEx(LPCTSTR pstrClass)
{
	if( _tcsicmp(pstrClass, _T("EXButton")) == 0 ) return new CUIEXButton;
	else if( _tcsicmp(pstrClass, _T("QQList")) == 0 ) return new CUIQQList;

	return NULL;
}

static bool HitControlEx(LPCTSTR pstrClass)
{
	if( _tcsicmp(pstrClass, _T("UIEXButton")) == 0 ||
		_tcsicmp(pstrClass, _T("UIEXProgress")) == 0 ||
		_tcsicmp(pstrClass, _T("UIButton")) == 0 ||
		_tcsicmp(pstrClass, _T("UIText")) == 0 ||
		_tcsicmp(pstrClass, _T("UIEdit")) == 0 ||
		_tcsicmp(pstrClass, _T("UICombo")) == 0 ||
		_tcsicmp(pstrClass, _T("UICalendar")) == 0)
	{
		return true;
	}

	return false;
}

static bool HitControlEx(CUIControl* pControl)
{
	if(pControl == NULL) return false;

	return HitControlEx(pControl->GetClass());
}

#define REALCONTROL0(Type, Object) static_cast<Type*>(Object)
#define REALCONTROL(Type, Name, Object) Type* Name = static_cast<Type*>(Object)
#define UIFINDCONTROL0(Type, ObjName) REALCONTROL0(Type, m_ui.FindControl(ObjName))
#define UIFINDCONTROL(Type, Name, ObjName) REALCONTROL(Type, Name, m_ui.FindControl(ObjName))
#define TUIFINDCONTROL0(Type, ObjName) REALCONTROL0(Type, pT->m_ui.FindControl(ObjName))
#define TUIFINDCONTROL(Type, Name, ObjName) REALCONTROL(Type, Name, pT->m_ui.FindControl(ObjName))