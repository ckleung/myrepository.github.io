// DialFind.cpp : implementation file
//

#include "stdafx.h"
#include "DataGrid_Demo.h"
#include "DialFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialFind dialog


CDialFind::CDialFind(CWnd* pParent /*=NULL*/)
	: CDialog(CDialFind::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialFind)
	m_nField = 0;
	m_strFind = _T("");
	//}}AFX_DATA_INIT
}


void CDialFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialFind)
	DDX_Control(pDX, IDC_COMBO_FIND, m_cmbFind);
	DDX_CBIndex(pDX, IDC_COMBO_FIND, m_nField);
	DDX_Text(pDX, IDC_FIND, m_strFind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialFind, CDialog)
	//{{AFX_MSG_MAP(CDialFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialFind message handlers

BOOL CDialFind::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_arFind.GetSize()>0)
	{
    //m_comboFind.
		for(int i=0;i<m_arFind.GetSize();i++)
				m_cmbFind.AddString(m_arFind.GetAt(i).m_name);

		m_cmbFind.SetCurSel(1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
