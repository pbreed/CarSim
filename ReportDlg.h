#pragma once
#include "afxwin.h"


// ReportDlg dialog

class ReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ReportDlg)
	int nPathPoints;
	CPoint * pp;
public:
	ReportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ReportDlg();
	void SetData(int n, CPoint * pp);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit MainEdit;
};
