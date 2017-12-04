// DialogBitPlane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogBitPlane.h"
#include "afxdialogex.h"


// CDialogBitPlane �Ի���

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


// CDialogBitPlane ��Ϣ�������


void CDialogBitPlane::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
