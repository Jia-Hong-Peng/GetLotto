
// GetLotto.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CGetLottoApp: 
// �аѾ\��@�����O�� GetLotto.cpp
//

class CGetLottoApp : public CWinApp
{
public:
	CGetLottoApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CGetLottoApp theApp;