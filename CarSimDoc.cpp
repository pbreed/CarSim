// CarSimDoc.cpp : implementation of the CCarSimDoc class
//

#include "stdafx.h"
#include "CarSim.h"

#include "CarSimDoc.h"
#include "WorldObjects.h"
#include "TheSimCar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarSimDoc

IMPLEMENT_DYNCREATE(CCarSimDoc, CDocument)

BEGIN_MESSAGE_MAP(CCarSimDoc, CDocument)
	//{{AFX_MSG_MAP(CCarSimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarSimDoc construction/destruction

const double Lot[] =
{
-200 * 12,0,0,
400 * 12,-400 * 12,0,
0,0,0
};


const double Outer[]={
60.629794943849625 * 12, 6.5476969894736534 * 12, 0,
89 * 12, 28.803745161308349 * 12, 0,
117.37020505615038 * 12, 6.5476969894736534 * 12, 0,
117.37020505615038 * 12, 6.5476969894736534 * 12, 0,
124.5900811611581 * 12, 2.7597704331499919 * 12, 0,
132.43973986588546 * 12, 0.55571580881303717 * 12, 0,
140.57611341809434 * 12, 0.031860879773802253 * 12, 0,
148.64360325090126 * 12, 1.2111006201661514 * 12, 0,
156.28962134650124 * 12, 4.0418965947148431 * 12, 0,
163.18000002445106 * 12, 8.4005294356659341 * 12, 0,
169.01359667281912 * 12, 14.096505972829014 * 12, 0,
173.53545512536925 * 12, 20.880884699202138 * 12, 0,
176.54794846944077 * 12, 28.457155709381745 * 12, 0,
177.91941629035085 * 12, 36.494199605241192 * 12, 0,
177.58991886329298 * 12, 44.640759002515928 * 12, 0,
175.57385680693369 * 12, 52.540790164015959 * 12, 0,
171.95934170727489 * 12, 59.849023819428325 * 12, 0,
166.9043452185395 * 12, 66.246055089215602 * 12, 0,
160.62979494384962 * 12, 71.452303010526322 * 12, 0,
153.40991883884192 * 12, 75.24022956684999 * 12, 0,
145.56026013411457 * 12, 77.444284191186938 * 12, 0,
137.42388658190566 * 12, 77.968139120226184 * 12, 0,
129.35639674909876 * 12, 76.78889937983385 * 12, 0,
121.71037865349879 * 12, 73.958103405285144 * 12, 0,
114.81999997554894 * 12, 69.599470564334055 * 12, 0,
114.81999997554894 * 12, 69.599470564334055 * 12, 0,
89 * 12, 49.196254838691637 * 12, 0,
63.180000024451061 * 12, 69.599470564334055 * 12, 0,
63.180000024451061 * 12, 69.599470564334055 * 12, 0,
56.289621346501214 * 12, 73.958103405285144 * 12, 0,
48.643603250901243 * 12, 76.78889937983385 * 12, 0,
40.576113418094351 * 12, 77.968139120226184 * 12, 0,
32.439739865885443 * 12, 77.444284191186938 * 12, 0,
24.590081161158075 * 12, 75.24022956684999 * 12, 0,
17.370205056150372 * 12, 71.452303010526322 * 12, 0,
11.095654781460492 * 12, 66.246055089215602 * 12, 0,
6.0406582927251016 * 12, 59.849023819428325 * 12, 0,
2.4261431930663235 * 12, 52.540790164015959 * 12, 0,
0.41008113670702073 * 12, 44.640759002515928 * 12, 0,
0.0805837096491544 * 12, 36.494199605241192 * 12, 0,
1.4520515305592419 * 12, 28.457155709381745 * 12, 0,
4.4645448746307519 * 12, 20.880884699202138 * 12, 0,
8.9864033271808736 * 12, 14.096505972829014 * 12, 0,
14.819999975548935 * 12, 8.4005294356659341 * 12, 0,
21.710378653498779 * 12, 4.0418965947148431 * 12, 0,
29.356396749098742 * 12, 1.2111006201661514 * 12, 0,
37.423886581905649 * 12, 0.031860879773802253 * 12, 0,
45.560260134114543 * 12, 0.55571580881303717 * 12, 0,
53.409918838841904 * 12, 2.7597704331499919 * 12, 0,
60.629794943849625 * 12, 6.5476969894736534 * 12, 0,
0, 0, 0 };

const double lfside[] =
{
	51.591167079402069 * 12, 19.752597277071892 * 12, 0,
	53.260000013657589 * 12, 20.954158384533997 * 12, 0,
	53.260000013657589 * 12, 20.954158384533997 * 12, 0,
	76.096774193548384 * 12, 38.999999999999993 * 12, 0,
	53.414746218948302 * 12, 56.923018916423608 * 12, 0,
	53.414746218948302 * 12, 56.923018916423608 * 12, 0,
	49.373156175224473 * 12, 59.527971915520546 * 12, 0,
	44.878472474817528 * 12, 61.236086916604968 * 12, 0,
	40.126871319220477 * 12, 61.972378218850487 * 12, 0,
	35.326020479644974 * 12, 61.704666359231311 * 12, 0,
	30.685740174818719 * 12, 60.444651630636827 * 12, 0,
	26.408832920597931 * 12, 58.247402722928094 * 12, 0,
	22.682220086870068 * 12, 55.208949956942035 * 12, 0,
	19.668772536741397 * 12, 51.462088298666259 * 12, 0,
	17.500192388278229 * 12, 47.170573582004437 * 12, 0,
	16.271256999970475 * 12, 42.521965593047049 * 12, 0,
	16.035676745373458 * 12, 37.719430807407541 * 12, 0,
	16.803747612052536 * 12, 32.97286304033706 * 12, 0 ,
	18.541901217520916 * 12, 28.489710079815769 * 12, 0,
	21.174171908633248 * 12, 24.465907222773126 * 12, 0,
	24.58551682515176 * 12, 21.077313962410216 * 12, 0 ,
	28.62684382477552 * 12, 18.47202808447944 * 12, 0  ,
	33.121527525182472 * 12, 16.763913083395018 * 12, 0,
	37.873128680779523 * 12, 16.027621781149499 * 12, 0,
	42.673979520355019 * 12, 16.295333640768675 * 12, 0,
	47.314259825181274 * 12, 17.555348369363159 * 12, 0,
	51.591167079402069 * 12, 19.752597277071892 * 12, 0,
	0,0,0 };


const double rtside[] = {
	126.40883292059793 * 12, 19.752597277071892 * 12,0,
	124.73999998634241 * 12, 20.954158384533997 * 12,0,
	124.73999998634241 * 12, 20.954158384533997 * 12,0,
	101.90322580645162 * 12, 38.999999999999993 * 12,0,
	124.5852537810517 * 12, 56.923018916423608 * 12,0,
	124.5852537810517 * 12, 56.923018916423608 * 12,0,
	128.62684382477553 * 12, 59.527971915520546 * 12,0,
	133.12152752518247 * 12, 61.236086916604968 * 12,0,
	137.87312868077953 * 12, 61.972378218850487 * 12,0,
	142.67397952035503 * 12, 61.704666359231311 * 12,0,
	147.3142598251813 * 12, 60.444651630636827 * 12,0,
	151.59116707940206 * 12, 58.247402722928094 * 12,0,
	155.31777991312993 * 12, 55.208949956942035 * 12,0,
	158.33122746325861 * 12, 51.462088298666259 * 12,0,
	160.49980761172176 * 12, 47.170573582004437 * 12,0,
	161.72874300002951 * 12, 42.521965593047049 * 12,0,
	161.96432325462655 * 12, 37.719430807407541 * 12,0,
	161.19625238794745 * 12, 32.97286304033706 * 12,0,
	159.45809878247908 * 12, 28.489710079815769 * 12,0,
	156.82582809136676 * 12, 24.465907222773126 * 12,0,
	153.41448317484824 * 12, 21.077313962410216 * 12,0,
	149.37315617522449 * 12, 18.47202808447944 * 12,0,
	144.87847247481753 * 12, 16.763913083395018 * 12,0,
	140.12687131922047 * 12, 16.027621781149499 * 12,0,
	135.32602047964497 * 12, 16.295333640768675 * 12,0,
	130.68574017481873 * 12, 17.555348369363159 * 12,0,
	126.40883292059793 * 12, 19.752597277071892 * 12,0,
	0,0,0 };

const double haybale[] = {
	169 * 12,43 * 12,0,
	169 * 12,35 * 12,0,
	171 * 12,35 * 12,0,
	171 * 12,43 * 12,0,
	169 * 12,43 * 12,0,
	0,0,0
};





const double Barrels[]=
{
39*12,39*12,12,
139*12,39*12,12,
163*12,39*12,12,
163 * 12,45 * 12,12,
166 * 12,41 * 12,12,
166 * 12,35 * 12,12,
0,0,0
};


void AddLine(WorldObject * &pHead,int x1,int y1, int x2,int y2, const char * name, bool bLaser, bool bCollide)
{
WorldObject * pNewLine = new LineObject(x1,-y1,x2,-y2,name,bLaser,bCollide);
pNewLine->m_pNext=pHead;
if(pHead) pHead->m_pPrev=pNewLine;
pNewLine->m_pPrev=0;
pHead=pNewLine;
}


void AddRhinoList(WorldObject * &pHead,const double list[],const char * name, bool bLaser, bool bCollide)
{
double fx=list[0];
double fy=list[1];
double lx=list[0];
double ly=list[1];
int n=1;

while(!((list[n*3]==0) && (list[n*3+1]==0)))
{
 AddLine(pHead,(int)lx,(int)ly,(int)list[n*3],(int)list[n*3+1],name,bLaser,bCollide);
 lx=list[n*3];
 ly=list[n*3+1];
 n++;
}
AddLine(pHead,(int)lx,(int)ly,(int)fx,(int)fy,name,bLaser,bCollide);
}

void AddRound(WorldObject * &pHead,int x,int y, int r, const char * name, bool bLaser, bool bCollide)
{
WorldObject * pNewRound = new RoundObject(x,-y,r,name,bLaser,bCollide);
pNewRound->m_pNext=pHead;
if(pHead) pHead->m_pPrev=pNewRound;
pNewRound->m_pPrev=0;
pHead=pNewRound;
}


void AddRoundList(WorldObject * &pHead,const double list[],const char * name, bool bLaser, bool bCollide)
{
int n=0;

while(!((list[n*3]==0) && (list[n*3+1]==0)))
{
 AddRound(pHead,(int)list[n*3],(int)list[n*3+1],(int)list[n*3+2],name,bLaser,bCollide);
n++;
}
}


BOOL CCarSimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCarSimDoc serialization

void CCarSimDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

CSize CCarSimDoc::GetSize()
{
WorldObject * p=m_pStaticListHead;
CRect extent=p->Extent();

do 
{
 p=p->m_pNext;
 if(p)
 {
   extent.UnionRect(extent,p->Extent());
 }
}
while(p);

return extent.Size();
}

void CCarSimDoc::Normalize()
{
WorldObject * p=m_pStaticListHead;
CRect extent=p->Extent();

do 
{
 p=p->m_pNext;
 if(p)
 {
   extent.UnionRect(extent,p->Extent());
 }
}
while(p);
  
m_xoff=extent.left;
m_yoff=extent.top;

p=m_pStaticListHead;
while(p)
{
p->Normalize(-m_xoff,-m_yoff);
p=p->m_pNext;
}

p=m_pDynamicListHead;
while(p)
{
p->Normalize(-m_xoff,-m_yoff);
p=p->m_pNext;
}

}





CCarSimDoc::CCarSimDoc()
{
	m_pStaticListHead=NULL;
    m_pDynamicListHead=NULL;


	
	AddRhinoList(m_pStaticListHead, Outer, "Outer", true, false);
	AddRhinoList(m_pStaticListHead, rtside, "RtSide", true, false);
	AddRhinoList(m_pStaticListHead, lfside, "LfSide", true, false);
	AddRhinoList(m_pStaticListHead, haybale, "HayBale", true, false);
	//AddRhinoList(m_pStaticListHead, Lot, "Lot", true, false);
	// TODO: add one-time construction code here
    pCar= new TheSimCar(58*12,63*12,135,135);
	//pCar = new TheSimCar(-180*12, 4 * 12, 135, 135); 
	
	
	AddRoundList(m_pStaticListHead,Barrels,"Barrels",true,true);
	m_pDynamicListHead=pCar;
	pCar->m_pNext=0;

	/*pCar= new TheSimCar(-121+50,1597+50,90,0);
	pCar->m_pNext=m_pDynamicListHead;
	m_pDynamicListHead=pCar;

	pCar= new TheSimCar(-121-50,1597-50,45,0);
	pCar->m_pNext=m_pDynamicListHead;
	m_pDynamicListHead=pCar;
*/

	Normalize();

}

CCarSimDoc::~CCarSimDoc()
{
}





/////////////////////////////////////////////////////////////////////////////
// CCarSimDoc diagnostics

#ifdef _DEBUG
void CCarSimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCarSimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCarSimDoc commands
