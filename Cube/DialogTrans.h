#pragma once

#include"resource.h"

// DialogTrans dialog

class DialogTrans : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTrans)

public:
	DialogTrans(CWnd* pParent = NULL);   // standard constructor
	virtual ~DialogTrans();

// Dialog Data
	enum { IDD = IDD_DIALOG_TRANS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_rotx;
	double m_roty;
	double m_rotz;
	double m_transx;
	double m_transy;
	double m_transz;
};
