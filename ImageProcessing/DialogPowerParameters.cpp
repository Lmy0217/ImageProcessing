// DialogPowerParameters.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogPowerParameters.h"
#include "afxdialogex.h"


// CDialogPowerParameters 对话框

IMPLEMENT_DYNAMIC(CDialogPowerParameters, CDialogEx)

CDialogPowerParameters::CDialogPowerParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POWER_PARAMETERS, pParent)
	, m_power_c(1)
	, m_power_gama(1)
{

}

CDialogPowerParameters::~CDialogPowerParameters()
{
}

void CDialogPowerParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PARAM_C, m_power_c);
	DDX_Text(pDX, IDC_EDIT_PARAM_GAMA, m_power_gama);
}


BEGIN_MESSAGE_MAP(CDialogPowerParameters, CDialogEx)
END_MESSAGE_MAP()


// CDialogPower_Parameters 消息处理程序
