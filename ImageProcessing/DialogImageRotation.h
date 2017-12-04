#pragma once


// CDialogImageRotation 对话框

class CDialogImageRotation : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageRotation)

public:
	CDialogImageRotation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogImageRotation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_ROTATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int r_x;
	int r_y;
	double r_thita;
};
