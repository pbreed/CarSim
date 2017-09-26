class CollideTestObj
{
public:
	int corners_x[4];
	int corners_y[4];
};

class WorldObject
{
public:
WorldObject *m_pNext;
WorldObject *m_pPrev;
const char * m_name;
 WorldObject(const char * name_v="Unknown") {m_pNext=0; m_pPrev=0; m_name=name_v;};

virtual CRect Extent()=0; //Virtual value
virtual void DrawMe(CDC* pDC)=0;
virtual bool bLaserHits()=0; //Can the Laser range off of this?
virtual bool bCollision()=0; //Can the car hit this?
virtual void Normalize(int xoff,int yoff)=0;
virtual double  LaserRange(double orgx, double orgy, double end_x,double endy) {return 0; }
virtual bool CarCollide(CollideTestObj & co) {return false; }
};


class LineObject: public WorldObject
{
public:
int m_x1;
int m_y1;
int m_x2;
int m_y2;
bool m_bLaser;
bool m_bCollide;
CRect m_extent;
LineObject(int x1,int y1, int x2,int y2, const char * name, bool bLaser=false, bool m_bCollide=true);
virtual CRect Extent() {return m_extent;};
virtual void DrawMe(CDC* pDC);
virtual bool bLaserHits() {return m_bLaser;};
virtual bool bCollision()  {return m_bCollide; };
virtual double  LaserRange(double orgx, double orgy, double end_x, double endy);
virtual bool CarCollide(CollideTestObj & co);
virtual void Normalize(int xoff,int yoff);
};


class RoundObject: public WorldObject
{
public:
int m_x;
int m_y;
int m_r;
bool m_bLaser;
bool m_bCollide;
CRect m_extent;
RoundObject(int x,int y, int r, const char * name, bool bLaser=false, bool m_bCollide=true);
virtual CRect Extent() {return m_extent;};
virtual void DrawMe(CDC* pDC);
virtual bool bLaserHits() {return m_bLaser;};
virtual bool bCollision()  {return m_bCollide; };
virtual double  LaserRange(double orgx, double orgy, double end_x, double endy);
virtual bool CarCollide(CollideTestObj & co);
virtual void Normalize(int xoff,int yoff);
};

