/*
�����������ƶȺ;���ļ���

���ƶȣ�
���н�����
�����ϵ��
��Dice
��Jaccard

����
�����Ͼ���
��ŷ�Ͼ���
�����Ͼ���
��Jffreys & Matusita ����
��Mahalanobis ���룬δʵ�֣�Э�������
��Camberra ���루Lance ���룬Williams ���룩
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;


	double dotProduct(const vector<double>& v1, const vector<double>& v2);

	double module(const vector<double>& v);


	// �н�����
	double cosine(const vector<double>& v1, const vector<double>& v2);

	double mean(const vector<double>& v);

	double cov(const vector<double>& v1, const vector<double>& v2);

	// ���ϵ��
	double coefficient(const vector<double>& v1, const vector<double>& v2);

	// Dice ϵ��
	double dice(const vector<double>& v1, const vector<double>& v2);

	// Jaccard ϵ��
	double jaccard(const vector<double>& v1, const vector<double>& v2);

	// Minkowsky ����
	double minkowsky(const vector<double>& v1, const vector<double>& v2, double m);

	// Euclidean ����
	double euclidean(const vector<double>& v1, const vector<double>& v2);

	// Manhattan ����
	double manhattan(const vector<double>& v1, const vector<double>& v2);

	// Jffreys & Matusita ����
	double jffreysMatusita(const vector<double>& v1, const vector<double>& v2);

	// Mahalanobis ����
	double mahalanobis(const vector<double>& v1, const vector<double>& v2);

	// Camberra ���루Lance ���룬Williams ���룩
	double camberra(const vector<double>& v1, const vector<double>& v2);

	double compareHist(const vector<double>& v1, const vector<double>& v2, const int method);
