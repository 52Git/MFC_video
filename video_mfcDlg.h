
// video_mfcDlg.h : ͷ�ļ�
//
#include<opencv2\opencv.hpp>
#include "afxcmn.h"
using namespace std;
using namespace cv;
#pragma once


// Cvideo_mfcDlg �Ի���
class Cvideo_mfcDlg : public CDialogEx
{
// ����
public:
	Cvideo_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIDEO_MFC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	bool Isread;
	VideoCapture capture;
	char windowname[20];
	CRect screenRect;
	// ���ɵ���Ϣӳ�亯��
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
