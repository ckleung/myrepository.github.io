// DataGrid_Demo.h : main header file for the DATAGRID_DEMO application
//
  
#if !defined(AFX_DATAGRID_DEMO_H__B49B2D4E_0963_4876_BFE1_D31B93EA1BB7__INCLUDED_)
#define AFX_DATAGRID_DEMO_H__B49B2D4E_0963_4876_BFE1_D31B93EA1BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"   // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataGrid_DemoApp:
// See DataGrid_Demo.cpp for the implementation of this class
//

class CDataGrid_DemoApp : public CWinApp
{
public:
  CDataGrid_DemoApp();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDataGrid_DemoApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL

// Implementation

  //{{AFX_MSG(CDataGrid_DemoApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAGRID_DEMO_H__B49B2D4E_0963_4876_BFE1_D31B93EA1BB7__INCLUDED_)
