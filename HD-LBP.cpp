#include "HD-LBP.h"



float CosAngle(vector<int>& hist1, vector<int>& hist2)
{
	int temp1 = 0, temp2 = 0, temp3 = 0;
	for (int i = 0; i <hist1.size(); i++)
	{
		temp1 += hist1[i] * hist2[i];
		temp2 += hist1[i] * hist1[i];
		temp3 += hist2[i] * hist2[i];
	}

	return temp1 / (sqrt(temp2)*sqrt(temp3));

}
void ReadGlobalParamFromFile(string path){
	cout << "Loading GlobalParam..." << endl;
	ifstream fin;
	fin.open(path);
	fin >> global_params.bagging_overlap;
	fin >> global_params.max_numtrees;
	fin >> global_params.max_depth;
	fin >> global_params.max_numthreshs;
	fin >> global_params.landmark_num;
	fin >> global_params.initial_num;
	fin >> global_params.max_numstage;

	for (int i = 0; i< global_params.max_numstage; i++){
		fin >> global_params.max_radio_radius[i];
	}

	for (int i = 0; i < global_params.max_numstage; i++){
		fin >> global_params.max_numfeats[i];
	}
	cout << "Loading GlobalParam end" << endl;
	fin.close();
}



vector<int> HDLBP(Mat& image){
	extern string cascadeName;
	string inputName;
	CvCapture* capture = 0;
	Mat frame, frameCopy;
	bool tryflip = false;
	double scale = 1.3;
	CascadeClassifier cascade;

	vector<int> repre;


	// -- 0. Load LBF model
	LBFRegressor regressor;
	regressor.Load(modelPath + "LBF.model");

	// -- 1. Load the cascades
	if (!cascade.load(cascadeName)){
		cerr << "ERROR: Could not load classifier cascade" << endl;
		//  return -1;
	}



	if (!image.empty()){
		cout << "In image read" << endl;
		repre = detectAndDraw(image, cascade, regressor, scale, tryflip);
		waitKey(0);
	}
	return repre;
}
bool Crop(const Mat inputFaceImage, const Mat_<double> current_shape, Mat &outputFaceImage, vector< pair<double, double> > &newLandmarks)
{
	//	Mat_<double> current_shape = regressor.Predict(gray, boundingbox, 1);
	vector< pair<double, double> > landmarks;
	for (int i = 0; i < current_shape.rows; i++)
	{
		pair<double, double> pt;
		pt.first = current_shape(i, 0);
		pt.second = current_shape(i, 1);
		landmarks.push_back(pt);
	}

	double eyeXdis = landmarks[16].first - landmarks[0].first;
	double eyeYdis = landmarks[16].second - landmarks[0].second;
	double angle = atan(eyeYdis / eyeXdis);
	double degree = angle * 180 / CV_PI;

	//rotate image and corresponding points to make the eyes horizontal even
	for (int i = 0; i<landmarks.size(); i++) {
		pair<double, double> pt;
		pt.first = (landmarks[i].first - landmarks[0].first)*cos(angle) + (landmarks[i].second - landmarks[0].second)*sin(angle)\
			+ landmarks[0].first;
		pt.second = (landmarks[i].second - landmarks[0].second)*cos(angle) - (landmarks[i].first - landmarks[0].first)*sin(angle)\
			+ landmarks[0].second;
		newLandmarks.push_back(pt);
	}
	Mat rotMat = getRotationMatrix2D(Point2f(landmarks[0].first, landmarks[0].second), degree, 1.0);
	//printf("%d %d\n", inputFaceImage.cols, inputFaceImage.rows);
	warpAffine(inputFaceImage, outputFaceImage, rotMat, Size(inputFaceImage.cols, inputFaceImage.rows));

	//crop face region from the image
	double eyeDist = abs((newLandmarks[0].first - newLandmarks[16].first));
	double eyeCenterX = (newLandmarks[0].first + newLandmarks[16].first) / 2 + int(eyeDistanceX*eyeDist);
	double eyeCenterY = (newLandmarks[0].second + newLandmarks[16].second) / 2 + int(eyeDistanceUp*eyeDist);
	int leftbound = int((eyeCenterX - eyeDistanceX*eyeDist));
	int rightbound = int((eyeCenterX + eyeDistanceX*eyeDist));
	int topbound = int((eyeCenterY - eyeDistanceUp*eyeDist));
	int bottombound = int((eyeCenterY + eyeDistanceDown*eyeDist));
	copyMakeBorder(outputFaceImage, outputFaceImage, int(eyeDistanceUp*eyeDist), int(eyeDistanceDown*eyeDist),
		int(eyeDistanceX*eyeDist), int(eyeDistanceX*eyeDist), BORDER_CONSTANT, Scalar(0));
	/*
	if (leftbound < 0 || topbound < 0 || rightbound >=outputFaceImage.cols || bottombound >=outputFaceImage.rows) {
	cerr<<"Error: face out of bound!\n";
	return false;
	}
	*/
	for (int i = 0; i<newLandmarks.size(); i++)
	{
		newLandmarks[i].first = newLandmarks[i].first - leftbound + int(eyeDistanceX*eyeDist);
		newLandmarks[i].second = newLandmarks[i].second - topbound + int(eyeDistanceUp*eyeDist);
	}
	outputFaceImage = outputFaceImage(Rect(leftbound, topbound, rightbound - leftbound, bottombound - topbound));
	outputFaceImage = outputFaceImage;//(Rect(leftbound, topbound, rightbound-leftbound, bottombound-topbound));      
	return true;
}


vector<int> detectAndDraw(Mat& img, CascadeClassifier& cascade, LBFRegressor& regressor, double scale, bool tryflip){
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] = { CV_RGB(0, 0, 255),
		CV_RGB(0, 128, 255),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 255, 0),
		CV_RGB(255, 128, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(255, 0, 0),
		CV_RGB(255, 0, 255) };
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	cvtColor(img, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	// --Detection
	t = (double)cvGetTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	if (tryflip){
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			| CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;
	printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));

	// --Alignment
	t = (double)cvGetTickCount();
	Mat_<double> current_shape;
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++){
		Point center;
		Scalar color = colors[i % 8];
		BoundingBox boundingbox;

		boundingbox.start_x = r->x*scale;
		boundingbox.start_y = r->y*scale;
		boundingbox.width = (r->width - 1)*scale;
		boundingbox.height = (r->height - 1)*scale;
		boundingbox.centroid_x = boundingbox.start_x + boundingbox.width / 2.0;
		boundingbox.centroid_y = boundingbox.start_y + boundingbox.height / 2.0;

		t = (double)cvGetTickCount();
		current_shape = regressor.Predict(gray, boundingbox, 1);
		t = (double)cvGetTickCount() - t;
		printf("alignment time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));


		LBPFeatureExtractor lbpFeatureExtractor(scales, patchSize, gridNumX, gridNumY, true);
		//int *feature = new int[totalDim];
		//ofstream flbp("F:\\123.txt");

		Mat temp_img;
		vector< pair<double, double> > newLandmarks, Landmarks_choosen;
		pair<double, double> point;

		bool crop = Crop(img, current_shape, temp_img, newLandmarks);

		const int landmarkPosition[] = { 0, 4, 5, 9, 19, 22, 25, 28, 13, 14, 18, 31, 34, 37, 40, 43 };
		for (int i = 0; i < landmarkNum; i++){
			point.first = newLandmarks[landmarkPosition[i]].first;
			point.second = newLandmarks[landmarkPosition[i]].second;
			Landmarks_choosen.push_back(point);
		}
		int *feature = new int[totalDim];

		lbpFeatureExtractor.extractAt(temp_img, Landmarks_choosen, feature);

		vector<int>  repre;
		for (int i = 0; i < totalDim; i++)
		{
			repre.push_back(feature[i]);
		}
		return repre;
	}

}