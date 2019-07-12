// DDXFields.h: interface for the CDDXFields class.
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

#if !defined(AFX_DDXFIELDS_H__56E5A66E_30DE_45E1_B9F2_43EF992E3A13__INCLUDED_)
#define AFX_FIELD_H__56E5A66E_30DE_45E1_B9F2_43EF992E3A13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExString.h"

class CDDXField
{
public:
  int m_IDC;
  CExString m_name;
  bool m_upper;
  bool m_float;
  CExString m_value;
  CExString m_error;
  CExString m_description;

  CDDXField()
  {
    m_IDC=-1;
    m_description=m_error=m_value=m_name="";
    m_upper=m_float=false;
  }
  void Set(const CString& strName,int nIDC,const CString& strDefaulValue="",bool bUpper=false,bool bfloat=false)
  {
    m_description=m_name=strName;
    m_name.MakeUpper();
    m_value=strDefaulValue;
    m_IDC=nIDC;
    m_upper=bUpper;
    m_float=bfloat;
  }
};

typedef CArray <CDDXField,CDDXField&> CDDXFieldArray;

class CDDXFields : public CDDXFieldArray
{
public:
  int WriteData(_RecordsetPtr pSet);
  void ReadData(_RecordsetPtr pSet);
  void DDX(CDataExchange* pDX);
  int m_iCurField;
  CWnd *m_pWnd;
};


#endif // !defined(AFX_DDXFIELDS_H__56E5A66E_30DE_45E1_B9F2_43EF992E3A13__INCLUDED_)
