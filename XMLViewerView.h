
// XMLViewerView.h : interface of the CXMLViewerView class
//

#pragma once

#include "TreeCtrlModified.h"

class TreeCtrlModified;

struct CItemNode;

class CXMLViewerView : public CView
{
protected: // create from serialization only
	CXMLViewerView() noexcept;
	DECLARE_DYNCREATE(CXMLViewerView)

// Attributes
public:
	CXMLViewerDoc* GetDocument() const;

	TreeCtrlModified m_treeCtrl;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CMenu* p_popup;
	void expandTreeItem(HTREEITEM parent, const ::IXMLDOMNodeListPtr& childPtr);

protected:

// Implementation
public:
	virtual ~CXMLViewerView();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:

//	bool isTreeUpToDate = false;
public:

private:
	static const UINT m_TreeCtrlID;
	BOOL insertTreeItem(CItemNode* itemnode, HTREEITEM parent, BSTR text);
	void destructTree(HTREEITEM Item);
};

#ifndef _DEBUG  // debug version in XMLViewerView.cpp
inline CXMLViewerDoc* CXMLViewerView::GetDocument() const
   { return reinterpret_cast<CXMLViewerDoc*>(m_pDocument); }
#endif

