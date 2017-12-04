// DialogGaussLowHighPassFiltering.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogGaussLowHighPassFiltering.h"
#include "afxdialogex.h"


// CDialogGaussLowHighPassFiltering �Ի���

IMPLEMENT_DYNAMIC(CDialogGaussLowHighPassFiltering, CDialogEx)

CDialogGaussLowHighPassFiltering::CDialogGaussLowHighPassFiltering(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GAUSS_LOW_HIGH_PASS_FILTERING, pParent)
	, m_D0(30)
{

}

CDialogGaussLowHighPassFiltering::~CDialogGaussLowHighPassFiltering()
{
}

void CDialogGaussLowHighPassFiltering::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_D0);
}


BEGIN_MESSAGE_MAP(CDialogGaussLowHighPassFiltering, CDialogEx)
END_MESSAGE_MAP()


// CDialogGaussLowHighPassFiltering ��Ϣ�������
