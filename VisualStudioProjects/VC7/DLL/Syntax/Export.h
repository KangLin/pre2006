
#pragma once

#include "CSyntax.h"

extern "C" BOOL WINAPI ShowVersion();
extern "C" BOOL WINAPI ShowHelp();
extern "C" int WINAPI GetRelativePath(BSTR* lpszDes = NULL, BSTR lpszSou = NULL, BOOL bClipboard = TRUE);
extern "C" LONG GetDLLPath(BSTR* pszPath);
extern "C" LONG PathRelativePath(BSTR* pszPath,
                                   BSTR pszFrom,
                                   DWORD dwAttrFrom,
                                   BSTR pszTo,
                                   DWORD dwAttrTo
                                   );
extern "C" LONG FullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn, LPCTSTR lpszCurPath);
extern "C" LONG GetIncludeFile(LPTSTR lpszFile,LPCTSTR lpszInFile);