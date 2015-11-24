
// face_compare_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "face_compare_demo.h"
#include "face_compare_demoDlg.h"
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
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cface_compare_demoDlg �Ի���



Cface_compare_demoDlg::Cface_compare_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cface_compare_demoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



BEGIN_MESSAGE_MAP(Cface_compare_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Cface_compare_demoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cface_compare_demoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cface_compare_demoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &Cface_compare_demoDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &Cface_compare_demoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_RADIOCAMERA, &Cface_compare_demoDlg::OnBnClickedRadiocamera)
	ON_BN_CLICKED(IDC_RADIOFILE, &Cface_compare_demoDlg::OnBnClickedRadiofile)
	ON_BN_CLICKED(IDC_RADIOCHISQUARE, &Cface_compare_demoDlg::OnBnClickedRadiochisquare)
	ON_BN_CLICKED(IDC_RADIOEULERDIS, &Cface_compare_demoDlg::OnBnClickedRadioeulerdis)
	ON_BN_CLICKED(IDC_RADIOCOSANGLE, &Cface_compare_demoDlg::OnBnClickedRadiocosangle)
	ON_BN_CLICKED(IDC_RADIO1, &Cface_compare_demoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Cface_compare_demoDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// Cface_compare_demoDlg ��Ϣ�������

BOOL Cface_compare_demoDlg::OnInitDialog()
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
	
	CheckDlgButton(IDC_RADIOFILE, 1);
	OnBnClickedRadiofile();

	CheckDlgButton(IDC_RADIO1, 1);
	OnBnClickedRadio1();

	CheckDlgButton(IDC_RADIOCHISQUARE, 1);
	OnBnClickedRadiochisquare();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cface_compare_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cface_compare_demoDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cface_compare_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void  Cface_compare_demoDlg::ShowImageTo(Mat image, UINT dst)
{
	CvvImage cvvImg; //CvvImage��

	CWnd *pwnd = GetDlgItem(dst);
	HDC hdc = pwnd->GetDC()->GetSafeHdc();
	CRect rect;
	pwnd->GetClientRect(&rect);

	IplImage img = image;
	cvvImg.CopyOf(&img);//����ͼ�񵽵�ǰ��CvvImage������  
	cvvImg.DrawToHDC(hdc, &rect);
}


void Cface_compare_demoDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	camera_capture.open(0);
	SetTimer(1, 10, NULL);

}

//void Cface_compare_demoDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	camera_capture >> current_camera_frame;
//	current_camera_frame = DetectFace(current_camera_frame,faces);
//	ShowImageTo(current_camera_frame, IDC_STATICSHOWCAMERA);
//	CDialogEx::OnTimer(nIDEvent);
//}


void Cface_compare_demoDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);


	camera_normal_face_image = current_camera_frame(faces[0]);
//	imwrite("F:\\reserve_camera_normal_face_image.jpg", camera_normal_face_image);
	ShowImageTo(camera_normal_face_image, IDC_STATICSHOWCATCHFACE);

}


void Cface_compare_demoDlg::OnBnClickedButton4()//��δ����������֤����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files(*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||"), NULL
		);										// ѡ��ͼƬ��Լ��
	dlg.m_ofn.lpstrTitle = _T("Open Image");	// ���ļ��Ի���ı�����
	if (dlg.DoModal() != IDOK)					// �ж��Ƿ���ͼƬ
		return;

	CString mPath = dlg.GetPathName();			// ��ȡͼƬ·��
	USES_CONVERSION;
	LPSTR Test = T2A(mPath);
	file_certificate_image = imread(Test);
	ShowImageTo(file_certificate_image, IDC_STATICSHOWFILEFACE);
	file_certificate_face_image = DetectFace(file_certificate_image, faces);//
	file_certificate_face_image = file_certificate_face_image(faces[0]);//
}


void Cface_compare_demoDlg::OnBnClickedButton1()
{
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Mat hist1, hist2;
	
	//GetPartHistLBPWay(file_certificate_face_image);
	
	hist1 = GetWholeHistLBPWay(file_certificate_face_image);



	switch (normal_image_source_choose)
	{
	case 0: hist2 = GetWholeHistLBPWay(camera_normal_face_image);
		break;
	case 1: 
		
		hist2 = GetWholeHistLBPWay(file_normal_face_image);
		break;
	default:
		break;
	}

	double hist_array1[2891], hist_array2[2891];


	hist1=hist1.reshape(1, 1);
	for (int i = 0; i < hist1.cols; i++)
	{
		hist_array1[i] = hist1.at<double>(0, i);
	}

	hist2 = hist2.reshape(1, 1);
	for (int i = 0; i < hist2.cols; i++)
	{
		hist_array2[i] = hist2.at<double>(0, i);
	}
	double simil = 0;
	switch (simil_compare_way_choose)
	{
	case 0:
		switch (weight_or_not)
	{
	case 0:
		simil = GetWeightedChiSquare(hist_array1, hist_array2);
		break;
	case 1:
		simil = GetNonWeightedChiSquare(hist_array1, hist_array2);
		break;
	}
		break;
	case 1:
		simil = GetEulerDst(hist_array1, hist_array2);
		break;
	case 2:
		simil = GetCosAngle(hist_array1, hist_array2);
		break;
	}
	/*ReadGlobalParamFromFile(modelPath + "LBF.model");
	vector<int> hist1 = HDLBP(file_certificate_image);

	vector<int> hist2 = HDLBP(file_nomal_image);

	
	float simil = CosAngle(hist1,hist2);*/

	CString StrSimil;
	StrSimil.Format(L"%f", simil);
	SetDlgItemText(IDC_EDITRESULIT, StrSimil);
}
Mat Cface_compare_demoDlg::DetectFace(Mat frame, vector<Rect>& faces)
{
	faces.clear();
	CascadeClassifier face_cascade;
	face_cascade.load("E:\\opencv\\sources\\data\\lbpcascades\\lbpcascade_frontalface.xml");

	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);

	}
	//-- Show what you got
	return frame;
}
Mat Cface_compare_demoDlg::GetWholeHistLBPWay(Mat imgOrg)
{
	cvtColor(imgOrg, imgOrg, CV_BGR2GRAY);
	resize(imgOrg, imgOrg, Size(130, 150));

	int XStep = 18;
	int YStep = 21;

	Mat TempImage, FinalHist = Mat::zeros(59, 49, CV_64F);
	vector<double> TempHist;

	int j = 0;
	for (int YLocation = 0; YLocation < 7; YLocation++)
	for (int XLocation = 0; XLocation < 7; XLocation++)
	{
		TempImage = imgOrg(cv::Rect(XLocation*XStep, YLocation*YStep, XStep, YStep));
		TempHist = GetPartHistLBPWay(TempImage);

		for (int i = 0; i < TempHist.size(); i++)
		{
			FinalHist.at<double>(i, j) = TempHist[i];
		};
		j++;
	}
	//FinalHist.t();
	FinalHist.reshape(1, 1);

	
	return FinalHist;
}

vector<double> Cface_compare_demoDlg::GetPartHistLBPWay(Mat imgOrg)
{
	int rad = 2;
	int pts = 8;
	std::string mapping = "u2";
	bool outputHist = 1, normalizeHist = 1;

	imgOrg.convertTo(imgOrg, CV_64F);

	Mat lbpImg = Mat(imgOrg.size(), CV_8UC1, Scalar(0));

	// Create an LBP instance of type "mapping" using "pts" support points
	LBP lbp(pts, LBP::strToType(mapping));

	for (int i = 0; i < imgOrg.channels(); i++) {
		// Copy channel i
		Mat img(imgOrg.size(), imgOrg.depth(), 1);
		const int from_to1[] = { i, 0 };
		mixChannels(&imgOrg, 1, &img, 1, from_to1, 1);

		// Calculate the descriptor
		lbp.calcLBP(img, rad, true);

		// Copy lbp image
		const int from_to2[] = { 0, i };
		Mat tmpImg = lbp.getLBPImage();
		mixChannels(&tmpImg, 1, &lbpImg, 1, from_to2, 1);
	}


	vector<double> part_hist = lbp.calcHist().getHist(normalizeHist);

	return part_hist;

}


void Cface_compare_demoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	camera_capture >> current_camera_frame;
	imwrite("F:\\reserve_camera_frame.jpg", current_camera_frame);//���δ����������ͼƬ
	current_camera_frame = DetectFace(current_camera_frame,faces);
	ShowImageTo(current_camera_frame, IDC_STATICSHOWCAMERA);
	CDialogEx::OnTimer(nIDEvent);
}


void Cface_compare_demoDlg::OnBnClickedButton5()//��δ������������ͨ��
{
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files(*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||"), NULL
		);										// ѡ��ͼƬ��Լ��
	dlg.m_ofn.lpstrTitle = _T("Open Image");	// ���ļ��Ի���ı�����
	if (dlg.DoModal() != IDOK)					// �ж��Ƿ���ͼƬ
		return;

	CString mPath = dlg.GetPathName();			// ��ȡͼƬ·��
	USES_CONVERSION;
	LPSTR Test = T2A(mPath);
	file_nomal_image = imread(Test);
	ShowImageTo(file_nomal_image, IDC_STATICSHOWNORMALIMAGE);
	file_normal_face_image = DetectFace(file_nomal_image, faces);
	file_normal_face_image = file_normal_face_image(faces[0]);
}


void Cface_compare_demoDlg::OnBnClickedRadiocamera()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	normal_image_source_choose = 0;
}


void Cface_compare_demoDlg::OnBnClickedRadiofile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	normal_image_source_choose = 1;
}


void Cface_compare_demoDlg::OnBnClickedRadiochisquare()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	simil_compare_way_choose =0;
}


void Cface_compare_demoDlg::OnBnClickedRadioeulerdis()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	simil_compare_way_choose = 1;
}


void Cface_compare_demoDlg::OnBnClickedRadiocosangle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	simil_compare_way_choose =2;
}


void Cface_compare_demoDlg::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	weight_or_not = 0;
}


void Cface_compare_demoDlg::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	weight_or_not = 1;
}
