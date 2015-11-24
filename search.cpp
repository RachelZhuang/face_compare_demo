#include "search.h"

#define compare_method 0



static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator ) {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

bool strict_weak_ordering(const pair<int, double> a, const pair<int, double> b)
{
	return a.second > b.second;
}

vector<int> search(Mat &m, vector<Mat> &imageset, int rad, int pts, std::string mapping)
{
	vector<int> a;
	string fn_csv = "F:\\test.csv";
	Mat sourceimage=m;

	MatND originalhist=gethistway1(sourceimage);

	//vector<double> originalhist=getLBPhist(sourceimage,rad,pts,mapping);

	double simil;

	// These vectors hold the images and corresponding labels.

	vector<int> labels;

	pair<int, double> temp;
	vector<pair<int, double>> store;
	// Read in the data. This can fail if no valid
	// input filename is given.
	read_csv(fn_csv, imageset, labels);

//	imshow("test",imageset[0]);
	
	int i = 0;
	MatND temphist;

	//vector<double> temphist;


	//imshow("1213", imageset[1]);

	vector<Rect> faces;
	for (Mat &m : imageset)
	{
		m = DetectFace(m,faces);
		m = m(faces[0]);

	//	temphist = getLBPhist(m,rad, pts, mapping);

		temphist = gethistway1(m);

	
	//	simil = compareHist(temphist, originalhist, compare_method);

		simil = cv::compareHist(originalhist,temphist,0);

		temp = make_pair(labels[i++], simil);

		store.push_back(temp);

	}
	sort(store.begin(), store.end(), strict_weak_ordering);
	
	
	for (pair<int, double>	&m : store) 
	a.push_back(m.first);

	return a;
}
Mat GetWholeHistLBPWay(Mat imgOrg)
{
	cvtColor(imgOrg, imgOrg, CV_BGR2GRAY);
	resize(imgOrg, imgOrg, Size(130, 150));

	int XStep = 18;
	int YStep = 21;

	Mat TempImage,  FinalHist = Mat::zeros(59, 49, CV_64F);
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
	 FinalHist.reshape(1,1);

	ofstream ofs;
	ofs.open("F:\\test.txt" ,ios::out);
	for (int i = 0; i < FinalHist.rows; i++)
	for (size_t j = 0; j < FinalHist.cols; j++)
	{
		if (i > 0) ofs << ", ";
		ofs << FinalHist.at<double>(i,j);
	}
	ofs << FinalHist.size();
	ofs << endl;
	ofs.close();
	return FinalHist;
}

vector<double> GetPartHistLBPWay(Mat imgOrg)
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

Mat DetectFace(Mat frame, vector<Rect>& faces)
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