
// XMLViewerDoc.cpp : implementation of the CXMLViewerDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "XMLViewer.h"
#include "MainFrm.h"
#include <string>

#endif

#include "XMLViewerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
#include <locale.h>

// CXMLViewerDoc

IMPLEMENT_DYNCREATE(CXMLViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CXMLViewerDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CXMLViewerDoc::OnFileSave)
//	ON_COMMAND(ID_FILE_OPEN, &CXMLViewerDoc::OnFileOpen)
ON_COMMAND(ID_FILE_SAVE_AS, &CXMLViewerDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CXMLViewerDoc construction/destruction

CXMLViewerDoc::CXMLViewerDoc() noexcept
{
	// TODO: add one-time construction code here

}

::IXMLDOMDocumentPtr CXMLViewerDoc::getXMLDoc()
{
	return m_docPtr;
}

CXMLViewerDoc::~CXMLViewerDoc()
{
}

BOOL CXMLViewerDoc::OnNewDocument()
{
	BOOL result = CDocument::OnNewDocument();
	if (result)
	{
		static CLSID CLSID_DOMDocument60 = { 0x88d96a05, 0xf192, 0x11d4, { 0xa6, 0x5f, 0x00, 0x40, 0x96, 0x32, 0x51, 0xe5 } };
		HRESULT hr = CoCreateInstance(CLSID_DOMDocument60, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**) &m_docPtr);
		if (SUCCEEDED(hr))
		{
			IXMLDOMProcessingInstructionPtr procInstructionPtr;
			hr = m_docPtr->createProcessingInstruction(TEXT("xml"), TEXT("version=\"1.0\" encoding=\"utf-8\" standalone=\"no\""), &procInstructionPtr);
			if (SUCCEEDED(hr))
			{
				VARIANT vt = { VT_NULL, 0 };
				m_docPtr->insertBefore(procInstructionPtr, vt, NULL);
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXMLViewerDoc::OnOpenDocument(LPWSTR filePath)
{

	VARIANT_BOOL varBool;

	HRESULT hr = m_docPtr.CreateInstance("Msxml2.DOMDocument.6.0");

	if (SUCCEEDED(hr))
	{
		hr = m_docPtr->load(_variant_t(filePath), &varBool);
		if (SUCCEEDED(hr) && varBool) {
			SetModifiedFlag(TRUE);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CXMLViewerDoc::OnSaveDocument(LPWSTR filePath)
{
	if (m_docPtr != nullptr)
	{
		HRESULT hr = m_docPtr->save(_variant_t(filePath));
		if (FAILED(hr)) {
			return FALSE;
		}
		SetModifiedFlag(FALSE);
	}
	
	return TRUE;
}

// LoadDOM.cpp : Defines the entry point for the console application.

// CXMLViewerDoc serialization

void CXMLViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//CT2A filePath(ar.m_strFileName);
		//const char* path = filePath.m_psz;
		//size_t cSize = strlen(filePath.m_psz) + 1;
		//size_t convertedChars = 0;
		//wchar_t* wc = new wchar_t[cSize];
		//mbstowcs_s(&convertedChars, wc, cSize, path, _TRUNCATE);
		//OnSaveDocument(wc);
		//wchar_t* data = new wchar_t[65536];
		//VARIANT_BOOL isSuccessful;
		//m_docPtr->loadXML(data, &isSuccessful);
		//if (isSuccessful) {
		//	ar << data;
		//}
	}
	else
	{
		// TODO: add loading code here
		CT2A filePath(ar.m_strFileName);
		const char *path = filePath.m_psz;
		size_t cSize = strlen(filePath.m_psz) + 1;
		size_t convertedChars = 0;
		wchar_t* wc = new wchar_t[cSize];
		setlocale(LC_ALL, "ru-RU");
		mbstowcs_s(&convertedChars, wc, cSize, path, _TRUNCATE);
		m_filepath = wc;
		OnOpenDocument(wc);
	}
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CXMLViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CXMLViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

BOOL CXMLViewerDoc::OnNewDocument(LP)
{
	return 0;
}

BOOL CXMLViewerDoc::OnNewDocument(LPCSTR filePath)
{
	return 0;
}

void CXMLViewerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}





#endif // SHARED_HANDLERS

// CXMLViewerDoc diagnostics

#ifdef _DEBUG
void CXMLViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXMLViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CXMLViewerDoc commands


void CXMLViewerDoc::OnFileSave()
{
	// TODO: Add your command handler code here
	if (wcslen(m_filepath))
	{
		OnSaveDocument(m_filepath);
	}
	else
	{
		OnFileSaveAs();
	}
	
}


void CXMLViewerDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog fd(true);
	fd.m_ofn.Flags |= OFN_FILEMUSTEXIST;
	fd.m_ofn.lpstrTitle = L"Открыть";
	fd.m_ofn.lpstrFilter = L"Все файлы(*.*)\0*.*";
	fd.m_ofn.lpstrInitialDir = NULL;
	if (fd.DoModal() == IDCANCEL)
		return;

	m_filepath = fd.m_ofn.lpstrFile;
	OnOpenDocument(m_filepath);
}


void CXMLViewerDoc::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	CFileDialog fd(false);
	fd.m_ofn.lpstrTitle = L"Сохранить как...";
	fd.m_ofn.lpstrFilter = L"Все файлы(*.*)\0*.*";
	fd.m_ofn.lpstrInitialDir = NULL;
	if (fd.DoModal() == IDCANCEL)
		return;

	m_filepath = fd.m_ofn.lpstrFile;
	OnSaveDocument(m_filepath);

	std::wstring wpath;
	wpath.assign(m_filepath);
	wpath = wpath.substr(wpath.find_last_of(L"/\\") + 1);

	CMainFrame* mainFrm = (CMainFrame*)AfxGetMainWnd();
	mainFrm->SetWindowTextW(wpath.c_str());
}
