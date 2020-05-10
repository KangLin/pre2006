VERSION 5.00
Begin VB.Form frmAddField 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "添加字段"
   ClientHeight    =   3735
   ClientLeft      =   2490
   ClientTop       =   2865
   ClientWidth     =   6120
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016117
   Icon            =   "Addfield.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3297.239
   ScaleMode       =   0  'User
   ScaleWidth      =   6054.501
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.OptionButton optVariable 
      Caption         =   "可变字段"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   2160
      Value           =   -1  'True
      Width           =   2379
   End
   Begin VB.OptionButton optFixedField 
      Caption         =   "固定字段"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   1920
      Width           =   2379
   End
   Begin VB.CheckBox chkAutoInc 
      Caption         =   "自动增加字段"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   2640
      Width           =   2379
   End
   Begin VB.CheckBox chkAllowZeroLen 
      Caption         =   "允许零长度"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   6
      Top             =   3000
      Width           =   2379
   End
   Begin VB.TextBox txtFieldName 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   2895
   End
   Begin VB.ComboBox cboFieldType 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      ItemData        =   "Addfield.frx":030A
      Left            =   120
      List            =   "Addfield.frx":030C
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   960
      Width           =   1695
   End
   Begin VB.TextBox txtFieldSize 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   120
      TabIndex        =   2
      Top             =   1560
      Width           =   1335
   End
   Begin VB.TextBox txtOrdinalPos 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   3120
      TabIndex        =   8
      Top             =   360
      Width           =   1335
   End
   Begin VB.TextBox txtValidationText 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   3120
      TabIndex        =   9
      Top             =   960
      Width           =   2895
   End
   Begin VB.TextBox txtValidationRule 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   3120
      TabIndex        =   10
      Top             =   1680
      Width           =   2895
   End
   Begin VB.TextBox txtDefaultValue 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   3120
      TabIndex        =   11
      Top             =   2280
      Width           =   2895
   End
   Begin VB.CheckBox chkRequired 
      Caption         =   "必要的"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   7
      Top             =   3360
      Width           =   2379
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定(&O)"
      Default         =   -1  'True
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3480
      MaskColor       =   &H00000000&
      TabIndex        =   12
      Top             =   2760
      Width           =   2175
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "关闭(&C)"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3480
      MaskColor       =   &H00000000&
      TabIndex        =   13
      Top             =   3240
      Width           =   2175
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   " 名称: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   0
      Left            =   120
      TabIndex        =   20
      Top             =   120
      Width           =   630
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   " 类型: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   2
      Left            =   120
      TabIndex        =   19
      Top             =   720
      Width           =   630
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   " 大小: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   3
      Left            =   120
      TabIndex        =   18
      Top             =   1320
      Width           =   630
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "顺序位置: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   4
      Left            =   3120
      TabIndex        =   17
      Top             =   120
      Width           =   900
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "验证文本: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   5
      Left            =   3120
      TabIndex        =   16
      Top             =   720
      Width           =   900
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "验证规则: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   6
      Left            =   3120
      TabIndex        =   15
      Top             =   1320
      Width           =   900
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "缺省值: "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Index           =   7
      Left            =   3120
      TabIndex        =   14
      Top             =   2040
      Width           =   720
   End
End
Attribute VB_Name = "frmAddField"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "添加字段"
Const BUTTON1 = "确定(&O)"
Const BUTTON2 = "关闭(&C)"
Const MSG1 = " 已经存在！"
'>>>>>>>>>>>>>>>>>>>>>>>>

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
'  If KeyCode = vbKeyF1 And Shift = 0 Then
'    DisplayTopic 2016117
'  End If
End Sub

Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdClose.Caption = BUTTON2

  cboFieldType.AddItem "Boolean"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbBoolean
  cboFieldType.AddItem "Byte"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbByte
  cboFieldType.AddItem "Integer"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbInteger
  cboFieldType.AddItem "Long"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbLong
  cboFieldType.AddItem "Currency"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbCurrency
  cboFieldType.AddItem "Single"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbSingle
  cboFieldType.AddItem "Double"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbDouble
  cboFieldType.AddItem "Date/Time"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbDate
  cboFieldType.AddItem "Text"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbText
  cboFieldType.AddItem "Binary"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbLongBinary
  cboFieldType.AddItem "Memo"
  cboFieldType.ItemData(cboFieldType.NewIndex) = dbMemo
  
  SetDefaults
  '需要禁止那些不用于非 Microsoft Access 表的控件
  If gsDataType <> gsMSACCESS Then
    optFixedField.Enabled = False
    chkAutoInc.Enabled = False
    optVariable.Enabled = False
    txtValidationText.Enabled = False
    txtValidationRule.Enabled = False
    txtDefaultValue.Enabled = False
    chkRequired.Enabled = False
    chkAllowZeroLen.Enabled = False
  End If
  
End Sub

Private Sub txtFieldName_Change()
  '只有“名称”（name）字段有内容时，才激活“确定”（OK）按钮
  cmdOK.Enabled = (Len(txtFieldName.Text) > 0)
End Sub

Private Sub cboFieldType_Click()
  Dim nFldType As Integer
  
  '调用函数设置字段的大小和类型
  txtFieldSize.Text = SetFldProperties(cboFieldType.ItemData(cboFieldType.ListIndex))
  txtFieldSize.Enabled = False

  nFldType = cboFieldType.ItemData(cboFieldType.ListIndex)
  
  '针对每个字段类型，使适当的控件工作
  If gsDataType <> gsMSACCESS Then
    If nFldType = dbText Then
      '允许输入字段长度
      txtFieldSize.Enabled = True
      'Access UI 的缺省字段大小
      txtFieldSize.Text = "50"
    End If
    '对 MDB 数据库仅做下面的部分
    Exit Sub
  End If
  
  If nFldType = dbText Then
    '允许输入字段长度
    txtFieldSize.Enabled = True
    'Access UI 的缺省字段大小
    txtFieldSize.Text = "50"
    '对 memo 和 text 有效
    chkAllowZeroLen.Enabled = True
    '仅对 text 有效
    optVariable.Enabled = True
    optFixedField.Enabled = True
    '关闭这些控件
    chkAutoInc.Enabled = False
    chkAutoInc.Value = vbUnchecked
  ElseIf nFldType = dbMemo Then
    '对 memo 和 text 有效
    chkAllowZeroLen.Enabled = True
    '关闭这些控件
    optVariable.Enabled = False
    optFixedField.Enabled = False
    chkAutoInc.Enabled = False
    '设置此值为0
    optVariable.Value = False
    optFixedField.Value = False
    chkAutoInc.Value = vbUnchecked
  ElseIf nFldType = dbLong Then
    '使这个控件可用，作为该类型字段的计数器
    chkAutoInc.Enabled = True
    '禁用这些控件
    chkAllowZeroLen.Enabled = False
    optVariable.Enabled = False
    optFixedField.Enabled = False
    '设置此值为0
    chkAllowZeroLen.Value = vbUnchecked
    optVariable.Value = False
    optFixedField.Value = False
  Else
    '对所有其他类型，禁用这些控件
    chkAllowZeroLen.Enabled = False
    optVariable.Enabled = False
    optFixedField.Enabled = False
    chkAutoInc.Enabled = False
    '设置此值为 0
    chkAllowZeroLen.Value = vbUnchecked
    optVariable.Value = False
    optFixedField.Value = False
    chkAutoInc.Value = vbUnchecked
  End If

End Sub

Private Sub cmdOK_Click()
  On Error GoTo OkayErr
  Dim fld As Field     '本地字段结构
  Dim i As Integer

  '得到一个新字段对象
  Set fld = gtdfTableDef.CreateField()
  'Set fld = frmBrow.Data1.Recordset.Fields(1)
  '填充字段结构
  With fld
    .Name = txtFieldName.Text
    .Type = cboFieldType.ItemData(cboFieldType.ListIndex)
    .Size = txtFieldSize.Text
    If Len(txtOrdinalPos.Text) > 0 Then .OrdinalPosition = txtOrdinalPos.Text
    
    If gsDataType = gsMSACCESS Then
      .Required = IIf(chkRequired.Value = vbChecked, -1, 0)
      If .Type = dbText Then
        '这个仅用于 text
        .AllowZeroLength = IIf(chkAllowZeroLen.Value = vbChecked, -1, 0)
      End If
      If optFixedField.Value Then
        .Attributes = .Attributes Or dbFixedField
      End If
      If .Type = dbLong Then
        '仅用于 long 类型
        If chkAutoInc.Value = vbChecked Then
          .Attributes = .Attributes Or dbAutoIncrField
        End If
      End If
      If optVariable.Value Then
        .Attributes = .Attributes Or dbVariableField
      End If
      .ValidationText = txtValidationText.Text
      .ValidationRule = txtValidationRule.Text
      .DefaultValue = txtDefaultValue.Text
    End If
  End With
  
  '检查有无重复
  'If ObjectExists(gtdfTableDef.Fields, fld.Name) Then
  '  MsgBox "'" & fld.Name & "'" & MSG1
  '  txtFieldName.SelStart = 0
  '  txtFieldName.SelLength = Len(txtFieldName.Text)
  '  txtFieldName.SetFocus
  '  Exit Sub
  'End If
  
  '试着追加字段
  'gtdfTableDef.Fields.Append  fld
  'frmBrow.Data1.Recordset.Fields.Append fld
  Rst.Fields.Append fld
  
  '一定已经成功了，所以...
  '在列表中添加这一项
  'frmTblStruct.lstFields.AddItem txtFieldName
  '使新项目开始工作
  'frmTblStruct.lstFields.ListIndex = frmTblStruct.lstFields.NewIndex
  
  
  '需要的话，使“添加表”按钮可用
  'If frmTblStruct.cmdAddTable.Visible Then
  '  frmTblStruct.cmdAddTable.Enabled = True
  'End If
  
  '清除名称并允许输入下一个
  SetDefaults
  txtFieldName.SetFocus
  Exit Sub

OkayErr:
  'ShowError
End Sub

Private Sub SetDefaults()
  txtFieldName.Text = vbNullString
  If gsDataType = gsMSACCESS Then
    optFixedField.Value = False
    chkAutoInc.Value = vbUnchecked
    optVariable.Value = True
    chkRequired.Value = vbUnchecked
    chkAllowZeroLen.Value = vbChecked
  Else
    optFixedField.Value = False
    chkAutoInc.Value = 2
    optVariable.Value = False
    chkRequired.Value = 2
    chkAllowZeroLen.Value = 2
  End If
  cboFieldType.ListIndex = 8             '缺省为 text
  txtFieldSize.Text = 50                 '缺省为 50
  txtValidationText.Text = vbNullString
  txtValidationRule.Text = vbNullString
  txtDefaultValue.Text = vbNullString
End Sub
