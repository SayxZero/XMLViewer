#include "pch.h"
#include "framework.h"
#include "TreeCtrlModified.h"

#ifndef SHARED_HANDLERS
#include "XMLViewer.h"
#include "MainFrm.h"
#endif

IMPLEMENT_DYNCREATE(TreeCtrlModified, CTreeCtrl)

BEGIN_MESSAGE_MAP(TreeCtrlModified, CTreeCtrl)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

TreeCtrlModified::TreeCtrlModified() : CTreeCtrl()
{
	p_popup = new CMenu;
	p_popup->LoadMenuW(IDR_MENU1);
}

TreeCtrlModified::~TreeCtrlModified()
{
	if (p_popup)
	{
		p_popup->DestroyMenu(); // Удаляем новый ресурс меню
		delete p_popup;
	}
}

void TreeCtrlModified::OnRButtonDown(UINT /*nFlags*/, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	ClientToScreen(&point);

	CMenu* psub = p_popup->GetSubMenu(0);
	if (psub) // Если такое подменю существует
	{
		// Отобразить его в том месте, где щелкнули правой кнопкой мыши
		psub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	//m_treeCtrl.GetSelectedItem();

	//Invalidate(NULL);

	//CView::OnRButtonDown(nFlags, point);
}

void TreeCtrlModified::onDeleteTreeItem(NMHDR* pNMHDR, LRESULT* pResult)
{
}

void TreeCtrlModified::onItemexpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
}

void TreeCtrlModified::onSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
}