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
    ON_NOTIFY(NM_RCLICK, 4, &CFinancialTrackerView::OnTransactionsListRightClick)
    ON_COMMAND(IDC_EDIT_ITEM, &CFinancialTrackerView::OnEditItem)
    ON_COMMAND(IDC_DELETE_ITEM, &CFinancialTrackerView::OnDeleteItem)
    ON_CBN_SELCHANGE(IDC_FILTER_COMBOBOX, &CFinancialTrackerView::OnFilterSelectionChanged)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_START_DATE_PICKER, &CFinancialTrackerView::OnStartDateChanged)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_END_DATE_PICKER, &CFinancialTrackerView::OnEndDateChanged)
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

    // Create and position the transactions list control
    m_TransactionsListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, CRect(10, 50, 600, 400), this, 4);
    m_TransactionsListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_TransactionsListCtrl.InsertColumn(0, _T("Date"), LVCFMT_LEFT, 100);
    m_TransactionsListCtrl.InsertColumn(1, _T("Amount"), LVCFMT_RIGHT, 100);
    m_TransactionsListCtrl.InsertColumn(2, _T("Description"), LVCFMT_LEFT, 390);

    // Create and position the filter combo box
    m_FilterComboBox.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, CRect(10, 410, 210, 430), this, IDC_FILTER_COMBOBOX);
    m_FilterComboBox.AddString(_T("All Transactions"));
    m_FilterComboBox.AddString(_T("Today"));
    m_FilterComboBox.AddString(_T("This Week"));
    m_FilterComboBox.AddString(_T("This Month"));
    m_FilterComboBox.AddString(_T("This Year"));
    m_FilterComboBox.AddString(_T("Custom Range"));
    m_FilterComboBox.SetCurSel(0);

    // Create and position the start date picker
    m_StartDatePicker.Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, CRect(220, 410, 330, 430), this, IDC_START_DATE_PICKER);
    m_StartDatePicker.EnableWindow(FALSE);

    // Create and position the end date picker
    m_EndDatePicker.Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, CRect(340, 410, 450, 430), this, IDC_END_DATE_PICKER);
    m_EndDatePicker.EnableWindow(FALSE);
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

    // Get the current date
    CTime currentTime = CTime::GetCurrentTime();
    CString date = currentTime.Format(_T("%Y-%m-%d"));

    // Add the new transaction to the transactions list control
    int newRow = m_TransactionsListCtrl.GetItemCount();
    m_TransactionsListCtrl.InsertItem(newRow, date);
    m_TransactionsListCtrl.SetItemText(newRow, 1, value);
    m_TransactionsListCtrl.SetItemText(newRow, 2, description);

    // Clear the description and value entry boxes
    m_DescriptionEntryBox.SetWindowText(_T(""));
    m_ValueEntryBox.SetWindowText(_T(""));
}


void CFinancialTrackerView::OnTransactionsListRightClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    if (pNMIA->iItem != -1)
    {
        CMenu contextMenu;
        contextMenu.CreatePopupMenu();
        contextMenu.AppendMenu(MF_STRING, IDC_EDIT_ITEM, _T("Edit"));
        contextMenu.AppendMenu(MF_STRING, IDC_DELETE_ITEM, _T("Delete"));

        CPoint cursorPosition;
        GetCursorPos(&cursorPosition);

        contextMenu.TrackPopupMenu(TPM_LEFTALIGN, cursorPosition.x, cursorPosition.y, this);
    }

    *pResult = 0;
}

void CFinancialTrackerView::OnEditItem()
{
    int selectedItem = m_TransactionsListCtrl.GetNextItem(-1, LVNI_SELECTED);
    if (selectedItem != -1)
    {
        CString amount = m_TransactionsListCtrl.GetItemText(selectedItem, 1);
        CString description = m_TransactionsListCtrl.GetItemText(selectedItem, 2);

        m_ValueEntryBox.SetWindowText(amount);
        m_DescriptionEntryBox.SetWindowText(description);

        // Delete the selected item so that it can be replaced by an updated one
        m_TransactionsListCtrl.DeleteItem(selectedItem);
    }
}

void CFinancialTrackerView::OnDeleteItem()
{
    int selectedItem = m_TransactionsListCtrl.GetNextItem(-1, LVNI_SELECTED);
    if (selectedItem != -1)
    {
        m_TransactionsListCtrl.DeleteItem(selectedItem);
    }
}

void CFinancialTrackerView::OnFilterSelectionChanged()
{
    int filterIndex = m_FilterComboBox.GetCurSel();
    bool isCustomRange = (filterIndex == 5);

    m_StartDatePicker.EnableWindow(isCustomRange);
    m_EndDatePicker.EnableWindow(isCustomRange);

    ApplyFilter();
}

void CFinancialTrackerView::OnStartDateChanged(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    ApplyFilter();
    *pResult = 0;
}

void CFinancialTrackerView::OnEndDateChanged(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    ApplyFilter();
    *pResult = 0;
}

int GetDaysInMonth(int year, int month)
{
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Check for leap year
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        return 29;
    }

    return daysInMonth[month - 1];
}

void CFinancialTrackerView::ApplyFilter()
{
    int filterIndex = m_FilterComboBox.GetCurSel();
    COleDateTime currentDate = COleDateTime::GetCurrentTime();
    COleDateTime startDate, endDate;
    int daysInMonth;

    switch (filterIndex)
    {
    case 0: // All Transactions
        ShowAllTransactions();
        break;
    case 1: // Today
        startDate = currentDate;
        endDate = currentDate;
        break;
    case 2: // This Week
        startDate = currentDate - COleDateTimeSpan(static_cast<int>(currentDate.GetDayOfWeek()) - 1, 0, 0, 0);
        endDate = startDate + COleDateTimeSpan(6, 23, 59, 59);
        break;
    case 3: // This Month
        startDate = COleDateTime(currentDate.GetYear(), currentDate.GetMonth(), 1, 0, 0, 0);
        daysInMonth = GetDaysInMonth(startDate.GetYear(), startDate.GetMonth());
        endDate = COleDateTime(currentDate.GetYear(), currentDate.GetMonth(), daysInMonth, 23, 59, 59);
        break;
    case 4: // This Year
        startDate = COleDateTime(currentDate.GetYear(), 1, 1, 0, 0, 0);
        endDate = COleDateTime(currentDate.GetYear(), 12, 31, 23, 59, 59);
        break;
    case 5: // Custom Range
        m_StartDatePicker.GetTime(startDate);
        m_EndDatePicker.GetTime(endDate);
        break;
    }

    if (filterIndex > 0 && filterIndex < 6)
    {
        ShowTransactionsInRange(startDate, endDate);
    }
}


void CFinancialTrackerView::ShowAllTransactions()
{
    for (int i = 0; i < m_TransactionsListCtrl.GetItemCount(); ++i)
    {
        m_TransactionsListCtrl.SetItemState(i, LVIS_CUT, LVIS_CUT);
    }
}

void CFinancialTrackerView::ShowTransactionsInRange(const COleDateTime& startDate, const COleDateTime& endDate)
{
    for (int i = 0; i < m_TransactionsListCtrl.GetItemCount(); ++i)
    {
        CString dateStr = m_TransactionsListCtrl.GetItemText(i, 0);
        COleDateTime date;
        date.ParseDateTime(dateStr);

        if (date >= startDate && date <= endDate)
        {
            m_TransactionsListCtrl.SetItemState(i, LVIS_CUT, LVIS_CUT);
        }
        else
        {
            m_TransactionsListCtrl.SetItemState(i, 0, LVIS_CUT);
        }
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
