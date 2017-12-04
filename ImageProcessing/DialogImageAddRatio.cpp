// DialogImageAddRatio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogImageAddRatio.h"
#include "afxdialogex.h"


// CDialogImageAddRatio �Ի���

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


// CDialogImageAddRatio ��Ϣ�������


BOOL CDialogImageAddRatio::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	addRatio = 50;
	CScrollBar *pScrollBarHueUp = (CScrollBar *)GetDlgItem(IDC_SCROLLBAR_ADD_RATIO);
	pScrollBarHueUp->SetScrollRange(0, 100);
	pScrollBarHueUp->SetScrollPos(addRatio, true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogImageAddRatio::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
