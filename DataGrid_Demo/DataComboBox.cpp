// DataComboBox.cpp: implementation of the CDataComboBox class.
//
// CDataComboBox class for access to database from ComboBox
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//???
#include "DataGrid_Demo.h"
//#include "Invent.h"

#include "DataComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataComboBox

CDataComboBox::CDataComboBox()
{
  m_state=UNBOUND;
  m_strDefaultId="";
  m_nOldPosition=m_nCurPosition=-1;
  m_bAddPosition=false;
  m_strAddPosition=_T("<All>");

}

CDataComboBox::~CDataComboBox()
{
  if(m_state==UNBOUND)
    return;
  try
  {
    m_pSet->Close();
  }
  catch( _com_error &e )
  {

    CString mes1,mes2,mes3,mes4;

    mes1.Format("Error:%08lx.\n", e.Error());
    mes2.Format("ErrorMessage:%s.\n", e.ErrorMessage());
    mes3.Format("Source:%s.\n", (LPCTSTR) _bstr_t(e.Source()));
    mes4.Format("Description:%s.\n", (LPCTSTR) _bstr_t(e.Description()));
    MessageBox(mes1+mes2+mes3+mes4,_T("DataComboBox error"),MB_ICONERROR);
    return;
  }
  catch(...)
  {
    MessageBox("Unhandled Exception",_T("DataComboBox error"),MB_ICONERROR);
    return;
  }

  m_pSet = NULL;
}


BEGIN_MESSAGE_MAP(CDataComboBox, CComboBox)
  //{{AFX_MSG_MAP(CDataComboBox)
  ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataComboBox message handlers

void CDataComboBox::Execute( _ConnectionPtr & Con
    ,const CString& strQuery
    ,const CString& strShowField
    ,const int CommandType)
{
  m_state=BOUND;
  _variant_t TheValue;
  m_pSet.CreateInstance(__uuidof(Recordset));

  m_strQuery= strQuery;
  m_strShowField= strShowField;

  for(int i=0;i<GetCount();i++)
    DeleteString(i);

  m_nCurPosition=0;

  try
  {
    m_pSet->CursorLocation = adUseClient;
    m_pSet->Open(m_strQuery.Variant(),Con.GetInterfacePtr(),
      adOpenStatic,
      adLockReadOnly,
      CommandType);

    while(!m_pSet->adoEOF)
    {
      TheValue = m_pSet->GetCollect(_variant_t(m_strShowField));
      if(TheValue.vt!=VT_NULL)
        AddString((char*)_bstr_t(TheValue));
      m_pSet->MoveNext();
    }
  }
  catch(_com_error *e)
  {
    CString Error = e->ErrorMessage();
    AfxMessageBox(e->ErrorMessage());
    return;
  }
  m_pSet->MoveFirst();
  //<All>;
  if(m_bAddPosition)
    AddString(m_strAddPosition);

  SetCurSel(0);
}

void CDataComboBox::OnSelendok()
{
  // TODO: Add your control notification handler code here
  SetCurPosition();
}

void CDataComboBox::Attach(CArrayStringBox * pArStrBox,const CExString& strDefaultId)
{
  m_state=UNBOUND;
  m_pArStrBox=pArStrBox;
  m_strDefaultId= strDefaultId;
}

void CArrayStringBox::Fill( _ConnectionPtr & Con
    ,const CString& strQuery
    ,const CString& strShowField
    ,const CString& strIdField)
{
  _RecordsetPtr pSet;
  pSet.CreateInstance(__uuidof(Recordset));
  CStrBox row;
  try
  {
    pSet->CursorLocation = adUseClient;
    pSet->Open(_variant_t(strQuery),Con.GetInterfacePtr(),
      adOpenStatic,
      adLockReadOnly,
      adCmdText);
    SetSize(pSet->GetRecordCount());
    int i=0;

    while(!pSet->adoEOF)
    {
      row.m_strField= pSet->GetCollect(_variant_t(strShowField));
      row.m_strId=pSet->GetCollect(_variant_t(strIdField));
      SetAt(i,row);
      i++;
      pSet->MoveNext();
    }
  }
  catch(_com_error *e)
  {
    CString Error = e->ErrorMessage();
    AfxMessageBox(e->ErrorMessage());
    return;
  }
  pSet->Close();

}

void CDataComboBox::Fill()
{
  CExString s;
  int pos=0;
  for(int i=0;i<(m_pArStrBox->GetSize());i++)
  {
    if(m_strDefaultId.GetLength()!=0)
    {
      if(m_pArStrBox->GetAt(i).m_strId==m_strDefaultId)
      {
        pos=i;
      }
    }
    AddString(m_pArStrBox->GetAt(i).m_strField);
  }
  m_nCurPosition=pos;
  SetCurSel(pos);

}
CExString CDataComboBox::GetCurId()
{
  //CExString s=m_nCurPosition;
  //return(s);
  return(m_pArStrBox->GetAt(m_nCurPosition).m_strId);
}

CExString CDataComboBox::GetCurFieldValue()
{
  return(m_pArStrBox->GetAt(m_nCurPosition).m_strField);
}


void CDataComboBox::SetCurPosition()
{
  int nCur=GetCurSel()  ;

  if(nCur!=m_nCurPosition)
  {
    m_nOldPosition=m_nCurPosition;
    if(m_state==BOUND)
    {
      if(IsAddPosition())
      {
        m_pSet->MoveFirst();
        m_pSet->Move(nCur); //-1
      }
      else
        m_pSet->Move(nCur-m_nCurPosition);
    }
    m_nCurPosition=nCur;
  }

}

void CDataComboBox::SetPrevPosition()
{
  if(m_nOldPosition>-1)
  {
    SetCurSel(m_nOldPosition);
    SetCurPosition();
  }
}

bool CDataComboBox::IsAddPosition()
{
  return ( (m_bAddPosition)&&(m_nCurPosition==GetCount() -1)  ) ;
}
