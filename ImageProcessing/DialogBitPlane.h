#pragma once


// CDialogBitPlane �Ի���

class CDialogBitPlane : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBitPlane)

public:
	CDialogBitPlane(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogBitPlane();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BIT_PLANE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int nBitPlane;
	afx_msg void OnBnClickedOk();
};
