#pragma once


// CDialogPowerParameters �Ի���

class CDialogPowerParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPowerParameters)

public:
	CDialogPowerParameters(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPowerParameters();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_power_c;
	double m_power_gama;
};
