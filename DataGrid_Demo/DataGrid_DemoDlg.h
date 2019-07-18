// DataGrid_DemoDlg.h : header file
//

#if !defined(AFX_DATAGRID_DEMODLG_H__54F1CDE6_23DE_425E_8E73_9429CE061F2C__INCLUDED_)
#define AFX_DATAGRID_DEMODLG_H__54F1CDE6_23DE_425E_8E73_9429CE061F2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataGrid_DemoDlg dialog
#include "BtnST.h"

#include "ResizableLib\ResizableDialog.h"


#include "DataGrid.h"

#include "DataComboBox.h"

class CDataGrid_DemoDlg : public CResizableDialog
{
// Construction
public:
  CArrayStringBox m_CatArray;
  CArrayStringBox m_SupArray;


  void Requery();

  CDataGrid m_Grid;
  _ConnectionPtr  m_pConnection;

	CDatabase m_db; //database variable
	CString m_dsn;

  void SetFields();
  CDataGrid_DemoDlg(CWnd* pParent = NULL);  // standard constructor

  CDataComboBox m_cmbEmp;
//  CDataComboBox m_cmbCompany;

  CExString m_strEmpId,m_strCompanyId;
  int m_nNextEmpID;

  CButtonST m_btnEdit,m_btnDel,m_btnCopy,m_btnAdd, m_btnUp,m_btnDown,m_btnPageup,m_btnPagedown;

  // Dialog Data
  //{{AFX_DATA(CDataGrid_DemoDlg)
  enum { IDD = IDD_DATAGRID_DEMO_DIALOG };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDataGrid_DemoDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    // inside the class declaration
	afx_msg LRESULT OnGridCtrlDBClick(WPARAM wParam, LPARAM lParam);

  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  //{{AFX_MSG(CDataGrid_DemoDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnSelchangeCmbCat();
  afx_msg void OnSelchangeCmbSup();
  afx_msg void OnBtnEdit();
  afx_msg void OnBtnAd();
  afx_msg void OnBtnCopy();
  afx_msg void OnBtnDel();
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectall();
	afx_msg void OnPrintButton();
	afx_msg void OnEditFind();
	afx_msg void OnAppAbout();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnDown();
	afx_msg void OnBtnPagedown();
	afx_msg void OnBtnPageup();
	afx_msg void OnBtnUp();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAGRID_DEMODLG_H__54F1CDE6_23DE_425E_8E73_9429CE061F2C__INCLUDED_)
