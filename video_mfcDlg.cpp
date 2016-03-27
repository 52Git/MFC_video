
// video_mfcDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "video_mfc.h"
#include "video_mfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cvideo_mfcDlg �Ի���



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
		// ����յ�IDΪ1�Ķ�ʱ������Ϣ�����func1����
		if (Isread)
		{
			pos = m_slider.GetPos();
			m_slider.SetPos(pos + 1);
		}
		break;
	case 2:
		// ����յ�IDΪ2�Ķ�ʱ������Ϣ�����func2����      
		
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


// Cvideo_mfcDlg ��Ϣ�������

BOOL Cvideo_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	Isread = false;
	capture.open("test.mp4");
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//��֡��
	int rate = capture.get(CV_CAP_PROP_FPS);//1���֡��
	
	
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
	
	m_slider.SetRange(0, sum_time);//���û�����Χ

	//AfxMessageBox(_T("λ��1"));
	//m_slider.SetTicFreq(1);//ÿ10����λ��һ�̶�
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cvideo_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cvideo_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



