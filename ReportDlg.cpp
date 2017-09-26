// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CarSim.h"
#include "ReportDlg.h"
#include "afxdialogex.h"


// ReportDlg dialog

IMPLEMENT_DYNAMIC(ReportDlg, CDialogEx)

ReportDlg::ReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	pp = NULL;
}

ReportDlg::~ReportDlg()
{
	if (pp) delete pp;
}

void ReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, MainEdit);
	CString sall;
	if (pp)
	{
		for (int i = 0; i < nPathPoints; i++)
		{
			CString s;
			s.Format("%d,%d\n", pp[i].x, pp[i].y);
			sall += s;
		}
	}
	MainEdit.SetWindowText(sall);
}

void ReportDlg::SetData(int n, CPoint * pi)
{
	pp = new CPoint[n];
	nPathPoints= n;
	for (int i = 0; i < n; i++) pp[i] = pi[i];
}


BEGIN_MESSAGE_MAP(ReportDlg, CDialogEx)
END_MESSAGE_MAP()


// ReportDlg message handlers
