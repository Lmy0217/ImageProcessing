#pragma once


// CDialogGaussLowHighPassFiltering 对话框

class CDialogGaussLowHighPassFiltering : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGaussLowHighPassFiltering)

public:
	CDialogGaussLowHighPassFiltering(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogGaussLowHighPassFiltering();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAUSS_LOW_HIGH_PASS_FILTERING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_D0;
};
