#pragma once


// CDialogImageAddRatio �Ի���

class CDialogImageAddRatio : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageAddRatio)

public:
	CDialogImageAddRatio(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogImageAddRatio();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_RATIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int addRatio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
