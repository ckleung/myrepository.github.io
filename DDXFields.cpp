// DDXFields.cpp: implementation of the CDDXFields class.
//
// CDDXFields class for editing fields
// Written by Kirill Panov <cpanov@yahoo.com>
// Copyright (c) 2000-2002. All Rights Reserved.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//??
#include "DataGrid_Demo.h"
//#include "invent.h"


#include "DDXFields.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CDDXFields::DDX(CDataExchange *pDX)
{
  int n=GetSize();
  for(m_iCurField=0;m_iCurField<n;m_iCurField++)
  {
    if( (GetAt(m_iCurField).m_IDC!=-1)&& (GetAt(m_iCurField).m_name!="") )
    {
      DDX_Text(pDX, GetAt(m_iCurField).m_IDC, ElementAt(m_iCurField).m_value );
    }
  }
}

void CDDXFields::ReadData(  _RecordsetPtr pSet)
{
  int n=GetSize();
  for(m_iCurField=0;m_iCurField<n;m_iCurField++)
  {
    if(GetAt(m_iCurField).m_name!="")
    {
      ElementAt(m_iCurField).m_value = pSet->Fields->GetItem(GetAt(m_iCurField).m_name.Variant())->Value;
    }
  }
}

int CDDXFields::WriteData(_RecordsetPtr pSet)
{
  int n=GetSize();

  try
  {

    for(m_iCurField=0;m_iCurField<n;m_iCurField++)
    {
      if(GetAt(m_iCurField).m_name!="")
      {
        if(GetAt(m_iCurField).m_upper)
        {
          ElementAt(m_iCurField).m_value.MakeUpper();
        }
        if( GetAt(m_iCurField).m_float)
        {
          ElementAt(m_iCurField).m_value.Replace(".",",");
          ElementAt(m_iCurField).m_value.Replace("-",",");
          ElementAt(m_iCurField).m_value.Replace(" ","");
        }
        pSet->Fields->GetItem(GetAt(m_iCurField).m_name.Variant())->Value= GetAt(m_iCurField).m_value.Variant();
      }//if
    }//for
  }//try
/*
  catch( _com_error &e )
  {
  }
*/
  catch(...)
  {
    m_pWnd->MessageBox(_T("Invalid field ")+GetAt(m_iCurField).m_description,_T("Ошибка поля "),MB_ICONERROR);

    int id=GetAt(m_iCurField).m_IDC;

    if(id!=-1)
    {
      CWnd *pWnd =m_pWnd->GetDlgItem( id );
      pWnd->SetFocus();
    }

    return(-1);
  }
  return(0);
}
