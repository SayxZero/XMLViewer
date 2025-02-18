#pragma once
#include <afxcmn.h>
class TreeCtrlModified :
    public CTreeCtrl
{
    DECLARE_DYNCREATE(TreeCtrlModified)

public:

    TreeCtrlModified();
    ~TreeCtrlModified();

protected:
    DECLARE_MESSAGE_MAP()

    CMenu* p_popup;

protected:

    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void onDeleteTreeItem(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void onItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void onSelChanged(NMHDR* pNMHDR, LRESULT* pResult);

    // Message map functions

};

