VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.UserControl ctrClient 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   3600
   ScaleWidth      =   4800
   Begin MSWinsockLib.Winsock sckDataClinet 
      Left            =   0
      Top             =   840
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock sckCmdClient 
      Left            =   840
      Top             =   0
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "ctrClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*****************************************************************************
'           客      户     端     用     户    控    件
'                          设 计:  康 林
'一个控件只处理一个通讯.
'*****************************************************************************
Option Explicit

Public Function fSendCommand(strCommand As String)
With sckCmdClient
     .RemoteHost = "127.0.0.1"
     .RemotePort = 1976
     .Connect
     .SendData strCommand
End With
End Function


