// DialogScalingFactor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogScalingFactor.h"
#include "afxdialogex.h"


// CDialogScalingFactor �Ի���

IMPLEMENT_DYNAMIC(CDialogScalingFactor, CDialogEx)

CDialogScalingFactor::CDialogScalingFactor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SCALING_FACTOR, pParent)
	, mHoriScalingFactor(0)
	, mVeriScalingFactor(0)
{

}

CDialogScalingFactor::~CDialogScalingFactor()
{
}

void CDialogScalingFactor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HORI_SCALING_FACTOR, mHoriScalingFactor);
	DDX_Text(pDX, IDC_EDIT_VERI_SCALING_FACTOR, mVeriScalingFactor);
}


BEGIN_MESSAGE_MAP(CDialogScalingFactor, CDialogEx)
END_MESSAGE_MAP()


// CDialogScalingFactor ��Ϣ�������
