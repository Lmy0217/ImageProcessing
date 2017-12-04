// GenicAffineTranform.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "GenicAffineTranform.h"
#include "afxdialogex.h"


// CGenicAffineTranform 对话框

IMPLEMENT_DYNAMIC(CGenicAffineTranform, CDialogEx)

CGenicAffineTranform::CGenicAffineTranform(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENERIC_AFFINE_TRANSFORM, pParent)
	, m_a(0)
	, m_b(0)
	, m_c(0)
	, m_d(0)
	, m_e(0)
	, m_f(0)
{

}

CGenicAffineTranform::~CGenicAffineTranform()
{
}

void CGenicAffineTranform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT3, m_b);
	DDX_Text(pDX, IDC_EDIT2, m_c);
	DDX_Text(pDX, IDC_EDIT4, m_d);
	DDX_Text(pDX, IDC_EDIT5, m_e);
	DDX_Text(pDX, IDC_EDIT6, m_f);
}


BEGIN_MESSAGE_MAP(CGenicAffineTranform, CDialogEx)
END_MESSAGE_MAP()


// CGenicAffineTranform 消息处理程序
