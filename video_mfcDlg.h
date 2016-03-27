
// video_mfcDlg.h : 头文件
//
#include<opencv2\opencv.hpp>
#include "afxcmn.h"
using namespace std;
using namespace cv;
#pragma once


// Cvideo_mfcDlg 对话框
class Cvideo_mfcDlg : public CDialogEx
{
// 构造
public:
	Cvideo_mfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIDEO_MFC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	bool Isread;
	VideoCapture capture;
	char windowname[20];
	CRect screenRect;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	//afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStop();
	CSliderCtrl m_slider;
};
