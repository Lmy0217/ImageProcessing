// DialogImageMagnifier.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogImageMagnifier.h"
#include "afxdialogex.h"


// CDialogImageMagnifier 对话框

IMPLEMENT_DYNAMIC(CDialogImageMagnifier, CDialogEx)

CDialogImageMagnifier::CDialogImageMagnifier(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_MAGNIFIER, pParent)
{
	m_zoom_number = 2;  //初始放大倍数为4
	m_radius = 120;      // 放大镜半径设为50
	m_Height = 0;
	m_Width = 0;

	erase = false;
}

CDialogImageMagnifier::~CDialogImageMagnifier()
{
}

void CDialogImageMagnifier::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogImageMagnifier, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_COMMAND(ID_MAGNIFIER, &CDialogImageMagnifier::OnMagnifier)
	ON_COMMAND(ID_MINIFIER, &CDialogImageMagnifier::OnMinifier)
	ON_WM_SETCURSOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDialogImageMagnifier 消息处理程序


BOOL CDialogImageMagnifier::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Width  = m_Image.GetWidth();
	m_Height = m_Image.GetHeight();
	int nBPP = m_Image.GetBPP();
	int nLineBytes = m_Image.GetPitch();
	sourcex = sourcey = 0;

	GetScrollInfo(SB_HORZ, &horz, SIF_ALL);
	horz.nMin = 0;
	horz.nMax = m_Width;
	SetScrollInfo(SB_HORZ, &horz);

	GetScrollInfo(SB_VERT, &vert, SIF_ALL);
	vert.nMin = 0;
	vert.nMax = m_Height;
	SetScrollInfo(SB_VERT, &vert);

	GetClientRect(&rectStaticClient);//得到控件的客户区
	rectStaticClient.NormalizeRect();
	m_size.cx = rectStaticClient.Size().cx;
	m_size.cy = rectStaticClient.Size().cy;
	m_size.cx = rectStaticClient.Width();    // zero based
	m_size.cy = rectStaticClient.Height();   // zero based
	ClientToScreen(&rectStaticClient);    //转换到屏幕坐标
	ScreenToClient(&rectStaticClient);    //控件屏幕坐标转换到相对于对话框的客户坐标
	m_pt.x = rectStaticClient.left;
	m_pt.y = rectStaticClient.top;

	offsetx = m_pt.x;
	offsety = m_pt.y;

	horz.cbSize = sizeof(SCROLLINFO);
	horz.fMask = SIF_ALL;
	horz.nMin = 0;
	horz.nMax = m_bmInfo.bmWidth - m_size.cx;
	horz.nPage = 0;
	horz.nPos = 0;
	horz.nTrackPos = 0;

	if (m_Width <= m_size.cx)
	{
		offsetx = m_pt.x;
		EnableScrollBarCtrl(SB_HORZ, false);
	}
	else
	{
		EnableScrollBarCtrl(SB_HORZ, true);
	}

	SetScrollInfo(SB_HORZ, &horz);

	vert.cbSize = sizeof(SCROLLINFO);
	vert.fMask = SIF_ALL;
	vert.nMin = 0;
	vert.nMax = m_Height - (m_size.cy);
	vert.nPage = 0;
	vert.nTrackPos = 0;
	if (m_Height <= m_size.cy)
	{
		if ((m_size.cy - m_Height) == 0)
			offsety = m_pt.y;
		else
			offsety = m_pt.y;
		EnableScrollBarCtrl(SB_VERT, false);
	}
	else
		EnableScrollBarCtrl(SB_VERT, true);

	SetScrollInfo(SB_VERT, &vert);
	InvalidateRect(&rectStaticClient);

	CRect rcClient;
	rcClient.left = 0;
	rcClient.right = m_Width <= m_size.cx ? m_Width + GetSystemMetrics(SM_CXVSCROLL) : m_size.cx;
	rcClient.top = 0;
	rcClient.bottom = m_Height <= m_size.cy ? m_Height + GetSystemMetrics(SM_CYVSCROLL) : m_size.cy;
	AdjustWindowRectEx(rcClient, GetStyle(), FALSE, GetExStyle());
	SetWindowPos(NULL, 0, 0, rcClient.Width(), rcClient.Height(), SWP_NOMOVE | SWP_NOZORDER);
	
	int x;
	int y;
	BYTE * pData = (BYTE *)m_Image.GetBits();
	m_saveImage.Destroy();
	VERIFY( m_saveImage.Create(m_Width, m_Height, nBPP, 0) );

	BYTE * pSaveData = (BYTE *)m_saveImage.GetBits();

	for (y = 0; y < m_Height; y++)
	for (x = 0; x < m_Width; x++)
	{
		pSaveData[y*nLineBytes + 3 * x + 0] = pData[y*nLineBytes + 3 * x + 0];
		pSaveData[y*nLineBytes + 3 * x + 1] = pData[y*nLineBytes + 3 * x + 1];
		pSaveData[y*nLineBytes + 3 * x + 2] = pData[y*nLineBytes + 3 * x + 2];
	}

	ImageZoom(&m_saveImage, &m_ZoomImage);
	m_pt.x = 0;
	m_pt.y = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogImageMagnifier::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point == m_pt)
		return;
	if (point.x > 0 && point.x < m_Width && point.y>0 && point.y < m_Height)
	{
		CPoint pt(m_pt.x + sourcex, m_pt.y + sourcey);
		RestoreLastArea(pt, m_radius);

		CPoint pt1(point.x + sourcex, point.y + sourcey);
		ReplaceWithZoomArea(pt1, m_radius);
	}

	m_pt = point;
	InvalidateRect(NULL, FALSE);;
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDialogImageMagnifier::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu menu; //定义下面要用到的cmenu对象
	menu.LoadMenu(IDR_MENU_ZOOM); //装载自定义的右键菜单 
	CMenu *pContextMenu = menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单  
	CPoint rdcpoint;//定义一个用于确定光标位置的位置 
	GetCursorPos(&rdcpoint);//获取当前光标的位置，以便使得菜单可以跟随光标 
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rdcpoint.x, rdcpoint.y, this);
	//在指定位置显示弹出菜单
	//this表示点击菜单的消息传递到本对话框，，，相应的改变其值也可以传递到其它对象。
	//如this->GetParent()，，则响应包含CArcSoft_EffectDlg.DoModal()函数的对象中的相
	//应函数了。

	CDialogEx::OnRButtonDown(nFlags, rdcpoint);
}


void CDialogImageMagnifier::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	m_Image.Draw(dc.m_hAttribDC,offsetx, offsety, m_size.cx, m_size.cy, sourcex, sourcey, m_size.cx,m_size.cy);

	erase = false; //恢复背景重画	


	CDialogEx::OnPaint();
}


void CDialogImageMagnifier::OnMagnifier()
{
	// TODO: 在此添加命令处理程序代码
	m_zoom_number++;
	if (m_zoom_number >= 10)
		m_zoom_number = 10;
	ImageZoom(&m_saveImage, &m_ZoomImage);
}


void CDialogImageMagnifier::OnMinifier()
{
	// TODO: 在此添加命令处理程序代码
	m_zoom_number--;
	if (m_zoom_number <= 1)
		m_zoom_number = 1;
	ImageZoom(&m_saveImage, &m_ZoomImage);
}


BOOL CDialogImageMagnifier::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nHitTest == HTCLIENT)
	{
		SetCursor(NULL);
	}
	else
	{
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
	return TRUE;

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CDialogImageMagnifier::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	GetScrollInfo(SB_HORZ, &horz, SIF_ALL);

	switch (nSBCode)
	{
	case SB_LEFT:
		horz.nPos = horz.nMin;
		break;
	case SB_RIGHT:
		horz.nPos = horz.nMax;
		break;
	case SB_LINELEFT:
		horz.nPos -= 1;
		if (horz.nPos<horz.nMin)
		{
			horz.nPos = horz.nMin;
			break;
		}
		break;
	case SB_LINERIGHT:
		horz.nPos += 1;
		if (horz.nPos>horz.nMax)
		{
			horz.nPos = horz.nMax;
			break;
		}
		break;
	case SB_PAGELEFT:
		horz.nPos -= 5;
		if (horz.nPos<horz.nMin)
		{
			horz.nPos = horz.nMin;
			break;
		}
		break;
	case SB_PAGERIGHT:
		horz.nPos += 5;
		if (horz.nPos>horz.nMax)
		{
			horz.nPos = horz.nMax;
			break;
		}
		break;
	case SB_THUMBPOSITION:
		horz.nPos = horz.nTrackPos;
		break;
	case SB_THUMBTRACK:
		horz.nPos = nPos;

		break;
	case SB_ENDSCROLL:
		break;
	}

	sourcex = horz.nPos;
	SetScrollInfo(SB_HORZ, &horz, SIF_ALL);
	erase = true;   //防止背景重画
	InvalidateRect(&rectStaticClient);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDialogImageMagnifier::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	GetScrollInfo(SB_VERT, &vert, SIF_ALL);
	switch (nSBCode)
	{
	case SB_TOP:
		vert.nPos = vert.nMin;
		break;
	case SB_BOTTOM:
		vert.nPos = vert.nMax;
		break;
	case SB_LINEUP:
		vert.nPos -= 1;
		if (vert.nPos<vert.nMin)
		{
			vert.nPos = vert.nMin;
			break;
		}
		break;
	case SB_LINEDOWN:
		vert.nPos += 1;
		if (vert.nPos>vert.nMax)
		{
			vert.nPos = vert.nMax;
			break;
		}
		break;
	case SB_PAGEUP:
		vert.nPos -= 5;
		if (vert.nPos<vert.nMin)
		{
			vert.nPos = vert.nMin;
			break;
		}
		break;
	case SB_PAGEDOWN:
		vert.nPos += 5;
		if (vert.nPos>vert.nMax)
		{
			vert.nPos = vert.nMax;
			break;
		}
		break;
	case SB_ENDSCROLL:
		break;
	case SB_THUMBPOSITION:
		break;
	case SB_THUMBTRACK:
		vert.nPos = nPos;

		break;
	}

	sourcey = vert.nPos;
	SetScrollInfo(SB_VERT, &vert, SIF_ALL);
	erase = true;//防止背景重画
	InvalidateRect(&rectStaticClient);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDialogImageMagnifier::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (erase)
		return false;
	else
		return CDialogEx::OnEraseBkgnd(pDC);
} 


void CDialogImageMagnifier::ImageZoom(CImage * sImage, CImage * rImage)
{
	int x;
	int y;

	int sWidth  = sImage->GetWidth();
	int sHeight = sImage->GetHeight();

	int rWidth  = (int)(sWidth * m_zoom_number);
	int rHeight = (int)(sHeight * m_zoom_number);

	rImage->Destroy();

	if (!rImage->Create(rWidth, rHeight, sImage->GetBPP(), 0))
		return;

	int sRowBytes = sImage->GetPitch();
	int rRowBytes = rImage->GetPitch();

	BYTE *sImageData = (BYTE *)sImage->GetBits();
	BYTE *rImageData = (BYTE *)rImage->GetBits();


	for (y = 1; y < rHeight - 1; y++)
	for (x = 1; x < rWidth - 1; x++)
	{
		double u = ((double) x) / m_zoom_number;
		double v = ((double) y) / m_zoom_number;
		int i = (int)u;
		int j = (int)v;
		u = u - i;
		v = v - j;

		if ((i >= sWidth - 1) && (j >= sHeight - 1))
		{
			rImageData[y*rRowBytes + x * 3]     = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3];
			rImageData[y*rRowBytes + x * 3 + 1] = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3 + 1];
			rImageData[y*rRowBytes + x * 3 + 2] = sImageData[(sHeight - 1) * sRowBytes + (sWidth - 1) * 3 + 2];
		}
		else if (j >= sHeight - 1)
		{
			rImageData[y*rRowBytes + x * 3]     = sImageData[(sHeight - 1) * sRowBytes + i * 3];
			rImageData[y*rRowBytes + x * 3 + 1] = sImageData[(sHeight - 1) * sRowBytes + i * 3 + 1];
			rImageData[y*rRowBytes + x * 3 + 2] = sImageData[(sHeight - 1) * sRowBytes + i * 3 + 2];
		}
		else if (i >= sWidth - 1)
		{
			rImageData[y*rRowBytes + x * 3] = sImageData[j * sRowBytes + (sWidth - 1) * 3];
			rImageData[y*rRowBytes + x * 3 + 1] = sImageData[j * sRowBytes + (sWidth - 1) * 3 + 1];
			rImageData[y*rRowBytes + x * 3 + 2] = sImageData[j * sRowBytes + (sWidth - 1) * 3 + 2];
		}
		else
		{
			rImageData[y*rRowBytes + x * 3] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3]));
			rImageData[y*rRowBytes + x * 3 + 1] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3 + 1])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3 + 1])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3 + 1])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3 + 1]));
			rImageData[y*rRowBytes + x * 3 + 2] = (BYTE)((1 - u)*(1 - v)*(sImageData[j * sRowBytes + i * 3 + 2])
				+ (1 - u)*v*(sImageData[(j + 1)*sRowBytes + i * 3 + 2])
				+ u*(1 - v)*(sImageData[j*sRowBytes + (i + 1) * 3 + 2])
				+ u*v*(sImageData[(j + 1)*sRowBytes + (i + 1) * 3 + 2]));
		}
	}
}


void CDialogImageMagnifier::ReplaceWithZoomArea(CPoint centerPt, int radius)
{

	int x;
	int y;
	BYTE *pData = (BYTE *)m_Image.GetBits();
	BYTE *pZoomData = (BYTE *)m_ZoomImage.GetBits();
	int nLineBytes = m_Image.GetPitch();
	int nZoomLineBytes = m_ZoomImage.GetPitch();

	CPoint cent = centerPt;
	cent.x = centerPt.x * m_zoom_number;
	cent.y = centerPt.y * m_zoom_number;

	for (y = -radius; y <= radius; y++)
	for (x = -radius; x <= radius; x++)
	{
		if ( centerPt.y + y >= 0 && centerPt.y + y < m_Height && centerPt.x + x >= 0 && centerPt.x + x < m_Width )
		{
			if (sqrt(x*x + y*y) <= radius)
			{
				pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 0] = pZoomData[(cent.y + y)*nZoomLineBytes + 3 * (cent.x + x) + 0];
				pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 1] = pZoomData[(cent.y + y)*nZoomLineBytes + 3 * (cent.x + x) + 1];
				pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 2] = pZoomData[(cent.y + y)*nZoomLineBytes + 3 * (cent.x + x) + 2];
			}
		}
	}

}



void CDialogImageMagnifier::RestoreLastArea(CPoint centerPt, int radius)
{
	int x;
	int y;

	BYTE *pData = (BYTE *)m_Image.GetBits();
	BYTE *psData = (BYTE *)m_saveImage.GetBits();
	int nLineBytes = m_Image.GetPitch();

	for (y = -radius; y <= radius; y++)
	for (x = -radius; x <= radius; x++)
	{
		if ( centerPt.y + y >= 0 && centerPt.y + y < m_Height && centerPt.x + x >= 0 && centerPt.x + x < m_Width )
		{
			pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 0] = psData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 0];
			pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 1] = psData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 1];
			pData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 2] = psData[(centerPt.y + y)*nLineBytes + 3 * (centerPt.x + x) + 2];
		}
	}
}
