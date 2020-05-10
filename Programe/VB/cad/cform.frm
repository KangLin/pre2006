VERSION 5.00
Begin VB.Form FTool 
   BorderStyle     =   0  'None
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4680
   LinkTopic       =   "cform"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   Visible         =   0   'False
End
Attribute VB_Name = "FTool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
Dim ctr As control
For Each ctr In Me
    If TypeName(ctr) = "Toolbar" Then
       With Me
            .Width = ctr.With
            .Height = ctr.Height
       End With
    End If
Next
End Sub

Private Sub Form_LostFocus()
        Unload Me
End Sub
