
// video_mfcDlg.cpp : 实现文件
#include "stdafx.h"
#include "video_mfc.h"
#include "video_mfcDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cvideo_mfcDlg 对话框



Cvideo_mfcDlg::Cvideo_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cvideo_mfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cvideo_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}

BEGIN_MESSAGE_MAP(Cvideo_mfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDREAD, &Cvideo_mfcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDSTOP, &Cvideo_mfcDlg::OnBnClickedStop)
END_MESSAGE_MAP()
void Cvideo_mfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int pos;
	switch (nIDEvent)
	{
	case 1:
		// 如果收到ID为1的定时器的消息则调用func1函数
		if (Isread)
		{
			pos = m_slider.GetPos();
			m_slider.SetPos(pos + 1);
		}
		break;
	case 2:
		// 如果收到ID为2的定时器的消息则调用func2函数      
		
		break;
	
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
void Cvideo_mfcDlg::OnBnClickedOk()
{

	Isread = 1;
	Mat frame;
	int nElapse = 1000;
	SetTimer(1, nElapse, NULL);
	while (Isread == 1)
	{
		capture >> frame;
		if (!frame.empty())
		{
			resize(frame, frame, Size(screenRect.right, screenRect.bottom));
			imshow(windowname, frame);
			waitKey(1000/capture.get(CV_CAP_PROP_FPS));
		}
		else
		{
			break;
		}

	}
}


void Cvideo_mfcDlg::OnBnClickedStop()
{
	Isread = !Isread;
	KillTimer(1);
}


// Cvideo_mfcDlg 消息处理程序

BOOL Cvideo_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	Isread = false;
	capture.open("test.mp4");
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//总帧数
	int rate = capture.get(CV_CAP_PROP_FPS);//1秒的帧数
	
	
	long sum_time = totalFrameNumber/ rate;
	if (!capture.isOpened())
	{
		cout << "error" << endl;
		MessageBox(_T("read error"));
	}
	sprintf(windowname, "%s", "window");
	
	
	GetDlgItem(IDC_SCREEN)->GetClientRect(&screenRect);
	HWND HMain = GetDlgItem(IDC_SCREEN)->GetSafeHwnd();
	namedWindow(windowname, WINDOW_AUTOSIZE);
	HWND HScreen = (HWND)cvGetWindowHandle(windowname);
	HWND hParent = ::GetParent(HScreen);
	::SetParent(HScreen, HMain);
	::ShowWindow(hParent, SW_HIDE);
	
	m_slider.SetRange(0, sum_time);//设置滑动范围

	//AfxMessageBox(_T("位置1"));
	//m_slider.SetTicFreq(1);//每10个单位画一刻度
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cvideo_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cvideo_mfcDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}
void Cvideo_mfcDlg::OnDestroy()
{
	capture.release();
	
	CDialogEx::OnDestroy();
	SendMessage(WM_QUIT);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cvideo_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



