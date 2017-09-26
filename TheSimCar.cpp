
#include "stdafx.h"
#include "CarSim.h"

#include "CarSimDoc.h"
#include "CarSimView.h"
#include "MainFrm.h"
#include "WorldObjects.h"
#include "TheSimCar.h"
#include <math.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const char * ModeNames[] =
{ "MODE_START_TO_FIRST_CORNER (0)",
"MODE_FIRST_GAP (1)",
"MODE_NEXT_STRAIGHT (2)",
"MODE_LEFT_TURN (3)",
"MODE_COAST_TO_CORNER (4)",
"MODE_SEC_GAP (5)",
"MODE_THIRD_STRIGHT (6)",
"MODE_RIGHT_TURN (7)",
"MODE_FIRST_CORNER (2)",
"MODE_STRAIGHT2_B4_NOTCH (3)",
"MODE_NOTCH (4)",
"MODE_AFTA_NOTCH (5)",
"MODE_COAST_TURN_2 (6)",
"MODE_2_CORNER (7)",
"MODE_3_STRAIGHT (8)",
"MODE_3_COAST (9)",
"MODE_3_CORNER (10)",
"MODE_4_STRAIGHT (11)",
"MODE_4_TURN (12)",
"MODE_5_STRAIGHT (13)"

};


TheSimCar::TheSimCar(int x, int y, double head, double speed)
{
m_origin_x=0;
m_origin_y=0;
pRedPen=NULL;
pGreenPen=NULL;
pBluePen = NULL;

m_Startx=x;
m_Starty=y;
m_Starth=head;
m_Starts=speed;
Restart();
}

void TheSimCar::Restart()
{

m_dcenter_x=m_Startx;
m_dcenter_y=m_Starty;

m_heading=m_Starth;
m_speed=m_Starts;
m_steer=0.0;
Base_Laser_Heading=0;

m_draw_center_x=(int)(m_dcenter_x+0.5)+m_origin_x;
m_draw_center_y=-(int)(m_dcenter_y+0.5)+m_origin_y;
m_dlaser_side_x=m_draw_center_x;
m_dlaser_side_y=m_draw_center_y;

CalcCorners();
m_side_range=0.0;
m_target_h=90.0;
mode=MODE_START_TO_FIRST_CORNER;
odometer=0.0;
time_inc=0.0;

}


CRect TheSimCar::Extent()
{
 int maxx=m_draw_corners_x[3];
 int minx=m_draw_corners_x[3];
 int maxy=m_draw_corners_y[3];
 int miny=m_draw_corners_y[3];
 for(int i=0; i<3; i++)
 {
	 if(m_draw_corners_x[i]>maxx) maxx=m_draw_corners_x[i];
     if(m_draw_corners_x[i]<minx) minx=m_draw_corners_x[i];
	
	 if(m_draw_corners_y[i]>maxy) maxy=m_draw_corners_y[i];
     if(m_draw_corners_y[i]<miny) miny=m_draw_corners_y[i];
	

 }
  CRect r(minx,miny,maxx,maxy);
	 r.NormalizeRect();
	 return r;
}


void TheSimCar::DrawMe(CDC* pDC)
{

if(!pRedPen)
{
 pRedPen= new CPen(PS_SOLID,1,RGB(255,0,0));
}
pDC->SelectObject(*pRedPen);


pDC->MoveTo(m_draw_corners_x[0]+m_draw_center_x,m_draw_corners_y[0]+m_draw_center_y);
 for(int i=1; i<4; i++)
	 pDC->LineTo(m_draw_corners_x[i]+m_draw_center_x,m_draw_corners_y[i]+m_draw_center_y);
  pDC->LineTo(m_draw_corners_x[0]+m_draw_center_x,m_draw_corners_y[0]+m_draw_center_y);

  pDC->LineTo(m_draw_center_x,m_draw_center_y);

  pDC->LineTo((int)(m_dlaser_side_x+0.5),(int)(m_dlaser_side_y+0.5));


  if (!pBluePen)
  {
	  pBluePen = new CPen(PS_SOLID, 1, RGB(0, 0,255));
  }

  pDC->SelectObject(*pBluePen);

  for (int i = 0; i < 72; i++)
  {
	  if (m_ScanArray[i]!=0)
	  {

		  pDC->MoveTo(m_draw_center_x, m_draw_center_y);
		  pDC->LineTo((int)(m_Scanx[i]+ 0.5), (int)(m_Scany[i] + 0.5));

	  }
		
  }



}

const double RAD_TO_DEGREES= 57.295779513;
const double PI= 3.14159265358979;

const double RANGE_ERROR_GAIN=(3.0);
//const double MAX_STEER=(30.0);

void TheSimCar::DoRangeSteer(double ts, double MAX_STEER)
{

	//Laser_HEading 0 = correct
    double real_range=m_side_range/cos(Laser_Heading*PI/180.0);



	double r_error=real_range-m_target_range; //Target 50 actual 40 r_error = -10
	double delta=r_error*RANGE_ERROR_GAIN;
	if(delta>25) delta =25;
	if(delta<-25) delta=-25;
	
	double c_head=m_target_h+delta;
	
	double herr=c_head-m_heading;
 	
	if(herr>(MAX_STEER *ts)) herr=(MAX_STEER*ts);
	else
	if(herr<(-MAX_STEER *ts)) herr=(-MAX_STEER *ts);

	m_heading+=herr;
}

bool TheSimCar::LeftSideScan()
{
	for (int i = 36 + 9; i < (72 - 9); i++)
		if (m_ScanArray[i]!=0) return true;
	return false;
}


void TheSimCar::DoLeftRangeSteer(double ts, double MAX_STEER, double trange)
{
	double r = 5000;
	for (int i = 36 + 9; i < (72 - 9); i++)
		if ((m_ScanArray[i] != 0) && (m_ScanArray[i] < r)) r = m_ScanArray[i];
		

	double r_error = trange -r; //Target 50 actual 40 r_error = -10
	double delta = r_error*RANGE_ERROR_GAIN;
	if (delta>25) delta = 25;
	if (delta<-25) delta = -25;

	double c_head = m_target_h + delta;

	double herr = c_head - m_heading;

	if (herr>(MAX_STEER *ts*10)) herr = (MAX_STEER*ts*10);
	else
		if (herr<(-MAX_STEER *ts*10)) herr = (-MAX_STEER *ts*10);

	m_heading += herr;
}

void TheSimCar::DoTimeStep(double ts,WorldObject * pStatics)
{
time_inc+=ts;
if(time_inc>1.0)
{
time_inc=0;
Laser_Heading=Base_Laser_Heading;
}
else
if(time_inc>0.666)
{
	Laser_Heading=Base_Laser_Heading;
}
else
if(time_inc>0.333)
{
	Laser_Heading=Base_Laser_Heading;
}
else
{
	Laser_Heading=Base_Laser_Heading;
}



switch(mode)
{
case MODE_START_TO_FIRST_CORNER:
		m_target_range=4.0;
		m_target_h = 120;
		DoRangeSteer(ts, 30.0);
		if (m_side_range > 20)
		{
			mode = MODE_FIRST_GAP;
		}
		//if((odometer<(12*50)))
			
		//else
	//	{
	//		mode=MODE_COAST_TO_CORNER;
	//	}

	break;
case MODE_FIRST_GAP:
	if (m_side_range < 10)
	{
		mode = MODE_NEXT_STRAIGHT;
		mark_odo = odometer;
	}
break;

case MODE_NEXT_STRAIGHT:
	m_target_h = 120;
	m_target_range = 12.0;
	if (LeftSideScan())
		DoLeftRangeSteer(ts, 90, 2.0);
	else
	DoRangeSteer(ts, 30.0);
	

	if (((odometer-mark_odo) > 400))// && (m_front_range<20))
	{
		mode = MODE_LEFT_TURN;
		mark_odo = odometer;
	}
	break;
case MODE_LEFT_TURN:
{
	double delta_odo = (odometer - mark_odo);
	mark_odo = odometer;
	m_target_h -= 0.149*delta_odo;
	if (m_target_h <= -135.0)
	{
		mode = MODE_COAST_TO_CORNER;
	}

	if (LeftSideScan())
		DoLeftRangeSteer(ts, 90, 2.0);
	else
		DoRangeSteer(ts, 30.0);
	}
	break;
	

case MODE_COAST_TO_CORNER:
	m_target_range = 4.0;
	m_target_h = -135;
	if(DeltaOdo()<350) DoRangeSteer(ts, 30.0);
	if (m_side_range > 20)
	{
		m_target_h = m_heading;

		mode = MODE_SEC_GAP;
	}
		break;

case MODE_SEC_GAP:
	if (m_side_range < 10)
	{
		mode = MODE_THIRD_STRAIGHT;
		mark_odo = odometer;
	}
	break;
case MODE_THIRD_STRAIGHT:
	m_target_h = -125;
	DoRangeSteer(ts, 30.0);
	if
		(((odometer-mark_odo)>450))// && (m_front_range<20))
	{
		mode = MODE_RIGHT_TURN;
		mark_odo = odometer;
	}
	break;
case MODE_RIGHT_TURN:
{
	double delta_odo = (odometer - mark_odo);
	mark_odo = odometer;
	m_target_h += 0.149*delta_odo;
	if (m_target_h >= 126.0)
	{
		mode = MODE_LAST_STRAIGHT;
	}
	DoRangeSteer(ts, 30);
}

	break;
case MODE_LAST_STRAIGHT:
	m_target_h = 120;
	DoRangeSteer(ts, 30.0);
	if (m_side_range > 20)
	{
		mode = MODE_STOP;
	}
	break;
case MODE_STOP:
	m_speed = 0;
	break;
case MODE_FIRST_CORNER:
	{
      if(m_heading<175)
	  {
		  	m_heading+=15.0*ts;
      }
	else
	{mode=MODE_STRAIGHT2_B4_NOTCH;
	odometer=0;
	}
	}
	break;

case MODE_AFTA_NOTCH:
case MODE_STRAIGHT2_B4_NOTCH:
	{
	 m_target_h=180.0;
   	 m_target_range=20.0;
	 //if((odometer<12*50))
		 DoRangeSteer(ts);
		 double la;
		 la=0;
		 for(int i=0; i<4; i++) la+=Last_Side_Laser[i];

		 if ((odometer>700) && ((m_side_range> ((la/4.0)+7.0))))
		 {
			 mode++;
		 }


	}
	break;

case MODE_NOTCH:
	{
	 m_target_h=180.0;
   	 m_target_range=30.0;
	 //if((odometer<12*50))
		 DoRangeSteer(ts);
		 double la=0;
		 for(int i=0; i<4; i++) la+=Last_Side_Laser[i];

		 if(m_side_range< ((la/4.0)-7))
		 {
			 mode++;
			 odometer=0;
		 }

    }
	break;

case MODE_COAST_TURN_2:
		if(m_side_range>75)
		{
			if(odometer>(10*12))
				{
				 mode++;
				 m_heading+=15.0*ts;
				}	
		}
		else
		{
		odometer=0;
		}
	break;



case MODE_2_CORNER :
	{
      if(m_heading<265)
	  {
		  	m_heading+=15.0*ts;
      }
		else
		{mode=MODE_3_STRAIGHT;
		odometer=0;
		Base_Laser_Heading=-30;

		}
	}
	break;

case MODE_3_STRAIGHT:
	m_target_h=270.0;
   	 m_target_range=35.0;
	 if(odometer>1000) mode++;
	 DoRangeSteer(ts);
	break;

case MODE_3_COAST:
		if(m_side_range>75)
		{
			if(odometer>(25*12))
			{mode++;
			 m_heading+=15.0*ts;
			}
		}
		else
			odometer=0;
	break;

case MODE_3_CORNER :
	{
      if(m_heading<355)
	  {
		  	m_heading+=15.0*ts;
      }
		else
		{mode=MODE_4_STRAIGHT;
		odometer=0;
//		Laser_Heading=90;

		}
	}
	break;

case MODE_4_STRAIGHT:
	{ m_target_h=360.0;
   	 m_target_range=35.0;
	 double la=0.0;
	 	 for(int i=0; i<4; i++) la+=Last_Side_Laser[i];

		 if ((odometer>1000) && ((m_side_range> ((la/4.0)+7.0))))
		 {
			 mode++;
		 }

	 }
	 DoRangeSteer(ts);
	
	break;

case MODE_4_TURN:
	   if(m_heading<445)
	  {
		  	m_heading+=15.0*ts;
      }
		else
		{mode=MODE_5_STRAIGHT;
		odometer=0;
		Base_Laser_Heading=0;
        m_heading-=360.0;
		m_target_h=90.0;
		}
		break;

case MODE_5_STRAIGHT:
	{
		m_target_range=18.0;
		DoRangeSteer(ts,30.0);
		if(odometer >1500) mode= MODE_COAST_TO_CORNER;
		Base_Laser_Heading=0;

	
	}




}



CalcCorners();
double a=(m_heading*PI/180.0);
double s=sin(a);
double c=cos(a);
double dx=s*m_speed*ts;
double dy=c*m_speed*ts;

odometer+=m_speed*ts;

m_dcenter_x+=dx;
m_dcenter_y+=dy;
m_draw_center_x=(int)(m_dcenter_x+0.5)+m_origin_x;
m_draw_center_y=-(int)(m_dcenter_y+0.5)+m_origin_y;


WorldObject *p = pStatics;
double range = 5000;
//Find the range...
for (int an = 0; an < 72; an++)
{
	a = ((m_heading + an*5)*PI / 180.0);
	s = sin(a);
	c = cos(a);

	double fx = 1200.0*s + m_draw_center_x;
	double fy = -1200.0*c + m_draw_center_y;
	p = pStatics;
	m_ScanArray[an] = 0;
	range = 5000;
	while (p)
	{
		double r;
		if (p->bLaserHits())
		{
			r = p->LaserRange(m_draw_center_x, m_draw_center_y, fx,fy);
			if ((r>0) && (r<range)) range = r;
		}
		p = p->m_pNext;
	}
	if (range<72.0)
	{
		m_ScanArray[an] = range/12;
		m_Scanx[an]= range*s + m_draw_center_x;
		m_Scany[an]= -range*c+m_draw_center_y;
	}
	else
	{
		m_ScanArray[an] = 0;
		m_Scanx[an] = 0;
		m_Scany[an] = 0;
	}



}



a=((m_heading+Laser_Heading+90.0)*PI/180.0);
s=sin(a);
c=cos(a);

m_dlaser_side_x=1200.0*s+m_draw_center_x;
m_dlaser_side_y=-1200.0*c+m_draw_center_y;
//Find the range...
p=pStatics;
range=5000;
while(p)
{
double r;
	if(p->bLaserHits())
	{
		r=p->LaserRange(m_draw_center_x,m_draw_center_y,(int)m_dlaser_side_x,(int)m_dlaser_side_y);
		if ((r>0) &&(r<range)) range=r;
	}
  p=p->m_pNext;
}
if(range<1200.0)
{
m_dlaser_side_x=range*s+m_draw_center_x;
m_dlaser_side_y=-range*c+m_draw_center_y;
}

m_side_range=range/12.0;


Last_Side_Laser[0]=Last_Side_Laser[1];
Last_Side_Laser[1]=Last_Side_Laser[2];
Last_Side_Laser[2]=Last_Side_Laser[3];
Last_Side_Laser[3]=Last_Side_Laser[4];
Last_Side_Laser[4]=m_side_range;

}





void TheSimCar::CalcCorners()
{
double a=(-m_heading*PI/180.0);

double s=sin(a);

double c=cos(a);


//Corners of car are at
//[0] -6,8 left front
//[1] 6,8 right front
//[2] 6,-19 right rear
//[3]-6,-19 left rear

double s8=8.0*s;
double c8=8.0*c;
double s19=19.0*s;
double c19=19.0*c;
double s6=6.0*s;
double c6=6.0*c;

  m_draw_corners_x[0]=((int) ((-c6-s8))); //Left Front
  m_draw_corners_y[0]=((int)-((c8-s6)));

  m_draw_corners_x[1]=((int) ((c6-s8)));
  m_draw_corners_y[1]=((int)-((c8+s6)));

  m_draw_corners_x[2]=((int) ((c6+s19)));  //Right Rear
  m_draw_corners_y[2]=((int)-((-c19+s6))); //Right Rear
 

  m_draw_corners_x[3]=((int) ((-c6+s19)));  //Left Rear
  m_draw_corners_y[3]=((int)-((-c19+-s6)));

m_draw_center_x=(int)(m_dcenter_x)+m_origin_x;
m_draw_center_y=-(int)(m_dcenter_y)+m_origin_y;



}


const char * TheSimCar::GetModeName()
{
return ModeNames[mode];
}