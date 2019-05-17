#ifndef _GRAPH_H_
#define	_GRAPH_H_

typedef double CALCFUNC(double x);

class CScreen
{
public:
	CScreen(int nDriver);
	virtual ~CScreen();
private:
	int	m_nDriver;
	char	m_szPath[80];
};

/*class CException
{
public:
	CException(char* szStr);
	virtual ~CException();
};*/
class CGraph;

class CWnd
{
public:
	CWnd(CGraph& gr, int x1,int y1, int x2, int y2);
	virtual ~CWnd() {};
//	int	SetMinMax(double xmin, double xmax);
	int	DrawGrid(unsigned nx, unsigned ny);
	int	DrawFunc(unsigned nx, unsigned ny);
	void	DrawXNum(double xmin, double xmax, unsigned nx);
	void	DrawYNum(double ymin, double ymax, unsigned ny);
//	double	GetMin(CALCFUNC func, double xmin, double xmax, unsigned width);
//	double	GetMax(CALCFUNC func, double xmin, double xmax, unsigned width);
	int	GetXTop() const { return m_nXtop; };
	int	GetYTop() const { return m_nYtop; };
	int	GetXBottom() const { return m_nXbottom; };
	int	GetYBottom() const { return m_nYbottom; };

private:
	int 	m_nXtop;
	int 	m_nYtop;
	int 	m_nXbottom;
	int 	m_nYbottom;
	CGraph& m_graph;
//	double	m_fXmax;
//	double	m_fXmin;
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