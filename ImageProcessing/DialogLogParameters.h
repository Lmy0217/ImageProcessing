#pragma once


// CDialogLogParameters �Ի���

class CDialogLogParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogParameters)

public:
	CDialogLogParameters(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogLogParameters();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOG_TRANSFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_log_c;
};
