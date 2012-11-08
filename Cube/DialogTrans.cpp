// DialogTrans.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DialogTrans.h"



// DialogTrans dialog

IMPLEMENT_DYNAMIC(DialogTrans, CDialogEx)

DialogTrans::DialogTrans(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogTrans::IDD, pParent)
{

	m_rotx = 0.0;
	m_roty = 0.0;
	m_rotz = 0.0;
	m_transx = 0.0;
	m_transy = 0.0;
	m_transz = 0.0;
}

DialogTrans::~DialogTrans()
{
}

void DialogTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROTX, m_rotx);
	DDV_MinMaxDouble(pDX, m_rotx, 0, 360);
	DDX_Text(pDX, IDC_EDIT_ROTY, m_roty);
	DDV_MinMaxDouble(pDX, m_roty, 0, 360);
	DDX_Text(pDX, IDC_EDIT_ROTZ, m_rotz);
	DDV_MinMaxDouble(pDX, m_rotz, 0, 360);
	DDX_Text(pDX, IDC_EDIT_TX, m_transx);
	DDX_Text(pDX, IDC_EDIT_TY, m_transy);
	DDX_Text(pDX, IDC_EDIT_TZ, m_transz);
}


BEGIN_MESSAGE_MAP(DialogTrans, CDialogEx)
END_MESSAGE_MAP()


// DialogTrans message handlers
