#include "graph.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

#ifndef xz
#define xz
double SinFunc(double x)
{
	return (sin(x) + cos(2*x));
}

//////////////////////////////////////////////////////////////////

CWnd::CWnd(CGraph& gr,int x1, int y1, int x2, int y2, HDC hdc) : 	m_nXtop(x1),
																	m_nYtop(y1),
																	m_nXbottom(x2),
																	m_nYbottom(y2),
																	m_graph(gr),
																	m_hDC(hdc)
{
}

int	CWnd::DrawGrid(unsigned unX, unsigned unY)
{
	HPEN	hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(127,127,127));
	hOldPen = (HPEN)SelectObject(m_hDC, hPen);
	unsigned i;
	double dx = double( GetXBottom() - GetXTop() )/unX;
	double dy = double( GetYBottom() - GetYTop() )/unY;
	for(i=0; i <= unX; i++)
	{
		MoveToEx(	m_hDC, GetXTop() + static_cast<int>(i*dx), GetYTop(), NULL);
		LineTo(m_hDC, GetXTop() + static_cast<int>(i*dx), GetYBottom());
	}
	for(i=0; i <= unY; i++)
	{
		MoveToEx(	m_hDC, GetXTop() , GetYTop() + static_cast<int>(i*dy), NULL);
		LineTo(m_hDC, GetXBottom() , GetYTop() + static_cast<int>(i*dy));
	}
	SelectObject(m_hDC, hOldPen);
	DeleteObject(hPen);
	return 0;
}

void CWnd::DrawXNum(double xmin, double xmax, unsigned num)
{
	COLORREF clPrev = SetTextColor(m_hDC, RGB(0, 0, 255));
	unsigned i;
	int dx = ( GetXBottom() - GetXTop() )/num;
	double dd = (xmax - xmin)/num;
	TCHAR szStr[10];
	for(i=0; i <= num; i++)
	{
		_stprintf_s(szStr, _T("%2.2f"),dd*i+xmin);
		TextOut(m_hDC,	GetXTop() + dx*i - 10, GetYBottom()+20, 
						szStr, _tcslen(szStr));
	}
	SetTextColor(m_hDC, clPrev);
}

void CWnd::DrawYNum(double ymin, double ymax, unsigned num)
{
	COLORREF clPrev = SetTextColor(m_hDC, RGB(0, 0, 255));
	unsigned i;
	int dy = ( GetYBottom() - GetYTop() )/num;
	double dd = (ymax - ymin)/num;
	TCHAR szStr[10];
	for(i=0; i <= num; i++)
	{
		_stprintf_s(szStr, _T("%2.2f"),dd*i+ymin);
		TextOut(m_hDC, 
				GetXTop() - 40, GetYTop() + (num - i)*dy , 
				szStr, _tcslen(szStr));
	}
	SetTextColor(m_hDC, clPrev);
}

int CWnd::DrawFunc(unsigned nx, unsigned ny)
{
	int width  = GetXBottom() - GetXTop();
	int i;
	DrawGrid(nx, ny);
	DrawXNum(m_graph.GetXMin(), m_graph.GetXMax(), nx);
	DrawYNum( m_graph.GetMin(), m_graph.GetMax(), ny);
	
	HPEN	hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0 , 0));
	hOldPen = (HPEN)SelectObject(m_hDC, hPen);
	int x1 = GetXTop();
	int	y1 = GetYBottom() - m_graph.GetFunc(0);
	MoveToEx(m_hDC, x1, y1, NULL);
	for(i=1; i<width; i += 7)
	{
		  x1 = GetXTop() + i;
		  y1 = GetYBottom() - m_graph.GetFunc(i);
		  LineTo(m_hDC, x1, y1);
	}
	x1 = GetXTop() + width;
	y1 = GetYBottom() - m_graph.GetFunc(width);
	LineTo(m_hDC, x1, y1);
	TCHAR str[] = _T("f(x) = sin(x)+cos(2x)");
	TextOut(m_hDC, 200, 10, str, _tcslen(str));
	SelectObject(m_hDC, hOldPen);
	DeleteObject(hPen);
	return 0;
}
////////////////////////////////////////////////////////////////////////

double CGraph::GetMin() const
{
	double min = 10e+10;
	double dd = (GetXMax() - GetXMin())/GetWidth();
	unsigned i;
	for(i=0; i <= GetWidth(); i++)
		if(min > m_fnCalc(i*dd + GetXMin()))
			min = m_fnCalc(i*dd + GetXMin());
	return min;
}

double CGraph::GetMax() const
{
	double max = -10e+10;
	double dd = (GetXMax() - GetXMin())/GetWidth();
	unsigned i;
	for(i=0; i <= GetWidth(); i++)
		if(max < (*m_fnCalc)(i*dd + GetXMax()))
			max = (*m_fnCalc)(i*dd + GetXMin());
	return max;
}

int CGraph::GetFunc( int x)
{
	double dx = (GetXMax() - GetXMin())/GetWidth();
	double dy = (GetMax() - GetMin())/GetHeight();
	return  static_cast<int>((m_fnCalc( dx*x + GetXMin()) - GetMin())/dy);
}
////////////////////////////////////////////////////////////////////////////

#endif