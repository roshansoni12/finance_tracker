// FinancialTrackerView.cpp : implementation of the CFinancialTrackerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FinancialTracker.h"
#endif

#include "FinancialTrackerDoc.h"
#include "FinancialTrackerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFinancialTrackerView

IMPLEMENT_DYNCREATE(CFinancialTrackerView, CView)

BEGIN_MESSAGE_MAP(CFinancialTrackerView, CView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFinancialTrackerView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_SUBMIT_BTN, &CFinancialTrackerView::OnSubmitButtonClicked)
END_MESSAGE_MAP()

// CFinancialTrackerView construction/destruction

CFinancialTrackerView::CFinancialTrackerView() noexcept
{
    // TODO: add construction code here
}

CFinancialTrackerView::~CFinancialTrackerView()
{
}

BOOL CFinancialTrackerView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

void CFinancialTrackerView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // Create and position the text entry box
    m_TextEntryBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(10, 10, 210, 30), this, 1);

    // Create and position the submit button
    m_SubmitButton.Create(_T("Submit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(220, 10, 320, 30), this, 2);
    m_SubmitButton.SetFont(GetParent()->GetFont());
    m_SubmitButton.SetDlgCtrlID(IDC_SUBMIT_BTN);
    m_SubmitButton.EnableWindow(TRUE);

    // Create and position the large text entry box
    m_LargeTextEntryBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL, CRect(10, 50, 600, 400), this, 3);
}

// CFinancialTrackerView drawing

void CFinancialTrackerView::OnDraw(CDC* /*pDC*/)
{
    CFinancialTrackerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}

// CFinancialTrackerView printing

void CFinancialTrackerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    CPrintPreviewState* pState = new CPrintPreviewState;
    if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this, RUNTIME_CLASS(CPreviewView), pState))
    {
        // In case of failure, delete the CPrintPreviewState object
        delete pState;
    }
#endif
}

BOOL CFinancialTrackerView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CFinancialTrackerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CFinancialTrackerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void CFinancialTrackerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CFinancialTrackerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CFinancialTrackerView::OnSubmitButtonClicked()
{
    // Get text from the small text entry box
    CString text;
    m_TextEntryBox.GetWindowText(text);

    // Add text to the large text entry box
    int length = m_LargeTextEntryBox.GetWindowTextLength();
    m_LargeTextEntryBox.SetSel(length, length);
    m_LargeTextEntryBox.ReplaceSel(text + _T("\r\n"));

    // Clear the small text entry box
    m_TextEntryBox.SetWindowText(_T(""));
}

// CFinancialTrackerView diagnostics

#ifdef _DEBUG
void CFinancialTrackerView::AssertValid() const
{
    CView::AssertValid();
}

void CFinancialTrackerView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CFinancialTrackerDoc* CFinancialTrackerView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinancialTrackerDoc)));
    return (CFinancialTrackerDoc*)m_pDocument;
}
#endif //_DEBUG

// CFinancialTrackerView message handlers

