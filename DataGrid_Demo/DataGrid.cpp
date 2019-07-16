// DataGrid.cpp: implementation of the CDataGrid class.
//
// CDataGrid - the Grid class for access to database
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Resource.h"

#include "DataGrid.h"
#include "ExString.h"

#ifdef IDD_DIAL_FIND
  #include "DialFind.h"
#endif IDD_DIAL_FIND

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CDataGrid,CGridCtrl)


BEGIN_MESSAGE_MAP(CDataGrid, CGridCtrl)
//{{AFX_MSG_MAP(CGridCtrl)
  ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()





CDataGrid::CDataGrid()
{
  m_strSQLFields=m_strSQLFrom=m_strSQLWhere=m_strSQLOrderBy=m_strKey=_T("");
  m_nSortField=-1;
  m_bWait=false;

  m_hCursorWait= AfxGetApp()->LoadStandardCursor(IDC_WAIT);
}

CDataGrid::~CDataGrid()
{

}


void CDataGrid::OnFixedRowClick(CCellID& cell)
{
  if (!IsValid(cell))
    return;
  Sort(cell.col);
}
void CDataGrid::Requery(  const CString& strKey
    ,const CString& strSQLFields
    ,const CString& strSQLFrom
    ,const CString& strSQLWhere
    ,int NumberSortField
    ,bool AscSortField)
{
  CString strSQLOrderBy;
  m_nSortField=NumberSortField;
  m_bAscSortField=AscSortField;
  if(NumberSortField!=-1)
  {
    strSQLOrderBy=m_field[NumberSortField].Field;
    if(!AscSortField)
      strSQLOrderBy+=_T(" DESC");
  }
  else
  {
    strSQLOrderBy=_T("");
  }
  Requery(strKey,strSQLFields,strSQLFrom,strSQLWhere,strSQLOrderBy);
}

void CDataGrid::Requery(  const CString& strKey
    ,const CString& strSQLFields
    ,const CString& strSQLFrom
    ,const CString& strSQLWhere
    ,const CString& strSQLOrderBy)
{
  ::SetCursor(m_hCursorWait);
  m_strSQLFields=strSQLFields;
  m_strSQLFrom=strSQLFrom;
  m_strSQLWhere=strSQLWhere;
  m_strSQLOrderBy=strSQLOrderBy;
  m_strKey=strKey;

  CString strSQL=_T("SELECT ")+m_strSQLFields+_T(" FROM ")+m_strSQLFrom;
  if(m_strSQLWhere.GetLength()>0)
    strSQL+=_T(" WHERE ")+m_strSQLWhere;

  if(m_strSQLOrderBy.GetLength()>0)
    strSQL+=_T(" ORDER BY ")+m_strSQLOrderBy;

  _variant_t TheValue;

  try
  {
    if(m_pSet==NULL)
    {
      m_pSet.CreateInstance(__uuidof(Recordset));
    }
    else
    {
      if(m_pSet->State == adStateOpen)
        m_pSet->Close();
    }
    m_pSet->Open(_variant_t(strSQL),m_pCon.GetInterfacePtr()
      ,adOpenKeyset
      ,adLockOptimistic
      ,adCmdText);
  }
  catch(_com_error *e)
  {
    CString Error = e->ErrorMessage();
    AfxMessageBox(e->ErrorMessage());
    return;
  }

}

void CDataGrid::Execute(_ConnectionPtr & Con
    ,const CString& strKey
    ,const CString& strSQLFields
    ,const CString& strSQLFrom
    ,const CString& strSQLWhere
    ,int NumberSortField
    ,bool AscSortField)
{
  m_bWait=true;
//  AfxMessageBox("m_bWait=true;");
  CString strSQLOrderBy;
  m_nSortField=NumberSortField;
  m_bAscSortField=AscSortField;
  if(NumberSortField!=-1)
  {
    strSQLOrderBy=m_field[NumberSortField].Field;
    if(!AscSortField)
      strSQLOrderBy+=_T(" DESC");
  }
  else
  {
    strSQLOrderBy=_T("");
  }
  Execute(Con,strKey,strSQLFields,strSQLFrom,strSQLWhere,strSQLOrderBy);
//  m_bWait=false;
//  AfxMessageBox("m_bWait=false;");

  if(NumberSortField!=-1)
  {
    SortItems(NumberSortField, AscSortField);
  }

  Invalidate();
}
void CDataGrid::Execute(_ConnectionPtr & Con
    ,const CString& strKey
    ,const CString& strSQLFields
    ,const CString& strSQLFrom
    ,const CString& strSQLWhere
    ,const CString& strSQLOrderBy)
{
  m_bWait=true;
  m_pCon=Con;
  Requery(strKey,strSQLFields,strSQLFrom,strSQLWhere,strSQLOrderBy);
  Refresh();
  m_bWait=false;
}

void CDataGrid::SetValue(GV_DISPINFO *pDispInfo)
{
  CString strRead;
  strRead.LoadString(IDS_GRID_READ);
  if (GVN_GETDISPINFO == pDispInfo->hdr.code)
  {

    if(pDispInfo->item.row!=0)
    {
      if(m_bWait) return;
      if(m_pSet->State == adStateOpen)
      {
        try
        {
          SetRecordsetPos(pDispInfo->item.row);
          CString name=m_field[pDispInfo->item.col].Field;

          _variant_t TheValue;
          TheValue = m_pSet->Fields->GetItem(_variant_t(name))->Value;

          pDispInfo->item.nFormat=m_field[pDispInfo->item.col].Align;
          if(TheValue.vt!=VT_NULL)
            pDispInfo->item.strText=(char*)_bstr_t(TheValue);
          else
            pDispInfo->item.strText="";
        }
        catch( _com_error &e )
        {
          #if defined PROGRAM_DEBUG
            CString mes1,mes2,mes3,mes4;
            mes1.Format("Error:%08lx.\n", e.Error());
            mes2.Format("ErrorMessage:%s.\n", e.ErrorMessage());
            mes3.Format("Source:%s.\n", (LPCTSTR) _bstr_t(e.Source()));
            mes4.Format("Description:%s.\n", (LPCTSTR) _bstr_t(e.Description()));
            MessageBox(mes1+mes2+mes3+mes4,strRead,MB_ICONERROR);
          #endif

          return;
        }
        catch(...)
        {
          #if defined PROGRAM_DEBUG
            MessageBox("Unhandled Exception",strRead,MB_ICONERROR);
          #endif
        }
      }
      else
      {
        pDispInfo->item.strText=_T("");
      }
    }
    else
    {
      pDispInfo->item.nFormat=DT_CENTER;
      pDispInfo->item.strText=m_field[pDispInfo->item.col].Caption;
    }

  }
  else if (GVN_ODCACHEHINT == pDispInfo->hdr.code)
  {
    GV_CACHEHINT *pCacheHint = (GV_CACHEHINT*)pDispInfo;
  }
}

void CDataGrid::Sort(int NumberField)
{
  CWaitCursor waiter;
  CString strOrderBy=m_field[NumberField].Field;
  if (NumberField == GetSortColumn())
  {
    if(GetSortAscending())
      strOrderBy=strOrderBy+_T(" DESC");
    SortItems(NumberField, !GetSortAscending());
  }
  else
  {
    SortItems(NumberField, TRUE);
  }
  Requery(m_strKey,m_strSQLFields,m_strSQLFrom,m_strSQLWhere,strOrderBy);
  Invalidate();
}

void CDataGrid::Delete()
{
  int nRow = IsSelectRow();
  if (nRow==-1)
    return;
  CString strDel,strErrorDesc;
  strDel.LoadString(IDS_GRID_DEL);
  CString strQuestion;

  strQuestion.LoadString(IDS_GRID_DEL_QUESTION);
  if (MessageBox (strQuestion, strDel,  MB_YESNO|MB_DEFBUTTON2 | MB_ICONQUESTION) == IDNO)
    return;

  try
  {
    m_pSet->Delete(adAffectCurrent);
//    m_pSet->Close();
    m_pSet->Update();
  }
  catch( _com_error &e )
  {

    CString mes1,mes2,mes3,mes4;

    mes1.Format("Error:%08lx.\n", e.Error());
    mes2.Format("ErrorMessage:%s.\n", e.ErrorMessage());
    mes3.Format("Source:%s.\n", (LPCTSTR) _bstr_t(e.Source()));
    mes4.Format("Description:%s.\n", (LPCTSTR) _bstr_t(e.Description()));
    MessageBox(mes1+mes2+mes3+mes4,strDel,MB_ICONERROR);
    return;
  }
  catch(...)
  {
    MessageBox("Unhandled Exception",strDel,MB_ICONERROR);
    return;
  }
  if(nRow==1)
  {
    if(1!=GetRowCount())
      SetRowFocus(nRow);
    else
      SetRowFocus(0);
  }
  else
    SetRowFocus(nRow-1);

  RequerySource(nRow);
}

void CDataGrid::SetRecordsetPos(int pos)
{
//m_pSet->MoveFirst();
//m_pSet->Move(pDispInfo->item.row+1);
  int move=pos-m_pSet->AbsolutePosition;
  try
  {
    m_pSet->Move(move);
  }
  catch (CMemoryException* e)
  {
    #if defined PROGRAM_DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }

}

void CDataGrid::Refresh(int nRowFocus)
{
  try
  {
    SetVirtualMode(true);
    SetCallbackFunc( NULL , 0);
    SetFixedRowCount(1);
    SetFixedColumnCount(0);

    SetColumnCount(m_field.GetSize());
    SetRowCount(m_pSet->GetRecordCount() +1 );
    SetListMode();
    m_bSortOnClick=TRUE;
    AutoSize();
    for(int i=0;i<m_field.GetSize();i++)
      if (m_field[i].With>0)
        SetColumnWidth(i, m_field[i].With);
    GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xFF));//0xE0//ckl
    SetRowFocus(nRowFocus);
  }
  catch (CMemoryException* e)
  {
    e->ReportError();
    e->Delete();
  }

}

void CDataGrid::AddNew()
{

  SetRowCount(m_pSet->GetRecordCount() +1 );
  SetRowFocus(GetRowCount()-1);
}

void CDataGrid::SetRowFocus(int nRow)
{
  if((GetRowCount()>nRow)&&(nRow>-1))
  {
    CCellID cell(nRow,1);
    SetFocusCell(cell);
    SetSelectedRange(nRow,GetFixedColumnCount(), nRow ,GetColumnCount()-1, TRUE);
    EnsureVisible(nRow,1);
  }
}
void CDataGrid::RequerySource(int nRow)
{
  Requery( m_strKey,m_strSQLFields,m_strSQLFrom,m_strSQLWhere,m_strSQLOrderBy);
  SetRowCount(m_pSet->GetRecordCount() +1 );
}



int CDataGrid::IsSelectRow()
{
  int nRow = GetFocusCell().row;
  if (nRow ==-1 )
  {
    CString strWarn,strWarnDesc;
    strWarnDesc.LoadString(IDS_GRID_NO_SEL_DESC);
    strWarn.LoadString(IDS_GRID_NO_SEL_REC);
    MessageBox(strWarnDesc,strWarn,MB_ICONWARNING);
    return( -1);
  }
  else
  {
    SetRecordsetPos(nRow);
    return( nRow);
  }
}

void CDataGrid::OnEditFind()
{

#ifdef IDD_DIAL_FIND

  CDialFind dlg;
  dlg.m_arFind.SetSize(0);
  int i,count=0;

  for(i=0;i<m_field.GetSize();i++)
  {
    if(m_field[i].Find)
    {
      dlg.m_arFind.SetAtGrow(count,CFind( m_field[i].Caption,  count ) );
      count++;
    }
  }

  if (dlg.DoModal() == IDOK)
  {
    int row=GetFocusCell().row ;
    SetRecordsetPos(row);
    int pos=m_pSet->AbsolutePosition;
    CExString strFind,strUp;
    i=dlg.m_arFind.GetAt(dlg.m_nField).m_index;
    if(m_field[i].Type==FIELD_NUMBER)
    {
      strFind=m_field[i].Field+"="+dlg.m_strFind;
    }
    else
    {
      strUp=dlg.m_strFind;
      strUp.MakeUpper();
      strUp.TrimRight();
      strUp.TrimLeft();
      strFind=m_field[i].Field+" like '%"+strUp+"%'";
    }
    m_pSet->Find(_bstr_t(strFind),0,adSearchForward);

    if(m_pSet->AbsolutePosition<1)
    {
      m_pSet->MoveFirst();
//    SetRecordsetPos(row);
      m_pSet->Find(_bstr_t(strFind),0,adSearchForward);
      if(m_pSet->AbsolutePosition<1)
      {
        m_pSet->MoveFirst();
        SetRecordsetPos(row);
        CString strWarn;
        strWarn.LoadString(IDS_GRID_FIND_WARN);
        MessageBox(strWarn,strWarn,MB_ICONWARNING);

      }
    }
    SetRowFocus(m_pSet->AbsolutePosition);
  }

#endif

}

void CDataGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

  CGridCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
  if (IsCTRLpressed())
  {
    switch (nChar)
    {
     case 'F':
       OnEditFind();
       break;
    }
  }

}
