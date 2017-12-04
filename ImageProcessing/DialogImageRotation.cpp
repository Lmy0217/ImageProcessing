// DialogImageRotation.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogImageRotation.h"
#include "afxdialogex.h"


// CDialogImageRotation 对话框

IMPLEMENT_DYNAMIC(CDialogImageRotation, CDialogEx)

CDialogImageRotation::CDialogImageRotation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_ROTATION, pParent)
	, r_x(0)
	, r_y(0)
	, r_thita(0)
{

}

CDialogImageRotation::~CDialogImageRotation()
{
}

void CDialogImageRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, r_x);
	DDX_Text(pDX, IDC_EDIT2, r_y);
	DDX_Text(pDX, IDC_EDIT3, r_thita);
}


BEGIN_MESSAGE_MAP(CDialogImageRotation, CDialogEx)
END_MESSAGE_MAP()


// CDialogImageRotation 消息处理程序
