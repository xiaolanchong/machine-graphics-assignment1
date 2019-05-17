#include "graph.h"
#include <graphics.h>
#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define	SCR_WIDTH	640
#define	SCR_HEIGHT	480

double SinFunc(double x)
{
	return (sin(x) + cos(2*x));
}

CScreen::CScreen(int nDriver)
{
	/* request auto detection */
	int gmode, errorcode;
	/* initialize graphics mode */
	initgraph(&nDriver, &gmode, NULL);
	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)
	{
	   cout << "Graphics error: " << grapherrormsg(errorcode) << '\n';
	   cout << "Press any key to halt:";
	   getch();
	}
}

CScreen::~CScreen()
{
	closegraph();
}
//////////////////////////////////////////////////////////////////

CWnd::CWnd(CGraph& gr,int x1, int y1, int x2, int y2) : 	m_nXtop(x1),
															m_nYtop(y1),
															m_nXbottom(x2),
															m_nYbottom(y2),
															m_graph(gr)
{
}

int	CWnd::DrawGrid(unsigned unX, unsigned unY)
{
	int nPrev = getcolor();
	unsigned i;
	setcolor(15);
	int dx = double( GetXBottom() - GetXTop() )/unX;
	int dy = double( GetYBottom() - GetYTop() )/unY;
	for(i=0; i <= unX; i++)
	{
		line(	GetXTop() + i*dx, GetYTop(),
			GetXTop() + i*dx, GetYBottom());
	}
	for(i=0; i <= unY; i++)
	{
		line(	GetXTop() , GetYTop() + i*dy,
			GetXBottom() , GetYTop() + i*dy);
	}
	setcolor(nPrev);
	return 0;
}

void CWnd::DrawXNum(double xmin, double xmax, unsigned num)
{
	int nPrev = getcolor();
	unsigned i;
	setcolor(10);
	int dx = double( GetXBottom() - GetXTop() )/num;
	  //	int dy = double( GetYBottom() - GetYTop() )/unY;
	double dd = (xmax - xmin)/num;
	int numd, decd;
	char szStr[10];
	for(i=0; i <= num; i++)
	{
		sprintf(szStr, "%2.2f",dd*i+xmin);
		outtextxy(GetXTop() + dx*i - 10, GetYBottom()+20, szStr);
	}
	setcolor(nPrev);
}

void CWnd::DrawYNum(double ymin, double ymax, unsigned num)
{
	int nPrev = getcolor();
	unsigned i;
	setcolor(10);
	int dy = double( GetYBottom() - GetYTop() )/num;
	double dd = (ymax - ymin)/num;
	char szStr[10];
	for(i=0; i <= num; i++)
	{
		sprintf(szStr, "%2.2f",dd*i+ymin);
		outtextxy(GetXTop() - 40, GetYTop() + (num - i)*dy , szStr);
	}
	setcolor(nPrev);
}

int CWnd::DrawFunc(unsigned nx, unsigned ny)
{
	int width  = GetXBottom() - GetXTop();
 //	int height = GetYBottom() - GetYTop();
	int i;
	DrawGrid(nx, ny);
	DrawXNum(m_graph.GetXMin(), m_graph.GetXMax(), nx);
	DrawYNum( m_graph.GetMin(), m_graph.GetMax(), ny);
	int nPrev = getcolor();
	linesettingstype lst;
	getlinesettings(&lst);
	setlinestyle(SOLID_LINE, 1, 3);
	setcolor(1);
	for(i=0; i<width; i++)
	{
		  int x1 = GetXTop() + i;
		  int y1 = GetYBottom() - m_graph.GetFunc(i);//-(CalcFunc(i*dx+xmin) - ymind)/dy + GetYBottom();
//		  int x1 = GetXTop() + i;
		  int y2 = GetYBottom() - m_graph.GetFunc(i+1);//-(CalcFunc((i+1)*dx+xmin) - ymind)/dy + GetYBottom();
		  int x2 = GetXTop() + (i+1);
		  line(x1,y1,x2,y2);
	}
	setcolor(nPrev);
	setlinestyle(lst.linestyle, lst.upattern, lst.thickness);
	outtextxy(100, 30, "f(x) = sin(x)+cos(2x)");
	outtextxy(100, SCR_HEIGHT-20, "Press Enter");
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
	return  (m_fnCalc( dx*x + GetXMin()) - GetMin())/dy;
}
////////////////////////////////////////////////////////////////////////////

int main()
{
	CScreen scr(DETECT);
	CGraph	gr(SinFunc, -3.14, 3.14, SCR_WIDTH-100, SCR_HEIGHT-100);
	CWnd	wnd(gr, 50,50, SCR_WIDTH-50, SCR_HEIGHT-50);
	wnd.DrawFunc(10, 20);
	getch();
	return 0;
}