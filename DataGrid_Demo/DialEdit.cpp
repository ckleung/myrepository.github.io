// DialEdit.cpp : implementation file
//
// Chris Leung - BAH July 2019

#include "stdafx.h"
#include "DataGrid_Demo.h"
#include "DialEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialEdit dialog


CDialEdit::CDialEdit(CWnd* pParent /*=NULL*/)
  : CDialog(CDialEdit::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDialEdit)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  m_operation=EDIT;
  m_catChange=m_supChange=false;
  //ckl how many fields display in the edit dialog - hard code??
  m_DDXFields.SetSize(12);
}


void CDialEdit::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDialEdit)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
  DDX_Control(pDX, IDC_CMB_CAT, m_cmbEmp);
  DDX_Control(pDX, IDC_CMB_SUP, m_cmbCompany);

  m_DDXFields.DDX(pDX);

}


BEGIN_MESSAGE_MAP(CDialEdit, CDialog)
  //{{AFX_MSG_MAP(CDialEdit)
  ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
  ON_CBN_SELCHANGE(IDC_CMB_SUP, OnSelchangeCmbSup)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialEdit message handlers

BOOL CDialEdit::OnInitDialog()
{
  CDialog::OnInitDialog();


  // TODO: Add extra initialization here


  int i;

  m_DDXFields.m_pWnd=this;

  i=0;
  m_DDXFields.ElementAt(i).Set(_T( "last_name" ),IDC_ED_PROD) ;
  m_DDXFields.ElementAt(i).m_description=_T("last_name");

  i=1;
  m_DDXFields.ElementAt(i).Set(_T( "first_name" ), IDC_ED_QTY) ;
  m_DDXFields.ElementAt(i).m_description=_T("first_name");

  i=2;
  m_DDXFields.ElementAt(i).Set(_T( "email" ), IDC_ED_PRICE) ;
  m_DDXFields.ElementAt(i).m_description=_T("email") ;

  i=3;
  m_DDXFields.ElementAt(i).Set(_T( "gender" ),IDC_ED_UNITS) ;
  m_DDXFields.ElementAt(i).m_description=_T("gender");

  i=4;
  m_DDXFields.ElementAt(i).Set(_T( "phone_number" ),IDC_PHONE) ;
  m_DDXFields.ElementAt(i).m_description=_T("phone");

  i=5;
  m_DDXFields.ElementAt(i).Set(_T( "company_name" ),IDC_COMPANYNAME) ;
  m_DDXFields.ElementAt(i).m_description=_T("company name");

  i=6;
  m_DDXFields.ElementAt(i).Set(_T( "job_title" ),IDC_ED_DISCONT) ;
  m_DDXFields.ElementAt(i).m_description=_T("job title");

  i=7;
  m_DDXFields.ElementAt(i).Set(_T( "address" ),IDC_ADDRESS) ;
  m_DDXFields.ElementAt(i).m_description=_T("address");

  i=8;
  m_DDXFields.ElementAt(i).Set(_T( "city" ),IDC_CITY) ;
  m_DDXFields.ElementAt(i).m_description=_T("city");

  i=9;
  m_DDXFields.ElementAt(i).Set(_T( "state" ),IDC_STATE) ;
  m_DDXFields.ElementAt(i).m_description=_T("state");

  i=10;
  m_DDXFields.ElementAt(i).Set(_T( "emp_id" ),IDC_EMPID,m_NextEmpID) ;

  i=11;
  m_DDXFields.ElementAt(i).Set(_T( "companyid" ),IDC_ED_ID) ;
  m_DDXFields.ElementAt(i).m_description=_T("companyid");

  switch (m_operation)
  {
    case NEW:
      break;
    default:
		// read data from recordset
      m_DDXFields.ReadData(m_pSet);
	  // update the GUI for gender
		if (m_DDXFields.ElementAt(3).m_value == _T("Male"))
		{
			CButton* pButton = (CButton*)GetDlgItem(IDC_MALE);
			pButton->SetCheck(true);
		}
		else
		{
			CButton* pButton = (CButton*)GetDlgItem(IDC_FEMALE);
			pButton->SetCheck(true);
		}

    break;
  }
  UpdateData(FALSE);

  m_cmbCompany.Fill();
//  m_cmbEmp.Fill();

  m_btnSave.SubclassDlgItem(IDC_BTN_SAVE, this);
  m_btnSave.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
  m_btnSave.SetFlat(FALSE);
  m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);

  m_btnCancel.SubclassDlgItem(IDCANCEL, this);
  m_btnCancel.SetBitmaps(IDB_DEL, RGB(255, 0, 255));
  m_btnCancel.SetFlat(FALSE);
  m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialEdit::OnBtnSave()
{
  // TODO: Add your control notification handler code here
  CExString strField;
  UpdateData();

  // check the GUI (gender) status then update the DDXFields variable

	if (BST_CHECKED == IsDlgButtonChecked(IDC_MALE))
	{
		m_DDXFields.ElementAt(3).m_value = _T("Male");
	}
	else 
	{
		m_DDXFields.ElementAt(3).m_value = _T("Female");
	}

  try
  {
    switch (m_operation)
    {
      case EDIT:
        break;
      default:
        m_pSet->AddNew();

        strField=_T("ID");
//        m_pSet->Fields->GetItem(strField.Variant())->Value = m_empId.Variant();

        //strField=_T("ID");
        //m_pSet->Fields->GetItem(strField.Variant())->Value = m_compId.Variant();

        break;
    }
    try
    {
      if( m_DDXFields.WriteData(m_pSet)==-1)
        return;
    }
    catch(...)
    {
      ;
    }
    CExString strEmpId,strCompId;

	// get next emp ID here	for new record
	if (m_operation=CDialEdit::NEW)
	{
		strEmpId = m_NextEmpID;
	}
    else
	{
		strEmpId=m_cmbEmp.GetCurId();
	}
    strCompId=m_cmbCompany.GetCurId();
    CExString strCompanyName=m_cmbCompany.GetCurFieldValue();

    //if(strCatId!=m_empId)
    //{
    //  m_catChange=true;
    //  strField=_T("emp_ID");
    //  m_pSet->Fields->GetItem(strField.Variant())->Value=strCatId.Variant();
    //}

 //   if(strSupId!=m_compId)
    {
      m_supChange=true;
//	  if (m_operation == EDIT)
//	  {
		strField=_T("CompanyID");
//	  }
	 // else
	 // {
		//strField=_T("ID");
	 // }
      m_pSet->Fields->GetItem(strField.Variant())->Value = strCompId.Variant();
//	  strField=_T("Company_Name");
//	  m_pSet->Fields->GetItem(strField.Variant())->Value = strCompanyName.Variant();
    }
    m_pSet->Update();

    CDialog::OnOK();


  }//try
  catch( _com_error &e )
  {

    CString mes1,mes2,mes3,mes4;

    mes1.Format(_T("Error:%08lx.\n"), e.Error());
    mes2.Format(_T("ErrorMessage:%s.\n"), e.ErrorMessage());
    mes3.Format(_T("Source:%s.\n"), (LPCTSTR) _bstr_t(e.Source()));
    mes4.Format(_T("Description:%s.\n"), (LPCTSTR) _bstr_t(e.Description()));
    MessageBox(mes1+mes2+mes3+mes4,_T("Invalid field "),MB_ICONERROR);

    return;
  }
  catch(...)
  {

    MessageBox(_T("Unhandled Exception"),_T("Invalid field ")+strField,MB_ICONERROR);
    return;
  }

}

void CDialEdit::OnSelchangeCmbSup()
{
  // TODO: Add your control notification handler code here
//	CButton* pButton = (CEdit*)GetDlgItem(IDC_MALE);
//	pButton->SetCheck(true);
	CExString strField;
	CExString strCompanyName;
	strField=_T("company_name");
//	m_cmbCompany.m_pArStrBox()
	    
//	m_DDXFields.ElementAt(5).m_value = m_cmbCompany.GetCurFieldValue();
	CEdit* pCompanyName = (CEdit*)GetDlgItem(IDC_COMPANYNAME);
	pCompanyName->SetWindowText(TEXT(m_cmbCompany.GetCurFieldValue()));


	// read data from recordset
//    m_DDXFields.ReadData(m_pSet);
	UpdateData(FALSE);
}