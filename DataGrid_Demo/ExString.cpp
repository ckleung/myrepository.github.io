// ExString.cpp: implementation of the CExString class.
//
// CExString - CString extension class
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// The code contained in this file is based on the original
// XString class written by Joachim Raidl,
//      mailto:Joachim.Raidl@iname.com
//      http://www.codeguru.com/string/xstring.shtml
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CExString itoa(int i)       { CExString h; h.Format("%d", i); return h; }
CExString utoa(UINT u)      { CExString h; h.Format("%u", u); return h; }
CExString dtoa(double d)      { CExString h; h.Format("%g", d); return h; }
CExString dtoa(double d, int n) { CExString h; h.Format("%.*f", n, d); return h; }
CExString Set(const CString s) {CExString h=s;return h;}
CExString vtoa ( _variant_t v)
{
  CExString h;
  if(v.vt!=VT_NULL)
    h=(char*)_bstr_t(v);
  return h;
}
_variant_t atov(const CString s)
{
  if(s==_T(""))
  {
    _variant_t v;
    v.vt=VT_NULL;
    return (v);
  }
  else
    return _variant_t(s);
}
COleCurrency atoCur(const CString s)
{
  COleCurrency cur;

  CExString strD,strF,str=s;
  int i;

  str.TrimLeft();
  str.TrimRight();

  str.Replace(",",".");
  str.Replace("-",".");

  i=str.Find('.');

  if(i>0)
  {
    strD=str.Left(i);
    strF=str.Mid(i+1,2);
  }
  else
  {
    strD=str;
    strF="00";
  }

  i=strF.Int();

  if(i<10)
    i*=10;

  i=i*100;

  cur.SetCurrency(strD.Int(),i);
  return (cur);
}

/*
ostream& operator<<(ostream& s, CExString& x)
{
  CString tmp=x;
  tmp.AnsiToOem();
  return s <<tmp ;
}
*/
