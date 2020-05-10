VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public WithEvents m_sckCmdClient As Winsock
Attribute m_sckCmdClient.VB_VarHelpID = -1

Public Function fSendCommand(sckCmdClient As Winsock, sCmdCommand As String)
sckCmdClient.SendData sCmdCommand
End Function

Private Sub sckCmdClient_DataArrival(ByVal bytesTotal As Long)
Dim s As String
sckCmdClient.GetData s
Debug.Print s
End Sub

