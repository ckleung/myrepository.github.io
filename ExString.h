// ExString.h: interface for the CExString class.
//
// CExString - CString extension class
// Written by Kirill Panov <cpanov@yahoo.com>
// Copyright (c) 1998-2002. All Rights Reserved.
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

#if !defined(AFX_EXSTRING_H__F25E5E0F_D01F_11D2_9D29_F4A9337BEE5E__INCLUDED_)
#define AFX_EXSTRING_H__F25E5E0F_D01F_11D2_9D29_F4A9337BEE5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <stdlib.h>
class CExString:public CString
{
public:
  CExString() : CString( ){};
  CExString( const CString& stringSrc) : CString( stringSrc ){};
  CExString( const CExString& stringSrc) : CString( stringSrc ){};
  CExString( TCHAR ch, int nRepeat = 1 ) : CString( ch, nRepeat ){};
  CExString( LPCTSTR lpch, int nLength ) : CString( lpch, nLength ){};
  CExString( const unsigned char* psz ) : CString( psz ){};
  CExString( LPCWSTR lpsz ) : CString( lpsz ){};
  CExString( LPCSTR lpsz ) : CString( lpsz ){};
  CExString(const int i)        : CString(itoa(i))      {}
  CExString(const UINT u)       : CString(utoa(u))      {}
  CExString(const double d)     : CString(dtoa(d))      {}
  CExString(const float d)      : CString(dtoa(d))      {}
  CExString(const _variant_t v) :CString(vtoa(v))      {}
  friend  CExString itoa(int i);
  friend  CExString utoa(UINT u);
  friend  CExString dtoa(double d);
  friend  CExString dtoa(double d, int n);
  friend  CExString vtoa(const _variant_t v);
  friend  _variant_t atov(const CString s);
  friend  COleCurrency atoCur(const CString s);

  //  friend ostream& operator<<(ostream&, CExString&);

  double  Double() const        { return atof(m_pchData); }
  float Float() const       { return float(atof(m_pchData)); }
  int   Int() const         { return atoi(m_pchData); }
  char  Char() const        { return m_pchData[0]; }
  bool  Bool() const        { return (Int() != 0); }
  _variant_t Variant() const{return atov(m_pchData);}
  COleCurrency Currency() const{return atoCur(m_pchData);}
};

#endif // !defined(AFX_EXSTRING_H__F25E5E0F_D01F_11D2_9D29_F4A9337BEE5E__INCLUDED_)
