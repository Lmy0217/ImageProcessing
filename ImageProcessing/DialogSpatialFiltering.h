#pragma once


// CDialogSpatialFiltering 对话框

class CDialogSpatialFiltering : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSpatialFiltering)

public:
	CDialogSpatialFiltering(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSpatialFiltering();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SMOOTHING_SPATIAL_FILTERING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_para_k;
	int m_XRadius;
	int m_YRadius;
	double m_sigma;
	BOOL m_checkImageEnhancement;
	int m_smooth_operator;
	int m_statistics_operator;
	int m_smooth_enhancement_type;	
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedRadioStatisticsFilteringOperator();
	afx_msg void OnBnClickedRadioNonsharpeningMaskImageEnhancement();
	afx_msg void OnBnClickedRadioHighPromotionImageEnhancement();
	afx_msg void OnBnClickedRadioGaussOperator();
	afx_msg void OnBnClickedRadioMeanOperator();
	afx_msg void OnBnClickedCheckSpatialImageFiltering();
	afx_msg void OnBnClickedOk();
};
