
// 3170106249SX15Dlg.h : header file
//

#pragma once


// CMy3170106249SX15Dlg dialog
class CMy3170106249SX15Dlg : public CDialogEx
{
// Construction
public:
	CMy3170106249SX15Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY3170106249SX15_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CString imgInputPath = "D:\\desktop\\RS\\12非监督分类\\实验数据\\GF1\\GF1.tif";
	CString imgOutputPath = "D:\\desktop\\RS\\12非监督分类\\实验数据\\GF1\\tryoutout.tif";
	//char * imgOutputPath2 = "D:\\desktop\\RS\\12非监督分类\\实验数据\\GF1\\tryoutout2.tif";
	//char * imgOutputPath1 = "D:\\desktop\\RS\\12非监督分类\\实验数据\\GF1\\tryout.txt";
	

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMean();
	afx_msg void OnBnClickedInfile();
	afx_msg void OnBnClickedOutfile();
	double dis(unsigned long source[], unsigned long p[],int iBands);
};
