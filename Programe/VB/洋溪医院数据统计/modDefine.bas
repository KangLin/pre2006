Attribute VB_Name = "modDefine"
'功能:数据定义
'作者:康林
'时间:2005年6月

Option Explicit

Public Enum Enum_Postion
       TopLeft
       TopCenter
       TopRight
       BottomLeft
       BottomCenter
       BottomRight
End Enum

Public Type PrintParameter '打印设置
       m_szTitle As String
       m_PosTitle As Enum_Postion
       m_szHead As String
       m_PosHead As Enum_Postion
       m_bPageNo As Boolean '是否打印页号
       m_PosPageNo As Enum_Postion '页号位置
       m_iPageNumber As Integer '页数
       m_HeightBetwwenPage As Single   '两页之间的距离
       m_iPrintNumber As Integer '打印份数
       m_TopBorder As Single '上边距
       m_LeftBorder As Single '左边距
       m_RightBorder As Single '右边距
       m_BottomBorder As Single '下边距
       m_WidthBorder As Single '打印区域高度
       m_HeightBorder As Single '打印区域宽度
       m_Width As Single '纸张宽度
       m_Height As Single '纸张高度
End Type

Public Declare Function StretchBlt Lib "gdi32" (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal nSrcWidth As Long, ByVal nSrcHeight As Long, ByVal dwRop As Long) As Long
Public Const SRCCOPY = &HCC0020 ' (DWORD) dest = source

Public g_Para As PrintParameter
