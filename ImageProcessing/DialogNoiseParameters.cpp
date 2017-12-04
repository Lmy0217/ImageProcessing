// DialogNoiseParameters.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogNoiseParameters.h"
#include "afxdialogex.h"


// CDialogNoiseParameters 对话框

IMPLEMENT_DYNAMIC(CDialogNoiseParameters, CDialogEx)

CDialogNoiseParameters::CDialogNoiseParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_NOISE_PARAMETERS, pParent)
	, m_pa(0.1)
	, m_pb(0.1)
	, m_ua(0)
	, m_ub(60)
	, m_gauess_k(128)
	, m_gauess_mu(0)
	, m_gauess_sigma(1)
	, m_radio1(0)
	, m_check1(true)
{

}

CDialogNoiseParameters::~CDialogNoiseParameters()
{
}

void CDialogNoiseParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Text(pDX, IDC_EDIT_PA, m_pa);
	DDX_Text(pDX, IDC_EDIT_PB, m_pb);
	DDX_Text(pDX, IDC_EDIT_UA, m_ua);
	DDX_Text(pDX, IDC_EDIT_UB, m_ub);
	DDX_Text(pDX, IDC_EDIT_GAUESS_MU, m_gauess_mu);
	DDX_Text(pDX, IDC_EDIT_GAUESS_SIGMA, m_gauess_sigma);
	DDX_Text(pDX, IDC_EDIT_GAUESS_K, m_gauess_k);
}


BEGIN_MESSAGE_MAP(CDialogNoiseParameters, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDialogNoiseParameters::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDialogNoiseParameters::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDialogNoiseParameters::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CDialogNoiseParameters 消息处理程序


BOOL CDialogNoiseParameters::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	((CEdit*)GetDlgItem(IDC_EDIT_PA))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_PB))->EnableWindow(true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogNoiseParameters::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	((CEdit*)GetDlgItem(IDC_EDIT_PA))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_PB))->EnableWindow(true);

	((CEdit*)GetDlgItem(IDC_EDIT_UA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_UB))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_MU))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_SIGMA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_K))->EnableWindow(false);
}


void CDialogNoiseParameters::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	((CEdit*)GetDlgItem(IDC_EDIT_PA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_PB))->EnableWindow(false);

	((CEdit*)GetDlgItem(IDC_EDIT_UA))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_UB))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_MU))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_SIGMA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_K))->EnableWindow(false);
}


void CDialogNoiseParameters::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	((CEdit*)GetDlgItem(IDC_EDIT_PA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_PB))->EnableWindow(false);

	((CEdit*)GetDlgItem(IDC_EDIT_UA))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_UB))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_MU))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_SIGMA))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT_GAUESS_K))->EnableWindow(true);
}
