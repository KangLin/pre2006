#ifndef __SHOW_HPP__
#define __SHOW_HPP__
#pragma once

/////////////////////////////////////////////////////////////////////////////

class CShow : public CObject
{
public: 
    CShow();                                     //--缺省构造函数。
    virtual ~CShow();                            //--析构函数。

public:
    virtual void Serialize(CArchive& ar);        //--序列化函数，将对象数据定入文档或从文档载入。
    CString CreateNewObj(CString Name, int Age); //--新建一个对象


protected:
    CString    mName; //RW 小猫的名字。
	int        mAge;  //RW 小猫的年龄。
	CString    mAddr; //R  小猫的家庭地址。
	CDocument* mpDoc; //RW 文档指针。
	CFile      mFile; //R  小猫的文件。

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
    CString GetName() const;                     //--返回小猫的名字。
    void SetName(const CString& Name);           //--设置小猫的名字。
    int GetAge() const;                          //--返回小猫的年龄。
    void SetAge(int Age);                        //--设置小猫的年龄。
    CString GetAddr() const;                     //--返回小猫的家庭地址。
    CDocument* GetDoc();                         //--返回文档指针。
    void SetDoc(CDocument* Doc);                 //--设置文档指针。
    CFile* GetFile();                            //--返回小猫的文件。

};

#include "Show.inl"
#endif