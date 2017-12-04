#pragma once


// CDialogBitPlane 对话框

class CDialogBitPlane : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBitPlane)

public:
	CDialogBitPlane(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogBitPlane();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BIT_PLANE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int nBitPlane;
	afx_msg void OnBnClickedOk();
};
