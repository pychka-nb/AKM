
// number8Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "number8.h"
#include "number8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define Pi 3.1415926535

// Диалоговое окно Cnumber8Dlg



Cnumber8Dlg::Cnumber8Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMBER8_DIALOG, pParent)
	, N(1024)
	, fd(1)
	, Nsin(2)
	, p(50)
	, eps(0.05)
	, NNsin(10)
	, alpha(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cnumber8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, N);
	DDX_Text(pDX, IDC_EDIT2, fd);
	DDX_Text(pDX, IDC_EDIT3, Nsin);
	DDX_Text(pDX, IDC_EDIT4, p);
	DDX_Text(pDX, IDC_EDIT5, eps);
	DDX_Text(pDX, IDC_EDIT6, NNsin);
	DDX_Text(pDX, IDC_EDIT7, alpha);
}

BEGIN_MESSAGE_MAP(Cnumber8Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cnumber8Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений Cnumber8Dlg

BOOL Cnumber8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	graph1.Create(GetDlgItem(IDC_INPUT)->GetSafeHwnd());
	graph2.Create(GetDlgItem(IDC_OUTPUT)->GetSafeHwnd());

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Cnumber8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Cnumber8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*Ф-ция, вычисляющая предел графика*/
double Cnumber8Dlg::FindMin(vector <double> data, int N)
{
	double min = data[0];
	for (int i = 0; i < N; i++)
	{
		if (min > data[i])
			min = data[i];
	}
	return min;
}
/*Ф-ция, вычисляющая предел графика*/
double Cnumber8Dlg::FindMax(vector <double> data, int N)
{
	double max = data[0];
	for (int i = 0; i < N; i++)
	{
		if (max < data[i])
			max = data[i];
	}
	return max;
}
/*Ф-ция, генерирующая рандомное число*/
double Random()
{
	double a = 0;
	for (int i = 0; i < 12; i++)
		a += -1. + 2 * (double)rand() / RAND_MAX;
	return a;
}
/*Ф-ция, считающая сумму квадратов отсчётов сигнала*/
double Sum(vector <double> mas)
{
	double a = 0;
	for (int i = 0; i < mas.size(); i++)
		a += mas[i] * mas[i];
	return a;
}
void Cnumber8Dlg::CreateSignal()
{
	double a3, a4, aA, aF,aFi;//вспомогательные переменные для амплитуды и частоты;
	for (int i = 0; i < Nsin; i++) {
		aF = rand() / (2.0 * RAND_MAX);
		Fsin.push_back(aF);//вектор частот для каждой синусоиды
	}
	for (int i = 0; i < Nsin; i++) {
		aFi = 0;// (2.0 * Pi)* rand() / RAND_MAX;
		Fisin.push_back(aFi);//вектор частот для каждой синусоиды
	}
	for (int i = 0; i <= N; i++)
	{
		a3 = 0;
		for (int j = 0; j < Nsin; j++) {
			a3 += sin(2 * Pi * Fsin[j] * (i / fd)+Fisin[j]);
		}
		Sign.push_back(a3);
	}
	vector <double> n0;
	double Es;
	double En;
	double B;
	double Al = alpha / 100;
	for (int i = 0; i <= N; i++)
	{
		n0.push_back(Random());
	}
	Es = Sum(Sign);
	En = Sum(n0);
	B = sqrt(Al * Es / En);
	for (int i = 0; i <= N; i++)
	{
		Sign[i] += B * n0[i];
	}
	n0.clear();
	int i, j;
	for (i = 0; i < p; i++) {
		for (j = 0; j < N - i; j++) {
			rx[i] += Sign[i + j] * Sign[j];
		}
		int p1;
		p1 = N - i;
		rx[i] /= p1;
	}
	for (i = 0; i < p; i++) {
		for (j = 0; j < p; j++) {
			rxm[p*i+j] = rx[abs(i - j)];
		}
		//R[i][i] = 1.;

		//B[i] = rx[i + 1];
		//B[i] = 0.;
	}
}

void Cnumber8Dlg::svd(int m_m, int n_n, double* a, double* u, double* v, double* sigma)
{
	double thr = 1.E-4f, nul = 1.E-16f;
	int n, m, i, j, l, k, lort, iter, in, ll, kk;
	double alfa, betta, hamma, eta, t, cos0, sin0, buf, s;
	n = n_n;
	m = m_m;
	for (i = 0; i < n; i++)
	{
		in = i * n;
		for (j = 0; j < n; j++)
			if (i == j) v[in + j] = 1.;
			else v[in + j] = 0.;
	}
	for (i = 0; i < m; i++)
	{
		in = i * n;
		for (j = 0; j < n; j++)
		{
			u[in + j] = a[in + j];
		}
	}

	iter = 0;
	while (1)
	{
		lort = 0;
		iter++;
		for (l = 0; l < n - 1; l++)
			for (k = l + 1; k < n; k++)
			{
				alfa = 0.; betta = 0.; hamma = 0.;
				for (i = 0; i < m; i++)
				{
					in = i * n;
					ll = in + l;
					kk = in + k;
					alfa += u[ll] * u[ll];
					betta += u[kk] * u[kk];
					hamma += u[ll] * u[kk];
				}

				if (sqrt(alfa * betta) < nul)	continue;
				if (fabs(hamma) / sqrt(alfa * betta) < thr) continue;

				lort = 1;
				eta = (betta - alfa) / (2.f * hamma);
				t = (double)((eta / fabs(eta)) / (fabs(eta) + sqrt(1. + eta * eta)));
				cos0 = (double)(1. / sqrt(1. + t * t));
				sin0 = t * cos0;

				for (i = 0; i < m; i++)
				{
					in = i * n;
					buf = u[in + l] * cos0 - u[in + k] * sin0;
					u[in + k] = u[in + l] * sin0 + u[in + k] * cos0;
					u[in + l] = buf;

					if (i >= n) continue;
					buf = v[in + l] * cos0 - v[in + k] * sin0;
					v[in + k] = v[in + l] * sin0 + v[in + k] * cos0;
					v[in + l] = buf;
				}
			}

		if (!lort) break;
	}

	for (i = 0; i < n; i++)
	{
		s = 0.;
		for (j = 0; j < m; j++)	s += u[j * n + i] * u[j * n + i];
		s = (double)sqrt(s);
		sigma[i] = s;
		if (s < nul)	continue;
		for (j = 0; j < m; j++)	u[j * n + i] /= s;
	}
	//======= Sortirovka ==============
	for (i = 0; i < n - 1; i++)
		for (j = i; j < n; j++)
			if (sigma[i] < sigma[j])
			{
				s = sigma[i]; sigma[i] = sigma[j]; sigma[j] = s;
				for (k = 0; k < m; k++)
				{
					s = u[i + k * n]; u[i + k * n] = u[j + k * n]; u[j + k * n] = s;
				}
				for (k = 0; k < n; k++)
				{
					s = v[i + k * n]; v[i + k * n] = v[j + k * n]; v[j + k * n] = s;
				}
			}
			
	//return iter;
}


void Cnumber8Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	srand(time(NULL));
	UpdateData(TRUE);
	graph1.DrawW();
	graph2.DrawW();
	/*rx = new double[p * p];
	a = new double[p * p];
	u = new double[p * p];
	v = new double[p * p];
	sigma = new double[p * p];*/
	//graph2.DrawW();
	
	
	CreateSignal();
	svd(p, p, rxm, u, v, sigma);
	for (int i = 0; i < p; i++) {
		sig.push_back(sigma[i]);
	}
	for (int i = 0; i < p; i++)
	{
		keys.push_back(i / fd);
	}
	double xmax = (p - 1) / fd,
		ymax = FindMax(sig, p),
		ymin = FindMin(sig, p);
	graph1.DrawOne(sig, 0, xmax, ymin, ymax, keys);
	keys.clear();
	for (int i2 = 0; i2 <= NNsin; i2++) {
		double ind = 0;
		Sign.clear();
		Fsin.clear();
		Fisin.clear();
		Nsin = i2;
		for (int i1 = 0; i1 < 50; i1++) {
			ind = 0;
			CreateSignal();
			svd(p, p, rxm, u, v, sigma);
			for (int i = 0; i < p; i++) {
				if (ind == 0) {
					if (sigma[i] < eps) {
						ind++;	
						sumS[i2] += i;
						sumSS[i1] = i;
					}
				}
			}
		}
		double ss;
		ss = 0.;
		sumS[i2] /= 50;
		for (int i3 = 0; i3 < 50; i3++) {
			ss += (sumSS[i3] - sumS[i2]) * (sumSS[i3] - sumS[i2]);
		}
		ss = ss / 50.;
		ss = pow(ss, 0.5);
		stand.push_back(ss);
		
	}
	for (int i = 0; i <= NNsin; i++) { 
		Sred.push_back(sumS[i]);
		stand[i] = 1.96 * stand[i] / pow(50., 0.5);
		SredTeor.push_back(2 * i + 1);
	}

	for (int i = 0; i <=NNsin; i++)
	{
		keys.push_back(i / fd);
	}
	xmax = NNsin / fd;
	ymax = FindMax(SredTeor, NNsin+1);
	ymin = FindMin(Sred, NNsin+1);
	//graph2.DrawOne(Sred, 0, xmax, ymin, ymax, keys);
	graph2.DrawTwoRecovered(Sred, SredTeor,stand, 0, xmax, ymin, ymax, keys, keys);
	Sign.clear();
	keys.clear();
	sig.clear();
	Fsin.clear();
	Fisin.clear();
	Sred.clear();
	SredTeor.clear();
	stand.clear();
	
	/*
	delete[] rx;
	delete[] a;
	delete[] u;
	delete[] v;
	delete[] sigma;*/

}
