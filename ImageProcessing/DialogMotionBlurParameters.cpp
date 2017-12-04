// DialogMotionBlurParameters.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogMotionBlurParameters.h"
#include "afxdialogex.h"


// CDialogMotionBlurParameters �Ի���

IMPLEMENT_DYNAMIC(CDialogMotionBlurParameters, CDialogEx)

CDialogMotionBlurParameters::CDialogMotionBlurParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MOTION_BLUR_RESTORATION, pParent)
	, m_Xmotion(10)
	, m_Ymotion(10)
	, m_bHoriMotion(TRUE)
	, m_bRestoration(FALSE)
	, m_bOnlyHoriMotion(TRUE)
	, m_aver_grey(100)
{

}

CDialogMotionBlurParameters::~CDialogMotionBlurParameters()
{
}

void CDialogMotionBlurParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOTION_X, m_Xmotion);
	DDX_Text(pDX, IDC_EDIT_MOTION_Y, m_Ymotion);
	DDX_Check(pDX, IDC_CHECK_ONLY_HORI_MOTION, m_bHoriMotion);
	DDX_Text(pDX, IDC_EDIT_AVER_GREY, m_aver_grey);
}


BEGIN_MESSAGE_MAP(CDialogMotionBlurParameters, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_ONLY_HORI_MOTION, &CDialogMotionBlurParameters::OnBnClickedCheckOnlyHoriMotion)
END_MESSAGE_MAP()


// CDialogMotionBlurParameters ��Ϣ�������


void CDialogMotionBlurParameters::OnBnClickedCheckOnlyHoriMotion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bHoriMotion = !m_bHoriMotion;
	UpdateData(false);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_MOTION_Y);
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_YDIR);

	if (m_bHoriMotion)
	{
		pEdit->ShowWindow(SW_HIDE);
		pStatic->ShowWindow(SW_HIDE);
		m_Ymotion = 0;
	}
	else
	{
		pEdit->ShowWindow(SW_SHOW);
		pStatic->ShowWindow(SW_SHOW);
		m_Ymotion = 10;

	}
}


BOOL CDialogMotionBlurParameters::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_AVER_GREY);
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_AVER_GREY);

	if (m_bRestoration)
	{
		pEdit->ShowWindow(SW_SHOW);
		pStatic->ShowWindow(SW_SHOW);
	}
	else
	{
		pEdit->ShowWindow(SW_HIDE);
		pStatic->ShowWindow(SW_HIDE);
	}

	CButton *pCheck = (CButton *)GetDlgItem(IDC_CHECK_ONLY_HORI_MOTION);
	pCheck->EnableWindow(!m_bOnlyHoriMotion);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
