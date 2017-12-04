#pragma once


// CDialogLogParameters 对话框

class CDialogLogParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogParameters)

public:
	CDialogLogParameters(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLogParameters();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOG_TRANSFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_log_c;
};
