Imports System
Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics
Imports Microsoft.VisualStudio.VCProject
Imports Microsoft.VisualStudio.VCProjectEngine
Imports Microsoft.VisualStudio.VCCodeModel

Public Module Module1

    'Text属性与Insert方法的区别
    Sub TextAndInsert()
        Dim doc As Document
        Dim sel As TextSelection
        doc = DTE.ActiveDocument
        sel = doc.Selection
        sel.Insert("a")

    End Sub

    Sub pro()
        Dim dir As VCDirectories
        Dim pro As VCProject
        Dim plat As VCPlatform
        Dim en As Microsoft.VisualStudio.VCProjectEngine.VCPlatform

        pro = DTE.Solution.Projects.Item(1).Object
        Debug.WriteLine(DTE.Solution.Projects.Item(1).Kind)
        Debug.WriteLine(pro.VCProjectEngine)
        Debug.WriteLine(pro.Name)
        Debug.WriteLine(pro.VCProjectEngine.platforms.item(1).includedirectories())

        Debug.WriteLine(dir.IncludeDirectories)


    End Sub

    Sub GetIncludeDirectoriesOnSolution()
        Dim prj As VCProject
        Dim cfgs, tools As IVCCollection
        Dim cfg As VCConfiguration
        Dim p As VCPlatform
        Dim x As String
        prj = DTE.Solution.Projects.Item(1).Object '从工程得到 VCProject
        p = prj.Platforms(1)
        x = p.IncludeDirectories
        p.IncludeDirectories = x + ";something"
        MsgBox(p.IncludeDirectories)
    End Sub

    Sub GetIncludeDirectories()
        Dim pros As Projects
        Dim eng As Microsoft.VisualStudio.VCProjectEngine.VCProjectEngine
        Dim plat As Microsoft.VisualStudio.VCProjectEngine.VCPlatform
        Dim d As VCDirectories
        pros = DTE.GetObject("VCProjects")                         '直接从 DTE 得到 VCProject
        eng = pros.Properties.Item("VCProjectEngine").Object
        For Each plat In eng.Platforms
            Debug.WriteLine(plat.Name)
            Debug.WriteLine(plat.IncludeDirectories)                '得到头文件目录
            Debug.WriteLine(plat.Evaluate(plat.IncludeDirectories)) '取值
        Next
    End Sub

    Sub test3()
        Dim prjs As Projects
        Dim msg As String
        Dim prop As [Property]
        Try
            prjs = DTE.Solution.Projects
            msg = "There are " + prjs.Count.ToString() + " projects in this collection."
            msg = msg + "\nThe application containing this Projects collection: " + prjs.DTE.Name
            msg = msg + "\nThe parent object of the Projects collection: " + prjs.Parent.Name
            msg = msg + "\nThe GUID representing the Projects type: " + prjs.Kind
            If Not prjs.Properties Is Nothing Then
                msg = msg + "\nProperties:"
                For Each prop In prjs.Properties
                    msg = msg + "\n   " + prop.Name
                Next
            End If
            MsgBox(msg)
        Catch e As Exception
            MsgBox(e.Message)
        End Try
    End Sub

    Sub GetFunctions()
        Dim vcCM As VCCodeModel
        Dim vcFunc As VCCodeFunction
        vcCM = DTE.Solution.Item(1).CodeModel
        For Each vcFunc In vcCM.Functions
            Debug.WriteLine(vcFunc.DisplayName)
        Next
        vcFunc = vcCM.Functions.Item("DllCanUnloadNow")
        Debug.WriteLine(vcFunc.Name)
    End Sub

End Module

