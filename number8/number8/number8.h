
// number8.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Cnumber8App:
// Сведения о реализации этого класса: number8.cpp
//

class Cnumber8App : public CWinApp
{
public:
	Cnumber8App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Cnumber8App theApp;
