#pragma once


// CDialogMotionBlurParameters 对话框

class CDialogMotionBlurParameters : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMotionBlurParameters)

public:
	CDialogMotionBlurParameters(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogMotionBlurParameters();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOTION_BLUR_RESTORATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Xmotion;
	int m_Ymotion;
	BOOL m_bHoriMotion;
	afx_msg void OnBnClickedCheckOnlyHoriMotion();
	bool m_bRestoration;
	bool m_bOnlyHoriMotion;
	virtual BOOL OnInitDialog();
	int m_aver_grey;
};
