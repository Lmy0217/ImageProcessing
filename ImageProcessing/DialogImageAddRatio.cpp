// DialogImageAddRatio.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogImageAddRatio.h"
#include "afxdialogex.h"


// CDialogImageAddRatio 对话框

IMPLEMENT_DYNAMIC(CDialogImageAddRatio, CDialogEx)

CDialogImageAddRatio::CDialogImageAddRatio(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_RATIO, pParent)
	, addRatio(0)
{

}

CDialogImageAddRatio::~CDialogImageAddRatio()
{
}

void CDialogImageAddRatio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Scroll(pDX, IDC_SCROLLBAR_ADD_RATIO, addRatio);
	DDV_MinMaxInt(pDX, addRatio, 0, 100);
}


BEGIN_MESSAGE_MAP(CDialogImageAddRatio, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDialogImageAddRatio 消息处理程序


BOOL CDialogImageAddRatio::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	addRatio = 50;
	CScrollBar *pScrollBarHueUp = (CScrollBar *)GetDlgItem(IDC_SCROLLBAR_ADD_RATIO);
	pScrollBarHueUp->SetScrollRange(0, 100);
	pScrollBarHueUp->SetScrollPos(addRatio, true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogImageAddRatio::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int mID = pScrollBar->GetDlgCtrlID();
	switch (nSBCode)
	{
		case SB_LINELEFT:
			addRatio--;
			break;
		case SB_LINERIGHT:
			addRatio++;
			break;
		case SB_PAGELEFT:
			addRatio -= 10;
			break;
		case SB_PAGERIGHT:
			addRatio += 10;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			addRatio = nPos - 30;
			break;
		default:
			break;
	}
	pScrollBar->SetScrollPos(addRatio + 30);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
