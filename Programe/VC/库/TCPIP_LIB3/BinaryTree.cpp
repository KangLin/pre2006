// BinaryTree.cpp: implementation of the CBinaryTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinaryTree.h"
#include "AsyncSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CBinaryTree_LOGNAME "CBinaryTree"

CBinaryTree::CBinaryTree() : CSpoofBase()
{
	try
	{
		SetName(CBinaryTree_LOGNAME);

		//Null all
		m_ID=0;
		m_Right=NULL;
		m_Left=NULL;
		m_Data=NULL;

		//Not locked
		Unlock();
		UnlockWrite();

		//And thread safe
		setThreadSafety(TRUE);
	}
	ERROR_HANDLER("CBinaryTree")
}

CBinaryTree::~CBinaryTree()
{
	try
	{
		if (m_Data)
			delete m_Data;

		if (m_Right)
			delete m_Right;

		if (m_Left)
			delete m_Left;
	}
	ERROR_HANDLER("~CBinaryTree")
}

void CBinaryTree::setData(CAsyncSocket* vData)
{
	try
	{
		m_Data=vData;
	}
	ERROR_HANDLER("setData")
}

CAsyncSocket* CBinaryTree::getData()
{
	return m_Data;
}

CBinaryTree* CBinaryTree::newNode(int iID)
{
	try
	{
		//Return value
		CBinaryTree* retVal;

		//First check if node is empty ?
		while (isLockedWrite())
			;

		//Lock
		Lock();

		if (!m_ID)
		{
			//Lock write
			LockWrite();

			//Set the ID
			setID(iID);

			//Unlock write
			UnlockWrite();

			retVal=this;
		}
		else if (iID>m_ID)
			if (m_Right)
			{
				//Unlock read
				Unlock();
				retVal=m_Right->newNode(iID);
			}
			else
			{
				//Lock for write

				LockWrite();

				//Set the value
				m_Right=new CBinaryTree;
				m_Right->setID(iID);
				retVal=m_Right;

				//Unlock write
				UnlockWrite();
			}
		else if (iID<m_ID)
			if (m_Left)
			{
				//Unlock read
				Unlock();
				retVal=m_Left->newNode(iID);
			}
			else
			{
				//Lock write
				LockWrite();

				//Set the value
				m_Left=new CBinaryTree;
				m_Left->setID(iID);
				retVal=m_Left;

				//Unlock write
				UnlockWrite();

			}
		else
			//we are the node
			retVal=this;

		//Unlock read
		Unlock();

		//Return the value
		return retVal;
	}
	ERROR_HANDLER_RETURN("newNode",NULL)
}

CBinaryTree* CBinaryTree::getNode(int iID)
{
	try
	{
		//While not locked for write
		while (isLockedWrite())
			;

		//Lock for read
		Lock();

		//Return value
		CBinaryTree* retVal;

		if (!m_ID)
			retVal=NULL;
		else if (iID==m_ID)
			retVal=this;
		else if (iID>m_ID)
			if (m_Right)
			{
				//Unlock it
				Unlock();
				retVal=m_Right->getNode(iID);
			}
			else
				//Nothing
				retVal=NULL;
		else if (m_Left)
		{
			//Unlock it
			Unlock();
			retVal=m_Left->getNode(iID);
		}
		else
			//Nothing
			retVal=NULL;

		//Unlock read
		Unlock();

		//Return the value
		return retVal;
	}
	ERROR_HANDLER_RETURN("getNode",NULL)
}

void CBinaryTree::deleteNode(int iID)
{
	try
	{
		//First get the node
		CBinaryTree* tmpNode;
		tmpNode=getNode(iID);

		//Only if not null
		if (tmpNode)
			tmpNode->setData(NULL);
	}
	ERROR_HANDLER("deleteNode")
}

void CBinaryTree::setID(int iID)
{
	m_ID=iID;
}

int CBinaryTree::getID()
{
	return m_ID;
}

void CBinaryTree::Lock()
{
	m_Locked=TRUE;
}

void CBinaryTree::Unlock()
{
	m_Locked=FALSE;
}

BOOL CBinaryTree::isLocked()
{
	return m_Locked && !m_ThreadSafe;
}

void CBinaryTree::UnlockWrite()
{
	m_LockedWrite=FALSE;
}

void CBinaryTree::LockWrite()
{
	m_LockedWrite=TRUE;
}

BOOL CBinaryTree::isLockedWrite()
{
	return m_LockedWrite && !m_ThreadSafe;
}

void CBinaryTree::setThreadSafety(BOOL bSafety)
{
	m_ThreadSafe=bSafety;
}
