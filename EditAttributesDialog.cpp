#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "XMLViewer.h"
#endif

#include "EditAttributesDialog.h"
#include "XMLViewerDoc.h"

const UINT EditAttributesDialog::m_TreeCtrlID = 11112;

IMPLEMENT_DYNCREATE(EditAttributesDialog, CDialog)

BEGIN_MESSAGE_MAP(EditAttributesDialog, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

EditAttributesDialog::EditAttributesDialog(CWnd* parent, CXMLViewerDoc* doc, ::IXMLDOMNodePtr node)
	: CDialog(IDD, parent),
	m_Parent(parent),
	m_Doc(doc),
	m_Node(node)
{
}

EditAttributesDialog::~EditAttributesDialog()
{
}

void EditAttributesDialog::addAttribute(LPWSTR Name, LPWSTR Value)
{
}

void EditAttributesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


int EditAttributesDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.bottom = rectClient.bottom - 45;

	m_listCtrl.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | LVS_REPORT,
		rectClient, this, m_TreeCtrlID);

	int nColInterval = rectClient.Width() / 4;

	m_listCtrl.InsertColumn(0, _T("Item Name"), LVCFMT_LEFT, nColInterval);
	m_listCtrl.InsertColumn(1, _T("Value"), LVCFMT_LEFT, nColInterval * 3);

	if (m_Node)
	{
		VARIANT var = VARIANT();
		::IXMLDOMNamedNodeMapPtr nodeMapPtr;
		HRESULT hr = m_Node->get_attributes(&nodeMapPtr);
		::IXMLDOMNodePtr attributePtr;
		if (SUCCEEDED(hr))
		{
			long attrLength;
			nodeMapPtr->get_length(&attrLength);
			for (long k = 0; k < attrLength; k++)
			{
				hr = nodeMapPtr->get_item(k, &attributePtr);
				if (SUCCEEDED(hr) /*&& attributePtr*/)
				{
					BSTR nodeName;
					hr = attributePtr->get_nodeName(&nodeName);
					hr = attributePtr->get_nodeValue(&var);
					if (SUCCEEDED(hr))
					{
						LVITEMW lvi;
						lvi.mask = LVIF_TEXT;
						lvi.iItem = k;
						lvi.iSubItem = 0;
						lvi.pszText = nodeName;
						m_listCtrl.InsertItem(&lvi);
						lvi.iSubItem = 1;
						lvi.pszText = var.bstrVal;
						int kkk = m_listCtrl.SetItem(&lvi);
						kkk;
					}

				}
			}
		}
	}

	return 0;
}
