/*
特征向量相似度和距离的计算

相似度：
·夹角余弦
·相关系数
·Dice
·Jaccard

距离
·明氏距离
·欧氏距离
·马氏距离
·Jffreys & Matusita 距离
·Mahalanobis 距离，未实现，协方差矩阵
·Camberra 距离（Lance 距离，Williams 距离）
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;


	double dotProduct(const vector<double>& v1, const vector<double>& v2);

	double module(const vector<double>& v);


	// 夹角余弦
	double cosine(const vector<double>& v1, const vector<double>& v2);

	double mean(const vector<double>& v);

	double cov(const vector<double>& v1, const vector<double>& v2);

	// 相关系数
	double coefficient(const vector<double>& v1, const vector<double>& v2);

	// Dice 系数
	double dice(const vector<double>& v1, const vector<double>& v2);

	// Jaccard 系数
	double jaccard(const vector<double>& v1, const vector<double>& v2);

	// Minkowsky 距离
	double minkowsky(const vector<double>& v1, const vector<double>& v2, double m);

	// Euclidean 距离
	double euclidean(const vector<double>& v1, const vector<double>& v2);

	// Manhattan 距离
	double manhattan(const vector<double>& v1, const vector<double>& v2);

	// Jffreys & Matusita 距离
	double jffreysMatusita(const vector<double>& v1, const vector<double>& v2);

	// Mahalanobis 距离
	double mahalanobis(const vector<double>& v1, const vector<double>& v2);

	// Camberra 距离（Lance 距离，Williams 距离）
	double camberra(const vector<double>& v1, const vector<double>& v2);

	double compareHist(const vector<double>& v1, const vector<double>& v2, const int method);
