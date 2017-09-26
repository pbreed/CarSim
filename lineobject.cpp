#include "stdafx.h"
#include "CarSim.h"

#include "CarSimDoc.h"
#include "CarSimView.h"
#include "MainFrm.h"
#include "WorldObjects.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LineObject::LineObject(int x1,int y1, int x2,int y2, const char * name, bool bLaser, bool bCollide)
:WorldObject(name)
{
 int xr,yr;
 if(x1==x2) xr=x2+1; else xr=x2;
 if(y1==y2) yr=y2+1; else yr=y2;

 m_extent=CRect(x1,y1,xr,yr);
 m_extent.NormalizeRect();
 m_x1=x1;
 m_y1=y1;
 m_x2=x2;
 m_y2=y2;
 m_bLaser=bLaser;
 m_bCollide=bCollide;
}



void LineObject::DrawMe(CDC* pDC)
{
pDC->MoveTo(m_x1,m_y1);
pDC->LineTo(m_x2,m_y2);
}


bool LineObject::CarCollide(CollideTestObj & co)
{
return false;
}


void LineObject::Normalize(int xoff,int yoff)
{
m_x1=m_x1+xoff;
m_x2=m_x2+xoff;
m_y1=m_y1+yoff;
m_y2=m_y2+yoff;
int xr,yr;
 if(m_x1==m_x2) xr=m_x2+1; else xr=m_x2;
 if(m_y1==m_y2) yr=m_y2+1; else yr=m_y2;
 m_extent=CRect(m_x1,m_y1,xr,yr);
 m_extent.NormalizeRect();


}


CPoint Intersect(double x1, double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{

	
double d=(x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);

if(d==0) return CPoint(0,0);

double x=(((x1*y2-y1*x2)*(x3-x4))-((x1-x2)*(x3*y4-y3*x4)))/d;

double y=(((x1*y2-y1*x2)*(y3-y4))-((y1-y2)*(x3*y4-y3*x4)))/d;

return CPoint((int)(x+0.5),(int(y+0.5)));

}

double Distance(double x1, double y1, double x2, double y2)
{
return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double  LineObject::LaserRange(double orgx, double orgy, double end_x,double end_y)
{



 if((orgx<m_x1) && (orgx<m_x2) && (end_x<m_x1) && (end_x<m_x2)) return -1;
 if((orgx>m_x1) && (orgx>m_x2) && (end_x>m_x1) && (end_x>m_x2)) return -1;

 if((orgy<m_y1) && (orgy<m_y2) && (end_y<m_y1) && (end_y<m_y2)) return -1;
 if((orgy>m_y1) && (orgy>m_y2) && (end_y>m_y1) && (end_y>m_y2)) return -1;



CPoint p=Intersect(m_x1,m_y1,m_x2,m_y2,orgx,orgy,end_x,end_y);

if ((p.x!=0) && (p.y!=0))
{
 if ((p.x<m_x1)&& (p.x<m_x2))  return -1;
 if ((p.x<orgx)&& (p.x<end_x))  return -1;
 if ((p.x>m_x1)&& (p.x>m_x2))  return -1;
 if ((p.x>orgx)&& (p.x>end_x))  return -1;

 if ((p.y<m_y1)&& (p.y<m_y2))  return -1;
 if ((p.y<orgy)&& (p.y<end_y))  return -1;
 if ((p.y>m_y1)&& (p.y>m_y2))  return -1;
 if ((p.y>orgy)&& (p.y>end_y))  return -1;



 return Distance(orgx,orgy,p.x,p.y);
}
return -1;
}


RoundObject::RoundObject(int x,int y, int r, const char * name, bool bLaser, bool bCollide)
:WorldObject(name)
{

 m_extent=CRect(x-r,y-r,x+r,y+r);
 m_extent.NormalizeRect();
 m_x=x;
 m_y=y;
 m_r=r;
 m_bLaser=bLaser;
 m_bCollide=bCollide;
}


void RoundObject::DrawMe(CDC* pDC)
{
 pDC->Arc(m_x-m_r,m_y-m_r,m_x+m_r,m_y+m_r,m_x,m_y+m_r,m_x,m_y-m_r);
 pDC->Arc(m_x-m_r,m_y-m_r,m_x+m_r,m_y+m_r,m_x,m_y-m_r,m_x,m_y+m_r);

}


bool OnLine(double x, double y, double x1, double y1, double x2, double y2)
{
	if ((x < x1) && (x < x2)) return false;
	if ((x > x1) && (x > x2)) return false;
	if ((y < y1) && (y < y2)) return false;
	if ((y > y1) && (y > y2)) return false;
	double dx = (x2 - x1);
	double dy = (y2 - y1);
	
	if(fabs(dx)>fabs(dy))
	{
		double yi = y1 + dy*(x-x1) / (dx);
		if (fabs(yi - y) < 0.00001) return true;
	}
	else
	{
		double xi = x1 + dx*(y - y1) / (dy);
		if (fabs(xi - x) < 0.00001) return true;
	}
	return false;
}

double sgn(double d)
{
if(d<0) return -1;
return 0;
}


double  RoundObject::LaserRange(double orgx, double orgy, double end_x,double  end_y)
{
 int rt=m_x+m_r;
 int lf=m_x-m_r;
 int tp=m_y-m_r;
 int bt=m_y+m_r;

 if((orgx<lf) && (end_x<lf)) return -1;
 if((orgx>rt) && (end_x>rt)) return -1;
 if((orgy<tp) && (end_y<tp)) return -1;
 if((orgy>bt) && (end_y>bt)) return -1;

double x1=orgx-m_x;
double x2=end_x-m_x;
double y1=orgy-m_y;
double y2=end_y-m_y;
double r=m_r;


double dx=(x2-x1);
double dy=(y2-y1);
double dr=sqrt((dx*dx)+(dy*dy));
double D=(x1*y2-x2*y1);
double root=(r*r*dr*dr)-(D*D);
if(root<0) return -1;
root=sqrt(root);

x1=(D*dy+sgn(dy)*dx*root)/(dr*dr);
x2=(D*dy-sgn(dy)*dx*root)/(dr*dr);
y1=(-D*dx+fabs(dy)*root)/(dr*dr);
y2=(-D*dx-fabs(dy)*root)/(dr*dr);

double test11= fabs(((x1*x1) + (y1*y1))-(r*r));
double test22= fabs(((x2*x2) + (y2*y2))-(r*r));






x1+=m_x;
x2+=m_x;
y1+=m_y;
y2+=m_y;

dx=((double)orgx-x1);
dy=((double)orgy-y1);
root=(dx*dx+dy*dy);

dx=((double)orgx-x2);
dy=((double)orgy-y2);
r=(dx*dx+dy*dy);

if((test11>0.00001) && (test22>0.00001))
{
   return -1;
}

if((test11>0.00001) || (r<root))
return sqrt(r);

return sqrt(root);

}

/*
double  RoundObject::LaserRange(double orgx, double orgy, double end_x,double end_y)
{
 int rt=m_x+m_r;
 int lf=m_x-m_r;
 int tp=m_y-m_r;
 int bt=m_y+m_r;


 if((orgx<lf) && (end_x<lf)) return -1;
 if((orgx>rt) && (end_x>rt)) return -1;
 if((orgy>tp) && (end_y>tp)) return -1;
 if((orgy<bt) && (end_y<bt)) return -1;





double x1=orgx-m_x;
double x2=end_x-m_x;
double y1=orgy-m_y;
double y2=end_y-m_y;
double r=m_r;

double lx1 = x1;
double lx2 = x2;
double ly1 = y1;
double ly2 = y2;


double dx=(x2-x1);
double dy=(y2-y1);

double dr=sqrt((dx*dx)+(dy*dy));

double D=(x1*y2-x2*y1);

double root=(r*r*dr*dr)-(D*D);
if(root<0) return -1;
root=sqrt(root);


x1=(D*dy+sgn(dy)*dx*root)/(dr*dr);
x2=(D*dy-sgn(dy)*dx*root)/(dr*dr);

y1=(-D*dx+fabs(dy)*root)/(dr*dr);
y2 = (-D*dx - fabs(dy)*root) / (dr*dr);

//x1,y1,x2,y1,x1,y2,x2,y2 all possible.
double range = 9999;

double test11= fabs(((x1*x1) + (y1*y1))-(r*r));
double test12= fabs(((x1*x1) + (y2*y2))-(r*r));
double test21= fabs(((x2*x2) + (y1*y1))-(r*r));
double test22= fabs(((x2*x2) + (y2*y2))-(r*r));

if ((test11 > 0.0001) && (test12 > 0.0001) && (test21 > 0.0001) && (test22 > 0.0001)) return -1;

if (test11 < 0.0001)
{
	if (OnLine(x1, y1, lx1, ly1, lx2, ly2))
		range = Distance(x1, y1, lx1, ly1);
}

if (test12 < 0.0001)
{
	if (OnLine(x1, y2, lx1, ly1, lx2, ly2))
	{
		r = Distance(x1, y2, lx1, ly1);
		if (r < range) range = r;
	}
}

if (test21 < 0.0001)
{
	if (OnLine(x2, y1, lx1, ly1, lx2, ly2))
	{
		r = Distance(x2, y1, lx1, ly1);
		if (r < range) range = r;
	}
}

if (test22 < 0.0001)
{
	if (OnLine(x2, y2, lx1, ly1, lx2, ly2))
	{
		r = Distance(x2, y2, lx1, ly1);
		if (r < range) range = r;
	}
}

return r;
}
*/

bool RoundObject::CarCollide(CollideTestObj & co)
{
return false;
}


void RoundObject::Normalize(int xoff,int yoff)
{
m_x=m_x+xoff;
m_y=m_y+yoff;
}
