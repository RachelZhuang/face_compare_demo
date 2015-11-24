
#include "GetChiSquare.h"

/* Function Definitions */
double GetWeightedChiSquare(const double LBPHist1[2891], const double LBPHist2[2891])
{
	double ChiSquareResult;
	int i;
	int j;
	double a;
	static const unsigned char weight[49] = { 2, 1, 1, 1, 1, 1, 1, 2, 4, 4, 1, 4, 4, 2, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 1, 1,
		0, 0, 1, 1, 1, 1, 1, 0 };

	ChiSquareResult = 0.0;
	for (i = 0; i < 59; i++) {
		for (j = 0; j < 49; j++) {
			if (LBPHist1[i + 59 * j] + LBPHist2[i + 59 * j] > 0.0) {
				/*  ChiSquareResult=ChiSquareResult+weight(1,j)/w*square(LBPHist1(i,j)-LBPHist2(i,j))/(LBPHist1(i,j)+LBPHist2(i,j)); */
				a = LBPHist1[i + 59 * j] - LBPHist2[i + 59 * j];
				ChiSquareResult += (double)weight[j] / 55.0 * (a * a) / (LBPHist1[i + 59
					* j] + LBPHist2[i + 59 * j]);
				//a = LBPHist1[i + 59 * j] - LBPHist2[i + 59 * j];
				//ChiSquareResult +=  (a * a) / (LBPHist1[i + 59
				//	* j] + LBPHist2[i + 59 * j]);
			}
		}
	}

	return ChiSquareResult;
}

double  GetNonWeightedChiSquare(const double LBPHist1[2891], const double LBPHist2[2891])
{
	double ChiSquareResult;
	int i;
	int j;
	double a;

	ChiSquareResult = 0.0;
	for (i = 0; i < 59; i++) {
		for (j = 0; j < 49; j++) {
			if (LBPHist1[i + 59 * j] + LBPHist2[i + 59 * j] > 0.0) {

				a = LBPHist1[i + 59 * j] - LBPHist2[i + 59 * j];
				ChiSquareResult += 1.0/49*(a * a) / (LBPHist1[i + 59
					* j] + LBPHist2[i + 59 * j]);

			}
		}
	}

	return ChiSquareResult;
}

double GetEulerDst(const double LBPHist1[2891], const double LBPHist2[2891])
{
	double result = 0;
	for (int i = 0; i < 2891; i++)
	{
		result += (LBPHist1[i] - LBPHist2[i])*(LBPHist1[i] - LBPHist2[i]);
	}
	return sqrt(result);
}

double GetCosAngle(const double LBPHist1[2891], const double LBPHist2[2891])
{
	double temp1 = 0,temp2=0,temp3=0;
	for (int i = 0; i < 2891; i++)
	{
		temp1 +=(LBPHist1[i] * LBPHist2[i]);
		temp2 += (LBPHist1[i] * LBPHist1[i]);
		temp3 += (LBPHist2[i] * LBPHist2[i]);

	}
	return temp1 / (sqrt(temp2)*sqrt(temp3));
}