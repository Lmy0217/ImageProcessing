// DialogMaskHighPromotion.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogMaskHighPromotion.h"
#include "afxdialogex.h"


// CDialogMaskHighPromotion 对话框

IMPLEMENT_DYNAMIC(CDialogMaskHighPromotion, CDialogEx)

CDialogMaskHighPromotion::CDialogMaskHighPromotion(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MASK_HIGH_PROMOTION, pParent)
	, m_myChoice(0)
	, m_radius(1)
	, m_sigma(0.4)
	, m_radio_k(0)
	, m_para_k(1)

{

}

CDialogMaskHighPromotion::~CDialogMaskHighPromotion()
{
}

void CDialogMaskHighPromotion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_radius);
	DDX_Radio(pDX, IDC_RADIO_MEAN, m_myChoice);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_radius);
	DDX_Text(pDX, IDC_EDIT_GAUSS_SIGMA, m_sigma);
	DDX_Text(pDX, IDC_EDIT_PARAMETER_K, m_para_k);
	DDX_Radio(pDX, IDC_RADIO3, m_radio_k);
}


BEGIN_MESSAGE_MAP(CDialogMaskHighPromotion, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_GAUSS, &CDialogMaskHighPromotion::OnBnClickedRadioGauss)
	ON_BN_CLICKED(IDC_RADIO_MEDIAN, &CDialogMaskHighPromotion::OnBnClickedRadioMedan)
	ON_BN_CLICKED(IDC_RADIO_MEAN, &CDialogMaskHighPromotion::OnBnClickedRadioMean)
	ON_BN_CLICKED(IDC_RADIO3, &CDialogMaskHighPromotion::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDialogMaskHighPromotion::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CDialogMaskHighPromotion 消息处理程序


void CDialogMaskHighPromotion::OnBnClickedRadioGauss()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pStatic->ShowWindow(SW_SHOW);
	pEdit->ShowWindow(SW_SHOW);
}


void CDialogMaskHighPromotion::OnBnClickedRadioMedan()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pStatic->ShowWindow(SW_HIDE);
	pEdit->ShowWindow(SW_HIDE);
}


void CDialogMaskHighPromotion::OnBnClickedRadioMean()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pStatic->ShowWindow(SW_HIDE);
	pEdit->ShowWindow(SW_HIDE);
}


BOOL CDialogMaskHighPromotion::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pStatic->ShowWindow(SW_HIDE);
	pEdit->ShowWindow(SW_HIDE);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	m_para_k = 1.0;
	UpdateData(false);
	pEdit1->SetReadOnly(true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogMaskHighPromotion::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	m_para_k = 1.0;
	UpdateData(false);
	pEdit->SetReadOnly(true);
}


void CDialogMaskHighPromotion::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	m_para_k = 1.5;
	UpdateData(false);
	pEdit->SetReadOnly(false);
}
