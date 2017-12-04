// DialogLogParameters.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogLogParameters.h"
#include "afxdialogex.h"


// CDialogLogParameters 对话框

IMPLEMENT_DYNAMIC(CDialogLogParameters, CDialogEx)

CDialogLogParameters::CDialogLogParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOG_TRANSFORM, pParent)
	, m_log_c(1)
{

}

CDialogLogParameters::~CDialogLogParameters()
{
}

void CDialogLogParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PARAM_C, m_log_c);
}


BEGIN_MESSAGE_MAP(CDialogLogParameters, CDialogEx)
END_MESSAGE_MAP()


// CDialogLogParameters 消息处理程序
