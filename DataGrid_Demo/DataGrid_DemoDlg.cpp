// DataGrid_DemoDlg.cpp : implementation file
//
// Chris Leung - BAH July 2019

#include "stdafx.h"
#include "DataGrid_Demo.h"
#include "DataGrid_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include "HyperLink.h"
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CResizableDialog
{
public:
  CAboutDlg();

 // CHyperLink	m_eMail0,m_eMail1,m_eMail2,m_eMail3;
	//CHyperLink	m_wLink0,m_wLink1,m_wLink2,m_wLink3;

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CResizableDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CResizableDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
  //DDX_Control(pDX, IDC_MAIL0, m_eMail0);
  //DDX_Control(pDX, IDC_MAIL1, m_eMail1);
  //DDX_Control(pDX, IDC_MAIL2, m_eMail2);
  //DDX_Control(pDX, IDC_MAIL3, m_eMail3);

  //DDX_Control(pDX, IDC_WWW0,  m_wLink0);
  //DDX_Control(pDX, IDC_WWW1,  m_wLink1);
  //DDX_Control(pDX, IDC_WWW2,  m_wLink2);
  //DDX_Control(pDX, IDC_WWW3,  m_wLink3);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CResizableDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataGrid_DemoDlg dialog

CDataGrid_DemoDlg::CDataGrid_DemoDlg(CWnd* pParent /*=NULL*/)
  : CResizableDialog(CDataGrid_DemoDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDataGrid_DemoDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataGrid_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
  CResizableDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDataGrid_DemoDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
  DDX_Control(pDX, IDC_GRID, m_Grid);             // associate the grid window with a C++ object

  DDX_Control(pDX, IDC_CMB_CAT, m_cmbEmp);
//  DDX_Control(pDX, IDC_CMB_SUP, m_cmbCompany);
}

BEGIN_MESSAGE_MAP(CDataGrid_DemoDlg, CResizableDialog)
  //{{AFX_MSG_MAP(CDataGrid_DemoDlg)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_CBN_SELCHANGE(IDC_CMB_CAT, OnSelchangeCmbCat)
  ON_CBN_SELCHANGE(IDC_CMB_SUP, OnSelchangeCmbSup)
  ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
  ON_BN_CLICKED(IDC_BTN_AD, OnBtnAd)
  ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
  ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(IDC_PRINT_BUTTON, OnPrintButton)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DOWN, &CDataGrid_DemoDlg::OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_PAGEDOWN, &CDataGrid_DemoDlg::OnBtnPagedown)
	ON_BN_CLICKED(IDC_BTN_PAGEUP, &CDataGrid_DemoDlg::OnBtnPageup)
	ON_BN_CLICKED(IDC_BTN_UP, &CDataGrid_DemoDlg::OnBtnUp)
    ON_MESSAGE(NM_DBLCLK, OnGridCtrlDBClick)
END_MESSAGE_MAP()
extern void ProcessMsgs();

/////////////////////////////////////////////////////////////////////////////
// CDataGrid_DemoDlg message handlers

/**********************************************************************
*	Function:	ProcessMsgs
*
*	Created:	11/24/1998 CKL
*
*	Purpose:	This works by getting all messages for our process, then
*				discarding those that don't belong to the specified window
*				or its descendants.
*
*	Returns:	void
***********************************************************************/
void ProcessMsgs()
{

	MSG         Msg;
	DWORD       FinalTime = GetTickCount();
	DWORD		CurTime=0;
	CString str;

	/*
	** This works by getting all messages for our process, then
	** discarding those that don't belong to the specified window
	** or its descendants.
	*/

	while (::PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE|PM_NOYIELD) && CurTime < FinalTime)
	{
		::GetMessage(&Msg,NULL,0,0);  // this can yield!
		CurTime = ::GetMessageTime();
		::TranslateMessage(&Msg);
		::DispatchMessage(&Msg);
	}
	return;
}

BOOL CDataGrid_DemoDlg::OnInitDialog()
{
  CResizableDialog::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  // TODO: Add extra initialization here

  AddAnchor(IDC_GRID,TOP_LEFT, BOTTOM_RIGHT);

  AddAnchor(IDC_BTN_EDIT,BOTTOM_CENTER);
  AddAnchor(IDC_BTN_AD, BOTTOM_CENTER);
  AddAnchor(IDC_BTN_COPY, BOTTOM_CENTER);
  AddAnchor(IDC_BTN_DEL,BOTTOM_CENTER);

  AddAnchor(IDC_BTN_UP,BOTTOM_CENTER);
  AddAnchor(IDC_BTN_DOWN, BOTTOM_CENTER);
  AddAnchor(IDC_BTN_PAGEUP, BOTTOM_CENTER);
  AddAnchor(IDC_BTN_PAGEDOWN,BOTTOM_CENTER);

  m_btnEdit.SubclassDlgItem(IDC_BTN_EDIT, this);
  m_btnEdit.SetBitmaps(IDB_EDIT, RGB(255, 0, 255));
  m_btnEdit.SetFlat(FALSE);
  m_btnEdit.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnCopy.SubclassDlgItem(IDC_BTN_COPY, this);
  m_btnCopy.SetBitmaps(IDB_COPY , RGB(192, 192, 192));
  m_btnCopy.SetFlat(FALSE);
  m_btnCopy.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnDel.SubclassDlgItem(IDC_BTN_DEL, this);
  m_btnDel.SetBitmaps(IDB_DEL, RGB(255,0 , 255));
  m_btnDel.SetFlat(FALSE);
  m_btnDel.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnAdd.SubclassDlgItem(IDC_BTN_AD, this);
  m_btnAdd.SetBitmaps(IDB_ADD, RGB(192, 192, 192));
  m_btnAdd.SetFlat(FALSE);
  m_btnAdd.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnUp.SubclassDlgItem(IDC_BTN_UP, this);
//  m_btnUp.SetBitmaps(IDB_EDIT, RGB(255, 0, 255));
  m_btnUp.SetFlat(FALSE);
  m_btnUp.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnDown.SubclassDlgItem(IDC_BTN_DOWN, this);
//  m_btnDown.SetBitmaps(IDB_EDIT, RGB(255, 0, 255));
  m_btnDown.SetFlat(FALSE);
  m_btnDown.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnPageup.SubclassDlgItem(IDC_BTN_PAGEUP, this);
//  m_btnPageup.SetBitmaps(IDB_EDIT, RGB(255, 0, 255));
  m_btnPageup.SetFlat(FALSE);
  m_btnPageup.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnPagedown.SubclassDlgItem(IDC_BTN_PAGEDOWN, this);
//  m_btnPagedown.SetBitmaps(IDB_EDIT, RGB(255, 0, 255));
  m_btnPagedown.SetFlat(FALSE);
  m_btnPagedown.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_pConnection.CreateInstance(__uuidof(Connection)); //Create connection

  try
  {
    //Open connection
    //I prefer to use udl
    //m_pConnection->Open(L"File Name=C:\\Program Files\\Common Files\\System\\Ole DB\\Data Links\\nwind.udl", L"", L"", -1);
//    HRESULT hr = m_pConnection->Open(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\CACI_Laptop\\Data\\download\\Nwind.mdb", L"", L"", -1);
//    HRESULT hr = m_pConnection->Open(L"Provider=MySQLProv;Data Source=classicmodels;User Id=root;Password=catonese1!;", L"root", L"catonese1!", -1);
    HRESULT hr = m_pConnection->Open(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\CACI_Laptop\\Data\\IRSPOCDB.mdb", L"", L"", -1);

	
    //HRESULT hr = m_pConnection->Open(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\CACI_Laptop\\Data\\download\\Nwind.mdb", L"", L"", -1);
	if(SUCCEEDED(hr))
	{	
//		m_cmbEmp.m_bAddPosition=m_cmbCompany.m_bAddPosition=true;
		m_cmbEmp.m_bAddPosition=true;
//		m_cmbEmp.Execute(m_pConnection,_T("SELECT emp_id FROM employee order by emp_id"),_T("emp_id"));
//		m_cmbCompany.Execute(m_pConnection,_T("SELECT * FROM company ORDER BY company_name"),_T("company_name"));

		// set the default next emp id for employee table
		m_nNextEmpID = 0;
//		m_nNextEmpID = m_cmbEmp.GetCount();
//		m_CatArray.Fill(m_pConnection,_T("SELECT emp_id FROM employee ORDER BY emp_id"),_T("emp_id"),_T("emp_id"));//m_CatArray
		m_SupArray.Fill(m_pConnection,_T("SELECT * FROM company ORDER BY company_name"),_T("company_name"),_T("ID"));

    //m_cmbEmp.Execute(m_pConnection,_T("SELECT * FROM Categories ORDER BY CategoryName"),_T("CategoryName"));
    //m_cmbCompany.Execute(m_pConnection,_T("SELECT * FROM Suppliers ORDER BY CompanyName"),_T("CompanyName"));

    //m_CatArray.Fill(m_pConnection,_T("SELECT * FROM Categories ORDER BY CategoryName"),_T("CategoryName"),_T("CategoryID"));
    //m_SupArray.Fill(m_pConnection,_T("SELECT * FROM Suppliers ORDER BY CompanyName"),_T("CompanyName"),_T("SupplierID"));
	}
  }
  catch(_com_error *e)
  {
    CString Error = e->ErrorMessage();
    AfxMessageBox(e->ErrorMessage());
  }
  catch(...)
  {
	  AfxMessageBox(_T("connection failed"));
	  return FALSE;
  }

  SetFields();



  return TRUE;  // return TRUE  unless you set the focus to a control
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDataGrid_DemoDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CResizableDialog::OnPaint();
  }
//  ProcessMsgs();//ckl fixed painting issue
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataGrid_DemoDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}



void CDataGrid_DemoDlg::SetFields()
{
  int n;

  // set the field size here
  m_Grid.m_field.SetSize(13);

  n=0;
  //m_Grid.m_field[n].Field=_T("ProductName");
  //m_Grid.m_field[n].Caption=_T("Product");
  //m_Grid.m_field[n].With=200;
  //m_Grid.m_field[n].Find=true;


  //n=1;
  //m_Grid.m_field[n].Field=_T("QuantityPerUnit");
  //m_Grid.m_field[n].Caption=_T("Quantity Per Unit");
  //m_Grid.m_field[n].With=200;
  //m_Grid.m_field[n].Find=true;

  m_Grid.m_field[n].Field=_T("last_name");
  m_Grid.m_field[n].Caption=_T("Last Name");
  m_Grid.m_field[n].With=150;
  m_Grid.m_field[n].Find=true;


  n=1;
  m_Grid.m_field[n].Field=_T("first_name");
  m_Grid.m_field[n].Caption=_T("First Name");
  m_Grid.m_field[n].With=150;
  m_Grid.m_field[n].Find=true;

  n=2;
  m_Grid.m_field[n].Field=_T("email");
  m_Grid.m_field[n].Caption=_T("Email");
  m_Grid.m_field[n].With=250;
  m_Grid.m_field[n].Find=true;

  n=3;
  m_Grid.m_field[n].Field=_T("gender");
  m_Grid.m_field[n].Caption=_T("Gender");
  m_Grid.m_field[n].With=60;
  m_Grid.m_field[n].Find=true;

  n=4;
  m_Grid.m_field[n].Field=_T("phone_number");
  m_Grid.m_field[n].Caption=_T("Phone Number");
  m_Grid.m_field[n].With=120;
  m_Grid.m_field[n].Find=true;

  n=5;
  m_Grid.m_field[n].Field=_T("job_title");
  m_Grid.m_field[n].Caption=_T("Job Title");
  m_Grid.m_field[n].With=200;
  m_Grid.m_field[n].Find=true;

  n=6;
  m_Grid.m_field[n].Field=_T("company_name");
  m_Grid.m_field[n].Caption=_T("Company Name");
  m_Grid.m_field[n].With=115;
  m_Grid.m_field[n].Find=true;

  n=7;
  m_Grid.m_field[n].Field=_T("address");
  m_Grid.m_field[n].Caption=_T("Address");
  m_Grid.m_field[n].With=220;
  m_Grid.m_field[n].Find=true;

  n=8;
  m_Grid.m_field[n].Field=_T("city");
  m_Grid.m_field[n].Caption=_T("City");
  m_Grid.m_field[n].With=100;
  m_Grid.m_field[n].Find=true;

  n=9;
  m_Grid.m_field[n].Field=_T("state");
  m_Grid.m_field[n].Caption=_T("State");
  m_Grid.m_field[n].With=45;
  m_Grid.m_field[n].Find=true;

  n=10;
  m_Grid.m_field[n].Field=_T("zip");
  m_Grid.m_field[n].Caption=_T("Zip");
  m_Grid.m_field[n].With=50;
  m_Grid.m_field[n].Find=true;

  n=11;
  m_Grid.m_field[n].Field=_T("emp_id");
  m_Grid.m_field[n].Caption=_T("Employee ID");
  m_Grid.m_field[n].With=100;
  m_Grid.m_field[n].Find=true;

  n=12;
  m_Grid.m_field[n].Field=_T("companyid");
  m_Grid.m_field[n].Caption=_T("Company ID");
  m_Grid.m_field[n].With=100;
  m_Grid.m_field[n].Find=true;

  Requery();

//  m_Grid.Execute(m_pConnection,"ProductId"/*Primary key field */
//    ,"*"//fields in SELECT statment
//    ,"Products" //from
//    ,""         // where
//    ,0);        // order by N of the Grid column


}

BOOL CDataGrid_DemoDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  // TODO: Add your specialized code here and/or call the base class
  if (wParam == (WPARAM)m_Grid.GetDlgCtrlID())
  {
    *pResult = 1;
    GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;

	// ckl capture grid double click message
	if (pDispInfo->hdr.code == NM_DBLCLK)
	{
//		CWnd *pOwner = m_Grid.GetOwner();
//		if (pOwner && IsWindow(pOwner->m_hWnd))
		
		OnBtnEdit();
		return SendMessage(NM_DBLCLK, wParam, lParam);
	}
    m_Grid.SetValue(pDispInfo);
  }

  return CResizableDialog::OnNotify(wParam, lParam, pResult);
}

void CDataGrid_DemoDlg::OnSelchangeCmbCat()
{
  // TODO: Add your control notification handler code here
  Requery();
}

void CDataGrid_DemoDlg::OnSelchangeCmbSup()
{
  // TODO: Add your control notification handler code here
  Requery();
}

void CDataGrid_DemoDlg::Requery()
{
  CString strEmp,strComp,strWhere;

  if (!m_cmbEmp.IsAddPosition())
  {
    m_strEmpId=m_cmbEmp.m_pSet->GetCollect(L"id");
    strEmp=_T(" ID=")+m_strEmpId;
  }

  //if (!m_cmbCompany.IsAddPosition())
  //{
  //  m_strCompanyId=m_cmbCompany.m_pSet->GetCollect(L"ID");
  //  strComp=" ID="+m_strCompanyId;
  //}

  strWhere=strEmp;

  if( ( strComp.GetLength()*strWhere.GetLength() ) ==0 )
    strWhere+=strComp;
  else
    strWhere+=" AND "+strComp;

  strWhere = " employee.companyid = company.ID ";
  m_Grid.Execute(m_pConnection,_T("ID")/*Primary key field */
    ,_T("*")//fields in SELECT statment
    ,_T("employee, company") //from
    ,strWhere   // where
    ,-1);        // order by N of the Grid column - ckl not using grid sorting on display do it in where clause
  //

}

#include "DialEdit.h"

void CDataGrid_DemoDlg::OnBtnEdit()
{
  // TODO: Add your control notification handler code here
  int nRow=m_Grid.IsSelectRow();
  if(nRow==-1)
    return;

  CDialEdit dlg;

  dlg.m_pSet=m_Grid.m_pSet;

  dlg.m_empId=m_Grid.m_pSet->GetCollect(L"emp_ID") ;
  dlg.m_compId=m_Grid.m_pSet->GetCollect(L"companyID") ;
  dlg.m_cmbEmp.Attach(&m_CatArray,dlg.m_empId);
  dlg.m_cmbCompany.Attach(&m_SupArray,dlg.m_compId);

  dlg.m_operation=CDialEdit::EDIT;

  if (dlg.DoModal() == IDOK)
  {
    if( ((dlg.m_catChange)&&(!m_cmbEmp.IsAddPosition())))
//        || ( (dlg.m_supChange)&&(!m_cmbCompany.IsAddPosition()) ) )
    {
      if(nRow==1)
      {
        if(1!=m_Grid.GetRowCount())
          m_Grid.SetRowFocus(nRow);
        else
          m_Grid.SetRowFocus(0);
      }
      else
      {
        m_Grid.SetRowFocus(nRow-1);
      }
      m_Grid.RequerySource();
    }
    else
      m_Grid.Invalidate();
  }
}

void CDataGrid_DemoDlg::OnBtnAd()
{
  // TODO: Add your control notification handler code here
  CDialEdit dlg;
  dlg.m_pSet=m_Grid.m_pSet;

  // generate the next empID
	m_nNextEmpID =	dlg.m_pSet->GetRecordCount() +1;
  dlg.m_NextEmpID.Format(_T("%d"),m_nNextEmpID);
  
//  dlg.m_empId=m_Grid.m_pSet->GetCollect(L"ID") ;
  dlg.m_compId=30;//m_Grid.m_pSet->GetCollect(L"companyID") ;

//  dlg.m_cmbEmp.Attach(&m_CatArray,dlg.m_empId);
  dlg.m_cmbCompany.Attach(&m_SupArray,dlg.m_compId);

  dlg.m_operation=CDialEdit::NEW;

  if (dlg.DoModal() == IDOK)
  {
    //m_Grid.Invalidate();
    m_Grid.AddNew();
  }
	Requery();
}

void CDataGrid_DemoDlg::OnBtnCopy()
{
  // TODO: Add your control notification handler code here
  if(m_Grid.IsSelectRow()==-1)
    return;

  CDialEdit dlg;
  dlg.m_pSet=m_Grid.m_pSet;

  dlg.m_operation=CDialEdit::COPY;

  dlg.m_empId=m_Grid.m_pSet->GetCollect(L"ID") ;
//  dlg.m_compId=m_Grid.m_pSet->GetCollect(L"ID") ;

  dlg.m_cmbEmp.Attach(&m_CatArray,dlg.m_empId);
//  dlg.m_cmbCompany.Attach(&m_SupArray,dlg.m_compId);

  if (dlg.DoModal() == IDOK)
  {
    m_Grid.AddNew();
  }
}

void CDataGrid_DemoDlg::OnBtnDel()
{
  // TODO: Add your control notification handler code here
  m_Grid.Delete();
}

void CDataGrid_DemoDlg::OnEditCopy() 
{
	// TODO: Add your command handler code here
  m_Grid.OnEditCopy();		
}

void CDataGrid_DemoDlg::OnEditSelectall() 
{
	// TODO: Add your command handler code here
  m_Grid.OnEditSelectAll();	
}

void CDataGrid_DemoDlg::OnPrintButton() 
{
	// TODO: Add your command handler code here
	m_Grid.Print();	
}

void CDataGrid_DemoDlg::OnEditFind() 
{
	// TODO: Add your command handler code here
  m_Grid.OnEditFind();	
}

void CDataGrid_DemoDlg::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CResizableDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  //CString s;
  //CWnd *pWnd;

  //pWnd=GetDlgItem(  IDC_MAIL0 ); 
  //pWnd->GetWindowText(s);
  //m_eMail0.SetURL(_T("mailto:")+s);
  //m_eMail0.SetUnderline(CHyperLink::ulAlways);

  //pWnd=GetDlgItem(  IDC_MAIL1 ); 
  //pWnd->GetWindowText(s);
  //m_eMail1.SetURL(_T("mailto:")+s);
  //m_eMail1.SetUnderline(CHyperLink::ulAlways);
  //
  //pWnd=GetDlgItem(  IDC_MAIL2 ); 
  //pWnd->GetWindowText(s);
  //m_eMail2.SetURL(_T("mailto:")+s);
  //m_eMail2.SetUnderline(CHyperLink::ulAlways);

  //pWnd=GetDlgItem(  IDC_MAIL3 ); 
  //pWnd->GetWindowText(s);
  //m_eMail3.SetURL(_T("mailto:")+s);
  //m_eMail3.SetUnderline(CHyperLink::ulAlways);
  //

  //pWnd=GetDlgItem(  IDC_WWW0 ); 
  //pWnd->GetWindowText(s);
  //m_wLink0.SetURL(s);
  //m_wLink0.SetUnderline(CHyperLink::ulAlways);
  //
  //pWnd=GetDlgItem(  IDC_WWW1 ); 
  //pWnd->GetWindowText(s);
  //m_wLink1.SetURL(s);
  //m_wLink1.SetUnderline(CHyperLink::ulAlways);

  //pWnd=GetDlgItem(  IDC_WWW2 ); 
  //pWnd->GetWindowText(s);
  //m_wLink2.SetURL(s);
  //m_wLink2.SetUnderline(CHyperLink::ulAlways);

  //pWnd=GetDlgItem(  IDC_WWW3 ); 
  //pWnd->GetWindowText(s);
  //m_wLink3.SetURL(s);
  //m_wLink3.SetUnderline(CHyperLink::ulAlways);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDataGrid_DemoDlg::OnBtnDown()
{
	// TODO: Add your control notification handler code here
	m_Grid.PostMessage(WM_KEYDOWN,VK_DOWN,0); //down arrow key is press
}


void CDataGrid_DemoDlg::OnBtnPagedown()
{
	// TODO: Add your control notification handler code here
	m_Grid.PostMessage(WM_KEYDOWN,VK_NEXT,0); //page down key is press
}


void CDataGrid_DemoDlg::OnBtnPageup()
{
	// TODO: Add your control notification handler code here
	m_Grid.PostMessage(WM_KEYDOWN,VK_PRIOR,0); //page up key is press
}


void CDataGrid_DemoDlg::OnBtnUp()
{
	// TODO: Add your control notification handler code here
	m_Grid.PostMessage(WM_KEYDOWN,VK_UP,0); //up arrow key is press
}


afx_msg LRESULT CDataGrid_DemoDlg::OnGridCtrlDBClick(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("OnGridCtrlDBClick"));
	return 0;
}