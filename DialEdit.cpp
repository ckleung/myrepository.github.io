// DialEdit.cpp : implementation file
//

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
  m_DDXFields.SetSize(5);
}


void CDialEdit::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDialEdit)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
  DDX_Control(pDX, IDC_CMB_CAT, m_cmbCat);
  DDX_Control(pDX, IDC_CMB_SUP, m_cmbSup);

  m_DDXFields.DDX(pDX);

}


BEGIN_MESSAGE_MAP(CDialEdit, CDialog)
  //{{AFX_MSG_MAP(CDialEdit)
  ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
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
  m_DDXFields.ElementAt(i).Set(_T( "ProductName" ),IDC_ED_PROD) ;
  m_DDXFields.ElementAt(i).m_description=_T("Product");

  i=1;
  m_DDXFields.ElementAt(i).Set(_T( "QuantityPerUnit" ), IDC_ED_QTY, _T( "1" ),false,true) ;
  m_DDXFields.ElementAt(i).m_description=_T("Quantity Per Unit");

  i=2;
  m_DDXFields.ElementAt(i).Set(_T( "UnitPrice" ), IDC_ED_PRICE, _T( "0" ),false,true) ;
  m_DDXFields.ElementAt(i).m_description=_T("Price") ;

  i=3;
  m_DDXFields.ElementAt(i).Set(_T( "UnitsInStock" ),IDC_ED_UNITS, _T( "0" ),false,true) ;
  m_DDXFields.ElementAt(i).m_description=_T("Units In Stock");

  i=4;
  m_DDXFields.ElementAt(i).Set(_T( "Discontinued" ),IDC_ED_DISCONT,_T( "0" ),false,true) ;

  switch (m_operation)
  {
    case NEW:
      break;
    default:
      m_DDXFields.ReadData(m_pSet);
    break;
  }
  UpdateData(FALSE);

  m_cmbSup.Fill();
  m_cmbCat.Fill();

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
  try
  {
    switch (m_operation)
    {
      case EDIT:
        break;
      default:
        m_pSet->AddNew();

        strField=_T("CategoryID");
        m_pSet->Fields->GetItem(strField.Variant())->Value = m_catId.Variant();

        strField=_T("SupplierID");
        m_pSet->Fields->GetItem(strField.Variant())->Value = m_supId.Variant();

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
    CExString strCatId,strSupId;
    strCatId=m_cmbCat.GetCurId();
    strSupId=m_cmbSup.GetCurId();;

    if(strCatId!=m_catId)
    {

      m_catChange=true;
      strField=_T("CategoryID");
      m_pSet->Fields->GetItem(strField.Variant())->Value=strCatId.Variant();
    }

    if(strSupId!=m_supId)
    {
      m_supChange=true;
      strField=_T("SupplierID");
      m_pSet->Fields->GetItem(strField.Variant())->Value=strSupId.Variant();
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
