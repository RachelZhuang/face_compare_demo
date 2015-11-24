
// face_compare_demoDlg.h : 头文件
//

#pragma once

#include <opencv2/opencv.hpp>

#include <iostream>  
#include <fstream> 

#include "CvvImage.h"
#include "search.h"
#include "stdafx.h"
#include "GetChiSquare.h"
#include "afxwin.h"
#include  "HD-LBP.h"


using namespace cv;
// Cface_compare_demoDlg 对话框
class Cface_compare_demoDlg : public CDialogEx
{
// 构造
public:
	Cface_compare_demoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FACE_COMPARE_DEMO_DIALOG };


	


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
	void ShowImageTo(Mat image, UINT dst);
	vector<double> GetPartHistLBPWay(Mat imgOrg);
	Mat GetWholeHistLBPWay(Mat imgOrg);
	Mat DetectFace(Mat frame, vector<Rect>& faces);

	VideoCapture camera_capture;
	Mat current_camera_frame, camera_normal_face_image;//current_camera_frame是摄像头实时画面， camera_normal_face_image是捕捉后经人脸检测的图片

	vector<Rect> faces;
	Mat file_certificate_image,file_certificate_face_image;//file_certificate_image是未经人脸检测的证件照,file_certificate_face_image是检测之后的人脸照
	
	Mat file_nomal_image, file_normal_face_image;//file_nomal_image是未经人脸检测的普通照，file_nomal_face_image是检测之后的人脸照
	
	
	bool normal_image_source_choose=1;

	unsigned char simil_compare_way_choose;

	bool weight_or_not;
	

	afx_msg void OnBnClickedRadiocamera();
	afx_msg void OnBnClickedRadiofile();
	afx_msg void OnBnClickedRadiochisquare();
	afx_msg void OnBnClickedRadioeulerdis();
	afx_msg void OnBnClickedRadiocosangle();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
