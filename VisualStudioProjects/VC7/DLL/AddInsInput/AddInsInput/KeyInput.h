#ifndef __KEYINPUT_H__
#define __KEYINPUT_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // ½áÊø #ifdef __cplusplus

int AddBracket(TCHAR c, EnvDTE::TextSelection * pSel);
int AddIncludeFile(TCHAR c, EnvDTE::TextSelection * pSel);

#ifdef __cplusplus
}
#endif // ½áÊø #ifdef __cplusplus

#endif // ½áÊø #ifdef __KEYINPUT_H__