#ifndef __KEYINPUT_H__
#define __KEYINPUT_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // ���� #ifdef __cplusplus

void __stdcall Show();
BOOL __stdcall Init(EnvDTE::_DTE * pDTE);

#ifdef __cplusplus
}
#endif // ���� #ifdef __cplusplus

#endif // ���� #ifdef __KEYINPUT_H__