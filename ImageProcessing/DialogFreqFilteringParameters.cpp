// DialogFreqFilteringParameters.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogFreqFilteringParameters.h"
#include "afxdialogex.h"


// CDialogFreqFilteringParameters �Ի���

IMPLEMENT_DYNAMIC(CDialogFreqFilteringParameters, CDialogEx)

CDialogFreqFilteringParameters::CDialogFreqFilteringParameters(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FREQ_FILTERING_PARAMETERS, pParent)
	, m_alpha(98)
	, m_filteringRadius(50)
{

}

CDialogFreqFilteringParameters::~CDialogFreqFilteringParameters()
{
}

void CDialogFreqFilteringParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_alpha);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_filteringRadius);
}


BEGIN_MESSAGE_MAP(CDialogFreqFilteringParameters, CDialogEx)
END_MESSAGE_MAP()


// CDialogFreqFilteringParameters ��Ϣ�������
