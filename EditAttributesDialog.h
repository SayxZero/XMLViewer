#pragma once
#include <afxwin.h>

class CXMLViewerDoc;

class EditAttributesDialog :
    public CDialog
{
    DECLARE_DYNCREATE(EditAttributesDialog)

public:

    EditAttributesDialog(CWnd* parent = NULL, CXMLViewerDoc* doc = nullptr, ::IXMLDOMNodePtr node = nullptr);

    ~EditAttributesDialog();

    void addAttribute(LPWSTR Name, LPWSTR Value);

    enum { IDD = IDD_EDITTREEITEMDIALOG };

protected:

    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

    CWnd* m_Parent;
    CXMLViewerDoc* m_Doc;
    ::IXMLDOMNodePtr m_Node;

    static const UINT m_TreeCtrlID;
    CListCtrl m_listCtrl;

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    // Generated message map functions

};

