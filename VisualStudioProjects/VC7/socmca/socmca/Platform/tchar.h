#ifndef __TCHAR_H_KL__
#define __TCHAR_H_KL__

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt

typedef const wchar_t * LPCTSTR;
typedef wchar_t TCHAR;

#define _T(x) L##x
#define _tprintf wprintf

#else   /* UNICODE */               // r_winnt

typedef const char * LPCTSTR;
typedef char TCHAR;

#define _T(x) x
#define _tprintf printf

#endif /* UNICODE */                // r_winnt

typedef const char * LPCSTR;
typedef unsigned long DWORD;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif // ½áÊø #ifdef __TCHAR_H_KL__
