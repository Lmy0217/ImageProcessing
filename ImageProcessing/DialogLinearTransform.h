#pragma once

// CDialogLinearTransform 对话框

class CDialogLinearTransform : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLinearTransform)

public:
	CDialogLinearTransform(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLinearTransform();

	typedef struct BreakPointLink
	{
		CPoint m_pt;
		double m_k;
		struct BreakPointLink *pNext;
	} BREAKPOINTLINK;

	BREAKPOINTLINK *pBreakPoints;
	BREAKPOINTLINK *plink;

	int histogram[256];
	int averagegrey;
	CRect m_rect;
	CPoint m_point;
	bool bLMouseDown;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LINEAR_TRANSFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	void DrawAverage(CPaintDC *pDC);
	void DrawCoordinate(CPaintDC *pDC);
	void DrawHistogram(CPaintDC* pDC);
	void DrawBreakLines(BREAKPOINTLINK *pBPLink, CPaintDC * pDC);
	void DrawBreakLines(CPoint *pt, BREAKPOINTLINK *pBPLink, CPaintDC *pDC);
	afx_msg void OnBnClickedClearBreakLines();
	afx_msg void OnBnClickedOk();
};
