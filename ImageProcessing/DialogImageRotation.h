#pragma once


// CDialogImageRotation �Ի���

class CDialogImageRotation : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImageRotation)

public:
	CDialogImageRotation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogImageRotation();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_ROTATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int r_x;
	int r_y;
	double r_thita;
};
