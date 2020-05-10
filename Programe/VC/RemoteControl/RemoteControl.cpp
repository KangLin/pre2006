// RemoteControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RemoteControl.h"
#include "FileSystem\FileSystem.h"

using namespace std;
int pd(LPCTSTR lpszFileName, void * para)
{
	cout << "Ä¿Â¼£º" << lpszFileName << endl;
	return 1;
}

int pf(LPCTSTR lpszFileName, void * para)
{
	cout << "ÎÄ¼þ£º" << lpszFileName << endl;
	return 1;
}

int main(int argc, char * argv[])
{
	 
	CFileSystem fs;

	string szpath="D:\\Programe\\VC\\RemoteControl\\a";
	fs.DeleteDirTree(szpath.c_str());

	return 0;
}


