
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
	//CEdit m_TextEntryBox; - old, name changed
	// Controls
	CEdit m_DescriptionEntryBox;
	CEdit m_ValueEntryBox;
	CButton m_SubmitButton;
	CListCtrl m_EntryList;
	CButton m_EditButton;
	CButton m_DeleteButton;

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
	afx_msg void OnEditButtonClicked();
	afx_msg void OnDeleteButtonClicked();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FinancialTrackerView.cpp
inline CFinancialTrackerDoc* CFinancialTrackerView::GetDocument() const
   { return reinterpret_cast<CFinancialTrackerDoc*>(m_pDocument); }
#endif

