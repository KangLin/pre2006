
从vs2003升级到VS2005，请看：
ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.en/dv_extcore/html/e518a67e-c214-4099-a2c1-2f8a827834dc.htm
ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.en/dv_extcore/html/690fa876-3952-4f89-84b5-77ba19d74d92.htm

========================================================================
    MICROSOFT 基础类库 : Syntax 项目概况
========================================================================

功能：完成C的语法分析的项目。在本目录中还有《微软开发环境扩展工具集》的帮助文档与技术文档。

应用程序向导已为您创建了此 Syntax DLL。此 DLL 不仅
说明了使用 Microsoft 基础类的基础，而且
也是编写 DLL 的起点。

此文件包含组成 Syntax DLL
的每个文件的内容摘要。

Syntax.vcproj
    这是用应用程序向导生成的 VC++ 项目的主项目文件。
    它包含有关生成此文件的 Visual C++ 版本的信息，以及
    有关使用应用程序向导选择的
    平台、配置和项目功能的信息。

Syntax.h
    这是 DLL 的主头文件。它声明了
    CSyntaxApp 类。

Syntax.cpp
    这是主 DLL 源文件。它包含了类 CSyntaxApp。
    它还包含了需要 inproc 服务器具有的 OLE 入口点。
Syntax.idl
    此文件包含 DLL
    类型库的对象描述语言源代码。
Syntax.rc
    这是程序使用的所有 Microsoft Windows 资源的列表。
    它包含存储在 RES 子目录下的图标、位图和光标。
    此文件可在 Microsoft Visual C++ 中直接编辑。
    

res\Syntax.rc2
    此文件包含不由 Microsoft 
    Visual C++ 编辑的资源。您应将不能由
    资源编辑器编辑的所有资源放置在此文件中。

Syntax.def
    此文件包含有关运行 Microsoft Windows 
    所需的 DLL 的信息。
    它定义此 DLL 的名称和说明等参数。
    它还从此 DLL 导出函数。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h、StdAfx.cpp
    这些文件用于生成名为 Syntax.pch
    的预编译头(PCH)文件以及名为 StdAfx.obj 的预编译类型文件。

Resource.h
    这是标准的头文件，它定义了新的资源 ID。
    Microsoft Visual C++ 读取和更新此文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用 "TODO:" 注释指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////

