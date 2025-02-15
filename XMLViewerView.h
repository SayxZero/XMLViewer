
// XMLViewerView.h : interface of the CXMLViewerView class
//

#pragma once

struct CItemNode;

class CXMLViewerView : public CView
{
protected: // create from serialization only
	CXMLViewerView() noexcept;
	DECLARE_DYNCREATE(CXMLViewerView)

// Attributes
public:
	CXMLViewerDoc* GetDocument() const;

	CTreeCtrl m_treeCtrl;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdateTree();
	CMenu* p_popup;
	void expandTreeItem(HTREEITEM parent, const ::IXMLDOMNodeListPtr& childPtr);

protected:

// Implementation
public:
	virtual ~CXMLViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
#endif

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void onDeleteTreeItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void onItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void onSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:

//	bool isTreeUpToDate = false;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:
	static const UINT m_TreeCtrlID;
	BOOL insertTreeItem(CItemNode* itemnode, HTREEITEM parent, BSTR text);
};

#ifndef _DEBUG  // debug version in XMLViewerView.cpp
inline CXMLViewerDoc* CXMLViewerView::GetDocument() const
   { return reinterpret_cast<CXMLViewerDoc*>(m_pDocument); }
#endif

