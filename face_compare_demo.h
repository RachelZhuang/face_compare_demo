
// face_compare_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cface_compare_demoApp: 
// �йش����ʵ�֣������ face_compare_demo.cpp
//

class Cface_compare_demoApp : public CWinApp
{
public:
	Cface_compare_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cface_compare_demoApp theApp;