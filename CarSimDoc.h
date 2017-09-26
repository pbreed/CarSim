// CarSimDoc.h : interface of the CCarSimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARSIMDOC_H__EA24E95A_B0C4_41E2_8A2A_FAEBC571E408__INCLUDED_)
#define AFX_CARSIMDOC_H__EA24E95A_B0C4_41E2_8A2A_FAEBC571E408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WorldObject;
class TheSimCar;

class CCarSimDoc : public CDocument
{
protected: // create from serialization only
	CCarSimDoc();
	DECLARE_DYNCREATE(CCarSimDoc)

// Attributes
public:

		WorldObject *m_pStaticListHead;
		WorldObject *m_pDynamicListHead;
		TheSimCar * pCar;

		int m_xoff;
		int m_yoff;
        CSize GetSize();
		void Normalize();

		

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarSimDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCarSimDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCarSimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARSIMDOC_H__EA24E95A_B0C4_41E2_8A2A_FAEBC571E408__INCLUDED_)
