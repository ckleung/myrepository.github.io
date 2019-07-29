// DataComboBox.h: interface for the CDataComboBox class.
//
// CDataComboBox class for access to database from ComboBox
// Written by Kirill Panov <cpanov@yahoo.com>
// Copyright (c) 2000-2002. All Rights Reserved.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_DATACOMBOBOX1_H__C8A4E76F_0031_4F2D_A390_716209BF8809__INCLUDED_)
#define AFX_DATACOMBOBOX1_H__C8A4E76F_0031_4F2D_A390_716209BF8809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Exstring.h"
/////////////////////////////////////////////////////////////////////////////
// CDataComboBox window
class CStrBox
{
public:
  CExString m_strField;
  CExString m_strId;
};
typedef CArray <CStrBox,CStrBox&> CArrayStrBox;

class CArrayStringBox: public CArrayStrBox
{
public:
  void Fill( _ConnectionPtr & Con
    ,const CString& strQuery
    ,const CString& strShowField
    ,const CString& strIdField);
};

class CDataComboBox : public CComboBox
{
// Construction
public:
  CDataComboBox();
  _RecordsetPtr m_pSet;
  enum {BOUND,UNBOUND};
  int m_state;
  CExString GetCurId();
  CExString GetCurFieldValue();
  bool m_bAddPosition;
  CExString m_strAddPosition;
  int GetCurPosition();
protected:
  CExString m_strQuery;
  CString m_strShowField;
  int m_nCurPosition;
  int m_nOldPosition;
  CExString m_strDefaultId;
  _CommandPtr m_pCommand;
  CArrayStringBox *m_pArStrBox;
// Attributes
public:

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDataComboBox)
  //}}AFX_VIRTUAL

// Implementation
public:
  bool IsAddPosition();
  void SetPrevPosition();
  void SetCurPosition();
  void Fill();
  void Attach(CArrayStringBox * pArStrBox,const CExString& strDefaultId="");
  virtual void Execute( _ConnectionPtr & Con,
       const CString& strQuery,
       const CString& strShowField,const int CommandType=adCmdText );

  virtual ~CDataComboBox();

  // Generated message map functions
protected:
  //{{AFX_MSG(CDataComboBox)
  afx_msg void OnSelendok();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATACOMBOBOX1_H__C8A4E76F_0031_4F2D_A390_716209BF8809__INCLUDED_)
