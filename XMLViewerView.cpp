
// XMLViewerView.cpp : implementation of the CXMLViewerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "XMLViewer.h"
#endif

#include "XMLViewerDoc.h"
#include "XMLViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT CXMLViewerView::m_TreeCtrlID = 11111;

// CXMLViewerView

IMPLEMENT_DYNCREATE(CXMLViewerView, CView)

BEGIN_MESSAGE_MAP(CXMLViewerView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()

	//ON_NOTIFY(TVN_DELETEITEM, CXMLViewerView::m_TreeCtrlID, &CXMLViewerView::onDeleteTreeItem)
	//ON_NOTIFY(TVN_ITEMEXPANDING, CXMLViewerView::m_TreeCtrlID, &CXMLViewerView::onItemexpanding)
	//ON_NOTIFY(TVN_SELCHANGED, CXMLViewerView::m_TreeCtrlID, &CXMLViewerView::onSelChanged)
END_MESSAGE_MAP()

// CXMLViewerView construction/destruction

CXMLViewerView::CXMLViewerView() noexcept
{
	// TODO: add construction code here
	p_popup = new CMenu;
	p_popup->LoadMenuW(IDR_MENU1);
}

CXMLViewerView::~CXMLViewerView()
{
	if (p_popup)
	{
		p_popup->DestroyMenu(); // Удаляем новый ресурс меню
		delete p_popup;
	}
}

BOOL CXMLViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs



	return CView::PreCreateWindow(cs);
}

void CXMLViewerView::OnUpdateTree()
{
	//if (!isTreeUpToDate)
	//{

	//	CRect rectClient;
	//	GetClientRect(rectClient);

	//	m_treeCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	//	//isTreeUpToDate = true;

	//}
	
}

void CXMLViewerView::expandTreeItem(HTREEITEM parent, const::IXMLDOMNodeListPtr& childPtr)
{
	LockWindowUpdate();

	long nodeCount = 0;
	::IXMLDOMNodePtr nodePtr;

	HRESULT hr = childPtr->get_length(&nodeCount);

	if (SUCCEEDED(hr) && nodeCount > 0)
	{
		long firstIndex;
		parent == NULL ? firstIndex = 1 : firstIndex = 0;
		for (long i = firstIndex; i < nodeCount; i++)
		{
			hr = childPtr->get_item(i, &nodePtr);
			{
				if (SUCCEEDED(hr) && nodePtr)
				{
					CItemNode* Item = new CItemNode(nodePtr);
					BSTR nodeName;
					::IXMLDOMNamedNodeMapPtr nodeMapPtr;
					if (SUCCEEDED(hr))
					{
						hr = Item->m_Node->get_nodeName(&nodeName);
						hr = Item->m_Node->get_attributes(&nodeMapPtr);
						::IXMLDOMNodePtr attributePtr;
						if (SUCCEEDED(hr))
						{
							long attrLength;
							nodeMapPtr->get_length(&attrLength);
							hr = nodeMapPtr->get_item(0, &attributePtr);
							if (SUCCEEDED(hr) /*&& attributePtr*/)
							{
								if (attrLength) 
								{
									VARIANT var = VARIANT();
									hr = attributePtr->get_nodeValue(&var);
									if (SUCCEEDED(hr))
									{
										if (wcslen(var.bstrVal) != 0)
										{
											insertTreeItem(Item, parent, var.bstrVal);
										}
										else
										{
											insertTreeItem(Item, parent, nodeName);
										}
									}
								}
								else
								{
									insertTreeItem(Item, parent, nodeName);
								}
								
								::IXMLDOMNodeListPtr childrenPtr;
								hr = Item->m_Node->get_childNodes(&childrenPtr);
								if (SUCCEEDED(hr) && childrenPtr)
								{
									expandTreeItem(Item->m_item, childrenPtr);
								}
							}
						}
					}
				}
			}
		}
	}

	UnlockWindowUpdate();
}

// CXMLViewerView drawing

void CXMLViewerView::OnDraw(CDC* /*pDC*/)
{
	CXMLViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

//	OnUpdateTree();
	// TODO: add draw code for native data here
}


// CXMLViewerView diagnostics

#ifdef _DEBUG
void CXMLViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CXMLViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXMLViewerDoc* CXMLViewerView::GetDocument() const // non-debug version is inline
{

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXMLViewerDoc)));
	return (CXMLViewerDoc*)m_pDocument;
}
#endif //_DEBUG


void CXMLViewerView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	m_treeCtrl.DeleteAllItems();

	/*CRect rectClient;
	GetClientRect(rectClient);

	m_treeCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);*/

	::IXMLDOMDocumentPtr documentPtr;
	::IXMLDOMNodeListPtr childrenPtr;
	CXMLViewerDoc* documentObjectPtr = GetDocument();

	if (documentObjectPtr)
	{
		documentPtr = documentObjectPtr->getXMLDoc();
		if (documentPtr)
		{
			HRESULT hr = documentPtr->get_childNodes(&childrenPtr);
			if (SUCCEEDED(hr) && childrenPtr)
			{
				expandTreeItem(NULL, childrenPtr);
			}
		}
	}
}

int CXMLViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient;
	GetClientRect(rectClient);

	m_treeCtrl.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD |
		TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES |
		TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS,
		rectClient, this, m_TreeCtrlID);

	return 0;
}

void CXMLViewerView::onDeleteTreeItem(NMHDR* pNMHDR, LRESULT* pResult)
{
}

void CXMLViewerView::onItemexpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
}

void CXMLViewerView::onSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
}

void CXMLViewerView::OnSize(UINT nType, int cx, int cy)
{
	CRect rectClient;
	GetClientRect(rectClient);

	m_treeCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

// CXMLViewerView message handlers


void CXMLViewerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	ClientToScreen(&point);

	CMenu* psub = p_popup->GetSubMenu(0);
	if (psub) // Если такое подменю существует
	{
		// Отобразить его в том месте, где щелкнули правой кнопкой мыши
		psub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	m_treeCtrl.GetSelectedItem();

	Invalidate(NULL);

	CView::OnRButtonDown(nFlags, point);
}

BOOL CXMLViewerView::insertTreeItem(CItemNode* itemnode, HTREEITEM parent, BSTR text)
{
	TVINSERTSTRUCT insertStruct = { '\0' };
	insertStruct.hParent = parent == NULL ? TVI_ROOT : parent;
	insertStruct.itemex.mask = TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM;
	insertStruct.itemex.pszText = text;
	insertStruct.itemex.lParam = LPARAM(itemnode);
	itemnode->m_item = m_treeCtrl.InsertItem(&insertStruct);
	if (itemnode->m_item)
	{
		TVITEM tvItem = { '\0' };
		tvItem.mask = TVIF_CHILDREN;
		tvItem.cChildren = 1;
		tvItem.hItem = parent;

		m_treeCtrl.SetItem(&tvItem);
		return 0;
	}
	else
	{
		return -1;
	}
}
