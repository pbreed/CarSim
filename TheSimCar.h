class TheSimCar: public WorldObject
{
protected:
	void CalcCorners();
	CPen * pRedPen;
    CPen * pGreenPen;
	CPen * pBluePen;
 
public:
int m_draw_corners_x[4]; //In draw coordinates
int m_draw_corners_y[4];
int m_origin_x;
int m_origin_y;
int m_draw_center_x;
int m_draw_center_y;
double m_heading;
double m_speed;
double m_steer;
double  m_dcenter_x;
double  m_dcenter_y;
double  Laser_Heading;
double  Base_Laser_Heading;
double  m_dlaser_side_x;
double  m_dlaser_side_y;
double  m_ScanArray[72];
double  m_Scanx[72];
double  m_Scany[72];

int m_Startx;
int m_Starty;
double m_Starth;
double m_Starts;
double m_side_range;



double odometer;
double mark_odo;
double m_target_range;
double m_target_h;
int mode;
int avg_side_range;
double Last_Side_Laser[5];
double time_inc;

double DeltaOdo() { return odometer - mark_odo; };



TheSimCar(int x, int y, double head, double speed);
virtual CRect Extent();
virtual void DrawMe(CDC* pDC);
virtual bool bLaserHits() {return false;};
virtual bool bCollision()  {return false; };
virtual double  LaserRange(int orgx, int orgy, int end_x,int endy) {return 0; };
virtual bool CarCollide(CollideTestObj & co) {return false; };
virtual void Normalize(int xoff,int yoff) {m_origin_x=xoff; m_origin_y=yoff; CalcCorners(); Restart();};
void DoTimeStep(double ts, WorldObject * pStatic);
void Restart();
void DoRangeSteer(double ts, double mdelta=10.0);
bool LeftSideScan();
void DoLeftRangeSteer(double ts, double maxangle, double range);
const char * GetModeName();

};


#define MODE_START_TO_FIRST_CORNER (0)
#define MODE_FIRST_GAP (1)
#define MODE_NEXT_STRAIGHT (2)
#define MODE_LEFT_TURN (3)
#define MODE_COAST_TO_CORNER (4)
#define MODE_SEC_GAP (5)
#define MODE_THIRD_STRAIGHT (6)
#define MODE_RIGHT_TURN (7)
#define MODE_LAST_STRAIGHT (8)
#define MODE_STOP (9)
#define MODE_FIRST_CORNER (13)
#define MODE_STRAIGHT2_B4_NOTCH (14)
#define MODE_NOTCH (15)
#define MODE_AFTA_NOTCH (16)
#define MODE_COAST_TURN_2 (17)
#define MODE_2_CORNER (18)
#define MODE_3_STRAIGHT (19)
#define MODE_3_COAST (20)
#define MODE_3_CORNER (21)
#define MODE_4_STRAIGHT (22)
#define MODE_4_TURN (23)
#define MODE_5_STRAIGHT (24)
