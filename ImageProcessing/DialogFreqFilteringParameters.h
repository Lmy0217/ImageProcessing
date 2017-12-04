#pragma once


// CDialogFreqFilteringParameters �Ի���

class CDialogFreqFilteringParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFreqFilteringParameters)

public:
	CDialogFreqFilteringParameters(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogFreqFilteringParameters();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FREQ_FILTERING_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_alpha;
	int m_filteringRadius;
};
