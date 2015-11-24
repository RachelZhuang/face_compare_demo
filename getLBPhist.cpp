#include "getLBPhist.h"

Mat GetWholeHistLBPWay(Mat imgOrg)
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

