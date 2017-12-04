#pragma once


// CDialogImageMagnifier �Ի���

class CDialogImageMagnifier : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageMagnifier)

public:
	CDialogImageMagnifier(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogImageMagnifier();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_MAGNIFIER };
#endif
public:
	int m_zoom_number;   //�Ŵ���
	int m_radius;        //�Ŵ󾵰뾶
	CImage m_Image;      //ԭʼͼ��
	CImage m_saveImage;
	CImage m_ZoomImage;  //�Ŵ��ͼ��
	int m_Height;
	int m_Width;


	CRect rectStaticClient; //��ʾ�ͻ�����
	SCROLLINFO horz;        //ˮƽ����
	SCROLLINFO vert;        //��ֱ����
	BOOL  erase;            //������־  
	int sourcex;            //ԭʼͼ�����Ͻ�X����
	int sourcey;            //ԭʼͼ�����Ͻ�Y����
	int offsetx;            //�������ƶ���X����ƫ��
	int offsety;            //�������ƶ���Y����ƫ��

	CSize  m_size;           //λͼ��С
	BITMAP m_bmInfo;        // λͼ��Ϣ�ṹ
	CPoint m_pt;            // λͼ���Ͻ�λ��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
