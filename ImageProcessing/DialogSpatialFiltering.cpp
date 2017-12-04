// DialogSpatialFiltering.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogSpatialFiltering.h"
#include "afxdialogex.h"


// CDialogSpatialFiltering 对话框

IMPLEMENT_DYNAMIC(CDialogSpatialFiltering, CDialogEx)

CDialogSpatialFiltering::CDialogSpatialFiltering(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SMOOTHING_SPATIAL_FILTERING, pParent)
	, m_XRadius(1)
	, m_YRadius(1)	
	, m_para_k(1)
	, m_sigma(2)
	, m_checkImageEnhancement(FALSE)
	, m_smooth_operator(0)
	, m_statistics_operator(0)
	, m_smooth_enhancement_type(-1)
{

}

CDialogSpatialFiltering::~CDialogSpatialFiltering()
{
}

void CDialogSpatialFiltering::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XRADIUS, m_XRadius);
	DDX_Text(pDX, IDC_EDIT_YRADIUS, m_YRadius);	
	DDX_Text(pDX, IDC_EDIT_PARAMETER_K, m_para_k);
	DDX_Text(pDX, IDC_EDIT_GAUSS_SIGMA, m_sigma);
	DDX_Check(pDX, IDC_CHECK_SPATIAL_IMAGE_FILTERING, m_checkImageEnhancement);
	DDX_Radio(pDX, IDC_RADIO_MEAN_OPERATOR, m_smooth_operator);
	DDX_Radio(pDX, IDC_RADIO_MEDIAN_OPERATOR, m_statistics_operator);
	DDX_Radio(pDX, IDC_RADIO_NONSHARPENING_MASK_IMAGE_ENHANCEMENT, m_smooth_enhancement_type);
}


BEGIN_MESSAGE_MAP(CDialogSpatialFiltering, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_STATISTICS_FILTERING_OPERATOR, &CDialogSpatialFiltering::OnBnClickedRadioStatisticsFilteringOperator)
	ON_BN_CLICKED(IDC_RADIO_NONSHARPENING_MASK_IMAGE_ENHANCEMENT, &CDialogSpatialFiltering::OnBnClickedRadioNonsharpeningMaskImageEnhancement)
	ON_BN_CLICKED(IDC_RADIO_HIGH_PROMOTION_IMAGE_ENHANCEMENT, &CDialogSpatialFiltering::OnBnClickedRadioHighPromotionImageEnhancement)
	ON_BN_CLICKED(IDC_RADIO_GAUSS_OPERATOR, &CDialogSpatialFiltering::OnBnClickedRadioGaussOperator)
	ON_BN_CLICKED(IDC_RADIO_MEAN_OPERATOR, &CDialogSpatialFiltering::OnBnClickedRadioMeanOperator)
	ON_BN_CLICKED(IDC_CHECK_SPATIAL_IMAGE_FILTERING, &CDialogSpatialFiltering::OnBnClickedCheckSpatialImageFiltering)
	ON_BN_CLICKED(IDOK, &CDialogSpatialFiltering::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSpatialFiltering 消息处理程序


BOOL CDialogSpatialFiltering::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CButton *pButton1 = (CButton *)GetDlgItem(IDC_RADIO_NONSHARPENING_MASK_IMAGE_ENHANCEMENT);
	CButton *pButton2 = (CButton *)GetDlgItem(IDC_RADIO_HIGH_PROMOTION_IMAGE_ENHANCEMENT);
	pButton1->EnableWindow(false);
	pButton2->EnableWindow(false);
	
	CButton *pButton3 = (CButton *)GetDlgItem(IDC_RADIO_MININUM_OPERATOR);
	CButton *pButton4 = (CButton *)GetDlgItem(IDC_RADIO_MEDIAN_OPERATOR);
	CButton *pButton5 = (CButton *)GetDlgItem(IDC_RADIO_MIDDLE_OPERATOR);
	CButton *pButton6 = (CButton *)GetDlgItem(IDC_RADIO_MAXINUM_OPERATOR);
	CStatic * pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC);
	pButton3->ShowWindow(SW_HIDE);
	pButton4->ShowWindow(SW_HIDE);
	pButton5->ShowWindow(SW_HIDE);
	pButton6->ShowWindow(SW_HIDE);
	pStatic1->ShowWindow(SW_HIDE);

	CStatic * pStatic2 = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	pStatic2->ShowWindow(SW_HIDE);
	CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC_GAUSS);
	pStatic3->ShowWindow(SW_HIDE);
	CStatic * pStatic4 = (CStatic *)GetDlgItem(IDC_STATIC_GAUSS);
	pStatic4->ShowWindow(SW_HIDE);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pEdit1->ShowWindow(SW_HIDE);

	m_para_k = 1.0;
	UpdateData(false);
	CStatic * pStatic5 = (CStatic *)GetDlgItem(IDC_STATIC_K);
	pStatic5->ShowWindow(SW_HIDE);
	CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	pEdit2->SetReadOnly(true);
	pEdit2->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialogSpatialFiltering::OnBnClickedCheckSpatialImageFiltering()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CButton *pButton1 = (CButton *)GetDlgItem(IDC_RADIO_NONSHARPENING_MASK_IMAGE_ENHANCEMENT);
	CButton *pButton2 = (CButton *)GetDlgItem(IDC_RADIO_HIGH_PROMOTION_IMAGE_ENHANCEMENT);
	pButton1->EnableWindow(m_checkImageEnhancement);
	pButton2->EnableWindow(m_checkImageEnhancement);
	if (m_checkImageEnhancement)
	{
		CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_K);
		pStatic3->ShowWindow(SW_SHOW);
		CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
		pEdit2->ShowWindow(SW_SHOW);
		m_smooth_enhancement_type = 0;
		UpdateData(false);

	}
	else
	{
		CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_K);
		pStatic3->ShowWindow(SW_HIDE);
		CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
		pEdit2->ShowWindow(SW_HIDE);
		m_smooth_enhancement_type = -1;
		UpdateData(false);
	}
}

void CDialogSpatialFiltering::OnBnClickedRadioMeanOperator()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pButton3 = (CButton *)GetDlgItem(IDC_RADIO_MININUM_OPERATOR);
	CButton *pButton4 = (CButton *)GetDlgItem(IDC_RADIO_MEDIAN_OPERATOR);
	CButton *pButton5 = (CButton *)GetDlgItem(IDC_RADIO_MIDDLE_OPERATOR);
	CButton *pButton6 = (CButton *)GetDlgItem(IDC_RADIO_MAXINUM_OPERATOR);
	CStatic * pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC);
	pButton3->ShowWindow(SW_HIDE);
	pButton4->ShowWindow(SW_HIDE);
	pButton5->ShowWindow(SW_HIDE);
	pButton6->ShowWindow(SW_HIDE);
	pStatic1->ShowWindow(SW_HIDE);

	CStatic * pStatic2 = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	pStatic2->ShowWindow(SW_HIDE);
	CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC_GAUSS);
	pStatic3->ShowWindow(SW_HIDE);
	CStatic * pStatic4 = (CStatic *)GetDlgItem(IDC_STATIC_GAUSS);
	pStatic4->ShowWindow(SW_HIDE);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pEdit1->ShowWindow(SW_HIDE);

}

void CDialogSpatialFiltering::OnBnClickedRadioGaussOperator()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pButton3 = (CButton *)GetDlgItem(IDC_RADIO_MININUM_OPERATOR);
	CButton *pButton4 = (CButton *)GetDlgItem(IDC_RADIO_MEDIAN_OPERATOR);
	CButton *pButton5 = (CButton *)GetDlgItem(IDC_RADIO_MIDDLE_OPERATOR);
	CButton *pButton6 = (CButton *)GetDlgItem(IDC_RADIO_MAXINUM_OPERATOR);
	CStatic * pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC);
	pButton3->ShowWindow(SW_HIDE);
	pButton4->ShowWindow(SW_HIDE);
	pButton5->ShowWindow(SW_HIDE);
	pButton6->ShowWindow(SW_HIDE);
	pStatic1->ShowWindow(SW_HIDE);

	CStatic * pStatic2 = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	pStatic2->ShowWindow(SW_SHOW);
	CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC_GAUSS);
	pStatic3->ShowWindow(SW_SHOW);
	CStatic * pStatic4 = (CStatic *)GetDlgItem(IDC_STATIC_GAUSS);
	pStatic4->ShowWindow(SW_SHOW);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pEdit1->ShowWindow(SW_SHOW);
}

void CDialogSpatialFiltering::OnBnClickedRadioStatisticsFilteringOperator()
{
	// TODO: 在此添加控件通知处理程序代码

	CButton *pButton3 = (CButton *)GetDlgItem(IDC_RADIO_MININUM_OPERATOR);
	CButton *pButton4 = (CButton *)GetDlgItem(IDC_RADIO_MEDIAN_OPERATOR);
	CButton *pButton5 = (CButton *)GetDlgItem(IDC_RADIO_MIDDLE_OPERATOR);
	CButton *pButton6 = (CButton *)GetDlgItem(IDC_RADIO_MAXINUM_OPERATOR);
	CStatic * pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC);
	pButton3->ShowWindow(SW_SHOW);
	pButton4->ShowWindow(SW_SHOW);
	pButton5->ShowWindow(SW_SHOW);
	pButton6->ShowWindow(SW_SHOW);
	pStatic1->ShowWindow(SW_SHOW);

	CStatic * pStatic2 = (CStatic *)GetDlgItem(IDC_STATIC_SIGMA);
	pStatic2->ShowWindow(SW_HIDE);
	CStatic * pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_STATISTIC_GAUSS);
	pStatic3->ShowWindow(SW_HIDE);
	CStatic * pStatic4 = (CStatic *)GetDlgItem(IDC_STATIC_GAUSS);
	pStatic4->ShowWindow(SW_HIDE);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_GAUSS_SIGMA);
	pEdit1->ShowWindow(SW_HIDE);

	CStatic * pStatic5 = (CStatic *)GetDlgItem(IDC_STATIC_K);
	pStatic5->ShowWindow(SW_HIDE);

	CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	pEdit2->ShowWindow(SW_HIDE);
}

void CDialogSpatialFiltering::OnBnClickedRadioNonsharpeningMaskImageEnhancement()
{
	// TODO: 在此添加控件通知处理程序代码
	m_smooth_enhancement_type = 0;
	m_para_k = 1.0;
	UpdateData(false);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	pEdit1->SetReadOnly(true);
}


void CDialogSpatialFiltering::OnBnClickedRadioHighPromotionImageEnhancement()
{
	// TODO: 在此添加控件通知处理程序代码
	m_smooth_enhancement_type = 1;
	m_para_k = 1.5;
	UpdateData(false);
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDIT_PARAMETER_K);
	pEdit1->SetReadOnly(false);
}


void CDialogSpatialFiltering::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_XRadius <= 0 || m_YRadius <= 0)
	{
		AfxMessageBox(L"滤波半径必须大于0");
		return;
	}
	CDialogEx::OnOK();
}
