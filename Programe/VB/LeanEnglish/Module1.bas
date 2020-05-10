Attribute VB_Name = "mMain"
Option Explicit

Public Const WS_MAXIMIZEBOX = &H10000
Public Const GWL_STYLE = (-16)
Public Const GW_HWNDNEXT = 2
Public Const GW_HWNDPREV = 3
Public Const SW_MAXIMIZE = 3
Public Const SW_SHOW = 5
Public Const SW_PARENTOPENING = 3
Public Const SW_RESTORE = 9
Public Const SW_SHOWDEFAULT = 10
Public Const SW_NORMAL = 1
Public Const SW_SHOWNOACTIVATE = 4
Public Const GWL_EXSTYLE = (-20)
Public Const MAX_PATH = 260
Public Type FILETIME
        dwLowDateTime As Long
        dwHighDateTime As Long
End Type
Public Type WIN32_FIND_DATA
        dwFileAttributes As Long
        ftCreationTime As FILETIME
        ftLastAccessTime As FILETIME
        ftLastWriteTime As FILETIME
        nFileSizeHigh As Long
        nFileSizeLow As Long
        dwReserved0 As Long
        dwReserved1 As Long
        cFileName As String * MAX_PATH
        cAlternate As String * 14
End Type
Private Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Public Declare Function GetWindow Lib "user32" (ByVal hwnd As Long, ByVal wCmd As Long) As Long
Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function GetWindowText Lib "user32" Alias "GetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String, ByVal cch As Long) As Long
Public Declare Function GetWindowTextLength Lib "user32" Alias "GetWindowTextLengthA" (ByVal hwnd As Long) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long

Public frmMain As frmMainMdi '������

Public Dbs As Database
Public Const Table = "dictionary"
Public INIFile As String

Public Type OptionVal
       Backmap As String '����ͼƬ
       End Type
Public OptionsVal As OptionVal

Public Enum SplitStyleenum
       SpS���� = False
       SpS����붺�� = True
End Enum

Public Enum FindStyle
       ͬ��� = 0
       ����� = 1
       ���ƴ� = 2
       ������ = 3
       ��ֹ�õ��ظ��ַ��� = 4
End Enum

Public gtdfTableDef  As TableDef    'Public tabledef used by frmTblStruct
'Public database variables
Public gsDataType       As String   'data backend = connect string
                                    'for everything accept Access
Public gsDBName         As String   'current database name
Public gsODBCDatasource As String   'Public odbc values
Public gsODBCDatabase   As String   '       "
Public gsODBCUserName   As String   '       "
Public gsODBCPassword   As String   '       "
Public gsODBCDriver     As String   '       "
Public gsODBCServer     As String   '       "
Public gsTblName        As String   '
Public glQueryTimeout   As Long     '
Public glLoginTimeout   As Long     '
Public gsTableDynaFilter As String  '
Public gnReadOnly       As Integer  'database readonly flag

'other Public vars
Public gsZoomData       As String   'pass info to the zoom form

'multi user variables
Public gnMURetryCnt     As Integer
Public gnMUDelay        As Integer
Public gnMULocking      As Integer  'flag for pessimistic or optimistic locking

'Public find values used to pass info between
'the dynaset form and find dialog
Public gbFindFailed     As Boolean
Public gsFindExpr       As String
Public gsFindOp         As String
Public gsFindField      As String
Public gnFindType       As Integer
Public gbFromTableView  As Boolean

'Public seek values used to pass info between
'the table form and find dialog
Public gsSeekOperator   As String
Public gsSeekValue      As String

'Public flags
Public gbDBChanged      As Boolean   '
Public gbTransPending   As Boolean   'used for transaction management
Public gbFromSQL        As Boolean   'source of sql statement was SQL form
Public gbAddTableFlag   As Boolean   'new or design designator
Public gbSettingDataCtl As Boolean   'used to reset data control props

'Public vars used in the Import Export Code
Public gImpDB As Database
Public gExpDB As Database
Public gExpTable As String

'data backend types used as the connect string
Public Const gsMSACCESS = "Microsoft Access"
Public Const gsDBASEIII = "Dbase III;"
Public Const gsDBASEIV = "Dbase IV;"
Public Const gsDBASE5 = "Dbase 5.0;"
Public Const gsFOXPRO20 = "FoxPro 2.0;"
Public Const gsFOXPRO25 = "FoxPro 2.5;"
Public Const gsFOXPRO26 = "FoxPro 2.6;"
Public Const gsFOXPRO30 = "FoxPro 3.0;"
Public Const gsPARADOX3X = "Paradox 3.X;"
Public Const gsPARADOX4X = "Paradox 4.X;"
Public Const gsPARADOX5X = "Paradox 5.X;"
Public Const gsBTRIEVE = "Btrieve;"
Public Const gsEXCEL30 = "Excel 3.0;"
Public Const gsEXCEL40 = "Excel 4.0;"
Public Const gsEXCEL50 = "Excel 5.0;"
Public Const gsTEXTFILES = "Text;"
Public Const gsSQLDB = "ODBC;"

'import/export data types
Public gnDataType As gnDataTypes
Public Enum gnDataTypes
  gnDT_NONE = -1
  gnDT_MSACCESS = 0
  gnDT_DBASEIV = 1
  gnDT_DBASEIII = 2
  gnDT_FOXPRO26 = 3
  gnDT_FOXPRO25 = 4
  gnDT_FOXPRO20 = 5
  gnDT_PARADOX4X = 6
  gnDT_PARADOX3X = 7
  gnDT_BTRIEVE = 8
  gnDT_EXCEL50 = 9
  gnDT_EXCEL40 = 10
  gnDT_EXCEL30 = 11
  gnDT_TEXTFILE = 12
  gnDT_SQLDB = 13
End Enum

'Public constants
Public Const APPNAME = "VisData6"
Public Const gsDEFAULT_DRIVER = "SQL Server"  'used for registerdatabase
Public Const gnEOF_ERR = 626                  '
Public Const gnFTBLS = 0                      '
Public Const gnFFLDS = 1                      '
Public Const gnFINDX = 2                      '
Public Const gnMAX_GRID_ROWS = 31999          '
Public Const gnMAX_MEMO_SIZE = 20000          '
Public Const gnGETCHUNK_CUTOFF = 50           '

Public Const gnFORM_DATACTL = 0               '
Public Const gnFORM_NODATACTL = 1             '
Public Const gnFORM_DATAGRID = 2              '

Public Const gnRS_TABLE = vbRSTypeTable
Public Const gnRS_DYNASET = vbRSTypeDynaset
Public Const gnRS_SNAPSHOT = vbRSTypeSnapShot
Public Const gnRS_PASSTHRU = 8

Public Const gnCTLARRAYHEIGHT = 340&          '
Public Const gnSCREEN = 0                     'used to center forms on screen
Public Const gnMDIFORM = 1                    'used to center forms on frmMDI

Public Const TABLE_STR = "Table"
Public Const ATTACHED_STR = "Attached"
Public Const QUERY_STR = "Query"
Public Const FIELD_STR = "Field"
Public Const FIELDS_STR = "Fields"
Public Const INDEX_STR = "Index"
Public Const INDEXES_STR = "Indexes"
Public Const PROPERTY_STR = "Property"
Public Const PROPERTIES_STR = "Properties"

Public Const APP_CATEGORY = "Microsoft Visual Basic AddIns"

Private Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Private Declare Function LoadStringA Lib "user32" (ByVal hInstance As Long, ByVal Wid As Long, ByVal lpBuffer As String, ByVal nBufferMax As Long) As Long
Private Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long

'LoadLibrary constants
Public Const LOAD_LIBRARY_AS_DATAFILE As Long = &H2

'GetLocaleInfo constants
Public Const LOCALE_SLANGUAGE = &H2
Public Const LOCALE_SABBREVLANGNAME = &H3


'------------------------------------------------------------
'this function returns the size of the field type
'passed in for use on the frmAddField form
'------------------------------------------------------------
Function SetFldProperties(rnType As Integer) As Integer
  'return field length
  Select Case rnType
    Case dbBoolean
      SetFldProperties = 1
    Case dbByte
      SetFldProperties = 1
    Case dbInteger
      SetFldProperties = 2
    Case dbLong
      SetFldProperties = 4
    Case dbCurrency
      SetFldProperties = 8
    Case dbSingle
      SetFldProperties = 4
    Case dbDouble
      SetFldProperties = 8
    Case dbDate
      SetFldProperties = 8
    Case dbText
      SetFldProperties = 50
    Case dbLongBinary
      SetFldProperties = 0
    Case dbMemo
      SetFldProperties = 0
  End Select
End Function

Sub main()
Dim Sty As Long
Dim ss As String * 20
    
    INIFile = App.Path + "\ѧϰӢ��.ini"
    Set frmMain = New frmMainMdi
    'ShowWindow frmMain.hwnd, SW_MAXIMIZE
    Sty = GetPrivateProfileString("ͼƬ", "����ͼƬ", "", ss, 20, INIFile)
    If Sty <> 0 And ss <> "" Then
       OptionsVal.Backmap = Left$(ss, Sty)
       frmMain.Picture = LoadPicture(Left$(ss, Sty))
    End If
    
    frmMain.Show
    Sty = GetWindowLong(frmMain.hwnd, GWL_STYLE)
    Sty = Sty Xor WS_MAXIMIZEBOX
    Sty = SetWindowLong(frmMain.hwnd, GWL_STYLE, Sty)

End Sub

'�˹���������:�ֽ��ַ���������ss(),�ָ���ΪSplitCode
Public Sub Split(Fld As Field, ss() As String, Optional SplitCode As String = ",")
Dim fs As String
Dim i As Long, k
       If Fld.Value <> vbNullString Then
          fs = Trim(Fld.Value)
       End If
       i = InStr(1, fs, SplitCode)
       While i <> 0
             ReDim Preserve ss(UBound(ss) + 1)
             ss(UBound(ss)) = Left$(fs, i - 1)
             fs = Right$(fs, Len(fs) - i)
             i = InStr(1, fs, SplitCode)
       Wend
       If Len(fs) <> 0 Then
          ReDim Preserve ss(UBound(ss) + 1)
          ss(UBound(ss)) = fs
       End If
End Sub

'�����ַ���
Public Sub SplitString(sString As String, ss() As String, Optional SplitCode As String = ",", Optional SplitStyle As SplitStyleenum = False, Optional Style As FindStyle = -1)
On Error Resume Next

Dim fs As String
Dim i As Long
Dim k As Long

       If sString <> vbNullString Then
          fs = Trim(sString)
       End If
       i = InStr(1, fs, SplitCode)
       While i <> 0
             ReDim Preserve ss(UBound(ss) + 1)
             ss(UBound(ss)) = Left$(fs, i - 1)
             If SplitStyle Then
                k = InStr(1, ss(UBound(ss)), ".")
                If (Not IsNull(k)) Or k <> 0 Then
                    ss(UBound(ss)) = Right$(ss(UBound(ss)), Len(ss(UBound(ss))) - k)
                End If
             End If
             Select Case Style
                    Case 0 'ͬ���
                         ss(UBound(ss)) = "*" & ss(UBound(ss)) & "*"
                    Case 1 '�����
                    
                    Case 2 '���ƴ�
                    
                    Case 3 '������
                    
                    Case FindStyle.��ֹ�õ��ظ��ַ���
                         For k = 1 To UBound(ss) - 1
                             If ss(k) = ss(UBound(ss)) Then
                                ReDim Preserve ss(UBound(ss) - 1)
                                Exit For
                             End If
                         Next k
             End Select
             fs = Right$(fs, Len(fs) - i)
             i = InStr(1, fs, SplitCode)
       Wend
       If Len(fs) <> 0 Then
          ReDim Preserve ss(UBound(ss) + 1)
          ss(UBound(ss)) = fs
             If SplitStyle Then
                k = InStr(1, ss(UBound(ss)), ".")
                If k <> 0 Then
                    ss(UBound(ss)) = Right$(ss(UBound(ss)), Len(ss(UBound(ss))) - k)
                End If
             End If
             Select Case Style
                    Case 0 'ͬ���
                         ss(UBound(ss)) = "*" & ss(UBound(ss)) & "*"
                    Case 1 '�����
                    
                    Case 2 '���ƴ�
                    
                    Case 3 '������
                    
                    Case 4
                         For k = 1 To UBound(ss) - 1
                             If ss(k) = ss(UBound(ss)) Then
                                ReDim Preserve ss(UBound(ss) - 1)
                                Exit For
                             End If
                         Next k
             End Select
          
       End If

End Sub

'��RString�е��ַ�����DString��,������cmbText��
Public Function InsertString(cmbText As Object, ByVal RString As String)
On Error Resume Next

Dim ss() As String, i, ss1() As String, Flag As Boolean, j, DString As String
ReDim ss(0)
ReDim ss1(0)
       If InStr(1, RString, ".") Then '�Ƚϴ�����"."��ʱ
          SplitString RString, ss, , SpS����붺��
       Else
          SplitString RString, ss
       End If
       
       
       For i = 1 To UBound(ss)
           Flag = True
           DString = cmbText
           SplitString DString, ss1
           For j = 1 To UBound(ss1)
               If ss(i) = ss1(j) Then
                  Flag = False
               End If
           Next j
           If Flag Then
              If Right$(cmbText, 1) = "," Then
                 cmbText = cmbText & ss(i)
              Else
                 cmbText = cmbText & "," & ss(i)
              End If
           End If
       Next i
       
       If cmbText = "" Then Exit Function
       
       If Left$(cmbText, 1) = "," Then 'ȥ��","��
          cmbText = Right$(cmbText, Len(cmbText) - 1)
       ElseIf Right$(cmbText, 1) = "," Then
          cmbText = Left$(cmbText, Len(cmbText) - 1)
       End If
End Function

'������������
Public Function Find(sString() As String, Optional Operater As String = "like", Optional Field As String = "����", Optional DateFlag As Boolean = False) As Recordset
'On Error Resume Next
Dim i, N
Dim sTmp As String
       N = UBound(sString)
       If DateFlag Then
          N = N - 1
       End If
       For i = 0 To N
           If sString(i) <> "" Then
              sTmp = sTmp & " or " & "(" & Field & " " & Operater & " " & "'" & sString(i) & "'" & ")"
           End If
       Next i
       If DateFlag Then
          sTmp = sTmp & " or " & "(" & "���� = " & "'" & sString(N + 1) & "')"
       End If
       If Left$(sTmp, 4) = " or " Then
          sTmp = Right$(sTmp, Len(sTmp) - 4)
       End If
       
       Set Find = Dbs.OpenRecordset("select * from " & Table & " where " & sTmp)
       
End Function

'��ʾ���ҽ������
Public Function ShowFind(Caption As String, Rst As Recordset)
On Error Resume Next

Dim fmBrow As frmBrow
       
       Set fmBrow = New frmBrow
       fmBrow.Show
       fmBrow.Caption = Caption
       frmMain.ActiveForm.InputRst Rst
       Set frmMain.ActiveForm.Data1.Recordset = frmMain.ActiveForm.Rst
       frmMain.ActiveForm.Data1.Caption = Rst(0).Value
       frmMain.ActiveForm.mnuPrev.Enabled = True
       frmMain.ActiveForm.SetFocus

End Function

Public Sub SameWord(Rst As Recordset)    '����ͬ���
Dim ss() As String

       ReDim ss(0)
       ss(0) = Rst("����").Value
       Split Rst("ͬ���"), ss, ","
       ShowFind "���ҵ� " & Rst("����").Value & " ��ͬ���", Find(ss)
       
End Sub

Public Sub DifferentWord(Rst As Recordset)  '���ҷ����
Dim ss() As String

       ReDim ss(0)
       'ss(0) = Rst("����").Value
       Split Rst("�����"), ss, ","
       ShowFind "���ҵ� " & Rst("����").Value & " �ķ����", Find(ss)
       
End Sub

Public Sub LikeWord(Rst As Recordset)  '���ƴ�
Dim ss() As String

       ReDim ss(0)
       ss(0) = Rst("����").Value
       Split Rst("���ƴ�"), ss, ","
       ShowFind "���ҵ� " & Rst("����").Value & " �����ƴ�", Find(ss)
       
End Sub

Public Sub RalationWord(Rst As Recordset)  '������
Dim ss() As String

       ReDim ss(0)
       ss(0) = Rst("����").Value
       Split Rst("������"), ss, ","
       ShowFind "���ҵ� " & Rst("����").Value & " �Ĺ�����", Find(ss)
       
End Sub

Public Sub Dateword(Optional Rst As Recordset = Nothing, Optional sString As String, Optional Caption As String)  '������ͬ�Ĵ�
Dim ss() As String

       ReDim ss(0)
       If Rst Is Nothing Then
          SplitString sString, ss
          ShowFind Caption, Find(ss, , "����", True)
       Else
          ss(0) = Rst("����").Value
          ShowFind "���ҵ��� " & Rst("����").Value & " ѧϰ�Ĵ�", Find(ss, "=", "����")
       End If
       
End Sub

Public Sub AllRalation(Rst As Recordset, Optional IfDate As Boolean = False)
On Error Resume Next

       Dim ss() As String
       ReDim ss(0)
       ss(0) = Rst("����").Value
       Split Rst("ͬ���"), ss, ","
       Split Rst("�����"), ss, ","
       Split Rst("���ƴ�"), ss, ","
       Split Rst("������"), ss, ","
       If IfDate Then
          ReDim Preserve ss(UBound(ss) + 1)
          ss(UBound(ss)) = Rst("����").Value
       End If
       ShowFind "���ҵ��� " & Rst("����").Value & " ����ϵ�Ĵ�", Find(ss, , , True)
End Sub


