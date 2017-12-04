#pragma once


// CDialogImageAddRatio 对话框

class CDialogImageAddRatio : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageAddRatio)

public:
	CDialogImageAddRatio(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogImageAddRatio();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_RATIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int addRatio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
