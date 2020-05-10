// BinaryTree.h: interface for the CBinaryTree class.
//
//////////////////////////////////////////////////////////////////////
/*
 *
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

#if !defined(AFX_BINARYTREE_H__4E140191_3CD1_4A65_ACC0_6A6BBACE25A2__INCLUDED_)
#define AFX_BINARYTREE_H__4E140191_3CD1_4A65_ACC0_6A6BBACE25A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofBase.h"

class CAsyncSocket;

class CBinaryTree : protected CSpoofBase
{
public:
	//Thread safety methods
	void setThreadSafety(BOOL bSafety);

	//Delete a node
	void deleteNode(int iID);

	//Get a node
	CBinaryTree* getNode(int iID);

	//Create a new node
	CBinaryTree* newNode(int iID);

	//Get data in the current node
	CAsyncSocket* getData();

	//Set the data in the current node
	void setData(CAsyncSocket* vData);

	//ctor and dtor
	CBinaryTree();
	virtual ~CBinaryTree();
private:
	//Thread safety indicator
	BOOL m_ThreadSafe;
	BOOL m_LockedWrite;
	BOOL m_Locked;

	//Thread safety state checkers
	BOOL isLockedWrite();
	void LockWrite();
	void UnlockWrite();
	BOOL isLocked();
	void Unlock();
	void Lock();

	//Get/Set the ID of the node
	int getID();
	void setID(int iID);
	
	//The actual ID
	int m_ID;

	//Our data
	CAsyncSocket* m_Data;

	//Left and right childrens
	CBinaryTree* m_Right;
	CBinaryTree* m_Left;
};

#endif // !defined(AFX_BINARYTREE_H__4E140191_3CD1_4A65_ACC0_6A6BBACE25A2__INCLUDED_)
