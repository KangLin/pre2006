Attribute VB_Name = "modDefine"
'����:���ݶ���
'����:����
'ʱ��:2005��6��

Option Explicit

Public Enum Enum_Postion
       TopLeft
       TopCenter
       TopRight
       BottomLeft
       BottomCenter
       BottomRight
End Enum

Public Type PrintParameter '��ӡ����
       m_szTitle As String
       m_PosTitle As Enum_Postion
       m_szHead As String
       m_PosHead As Enum_Postion
       m_bPageNo As Boolean '�Ƿ��ӡҳ��
       m_PosPageNo As Enum_Postion 'ҳ��λ��
       m_iPageNumber As Integer 'ҳ��
       m_HeightBetwwenPage As Single   '��ҳ֮��ľ���
       m_iPrintNumber As Integer '��ӡ����
       m_TopBorder As Single '�ϱ߾�
       m_LeftBorder As Single '��߾�
       m_RightBorder As Single '�ұ߾�
       m_BottomBorder As Single '�±߾�
       m_WidthBorder As Single '��ӡ����߶�
       m_HeightBorder As Single '��ӡ������
       m_Width As Single 'ֽ�ſ��
       m_Height As Single 'ֽ�Ÿ߶�
End Type

Public Declare Function StretchBlt Lib "gdi32" (ByVal hdc As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal nSrcWidth As Long, ByVal nSrcHeight As Long, ByVal dwRop As Long) As Long
Public Const SRCCOPY = &HCC0020 ' (DWORD) dest = source

Public g_Para As PrintParameter
