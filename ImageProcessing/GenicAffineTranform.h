#pragma once


// CGenicAffineTranform �Ի���

class CGenicAffineTranform : public CDialogEx
{
	DECLARE_DYNAMIC(CGenicAffineTranform)

public:
	CGenicAffineTranform(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGenicAffineTranform();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERIC_AFFINE_TRANSFORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_a;
	double m_b;
	double m_c;
	double m_d;
	double m_e;
	double m_f;
};
