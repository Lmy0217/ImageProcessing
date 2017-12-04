#pragma once


// CDialogMaskHighPromotion �Ի���

class CDialogMaskHighPromotion : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMaskHighPromotion)

public:
	CDialogMaskHighPromotion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogMaskHighPromotion();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MASK_HIGH_PROMOTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_myChoice;
	int m_radius;
	double m_sigma;
	afx_msg void OnBnClickedRadioGauss();
	afx_msg void OnBnClickedRadioMedan();
	afx_msg void OnBnClickedRadioMean();
	virtual BOOL OnInitDialog();
	double m_para_k;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	int m_radio_k;
};
