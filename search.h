/*
* Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
* Released to public domain under terms of the BSD Simplified license.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of the organization nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*   See <http://www.opensource.org/licenses/bsd-license>
*/

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include "getLBPhist.h"
#include "compareHist.hpp"

using namespace cv;
using namespace std;



	static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');

	bool strict_weak_ordering(const pair<int, double> a, const pair<int, double> b);

	MatND gethistway1(Mat m);

	Mat DetectFace(Mat frame, vector<Rect>& faces);

	vector<int> search(Mat &m, vector<Mat> &imageset,int rad, int pts, std::string mapping);

	Mat GetWholeHistLBPWay(Mat imgOrg);

	vector<double> GetPartHistLBPWay(Mat imgOrg);

	double GetChiSquare(Mat hist1, Mat hist2);

