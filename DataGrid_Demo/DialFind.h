#if !defined(AFX_DIALFIND_H__114BE63F_F9D9_47C2_AC4E_1E67EC11BED4__INCLUDED_)
#define AFX_DIALFIND_H__114BE63F_F9D9_47C2_AC4E_1E67EC11BED4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialFind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialFind dialog

#include "DataGrid.h"
#include "ExString.h"

class CFind
{
public:
	CExString m_name;
	//int m_type;
	int m_index;
	
	CFind(const CExString& strName=""
		//,int type=-1		
		,int index=-1		)
	{
		m_name=strName;
		//m_type=type;
		m_index=index;
	}
};

typedef CArray <CFind,CFind&> CFindArray;


class CDialFind : public CDialog
{
// Construction
public:
	CDialFind(CWnd* pParent = NULL);   // standard constructor
  CFindArray m_arFind;
// Dialog Data
	//{{AFX_DATA(CDialFind)
	enum { IDD = IDD_DIAL_FIND };
	CComboBox	m_cmbFind;
	int		m_nField;
	CString	m_strFind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialFind)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALFIND_H__114BE63F_F9D9_47C2_AC4E_1E67EC11BED4__INCLUDED_)
