VERSION 5.00
Begin {C62A69F0-16DC-11CE-9E98-00AA00574A4F} UserForm1 
   Caption         =   "UserForm1"
   ClientHeight    =   3120
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4710
   OleObjectBlob   =   "UserForm1.frx":0000
   StartUpPosition =   1  '所有者中心
End
Attribute VB_Name = "UserForm1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub CommandButton1_Click()
InsertWebPart False
Unload Me
End Sub

Private Sub CommandButton2_Click()
Unload Me
End Sub

Public Sub InsertWebPart(b As Boolean)

    Dim strPageDirective As String
    Dim strRegisterDirective As String
    Dim strWebPart As String
    Dim objWebPart As FPHTMLWebPartElement

    Dim szID As String, szShowText As String
    szID = txtID.Text
    If b Then
        szShowText = ActiveDocument.activeElement.innerText ' txt.Text
    Else
        szShowText = txt.Text
    End If
    strWebPart = "<p><span class=""ShowLink"" onclick=""Call Show(" & szID & ")"" > " & szShowText & "</span>"
    strWebPart = strWebPart & vbCrLf & "<table class=""TableStyle"" id=""" & szID & """ style=""display:none"">"
    strWebPart = strWebPart & vbCrLf & vbTab & "<tr><td>" & vbCrLf & vbCrLf & vbTab & "</td></tr>" & vbCrLf & "</table></p>"
    
    'ActiveDocument.body.insertAdjacentHTML "beforeEnd", strWebPart
    
    ActiveDocument.activeElement.insertAdjacentHTML "afterEnd", strWebPart

End Sub


Public Sub InShow()
UserForm1.Show
End Sub

Private Sub CommandButton3_Click()
InsertWebPart True
Unload Me
End Sub

Private Sub UserForm_Click()

End Sub
