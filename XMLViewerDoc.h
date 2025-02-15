
// XMLViewerDoc.h : interface of the CXMLViewerDoc class
//


#pragma once
#include <vector>
#include <objbase.h>  
#include <msxml6.h>

struct CItemNode
{
	CItemNode(::IXMLDOMNodePtr Node = nullptr, HTREEITEM TreeItem = nullptr)
	{
		m_Node = Node;
		m_item = TreeItem;
	}

	::IXMLDOMNodePtr m_Node;
	HTREEITEM m_item;
};

struct CItemAttribute
{
	CItemAttribute(::IXMLDOMNodePtr Attribute = nullptr, HTREEITEM TreeItem = nullptr)
	{
		m_Attribute = Attribute;
		m_item = TreeItem;
	}

	::IXMLDOMAttributePtr m_Attribute;
	HTREEITEM m_item;
};

class CXMLViewerDoc : public CDocument
{
protected: // create from serialization only
	CXMLViewerDoc() noexcept;
	DECLARE_DYNCREATE(CXMLViewerDoc)

// Attributes
public:
	::IXMLDOMDocumentPtr getXMLDoc();
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPWSTR filePath);
	virtual BOOL OnSaveDocument(LPWSTR filePath);

	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CXMLViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	::IXMLDOMDocumentPtr		m_docPtr;
	BSTR m_filepath = L"";

public:
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
};
