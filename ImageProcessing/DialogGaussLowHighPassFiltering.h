#pragma once


// CDialogGaussLowHighPassFiltering �Ի���

class CDialogGaussLowHighPassFiltering : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGaussLowHighPassFiltering)

public:
	CDialogGaussLowHighPassFiltering(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogGaussLowHighPassFiltering();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAUSS_LOW_HIGH_PASS_FILTERING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_D0;
};
