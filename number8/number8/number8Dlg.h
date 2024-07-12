
// number8Dlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include "Drawer.h"
#include <math.h>


// Диалоговое окно Cnumber8Dlg
class Cnumber8Dlg : public CDialogEx
{
// Создание
public:
	Cnumber8Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMBER8_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double N;
	double fd;
	double Nsin;
	int p;
	vector <double> Fsin;
	vector <double> Fisin;
	vector <double> Sign;
	
	vector <double> keys;
	vector <double> sig;
	vector <double> Sred;
	vector <double> SredTeor;
	vector <double> stand;
	double rx[10000];
	double rxm[10000];
	double sumS[100];
	double sumSS[100];

	double a[10000];
	double u[10000];
	double v[10000];
	double sigma[10000];
	/*
	double* rx;
	double* a;
	double* u;
	double* v;
	double* sigma;
	*/
	double R[100][100];
	
	
	Drawer
		graph1,
		graph2;
	double ymin, ymax;
	double FindMin(vector<double> data, int N);
	double FindMax(vector<double> data, int N);
	void svd(int m_m, int n_n, double* a, double* u, double* v, double* sigma);
	void CreateSignal();
	afx_msg void OnBnClickedButton1();
	double eps;
	int NNsin;
	double alpha;
};
