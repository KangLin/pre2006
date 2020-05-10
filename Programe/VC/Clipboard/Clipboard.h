#pragma once

class CClipboard
{
public:
    CClipboard(void);
    ~CClipboard(void);
    // Çå¿Õµ±Ç°¼ôÇÐ°å
    BOOL Empty(void);
    BOOL Open();
    BOOL Close();
    BOOL SetData(LPVOID lpData, int iLen, UINT uFormat = CF_TEXT);
    BOOL SetData(LPCTSTR lpszData);
};
