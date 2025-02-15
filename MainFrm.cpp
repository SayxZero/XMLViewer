
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "XMLViewer.h"
#include "EditAttributesDialog.h"
#include "XMLViewerView.h"
#include "XMLViewerDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_EDIT, &CMainFrame::OnEditTreeItem)
	ON_COMMAND(ID_EDIT_CUT, &CMainFrame::OnCutTreeItem)
	ON_COMMAND(ID_EDIT_COPY, &CMainFrame::OnCopyTreeItem)
	ON_COMMAND(ID_EDIT_PASTE, &CMainFrame::OnPasteTreeItem)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnEditTreeItem()
{
	// TODO: Add your command handler code here
	CView* view = GetActiveView();

	CXMLViewerView* xmlView = static_cast<CXMLViewerView*>(view);

	if (xmlView)
	{
		HTREEITEM item = xmlView->m_treeCtrl.GetSelectedItem();
		if (item)
		{
			CItemNode* itemNode = (CItemNode*)xmlView->m_treeCtrl.GetItemData(item);
			if (itemNode)
			{
				EditAttributesDialog* dlg = new EditAttributesDialog(this, xmlView->GetDocument(), itemNode->m_Node);
				dlg->DoModal();
			}
		}
	}
}


void CMainFrame::OnCutTreeItem()
{
	// TODO: Add your command handler code here

}


void CMainFrame::OnCopyTreeItem()
{
	// TODO: Add your command handler code here

}


void CMainFrame::OnPasteTreeItem()
{
	// TODO: Add your command handler code here

}
