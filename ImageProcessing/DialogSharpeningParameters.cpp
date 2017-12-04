// DialogSharpeningParameters.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogSharpeningParameters.h"
#include "afxdialogex.h"


// CDialogSharpeningParameters �Ի���

IMPLEMENT_DYNAMIC(CDialogSharpeningParameters, CDialogEx)

CDialogSharpeningParameters::CDialogSharpeningParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_SHARPENING_PARAMETERS, pParent)
	, sigma(0.4)
	, ratioLow_High(0.4)
	, ratioHigh_Total(0.79)
	, m_radio_operatorType(0)
	, m_radio_laplacian_operatorType(0)
	, m_radio_kirschType(0)
	, m_check_bCalibration(FALSE)
	, bCheckSpatialSharpeningEnhancenent(FALSE)
{

}

CDialogSharpeningParameters::~CDialogSharpeningParameters()
{
}

void CDialogSharpeningParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SIGMA, sigma);
	DDX_Text(pDX, IDC_EDIT_RATIO_LH, ratioLow_High);
	DDX_Text(pDX, IDC_EDIT_RATIO_HT, ratioHigh_Total);
	DDX_Radio(pDX, IDC_RADIO_GRADS_OPERATOR, m_radio_operatorType);
	DDX_Radio(pDX, IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1, m_radio_laplacian_operatorType);
	DDX_Radio(pDX, IDC_RADIO_KIRSCH_OPERATOR_SELECT1, m_radio_kirschType);
	DDX_Check(pDX, IDC_CHECK_CALIBRATION, m_check_bCalibration);
	DDX_Check(pDX, IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT, bCheckSpatialSharpeningEnhancenent);
}


BEGIN_MESSAGE_MAP(CDialogSharpeningParameters, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_LAPLACIAN_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioLaplacianOperator)
	ON_BN_CLICKED(IDC_RADIO_GRADS_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioGradsOperator)
	ON_BN_CLICKED(IDC_RADIO_ROBERTS_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioRobertsOperator)
	ON_BN_CLICKED(IDC_RADIO_SOBEL_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioSobelOperator)
	ON_BN_CLICKED(IDC_RADIO_PREWITT_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioPrewittOperator)
	ON_BN_CLICKED(IDC_RADIO_ISTROPI_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioIstropiOperator)
	ON_BN_CLICKED(IDC_RADIO_CANNY_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioCannyOperator)
	ON_BN_CLICKED(IDC_RADIO_KIRSCH_OPERATOR, &CDialogSharpeningParameters::OnBnClickedRadioKirschOperator)
	ON_BN_CLICKED(IDC_RADIO_IMAGE_SHARPEN_EMBOSSMENT, &CDialogSharpeningParameters::OnBnClickedRadioImageSharpenEmbossment)
END_MESSAGE_MAP()


// CDialogSharpeningParameters ��Ϣ�������

BOOL CDialogSharpeningParameters::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogSharpeningParameters::OnBnClickedRadioGradsOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioRobertsOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioSobelOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioPrewittOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioIstropiOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioCannyOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(true);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(true);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(true);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->SetCheck(0);
	pCheckCalibration->EnableWindow(false);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	bCheckSpatialSharpeningEnhancenent = false;
	UpdateData(false);
	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_HIDE);
}

void CDialogSharpeningParameters::OnBnClickedRadioLaplacianOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(true);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(true);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(true);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(true);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_SHOW);
}

void CDialogSharpeningParameters::OnBnClickedRadioKirschOperator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->EnableWindow(true);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(true);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(true);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(true);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(true);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(true);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(true);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(true);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(true);

	bCheckSpatialSharpeningEnhancenent = false;
	UpdateData(false);
	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_HIDE);
}


void CDialogSharpeningParameters::OnBnClickedRadioImageSharpenEmbossment()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *pEditSigma = (CEdit *)GetDlgItem(IDC_EDIT_SIGMA);
	pEditSigma->EnableWindow(false);
	CEdit *pEditLH = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_LH);
	pEditLH->EnableWindow(false);
	CEdit *pEditHT = (CEdit *)GetDlgItem(IDC_EDIT_RATIO_HT);
	pEditHT->EnableWindow(false);

	CButton *pCheckCalibration = (CButton *)GetDlgItem(IDC_CHECK_CALIBRATION);
	pCheckCalibration->SetCheck(0);
	pCheckCalibration->EnableWindow(false);

	CButton *pButtonlaplace1 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT1);
	pButtonlaplace1->EnableWindow(false);
	CButton *pButtonlaplace2 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT2);
	pButtonlaplace2->EnableWindow(false);
	CButton *pButtonlaplace3 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT3);
	pButtonlaplace3->EnableWindow(false);
	CButton *pButtonlaplace4 = (CButton *)GetDlgItem(IDC_RADIO_LAPLACIAN_OPERATOR_SELECT4);
	pButtonlaplace4->EnableWindow(false);

	CButton *pButtonkirsch1 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT1);
	pButtonkirsch1->EnableWindow(false);
	CButton *pButtonkirsch2 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT2);
	pButtonkirsch2->EnableWindow(false);
	CButton *pButtonkirsch3 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT3);
	pButtonkirsch3->EnableWindow(false);
	CButton *pButtonkirsch4 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT4);
	pButtonkirsch4->EnableWindow(false);
	CButton *pButtonkirsch5 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT5);
	pButtonkirsch5->EnableWindow(false);
	CButton *pButtonkirsch6 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT6);
	pButtonkirsch6->EnableWindow(false);
	CButton *pButtonkirsch7 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT7);
	pButtonkirsch7->EnableWindow(false);
	CButton *pButtonkirsch8 = (CButton *)GetDlgItem(IDC_RADIO_KIRSCH_OPERATOR_SELECT8);
	pButtonkirsch8->EnableWindow(false);

	bCheckSpatialSharpeningEnhancenent = false;
	UpdateData(false);
	CButton *pButtonkirsch9 = (CButton *)GetDlgItem(IDC_CHECK_SPATIAL_SHARPENING_ENHANCEMENT);
	pButtonkirsch9->ShowWindow(SW_HIDE);
}
