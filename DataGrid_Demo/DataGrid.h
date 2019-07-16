// DataGrid.h: interface for the CDataGrid class.
//
// CDataGrid - the Grid class for access to database
// Written by Kirill Panov <cpanov@yahoo.com>
// Copyright (c) 2000-2002. All Rights Reserved.
//
// This class derived from CGridCtrl by Chris Maunder <cmaunder@mail.com>
// http://www.codeproject.com/miscctrl/gridctrl.asp
// Copyright (c) 1998-2001. All Rights Reserved.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
//////////////////////////////////////////////////////////////////////



#if !defined(AFX_DATAGRID_H__E2EE8DAA_EEBF_4DEC_A786_337350892CE7__INCLUDED_)
#define AFX_DATAGRID_H__E2EE8DAA_EEBF_4DEC_A786_337350892CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define PROGRAM_DEBUG 1

#include "GRIDCTRL_SRC\GridCtrl.h"
enum eTypeFields {FIELD_TEXT,FIELD_DATE,FIELD_NUMBER};
class CGridField
{
public:
  CString Caption;
  CString Field;
  CString Format;
  int With;
  UINT Align;
  eTypeFields Type;
  bool Find;
  CGridField()
  {
    Caption=Field="";
    Align=DT_LEFT;
    With=-1;
    Type=FIELD_TEXT;
    Find=false;
  }
};
typedef CArray <CGridField,CGridField&> CGridFields;


class CDataGrid : public CGridCtrl
{
DECLARE_DYNCREATE(CDataGrid)
public:
  void OnEditFind();
  int IsSelectRow();
  bool m_bWait;
  void RequerySource(int nRow=-1);
  virtual void SetRecordsetPos(int pos);
  virtual void Delete();
  virtual void Sort(int NumberField);
  virtual void SetValue(GV_DISPINFO *pDispInfo);
  virtual void Refresh(int nRowFocus =-1);
  virtual void SetRowFocus(int nRow);
  CDataGrid();
  virtual ~CDataGrid();
  virtual void AddNew();
  _RecordsetPtr m_pSet;

  int m_nSortField;

  void Execute(_ConnectionPtr & Con
    ,const CString& strKey=_T("")
    ,const CString& strSQLFields=_T("")
    ,const CString& strSQLFrom=_T("")
    ,const CString& strSQLWhere=_T("")
    ,const CString& strSQLOrderBy=_T(""));

  void Requery( const CString& strKey=_T("")
    ,const CString& strSQLFields=_T("")
    ,const CString& strSQLFrom=_T("")
    ,const CString& strSQLWhere=_T("")
    ,const CString& strSQLOrderBy=_T(""));

  void Execute(_ConnectionPtr & Con
    ,const CString& strKey=_T("")
    ,const CString& strSQLFields=_T("")
    ,const CString& strSQLFrom=_T("")
    ,const CString& strSQLWhere=_T("")
    ,int NumberSortField=-1
    ,bool AscSortField=true);

  void Requery( const CString& strKey=_T("")
    ,const CString& strSQLFields=_T("")
    ,const CString& strSQLFrom=_T("")
    ,const CString& strSQLWhere=_T("")
    ,int NumberSortField=-1
    ,bool AscSortField=true);


  CGridFields m_field;
protected:
  _ConnectionPtr m_pCon;
  virtual void  OnFixedRowClick(CCellID& cell);
  CString m_strSQLFields;
  CString m_strSQLFrom;
  CString m_strSQLWhere;
  CString m_strSQLOrderBy;
  CString m_strKey;

  bool m_bAscSortField;

  HCURSOR m_hCursorWait;

protected:
  // Generated message map functions
  //{{AFX_MSG(CDataGrid)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_DATAGRID_H__E2EE8DAA_EEBF_4DEC_A786_337350892CE7__INCLUDED_)
