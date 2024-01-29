
// PalStudioDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PalStudio.h"
#include "PalStudioDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPalStudioDlg 对话框



CPalStudioDlg::CPalStudioDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PALSTUDIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPalStudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPalStudioDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BOX_MAIN, &CPalStudioDlg::OnTcnSelchangeTabBoxMain)
END_MESSAGE_MAP()


// CPalStudioDlg 消息处理程序

BOOL CPalStudioDlg::OnInitDialog()
{
	INT i;

	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//////////////////////////////////////////////////
	///
	/// 加载用户添加的控件
	///
	// 
   // 将TabControl控件变量关联到资源编辑器中的TabControl控件
	// 
	tcTabBoxMain.SubclassDlgItem(IDC_TAB_BOX_MAIN, this);
	//
	// 添加Tab页
	//
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;

	const LPWSTR lpzsTabOpName[] = {
		L"< 店铺 >", L"< 敌人 >",     L"< 队员 >",   L"< 仙术 >", L"< 战斗 >",
		L"< 术谱 >", L"< 行动特效 >", L"< 修行晋 >", L"< 场景 >", L"< 对象 >",
		L"< 脚本 >"
	};

	iTabPageX = 0;
	iTabPageY = 10;
	for (nTabPage = 0; nTabPage < sizeof(lpzsTabOpName) / sizeof(lpzsTabOpName[0]); nTabPage++)
	{
		tcItem.pszText = lpzsTabOpName[nTabPage];
		tcTabBoxMain.InsertItem(nTabPage, &tcItem);
		dlgTabPage[nTabPage].Create(IDD_TAB_FIRST + nTabPage, this);
	}

	iTabBoxMain_PrevSel = 0;
	dlgTabPage[iTabBoxMain_PrevSel].ShowWindow(SW_SHOW);
	///
	/// 加载用户添加的控件
	///
	//////////////////////////////////////////////////

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPalStudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPalStudioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPalStudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPalStudioDlg::OnTcnSelchangeTabBoxMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 获取选中的Tab页索引
	int tabIndex = tcTabBoxMain.GetCurSel();

	// 显示当前选中的对话框
	if (tabIndex != -1) dlgTabPage[tabIndex].ShowWindow(SW_SHOW);

	// 隐藏之前选中的对话框
	if (iTabBoxMain_PrevSel != -1) dlgTabPage[iTabBoxMain_PrevSel].ShowWindow(SW_HIDE);

	iTabBoxMain_PrevSel = tabIndex;

	*pResult = 0;
}
