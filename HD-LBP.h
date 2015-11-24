//
//  Facedetect.cpp
//  myopencv
//
//  Created by lequan on 1/24/15.
//  Copyright (c) 2015 lequan. All rights reserved.
//
#include "LBF.h"
#include "LBFRegressor.h"
#include "LBPFeatureExtractor.h"


using namespace std;
using namespace cv;

const float eyeDistanceX = 0.6;
const float eyeDistanceUp = 0.6;
const float eyeDistanceDown = 0.6;
const int notFace = 0.5;
const vector<int>scales = { 300, 212, 150, 106, 75 };
const int patchSize = 10;
const int gridNumX = 4;
const int gridNumY = 4;
const int lbpDim = 59;
const int landmarkNum = 16;
const int totalDim = scales.size()*gridNumX*gridNumY*lbpDim*landmarkNum;

// Params global_params;
// cv::string modelPath = "E://BaiduYunDownload//model//";
//cv::string cascadeName = "lbpcascade_frontalface.xml";

vector<int> detectAndDraw(Mat& img, CascadeClassifier& cascade, LBFRegressor& regressor, double scale, bool tryflip);


vector<int> HDLBP(const char* inputname);

bool Crop(const Mat inputFaceImage, const Mat_<double> current_shape, Mat &outputFaceImage, vector< pair<double, double> > &newLandmarks);

vector<int> detectAndDraw(Mat& img, CascadeClassifier& cascade, LBFRegressor& regressor, double scale, bool tryflip); 

void ReadGlobalParamFromFile(string path);
//int main(int argc, const char** argv){
//
//
//	ReadGlobalParamFromFile("E://BaiduYunDownload//model//LBF.model");
//
//	vector<int> repre1;
//	repre1 = HDLBP("F:\\reserve1.jpg");
//
//
//}