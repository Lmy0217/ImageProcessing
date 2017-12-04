#pragma once


// CDialogFreqFilteringParameters 对话框

class CDialogFreqFilteringParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFreqFilteringParameters)

public:
	CDialogFreqFilteringParameters(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogFreqFilteringParameters();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FREQ_FILTERING_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_alpha;
	int m_filteringRadius;
};
