#pragma once


// CDialogNoiseParameters �Ի���

class CDialogNoiseParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNoiseParameters)

public:
	CDialogNoiseParameters(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNoiseParameters();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOISE_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_radio1;
	BOOL m_check1;
	double m_pa;
	double m_pb;
	double m_ua;
	double m_ub;
	double m_gauess_mu;
	double m_gauess_sigma;
	double m_gauess_k;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};
