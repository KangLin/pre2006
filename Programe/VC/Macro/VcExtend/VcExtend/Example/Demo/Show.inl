

inline CString CShow::GetName() const
{
    return mName;
}

inline void CShow::SetName(const CString& Name)
{
    mName = Name;
}

inline int CShow::GetAge() const
{
    return mAge;
}

inline void CShow::SetAge(int Age)
{
    mAge = Age;
}

inline CString CShow::GetAddr() const
{
    return mAddr;
}

inline CDocument* CShow::GetDoc()
{
    return mpDoc;
}

inline void CShow::SetDoc(CDocument* Doc)
{
    mpDoc = Doc;
}

inline CFile* CShow::GetFile()
{
    return &mFile;
}
