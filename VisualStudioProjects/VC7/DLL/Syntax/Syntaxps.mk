
Syntaxps.dll: dlldata.obj Syntax_p.obj Syntax_i.obj
	link /dll /out:Syntaxps.dll /def:Syntaxps.def /entry:DllMain dlldata.obj Syntax_p.obj Syntax_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<
# _WIN32_WINNT=0x0500 is for Win2000, change it to 0x0400 for NT4 or Win95 with DCOM

clean:
	@del Syntaxps.dll
	@del Syntaxps.lib
	@del Syntaxps.exp
	@del dlldata.obj
	@del Syntax_p.obj
	@del Syntax_i.obj
