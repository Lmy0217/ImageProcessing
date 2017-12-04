// DialogBitPlane.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogBitPlane.h"
#include "afxdialogex.h"


// CDialogBitPlane 对话框

IMPLEMENT_DYNAMIC(CDialogBitPlane, CDialogEx)

CDialogBitPlane::CDialogBitPlane(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_BIT_PLANE, pParent)
	, nBitPlane(0)
{

}

CDialogBitPlane::~CDialogBitPlane()
{
}

void CDialogBitPlane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_BIT_PLANE, nBitPlane);
	DDV_MinMaxInt(pDX, nBitPlane, 0, 7);
}


BEGIN_MESSAGE_MAP(CDialogBitPlane, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogBitPlane::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogBitPlane 消息处理程序


void CDialogBitPlane::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
