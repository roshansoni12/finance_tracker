// FinancialTrackerView.h : interface of the CFinancialTrackerView class
//

#pragma once

class CFinancialTrackerView : public CView
{
protected: // create from serialization only
    CFinancialTrackerView() noexcept;
    DECLARE_DYNCREATE(CFinancialTrackerView)

        // Attributes
public:
    CFinancialTrackerDoc* GetDocument() const;


    // Operations
public:

    // Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    // Controls
    CEdit m_DescriptionEntryBox;
    CEdit m_ValueEntryBox;
    CButton m_SubmitButton;
    CListCtrl m_TransactionsListCtrl;
    CComboBox m_FilterComboBox;
    CDateTimeCtrl m_StartDatePicker;
    CDateTimeCtrl m_EndDatePicker;

    // Implementation
public:
    virtual ~CFinancialTrackerView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnSubmitButtonClicked();
    afx_msg void OnInitialUpdate();
    afx_msg void OnTransactionsListRightClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEditItem();
    afx_msg void OnDeleteItem();
    afx_msg void OnFilterSelectionChanged();
    afx_msg void OnStartDateChanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEndDateChanged(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    void ApplyFilter();
    void ShowAllTransactions();
    void ShowTransactionsInRange(const COleDateTime& startDate, const COleDateTime& endDate);
};

#ifndef _DEBUG  // debug version in FinancialTrackerView.cpp
inline CFinancialTrackerDoc* CFinancialTrackerView::GetDocument() const
{
    return reinterpret_cast<CFinancialTrackerDoc*>(m_pDocument);
}
#endif
