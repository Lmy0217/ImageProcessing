#pragma once


// CDialogPowerParameters 对话框

class CDialogPowerParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPowerParameters)

public:
	CDialogPowerParameters(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPowerParameters();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_PARAMETERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_power_c;
	double m_power_gama;
};
