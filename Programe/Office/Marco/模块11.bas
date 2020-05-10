Attribute VB_Name = "Ä£¿é11"
Public Sub Show()
'Attribute Show.VB_ProcData.VB_Invoke_Func = "w\n14"
UserForm1.Show
End Sub


Sub AddModifiedDateToDocument(objDoc As FPHTMLDocument, strFont As String, _
        strSize As String, strColor As String)
    Dim objFont As FPHTMLFontElement
    
    objDoc.body.insertAdjacentHTML where:="beforeEnd", _
        HTML:="<p><font id=""modifiedon""></font></p>"
    
    Set objFont = objDoc.body.all.tags("font").Item("modifiedon")
    
    objFont.insertAdjacentText where:="beforeEnd", Text:="Last modified on: " _
        & objDoc.fileModifiedDate
    
    With objFont
        .face = strFont
        .Size = strSize
        .Color = strColor
    End With
End Sub
