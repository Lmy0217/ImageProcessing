#pragma once


// CDialogImageMagnifier 对话框

class CDialogImageMagnifier : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageMagnifier)

public:
	CDialogImageMagnifier(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogImageMagnifier();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_MAGNIFIER };
#endif
public:
	int m_zoom_number;   //放大倍数
	int m_radius;        //放大镜半径
	CImage m_Image;      //原始图像
	CImage m_saveImage;
	CImage m_ZoomImage;  //放大后图像
	int m_Height;
	int m_Width;


	CRect rectStaticClient; //显示客户区域
	SCROLLINFO horz;        //水平滚动
	SCROLLINFO vert;        //垂直滚动
	BOOL  erase;            //擦除标志  
	int sourcex;            //原始图像左上角X坐标
	int sourcey;            //原始图像左上角Y坐标
	int offsetx;            //滚动条移动后X坐标偏移
	int offsety;            //滚动条移动后Y坐标偏移

	CSize  m_size;           //位图大小
	BITMAP m_bmInfo;        // 位图信息结构
	CPoint m_pt;            // 位图左上角位置

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMagnifier();
	afx_msg void OnMinifier();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void ImageZoom(CImage * sImage, CImage * rImage);
	void ReplaceWithZoomArea(CPoint centerPt, int radius);
	void RestoreLastArea(CPoint centerPt, int radius);
};
