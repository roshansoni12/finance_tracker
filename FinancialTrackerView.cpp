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
    ON_BN_CLICKED(4, &CFinancialTrackerView::OnEditButtonClicked)
    ON_BN_CLICKED(5, &CFinancialTrackerView::OnDeleteButtonClicked)
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

    // Create and position the description entry box
    m_DescriptionEntryBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(10, 10, 310, 30), this, 1);

    // Create and position the value entry box
    m_ValueEntryBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, CRect(320, 10, 420, 30), this, 2);

    // Create and position the submit button
    m_SubmitButton.Create(_T("Submit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(430, 10, 530, 30), this, 3);
    m_SubmitButton.SetFont(GetParent()->GetFont());
    m_SubmitButton.SetDlgCtrlID(IDC_SUBMIT_BTN);
    m_SubmitButton.EnableWindow(TRUE);

    // Create and position the edit button
    m_EditButton.Create(_T("Edit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(540, 10, 640, 30), this, 4);
    m_EditButton.SetFont(GetParent()->GetFont());
    m_EditButton.EnableWindow(TRUE);

    // Create and position the delete button
    m_DeleteButton.Create(_T("Delete"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(650, 10, 750, 30), this, 5);
    m_DeleteButton.SetFont(GetParent()->GetFont());
    m_DeleteButton.EnableWindow(TRUE);

    // Create and position the entry list
    m_EntryList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, CRect(10, 50, 800, 400), this, 6);
    m_EntryList.InsertColumn(0, _T("Description"), LVCFMT_LEFT, 350);
    m_EntryList.InsertColumn(1, _T("Value"), LVCFMT_RIGHT, 100);
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
    // Get text from the description entry box
    CString description;
    m_DescriptionEntryBox.GetWindowText(description);

    // Get value from the value entry box
    CString value;
    m_ValueEntryBox.GetWindowText(value);

    // Add a new item to the list control
    int newIndex = m_EntryList.InsertItem(m_EntryList.GetItemCount(), description);
    m_EntryList.SetItemText(newIndex, 1, value);

    // Clear the description and value entry boxes
    m_DescriptionEntryBox.SetWindowText(_T(""));
    m_ValueEntryBox.SetWindowText(_T(""));
}

void CFinancialTrackerView::OnEditButtonClicked()
{
    int selectedIndex = m_EntryList.GetNextItem(-1, LVNI_SELECTED);

    if (selectedIndex != -1)
    {
        CString description = m_EntryList.GetItemText(selectedIndex, 0);
        CString value = m_EntryList.GetItemText(selectedIndex, 1);

        m_DescriptionEntryBox.SetWindowText(description);
        m_ValueEntryBox.SetWindowText(value);

        m_EntryList.DeleteItem(selectedIndex);
    }
}

void CFinancialTrackerView::OnDeleteButtonClicked()
{
    int selectedIndex = m_EntryList.GetNextItem(-1, LVNI_SELECTED);

    if (selectedIndex != -1)
    {
        m_EntryList.DeleteItem(selectedIndex);
    }
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

