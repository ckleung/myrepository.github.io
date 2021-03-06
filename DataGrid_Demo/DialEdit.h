#if !defined(AFX_DIALEDIT_H__118C9001_168E_11D6_9341_80AF4061CB16__INCLUDED_)
#define AFX_DIALEDIT_H__118C9001_168E_11D6_9341_80AF4061CB16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialEdit.h : header file
//
#include "BtnST.h"

#include "DataComboBox.h"
#include "DDXFields.h"

/////////////////////////////////////////////////////////////////////////////
// CDialEdit dialog

class CDialEdit : public CDialog
{
// Construction
public:
  bool m_catChange,m_supChange;
  _RecordsetPtr m_pSet;
  CDDXFields m_DDXFields;
  enum {EDIT, COPY, NEW};
  int m_operation;
  CExString m_NextEmpID;

  CDataComboBox m_cmbEmp;
  CDataComboBox m_cmbCompany;

  CExString m_empId,m_compId;

  CDialEdit(CWnd* pParent = NULL);   // standard constructor

  CButtonST m_btnSave,m_btnCancel;
// Dialog Data
  //{{AFX_DATA(CDialEdit)
  enum { IDD = IDD_DIAL_EDIT };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDialEdit)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CDialEdit)
  virtual BOOL OnInitDialog();
  afx_msg void OnBtnSave();
  afx_msg void OnSelchangeCmbSup();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALEDIT_H__118C9001_168E_11D6_9341_80AF4061CB16__INCLUDED_)
