
// video_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cvideo_mfcApp: 
// �йش����ʵ�֣������ video_mfc.cpp
//

class Cvideo_mfcApp : public CWinApp
{
public:
	Cvideo_mfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cvideo_mfcApp theApp;