; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DataGrid_Demo.h"

ClassCount=5
Class1=CDataGrid_DemoApp
Class2=CDataGrid_DemoDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DATAGRID_DEMO_DIALOG
Resource4=IDD_DATAGRID_DEMO_DIALOG (English (U.S.))
Resource5=IDD_DIAL_EDIT (English (U.S.))
Class4=CDialEdit
Resource6=IDD_DIAL_FIND (English (U.S.))
Resource7=IDD_ABOUTBOX (English (U.S.))
Class5=CDialFind
Resource8=IDR_MENU (English (U.S.))

[CLS:CDataGrid_DemoApp]
Type=0
HeaderFile=DataGrid_Demo.h
ImplementationFile=DataGrid_Demo.cpp
Filter=N

[CLS:CDataGrid_DemoDlg]
Type=0
HeaderFile=DataGrid_DemoDlg.h
ImplementationFile=DataGrid_DemoDlg.cpp
Filter=D
BaseClass=CResizableDialog
VirtualFilter=dWC
LastObject=CDataGrid_DemoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DataGrid_DemoDlg.h
ImplementationFile=DataGrid_DemoDlg.cpp
Filter=D
BaseClass=CResizableDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_DATAGRID_DEMO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CDataGrid_DemoDlg

[DLG:IDD_DATAGRID_DEMO_DIALOG (English (U.S.))]
Type=1
Class=CDataGrid_DemoDlg
ControlCount=11
Control1=IDC_GRID,MFCGridCtrl,1342242816
Control2=IDC_BTN_EDIT,button,1342242816
Control3=IDC_BTN_AD,button,1342242816
Control4=IDC_BTN_COPY,button,1342242816
Control5=IDC_BTN_DEL,button,1342242816
Control6=IDC_CMB_CAT,combobox,1344339971
Control7=IDC_CMB_SUP,combobox,1344339971
Control8=IDOK,button,1073741825
Control9=IDCANCEL,button,1073741824
Control10=IDC_STATIC,static,1342308353
Control11=IDC_STATIC,static,1342308353

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=17
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_MAIL1,static,1342308352
Control7=IDC_NAME1,static,1342308352
Control8=IDC_MAIL0,static,1342308352
Control9=IDC_NAME0,static,1342308352
Control10=IDC_WWW0,static,1342308352
Control11=IDC_WWW1,static,1342308352
Control12=IDC_MAIL2,static,1342308352
Control13=IDC_NAME2,static,1342308352
Control14=IDC_WWW2,static,1342308352
Control15=IDC_MAIL3,static,1342308352
Control16=IDC_NAME3,static,1342308352
Control17=IDC_WWW3,static,1342308352

[CLS:CDialEdit]
Type=0
HeaderFile=DialEdit.h
ImplementationFile=DialEdit.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialEdit
VirtualFilter=dWC

[DLG:IDD_DIAL_EDIT (English (U.S.))]
Type=1
Class=CDialEdit
ControlCount=16
Control1=IDC_ED_PROD,edit,1350631552
Control2=IDC_ED_QTY,edit,1350631552
Control3=IDC_ED_PRICE,edit,1350631552
Control4=IDC_ED_UNITS,edit,1350631552
Control5=IDC_ED_DISCONT,edit,1350631552
Control6=IDC_BTN_SAVE,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_CMB_CAT,combobox,1344339971
Control9=IDC_CMB_SUP,combobox,1344339971
Control10=IDC_STATIC,static,1342308353
Control11=IDC_STATIC,static,1342308353
Control12=IDC_STATIC,static,1342308353
Control13=IDC_STATIC,static,1342308353
Control14=IDC_STATIC,static,1342308353
Control15=IDC_STATIC,static,1342308353
Control16=IDC_STATIC,static,1342308353

[MNU:IDR_MENU (English (U.S.))]
Type=1
Class=?
Command1=IDC_PRINT_BUTTON
Command2=ID_APP_EXIT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_SELECTALL
Command5=ID_EDIT_FIND
Command6=ID_APP_ABOUT
CommandCount=6

[DLG:IDD_DIAL_FIND (English (U.S.))]
Type=1
Class=CDialFind
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FIND,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_FIND,combobox,1344339971

[CLS:CDialFind]
Type=0
HeaderFile=DialFind.h
ImplementationFile=DialFind.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialFind
VirtualFilter=dWC

