
// PalStudioDlg.h: 头文件
//

#pragma once

// CPalStudioDlg 对话框
class CPalStudioDlg : public CDialog
{
// 构造
public:
	CPalStudioDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PALSTUDIO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	
private:
	//
	// 主 TabBox 盒子
	//
	CTabCtrl tcTabBoxMain;
	INT      iTabBoxMain_PrevSel;
	INT      nTabPage;
	INT      iTabPageX;
	INT      iTabPageY;
	CDialog  dlgTabPage[11];

public:
	afx_msg void OnTcnSelchangeTabBoxMain(NMHDR* pNMHDR, LRESULT* pResult);
};
