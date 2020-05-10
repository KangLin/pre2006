#ifndef __SHOW_HPP__
#define __SHOW_HPP__
#pragma once

/////////////////////////////////////////////////////////////////////////////

class CShow : public CObject
{
public: 
    CShow();                                     //--ȱʡ���캯����
    virtual ~CShow();                            //--����������

public:
    virtual void Serialize(CArchive& ar);        //--���л����������������ݶ����ĵ�����ĵ����롣
    CString CreateNewObj(CString Name, int Age); //--�½�һ������


protected:
    CString    mName; //RW Сè�����֡�
	int        mAge;  //RW Сè�����䡣
	CString    mAddr; //R  Сè�ļ�ͥ��ַ��
	CDocument* mpDoc; //RW �ĵ�ָ�롣
	CFile      mFile; //R  Сè���ļ���

private:



/////////////////////////////////////////////////////////////////////////////
DECLARE_SERIAL(CShow)

#ifdef _DEBUG
public:
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

//!begin get/set
public:
    CString GetName() const;                     //--����Сè�����֡�
    void SetName(const CString& Name);           //--����Сè�����֡�
    int GetAge() const;                          //--����Сè�����䡣
    void SetAge(int Age);                        //--����Сè�����䡣
    CString GetAddr() const;                     //--����Сè�ļ�ͥ��ַ��
    CDocument* GetDoc();                         //--�����ĵ�ָ�롣
    void SetDoc(CDocument* Doc);                 //--�����ĵ�ָ�롣
    CFile* GetFile();                            //--����Сè���ļ���

};

#include "Show.inl"
#endif