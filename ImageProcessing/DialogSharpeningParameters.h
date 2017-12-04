#pragma once


// CDialogSharpeningParameters 对话框

class CDialogSharpeningParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSharpeningParameters)

public:
	CDialogSharpeningParameters(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSharpeningParameters();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_SHARPENING_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double sigma;
	double ratioLow_High;
	double ratioHigh_Total;
	int m_radio_operatorType;
	int m_radio_laplacian_operatorType;
	int m_radio_kirschType;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioLaplacianOperator();
	afx_msg void OnBnClickedRadioGradsOperator();
	afx_msg void OnBnClickedRadioRobertsOperator();
	afx_msg void OnBnClickedRadioSobelOperator();
	afx_msg void OnBnClickedRadioPrewittOperator();
	afx_msg void OnBnClickedRadioIstropiOperator();
	afx_msg void OnBnClickedRadioCannyOperator();
	afx_msg void OnBnClickedRadioKirschOperator();
	afx_msg void OnBnClickedRadioImageSharpenEmbossment();
	BOOL m_check_bCalibration;
	BOOL bCheckSpatialSharpeningEnhancenent;
};
