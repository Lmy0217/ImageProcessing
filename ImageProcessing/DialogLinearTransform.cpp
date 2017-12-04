// DialogLinearTransform.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogLinearTransform.h"
#include "afxdialogex.h"


// CDialogLinearTransform 对话框

IMPLEMENT_DYNAMIC(CDialogLinearTransform, CDialogEx)

CDialogLinearTransform::CDialogLinearTransform(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LINEAR_TRANSFORM, pParent)
{

}

CDialogLinearTransform::~CDialogLinearTransform()
{
}

void CDialogLinearTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogLinearTransform, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_CLEAR_BREAK_LINES, &CDialogLinearTransform::OnBnClickedClearBreakLines)
	ON_BN_CLICKED(IDOK, &CDialogLinearTransform::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDialogLinearTransform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	GetClientRect(&rect);
	m_rect.left = rect.left + 60;
	m_rect.top = rect.top + 60;
	m_rect.right = m_rect.left + 255;
	m_rect.bottom = m_rect.top + 255;
	pBreakPoints = new(BREAKPOINTLINK);
	BREAKPOINTLINK *newBreakPoint = new(BREAKPOINTLINK);
	pBreakPoints->m_pt = CPoint(m_rect.left, m_rect.bottom);
	pBreakPoints->pNext = newBreakPoint;
	newBreakPoint->m_pt = CPoint( m_rect.right,m_rect.top);
	newBreakPoint->pNext = NULL;
	bLMouseDown = FALSE;
	m_point.x = -1;
	m_point.y = -1;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// CDialogLinearTransform 消息处理程序

int CDialogLinearTransform::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CDialogLinearTransform::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
		return;

	m_point = point;

	bLMouseDown = true;
	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDialogLinearTransform::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
		return;
	if (bLMouseDown)
	{
		m_point = point;
		Invalidate();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDialogLinearTransform::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
		return;

	BREAKPOINTLINK *p = pBreakPoints,*q;
	while (p)
	{
		if (point.x == p->m_pt.x && ((point.x == m_rect.left) || (point.x == m_rect.right)))
		{
			p->m_pt.y = point.y;
			break;
		}
		else if(point == p->m_pt)
			break;
		else if (point.x < p->pNext->m_pt.x)
		{
			q = new(BREAKPOINTLINK);
			q->m_pt = point;
			q->pNext = p->pNext;
			p->pNext = q;
			break;
		}
	
		p = p->pNext;
	}

	bLMouseDown = FALSE;
	m_point.x = -1;
	m_point.y = -1;
	Invalidate();
	CDialogEx::OnLButtonUp(nFlags, point);
}



//显示图像坐标系统
void CDialogLinearTransform::DrawCoordinate(CPaintDC *pDC)
{
	CPen myPen, *oldPen;
	myPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldPen = pDC->SelectObject(&myPen);
	pDC->MoveTo(m_rect.left , m_rect.bottom + 20);
	pDC->LineTo(m_rect.left, m_rect.top - 20);
	pDC->LineTo(m_rect.left - 3, m_rect.top - 15);
	pDC->LineTo(m_rect.left + 3, m_rect.top - 15);
	pDC->LineTo(m_rect.left, m_rect.top - 20);

	pDC->MoveTo(m_rect.left - 20, m_rect.bottom);
	pDC->LineTo(m_rect.right + 20, m_rect.bottom);
	pDC->LineTo(m_rect.right + 15, m_rect.bottom - 3);
	pDC->LineTo(m_rect.right + 15, m_rect.bottom + 2);
	pDC->LineTo(m_rect.right + 20, m_rect.bottom);

	pDC->SelectObject(oldPen);
	myPen.DeleteObject();
}

void CDialogLinearTransform::DrawAverage(CPaintDC *pDC)
{
	CPen myPen, *oldPen;
	myPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = pDC->SelectObject(&myPen);

	pDC->MoveTo(m_rect.left + averagegrey, m_rect.top);
	pDC->LineTo(m_rect.left + averagegrey, m_rect.bottom);
	pDC->SelectObject(oldPen);
	myPen.DeleteObject();
}
void CDialogLinearTransform::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

					   // TODO: Add your message handler code here
	CBrush myBrush(RGB(255, 255, 255));
	dc.FillRect(m_rect, &myBrush);
	DrawCoordinate(&dc);
	DrawHistogram(&dc);
	DrawAverage(&dc);
	CPoint mypoint(0, 0);
	if (!bLMouseDown)
		DrawBreakLines(pBreakPoints, &dc);
	else
		DrawBreakLines(&m_point, pBreakPoints, &dc);
}


void CDialogLinearTransform::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	return;
}

void CDialogLinearTransform::DrawHistogram(CPaintDC * pDC)
{
	CPen myPen,*oldPen;
	myPen.CreatePen(PS_SOLID,1,RGB(180,180,180));
	oldPen = pDC->SelectObject(&myPen);
	for (int i = 0; i < 256; i++)
	{
		pDC->MoveTo(m_rect.left + i, m_rect.bottom - histogram[i]);
		pDC->LineTo(m_rect.left + i, m_rect.bottom);
	}
	pDC->SelectObject(oldPen);
	myPen.DeleteObject();
}


void CDialogLinearTransform::DrawBreakLines(CPoint *pt, BREAKPOINTLINK *pBPLink, CPaintDC * pDC)
{
	CPen myPen, *oldPen;
	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = pDC->SelectObject(&myPen);
	BREAKPOINTLINK *p = pBPLink;
	if (p == NULL) return;

	p = pBPLink;
	pDC->MoveTo(p->m_pt);
	while (p->pNext != NULL)
	{
		if ( ((pt->x < p->pNext->m_pt.x && pt->x >= p->m_pt.x))|| (!p->pNext->pNext && pt->x == m_rect.right) )
		{
			pDC->LineTo(*pt);
		}
		pDC->LineTo(p->pNext->m_pt);
		p = p->pNext;
	}

	CString str;
	str.Format(L"%3d,%3d", pt->x - m_rect.left,  m_rect.bottom - pt->y );
	CRect  cRect;
	cRect.SetRect(pt->x+5,pt->y+5,pt->x+65,pt->y+25);
	pDC->DrawText(str, &cRect, DT_CENTER);
	pDC->SelectObject(oldPen);
	myPen.DeleteObject();

	return;
}

void CDialogLinearTransform::DrawBreakLines(BREAKPOINTLINK *pBPLink, CPaintDC * pDC)
{
	CPen myPen, *oldPen;
	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = pDC->SelectObject(&myPen);
	BREAKPOINTLINK *p = pBPLink;
	if (p == NULL) return;
	pDC->MoveTo(p->m_pt);
	while (p->pNext != NULL)
	{
		pDC->LineTo(p->pNext->m_pt);
		p = p->pNext;
	}
	pDC->SelectObject(oldPen);
	myPen.DeleteObject();
	return;
}

void CDialogLinearTransform::OnBnClickedClearBreakLines()
{
	// TODO: 在此添加控件通知处理程序代码
	BREAKPOINTLINK *p = pBreakPoints;
	p = p->pNext;
	while (p->pNext)
	{
		pBreakPoints->pNext = p->pNext;
		delete p;
		p = pBreakPoints->pNext;
	}
	pBreakPoints->m_pt.x = m_rect.left;
	pBreakPoints->m_pt.y = m_rect.bottom;
	pBreakPoints->pNext->m_pt.x = m_rect.right;
	pBreakPoints->pNext->m_pt.y = m_rect.top;
	pBreakPoints->pNext->pNext = NULL;
	Invalidate();
	return;
}


void CDialogLinearTransform::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	BREAKPOINTLINK *p = pBreakPoints;
	while (p)
	{
		p->m_pt.x = p->m_pt.x - m_rect.left;
		p->m_pt.y = m_rect.bottom - p->m_pt.y;
		p = p->pNext;
	}

	p = pBreakPoints;
	while (p)
	{
		if (p->pNext)
		{
			if (p->m_pt.x == p->pNext->m_pt.x)
  		        p->m_k = p->pNext->m_pt.y;
			else
				p->m_k = ((double)(p->pNext->m_pt.y - p->m_pt.y)) / (p->pNext->m_pt.x - p->m_pt.x);
		}
		else
			p->m_k = p->m_pt.y;
		p = p->pNext;
	}

	CDialogEx::OnOK();
}
