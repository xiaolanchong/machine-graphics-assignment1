#ifndef _GRAPH_H_
#define	_GRAPH_H_

#include <windows.h>

typedef double CALCFUNC(double x);

class CGraph;

class CWnd
{
public:
	CWnd(CGraph& gr, int x1,int y1, int x2, int y2, HDC hdc);
	virtual ~CWnd() {};
	int	DrawGrid(unsigned nx, unsigned ny);
	int	DrawFunc(unsigned nx, unsigned ny);
	void	DrawXNum(double xmin, double xmax, unsigned nx);
	void	DrawYNum(double ymin, double ymax, unsigned ny);
	int	GetXTop() const { return m_nXtop; };
	int	GetYTop() const { return m_nYtop; };
	int	GetXBottom() const { return m_nXbottom; };
	int	GetYBottom() const { return m_nYbottom; };

private:
	int 	m_nXtop;
	int 	m_nYtop;
	int 	m_nXbottom;
	int 	m_nYbottom;
    HDC		m_hDC;
	CGraph& m_graph;
};

class CGraph
{
public:
	CGraph(	CALCFUNC* func,
			double xmin, double xmax,
			unsigned width, unsigned height) :	m_fnCalc(func),
												m_fXmin(xmin),
												m_fXmax(xmax),
												m_unWidth(width),
												m_unHeight(height) {};
	virtual ~CGraph() {};
	double		GetFunc( double x) {return m_fnCalc(x);};
	int         GetFunc( int x);
	double		GetXMin() 	const { return m_fXmin; 	};
	double  	GetXMax() 	const { return m_fXmax; 	};
	unsigned	GetWidth() 	const { return m_unWidth; 	};
	unsigned	GetHeight() const { return m_unHeight;	};
	double 		GetMax()	const;
	double 		GetMin()	const;
private:
	double 		m_fXmin;
	double 		m_fXmax;
	unsigned	m_unWidth;
	unsigned	m_unHeight;
	CALCFUNC*    m_fnCalc;
};
#endif